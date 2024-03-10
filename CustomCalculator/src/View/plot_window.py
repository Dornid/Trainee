from PySide6.QtWidgets import QMainWindow, QPushButton, QLineEdit, QVBoxLayout
from View.ui.form_plot_ui import Ui_Plot
import pyqtgraph as pg
from Controller.user_controller import UserController

import sys
sys.path.append('../Controller/user_controller.py')


class PlotWindow(QMainWindow):

    def __init__(self, main_window: QMainWindow):
        super().__init__()

        self.ui = Ui_Plot()
        self.ui.setupUi(self)

        self.controller = UserController()

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

        is_valid_inputs = self.controller.is_valid_inputs
        is_valid_variable_str = self.controller.is_valid_variable_str
        float_from_str = self.controller.float_from_str
        calculate_expr_at = self.controller.calculate_expr_at

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
