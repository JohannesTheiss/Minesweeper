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

    //on Game ended: pass if the game is won and the best time for the currently active mode
    Connections {
        target: statisticsController;
        function onGameEnded(bestTime, won) {
            isGameWon = won;
            bestTimeForGameMode = bestTime;
        }
    }

    //winPopup is called when Game ended and isGameWon = true
    WinPopup {
        id: winPopup

        parentWindow: mainWindow;
        topAnchor: boardTopBorder;
        leftAnchor: boardLeftBorder;
    }

    //MenuBar to access Game Settings, Statistics and Help windows
    MinesweeperMenuBar {
        id: menuBar;

        parentWindow: mainWindow;
        passedStatusBar: statusBar;
    }

    title: "Minesweeper";
    visible: true;

    color: Style.windowBackground;

    //statusBar contains Buttons for new, pause and end game and 2 counters for flags and timer
    Rectangle {
        id: statusBar;

        width: Math.max(board.width, 340 * sizeFactor);
        height: Style.defaultHeight * sizeFactor;

        anchors.horizontalCenter: parent.horizontalCenter;

        y: 12;

        color: Style.windowBackground;

        TextLabel {
            id: flagsLabel;

            x: 10;

            anchors.verticalCenter: statusBar.verticalCenter;
            verticalAlignment: Text.AlignVCenter;

            font.pointSize: Style.largeFontSize * sizeFactor;
            font.family: Style.counterFont;
            color: +text < 0 ? Style.counterRed : Style.counterBlue;

            text: Adapter.flagsToString(gameModel.flagCount);
        }

        Image {
            id: flagImage;

            x: flagsLabel.x + flagsLabel.width + 2;

            anchors.verticalCenter: statusBar.verticalCenter;

            width: Style.cellWidth * sizeFactor;
            height: Style.cellHeight * sizeFactor;

            source: "qrc:/images/flagTransparent.png";
        }

        ImageButton {
            id: newButton;

            width: Style.menuButtonWidth * 2 * sizeFactor;
            height: Style.menuButtonHeight * sizeFactor;

            x: pausePlayButton.x - width - 10;

            anchors.verticalCenter: parent.verticalCenter;

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

            width: Style.menuButtonWidth * sizeFactor;
            height: Style.menuButtonHeight * sizeFactor;

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

            width: Style.menuButtonWidth * 2 * sizeFactor;
            height: Style.menuButtonHeight * sizeFactor;

            x: pausePlayButton.x + pausePlayButton.width + 10;

            anchors.verticalCenter: parent.verticalCenter;

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

            width: Style.cellWidth * sizeFactor;
            height: Style.cellHeight * sizeFactor;

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
            font.family: Style.counterFont;
            color: Style.counterBlue;

            text: Adapter.getMinutesFromSeconds(Math.min(gameModel.timePlayed, 5999));          //timeLabel should visually stop at 99:59, backend timer does not stop
        }
    }

    //Borders around statusBar
    Rectangle {
        id: statusBottomBorder;

        width: statusBar.width + 6;
        height: 3;

        anchors.top: statusBar.bottom;
        anchors.horizontalCenter: statusBar.horizontalCenter;
        color: Style.customWindowBorderLight;
    }

    Rectangle {
        id: statusRightBorder;

        width: 3;
        height: statusBar.height + 6;

        anchors.left: statusBar.right;
        anchors.verticalCenter: statusBar.verticalCenter;
        color: Style.customWindowBorderLight;
    }

    Rectangle {
        id: statusTopBorder;

        width: statusBar.width + 6;
        height: 3;

        anchors.bottom: statusBar.top;
        anchors.horizontalCenter: statusBar.horizontalCenter;
        color: Style.customWindowBorderDark;
    }

    Rectangle {
        id: statusLeftBorder;

        width: 3;
        height: statusBar.height + 6;

        anchors.right: statusBar.left;
        anchors.verticalCenter: statusBar.verticalCenter;
        color: Style.customWindowBorderDark;
    }

    //pauseText is shown after the pauseButton is clicked
    TextLabel {
        id: pauseText;

        width: boardTopBorder.width - 6;
        height: boardLeftBorder.height - 6;

        anchors.top: boardTopBorder.bottom;
        anchors.left: boardLeftBorder.right;

        verticalAlignment: Text.AlignVCenter;
        horizontalAlignment: Text.AlignHCenter;

        color: Style.pauseColor;
        fontSizeMode: Text.Fit;
        font.pointSize: Style.pauseFontSize;

        visible: false;

        text: "PAUSED";
    }

    //the Grid that holds the cells of the game board
    Grid {
        id: board;

        columns: gameModel.columns;
        rows: gameModel.rows;

        columnSpacing: 0;
        rowSpacing: 0;
        spacing: 0;

        anchors.top: boardTopBorder.bottom;
        x: statusBar.x;

        Repeater {
            id: cellRepeater;

            model: gameModel.grid;

            ImageButton {
                id: cell;

                width: Style.cellWidth * sizeFactor;
                height: Style.cellHeight * sizeFactor;

                buttonImage: Adapter.resolveImage(model.modelData);

                MouseArea {
                    id: ma;

                    anchors.fill: parent;
                    acceptedButtons: Qt.LeftButton | Qt.MiddleButton | Qt.RightButton;
                    enabled: model.modelData.hidden && !isGameWon;
                    onClicked: Manager.clickCell(model, mouse.button, cell);
                }
            }
        }
    }

    //Borders around the game board
    Rectangle {
        id: boardBottomBorder;

        width: statusBottomBorder.width;
        height: 3;

        y: bottomOuterBorder.y - 9;
        anchors.horizontalCenter: statusBar.horizontalCenter;
        color: Style.customWindowBorderLight;
    }

    Rectangle {
        id: boardRightBorder;

        width: 3;
        height: boardLeftBorder.height;

        anchors.right: boardBottomBorder.right;
        anchors.top: boardTopBorder.top;
        color: Style.customWindowBorderLight;
    }

    Rectangle {
        id: boardTopBorder;

        width: statusTopBorder.width;
        height: 3;

        y: statusBottomBorder.y + 9;
        anchors.horizontalCenter: statusBar.horizontalCenter;
        color: Style.customWindowBorderDark;
    }

    Rectangle {
        id: boardLeftBorder;

        width: 3;
        height: Math.max(board.height, 144 * sizeFactor) + 6;

        anchors.left: boardBottomBorder.left;
        anchors.top: boardTopBorder.top;
        color: Style.customWindowBorderDark;
    }

    //Border at the edges of the mainWindow
    Rectangle {
        id: bottomOuterBorder;

        width: statusBar.width + 24;
        height: 3;

        anchors.bottom: leftOuterBorder.bottom;
        anchors.horizontalCenter: statusBar.horizontalCenter;
        color: Style.customWindowBorderDark;
    }

    Rectangle {
        id: rightOuterBorder;

        width: 3;
        height: leftOuterBorder.height;

        x: boardRightBorder.x + 9;
        anchors.top: topOuterBorder.top;
        color: Style.customWindowBorderDark;
    }

    Rectangle {
        id: topOuterBorder;

        width: statusBar.width + 24;
        height: 3;

        y: statusBar.y - 12;
        anchors.horizontalCenter: parent.horizontalCenter;
        color: Style.customWindowBorderLight;
    }

    Rectangle {
        id: leftOuterBorder;

        width: 3;
        height: Math.max(board.height, 144 * sizeFactor) + statusBar.height + 36;

        x: boardLeftBorder.x - 9;
        anchors.top: topOuterBorder.top;
        color: Style.customWindowBorderLight;

        Component.onCompleted: {                                                            //needed so that the window is correctly resized after loading
            mainWindow.height = height;
        }
    }
}
