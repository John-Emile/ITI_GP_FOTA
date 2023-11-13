## This Python file uses the following encoding: utf-8
#import sys
#import os
#from pathlib import Path
#from PySide6.QtGui import QGuiApplication
#from PySide6.QtQml import QQmlApplicationEngine


#if __name__ == "__main__":
#    os.environ["QT_IM_MODULE"] = "qtvirtualkeyboard"
#    app = QGuiApplication(sys.argv)
#    engine = QQmlApplicationEngine()

#    qml_file = Path(__file__).resolve().parent / "main.qml"
#    engine.load(qml_file)
#    if not engine.rootObjects():
#        sys.exit(-1)
#    sys.exit(app.exec())


import sys
import os

from PyQt5.QtCore import Qt, QUrl
from PyQt5.QtGui import QGuiApplication
from PyQt5.QtQml import QQmlApplicationEngine
from PyQt5.QtWidgets import QApplication
from Back_end import Backend
if __name__ == '__main__':
#    os.environ['QT_QPA_PLATFORM'] = 'eglfs'
#    os.environ['QT_QPA_PLATFORM'] = 'vnc'
    os.environ["QT_IM_MODULE"] = "qtvirtualkeyboard"
    app = QApplication(sys.argv)

    # Create the QML application engine
    engine = QQmlApplicationEngine()

    # Load the QML file
    engine.load(QUrl('main.qml'))
    backend = Backend()
    engine.rootContext().setContextProperty("Backend", backend)

    if not engine.rootObjects():
        sys.exit(-1)

    sys.exit(app.exec_())
