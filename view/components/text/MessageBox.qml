import QtQuick 2.15

import "qrc:/text"
import "qrc:/includes"

/* @parameters
 * id: identifier for messageBox            (e.g. id: messageBox;)
 * width: width of the messageBox           (e.g. width: 100;)
 * height: height of the messageBox         (e.g. width: 60;)
 */
Rectangle {
    id: messageBox;
    y: -height;                                                                                         //the messageBox is positioned just outside the visible window
    z: 99;                                                                                              //the messageBox should not be covered by anything

    anchors.right: parent.right;

    color: Style.messageBoxBackground;
    radius: Style.borderRadius;
    border.width: Style.borderWidth * 2;
    border.color: "black";

    opacity: 0;

    state: "fadeOut";                                                                                   //start state fadeOut

    states: [
        State {
            name: "fadeIn";
            AnchorChanges { target: messageBox; anchors.top: parent.top }                               //place messageBox in the top right corner
        },
        State {
            name: "fadeOut";
            AnchorChanges { target: messageBox; anchors.bottom: parent.top }                            //place messageBox in the top right, but outside the visible area
        }
    ]

    transitions: [
        Transition {                                                                                    //fade in transition
            from: "fadeOut";
            to: "fadeIn";
            AnchorAnimation { duration: 500 }
            PropertyAnimation { target: messageBox; property: "opacity"; to: 1; duration: 600 }
        },
        Transition {                                                                                    //fade out transition
            from: "fadeIn";
            to: "fadeOut";
            AnchorAnimation { duration: 500 }
            PropertyAnimation { target: messageBox; property: "opacity"; to: 0; duration: 600}
        }
    ]

    MouseArea {                                                                                         //used to stop the messageBox from fading out, when mouseArea is hovered
        id: ma;

        anchors.fill: parent;
        hoverEnabled: true;

        onExited: timer.restart;                                                                        //restart timer when the mouseArea is exited

        TextLabel {
            id: content;

            anchors.fill: parent;

            text: "Dieser Song ist nicht verfügbar.";                                                   //default placeholder text
            color: "black";
            font.pointSize: 10;
            horizontalAlignment: TextInput.AlignHCenter;
        }

        Timer {
            id: timer;

            interval: 6500;
            running: !ma.containsMouse;                                                                 //timer should only run if the mouseArea is not hovered
            onTriggered: {
                messageBox.state = "fadeOut";
            }
        }

        Connections {                                                                                   //show MessageBox when a corrupt song is deleted
            target: backend;
            function onUserMessage(message) {
                content.text = message.message;
                messageBox.state = "fadeIn";
                timer.restart();
            }
        }
    }
}
