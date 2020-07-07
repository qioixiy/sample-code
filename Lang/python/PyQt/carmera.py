# coding=utf-8
import sys

from PyQt4 import QtGui
import cv
from PyQt4 import QtCore


class CameraDevice(QtCore.QObject):
    _DEFAULT_FPS = 30

    newFrame = QtCore.pyqtSignal(cv.iplimage)

    def __init__(self, cameraId=0, mirrored=False, parent=None,
                 size=(640, 480)):
        super(CameraDevice, self).__init__(parent)

        self.mirrored = mirrored

        self._cameraDevice = cv.CaptureFromCAM(cameraId)
        cv.SetCaptureProperty(self._cameraDevice, cv.CV_CAP_PROP_FRAME_WIDTH,
                              size[0])
        cv.SetCaptureProperty(self._cameraDevice, cv.CV_CAP_PROP_FRAME_HEIGHT,
                              size[1])

        self._timer = QtCore.QTimer(self)
        self._timer.timeout.connect(self._queryFrame)
        self._timer.setInterval(1000 / self.fps)

        self.paused = False

    @QtCore.pyqtSlot()
    def _queryFrame(self):
        frame = cv.QueryFrame(self._cameraDevice)
        if self.mirrored:
            mirroredFrame = cv.CreateImage(cv.GetSize(frame), frame.depth,
                                           frame.nChannels)
            cv.Flip(frame, mirroredFrame, 1)
            frame = mirroredFrame
            self.newFrame.emit(frame)

    @property
    def paused(self):
        return not self._timer.isActive()

    @paused.setter
    def paused(self, p):
        if p:
            self._timer.stop()
        else:
            self._timer.start()

    @property
    def frameSize(self):
        w = cv.GetCaptureProperty(self._cameraDevice,
                                  cv.CV_CAP_PROP_FRAME_WIDTH)
        h = cv.GetCaptureProperty(self._cameraDevice,
                                  cv.CV_CAP_PROP_FRAME_HEIGHT)
        return int(w), int(h)

    @property
    def fps(self):
        fps = int(cv.GetCaptureProperty(self._cameraDevice, cv.CV_CAP_PROP_FPS))
        if not fps > 0:
            fps = self._DEFAULT_FPS
        return fps


class CameraWidget(QtGui.QWidget):
    newFrame = QtCore.pyqtSignal(cv.iplimage)

    def __init__(self, cameraDevice, parent=None):
        super(CameraWidget, self).__init__(parent)

        self._frame = None

        self._cameraDevice = cameraDevice
        self._cameraDevice.newFrame.connect(self._on_new_frame)

        w, h = self._cameraDevice.frameSize
        self.setMinimumSize(w, h)
        self.setMaximumSize(w, h)

    @QtCore.pyqtSlot(cv.iplimage)
    def _on_new_frame(self, frame):
        self._frame = cv.CloneImage(frame)
        self.newFrame.emit(self._frame)
        self.update()

    def changeEvent(self, e):
        if e.type() == QtCore.QEvent.EnabledChange:
            if self.isEnabled():
                self._cameraDevice.newFrame.connect(self._on_new_frame)
            else:
                self._cameraDevice.newFrame.disconnect(self._on_new_frame)

    def paintEvent(self, e):
        if self._frame is None:
            return
        painter = QtGui.QPainter(self)
        painter.drawImage(QtCore.QPoint(0, 0), OpenCVQImage(self._frame))

    def get_curr_frame(self):
        return QtGui.QPixmap.fromImage(OpenCVQImage(self._frame))


class OpenCVQImage(QtGui.QImage):
    def __init__(self, opencv_bgr_img):
        depth, n_channels = opencv_bgr_img.depth, opencv_bgr_img.nChannels
        if depth != cv.IPL_DEPTH_8U or n_channels != 3:
            raise ValueError("the input image must be 8-bit, 3-channel")
        w, h = cv.GetSize(opencv_bgr_img)
        opencv_rgb_img = cv.CreateImage((w, h), depth, n_channels)
        # it's assumed the image is in BGR format
        cv.CvtColor(opencv_bgr_img, opencv_rgb_img, cv.CV_BGR2RGB)
        self._imgData = opencv_rgb_img.tostring()
        super(OpenCVQImage, self).__init__(self._imgData, w, h,
                                           QtGui.QImage.Format_RGB888)


class Example(QtGui.QWidget):
    def __init__(self):
        super(Example, self).__init__()
        self.initUI()

    def initUI(self):
        cameraDevice = CameraDevice(cameraId=1, mirrored=True, size=(640, 480))

        cameraWidget1 = CameraWidget(cameraDevice)
        cameraWidget2 = CameraWidget(cameraDevice)
        cameraWidget2.newFrame.connect(self.onNewFrame)

        hbox = QtGui.QHBoxLayout()
        hbox.addWidget(cameraWidget1)
        hbox.addWidget(cameraWidget2)

        self.setLayout(hbox)

        self.setWindowTitle('Buttons')
        self.show()

    @QtCore.pyqtSlot(cv.iplimage)
    def onNewFrame(self, frame):
        cv.CvtColor(frame, frame, cv.CV_RGB2BGR)
        msg = "processed frame"
        font = cv.InitFont(cv.CV_FONT_HERSHEY_DUPLEX, 1.0, 1.0)
        tsize, baseline = cv.GetTextSize(msg, font)
        w, h = cv.GetSize(frame)
        tpt = (w - tsize[0]) / 2, (h - tsize[1]) / 2
        cv.PutText(frame, msg, tpt, font, cv.RGB(255, 255, 0))


def main():
    app = QtGui.QApplication(sys.argv)
    ex = Example()

    sys.exit(app.exec_())


if __name__ == "__main__":
    main()
