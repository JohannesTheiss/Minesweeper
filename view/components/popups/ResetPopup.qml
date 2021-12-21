import QtQuick 2.15
import QtQuick.Controls 2.15

import "qrc:/text"
import "qrc:/includes"

/* @parameters
 * id: identifier for ResetPopup                                                                                        (e.g. id: resetPopup;)
 * passedScrollview: the scrollview in Statistics window, used to disable the scrollview while ResetPopup is visible    (e.g. passedScrollview: scrollview;)
 * passedButton: the button that opens ResetPopup, used to disable the scrollview while ResetPopup is visible           (e.g. passedButton: resetButton;)
 */
Rectangle {
    id: resetPopup;

    property var passedScrollview;
    property var passedButton;

    anchors.centerIn: parent;
    z: 90;

    width: 400;
    height: 150;

    border.width: Style.borderWidth;
    border.color: Style.popupBorder;
    color: Style.popupBackground;

    visible: false;

    TextLabel {
        anchors.centerIn: parent;

        horizontalAlignment: Text.AlignHCenter;

        text: "You are about to delete all saved statistics.\nAre you sure?";
    }

    Button {
        id: acceptButton

        anchors.right: cancelButton.left;
        anchors.bottom: parent.bottom;

        anchors.rightMargin: 10
        anchors.bottomMargin: 10;

        width: Style.standardButtonWidth;
        height: Style.standardButtonHeight;

        text: "Accept";

        background: Rectangle {
            anchors.fill: parent;

            color: Style.standardButtonBackground;
        }

        onClicked: {
            resetPopup.visible = false;
            passedScrollview.enabled = true;
            passedButton.enabled = true;

            statisticsController.resetStatistics();
        }
    }

    Button {
        id: cancelButton

        anchors.right: parent.right;
        anchors.bottom: parent.bottom;

        anchors.rightMargin: 10
        anchors.bottomMargin: 10;

        width: Style.standardButtonWidth;
        height: Style.standardButtonHeight;

        text: "Cancel";

        background: Rectangle {
            anchors.fill: parent;

            color: Style.standardButtonBackground;
        }

        onClicked: {
            resetPopup.visible = false;
            passedScrollview.enabled = true;
            passedButton.enabled = true;
        }
    }
}
