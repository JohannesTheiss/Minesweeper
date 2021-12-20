import QtQuick 2.15
import QtQuick.Controls 2.5
import QtQml.Models 2.15
import QtQuick.Window 2.15

import Qt.labs.platform 1.1

// import SizeScaling enum
import Backend.Game 1.0

import "qrc:/controls"
import "qrc:/includes"
import "qrc:/text"

import "qrc:/scripts/Adapter.js" as Adapter
import "qrc:/scripts/windowController.js" as WindowController
import "qrc:/scripts/Manager.js" as Manager

ApplicationWindow {
    id: mainWindow;

    property double sizeFactor: 1.0;

    property bool hideWinScreen: false;

    property bool isGameWon: false;
    property int bestTimeForGameMode: 0;

    Component.onCompleted: {
        // check if new size scaling is set (from backend side)
        Manager.updateSizeScaling();
    }

    Connections {
        target: statisticsController;
        function onGameEnded(bestTime, won) {
            // TODO start the end screen HERE
            // if the game is won the 'won' == true
            console.log("game won: " + won);
            isGameWon = won;
            bestTimeForGameMode = bestTime
        }
    }

    MenuBar {
        id: menuBar;

        Menu {
            title: qsTr("&Game");

            MenuItem {
                icon.source: "qrc:/cellImages/empty.png";

                checkable: true;
                checked: gameModel.columns === 9 && gameModel.rows === 9 && gameModel.mineCount === 10;

                text: qsTr("&Beginner");
                onTriggered: {
                    gameController.setGameMode(9, 9, 10);

                    mainWindow.minimumWidth = Math.max(gameModel.columns * Style.cellWidth * sizeFactor, 340 * sizeFactor) + 24;
                    mainWindow.minimumHeight = Math.max(gameModel.rows, 9) * Style.cellHeight * sizeFactor + statusBar.height + 36;

                    mainWindow.maximumWidth = Math.max(gameModel.columns * Style.cellWidth * sizeFactor, 340 * sizeFactor) + 24;
                    mainWindow.maximumHeight = Math.max(gameModel.rows, 9) * Style.cellHeight * sizeFactor + statusBar.height + 36;

                    mainWindow.width = Math.max(gameModel.columns * Style.cellWidth * sizeFactor, 340 * sizeFactor) + 24;
                    mainWindow.height = Math.max(gameModel.rows, 9) * Style.cellHeight * sizeFactor + statusBar.height + 36;

                    isGameWon = false;
                }
            }
            MenuItem {
                icon.source: "qrc:/cellImages/mine.png";

                checkable: true;
                checked: gameModel.columns === 16 && gameModel.rows === 16 && gameModel.mineCount === 40;

                text: qsTr("&Intermediate");
                onTriggered: {
                    gameController.setGameMode(16, 16, 40);

                    mainWindow.minimumWidth = Math.max(gameModel.columns * Style.cellWidth * sizeFactor, 340 * sizeFactor) + 24;
                    mainWindow.minimumHeight = Math.max(gameModel.rows, 9) * Style.cellHeight * sizeFactor + statusBar.height + 36;

                    mainWindow.maximumWidth = Math.max(gameModel.columns * Style.cellWidth * sizeFactor, 340 * sizeFactor) + 24;
                    mainWindow.maximumHeight = Math.max(gameModel.rows, 9) * Style.cellHeight * sizeFactor + statusBar.height + 36;

                    mainWindow.width = Math.max(gameModel.columns * Style.cellWidth * sizeFactor, 340 * sizeFactor) + 24;
                    mainWindow.height = Math.max(gameModel.rows, 9) * Style.cellHeight * sizeFactor + statusBar.height + 36;

                    isGameWon = false;
                }
            }
            MenuItem {
                icon.source: "qrc:/cellImages/mineRed.png";

                checkable: true;
                checked: gameModel.columns === 30 && gameModel.rows === 16 && gameModel.mineCount === 99;

                text: qsTr("&Expert");
                onTriggered: {
                    gameController.setGameMode(16, 30, 99);

                    mainWindow.minimumWidth = Math.max(gameModel.columns * Style.cellWidth * sizeFactor, 340 * sizeFactor) + 24;
                    mainWindow.minimumHeight = Math.max(gameModel.rows, 9) * Style.cellHeight * sizeFactor + statusBar.height + 36;

                    mainWindow.maximumWidth = Math.max(gameModel.columns * Style.cellWidth * sizeFactor, 340 * sizeFactor) + 24;
                    mainWindow.maximumHeight = Math.max(gameModel.rows, 9) * Style.cellHeight * sizeFactor + statusBar.height + 36;

                    mainWindow.width = Math.max(gameModel.columns * Style.cellWidth * sizeFactor, 340 * sizeFactor) + 24;
                    mainWindow.height = Math.max(gameModel.rows, 9) * Style.cellHeight * sizeFactor + statusBar.height + 36;

                    isGameWon = false;
                }
            }
            MenuItem {
                text: qsTr("&Custom...")

                onTriggered: {
                    WindowController.openWindow(mainWindow, "qrc:/windows/CustomSettings.qml",  { parentWindow: mainWindow });
                }
            }

            MenuSeparator { }

            Menu {
                title: qsTr("&Size");

                MenuItem {
                    checkable: true;
                    checked: gameModel.scaling === SizeScaling.SMALL

                    text: qsTr("&Small")
                    onTriggered: gameController.setScaling(SizeScaling.SMALL);
                }

                MenuItem {
                    checkable: true;
                    checked: gameModel.scaling === SizeScaling.MEDIUM

                    text: qsTr("&Medium")
                    onTriggered: gameController.setScaling(SizeScaling.MEDIUM);
                }

                MenuItem {
                    checkable: true;
                    checked: gameModel.scaling === SizeScaling.LARGE

                    text: qsTr("&Large")
                    onTriggered: gameController.setScaling(SizeScaling.LARGE);

                }

                Connections {
                    target: gameModel
                    function onScalingChanged() { Manager.updateSizeScaling(); }
                }
            }
        }

        Menu {
            title: qsTr("&Extras")

            MenuItem {
                icon.source: "qrc:/images/flagTransparent.png";
                text: qsTr("&Statistics");

                onTriggered: {
                    WindowController.openWindow(mainWindow, "qrc:/windows/Statistics.qml");
                }
            }

            MenuItem {
                icon.source: "qrc:/images/questionTransparent.png";
                text: qsTr("&Help");

                onTriggered: {
                    WindowController.openWindow(mainWindow, "qrc:/windows/HelpWindow.qml");
                }
            }
        }

        Menu {
            title: qsTr(gameModel.columns + "x" + gameModel.rows + "  " + gameModel.mineCount + " Mines");
            enabled: false;
        }
    }

    property int nWidth: 30;
    property int mHeight: 16;
    property int numOfMines: 99;

    title: "Minesweeper";
    visible: true;

    width: topOuterBorder.width;
    height: leftOuterBorder.height;

    //Minimum Size
    minimumWidth: topOuterBorder.width;
    minimumHeight: leftOuterBorder.height;

    maximumWidth: topOuterBorder.width;
    maximumHeight: leftOuterBorder.height;

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

            //width: 40 * sizeFactor; // 40 for linux font size
            x: 10;

            anchors.verticalCenter: statusBar.verticalCenter;
            verticalAlignment: Text.AlignVCenter;

            font.pointSize: Style.textSize * sizeFactor;
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

                hideWinScreen = isGameWon = false;
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

            font.pointSize: Style.textSize * sizeFactor;
            font.family: "Consolas";
            color: "blue";

            text: Adapter.getMinutesFromSeconds(Math.min(gameModel.timePlayed, 5999));
        }
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

    Rectangle {
        id: winScreen;

        anchors.horizontalCenter: boardTopBorder.horizontalCenter;
        anchors.verticalCenter: boardLeftBorder.verticalCenter;

        z: 90;

        width: winText.width + viewBoardButton.width + 30;
        height: winText.height + 20;

        border.width: 1;
        border.color: "#000000";
        color: "#c0c0c0";

        visible: isGameWon && !hideWinScreen; //TODO


        TextLabel {
            id: winText

            topPadding: 10;
            leftPadding: 10;

            font.pointSize: 8.0 * sizeFactor;

            text: (gameModel.timePlayed === bestTimeForGameMode ? "<b>New BEST TIME!</b>" : "<b>You won!</b>") +  "<br><br>" +
                  "<b>Mode: </b>" + Adapter.getConfigurationString(gameModel.rows, gameModel.columns, gameModel.mineCount) + "<br><br>" +
                  "<b>Best Time: </b>" + Adapter.getMinutesFromSeconds(bestTimeForGameMode)
                  + "<br><br>" +
                  "<b>Your Time: </b>" + Adapter.getMinutesFromSeconds(gameModel.timePlayed);
        }

        Button {
            id: viewBoardButton

            anchors.right: winScreen.right;
            anchors.bottom: winScreen.bottom;

            anchors.rightMargin: 10
            anchors.bottomMargin: 10;

            width: 100;
            height: 30;

            text: "View Board";

            background: Rectangle {
                anchors.fill: parent;

                color: "#f5f5f5";
            }

            onClicked: {
                hideWinScreen = true;
            }
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
//        anchors.top: board.bottom;
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

//        y: boardBottomBorder.y + 9;
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
