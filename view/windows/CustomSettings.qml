import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15

import "qrc:/controls"
import "qrc:/includes"
import "qrc:/text"

import "qrc:/scripts/Manager.js" as Manager

Window {
    id: customSettings

    property string difficulty;

    property var parentWindow;
    property var parentStatusBar;

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
            difficulty = "beginner";
        }
        else if (gameModel.columns === 16 && gameModel.rows === 16 && gameModel.mineCount === 40) {
            intermediateRadio.checked = true;
            difficulty = "intermediate";
        }
        else if (gameModel.columns === 30 && gameModel.rows === 16 && gameModel.mineCount === 99) {
            expertRadio.checked = true;
            difficulty = "expert";
        }
        else {
            customRadio.checked = true;
            difficulty = "custom";
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

        //CustomMouseAreas are used to be able to click the whole row next to a RadioButton to check this RadioButton
        CustomMouseArea {
            id: maBeginner;

            radioButton: beginnerRadio;
        }

        CustomMouseArea {
            id: maIntermediate;

            radioButton: intermediateRadio;
        }

        CustomMouseArea {
            id: maExpert;

            radioButton: expertRadio;
        }

        CustomMouseArea {
            id: maCustom;

            width: 110;
            radioButton: customRadio;
        }

        Grid {
            id: topThreeGrid

            topPadding: 25;
            leftPadding: 15;

            columns: 4;
            rows: 4;

            columnSpacing: 15;
            rowSpacing: 10;

            CustomRadioButton {
                id: beginnerRadio;

                onClicked: {
                    difficulty = "beginner";
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

            CustomRadioButton {
                id: intermediateRadio;

                onClicked: {
                    difficulty = "intermediate";
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

            CustomRadioButton {
                id: expertRadio;

                onClicked: {
                    difficulty = "expert";
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

            CustomRadioButton {
                id: customRadio;

                onClicked: {
                    difficulty = "custom";
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
            id: customGrid;

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

                validator: IntValidator { bottom: 0 }

                onFocusChanged: {
                    if(focus) {
                        customRadio.checked = true;
                        difficulty = "custom";
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

                validator: IntValidator { bottom: 0 }

                onFocusChanged: {
                    if(focus) {
                        customRadio.checked = true;
                        difficulty = "custom";
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
                        difficulty = "custom";
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
                switch (difficulty)
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

                Manager.resizeWindow(parentWindow, parentStatusBar);
                Manager.resetForNewGame(mainWindow);

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
