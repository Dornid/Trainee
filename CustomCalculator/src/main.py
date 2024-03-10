import sys
from PySide6.QtWidgets import QApplication
from View.mainwindow import MainWindow

if __name__ == "__main__":
    app = QApplication(sys.argv)
    calc_window = MainWindow()
    calc_window.show()
    app.exec()
