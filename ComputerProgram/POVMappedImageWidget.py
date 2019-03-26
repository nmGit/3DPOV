from PyQt4 import QtCore, QtGui
import numpy as np
import sys

from rasterViewer import rasterViewer
import mapping

import numpy as np
import os
import math
from PIL import Image
import cv2

class POVMappedImageWidget(QtGui.QFrame):
    szx = 32
    szy = 32
    def __init__(self):
        super(POVMappedImageWidget, self).__init__()
        self.mainLayout = QtGui.QGridLayout()


        self.setAcceptDrops(True)

        self.raster_view = rasterViewer(self.szx, self.szy)
        self.raster_view.makeSquare(True)

        self.setLayout(self.mainLayout)

        self.mainLayout.addWidget(self.raster_view, 0, 0, 1, 1)
        self.raster_view.show()

        self.raster_mapped = rasterViewer(5, 5)
        self.mainLayout.addWidget(self.raster_mapped, 1, 0, 1, 2)

        self.raster_mapped_scaled = rasterViewer(5, 5)
        self.mainLayout.addWidget(self.raster_mapped_scaled, 2, 0, 1, 2)
        pass

    def dragEnterEvent(self, event):
        print event
        if event.mimeData().hasUrls:
            event.setDropAction(QtCore.Qt.CopyAction)
            event.accept()
            links = []
            for url in event.mimeData().urls():
                links.append(str(url.toLocalFile()))
            print links
        else:
            event.ignore()
        # if e.mimeData().hasText():
        #     e.accept()
        # else:
        #     e.ignore()
    def flatten_img(self, img):
        flat = []
        for x in img:
            for val in x:
                flat.append(val)
        return flat

    def dropEvent(self, event):
        print "Dropped"
        if event.mimeData().hasUrls:
            event.setDropAction(QtCore.Qt.CopyAction)
            # For each path, process the dropped image
            for url in event.mimeData().urls():
                path_to_image = url.toLocalFile()
                self.process_image(path_to_image)


#            print self.image_pix_flat

        else:
            event.ignore()

    def process_image(self, path_to_image):
        # Read the image using OpenCV library
        self.image = cv2.imread(str(path_to_image))
        # Next, we want to reshape the image. If it is large, then it will take a long time to
        # do the initial processing. Additionally it would be a waste because we need to scale the image way down
        # in order to display it anyway.
        # Resize it to 120 x 120 pixels
        if self.image.shape[0] > 120:
            self.image = cv2.resize(self.image, (120, 120))
        # Store the resolution of hte image
        self.szx = self.image.shape[0]
        self.szy = self.image.shape[1]
        # The image comes in as a multi-dimensional array. We want a 1-D array for our processing
        # so we must "flatten" the image.
        self.image_pix_float = self.image.flatten()
        # The image comes in as float, but we need integers
        self.image_pix_flat_raw = [int(i) for i in self.image_pix_float]
        self.image_pix_rgb = []
        # In order to map the image, it is easiest if we have a 2-D array in the following format:
        #           img = [[pix1_r, pix1_g, pix1_b], [pix2_r, pix2_g, pix2_b], ... [pixn_r, pixn_g, pixn_b]]
        # Where n = szx * szy
        # The following loop will take the flat image and convert it to this format
        for i in range(0, len(self.image_pix_flat_raw), 3):
            print("%f percent"%((i / float(len(self.image_pix_flat_raw))*100)))
            self.image_pix_rgb.append((self.image_pix_flat_raw[i + 2],
                                           self.image_pix_flat_raw[i + 1],
                                           self.image_pix_flat_raw[i + 0]))
        # At this point, the image is just a 2-D python list. No built-in flatten operation exists to flatten lists
        # so we must call our own flatten operation. We will need a flat array of rgb values in order for my raster
        # viewer to display the image.
        self.image_pix_rgb_flat = self.flatten_img(self.image_pix_rgb)
        # Tell the raster viewer what the resolution should be
        self.raster_view.setResolution(self.szx, self.szy)
        # Tell the raster viewer what data it should be displaying
        self.raster_view.setImage(self.image_pix_rgb_flat)
        # This takes our 2-D array from above and maps it to the "donut" shape
        self.map_result = mapping.map_to_donut(self.image_pix_rgb, self.szx, self.szy, 0.1, 1)
        # Take the map result and flatten it using our flatten operation
        self.map_result_flat =self.flatten_img(self.map_result[2])
        # We now start the process of scaling the mapped image so that it can be displayed by our POV
        # the pov only has a certain number of leds, so we must scale the image to match that.
        # Libraries used to do this expect certain data types. We need to convert our mapped image to a flat
        # array with each value scaled so that it is between 0 and 1
        self.map_result_float = [float(i / 255.0) for i in self.map_result_flat]
        # The library also expects a 3-D array in the form of rgb tuples, inside rows which are inside columns.
        # Use numpy reshape command to reshape the list (matrix as far as numpy is concerned)
        self.map_result_float_3D = np.reshape(self.map_result_float, [self.map_result[1],self.map_result[0],3])
        # We then convert the result to a numpy array and pass it to the image resize method, giving it a size
        # of rows (leds) and columns (angular resolution) to scale it to
        self.map_result_image = cv2.resize(np.array(self.map_result_float_3D), (100, 16))
        self.scale_result = self.map_result_image
        # Flatten our image. It is also in the format of floats between 0 and 1 instead of between 0 and 255.
        self.scale_result_flat_float = self.scale_result.flatten()
        # Scale each element in the array to between 0 and 255
        self.scale_result_flat = [int(i * 255) for i in self.scale_result_flat_float]
        # Display our mapped image
        self.raster_mapped_scaled.setResolution(self.map_result_image.shape[1],self.map_result_image.shape[0] )
        self.raster_mapped_scaled.setImage(self.scale_result_flat)
        # Display our mapped image
        self.image_pix_mapped_flat = self.flatten_img(self.map_result[2])
        self.raster_mapped.setResolution(self.map_result[0], self.map_result[1])
        self.raster_mapped.setImage([int(x*255) for x in self.map_result_float])
