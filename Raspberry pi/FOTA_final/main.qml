import QtQuick 2.1
import QtQuick.Window 2.1
import QtQuick.Controls 2.1
import QtQuick.VirtualKeyboard 2.1
 ApplicationWindow {
   width: 1024
   height: 600
    
   
  visible: true
  title: qsTr("FOTA project")


Wait_screen{
    visible: false
    id: wait
}
Login_Screen{
visible: false
id :login
}
Screen01_copy{
visible: false
id: ask
}
Screen01_progress{
id: progress
    visible: false

}
StackView {
      id: stack
      initialItem: login
      anchors.fill: parent
  }
InputPanel {
            id: inputPanel
            z: 99
            x: 0
            y: parent.height
            width: parent.width

            states: State {
                name: "visible"
                when: inputPanel.active
                PropertyChanges {
                    target: inputPanel
                    y: parent.height - inputPanel.height
                }
            }
            transitions: Transition {
                from: ""
                to: "visible"
                reversible: true
                ParallelAnimation {
                    NumberAnimation {
                        properties: "y"
                        duration: 250
                        easing.type: Easing.InOutQuad
                    }
                }
            }

           }
//InputPanel {
//        id: inputPanel
//        visible: false
//        property bool showKeyboard :  active
//        y: parent.height/2
//        //y: showKeyboard ? parent.height - height : parent.height
//        Behavior on y {
//            NumberAnimation {
//                duration: 200
//                easing.type: Easing.InOutQuad
//            }
//        }
//        anchors.leftMargin: parent.width/10
//        anchors.rightMargin: parent.width/10
//        anchors.left: parent.left
//        anchors.right: parent.right
//    }


//   function nader()
//   {
//       console.log("U are signed")

//   }
//    Button {
//       id: ok
//        text: "Ok"
//        onClicked: {
//             console.log("U are signed")
//            console.log(idfield.text)
//        }



////        anchors.top: parent.top
////        anchors.topMargin: 250
////        anchors.left: parent.left
////        anchors.leftMargin: 200
//        x: 250
//        y: 250

//    }
//    Button {
//         anchors.top: parent.top
//        anchors.right: parent.right
//        text: "Cancel"
//        onClicked: model.revert()
//        anchors.rightMargin: 100

//        anchors.topMargin: 250


//    }

//    TextField {
//        id: idfield
//        placeholderText: qsTr("Enter Username")
//        x: 100
//        y: 100
//    }
//    TextField {
//        id : passfield
//        placeholderText: qsTr("Enter Password")
//        x: 150
//        y: 150
//    }

//
}





