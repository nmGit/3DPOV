from PyQt4 import QtCore, QtGui
from PyQt4.QtCore import QObject, pyqtSignal
import sys

from rasterViewer import rasterViewer
from POVMappedImageWidget import POVMappedImageWidget
from POVCommandLine import POVCommandLine
import mapping
from pyqtgraph.dockarea import *
import numpy as np
import os
import math
from PIL import Image
import cv2

from POVDataLink import POVDataLink

class main(QtGui.QMainWindow):

    szx = 32
    szy = 32
    radio_ack_sig = pyqtSignal(int)
    radio_rtr_sig = pyqtSignal(int)
    def __init__(self):
        super(main, self).__init__()

        self.setWindowTitle("3D POV Tools")
        self.mainTabWidget = DockArea()

        self.bt_rx_line = []

        self.control_widget = QtGui.QFrame()
        self.control_layout = QtGui.QGridLayout()
        self.control_layout.setColumnStretch(2, 0)
        self.control_layout.setRowStretch(2, 0)
        self.control_widget.setLayout(self.control_layout)

        self.mtr_settings_gb = QtGui.QGroupBox("Motor Settings")
        self.mtr_settings_spd_layout = QtGui.QHBoxLayout()


        self.mtr_settings_spd_slider_label = QtGui.QLabel("Motor Speed: ")
        self.mtr_settings_spd_layout.addWidget(self.mtr_settings_spd_slider_label)

        self.mtr_settings_spd_slider = QtGui.QSlider(QtCore.Qt.Horizontal)
        self.mtr_settings_spd_slider.setMinimum(0)
        self.mtr_settings_spd_slider.setMaximum(100)
        self.mtr_settings_spd_slider.valueChanged.connect(self.mtr_spd_change_handler)
        self.mtr_settings_spd_layout.addWidget(self.mtr_settings_spd_slider)

        self.mtr_settings_gb.setLayout(self.mtr_settings_spd_layout)
        self.control_layout.addWidget(self.mtr_settings_gb, 2, 0)

        self.bt_settings_gb = QtGui.QGroupBox("Radio Board Settings")
        self.bt_settings_layout = QtGui.QVBoxLayout()
        self.bt_settings_gb.setLayout(self.bt_settings_layout)

        # Create drop-down menus to select the bluetooth com ports
        # self.bt_settings_incoming_port_select = QtGui.QComboBox()
        # self.bt_settings_outgoing_port_select = QtGui.QComboBox()
        #
        # self.bt_settings_incoming_port_select.currentIndexChanged.connect(self.bt_incoming_port_change_handler)
        # self.bt_settings_outgoing_port_select.currentIndexChanged.connect(self.bt_outgoing_port_change_handler)
        #
        # self.bt_settings_incoming_port_select_layout = QtGui.QHBoxLayout()
        # self.bt_settings_outgoing_port_select_layout = QtGui.QHBoxLayout()
        #
        # self.bt_settings_incoming_port_select_layout.addWidget(QtGui.QLabel("Incoming port (From Radio board):"))
        # self.bt_settings_outgoing_port_select_layout.addWidget(QtGui.QLabel("Outgoing port (To Radio board):"))
        #
        # self.bt_settings_incoming_port_select_layout.addWidget(self.bt_settings_incoming_port_select)
        # self.bt_settings_outgoing_port_select_layout.addWidget(self.bt_settings_outgoing_port_select)
        #
        # self.bt_settings_port_select_refresh = QtGui.QPushButton("Refresh")
        # self.bt_settings_port_select_refresh.clicked.connect(self.bt_com_port_refresh)
        #
        # self.bt_settings_layout.addLayout(self.bt_settings_incoming_port_select_layout)
        # self.bt_settings_layout.addLayout(self.bt_settings_outgoing_port_select_layout)
        # self.bt_settings_layout.addWidget(self.bt_settings_port_select_refresh)
        # self.bt_settings_layout.addStretch(0)

        self.control_layout.addWidget(self.bt_settings_gb, 1, 0)

        self.control_layout_dock = Dock("3D POV Control")
        self.control_layout_dock.addWidget(self.control_widget)
        self.mainTabWidget.addDock(self.control_layout_dock, "bottom")

        self.mapped_image_dock = Dock("Live View")
        self.mapped_image_widget = POVMappedImageWidget()
        self.mapped_image_widget.new_image_sig.connect(self.new_image_handler)
        self.mapped_image_dock.addWidget(self.mapped_image_widget)
        self.mainTabWidget.addDock(self.mapped_image_dock, "top")

        self.cmd_line = POVCommandLine()
        self.cmd_line_dock = Dock("Main Board")
        self.cmd_line_dock.addWidget(self.cmd_line)
        self.mainTabWidget.addDock(self.cmd_line_dock, "right")

        self.bt_cmd_line = POVCommandLine()
        self.bt_cmd_line_dock = Dock("Radio Board")
        self.bt_cmd_line_dock.addWidget(self.bt_cmd_line)
        self.mainTabWidget.addDock(self.bt_cmd_line_dock, "right")

        self.setCentralWidget(self.mainTabWidget)

        self.datalink = POVDataLink()
        self.datalink.new_mn_driver_state.connect(self.new_main_state)
        self.datalink.new_mn_rx.connect(self.new_main_rx)
        self.datalink.new_bt_driver_state.connect(self.new_bt_state)
        self.datalink.new_bt_rx.connect(self.new_bt_rx)
        #self.radio_ack_sig.connect(self.datalink.radio_driver.continue_image_transmission)
        self.radio_ack_sig.connect(self.datalink.radio_driver.packetAcked)
        self.datalink.start()

        pass

    def bt_com_port_refresh(self):
        ports = self.datalink.get_available_ports()

        self.bt_settings_incoming_port_select.clear()
        self.bt_settings_outgoing_port_select.clear()

        self.bt_settings_incoming_port_select.addItems([port[0] for port in ports])
        self.bt_settings_outgoing_port_select.addItems([port[0] for port in ports])

    # def bt_outgoing_port_change_handler(self, index):
    #
    #     port = self.bt_settings_outgoing_port_select.itemText(index)
    #     print port
    #     #self.datalink.radio_driver.set_tx_port(port)
    #
    # def bt_incoming_port_change_handler(self, index):
    #
    #     port = self.bt_settings_incoming_port_select.itemText(index)
    #     print port
    #     #self.datalink.radio_driver.set_rx_port(port)

    def mtr_spd_change_handler(self, value):
        self.cmd_line.addLine("Setting Motor speed: %d" % value, (100, 100, 255))
        self.datalink.mn_set_motor_speed(value)

    def new_main_state(self):
        state = self.datalink.mn_driver_get_state()
        self.cmd_line.state_change(state)

        if ("Disconnected" in state or "Port error" in state):
            self.cmd_line.addLine(state, (255, 100, 100))
        elif ("Connected" in state):
            self.cmd_line.addLine(state, (100, 255, 100))
        elif ("Requesting" not in state):
            self.cmd_line.addLine(state, (255, 255, 100))

    def new_main_rx(self):
        while(True):
            char = self.datalink.mn_driver_next_byte()
            if(char == None):
                break

            self.cmd_line.addChar(char)
            if(char == '\0'):
                break

    def new_bt_state(self):
        state = self.datalink.bt_driver_get_state()
        self.bt_cmd_line.state_change(state)
        if("Disconnected" in state or "Port error" in state):
            self.bt_cmd_line.addLine(state, (255,100,100))
        elif("Connected" in state):
            self.bt_cmd_line.addLine(state, (100,255,100))
        elif("Requesting" not in state):
            self.bt_cmd_line.addLine(state, (255, 255, 100))

    def new_bt_rx(self):
        
       # print "Received something from bluetooth:"
        while(not self.datalink.bt_driver_rx_queue_empty()):
            char = ord(self.datalink.bt_driver_next_byte())
            #print "BT Rx char", char
            # if(char == None):
            #     break
            #print "BT received:%s" % (char)
            self.bt_cmd_line.addChar(char)
            self.bt_rx_line.append(char)
            #print "Bt RX line: ", self.bt_rx_line
            self.bt_rx_line_str = [chr(c) for c in self.bt_rx_line]
            if("ACK" in ''.join(self.bt_rx_line_str) and "ACK" in ''.join(self.bt_rx_line_str[-5:-2])):
                num = self.bt_rx_line[-1]
                self.radio_ack_sig.emit(num)
                self.bt_cmd_line.addLine("Ack Received: %d"%num, (180, 230, 255))
                self.bt_rx_line = []
            # if("PCK" in ''.join(self.bt_rx_line)):
            #     self.radio_rtr_sig.emit(''.join(self.bt_rx_line[4]))
            #     self.bt_rx_line = []
            if(str(char) == '\n'):

                print "Line Received: %s" % ''.join(self.bt_rx_line_str)


    def new_bt_tx(self, string):
        for chr in string:
            self.bt_cmd_line.addChar(chr)

    def flatten_img(self, img):
        flat = []
        for x in img:
            for val in x:
                flat.append(val)
        return flat


    def new_image_handler(self):
        data = self.mapped_image_widget.get_image_data()
        self.download_to_radio_board(data)

    def download_to_radio_board(self, image):

        self.datalink.bt_transmit_image(image)
        self.bt_cmd_line.addLine("Sending image...", (100, 180, 255))

if __name__ == '__main__':
    print "starting..."
    app = QtGui.QApplication(sys.argv)
    main = main()
    main.show()
    sys.exit(app.exec_())