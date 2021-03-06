from PyQt4 import QtCore, QtGui
from PyQt4.QtCore import QObject, pyqtSignal
from Queue import Queue
import serial
from datapacking import data_to_packets
import traceback
import numpy as np
import time
class POVDataLink(QtCore.QThread):

    bt_rx_queue = Queue()
    #bt_tx_queue = Queue()

    mn_rx_queue = Queue()
    #mn_tx_queue = Queue()

    new_mn_rx = pyqtSignal()
    new_mn_driver_state = pyqtSignal()

    new_bt_rx = pyqtSignal()
    new_bt_tx = pyqtSignal(str)
    new_bt_driver_state = pyqtSignal()


    mn_driver_state = ""
    bt_driver_state = ""

    mn_request_port_flag = False
    bt_request_port_flag = False

    radio_ack_sig = pyqtSignal(int)

    radio_cmd_line_sig = pyqtSignal(str, int, int, int)
    mn_cmd_line_sig = pyqtSignal(str, int, int, int)

    def __init__(self):
        super(POVDataLink, self).__init__()
        print("Starting datalink...")
        #self.start()

        self.main_driver = POVMainBoardDriver()
        self.main_driver.request_port_sig.connect(self.mn_request_port)
        self.main_driver.new_rx_sig.connect(self.mn_rx_handler)
        self.main_driver.new_message_sig.connect(self.mn_driver_state_change_handler)

        self.radio_driver = POVRadioBoardDriver()
        self.radio_driver.request_port_sig.connect(self.bt_request_port)
        self.radio_driver.new_rx_sig.connect(self.bt_rx_handler)
        self.radio_driver.new_message_sig.connect(self.bt_driver_state_change_handler)

        self.radio_ack_sig.connect(self.radio_driver.packetAcked)

        self.com_tx_port = None
        self.com_rx_port = None

        self.radio_ser = None

        self.last_packet_sent = None
        self.bt_rx_line = []

        pass

    def mn_rx_handler(self, string):

        self.mn_rx_queue.put(chr(string))
        self.new_mn_rx.emit()

    def mn_driver_next_byte(self):
        if(not self.mn_rx_queue.empty()):
            return self.mn_rx_queue.get()

    def mn_driver_state_change_handler(self, string):
        self.mn_driver_state = string
        self.new_mn_driver_state.emit()

    def mn_driver_get_state(self):
        return self.mn_driver_state

    def mn_transmit_message(self, data):
        self.main_driver.submit_for_transmit(data, "MSG")

    def mn_set_motor_speed(self, data):
        self.main_driver.submit_for_transmit(data, "SPD")

    def bt_driver_state_change_handler(self, string):
        self.bt_driver_state = string
        self.new_bt_driver_state.emit()

    def bt_driver_get_state(self):
        return self.bt_driver_state

    def bt_rx_handler(self, char):

        #self.bt_cmd_line.addChar(char)
        self.bt_rx_line.append(char)
        self.bt_rx_line_str = [chr(c) for c in self.bt_rx_line]
        if (str(char) == '\n'):
            print "Line Received: %s" % ''.join(self.bt_rx_line_str)
        if ("ACK" in ''.join(self.bt_rx_line_str) and "ACK" in ''.join(self.bt_rx_line_str[-5:-2])):
            num = self.bt_rx_line[-1]
            self.radio_ack_sig.emit(num)
            self.radio_cmd_line_sig.emit("Ack Received: %d" % num, 180, 230, 255)
            self.bt_rx_line = []

        else:
            self.bt_rx_queue.put(chr(char))
            self.new_bt_rx.emit()

    def bt_driver_rx_queue_empty(self):
        return self.bt_rx_queue.empty()

    def bt_driver_next_byte(self):
        if(not self.bt_rx_queue.empty()):
            return self.bt_rx_queue.get()
        else:
            return None
    #def bt_tx_handler(self, string):
    #    for c in string:
    #        self.bt_tx_queue.put(c)

    def bt_transmit_message(self, data):
        self.radio_driver.submit_for_transmit(data, "MSG")

    def bt_transmit_image(self, data):
        self.radio_driver.submit_image_for_transmit(data)

    def get_available_ports(self):
        ports = serial.tools.list_ports.comports()
        return ports

    def search_com_ports(self):

        responses = []
        ports = serial.tools.list_ports.comports()

        for port in ports:
            try:
                #print "trying port %s"%(str(port))
                ser = serial.Serial(port[0], 115200, timeout=1, write_timeout=0, inter_byte_timeout = 0.2)
                #print "port opened..."
            except:
               # traceback.print_exc()
                continue
            #print "Flushing input"
            ser.flushInput()
            #print "writing"
            ser.write("*IDN?\r\n")
            #print "reading"

            responses.append((port[0], ser.readline()))
            #print "read, ", responses[-1]
            #print "closing..."
            #if(not ("3DRadio" in responses[-1][1])):
            ser.close()
            #else:
             #   self.radio_ser = ser
            #print "closed"
        return responses

    def mn_request_port(self):
        self.mn_request_port_flag = True

    def bt_request_port(self):
        self.bt_request_port_flag = True


    def run(self):
        self.main_driver.start()
        self.radio_driver.start()
        while(1):
            self.msleep(500)
            if(self.mn_request_port or self.bt_request_port_flag):
               # print "Received prot request!"
                responses = self.search_com_ports()
                #print "Responses:", responses

                if(self.mn_request_port_flag):
                    for port_resp_pair in responses:
                        if ("3DPOV" in port_resp_pair[1]):
                            #print("Found 3dpov port")
                            self.mn_request_port_flag = False
                            self.main_driver.set_rx_port(port_resp_pair[0])
                            self.main_driver.set_tx_port(port_resp_pair[0])
                if(self.bt_request_port_flag):
                    for port_resp_pair in responses:
                        if ("3DRadio" in port_resp_pair[1]):
                            #print("Found 3dRadio port")
                            self.bt_request_port_flag = False
                            self.radio_driver.set_rx_port(port_resp_pair[0])
                            self.radio_driver.set_tx_port(port_resp_pair[0])


class POVCOMPortDriver(QtCore.QThread):


    def __init__(self):
        super(POVCOMPortDriver, self).__init__()


        self.tx_packet_queue = Queue()

        self.com_tx_port = None
        self.com_rx_port = None

        self.connected = 0
        self.disconnected = 1
        self.requesting_port = 2
        self.establishing_connection = 3

        self.serialState = self.disconnected
        # self.connected = 0
        # self.disconnected = 1
        # self.requesting_port = 2
        # self.establishing_connection = 3

        # self.serialState = self.disconnected
        # self.com_rx_port = None
        #self.start()

    def request_port(self):
        self.request_port_sig.emit()

    def set_rx_port(self, port):
        self.com_rx_port = port

    def get_rx_port(self):
        return self.com_rx_port

    def set_tx_port(self, port):
        self.com_tx_port = port

    def get_tx_port(self):
        return self.com_tx_port

    def msg(self, msg):
        print msg
        self.new_message_sig.emit(msg)


    def run(self):
        rx_ser = None
        tx_ser = None
        while (1):

            if (self.serialState == self.disconnected):

                self.serialState = self.requesting_port
                self.set_tx_port(None)
                self.set_rx_port(None)
                self.msg("Disconnected :(")

            elif (self.serialState == self.requesting_port):

                self.msg("Requesting Port...")

                self.request_port()

                while(self.get_rx_port() == None or self.get_tx_port() == None):

                    self.msleep(500)

                print "Found!", self.com_rx_port
                self.serialState = self.establishing_connection

            elif (self.serialState == self.establishing_connection):

                try:
                    # if (rx_ser != None):
                    #     rx_ser.close()
                    # else:
                    #     rx_ser = None
                    self.msg("Opening port %s..." % self.com_rx_port)
                    if( rx_ser == None or not rx_ser.isOpen()):
                        rx_ser = serial.Serial(str(self.com_rx_port), 115200, timeout=0.2)

                    self.msg("%s Connected..." % self.com_rx_port)
                    self.serialState = self.connected
                except:
                    self.msleep(500)
                    traceback.print_exc()
                    self.msg("Incoming port %s could not be opened :(" % (self.com_rx_port))
                    self.serialState = self.disconnected
                    #self.com_rx_port = None

                try:
                    if (tx_ser != None):
                        tx_ser.close()
                    else:
                        tx_ser = None

                    if (self.com_rx_port == self.com_tx_port and rx_ser != None):
                        tx_ser = rx_ser
                    else:
                        self.msg("Opening port %s..." % self.com_tx_port)
                        tx_ser = serial.Serial(str(self.com_tx_port), 115200, timeout=0.2)
                        self.msg("%s Connected..." % self.com_tx_port)
                except:
                    traceback.print_exc()
                    self.msleep(500)
                    self.msg("Outgoing port %s could not be opened :(" % (self.com_tx_port))
                    self.serialState = self.disconnected
                    #self.com_tx_port = None


            elif (self.serialState == self.connected):
                self.msg("Connected to %s!" % self.com_rx_port)
                try:
                    while (1):

                        if (rx_ser.inWaiting()):
                            c = rx_ser.read()
                            self.receive(c)
                            # if ord(c) >= 32 and ord(c) <= 127:
                            #     self.msg("Incoming char: %s" % c);
                            # else:
                            #     self.msg("Incoming byte: [%d]" % ord(c))
                            #print "Incoming %c" % c
                        if (not self.tx_packet_queue.empty()):
                            data = self.tx_packet_queue.get()
                            #print "Found new data in tx queue: %s" % str(data)
                            #if(data != None):
                            tx_ser.write(data)
                            #self.msg("Outgoing: %s " % (data));
                            #self.msleep(100)
                        self.housekeeping()
                        self.yieldCurrentThread()
                except:
                    traceback.print_exc()
                    self.msg("Port error")
                    self.serialState = self.disconnected
                    self.com_rx_port = None
                    self.msleep(500)

class POVMainBoardDriver(POVCOMPortDriver):
    new_message_sig = pyqtSignal(str)
    new_rx_sig = pyqtSignal(int)
    request_port_sig = pyqtSignal()
    def __init__(self):
        super(POVMainBoardDriver, self).__init__()
        print("Starting main board driver...")
        self.packetes = []

    def receive(self, rx_data):
        # print "Received", rx_data
        self.new_rx_sig.emit(int(ord(rx_data)))

    def housekeeping(self):
        pass

    def submit_for_transmit(self, data, data_type):
        if(self.serialState == self.connected):
            # 16 pixels x 3 bytes (RGB) per pixel
            packets = data_to_packets([data], data_type, 1)
            #print "Main tx:", packets
            #for packet in packets:
            #packets.append(ord("\r"))
            packets[0].append(ord("\n"))

            self.tx_packet_queue.put(packets[0])


class POVRadioBoardDriver(POVCOMPortDriver):

    new_message_sig = pyqtSignal(str)
    new_rx_sig = pyqtSignal(int)
    new_tx_sig = pyqtSignal(int)
    request_port_sig = pyqtSignal()
    tx_image_packet_queue = Queue()
    packets = []

    packet_seq_index = 5
    def __init__(self):
        super(POVRadioBoardDriver, self).__init__()
        print("Starting radio board driver...")
        self.connected = 0
        self.disconnected = 1
        self.requesting_port = 2
        self.establishing_connection = 3

        self.serialState = self.disconnected
        self.com_rx_port = None
        self.com_tx_port = None

        self.time_since_last_ack = 0
        self.max_ack_wait_time = 0.2
        self.start()

        self.last_packet_num_sent = 0
        self.last_packet_sent = None

        self.acked_packets = []
        self.time_of_transmit = time.time()
        for a in range(100):
            self.acked_packets.append(False)
    def msg(self, msg):
        print msg
        self.new_message_sig.emit(msg)

    def receive(self, rx_data):
        print "Received", rx_data
        self.new_rx_sig.emit(int(ord(rx_data)))

    def get_last_image_packets(self):
        return self.packets

    def resetAcketPackets(self):
        self.last_packet_num_sent = 0
        for i,p in enumerate(self.acked_packets):
            self.acked_packets[i] = False

    def packetAcked(self, packet_num):
        print "Acking message: %d" %(packet_num)
        self.acked_packets[packet_num] = True

    def continue_image_transmission(self, text):
        # Send another packet only if the last one we have sent has been acked

        if(self.acked_packets[self.last_packet_num_sent]):
            if (not self.tx_image_packet_queue.empty()):
                packet = self.tx_image_packet_queue.get()
                self.last_packet_set = packet
                self.time_of_transmit = time.time()
                self.submit_packet_for_transmit(packet)
                self.last_packet_num_sent = packet[self.packet_seq_index]

        elif(not self.tx_image_packet_queue.empty()):
            if( time.time() - self.time_of_transmit > self.max_ack_wait_time):
                #print "Acknowledge timeout, sending ack request"
                self.time_of_transmit = time.time()
                #
                if(self.last_packet_sent == None):
                    self.submit_packet_for_transmit(['P', 'C', 'K'])
                else:
                    self.submit_packet_for_transmit(self.last_packet_sent)


    def housekeeping(self):
        self.continue_image_transmission(None)
        
    def submit_image_for_transmit(self, data):
        d = np.reshape(data, (1600, 3)).tolist()

        data = np.zeros(100*16*3).tolist()
        for i,pixel in enumerate(d):
            position = (16 * (i % 100) + i/100)*3
            data[position + 0] = pixel[0]
            data[position + 1] = pixel[1]
            data[position + 2] = pixel[2]

        data = np.reshape(data, (100, 48)).tolist()
        #print data
        data_flat = []
        for row in data:
            for val in row:
                data_flat.append(val)
        self.image_packets = data_to_packets(data_flat, "IMG", 16 * 3)

        #print "Submitting first packet %s" % str(self.image_packets[0])
        self.resetAcketPackets()
        self.submit_packet_for_transmit(self.image_packets[0])
        for packet in self.image_packets[1:-1]:
            self.tx_image_packet_queue.put(packet)

    def submit_packet_for_transmit(self, packet):

        packet.append('\n')
        #print("Sending another packet: %s" % str(packet))
        self.tx_packet_queue.put(packet)
    
    def submit_for_transmit(self, data, data_type):
        #if(self.serialState == self.connected):
            # 16 pixels x 3 bytes (RGB) per pixel
        try:
            if data_type == "IMG":
                print "You used the wrong function!"
                #data = [d for d in data]

            else:
                self.packets = data_to_packets(data, data_type, len(data))
               # print "BT Transmit packets %s" % self.packets
            for packet in self.packets:
                #print "adding packet:", packet
               # time.sleep(0.1)
                
                #self.msg("Transmitting packet")
                #print "Transmitting packet"

                self.tx_packet_queue.put(packet)

                
        except:
            traceback.print_exc()

