from PyQt4 import QtCore, QtGui
from PyQt4.QtCore import QObject, pyqtSignal

import serial
import serial.tools.list_ports

class POVCommandLine(QtGui.QFrame):
    def __init__(self):
        super(POVCommandLine, self).__init__()
        self.mainLayout = QtGui.QVBoxLayout()
        self.buttonLayout = QtGui.QHBoxLayout()
        self.setLayout(self.mainLayout)

        self.cmd_buffer = ""
        self.info_label = QtGui.QLabel()

        self.mainLayout.addWidget(self.info_label)

        self.helper = POVCommandLineHelper()
        self.helper.new_message_sig.connect(self.com_state_change)
        self.helper.new_rx_sig.connect(self.cmd_action)

        self.text_window = QtGui.QTextEdit()
        self.text_window.setReadOnly(True)
        self.text_window.setFont(QtGui.QFont("Lucida Console"))
        self.mainLayout.addWidget(self.text_window)

        self.mainLayout.addLayout(self.buttonLayout)

        self.clear_button = QtGui.QPushButton("Clear")
        self.clear_button.clicked.connect(self.clear_terminal)

        self.pause_button = QtGui.QPushButton("Pause Caputure")
        self.pause_button.clicked.connect(self.pause_button_handler)

        self.capture_paused = False
        self.buttonLayout.addStretch(1)
        self.buttonLayout.addWidget(self.pause_button)

        self.bufferSize = 1024

    def pause_button_handler(self):
        if self.capture_paused:
            self.capture_paused = False
            self.pause_button.setText("Pause Capture")
        else:
            self.capture_paused = True
            self.pause_button.setText("Start Capture")

    def com_state_change(self, msg):
        self.info_label.setText(msg)

    def cmd_action(self, data):
        if self.capture_paused:
            return

        self.cmd_buffer += data
        if(len(self.cmd_buffer) > self.bufferSize):
            self.cmd_buffer[-1024:-1]
        # scroll to bottom
        self.text_window.setText(self.cmd_buffer)
        self.text_window.verticalScrollBar().setValue(self.text_window.verticalScrollBar().maximum())


class POVCommandLineHelper(QtCore.QThread):

    new_message_sig = pyqtSignal(str)
    new_rx_sig = pyqtSignal(str)

    def __init__(self):
        super(POVCommandLineHelper, self).__init__()
        self.connected = 0
        self.disconnected = 1
        self.searching = 2
        self.establishing_connection = 3

        self.serialState = self.disconnected
        self.com_port = None
        self.start()

    def msg(self, msg):
        print msg
        self.new_message_sig.emit(msg)

    def receive(self, rx_data):
       # print "Received", rx_data
        self.new_rx_sig.emit(rx_data)

    def search(self):
        ports = serial.tools.list_ports.comports()
        for port in ports:
            try:
                ser = serial.Serial(port[0], 115200, timeout=1)
            except:
                continue
            ser.write("*IDN?\r")
            ser.flushInput()

            line = ser.readline()
            print "Trying:", port, "\tRecieved:", line

            if(line == "3DPOV\r\n"):
                ser.close()
                return port[0]
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


                    self.com_port = self.search()
                    self.msg("Searching... attempt %d" % (search_attempt_number))
                    search_attempt_number += 1

                    if(self.com_port == None):
                        self.msleep(10)

                print "Found!", self.com_port
                self.serialState = self.establishing_connection

            elif(self.serialState == self.establishing_connection):
                try:
                    self.msg("Opening port...")
                    ser = serial.Serial(self.com_port, 115200, timeout = 1)
                    self.msg("Connected!")
                    self.serialState = self.connected
                except:
                    self.msg("Port not opened :(")
                    self.serialState = self.disconnected

            elif(self.serialState == self.connected):
                try:
                    while(1):
                        if(ser.inWaiting()):
                            self.receive(ser.read())

                except:
                    self.msg("Port error")
                    self.serialState = self.disconnected