from PySide6.QtWidgets import QMainWindow, QPushButton, QLineEdit, QComboBox, QCheckBox
import View.ui.deposit_calc_ui
from Controller.user_controller import UserController


class DepositWindow(QMainWindow):

    def __init__(self, controller: UserController):
        super().__init__()

        self.ui = View.ui.deposit_calc_ui.Ui_MainWindow()
        self.ui.setupUi(self)

        self.controller = controller

        self.setWindowTitle("Deposit details")

        self.sum_field = self.findChild(QLineEdit, "sum_deposit_line_edit")
        self.rate_field = self.findChild(QLineEdit, "rate_line_edit")
        self.tax_field = self.findChild(QLineEdit, "tax_line_edit")
        self.time_field = self.findChild(QLineEdit, "time_line_edit")

        self.frequency_combobox = self.findChild(
            QComboBox, "frequency_combobox")
        self.make_deposit_button = self.findChild(
            QPushButton, "make_deposit_button")
        self.capitalization_checkbox = self.findChild(
            QCheckBox, "capitalization_checkbox")

        self.charges_output = self.findChild(QLineEdit, "payment_line_edit")
        self.tax_output = self.findChild(QLineEdit, "tax_line_edit_2")
        self.final_sum_output = self.findChild(QLineEdit, "total_line_edit")

        freqs = ['Once a month', 'Once in two months',
                 "Once a quarter", 'Semiannually', 'Annually']
        self.frequency_combobox.addItems(freqs)

        self.frequency_combobox.setCurrentIndex(0)

        self.make_deposit_button.clicked.connect(self.calculate)

    def calculate(self):
        tax_output, charges_output, final_sum_output = self.controller.set_then_deposit_calculate(
            str(self.sum_field.text()),
            str(self.rate_field.text()),
            str(self.time_field.text()),
            str(self.tax_field.text()),
            self.capitalization_checkbox.isChecked()
        )

        self.tax_output.setText(tax_output)
        self.charges_output.setText(charges_output)
        self.final_sum_output.setText(final_sum_output)
