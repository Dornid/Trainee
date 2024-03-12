from PySide6.QtWidgets import QMainWindow, QPushButton, QLineEdit, QRadioButton
import View.ui.credit_calc_ui
from Controller.user_controller import UserController


class CreditWindow(QMainWindow):

    def __init__(self):
        super().__init__()

        self.ui = View.ui.credit_calc_ui.Ui_MainWindow()
        self.ui.setupUi(self)

        self.controller = UserController()

        self.setWindowTitle("Credit details")

        self.sum_field = self.findChild(QLineEdit, "sum_line_edit")
        self.rate_field = self.findChild(QLineEdit, "rate_line_edit")
        self.time_field = self.findChild(QLineEdit, "time_line_edit")
        self.month_radio = self.findChild(QRadioButton, "month_radio")
        self.year_radio = self.findChild(QRadioButton, "year_radio")
        self.annuity_radio = self.findChild(
            QRadioButton, "annuity_radio")
        self.differential_radio = self.findChild(
            QRadioButton, "differential_radio")

        self.payment_field = self.findChild(QLineEdit, "payment_line_edit")
        self.overpayment_field = self.findChild(
            QLineEdit, "overpayment_line_edit")
        self.total_field = self.findChild(QLineEdit, "total_line_edit")
        self.apply_button = self.findChild(QPushButton, "apply_button")

        self.month_radio.setChecked(True)
        self.annuity_radio.setChecked(True)

        self.payment_field.setReadOnly(True)
        self.overpayment_field.setReadOnly(True)
        self.total_field.setReadOnly(True)

        self.apply_button.clicked.connect(self.calculate)

    def calculate(self):
        str_payment, str_overpayment, str_total = self.controller.credit_calculate(
            str(self.sum_field.text()),
            str(self.rate_field.text()),
            str(self.time_field.text()),
            self.month_radio.isChecked(),
            self.annuity_radio.isChecked()
        )

        self.payment_field.setText(str_payment)
        self.overpayment_field.setText(str_overpayment)
        self.total_field.setText(str_total)
