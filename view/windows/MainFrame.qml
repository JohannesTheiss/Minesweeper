import QtQuick 2.15
import QtQuick.Controls 2.5
import QtQml.Models 2.15
import QtQuick.Window 2.15

import Qt.labs.platform 1.1

// import SizeScaling enum
import Backend.Game 1.0

import "qrc:/controls"
import "qrc:/includes"
import "qrc:/popups"
import "qrc:/text"

import "qrc:/scripts/Adapter.js" as Adapter
import "qrc:/scripts/Manager.js" as Manager

ApplicationWindow {
    id: mainWindow;

    property double sizeFactor: 1.0;

    property bool hideWinPopup: false;

    property bool isGameWon: false;
    property int bestTimeForGameMode: 0;

    Component.onCompleted: {
        // check if new size scaling is set (from backend side)
        Manager.updateSizeScaling(mainWindow, statusBar);
    }

    Connections {
        target: statisticsController;
        function onGameEnded(bestTime, won) {
            console.log("game won: " + won);
            isGameWon = won;
            bestTimeForGameMode = bestTime
        }
    }

    MinesweeperMenuBar {
        id: menuBar;

        parentWindow: mainWindow;
        passedStatusBar: statusBar;
    }

    title: "Minesweeper";
    visible: true;

    color: "#c0c0c0";

    Rectangle {
        id: statusBar;

        width: Math.max(board.width, 340 * sizeFactor);
        height: Style.defaultHeight * sizeFactor;

        anchors.horizontalCenter: parent.horizontalCenter;

        y: 12;

        color: "#c0c0c0";

        TextLabel {
            id: flagsLabel;

            x: 10;

            anchors.verticalCenter: statusBar.verticalCenter;
            verticalAlignment: Text.AlignVCenter;

            font.pointSize: Style.largeFontSize * sizeFactor;
            font.family: "Consolas";
            color: +text < 0 ? "red" : "blue";

            text: Adapter.flagsToString(gameModel.flagCount);
        }

        Image {
            id: flagImage;

            x: flagsLabel.x + flagsLabel.width + 2;

            anchors.verticalCenter: statusBar.verticalCenter;

            width: 16 * sizeFactor
            height: 16 * sizeFactor

            source: "qrc:/images/flagTransparent.png";
        }

        ImageButton {
            id: newButton;

            width: 60 * sizeFactor;
            height: 30 * sizeFactor;

            x: pausePlayButton.x - width - 10;

            anchors.verticalCenter: parent.verticalCenter

            buttonImage: "qrc:/images/newButton.png";

            MouseArea {
                id: maNewButton;

                hoverEnabled: true;

                anchors.fill: parent;
                z: 3;

                onContainsPressChanged: {
                    if(containsPress) {
                        newButton.buttonImage = "qrc:/images/newButtonPressed.png";
                    }
                    else {
                        newButton.buttonImage = "qrc:/images/newButton.png";
                    }
                }

                onClicked: {
                    newButton.onClicked();
                }
            }

            onClicked: {
                gameController.initGame();

                if (board.visible === false) {
                    board.visible = true;
                    pausePlayButton.buttonImage = "qrc:/images/pauseButton.png";
                    pauseText.visible = false;
                }

                hideWinPopup = isGameWon = false;
            }
        }

        ImageButton {
            id: pausePlayButton;

            width: 30 * sizeFactor;
            height: 30 * sizeFactor;

            anchors.centerIn: parent;

            buttonImage: "qrc:/images/pauseButton.png";

            onClicked: {
                gameController.togglePauseGame();

                if (buttonImage.toString() === "qrc:/images/pauseButton.png") {
                    buttonImage = "qrc:/images/playButtonPressed.png";
                    pauseText.visible = true;
                    board.visible = false;
                }else {
                    buttonImage = "qrc:/images/pauseButton.png";
                    pauseText.visible = false;
                    board.visible = true;
                }
            }
        }

        ImageButton {
            id: endButton;

            width: 60 * sizeFactor;
            height: 30 * sizeFactor;

            x: pausePlayButton.x + pausePlayButton.width + 10;

            anchors.verticalCenter: parent.verticalCenter

            buttonImage: "qrc:/images/endButton.png";

            MouseArea {
                id: maEndButton;

                hoverEnabled: true;

                anchors.fill: parent;
                z: 3;

                onContainsPressChanged: {
                    if(containsPress) {
                        endButton.buttonImage = "qrc:/images/endButtonPressed.png";
                    }
                    else {
                        endButton.buttonImage = "qrc:/images/endButton.png";
                    }
                }

                onClicked: {
                    endButton.onClicked();
                }
            }

            onClicked: {
                gameController.endGame(false);
                gameController.revealAllCells();

                if (board.visible === false) {
                    board.visible = true;
                    pausePlayButton.buttonImage = "qrc:/images/pauseButton.png";
                    pauseText.visible = false;
                }
            }
        }

        Image {
            id: timeImage;

            width: 16 * sizeFactor;
            height: 16 * sizeFactor;

            x: timeLabel.x - width - 2;
            anchors.verticalCenter: statusBar.verticalCenter;

            source: "qrc:/images/timerTransparent.png";
        }

        TextLabel {
            id: timeLabel;

            x: statusBar.width - width - 10;

            anchors.verticalCenter: statusBar.verticalCenter;
            verticalAlignment: Text.AlignVCenter;

            font.pointSize: Style.largeFontSize * sizeFactor;
            font.family: "Consolas";
            color: "blue";

            text: Adapter.getMinutesFromSeconds(Math.min(gameModel.timePlayed, 5999));
        }
    }

    //unten
    Rectangle {
        id: statusBottomBorder;

        width: statusBar.width + 6;
        height: 3;

        anchors.top: statusBar.bottom;
        anchors.horizontalCenter: statusBar.horizontalCenter;
        color: "#ffffff";
    }

    //rechts
    Rectangle {
        id: statusRightBorder;

        width: 3;
        height: statusBar.height + 6;

        anchors.left: statusBar.right;
        anchors.verticalCenter: statusBar.verticalCenter;
        color: "#ffffff";
    }

    //oben
    Rectangle {
        id: statusTopBorder;

        width: statusBar.width + 6;
        height: 3;

        anchors.bottom: statusBar.top;
        anchors.horizontalCenter: statusBar.horizontalCenter;
        color: "#808080";
    }

    TextLabel {
        id: pauseText

        width: boardTopBorder.width - 6;
        height: boardLeftBorder.height - 6;

        anchors.top: boardTopBorder.bottom;
        anchors.left: boardLeftBorder.right;

        verticalAlignment: Text.AlignVCenter;
        horizontalAlignment: Text.AlignHCenter;

        color: "blue";
        fontSizeMode: Text.Fit;
        font.pointSize: 30;

        visible: false;

        text: "PAUSED";
    }

    WinPopup {
        parentWindow: mainWindow;
        topAnchor: boardTopBorder;
        leftAnchor: boardLeftBorder;
    }

    //links
    Rectangle {
        id: statusLeftBorder;

        width: 3;
        height: statusBar.height + 6;

        anchors.right: statusBar.left;
        anchors.verticalCenter: statusBar.verticalCenter;
        color: "#808080";
    }

    Grid {
        id: board;

        columns: gameModel.columns;
        rows: gameModel.rows;

        columnSpacing: 0
        rowSpacing: 0;
        spacing: 0;

        anchors.top: boardTopBorder.bottom;
        x: statusBar.x;

        Repeater {
            id: cellRepeater;

            model: gameModel.grid

            ImageButton {
                id: cell;

                width: Style.cellWidth * sizeFactor;
                height: Style.cellHeight * sizeFactor;

                buttonImage: Adapter.resolveImage(model.modelData)

                MouseArea {
                    id: ma

                    anchors.fill: parent;
                    acceptedButtons: Qt.LeftButton | Qt.MiddleButton |Qt.RightButton;
                    enabled: model.modelData.hidden && !isGameWon
                    onClicked: Manager.clickCell(model, mouse.button, cell);
                }
            }
        }
    }

    //unten
    Rectangle {
        id: boardBottomBorder;

        width: statusBottomBorder.width;
        height: 3;

        y: bottomOuterBorder.y - 9;
        anchors.horizontalCenter: statusBar.horizontalCenter;
        color: "#ffffff";
    }

    //rechts
    Rectangle {
        id: boardRightBorder;

        width: 3;
        height: boardLeftBorder.height;

        anchors.right: boardBottomBorder.right;
        anchors.top: boardTopBorder.top;
        color: "#ffffff";
    }

    //oben
    Rectangle {
        id: boardTopBorder;

        width: statusTopBorder.width;
        height: 3;

        y: statusBottomBorder.y + 9;
        anchors.horizontalCenter: statusBar.horizontalCenter;
        color: "#808080";
    }

    //links
    Rectangle {
        id: boardLeftBorder;

        width: 3;
        height: Math.max(board.height, 144 * sizeFactor) + 6;

        anchors.left: boardBottomBorder.left;
        anchors.top: boardTopBorder.top;
        color: "#808080";
    }

    //unten rand
    Rectangle {
        id: bottomOuterBorder;

        width: statusBar.width + 24;
        height: 3;

        anchors.bottom: leftOuterBorder.bottom;
        anchors.horizontalCenter: statusBar.horizontalCenter;
        color: "#808080";
    }

    //rechts rand
    Rectangle {
        id: rightOuterBorder;

        width: 3;
        height: leftOuterBorder.height;

        x: boardRightBorder.x + 9;
        anchors.top: topOuterBorder.top;
        color: "#808080";
    }

    //oben rand
    Rectangle {
        id: topOuterBorder;

        width: statusBar.width + 24;
        height: 3;

        y: statusBar.y - 12;
        anchors.horizontalCenter: parent.horizontalCenter;
        color: "#ffffff";
    }

    //links rand
    Rectangle {
        id: leftOuterBorder;

        width: 3;
        height: Math.max(board.height, 144 * sizeFactor) + statusBar.height + 36;

        x: boardLeftBorder.x - 9;
        anchors.top: topOuterBorder.top;
        color: "#ffffff";

        Component.onCompleted: {
            mainWindow.height = height;
        }
    }
}
