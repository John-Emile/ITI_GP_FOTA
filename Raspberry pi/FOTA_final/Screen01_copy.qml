

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

    Text {
        id: label
        y: 39
        width: 566
        height: 102
        text: qsTr("Welcome ")
        font.pointSize: 35
        anchors.horizontalCenterOffset: -106
        font.family: Constants.font.family
        anchors.topMargin: -154
        anchors.horizontalCenter: parent.horizontalCenter

        SequentialAnimation {
            id: animation

            ColorAnimation {
                id: colorAnimation1
                target: rectangle
                property: "color"
                to: "#2294c6"
                from: parent.backgroundColor
            }

            ColorAnimation {
                id: colorAnimation2
                target: rectangle
                property: "color"
                to: parent.backgroundColor
                from: "#2294c6"
            }
        }
    }

    Button {
        id: button
        x: 423
        y: 216
        width: 260
        height: 134
        text: qsTr("NO")
        font.pointSize: 60
         onClicked: {
            Backend.Clean_updates()
            stack.pop(wait) 
        }
    }

    Text {
        id: text1
        x: 18
        y: 136
        width: 645
        height: 122
        text: qsTr("There is a new software Update do you want to download it ")
        font.pixelSize: 27
    }

    Button {
        id: button1
        x: 129
        y: 216
        width: 260
        height: 134
        text: qsTr("YES")
        font.pointSize: 60
         onClicked: {
            Backend.Decryption("/home/Neshwy/FOTA_final/Data_update/Encrypted_File.txt")
            Backend.send_Uart("update.txt")
            stack.pop(wait)
            
        }


    }
    states: [
        State {
            name: "clicked"

            PropertyChanges {
                target: label
                text: qsTr("Button Checked")
            }
        }
    ]
}
