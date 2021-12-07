import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15

import "qrc:/text"

Window {
    id: customSettings

    title: "Minesweeper - Custom Settings";

    width: 400;
    height: 400;

    color: "#c0c0c0";

    Rectangle {
        width: customSettings.width - 40;
        height: customSettings.height - 40;

        x: 20;
        y: 20;

        border.width: 1;
        border.color: "#595959";

        color: "#c0c0c0";

        TextBox {
            id: headerLabel;

            x: 10;
            y: - height / 2;

            text: "Difficulty Level";
        }

        Column {
            RadioButton {
                checked: true
                text: qsTr("Beginner \n 9x9 \n 10 Mines")

                indicator: Rectangle {
                        implicitWidth: 26
                        implicitHeight: 26
                        x: control.leftPadding
                        y: parent.height / 2 - height / 2
                        radius: 13
                        border.color: control.down ? "#17a81a" : "#21be2b"

                        Rectangle {
                            width: 14
                            height: 14
                            x: 6
                            y: 6
                            radius: 7
                            color: control.down ? "#17a81a" : "#21be2b"
                            visible: control.checked
                        }
                    }

                    contentItem: Text {
                        text: control.text
                        font: control.font
                        opacity: enabled ? 1.0 : 0.3
                        color: control.down ? "#17a81a" : "#21be2b"
                        verticalAlignment: Text.AlignVCenter
                        leftPadding: control.indicator.width + control.spacing
                    }
            }

            RadioButton {
                text: qsTr("Intermediate")
            }

            RadioButton {
                text: qsTr("Expert")
            }

            RadioButton {
                text: qsTr("Custom")
            }
        }
    }
}
