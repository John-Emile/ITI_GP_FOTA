

/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/
import QtQuick 2.1
import QtQuick.Controls 2.1
//import Logintest

Rectangle {
    id: rectangle
    width: parent.width
    height: parent.height
    color: "#55aaff"
    border.width: 8
    scale: 1

    Text {
        id: text1
        x: 52
        y: 134
        width: 1362
        height: 122
        text: qsTr("Your software is being downloaded")
        font.pixelSize: 60
    }

    ProgressBar {
        id: progressBar
        x: 104
        y: 289
        width: 835
        height: 202
        focusPolicy: Qt.WheelFocus
       // value: Backend.get_progress()
    }
     Button {
        id: button1
        x: 129
        y: 400
        width: 260
        height: 134
        text: qsTr("back")
        font.pointSize: 20
         onClicked: {
            stack.pop(ask)
        }
     }
    states: [
        State {
            name: "clicked"
        }
    ]
}