from PySide6.QtWidgets import QMainWindow, QPushButton, QLineEdit
import View.ui.form_ui
from functools import partial
from View.plot_window import PlotWindow
from View.credit_window import CreditWindow
from View.deposit_window import DepositWindow
from Controller.user_controller import UserController


class MainWindow(QMainWindow):
    def __init__(self, controller: UserController):
        super(MainWindow, self).__init__()
        self.ui = View.ui.form_ui.Ui_MainWindow()
        self.ui.setupUi(self)

        self.controller = controller

        self.setWindowTitle("Custom calculator")

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
        self.credit_window = CreditWindow(self.controller)
        self.credit_window.show()

    def make_deposit(self):
        self.deposit_window = DepositWindow(self.controller)
        self.deposit_window.show()

    def calculate_expression(self):
        text_from_input_field: str = self.get_expr()
        x_val_str: str = self.get_variable_str()
        is_valid = self.controller.set_then_validate(
            text_from_input_field, x_val_str)

        if not is_valid:
            self.output_field.setText("Invalid input or x")
        else:
            output_text = str(
                self.controller.set_then_calculate(
                    text_from_input_field,
                    self.controller.float_from_str(x_val_str)))
            self.output_field.setText(output_text)

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
        if not self.controller.set_then_validate(self.get_expr(), self.get_variable_str()):
            self.output_field.setText("Invalid input or x")
            self.plot_window.close()
        else:
            self.plot_window = PlotWindow(self, self.controller)
            self.plot_window.show()

    def closeEvent(self, event) -> None:
        if self.plot_window:
            self.plot_window.close()
        if self.credit_window:
            self.credit_window.close()
        if self.deposit_window:
            self.deposit_window.close()
        return super().closeEvent(event)
