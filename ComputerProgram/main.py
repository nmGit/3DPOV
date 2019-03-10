from PyQt4 import QtCore, QtGui

import sys

from rasterViewer import rasterViewer

import numpy as np
import os

from PIL import Image
class main(QtGui.QMainWindow):

    szx = 64
    szy = 64
    def __init__(self):
        super(main, self).__init__()
        self.mainFrame = QtGui.QFrame()
        self.mainLayout = QtGui.QGridLayout()

        self.setAcceptDrops(True)

        self.raster_view = rasterViewer(self.szx, self.szy)

        self.setCentralWidget(self.mainFrame)
        self.mainFrame.show()

        self.mainFrame.setLayout(self.mainLayout)

        self.mainLayout.addWidget(self.raster_view, 1, 1)
        self.raster_view.show()
        #print "creating random image"
        random_img = np.random.rand(self.szx * self.szy * 4).tolist()
        #print "Image created", random_img
        random_img = [int(d*float(255)) for d in random_img]
        #print "converting and showing", random_img
        self.raster_view.setImage(random_img)
        #print "shown"
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

    def dropEvent(self, event):
        print "Dropped"
        if event.mimeData().hasUrls:
            event.setDropAction(QtCore.Qt.CopyAction)
            event.accept()

            links = []
            for url in event.mimeData().urls():
                path_to_image = url.toLocalFile()

            self.image = Image.open(str(path_to_image),'r')
            self.image_pix = list(self.image.getdata())
            self.image_pix = [x[0:3] for x in self.image_pix]
            self.image_pix_flat = []
            for x in self.image_pix:
                for val in x:
                    self.image_pix_flat.append(val)

            self.raster_view.setImage(self.image_pix_flat)
            print self.image_pix_flat

        else:
            event.ignore()

if __name__ == '__main__':
    print "starting..."
    app = QtGui.QApplication(sys.argv)
    main = main()
    main.show()
    sys.exit(app.exec_())