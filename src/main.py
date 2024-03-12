import sys
from PySide6.QtWidgets import QApplication
from View.main_window import MainWindow

if __name__ == "__main__":
    app = QApplication(sys.argv)
    calc_window = MainWindow()
    calc_window.show()
    app.exec()
