# This Python file uses the following encoding: utf-8
from pathlib import Path
import sys

from PySide6.QtWidgets import QApplication, QMainWindow, QPushButton, \
    QLineEdit, QVBoxLayout,  QRadioButton,  QComboBox, QCheckBox  # QTextEdit
import form_ui
from form_plot_ui import Ui_Plot
import credit_calc_ui
import deposit_calc_ui
from ctypes import *
from functools import partial
import pyqtgraph as pg
from pathlib import Path

import datetime
from calendar import monthrange


class MainWindow(QMainWindow):
    def __init__(self):
        super(MainWindow, self).__init__()
        self.ui = form_ui.Ui_MainWindow()
        self.ui.setupUi(self)

        self.setWindowTitle("Smart calculator")

        self.equals_button = self.findChild(QPushButton, "small_button")
        self.output_field = self.findChild(QLineEdit, "output_field")
        self.input_field = self.findChild(QLineEdit, "line_input_field")
        self.x_input_field = self.findChild(QLineEdit, "x_input_field")
        self.plot_button = self.findChild(QPushButton, "plot_button")
        self.credit_button = self.findChild(QPushButton, "credit_button")
        self.deposit_button = self.findChild(QPushButton, "deposit_button")

        self.plot_window = None
        self.credit_window = None
        self.deposit_window = None

        self.output_field.setReadOnly(True)

        self.input_field.returnPressed.connect(self.calculate_expression)
        self.x_input_field.returnPressed.connect(self.calculate_expression)

        self.equals_button.clicked.connect(self.calculate_expression)
        self.plot_button.clicked.connect(self.draw_plot)
        self.credit_button.clicked.connect(self.open_credit)
        self.deposit_button.clicked.connect(self.make_deposit)

        fuct_btn_ids = [("sin_button", " sin("), ("cos_button", " cos("), ("tan_button", " tan("), ("acos_button", " acos("),
                        ("asin_button", " asin("), ("atan_button",
                                                    " atan("), ("sqrt_button", " sqrt("), ("ln_button", " ln("),
                        ("log_button", " log("), ("mod_button", " mod ")]
        for i in range(len(fuct_btn_ids)):
            self.findChild(QPushButton, fuct_btn_ids[i][0]).clicked.connect(
                partial(self.append_text, fuct_btn_ids[i][1]))
        self.findChild(QPushButton, "clear_button").clicked.connect(
            self.clear_input)

    def clear_input(self):
        self.input_field.setText("0")
        self.x_input_field.setText("1")

    def append_text(self, text: str):
        self.input_field.setText(str(self.input_field.text()) + text)

    def open_credit(self):
        self.credit_window = CreditWindow()
        self.credit_window.show()

    def make_deposit(self):
        self.deposit_window = DepositWindow()
        self.deposit_window.show()

    def calculate_expression(self):

        text_from_input_field: str = self.get_expr()

        x_val_str: str = self.get_variable_str()
        is_valid = is_valid_inputs(text_from_input_field, x_val_str)

        if not is_valid:
            self.output_field.setText("Invalid input or x")
        else:
            self.output_field.setText(str(calculate_expr_at(
                text_from_input_field, float_from_str(x_val_str))))

    def get_expr(self) -> str:
        text_from_input_field: str = str(
            self.input_field.text())
        if len(text_from_input_field) == 1:
            text_from_input_field += " "
        return text_from_input_field

    def get_variable_str(self) -> str:
        x_var = str(self.x_input_field.text())
        x_var = x_var.replace(',', '.')
        return x_var

    def draw_plot(self):
        if not is_valid_inputs(self.get_expr(), self.get_variable_str()):
            self.output_field.setText("Invalid input or x")
            self.plot_window.close()
        else:
            self.plot_window = PlotWindow(self)
            self.plot_window.show()

    def closeEvent(self, event) -> None:
        if self.plot_window:
            self.plot_window.close()
        if self.credit_window:
            self.credit_window.close()
        if self.deposit_window:
            self.deposit_window.close()
        return super().closeEvent(event)


class PlotWindow(QMainWindow):

    def __init__(self, main_window: MainWindow):
        super().__init__()

        self.ui = Ui_Plot()
        self.ui.setupUi(self)

        self.setWindowTitle("Plot/graph window")

        self.plot = pg.PlotWidget(name="main_plot")
        self.plot.showGrid(x=True, y=True)
        self.plot.setAspectLocked(lock=True, ratio=1)
        self.plot.setLabels(left=('Y value'))
        self.plot.setLabels(bottom=('X value'))
        self.main_window = main_window
        self.pen = pg.mkPen(color=(255, 0, 0), width=6)

        self.x_min_edit = self.findChild(QLineEdit, "x_min_line_edit")
        self.x_max_edit = self.findChild(QLineEdit, "x_max_line_edit")
        self.y_min_edit = self.findChild(QLineEdit, "y_min_line_edit")
        self.y_max_edit = self.findChild(QLineEdit, "y_max_line_edit")

        self.plot_button = self.findChild(QPushButton, "plot_button")
        self.reset_button = self.findChild(QPushButton, "reset_button")

        layout = self.findChild(QVBoxLayout, "plot_layout")

        self.plot_button.clicked.connect(self.redraw_plot)
        self.reset_button.clicked.connect(self.reset)

        layout.setContentsMargins(-2, -2, -2, -2)
        layout.setSpacing(-1)
        layout.addWidget(self.plot)

        self.redraw_plot()

    def reset(self):
        self.x_min_edit.setText("-100")
        self.x_max_edit.setText("+100")
        self.y_min_edit.setText("-100")
        self.y_max_edit.setText("+100")

        self.plot.getPlotItem().enableAutoRange()
        self.redraw_plot()

    def redraw_plot(self):
        x_min_str = str(self.x_min_edit.text())
        x_max_str = str(self.x_max_edit.text())
        y_min_str = str(self.y_min_edit.text())
        y_max_str = str(self.y_max_edit.text())

        all_strs_valid = is_valid_inputs(
            self.main_window.get_expr(), self.main_window.get_variable_str()) \
            and is_valid_variable_str(x_min_str) \
            and is_valid_variable_str(x_max_str) \
            and is_valid_variable_str(y_min_str) \
            and is_valid_variable_str(y_max_str)

        all_nums_valid = all_strs_valid and \
            float_from_str(x_max_str) >= float_from_str(x_min_str) and \
            float_from_str(y_max_str) >= float_from_str(y_min_str)

        if all_nums_valid:
            x_min = max(float_from_str(x_min_str), -1e6)
            x_max = min(float_from_str(x_max_str), +1e6)
            y_min = max(float_from_str(y_min_str), -1e6)
            y_max = min(float_from_str(y_max_str), +1e6)

            num_steps = 50000
            step = (x_max - x_min) / num_steps
            x_values = [x_min + step * i for i in range(num_steps)]
            y_values = [calculate_expr_at(
                self.main_window.get_expr(), x) for x in x_values]
            self.plot.clear()

            start_of_line = 0
            i = 0
            while i < len(x_values):
                if not (y_min <= y_values[i] <= y_max):
                    self.plot.plot(x_values[start_of_line:i],
                                   y_values[start_of_line:i],
                                   pen=self.pen)
                    while i < len(x_values) and not (y_min <= y_values[i] <= y_max):
                        i += 1
                    start_of_line = i
                else:
                    i += 1
            self.plot.plot(x_values[start_of_line:],
                           y_values[start_of_line:],
                           pen=self.pen)
            self.plot.setTitle(
                "Y = " + self.main_window.get_expr(), size="30pt")
        else:
            self.x_min_edit.setText("Invalid value")
            self.x_max_edit.setText("Invalid value")
            self.y_min_edit.setText("Invalid value")
            self.y_max_edit.setText("Invalid value")


class CreditWindow(QMainWindow):

    def __init__(self):
        super().__init__()

        self.ui = credit_calc_ui.Ui_MainWindow()
        self.ui.setupUi(self)

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

        sum_str = str(self.sum_field.text())
        rate_str = str(self.rate_field.text())
        time_str = str(self.time_field.text())

        all_strs_correct = is_valid_variable_str(sum_str) \
            and is_valid_integer_varible_str(time_str) \
            and is_valid_variable_str(rate_str)

        all_nums_correct = all_strs_correct \
            and float_from_str(sum_str) > 0 \
            and 0 <= float_from_str(rate_str) <= 1000 \
            and (self.month_radio.isChecked() and 1 <= float_from_str(time_str) <= 600
                 or self.year_radio.isChecked() and 1 <= float_from_str(time_str) <= 50)

        if all_nums_correct:
            credit = float_from_str(sum_str)
            rate = float_from_str(rate_str)
            time = int(float_from_str(time_str))

            if self.year_radio.isChecked():
                time *= 12

            p = rate / 1200
            if self.annuity_radio.isChecked():
                payment = credit * p * (1 + p)**time / ((1 + p)**time - 1)
                payments = [payment] * time
                self.payment_field.setText(str(payment))
            else:
                d = credit / time

                payments = [d + (credit - d * (month - 1)) *
                            p for month in range(1, time + 1)]
                self.payment_field.setText(
                    str(payments[0]) + " -> " + str(payments[-1]))

            total = sum(payments)
            overpayment = total - credit

            self.overpayment_field.setText(str(overpayment))
            self.total_field.setText(str(total))

        else:
            self.total_field.setText("Invalid input")
            self.payment_field.setText("Invalid input")
            self.overpayment_field.setText("Invalid input")


class DepositWindow(QMainWindow):

    def __init__(self):
        super().__init__()

        self.ui = deposit_calc_ui.Ui_MainWindow()
        self.ui.setupUi(self)

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

    def get_replenishment_period(self) -> int:
        if self.replenishment_combobox.currentText() == "Once a month":
            period = 1
        elif self.replenishment_combobox.currentText() == "Once in two months":
            period = 2
        elif self.replenishment_combobox.currentText() == "Once a quarter":
            period = 3
        elif self.replenishment_combobox.currentText() == "Semiannually":
            period = 6
        elif self.replenishment_combobox.currentText() == "Annually":
            period = 12
        else:
            period = -1
        return period

    def get_withdrawal_period(self) -> int:
        if self.withdrawal_combobox.currentText() == "Once a month":
            period = 1
        elif self.withdrawal_combobox.currentText() == "Once in two months":
            period = 2
        elif self.withdrawal_combobox.currentText() == "Once a quarter":
            period = 3
        elif self.withdrawal_combobox.currentText() == "Semiannually":
            period = 6
        elif self.withdrawal_combobox.currentText() == "Annually":
            period = 12
        else:
            period = -1
        return period

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


def day_in_this_year(year: int) -> int:
    days = 0
    if year % 4 != 0:
        days = 365
    elif year % 100 != 0:
        days = 366
    elif year % 400 != 0:
        days = 365
    else:
        days = 366
    return days


def convert_months_days(months: int) -> int:
    date = datetime.datetime.now()
    now_year, now_month = date.year, date.month
    converted_time = 0
    for i in range(months):
        days_in_month = monthrange(now_year, now_month)[1]
        converted_time += days_in_month
        now_month += 1
        if now_month > 12:
            now_year += 1
        now_month = 1

    return converted_time


def is_valid_variable_str(var_str: str) -> bool:
    var_str = var_str.replace(",", ".")
    is_valid = True
    try:
        x_value: float = float(var_str)
        is_valid = is_valid and (
            var_str[0].isdigit() or var_str[0] in ['-', '+'])
    except ValueError:
        is_valid = False
    return is_valid


def is_valid_integer_varible_str(var_str: str) -> bool:
    return is_valid_variable_str(var_str) \
        and var_str.isdigit() \



def float_from_str(var_str: str) -> float:
    var_str = var_str.replace(",", ".")
    if not is_valid_variable_str(var_str):
        raise Exception("Getting value from incorrect string!")
    else:
        return float(var_str)


def is_valid_inputs(expression: str, x_input: str) -> bool:
    so_file = str(Path(__file__).absolute())
    so_file = so_file[:so_file.rfind('/') + 1] + "/libcalculate.so"
    shared_fun = CDLL(so_file)

    arg_to_pass = expression.encode('ascii')
    is_valid = shared_fun.is_valid_input(arg_to_pass)
    is_valid = is_valid and is_valid_variable_str(x_input)

    return is_valid


def calculate_expr_at(expr: str, x: float) -> float:
    if not is_valid_inputs(expr, str(x)):
        raise Exception("Calculation on invalid string!")

    so_file = str(Path(__file__).absolute())
    so_file = so_file[:so_file.rfind('/') + 1] + "/libcalculate.so"
    shared_fun = CDLL(so_file)
    shared_fun.calculate.argtypes = [c_char_p, c_longdouble]
    shared_fun.calculate.restype = c_longdouble  # c_longdouble  # c_double

    arg_to_pass = expr.encode('ascii')
    return shared_fun.calculate(arg_to_pass, x)


if __name__ == "__main__":
    app = QApplication(sys.argv)
    calc_window = MainWindow()
    calc_window.show()
    app.exec()
