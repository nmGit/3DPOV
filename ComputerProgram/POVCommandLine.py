from PyQt4 import QtCore, QtGui
from PyQt4.QtCore import QObject, pyqtSignal

import serial
import serial.tools.list_ports

class POVCommandLine(QtGui.QFrame):
    def __init__(self):
        super(POVCommandLine, self).__init__()
        self.mainLayout = QtGui.QVBoxLayout()
        self.setLayout(self.mainLayout)

        self.cmd_buffer = ""
        self.info_label = QtGui.QLabel()

        self.mainLayout.addWidget(self.info_label)

        self.helper = POVCommandLineHelper()
        self.helper.new_message_sig.connect(self.com_state_change)

        self.text_window = QtGui.QTextEdit()
        self.mainLayout.addWidget(self.text_window)

    def com_state_change(self, msg):
        self.info_label.setText(msg)

    def cmd_action(self, data):
        self.cmd_buffer.append(data)
        self.text_window.setText(self.cmd_buffer)
class POVCommandLineHelper(QtCore.QThread):

    new_message_sig = pyqtSignal(str)
    new_rx_sig = pyqtSignal(str)

    def __init__(self):
        super(POVCommandLineHelper, self).__init__()
        self.connected = 0
        self.disconnected = 1
        self.searching = 2
        self.serialState = self.disconnected
        self.com_port = None
        self.start()

    def msg(self, msg):
        self.new_message_sig.emit(msg)

    def receive(self, rx_data):
        self.new_rx_sig.emit(rx_data)

    def search(self):
        ports = serial.tools.list_ports.comports()
        for port in ports:
            ser = serial.Serial(port[0], 115200, timeout=1)
            ser.write("*IDN\r\n")
            line = ser.readline()
            if(line == "3DPOV\r\n"):
                ser.close()
                return port
            ser.close()

        return None

    def run(self):
        while(1):
            if(self.serialState == self.disconnected):

                self.serialState = self.searching
                self.msg("Disconnected :(")

            elif (self.serialState == self.searching):

                self.msg("Searching...")
                self.com_port = self.search()
                search_attempt_number = 1

                while(self.com_port == None):

                    self.msg("Searching... attempt %d" % (search_attempt_number))
                    self.com_port = self.search()
                    search_attempt_number += 1

                    if(self.com_port == None):
                        self.sleep(1)

                self.serialState = self.connected

            elif(self.serialState == self.connected):
                try:
                    self.msg("Opening port...")
                    ser = serial.Serial(self.com_port, 115200, timeout = 1)
                    self.msg("Connected!")

                    if(ser.inWaiting()):
                        self.receive(ser.read())
                except:
                    self.msg("Port not opened :(")
                    self.serialState = self.disconnected