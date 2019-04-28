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
    radio_ack_sig = pyqtSignal(str)
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
        self.radio_ack_sig.connect(self.datalink.radio_driver.continue_image_transmission)
        
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
        while(True):
            char = self.datalink.bt_driver_next_byte()
            if(char == '\0'):
                break
            #print "BT received:%s or %x" % (char[0], ord(str(char)))
            self.bt_cmd_line.addChar(char)
            self.bt_rx_line.append(str(char))
            
            if("END" in ''.join(self.bt_rx_line)):
                self.radio_ack_sig.emit(''.join(self.bt_rx_line))
                #self.bt_cmd_line.addLine("Received ACK", (150, 200, 255) )
            if(str(char) == '\n'):
                self.bt_rx_line = []
                print "Line Received: %s" % ''.join(self.bt_rx_line)
            if(char == '\0'):
                break

    def new_bt_tx(self, string):
        for chr in string:
            self.bt_cmd_line.addChar(chr)

    # def dragEnterEvent(self, event):
    #     print event
    #     if event.mimeData().hasUrls:
    #         event.setDropAction(QtCore.Qt.CopyAction)
    #         event.accept()
    #         links = []
    #         for url in event.mimeData().urls():
    #             links.append(str(url.toLocalFile()))
    #         print links
    #     else:
    #         event.ignore()
    #     # if e.mimeData().hasText():
    #     #     e.accept()
    #     # else:
    #     #     e.ignore()
    def flatten_img(self, img):
        flat = []
        for x in img:
            for val in x:
                flat.append(val)
        return flat

#     def dropEvent(self, event):
#         print "Dropped"
#         if event.mimeData().hasUrls:
#             event.setDropAction(QtCore.Qt.CopyAction)
#             # For each path, process the dropped image
#             for url in event.mimeData().urls():
#                 path_to_image = url.toLocalFile()
#                 image = self.process_image(path_to_image)
#                 self.download_to_radio_board(image)
#
# #            print self.image_pix_flat
#
#         else:
#             print "Ignoring event!!"
#             event.ignore()
    def new_image_handler(self):
        data = self.mapped_image_widget.get_image_data()
        # self.data_shower = QtGui.QTextEdit()
        # cpackets = str(data)
        # self.data_shower.setText(cpackets)
        # self.data_shower.show()
        self.download_to_radio_board(data)

    def download_to_radio_board(self, image):
        # Now we have a bunch of packets that need to be sent
        # d = np.reshape(image, (1600, 3)).tolist()
        #
        # data = np.zeros(100*16*3).tolist()
        # for i,pixel in enumerate(d):
        #     position = (16 * (i % 100) + i/100)*3
        #     data[position + 0] = pixel[0]
        #     data[position + 1] = pixel[1]
        #     data[position + 2] = pixel[2]

        # self.datalink.bt_transmit_image(image)
        # packets = self.datalink.radio_driver.get_last_image_packets()
        # self.packet_shower = QtGui.QTextEdit()
        # cpackets = str(packets).replace("[", "{").replace("]", "}").replace("},", "},\n")
        # self.packet_shower.setText(cpackets)
        # self.packet_shower.show()
        #print "image packets:", packets
        self.datalink.bt_transmit_image(image)
        self.bt_cmd_line.addLine("Sending image...", (100, 180, 255))
        #packets = self.datalink.radio_driver.get_last_image_packets()

        #self.data_shower = QtGui.QTextEdit()
        #cpackets = str(packets).replace("],", "},\n").replace("[", "{")
        #self.data_shower.setText(str(cpackets))
        #self.data_shower.show()

        #for num,packet in enumerate(packets):
        #    print "Packet number: %d: %s" %(num, str(packet))
        #    self.bt_cmd_line.addLine("Image packet number %d: %s" %(num, str(packet)), (100, 255, 255))


    # def process_image(self, path_to_image):
    #     # Read the image using OpenCV library
    #     self.image = cv2.imread(str(path_to_image))
    #     # Next, we want to reshape the image. If it is large, then it will take a long time to
    #     # do the initial processing. Additionally it would be a waste because we need to scale the image way down
    #     # in order to display it anyway.
    #     # Resize it to 120 x 120 pixels
    #     if self.image.shape[0] > 120:
    #         self.image = cv2.resize(self.image, (120, 120))
    #     # Store the resolution of hte image
    #     self.szx = self.image.shape[0]
    #     self.szy = self.image.shape[1]
    #     # The image comes in as a multi-dimensional array. We want a 1-D array for our processing
    #     # so we must "flatten" the image.
    #     self.image_pix_float = self.image.flatten()
    #     # The image comes in as float, but we need integers
    #     self.image_pix_flat_raw = [int(i) for i in self.image_pix_float]
    #     self.image_pix_rgb = []
    #     # In order to map the image, it is easiest if we have a 2-D array in the following format:
    #     #           img = [[pix1_r, pix1_g, pix1_b], [pix2_r, pix2_g, pix2_b], ... [pixn_r, pixn_g, pixn_b]]
    #     # Where n = szx * szy
    #     # The following loop will take the flat image and convert it to this format
    #     for i in range(0, len(self.image_pix_flat_raw), 3):
    #         #print("%f percent"%((i / float(len(self.image_pix_flat_raw))*100)))
    #         self.image_pix_rgb.append((self.image_pix_flat_raw[i + 2],
    #                                        self.image_pix_flat_raw[i + 1],
    #                                        self.image_pix_flat_raw[i + 0]))
    #     # At this point, the image is just a 2-D python list. No built-in flatten operation exists to flatten lists
    #     # so we must call our own flatten operation. We will need a flat array of rgb values in order for my raster
    #     # viewer to display the image.
    #     self.image_pix_rgb_flat = self.flatten_img(self.image_pix_rgb)
    #     # Tell the raster viewer what the resolution should be
    #     self.raster_view.setResolution(self.szx, self.szy)
    #     # Tell the raster viewer what data it should be displaying
    #     self.raster_view.setImage(self.image_pix_rgb_flat)
    #     # This takes our 2-D array from above and maps it to the "donut" shape
    #     self.map_result = mapping.map_to_donut(self.image_pix_rgb, self.szx, self.szy, 0.1, 1)
    #     # Take the map result and flatten it using our flatten operation
    #     self.map_result_flat =self.flatten_img(self.map_result[2])
    #     # We now start the process of scaling the mapped image so that it can be displayed by our POV
    #     # the pov only has a certain number of leds, so we must scale the image to match that.
    #     # Libraries used to do this expect certain data types. We need to convert our mapped image to a flat
    #     # array with each value scaled so that it is between 0 and 1
    #     self.map_result_float = [float(i / 255.0) for i in self.map_result_flat]
    #     # The library also expects a 3-D array in the form of rgb tuples, inside rows which are inside columns.
    #     # Use numpy reshape command to reshape the list (matrix as far as numpy is concerned)
    #     self.map_result_float_3D = np.reshape(self.map_result_float, [self.map_result[1],self.map_result[0],3])
    #     # We then convert the result to a numpy array and pass it to the image resize method, giving it a size
    #     # of rows (leds) and columns (angular resolution) to scale it to
    #     self.map_result_image = cv2.resize(np.array(self.map_result_float_3D), (100, 16))
    #     self.scale_result = self.map_result_image
    #     # Flatten our image. It is also in the format of floats between 0 and 1 instead of between 0 and 255.
    #     self.scale_result_flat_float = self.scale_result.flatten()
    #     # Scale each element in the array to between 0 and 255
    #     self.scale_result_flat = [int(i * 255) for i in self.scale_result_flat_float]
    #     # Display our mapped image
    #     self.raster_mapped_scaled.setResolution(self.map_result_image.shape[1],self.map_result_image.shape[0] )
    #     self.raster_mapped_scaled.setImage(self.scale_result_flat)
    #     # Display our mapped image
    #     self.image_pix_mapped_flat = self.flatten_img(self.map_result[2])
    #     self.raster_mapped.setResolution(self.map_result[0], self.map_result[1])
    #     self.raster_mapped.setImage([int(x*255) for x in self.map_result_float])
    #
    #     return self.scale_result_flat
if __name__ == '__main__':
    print "starting..."
    app = QtGui.QApplication(sys.argv)
    main = main()
    main.show()
    sys.exit(app.exec_())