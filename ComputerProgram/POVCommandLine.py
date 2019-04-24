from PyQt4 import QtCore, QtGui
from PyQt4.QtCore import QObject, pyqtSignal

import serial
import serial.tools.list_ports
from POVDataLink import POVDataLink

class POVCommandLine(QtGui.QFrame):
    def __init__(self):
        super(POVCommandLine, self).__init__()
        self.mainLayout = QtGui.QVBoxLayout()
        self.buttonLayout = QtGui.QHBoxLayout()
        self.inputLayout = QtGui.QHBoxLayout()
        self.setLayout(self.mainLayout)

        self.cmd_buffer = ""
        self.info_label = QtGui.QLabel()

        self.mainLayout.addWidget(self.info_label)


        self.text_window = QtGui.QListWidget()
        self.text_window.setFont(QtGui.QFont("Lucida Console"))
        self.mainLayout.addWidget(self.text_window)

        self.mainLayout.addLayout(self.inputLayout)
        self.command_input = QtGui.QLineEdit()
        self.send_button = QtGui.QPushButton("Send")
        self.send_button.clicked.connect(self.send_cmd)
        self.inputLayout.addWidget(self.command_input)
        self.inputLayout.addWidget(self.send_button)

        self.mainLayout.addLayout(self.buttonLayout)

        self.clear_button = QtGui.QPushButton("Clear")
        self.clear_button.clicked.connect(self.clear_terminal)

        self.pause_button = QtGui.QPushButton("Pause Caputure")
        self.pause_button.clicked.connect(self.pause_button_handler)

        self.capture_paused = False
        self.buttonLayout.addStretch(1)
        self.buttonLayout.addWidget(self.pause_button)

        self.last_item = None
        self.line = ''
        self.bufferSize = 1024

    def pause_button_handler(self):
        if self.capture_paused:
            self.capture_paused = False
            self.pause_button.setText("Pause Capture")
        else:
            self.capture_paused = True
            self.pause_button.setText("Start Capture")
    def clear_terminal(self):
        self.cmd_buffer = ""
        self.text_window.setText("")
    def state_change(self, state):
        self.info_label.setText(state)

    def send_cmd(self):
        pass

    def addLine(self, string, color = (255, 255, 255)):
        self.item = QtGui.QListWidgetItem()
        self.item.setBackgroundColor(QtGui.QColor(*color))

        self.text_window.addItem(self.item)
        self.text_window.setItemWidget(self.item, QtGui.QLabel(string))
        self.text_window.setFont(QtGui.QFont("Lucida Console"))

        self.text_window.verticalScrollBar().setValue(self.text_window.verticalScrollBar().maximum())
    def addChar(self, chr):

        if self.capture_paused:
            return

        if(chr == '\n' or self.last_item is None):
            self.last_item = QtGui.QListWidgetItem()

            self.text_window.setItemWidget(self.last_item, QtGui.QLabel(self.line))
            self.text_window.addItem(self.last_item)
            self.line =""

        elif(chr == '\r'):
            self.line = ""
            pass
        else:
            self.line += chr
            self.text_window.setItemWidget(self.last_item, QtGui.QLabel(self.line))

        self.text_window.setFont(QtGui.QFont("Lucida Console"))
        self.text_window.verticalScrollBar().setValue(self.text_window.verticalScrollBar().maximum())
