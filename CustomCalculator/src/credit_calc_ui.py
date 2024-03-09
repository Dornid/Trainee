# -*- coding: utf-8 -*-

################################################################################
## Form generated from reading UI file 'credit_calc.ui'
##
## Created by: Qt User Interface Compiler version 6.5.2
##
## WARNING! All changes made in this file will be lost when recompiling UI file!
################################################################################

from PySide6.QtCore import (QCoreApplication, QDate, QDateTime, QLocale,
    QMetaObject, QObject, QPoint, QRect,
    QSize, QTime, QUrl, Qt)
from PySide6.QtGui import (QAction, QBrush, QColor, QConicalGradient,
    QCursor, QFont, QFontDatabase, QGradient,
    QIcon, QImage, QKeySequence, QLinearGradient,
    QPainter, QPalette, QPixmap, QRadialGradient,
    QTransform)
from PySide6.QtWidgets import (QApplication, QLabel, QLineEdit, QMainWindow,
    QMenu, QMenuBar, QPushButton, QRadioButton,
    QSizePolicy, QStatusBar, QVBoxLayout, QWidget)

class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        if not MainWindow.objectName():
            MainWindow.setObjectName(u"MainWindow")
        MainWindow.resize(825, 600)
        MainWindow.setMinimumSize(QSize(825, 600))
        MainWindow.setMaximumSize(QSize(825, 600))
        self.centralwidget = QWidget(MainWindow)
        self.centralwidget.setObjectName(u"centralwidget")
        self.sum_line_edit = QLineEdit(self.centralwidget)
        self.sum_line_edit.setObjectName(u"sum_line_edit")
        self.sum_line_edit.setGeometry(QRect(30, 10, 431, 41))
        font = QFont()
        font.setPointSize(18)
        self.sum_line_edit.setFont(font)
        self.time_line_edit = QLineEdit(self.centralwidget)
        self.time_line_edit.setObjectName(u"time_line_edit")
        self.time_line_edit.setGeometry(QRect(30, 130, 431, 41))
        self.time_line_edit.setFont(font)
        self.rate_line_edit = QLineEdit(self.centralwidget)
        self.rate_line_edit.setObjectName(u"rate_line_edit")
        self.rate_line_edit.setGeometry(QRect(30, 70, 431, 41))
        self.rate_line_edit.setFont(font)
        self.payment_line_edit = QLineEdit(self.centralwidget)
        self.payment_line_edit.setObjectName(u"payment_line_edit")
        self.payment_line_edit.setGeometry(QRect(30, 270, 551, 41))
        self.payment_line_edit.setFont(font)
        self.overpayment_line_edit = QLineEdit(self.centralwidget)
        self.overpayment_line_edit.setObjectName(u"overpayment_line_edit")
        self.overpayment_line_edit.setGeometry(QRect(30, 340, 551, 41))
        self.overpayment_line_edit.setFont(font)
        self.total_line_edit = QLineEdit(self.centralwidget)
        self.total_line_edit.setObjectName(u"total_line_edit")
        self.total_line_edit.setGeometry(QRect(30, 410, 551, 41))
        self.total_line_edit.setFont(font)
        self.label = QLabel(self.centralwidget)
        self.label.setObjectName(u"label")
        self.label.setGeometry(QRect(630, 0, 181, 61))
        self.label.setFont(font)
        self.label_2 = QLabel(self.centralwidget)
        self.label_2.setObjectName(u"label_2")
        self.label_2.setGeometry(QRect(560, 60, 261, 51))
        self.label_2.setFont(font)
        self.label_3 = QLabel(self.centralwidget)
        self.label_3.setObjectName(u"label_3")
        self.label_3.setGeometry(QRect(480, 110, 341, 61))
        self.label_3.setFont(font)
        self.label_4 = QLabel(self.centralwidget)
        self.label_4.setObjectName(u"label_4")
        self.label_4.setGeometry(QRect(610, 270, 211, 41))
        self.label_4.setFont(font)
        self.label_5 = QLabel(self.centralwidget)
        self.label_5.setObjectName(u"label_5")
        self.label_5.setGeometry(QRect(600, 330, 231, 61))
        self.label_5.setFont(font)
        self.label_6 = QLabel(self.centralwidget)
        self.label_6.setObjectName(u"label_6")
        self.label_6.setGeometry(QRect(620, 400, 201, 61))
        self.label_6.setFont(font)
        self.apply_button = QPushButton(self.centralwidget)
        self.apply_button.setObjectName(u"apply_button")
        self.apply_button.setGeometry(QRect(160, 480, 511, 61))
        font1 = QFont()
        font1.setPointSize(23)
        self.apply_button.setFont(font1)
        self.verticalLayoutWidget = QWidget(self.centralwidget)
        self.verticalLayoutWidget.setObjectName(u"verticalLayoutWidget")
        self.verticalLayoutWidget.setGeometry(QRect(230, 181, 316, 81))
        self.payment_radio_group = QVBoxLayout(self.verticalLayoutWidget)
        self.payment_radio_group.setObjectName(u"payment_radio_group")
        self.payment_radio_group.setContentsMargins(0, 0, 0, 0)
        self.annuity_radio = QRadioButton(self.verticalLayoutWidget)
        self.annuity_radio.setObjectName(u"annuity_radio")
        font2 = QFont()
        font2.setPointSize(16)
        self.annuity_radio.setFont(font2)

        self.payment_radio_group.addWidget(self.annuity_radio)

        self.differential_radio = QRadioButton(self.verticalLayoutWidget)
        self.differential_radio.setObjectName(u"differential_radio")
        self.differential_radio.setFont(font2)

        self.payment_radio_group.addWidget(self.differential_radio)

        self.verticalLayoutWidget_2 = QWidget(self.centralwidget)
        self.verticalLayoutWidget_2.setObjectName(u"verticalLayoutWidget_2")
        self.verticalLayoutWidget_2.setGeometry(QRect(30, 180, 160, 80))
        self.verticalLayout = QVBoxLayout(self.verticalLayoutWidget_2)
        self.verticalLayout.setObjectName(u"verticalLayout")
        self.verticalLayout.setContentsMargins(0, 0, 0, 0)
        self.month_radio = QRadioButton(self.verticalLayoutWidget_2)
        self.month_radio.setObjectName(u"month_radio")
        self.month_radio.setFont(font2)

        self.verticalLayout.addWidget(self.month_radio)

        self.year_radio = QRadioButton(self.verticalLayoutWidget_2)
        self.year_radio.setObjectName(u"year_radio")
        self.year_radio.setFont(font2)

        self.verticalLayout.addWidget(self.year_radio)

        MainWindow.setCentralWidget(self.centralwidget)
        self.menubar = QMenuBar(MainWindow)
        self.menubar.setObjectName(u"menubar")
        self.menubar.setGeometry(QRect(0, 0, 825, 22))
        self.menuCredit_OOO_Bank = QMenu(self.menubar)
        self.menuCredit_OOO_Bank.setObjectName(u"menuCredit_OOO_Bank")
        MainWindow.setMenuBar(self.menubar)
        self.statusbar = QStatusBar(MainWindow)
        self.statusbar.setObjectName(u"statusbar")
        MainWindow.setStatusBar(self.statusbar)

        self.menubar.addAction(self.menuCredit_OOO_Bank.menuAction())

        self.retranslateUi(MainWindow)

        QMetaObject.connectSlotsByName(MainWindow)
    # setupUi

    def retranslateUi(self, MainWindow):
        MainWindow.setWindowTitle(QCoreApplication.translate("MainWindow", u"MainWindow", None))
        self.sum_line_edit.setText(QCoreApplication.translate("MainWindow", u"0", None))
        self.time_line_edit.setText(QCoreApplication.translate("MainWindow", u"0", None))
        self.rate_line_edit.setText(QCoreApplication.translate("MainWindow", u"0", None))
        self.payment_line_edit.setText(QCoreApplication.translate("MainWindow", u"-", None))
        self.overpayment_line_edit.setText(QCoreApplication.translate("MainWindow", u"-", None))
        self.total_line_edit.setText(QCoreApplication.translate("MainWindow", u"-", None))
        self.label.setText(QCoreApplication.translate("MainWindow", u"Sum of a credit", None))
        self.label_2.setText(QCoreApplication.translate("MainWindow", u"Percent % rate, yearly", None))
        self.label_3.setText(QCoreApplication.translate("MainWindow", u"Time/term for a credit to pay", None))
        self.label_4.setText(QCoreApplication.translate("MainWindow", u"Monthly payment", None))
        self.label_5.setText(QCoreApplication.translate("MainWindow", u"Total overpayment", None))
        self.label_6.setText(QCoreApplication.translate("MainWindow", u"Total sum to pay", None))
        self.apply_button.setText(QCoreApplication.translate("MainWindow", u"Apply for a loan ", None))
        self.annuity_radio.setText(QCoreApplication.translate("MainWindow", u"Annuity payment", None))
        self.differential_radio.setText(QCoreApplication.translate("MainWindow", u"Differential payment", None))
        self.month_radio.setText(QCoreApplication.translate("MainWindow", u"Months", None))
        self.year_radio.setText(QCoreApplication.translate("MainWindow", u"Years", None))
        self.menuCredit_OOO_Bank.setTitle(QCoreApplication.translate("MainWindow", u"Credit OOO Bank", None))
    # retranslateUi

