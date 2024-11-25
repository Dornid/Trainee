import sys
from PySide6.QtWidgets import QApplication
from Controller.user_controller import UserController
from Model.main_model import SmartCalcModel
from View.main_window import MainWindow

if __name__ == "__main__":
    app = QApplication(sys.argv)
    calc_window = MainWindow(UserController(SmartCalcModel()))
    calc_window.show()
    app.exec()
