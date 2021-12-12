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

        Grid {
            id: topThreeGrid

            topPadding: 25;
            leftPadding: 15;

//            spacing: 5;

            columns: 4;
            rows: 4;

            columnSpacing: 15;
            rowSpacing: 10;

            RadioButton {
                id: beginnerRadio

                implicitWidth: 20
                implicitHeight: 20

                checked: true
                //text: qsTr("Beginner \t\t 9x9 \t\t 10 Mines")
                x: 15;

                indicator: Rectangle {
                    id: indicatorRect

                    anchors.fill: parent;

//                    implicitWidth: 20
//                    implicitHeight: 20
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
                width: 140;

                horizontalAlignment: Text.AlignLeft

                text: "Beginner";
            }

            TextLabel {
                width: 140;

                horizontalAlignment: Text.AlignLeft

                text: "9x9";
            }

            TextLabel {
                width: 100;

                horizontalAlignment: Text.AlignLeft

                text: "10 Mines";
            }

            RadioButton {
                id: intermediateRadio

                implicitWidth: 20
                implicitHeight: 20

//                text: qsTr("Intermediate \t 16x16 \t\t 40 Mines")
//                x: 15;

                indicator: Rectangle {
                    id: indicatorRect2

                    anchors.fill: parent;

//                    implicitWidth: 20
//                    implicitHeight: 20
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
                width: 140;

                horizontalAlignment: Text.AlignLeft

                text: "Intermediate";
            }

            TextLabel {
                width: 140;

                horizontalAlignment: Text.AlignLeft

                text: "16x16";
            }

            TextLabel {
                width: 100;

                horizontalAlignment: Text.AlignLeft

                text: "40 Mines";
            }

            RadioButton {
                id: expertRadio

                implicitWidth: 20
                implicitHeight: 20

//                text: qsTr("Intermediate \t 16x16 \t\t 40 Mines")
//                x: 15;

                indicator: Rectangle {
                    id: indicatorRect3

                    anchors.fill: parent;

//                    implicitWidth: 20
//                    implicitHeight: 20
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
                width: 140;

                horizontalAlignment: Text.AlignLeft

                text: "Expert";
            }

            TextLabel {
                width: 140;

                horizontalAlignment: Text.AlignLeft

                text: "30x16";
            }

            TextLabel {
                width: 100;

                horizontalAlignment: Text.AlignLeft

                text: "99 Mines";
            }

            RadioButton {
                id: customRadio

                implicitWidth: 20
                implicitHeight: 20

//                text: qsTr("Intermediate \t 16x16 \t\t 40 Mines")
//                x: 15;

                indicator: Rectangle {
                    id: indicatorRect4

                    anchors.fill: parent;

//                    implicitWidth: 20
//                    implicitHeight: 20
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
                width: 150;

                horizontalAlignment: Text.AlignLeft

                text: "Custom";
            }
        }

//        Column {
//            topPadding: 25;

//            RadioButton {
//                id: beginnerRadio2

//                checked: true
//                text: qsTr("Beginner \t\t 9x9 \t\t 10 Mines")
//                x: 15;

//                indicator: Rectangle {
//                    id: indicatorRect21

//                    implicitWidth: 20
//                    implicitHeight: 20
//                    radius: 13
//                    border.width: 1;
//                    border.color: "#595959";

//                    Rectangle {
//                        width: 10
//                        height: 10

//                        anchors.centerIn: parent;

//                        radius: 7
//                        color: "#595959";
//                        visible: beginnerRadio2.checked
//                    }
//                }

//                contentItem: Text {
//                    anchors.top: indicatorRect.top;
//                    leftPadding: beginnerRadio2.indicator.width + 10;

//                    font.pointSize: 12;

//                    text: beginnerRadio2.text
//                }

//                onClicked: {
//                    boardSize = "beginner";
//                }
//            }

//            RadioButton {
//                id: intermediateRadio2

//                text: qsTr("Intermediate \t 16x16 \t\t 40 Mines")
//                x: 15;

//                indicator: Rectangle {
//                    id: indicatorRect22

//                    implicitWidth: 20
//                    implicitHeight: 20
//                    radius: 13
//                    border.width: 1;
//                    border.color: "#595959";

//                    Rectangle {
//                        width: 10
//                        height: 10

//                        anchors.centerIn: parent;

//                        radius: 7
//                        color: "#595959";
//                        visible: intermediateRadio2.checked
//                    }
//                }

//                contentItem: Text {
//                    anchors.top: indicatorRect2.top;
//                    leftPadding: intermediateRadio2.indicator.width + 10;

//                    font.pointSize: 12

//                    text: intermediateRadio2.text;
//                }

//                onClicked: {
//                    boardSize = "intermediate";
//                }
//            }

//            RadioButton {
//                id: expertRadio2

//                text: qsTr("Expert \t\t 30x16 \t\t 99 Mines")
//                x: 15;

//                indicator: Rectangle {
//                    id: indicatorRect32

//                    implicitWidth: 20
//                    implicitHeight: 20
//                    radius: 13
//                    border.width: 1;
//                    border.color: "#595959";

//                    Rectangle {
//                        width: 10
//                        height: 10

//                        anchors.centerIn: parent;

//                        radius: 7
//                        color: "#595959";
//                        visible: expertRadio2.checked
//                    }
//                }

//                contentItem: Text {
//                    anchors.top: indicatorRect3.top;
//                    leftPadding: expertRadio2.indicator.width + 10;

//                    font.pointSize: 12

//                    text: expertRadio2.text
//                }

//                onClicked: {
//                    boardSize = "expert";
//                }
//            }

//            RadioButton {
//                id: customRadio2

//                text: qsTr("Custom")
//                x: 15;

//                indicator: Rectangle {
//                    id: indicatorRect42

//                    implicitWidth: 20
//                    implicitHeight: 20
//                    radius: 13
//                    border.width: 1;
//                    border.color: "#595959";

//                    Rectangle {
//                        width: 10
//                        height: 10

//                        anchors.centerIn: parent;

//                        radius: 7
//                        color: "#595959";
//                        visible: customRadio2.checked
//                    }
//                }

//                contentItem: Text {
//                    id: customRadioText

//                    anchors.top: indicatorRect4.top;
//                    leftPadding: customRadio2.indicator.width + 10;

//                    font.pointSize: 12

//                    text: customRadio2.text
//                }

//                onClicked: {
//                    boardSize = "custom";
//                }
//            }

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
//                height: widthLabel.height + 10;
                height: 30;
//                anchors.verticalCenter: widthLabel.verticalCenter

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

            TextLabel {
                id: heightLabel;

                height: 30;

                verticalAlignment: Text.AlignVCenter;

                text: "Height:";
            }

            InputBox {
                id: heightInput;

                width: 100;
//                height: heightLabel.height + 10;
                height: 30;
//                anchors.verticalCenter: heightLabel.verticalCenter

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

            TextLabel {
                id: minesLabel;

                height: 30;

                verticalAlignment: Text.AlignVCenter;

                text: "Mines:";
            }

            InputBox {
                id: minesInput;

                width: 100;
//                height: minesLabel.height + 10;
                height: 30;
//                anchors.verticalCenter: minesLabel.verticalCenter

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

//            Row {
//                id: widthRow;

//                leftPadding: 60;

//                spacing: 15;

//                TextLabel {
//                    id: widthLabel;

//                    text: "Width:";
//                }

//                InputBox {
//                    id: widthInput;

//                    width: 100;
//                    height: widthLabel.height + 10;
//                    anchors.verticalCenter: widthLabel.verticalCenter

//                    inputMethodHints: Qt.ImhDigitsOnly;

//                    placeholderText: gameModel.columns;

////                    enabled: customRadio.checked

//                    onFocusChanged: {
//                        if(focus) {
//                            customRadio.checked = true;
//                            boardSize = "custom";
//                        }
//                    }
//                }
//            }

//            Row {
//                id: heightRow;

//                topPadding: 5;
//                leftPadding: 60;

//                spacing: 10;

//                TextLabel {
//                    id: heightLabel;

//                    text: "Height:";
//                }

//                InputBox {
//                    id: heightInput;

//                    width: 100;
//                    height: heightLabel.height + 10;
//                    anchors.verticalCenter: heightLabel.verticalCenter

//                    inputMethodHints: Qt.ImhDigitsOnly;

//                    placeholderText: gameModel.rows;

////                    enabled: customRadio.checked

//                    onFocusChanged: {
//                        if(focus) {
//                            customRadio.checked = true;
//                            boardSize = "custom";
//                        }
//                    }
//                }
//            }

//            Row {
//                id: minesRow;

//                topPadding: 5;
//                leftPadding: 60;

//                spacing: 13;

//                TextLabel {
//                    id: minesLabel;

//                    text: "Mines:";
//                }

//                InputBox {
//                    id: minesInput;

//                    width: 100;
//                    height: minesLabel.height + 10;
//                    anchors.verticalCenter: minesLabel.verticalCenter

//                    inputMethodHints: Qt.ImhDigitsOnly;

//                    placeholderText: gameModel.mineCount;

////                    enabled: customRadio.checked

//                    onFocusChanged: {
//                        if(focus) {
//                            customRadio.checked = true;
//                            boardSize = "custom";
//                        }
//                    }
//                }
//            }

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

                parentWindow.minimumWidth = Math.max(gameModel.columns * Style.cellWidth * sizeFactor, 310 * sizeFactor) + 24;
                parentWindow.minimumHeight = gameModel.rows * Style.cellHeight * sizeFactor + statusBar.height + 36;

                parentWindow.maximumWidth = Math.max(gameModel.columns * Style.cellWidth * sizeFactor, 310 * sizeFactor) + 24;
                parentWindow.maximumHeight = gameModel.rows * Style.cellHeight * sizeFactor + statusBar.height + 36;

                parentWindow.width = Math.max(gameModel.columns * Style.cellWidth * sizeFactor, 310 * sizeFactor) + 24;
                parentWindow.height = gameModel.rows * Style.cellHeight * sizeFactor + statusBar.height + 36;
            }
        }
    }
}
