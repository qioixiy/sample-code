# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'httpWidget.ui'
#
# Created: Mon Jun 13 15:26:37 2011
#      by: PyQt4 UI code generator 4.8.4
#
# WARNING! All changes made in this file will be lost!

from PyQt4 import QtCore, QtGui

try:
    _fromUtf8 = QtCore.QString.fromUtf8
except AttributeError:
    _fromUtf8 = lambda s: s

class Ui_HttpWidget(object):
    def setupUi(self, HttpWidget):
        HttpWidget.setObjectName(_fromUtf8("HttpWidget"))
        HttpWidget.resize(636, 336)
        self.verticalLayout = QtGui.QVBoxLayout(HttpWidget)
        self.verticalLayout.setObjectName(_fromUtf8("verticalLayout"))
        self.horizontalLayout = QtGui.QHBoxLayout()
        self.horizontalLayout.setObjectName(_fromUtf8("horizontalLayout"))
        self.back = QtGui.QPushButton(HttpWidget)
        icon = QtGui.QIcon()
        icon.addPixmap(QtGui.QPixmap(_fromUtf8("back.png")), QtGui.QIcon.Normal, QtGui.QIcon.Off)
        self.back.setIcon(icon)
        self.back.setObjectName(_fromUtf8("back"))
        self.horizontalLayout.addWidget(self.back)
        self.next = QtGui.QPushButton(HttpWidget)
        self.next.setEnabled(True)
        self.next.setLayoutDirection(QtCore.Qt.RightToLeft)
        icon1 = QtGui.QIcon()
        icon1.addPixmap(QtGui.QPixmap(_fromUtf8("next.png")), QtGui.QIcon.Normal, QtGui.QIcon.Off)
        self.next.setIcon(icon1)
        self.next.setObjectName(_fromUtf8("next"))
        self.horizontalLayout.addWidget(self.next)
        self.stop = QtGui.QPushButton(HttpWidget)
        icon2 = QtGui.QIcon()
        icon2.addPixmap(QtGui.QPixmap(_fromUtf8("stop.png")), QtGui.QIcon.Normal, QtGui.QIcon.Off)
        self.stop.setIcon(icon2)
        self.stop.setObjectName(_fromUtf8("stop"))
        self.horizontalLayout.addWidget(self.stop)
        self.reload = QtGui.QPushButton(HttpWidget)
        icon3 = QtGui.QIcon()
        icon3.addPixmap(QtGui.QPixmap(_fromUtf8("reload.png")), QtGui.QIcon.Normal, QtGui.QIcon.Off)
        self.reload.setIcon(icon3)
        self.reload.setObjectName(_fromUtf8("reload"))
        self.horizontalLayout.addWidget(self.reload)
        self.url = QtGui.QLineEdit(HttpWidget)
        self.url.setObjectName(_fromUtf8("url"))
        self.horizontalLayout.addWidget(self.url)
        self.verticalLayout.addLayout(self.horizontalLayout)
        self.webView = QtWebKit.QWebView(HttpWidget)
        self.webView.setUrl(QtCore.QUrl(_fromUtf8("about:blank")))
        self.webView.setObjectName(_fromUtf8("webView"))
        self.verticalLayout.addWidget(self.webView)

        self.retranslateUi(HttpWidget)
        QtCore.QMetaObject.connectSlotsByName(HttpWidget)

    def retranslateUi(self, HttpWidget):
        HttpWidget.setWindowTitle(QtGui.QApplication.translate("HttpWidget", "Form", None, QtGui.QApplication.UnicodeUTF8))
        self.back.setToolTip(QtGui.QApplication.translate("HttpWidget", "Back", None, QtGui.QApplication.UnicodeUTF8))
        self.back.setText(QtGui.QApplication.translate("HttpWidget", "Back", None, QtGui.QApplication.UnicodeUTF8))
        self.next.setToolTip(QtGui.QApplication.translate("HttpWidget", "Next", None, QtGui.QApplication.UnicodeUTF8))
        self.next.setText(QtGui.QApplication.translate("HttpWidget", "    Next", None, QtGui.QApplication.UnicodeUTF8))
        self.stop.setToolTip(QtGui.QApplication.translate("HttpWidget", "Stop", None, QtGui.QApplication.UnicodeUTF8))
        self.stop.setText(QtGui.QApplication.translate("HttpWidget", "Stop", None, QtGui.QApplication.UnicodeUTF8))
        self.reload.setToolTip(QtGui.QApplication.translate("HttpWidget", "Reload", None, QtGui.QApplication.UnicodeUTF8))
        self.reload.setText(QtGui.QApplication.translate("HttpWidget", "Reload", None, QtGui.QApplication.UnicodeUTF8))

from PyQt4 import QtWebKit
