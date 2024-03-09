# -*- coding: utf-8 -*-

################################################################################
## Form generated from reading UI file 'form_plot.ui'
##
## Created by: Qt User Interface Compiler version 6.5.2
##
## WARNING! All changes made in this file will be lost when recompiling UI file!
################################################################################

from PySide6.QtCore import (QCoreApplication, QDate, QDateTime, QLocale,
    QMetaObject, QObject, QPoint, QRect,
    QSize, QTime, QUrl, Qt)
from PySide6.QtGui import (QBrush, QColor, QConicalGradient, QCursor,
    QFont, QFontDatabase, QGradient, QIcon,
    QImage, QKeySequence, QLinearGradient, QPainter,
    QPalette, QPixmap, QRadialGradient, QTransform)
from PySide6.QtWidgets import (QApplication, QLabel, QLineEdit, QPushButton,
    QSizePolicy, QVBoxLayout, QWidget)

class Ui_Plot(object):
    def setupUi(self, Plot):
        if not Plot.objectName():
            Plot.setObjectName(u"Plot")
        Plot.resize(839, 747)
        Plot.setMinimumSize(QSize(839, 747))
        Plot.setMaximumSize(QSize(839, 747))
        self.verticalLayoutWidget = QWidget(Plot)
        self.verticalLayoutWidget.setObjectName(u"verticalLayoutWidget")
        self.verticalLayoutWidget.setGeometry(QRect(0, 0, 841, 561))
        self.plot_layout = QVBoxLayout(self.verticalLayoutWidget)
        self.plot_layout.setObjectName(u"plot_layout")
        self.plot_layout.setContentsMargins(0, 0, 0, 0)
        self.x_min_line_edit = QLineEdit(Plot)
        self.x_min_line_edit.setObjectName(u"x_min_line_edit")
        self.x_min_line_edit.setGeometry(QRect(110, 600, 221, 51))
        font = QFont()
        font.setPointSize(20)
        self.x_min_line_edit.setFont(font)
        self.x_max_line_edit = QLineEdit(Plot)
        self.x_max_line_edit.setObjectName(u"x_max_line_edit")
        self.x_max_line_edit.setGeometry(QRect(430, 600, 241, 51))
        self.x_max_line_edit.setFont(font)
        self.y_min_line_edit = QLineEdit(Plot)
        self.y_min_line_edit.setObjectName(u"y_min_line_edit")
        self.y_min_line_edit.setGeometry(QRect(110, 670, 221, 51))
        self.y_min_line_edit.setFont(font)
        self.y_max_line_edit = QLineEdit(Plot)
        self.y_max_line_edit.setObjectName(u"y_max_line_edit")
        self.y_max_line_edit.setGeometry(QRect(430, 670, 241, 51))
        self.y_max_line_edit.setFont(font)
        self.label = QLabel(Plot)
        self.label.setObjectName(u"label")
        self.label.setGeometry(QRect(30, 600, 67, 51))
        self.label_2 = QLabel(Plot)
        self.label_2.setObjectName(u"label_2")
        self.label_2.setGeometry(QRect(350, 600, 67, 51))
        self.label_3 = QLabel(Plot)
        self.label_3.setObjectName(u"label_3")
        self.label_3.setGeometry(QRect(30, 670, 67, 51))
        self.label_4 = QLabel(Plot)
        self.label_4.setObjectName(u"label_4")
        self.label_4.setGeometry(QRect(350, 670, 67, 51))
        self.plot_button = QPushButton(Plot)
        self.plot_button.setObjectName(u"plot_button")
        self.plot_button.setGeometry(QRect(690, 590, 131, 61))
        self.plot_button.setFont(font)
        self.reset_button = QPushButton(Plot)
        self.reset_button.setObjectName(u"reset_button")
        self.reset_button.setGeometry(QRect(690, 670, 131, 61))
        self.reset_button.setFont(font)

        self.retranslateUi(Plot)

        QMetaObject.connectSlotsByName(Plot)
    # setupUi

    def retranslateUi(self, Plot):
        Plot.setWindowTitle(QCoreApplication.translate("Plot", u"Form", None))
        self.x_min_line_edit.setText(QCoreApplication.translate("Plot", u"-100", None))
        self.x_max_line_edit.setText(QCoreApplication.translate("Plot", u"100", None))
        self.y_min_line_edit.setText(QCoreApplication.translate("Plot", u"-100", None))
        self.y_max_line_edit.setText(QCoreApplication.translate("Plot", u"100", None))
        self.label.setText(QCoreApplication.translate("Plot", u"<html><head/><body><p><span style=\" font-size:20pt;\">X</span><span style=\" font-size:20pt; vertical-align:sub;\">min</span><span style=\" font-size:20pt;\"> =</span></p></body></html>", None))
        self.label_2.setText(QCoreApplication.translate("Plot", u"<html><head/><body><p><span style=\" font-size:20pt;\">X</span><span style=\" font-size:20pt; vertical-align:sub;\">max</span><span style=\" font-size:20pt;\"> =</span></p></body></html>", None))
        self.label_3.setText(QCoreApplication.translate("Plot", u"<html><head/><body><p><span style=\" font-size:20pt;\">Y</span><span style=\" font-size:20pt; vertical-align:sub;\">min</span><span style=\" font-size:20pt;\"> =</span></p></body></html>", None))
        self.label_4.setText(QCoreApplication.translate("Plot", u"<html><head/><body><p><span style=\" font-size:20pt;\">Y</span><span style=\" font-size:20pt; vertical-align:sub;\">max</span><span style=\" font-size:20pt;\"> =</span></p></body></html>", None))
        self.plot_button.setText(QCoreApplication.translate("Plot", u"Plot", None))
        self.reset_button.setText(QCoreApplication.translate("Plot", u"Reset", None))
    # retranslateUi

