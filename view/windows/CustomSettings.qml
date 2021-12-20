import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15

import "qrc:/text"
import "qrc:/includes"

Window {
    id: customSettings

    property string boardSize;

    property var parentWindow;

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

        MouseArea {
            id: maBeginner;

            width: 430;
            height: beginnerLabel.height;

            x: beginnerRadio.x
            y: beginnerLabel.y
            z: 90;

            onClicked: {
                if(!beginnerRadio.checked) {
                    beginnerRadio.toggle();
                    beginnerRadio.onClicked();
                    beginnerRadio.forceActiveFocus();
                }
            }
        }

        MouseArea {
            id: maIntermediate;

            width: 430;
            height: intermediateLabel.height;

            x: intermediateRadio.x
            y: intermediateLabel.y
            z: 90;

            onClicked: {
                if(!intermediateRadio.checked) {
                    intermediateRadio.toggle();
                    intermediateRadio.onClicked();
                    intermediateRadio.forceActiveFocus();
                }
            }
        }

        MouseArea {
            id: maExpert;

            width: 430;
            height: expertLabel.height;

            x: expertRadio.x
            y: expertLabel.y
            z: 90;

            onClicked: {
                if(!expertRadio.checked) {
                    expertRadio.toggle();
                    expertRadio.onClicked();
                    expertRadio.forceActiveFocus();
                }
            }
        }

        MouseArea {
            id: maCustom;

            width: 110;
            height: customLabel.height;

            x: customRadio.x
            y: customLabel.y
            z: 90;

            onClicked: {
                if(!customRadio.checked) {
                    customRadio.toggle();
                    customRadio.onClicked();
                    customRadio.forceActiveFocus();
                }
            }
        }

        Grid {
            id: topThreeGrid

            topPadding: 25;
            leftPadding: 15;

            columns: 4;
            rows: 4;

            columnSpacing: 15;
            rowSpacing: 10;

            RadioButton {
                id: beginnerRadio

                implicitWidth: 20
                implicitHeight: 20

                checked: true
                x: 15;

                indicator: Rectangle {
                    id: indicatorRect

                    anchors.fill: parent;

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

                onClicked: {
                    boardSize = "beginner";
                }
            }

            TextLabel {
                id: beginnerLabel;

                width: 140;

                horizontalAlignment: Text.AlignLeft

                text: "Beginner";
            }

            TextLabel {
                id: beginnerSizeLabel;

                width: 140;

                horizontalAlignment: Text.AlignLeft

                text: "9x9";
            }

            TextLabel {
                id: beginnerMinesLabel;

                width: 100;

                horizontalAlignment: Text.AlignLeft

                text: "10 Mines";
            }

            RadioButton {
                id: intermediateRadio

                implicitWidth: 20
                implicitHeight: 20

                indicator: Rectangle {
                    id: indicatorRect2

                    anchors.fill: parent;

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

                onClicked: {
                    boardSize = "intermediate";
                }
            }

            TextLabel {
                id: intermediateLabel

                width: 140;

                horizontalAlignment: Text.AlignLeft

                text: "Intermediate";
            }

            TextLabel {
                id: intermediateSizeLabel

                width: 140;

                horizontalAlignment: Text.AlignLeft

                text: "16x16";
            }

            TextLabel {
                id: intermediateMinesLabel

                width: 100;

                horizontalAlignment: Text.AlignLeft

                text: "40 Mines";
            }

            RadioButton {
                id: expertRadio

                implicitWidth: 20
                implicitHeight: 20

                indicator: Rectangle {
                    id: indicatorRect3

                    anchors.fill: parent;

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

                onClicked: {
                    boardSize = "expert";
                }
            }

            TextLabel {
                id: expertLabel

                width: 140;

                horizontalAlignment: Text.AlignLeft

                text: "Expert";
            }

            TextLabel {
                id: expertSizeLabel

                width: 140;

                horizontalAlignment: Text.AlignLeft

                text: "30x16";
            }

            TextLabel {
                id: expertMinesLabel

                width: 100;

                horizontalAlignment: Text.AlignLeft

                text: "99 Mines";
            }

            RadioButton {
                id: customRadio

                implicitWidth: 20
                implicitHeight: 20

                indicator: Rectangle {
                    id: indicatorRect4

                    anchors.fill: parent;

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

                onClicked: {
                    boardSize = "custom";
                }
            }

            TextLabel {
                id: customLabel;

                width: 150;

                horizontalAlignment: Text.AlignLeft

                text: "Custom";
            }
        }

        Grid {
            leftPadding: 60;

            columnSpacing: 10;
            rowSpacing: 5;

            anchors.top: topThreeGrid.bottom;

            columns: 2
            rows: 3;

            TextLabel {
                id: widthLabel;

                height: 30;

                verticalAlignment: Text.AlignVCenter;

                text: "Width:";
            }

            InputBox {
                id: widthInput;

                width: 100;
                height: 30;

                placeholderText: gameModel.columns;

                validator: IntValidator { bottom: 1 }

                onFocusChanged: {
                    if(focus) {
                        customRadio.checked = true;
                        boardSize = "custom";
                    }
                }
            }

            TextLabel {
                id: heightLabel;

                height: 30;

                verticalAlignment: Text.AlignVCenter;

                text: "Height:";
            }

            InputBox {
                id: heightInput;

                width: 100;
                height: 30;

                placeholderText: gameModel.rows;

                validator: IntValidator { bottom: 1 }

                onFocusChanged: {
                    if(focus) {
                        customRadio.checked = true;
                        boardSize = "custom";
                    }
                }
            }

            TextLabel {
                id: minesLabel;

                height: 30;

                verticalAlignment: Text.AlignVCenter;

                text: "Mines:";
            }

            InputBox {
                id: minesInput;

                width: 100;
                height: 30;

                validator: IntValidator { bottom: 0 }

                placeholderText: gameModel.mineCount;

                onFocusChanged: {
                    if(focus) {
                        customRadio.checked = true;
                        boardSize = "custom";
                    }
                }
            }
        }

        Button {
            id: applyButton

            anchors.right: cancelButton.left;
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

                parentWindow.minimumWidth = Math.max(gameModel.columns * Style.cellWidth * sizeFactor, 340 * sizeFactor) + 24;
                parentWindow.minimumHeight = Math.max(gameModel.rows, 9) * Style.cellHeight * sizeFactor + statusBar.height + 36;

                parentWindow.maximumWidth = Math.max(gameModel.columns * Style.cellWidth * sizeFactor, 340 * sizeFactor) + 24;
                parentWindow.maximumHeight = Math.max(gameModel.rows, 9) * Style.cellHeight * sizeFactor + statusBar.height + 36;

                parentWindow.width = Math.max(gameModel.columns * Style.cellWidth * sizeFactor, 340 * sizeFactor) + 24;
                parentWindow.height = Math.max(gameModel.rows, 9) * Style.cellHeight * sizeFactor + statusBar.height + 36;

                isGameWon = false;
                hideWinScreen = false;

                customSettings.close();
            }
        }

        Button {
            id: cancelButton

            anchors.right: screenBorder.right;
            anchors.bottom: screenBorder.bottom;

            anchors.rightMargin: 10
            anchors.bottomMargin: 10;

            width: 100;
            height: 30;

            text: "Cancel";

            background: Rectangle {
                anchors.fill: parent;

                color: "#f5f5f5";
            }

            onClicked: {
                customSettings.close();
            }
        }
    }
}
