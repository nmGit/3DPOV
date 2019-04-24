from PyQt4 import QtCore, QtGui
import numpy as np
import sys

class rasterViewer(QtGui.QWidget):
    datasource = 0
    szx = 1
    szy = 1
    x=0
    def __init__(self, szx, szy):
        super(rasterViewer, self).__init__()

        self.imageLabel = QtGui.QLabel()
        self.imageLabel.setBackgroundRole(QtGui.QPalette.Base)
        self.imageLabel.setScaledContents(True)
        self.layout = QtGui.QHBoxLayout()
        self.setWindowTitle("Image Viewer")
        self.resize(szx, szy)
        self.imageLabel.show()
        self.layout.addWidget(self.imageLabel)
        self.setLayout(self.layout)
        self.szx = szx
        self.szy = szy
        self.aspect_square = False
        self.setSizePolicy(QtGui.QSizePolicy.Ignored, QtGui.QSizePolicy.Ignored)
    def setResolution(self, x, y):
        self.szx = x
        self.szy = y
    def makeSquare(self, lock):

        self.aspect_square = lock

    def resizeEvent(self, QResizeEvent):
        if(self.aspect_square):
            self.setFixedWidth(self.height())
    def setImage(self, pilimg):

        #print "Pilimg:",pilimg
        img = np.array([])

        img = img.astype(np.uint32)
        print("Converting to raster")
        for i in range(len(pilimg)/3):
            #print("%f percent" % ((i/float((len(pilimg)/3)))*100))
            pix = 0xFF000000
            pix |= (pilimg[i*3+0] << 16)
            pix |= (pilimg[i*3+1] << 8)
            pix |= (pilimg[i*3+2] << 0)
            #print hex(pix)
            img = np.append(img, np.array(pix, dtype=np.uint32))
        image = QtGui.QImage(img, self.szx, self.szy, QtGui.QImage.Format_RGB32)
        image.setColorCount(3)
        if image.isNull():
            QtGui.QMessageBox.information(self, "Image Viewer","Cannot load image")
            return

        self.imageLabel.setPixmap(QtGui.QPixmap.fromImage(image).scaledToHeight(200, QtCore.Qt.FastTransformation))
   #     self.imageLabel.adjustSize()
#
# if __name__ == '__main__':
#     print "starting..."
#     app = QtGui.QApplication(sys.argv)
#     r = rasterViewer(2, 2)
#     r.show()
#     r.setImage([
#         0xFF0000, 0x00FF00,
#         0x0000FF, 0xFFFFFF
#
#     ])
#     sys.exit(app.exec_())
#
