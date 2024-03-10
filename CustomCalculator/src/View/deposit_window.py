from PySide6.QtWidgets import QMainWindow, QPushButton, QLineEdit, QComboBox, QCheckBox
import View.ui.deposit_calc_ui
from Controller.user_controller import UserController
import datetime
from calendar import monthrange


class DepositWindow(QMainWindow):

    def __init__(self):
        super().__init__()

        self.ui = View.ui.deposit_calc_ui.Ui_MainWindow()
        self.ui.setupUi(self)

        self.controller = UserController()

        self.setWindowTitle("Deposit details")

        self.sum_field = self.findChild(QLineEdit, "sum_deposit_line_edit")
        self.rate_field = self.findChild(QLineEdit, "rate_line_edit")
        self.tax_field = self.findChild(QLineEdit, "tax_line_edit")
        self.time_field = self.findChild(QLineEdit, "time_line_edit")

        self.replenishment_combobox = self.findChild(
            QComboBox, "replenishment_combobox")
        self.withdrawal_combobox = self.findChild(
            QComboBox, "withdrawal_combobox")
        self.frequency_combobox = self.findChild(
            QComboBox, "frequency_combobox")
        self.make_deposit_button = self.findChild(
            QPushButton, "make_deposit_button")
        self.replenishment_field = self.findChild(
            QLineEdit, "replenishment_line_edit")
        self.withdrawal_field = self.findChild(
            QLineEdit, "withdrawal_line_edit")
        self.capitalization_checkbox = self.findChild(
            QCheckBox, "capitalization_checkbox")
        self.charges_output = self.findChild(QLineEdit, "payment_line_edit")
        self.tax_output = self.findChild(QLineEdit, "tax_line_edit_2")
        self.final_sum_output = self.findChild(QLineEdit, "total_line_edit")

        freqs = ['Once a month', 'Once in two months',
                 "Once a quarter", 'Semiannually', 'Annually']
        self.replenishment_combobox.addItems(freqs)
        self.withdrawal_combobox.addItems(freqs)
        self.frequency_combobox.addItems(freqs)

        self.frequency_combobox.setCurrentIndex(0)

        self.make_deposit_button.clicked.connect(self.calculate)

    def calculate(self):
        all_nums_correct = self.check_nums_input()

        if all_nums_correct:
            deposit = float_from_str(str(self.sum_field.text()))
            rate = float_from_str(str(self.rate_field.text()))
            time = int(float_from_str(str(self.time_field.text())))
            tax = float_from_str(str(self.tax_field.text()))
            replenishment = float_from_str(
                str(self.replenishment_field.text()))
            withdrawal = float_from_str(str(self.withdrawal_field.text()))

            is_making_repls = self.replenishment_combobox.currentText() != "None"
            is_making_withdraws = self.withdrawal_combobox.currentText() != "None"

            repl_months_period = self.get_replenishment_period()
            withdr_months_period = self.get_withdrawal_period()

            charges, got_taxes = self.process_charges_taxes(deposit, time, is_making_repls, repl_months_period,
                                                            replenishment, is_making_withdraws, withdr_months_period,
                                                            withdrawal, rate)

            self.charges_output.setText(str(charges))
            self.final_sum_output.setText(str(charges + deposit))
            self.tax_output.setText(str(got_taxes * tax / 100))

        else:
            self.tax_output.setText("Invalid input")
            self.charges_output.setText("Invalid input")
            self.final_sum_output.setText("Invalid input")

    def check_nums_input(self) -> bool:
        sum_str = str(self.sum_field.text())
        rate_str = str(self.rate_field.text())
        time_str = str(self.time_field.text())
        tax_str = str(self.tax_field.text())
        replenish_str = str(self.replenishment_field.text())
        withdrawal_str = str(self.withdrawal_field.text())

        strs_inputs = [sum_str, rate_str, time_str,
                       tax_str, replenish_str, withdrawal_str]

        all_strs_correct = sum([is_valid_variable_str(var_str) for var_str in strs_inputs]) == len(strs_inputs) \
            and is_valid_integer_varible_str(time_str)

        all_nums_correct = all_strs_correct \
            and float_from_str(sum_str) > 0 \
            and 0 <= float_from_str(rate_str) <= 100 \
            and 0 <= float_from_str(tax_str) <= 100 \
            and float_from_str(replenish_str) >= 0 \
            and float_from_str(withdrawal_str) >= 0 \
            and float_from_str(time_str) > 0 \
            and float_from_str(time_str) <= 18250

        return all_nums_correct

    # def get_replenishment_period(self) -> int:
    #     if self.replenishment_combobox.currentText() == "Once a month":
    #         period = 1
    #     elif self.replenishment_combobox.currentText() == "Once in two months":
    #         period = 2
    #     elif self.replenishment_combobox.currentText() == "Once a quarter":
    #         period = 3
    #     elif self.replenishment_combobox.currentText() == "Semiannually":
    #         period = 6
    #     elif self.replenishment_combobox.currentText() == "Annually":
    #         period = 12
    #     else:
    #         period = -1
    #     return period

    # def get_withdrawal_period(self) -> int:
    #     if self.withdrawal_combobox.currentText() == "Once a month":
    #         period = 1
    #     elif self.withdrawal_combobox.currentText() == "Once in two months":
    #         period = 2
    #     elif self.withdrawal_combobox.currentText() == "Once a quarter":
    #         period = 3
    #     elif self.withdrawal_combobox.currentText() == "Semiannually":
    #         period = 6
    #     elif self.withdrawal_combobox.currentText() == "Annually":
    #         period = 12
    #     else:
    #         period = -1
    #     return period

    def process_charges_taxes(self, deposit, time, is_making_repls, repl_months_period,
                              replenishment, is_making_withdraws, withdr_months_period, withdrawal, rate) -> (int, int):
        # (charges, taxes)
        KEY_BANK_PERCENT = 0.15

        charges, got_taxes = 0, 0
        got_last_year_taxes = 0
        date = datetime.datetime.now()
        now_year, now_month, now_day = date.year, date.month, date.day
        months_passed = 0
        start_day = now_day
        for i in range(time):
            days_in_month = monthrange(now_year, now_month)[1]
            days_in_year = day_in_this_year(now_year)

            if now_day > days_in_month:
                now_month += 1
                now_day = 1
                months_passed += 1

                if is_making_repls and months_passed % repl_months_period == 0:
                    deposit += replenishment

                if is_making_withdraws and months_passed % withdr_months_period == 0:
                    deposit -= withdrawal
                    deposit = max(deposit, 0)

            if now_month > 12:
                got_taxes += max(got_last_year_taxes -
                                 1_000_000 * KEY_BANK_PERCENT, 0)
                got_last_year_taxes = 0

                now_year += 1
                now_month = 1

            if self.capitalization_checkbox.isChecked():
                day_payment = round(
                    (charges + deposit) * rate / (100 * days_in_year), 2)
            else:
                day_payment = round(
                    deposit * rate / (100 * days_in_year), 2)

            charges += day_payment
            got_last_year_taxes += day_payment

            now_day += 1

        got_taxes += max(got_last_year_taxes -
                         1_000_000 * KEY_BANK_PERCENT, 0)

        return (charges, got_taxes)
