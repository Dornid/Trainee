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

        # sum_str = str(self.sum_field.text())
        # rate_str = str(self.rate_field.text())
        # time_str = str(self.time_field.text())

        # is_valid_variable_str = self.controller.is_valid_variable_str
        # float_from_str = self.controller.float_from_str
        # is_valid_integer_varible_str = self.controller.is_valid_integer_varible_str

        # all_strs_correct = is_valid_variable_str(sum_str) \
        #     and is_valid_integer_varible_str(time_str) \
        #     and is_valid_variable_str(rate_str)

        # all_nums_correct = all_strs_correct \
        #     and float_from_str(sum_str) > 0 \
        #     and 0 <= float_from_str(rate_str) <= 1000 \
        #     and (self.month_radio.isChecked() and 1 <= float_from_str(time_str) <= 600
        #          or self.year_radio.isChecked() and 1 <= float_from_str(time_str) <= 50)

        # if all_nums_correct:
        #     credit = float_from_str(sum_str)
        #     rate = float_from_str(rate_str)
        #     time = int(float_from_str(time_str))

        #     if self.year_radio.isChecked():
        #         time *= 12

        #     p = rate / 1200
        #     if self.annuity_radio.isChecked():
        #         payment = credit * p * (1 + p)**time / ((1 + p)**time - 1)
        #         payments = [payment] * time
        #         self.payment_field.setText(str(payment))
        #     else:
        #         d = credit / time

        #         payments = [d + (credit - d * (month - 1)) *
        #                     p for month in range(1, time + 1)]
        #         self.payment_field.setText(
        #             str(payments[0]) + " -> " + str(payments[-1]))

        #     total = sum(payments)
        #     overpayment = total - credit

        #     str_payment, str_overpayment, str_total = self.controller.credit_calculate()

        #     self.overpayment_field.setText(str(overpayment))
        #     self.total_field.setText(str(total))

        # else:
        #     self.total_field.setText("Invalid input")
        #     self.payment_field.setText("Invalid input")
        #     self.overpayment_field.setText("Invalid input")
