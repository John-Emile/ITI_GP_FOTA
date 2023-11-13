

/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/
import QtQuick 2.1
import QtQuick.Controls 2.1


Rectangle {
    id: rectangle
    width: parent.width
    height: parent.height
    //anchors.fill:parent
    color: "#55aaff"

    Text {
        id: label
        y: 44
        width: 566
        height: 102
        text: qsTr("Login to your account")
        font.pointSize: 25
        anchors.horizontalCenterOffset: 49
        font.family: parent.font.family
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

    TextEdit {
        id: userpass
        x: 291
        y: 281
        width: 424
        height: 99
        text: qsTr("Enter your password")
        font.pixelSize: 40
    }

    TextInput {
        id: userid
        x: 278
        y: 175
        width: 389
        height: 100
        text: qsTr("Enter ur ID")
        font.pixelSize: 40
    }


    Image {
        id: image
        x: 786
        y: 100
        width: 177
        height: 113
        source: "login.png"
        fillMode: Image.PreserveAspectFit
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
  Dialog {
    id: dialog
    title: "Unathurized user"
    standardButtons: Dialog.Ok | Dialog.Cancel

    onAccepted: console.log("Ok clicked")
    onRejected: console.log("Cancel clicked")
}
    Button {
    
        id: button
        x: 210
        y: 434
        width: 548
        height: 109
        text: qsTr("Enter")
        icon.cache: false
        font.pointSize: 20
         onClicked: {
            
           Backend.say_hello()
           console.log(userid.text)
           console.log(userpass.text)
           let auth = Backend.authen(userid.text, userpass.text)
           if (auth == true) {
            stack.push(wait)
           }
           else
           {
           dialog.open()
          }
        }
    }
}
