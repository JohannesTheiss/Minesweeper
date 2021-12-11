import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15

import "qrc:/text"
import "qrc:/includes"

Window {
    id: customSettings

    property string boardSize;

    modality: Qt.WindowModal;

    title: "Minesweeper - Custom Settings";

    width: 500;
    height: 350;

    minimumWidth: 500;
    minimumHeight: 350;

    maximumWidth: 500;
    maximumHeight: 350;

    visible: true;

    color: "#c0c0c0";

    Component.onCompleted: {
        if (gameModel.columns === 9 && gameModel.rows === 9 && gameModel.mineCount === 10) {
            beginnerRadio.checked = true;
            boardSize = "beginner";
        }
        else if (gameModel.columns === 16 && gameModel.rows === 16 && gameModel.mineCount === 40) {
            intermediateRadio.checked = true;
            boardSize = "intermediate";
        }
        else if (gameModel.columns === 30 && gameModel.rows === 16 && gameModel.mineCount === 99) {
            expertRadio.checked = true;
            boardSize = "expert";
        }
        else {
            customRadio.checked = true;
            boardSize = "custom";
        }
    }

    Rectangle {
        id: screenBorder

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
            topPadding: 25;

            RadioButton {
                id: beginnerRadio

                checked: true
                text: qsTr("Beginner \t\t 9x9 \t\t 10 Mines")
                x: 15;

                indicator: Rectangle {
                    id: indicatorRect

                    implicitWidth: 20
                    implicitHeight: 20
                    radius: 13
                    border.width: 1;
                    border.color: "#595959";

                    Rectangle {
                        width: 10
                        height: 10

                        anchors.centerIn: parent;

                        radius: 7
                        color: "#595959";
                        visible: beginnerRadio.checked
                    }
                }

                contentItem: Text {
                    anchors.top: indicatorRect.top;
                    leftPadding: beginnerRadio.indicator.width + 10;

                    font.pointSize: 12;

                    text: beginnerRadio.text
                }

                onClicked: {
                    boardSize = "beginner";
                }
            }

            RadioButton {
                id: intermediateRadio

                text: qsTr("Intermediate \t 16x16 \t\t 40 Mines")
                x: 15;

                indicator: Rectangle {
                    id: indicatorRect2

                    implicitWidth: 20
                    implicitHeight: 20
                    radius: 13
                    border.width: 1;
                    border.color: "#595959";

                    Rectangle {
                        width: 10
                        height: 10

                        anchors.centerIn: parent;

                        radius: 7
                        color: "#595959";
                        visible: intermediateRadio.checked
                    }
                }

                contentItem: Text {
                    anchors.top: indicatorRect2.top;
                    leftPadding: intermediateRadio.indicator.width + 10;

                    font.pointSize: 12

                    text: intermediateRadio.text;
                }

                onClicked: {
                    boardSize = "intermediate";
                }
            }

            RadioButton {
                id: expertRadio

                text: qsTr("Expert \t\t 30x16 \t\t 99 Mines")
                x: 15;

                indicator: Rectangle {
                    id: indicatorRect3

                    implicitWidth: 20
                    implicitHeight: 20
                    radius: 13
                    border.width: 1;
                    border.color: "#595959";

                    Rectangle {
                        width: 10
                        height: 10

                        anchors.centerIn: parent;

                        radius: 7
                        color: "#595959";
                        visible: expertRadio.checked
                    }
                }

                contentItem: Text {
                    anchors.top: indicatorRect3.top;
                    leftPadding: expertRadio.indicator.width + 10;

                    font.pointSize: 12

                    text: expertRadio.text
                }

                onClicked: {
                    boardSize = "expert";
                }
            }

            RadioButton {
                id: customRadio

                text: qsTr("Custom")
                x: 15;

                indicator: Rectangle {
                    id: indicatorRect4

                    implicitWidth: 20
                    implicitHeight: 20
                    radius: 13
                    border.width: 1;
                    border.color: "#595959";

                    Rectangle {
                        width: 10
                        height: 10

                        anchors.centerIn: parent;

                        radius: 7
                        color: "#595959";
                        visible: customRadio.checked
                    }
                }

                contentItem: Text {
                    id: customRadioText

                    anchors.top: indicatorRect4.top;
                    leftPadding: customRadio.indicator.width + 10;

                    font.pointSize: 12

                    text: customRadio.text
                }

                onClicked: {
                    boardSize = "custom";
                }
            }

            Row {
                id: widthRow;

                leftPadding: 60;

                spacing: 15;

                TextLabel {
                    id: widthLabel;

                    text: "Width:";
                }

                InputBox {
                    id: widthInput;

                    width: 100;
                    height: widthLabel.height + 10;
                    anchors.verticalCenter: widthLabel.verticalCenter

                    inputMethodHints: Qt.ImhDigitsOnly;

                    placeholderText: gameModel.columns;

//                    enabled: customRadio.checked

                    onFocusChanged: {
                        if(focus) {
                            customRadio.checked = true;
                            boardSize = "custom";
                        }
                    }
                }
            }

            Row {
                id: heightRow;

                topPadding: 5;
                leftPadding: 60;

                spacing: 10;

                TextLabel {
                    id: heightLabel;

                    text: "Height:";
                }

                InputBox {
                    id: heightInput;

                    width: 100;
                    height: heightLabel.height + 10;
                    anchors.verticalCenter: heightLabel.verticalCenter

                    inputMethodHints: Qt.ImhDigitsOnly;

                    placeholderText: gameModel.rows;

//                    enabled: customRadio.checked

                    onFocusChanged: {
                        if(focus) {
                            customRadio.checked = true;
                            boardSize = "custom";
                        }
                    }
                }
            }

            Row {
                id: minesRow;

                topPadding: 5;
                leftPadding: 60;

                spacing: 13;

                TextLabel {
                    id: minesLabel;

                    text: "Mines:";
                }

                InputBox {
                    id: minesInput;

                    width: 100;
                    height: minesLabel.height + 10;
                    anchors.verticalCenter: minesLabel.verticalCenter

                    inputMethodHints: Qt.ImhDigitsOnly;

                    placeholderText: gameModel.mineCount;

//                    enabled: customRadio.checked

                    onFocusChanged: {
                        if(focus) {
                            customRadio.checked = true;
                            boardSize = "custom";
                        }
                    }
                }
            }
        }

        Button {
            id: okButton

            anchors.right: screenBorder.right;
            anchors.bottom: screenBorder.bottom;

            anchors.rightMargin: 10
            anchors.bottomMargin: 10;

            width: 100;
            height: 30;

            text: "Apply";

            background: Rectangle {
                anchors.fill: parent;

                color: "#f5f5f5";
            }

            onClicked: {
                switch (boardSize)
                {
                    case "beginner":
                        gameController.setGameMode(9, 9, 10);
                        break;

                    case "intermediate":
                        gameController.setGameMode(16, 16, 40);
                        break;

                    case "expert":
                        gameController.setGameMode(16, 30, 99);
                        break;

                    case "custom":
                        gameController.setGameMode(heightInput.text != "" ? +heightInput.text : +heightInput.placeholderText,
                                                   widthInput.text != "" ? +widthInput.text : +widthInput.placeholderText,
                                                   minesInput.text != "" ? +minesInput.text : +minesInput.placeholderText);
                        break;
                }

                mainWindow.minimumWidth = Math.max(gameModel.columns * Style.cellWidth * sizeFactor, 310 * sizeFactor) + 24;
                mainWindow.minimumHeight = gameModel.rows * Style.cellHeight * sizeFactor + statusBar.height + 36;

                mainWindow.maximumWidth = Math.max(gameModel.columns * Style.cellWidth * sizeFactor, 310 * sizeFactor) + 24;
                mainWindow.maximumHeight = gameModel.rows * Style.cellHeight * sizeFactor + statusBar.height + 36;

                mainWindow.width = Math.max(gameModel.columns * Style.cellWidth * sizeFactor, 310 * sizeFactor) + 24;
                mainWindow.height = gameModel.rows * Style.cellHeight * sizeFactor + statusBar.height + 36;
            }
        }
    }
}
