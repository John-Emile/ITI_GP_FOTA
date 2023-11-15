
import QtQuick 2.1
import QtQuick.Controls 2.1


Rectangle {
    id: rectangle
    width: Constants.width
    height: Constants.height
    color: "#55aaff"


    BusyIndicator {
        id: busyIndicator
        x: 450
        y: 188
        width: 120
        height: 108
    }
    
    Text {
        id: text1
        x: 465
        y: 109
        width: 93
        height: 41
        text: qsTr("Wait")
        font.pixelSize: 40
    }
    Dialog {
    id: dialog
    title: "no update"
    standardButtons: Dialog.Ok | Dialog.Cancel

    onAccepted: console.log("Ok clicked")
    onRejected: console.log("Cancel clicked") 
    }
    
    states: [
        State {
            name: "clicked"
            when: button.checked
        }
    ]
 Button {
        id: button1
        x: 129
        y: 400
        width: 260
        height: 134
        text: qsTr("Back")
        font.pointSize: 20
         onClicked: {
            stack.pop(login)
        }
 }
 
 Button {
        id: button2
        x: 629
        y: 400
        width: 260
        height: 134
        text: qsTr("Check Update")
        font.pointSize: 20
         onClicked: {
             var update_check = Backend.update()
           if (update_check == true)
           {
            stack.push(ask)
           }
           else
           {
           dialog.open()
           }
        }
 }
    //Timer {
      //  interval: 10
       // running: true
        //repeat: true

      //  onTriggered: {
       //    var update_check = Backend.update()
        //   if (update_check == true)
        //   {
         //   stack.push(ask)
          // }
        //}
    //}
    
}
