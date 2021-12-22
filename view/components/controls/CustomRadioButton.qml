import QtQuick 2.15
import QtQuick.Controls 2.15

import "qrc:/includes"

/* @parameters
 * id: identifier for CustomRadioButton                                             (e.g. id: beginnerRadio;)
 * onClicked: { } code that should be run, when CustomRadioButton is clicked        (e.g. onClicked: { boardSize = "beginner"; })
 */
RadioButton {
    id: radioButton

    implicitWidth: 20
    implicitHeight: 20

    x: 15;

    indicator: Rectangle {
        id: indicatorRect

        anchors.fill: parent;

        radius: 13
        border.width: Style.borderWidth;
        border.color: Style.radioButton;

        Rectangle {
            width: 10
            height: 10

            anchors.centerIn: parent;

            radius: 7
            color: Style.radioButton;
            visible: radioButton.checked
        }
    }
}
