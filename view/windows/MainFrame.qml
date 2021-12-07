import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQml.Models 2.12
import QtQuick.Window 2.12
import QtQuick.Dialogs 1.0

import Qt.labs.platform 1.1

import "qrc:/controls"
import "qrc:/includes"
import "qrc:/text"

import "qrc:/scripts/Adapter.js" as Adapter

ApplicationWindow {
    id: mainWindow;

    MenuBar {
        id: menuBar;

        Menu {
            title: qsTr("&Game");

            MenuItem {
                icon.source: "qrc:/images/empty.png"

                text: qsTr("&Beginner");
                onTriggered: {
                    console.log("pre min");
                    mainWindow.minimumWidth = Math.max(20 * Style.cellWidth, 310) + 24;
                    mainWindow.minimumHeight = 11 * Style.cellHeight + statusBar.height + 36;
                    console.log("post min - pre max");
                    mainWindow.maximumWidth = Math.max(20 * Style.cellWidth, 310) + 24;
                    mainWindow.maximumHeight = 11 * Style.cellHeight + statusBar.height + 36;
                    console.log("post max - pre set");

                    nWidth = 9;
                    mHeight = 9;
                    numOfMines = 10;

                    gameController.setGameMode(9, 9, 10);

                    mainWindow.minimumWidth = topOuterBorder.width;
                    mainWindow.minimumHeight = leftOuterBorder.height;

                    mainWindow.maximumWidth = topOuterBorder.width;
                    mainWindow.maximumHeight = leftOuterBorder.height;

                    mainWindow.width = topOuterBorder.width;
                    mainWindow.height = leftOuterBorder.height;
                    console.log("change beginner");
                }
            }
            MenuItem {
                icon.source: "qrc:/images/mine.png"

                text: qsTr("&Intermediate");
                onTriggered: {
                    console.log("pre min");
                    mainWindow.minimumWidth = Math.max(25 * Style.cellWidth, 310) + 24;
                    mainWindow.minimumHeight = 14 * Style.cellHeight + statusBar.height + 36;
                    console.log("post min - pre max");
                    mainWindow.maximumWidth = Math.max(25 * Style.cellWidth, 310) + 24;
                    mainWindow.maximumHeight = 14 * Style.cellHeight + statusBar.height + 36;
                    console.log("post max - pre set");

                    nWidth = 16;
                    mHeight = 16;
                    numOfMines = 40;

                    gameController.setGameMode(16, 16, 40);

                    mainWindow.minimumWidth = topOuterBorder.width;
                    mainWindow.minimumHeight = leftOuterBorder.height;

                    mainWindow.maximumWidth = topOuterBorder.width;
                    mainWindow.maximumHeight = leftOuterBorder.height;

                    mainWindow.width = topOuterBorder.width;
                    mainWindow.height = leftOuterBorder.height;
                    console.log("change beginner");
                }
            }
            MenuItem {
                icon.source: "qrc:/images/mineRed.png"

                text: qsTr("&Expert");
                onTriggered: {
                    console.log("pre min");
                    mainWindow.minimumWidth = Math.max(30 * Style.cellWidth, 310) + 24;
                    mainWindow.minimumHeight = 16 * Style.cellHeight + statusBar.height + 36;
                    console.log("post min - pre max");
                    mainWindow.maximumWidth = Math.max(30 * Style.cellWidth, 310) + 24;
                    mainWindow.maximumHeight = 16 * Style.cellHeight + statusBar.height + 36;
                    console.log("post max - pre set");

                    nWidth = 30;
                    mHeight = 16;
                    numOfMines = 99;

                    gameController.setGameMode(16, 30, 99);

                    mainWindow.minimumWidth = topOuterBorder.width;
                    mainWindow.minimumHeight = leftOuterBorder.height;

                    mainWindow.maximumWidth = topOuterBorder.width;
                    mainWindow.maximumHeight = leftOuterBorder.height;

                    mainWindow.width = topOuterBorder.width;
                    mainWindow.height = leftOuterBorder.height;
                    console.log("change beginner");
                }
            }
            MenuItem { text: qsTr("&Custom...") }
        }


        Menu {
            title: qsTr("&Extras")

            MenuItem {
                icon.source: "qrc:/images/flagTransparent.png";
                text: qsTr("&Statistics");
            }
            MenuItem {
                icon.source: "qrc:/images/questionTransparent.png";
                text: qsTr("&Help");
            }
        }

//        Menu {
//            enabled: false;
//        }
//        Menu {
//            enabled: false;
//        }
//        Menu {
//            enabled: false;
//        }
//        Menu {
//            enabled: false;
//        }
//        Menu {
//            enabled: false;
//        }
//        Menu {
//            enabled: false;
//        }

        Menu {
            title: qsTr(gameModel.rows + "x" + gameModel.columns + "  " + gameModel.mineCount + " Mines");
            enabled: false;
        }
    }

//    footer: TextLabel {
//        text: "99 Mines";
//    }

    property int nWidth: 30;
    property int mHeight: 16;
    property int numOfMines: 99;

    title: "Minesweeper";
    visible: true;
//    width: Style.cellWidth * n;
//    height: Style.cellHeight * m;

//    //Minimum Size
//    minimumWidth: Style.cellWidth * n;
//    minimumHeight: Style.cellHeight * m;

//    maximumWidth: Style.cellWidth * n;
//    maximumHeight: Style.cellHeight * m;

//    width: 1500;
//    height: 600;

    width: topOuterBorder.width;
    height: leftOuterBorder.height;

    //Minimum Size
    minimumWidth: topOuterBorder.width;
    minimumHeight: leftOuterBorder.height;

    maximumWidth: topOuterBorder.width;
    maximumHeight: leftOuterBorder.height;

    color: "#c0c0c0";

//    Rectangle {
//        id: menuBar;

//        width: topOuterBorder.width;
//        height: 20;

//        anchors.horizontalCenter: statusBar.horizontalCenter;

//        color: "#ffffff";

//        Row {
//            anchors.fill: parent;

//            Button {
//                id: gameButton;

//                height: menuBar.height;
//                width: 45;

//                MouseArea {                                         //used for showing toolTips
//                    id: ma;

//                    anchors.fill: parent;
//                    hoverEnabled: true;
//                    onClicked: {                                    //pass click to Button
//                        parent.onClicked();
//                    }
//                }

//                Text {
//                    anchors.centerIn: parent;

//                    font.family: "Arial";
//                    color: "black";
//                    text: "Game";
//                }

//                background: Rectangle {
//                    color: ma.containsMouse? "lightblue" : "transparent";

//                    border.width: ma.containsMouse? 1 : 0;
//                    border.color: "lightblue";
//                }
//            }

//            Button {
//                id: statisticsButton;

//                height: menuBar.height;
//                width: 45;

//                Text {
//                    anchors.centerIn: parent;

//                    font.family: "Arial";
//                    color: "black";
//                    text: "Statistics";
//                }

//                background: Rectangle {
//                    color: "transparent";
//                }
//            }

//            Button {
//                id: helpButton;

//                height: menuBar.height;
//                width: 45;

//                Text {
//                    anchors.centerIn: parent;

//                    font.family: "Arial";
//                    color: "black";
//                    text: "Help";
//                }

//                background: Rectangle {
//                    color: "transparent";
//                }
//            }
//        }

//        TextLabel {
//            anchors.right: parent.right;
//            anchors.rightMargin: 5;
//            height: parent.height;

//            verticalAlignment: Text.AlignVCenter;

//            font.pointSize: 8.0;

//            text: nWidth + "x" + mHeight + " 99 Mines";
//        }
//    }

    Rectangle {
        id: statusBar;

        width: Math.max(board.width, 310);
        height: Style.defaultHeight;

        anchors.horizontalCenter: parent.horizontalCenter;

        y: 12;

        color: "#c0c0c0";

        TextLabel {
            id: flagsLabel;

            width: 40;
            x: 10;

            anchors.verticalCenter: statusBar.verticalCenter;
            verticalAlignment: Text.AlignVCenter;

            font.family: "Consolas";
            color: "blue";

            //text: "0" + numOfMines;
            text: gameModel.flagCount;
        }

        Image {
            id: flagImage;

            x: flagsLabel.x + flagsLabel.width + 2;
            anchors.verticalCenter: statusBar.verticalCenter;

            source: "qrc:/images/flagTransparent.png";
        }

        IconButton {
            id: newButton;

            width: 50;
            height: 15;

            x: pausePlayButton.x - 52;

            anchors.verticalCenter: parent.verticalCenter

            icon.source: "qrc:/images/new.png";
            hasBorder: false;
            onClicked: {
                gameController.initGame();

                if (board.visible === false) {
                    board.visible = true;
                    pausePlayButton.icon.source = "qrc:/images/pause.png";
                    pausePlayButton.toolTipText = "Pause";
                    pausePlayButton.imageIndex = 0;
                    pauseText.visible = false;
                }
            }
        }

        IconButton {
            id: pausePlayButton;

            width: 30;
            height: 30;

            anchors.centerIn: parent;

            icon.source: "qrc:/images/pause.png";
            hasBorder: false;
            onClicked: {
                gameController.togglePauseGame();
                if (imageIndex === 0) {
                    icon.source = "qrc:/images/play.png";
                    toolTipText = "Play";
                    imageIndex = 1;
                    pauseText.visible = true;
                    board.visible = false;
                }else {
                    icon.source = "qrc:/images/pause.png";
                    toolTipText = "Pause";
                    imageIndex = 0;
                    pauseText.visible = false;
                    board.visible = true;
                }
            }
        }

        IconButton {
            id: stopButton;

            width: 62;
            height: 15;

            x: pausePlayButton.x + 32;

            anchors.verticalCenter: parent.verticalCenter

            icon.source: "qrc:/images/stop.png";
            hasBorder: false;
            onClicked: {
                gameController.endGame();
                for (let i = 0; i < nWidth * mHeight; i++) {
                    cellRepeater.itemAt(i).buttonImage = "qrc:/cellImages/empty.png";
                }

                if (board.visible === false) {
                    board.visible = true;
                    pausePlayButton.icon.source = "qrc:/images/pause.png";
                    pausePlayButton.toolTipText = "Pause";
                    pausePlayButton.imageIndex = 0;
                    pauseText.visible = false;
                }
            }
        }

        Image {
            id: hourglassImage;

            width: 16;
            height: 16;

            x: timeLabel.x - 18;
            anchors.verticalCenter: statusBar.verticalCenter;

            source: "qrc:/images/timerTransparent.png";
        }

        TextLabel {
            id: timeLabel;

            width: 40;
            x: statusBar.width - 40;

            anchors.verticalCenter: statusBar.verticalCenter;
            verticalAlignment: Text.AlignVCenter;

            font.family: "Consolas";
            color: "blue";

            text: Adapter.timeToString(gameModel.timePlayed);
        }
    }

    TextLabel {
        id: pauseText

        width: boardTopBorder.width - 6;
        height: boardLeftBorder.height - 6;

        anchors.top: boardTopBorder.bottom;
        anchors.left: boardLeftBorder.right;


//                height: Math.min(boardBottomBorder.y - boardTopBorder.y - 3, Style.defaultHeight);

        verticalAlignment: Text.AlignVCenter;
        horizontalAlignment: Text.AlignHCenter;

        color: "blue";
        fontSizeMode: Text.Fit;
        font.pointSize: 30;

        visible: false;

        text: "PAUSED";
    }

//    Item {
//        id: pauseScreen

//        width: boardTopBorder.width - 6;
//        height: boardLeftBorder.height - 6;

//        anchors.top: boardTopBorder.bottom;
//        anchors.left: boardLeftBorder.right;

//        z: 3;

//        visible: false;

//        Rectangle {
//            width: pauseText.width;
//            height: pauseText.height;

//            anchors.centerIn: parent;

//            color: "grey";


//        }
//    }

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

        //columns: nWidth;
        //rows: mHeight;
        columns: gameModel.columns;
        rows: gameModel.rows;

        columnSpacing: 0
        rowSpacing: 0;
        spacing: 0;

        anchors.top: boardTopBorder.bottom;
        x: statusBar.x;

        Repeater {
            id: cellRepeater;

            //model: nWidth * mHeight;
            model: gameModel.grid

            ImageButton {
                id: cell;

                x: 100;
                y: 100;

                buttonImage: Adapter.resolveImage(model.modelData)

                MouseArea {
                    id: ma

                    anchors.fill: parent;
                    acceptedButtons: Qt.LeftButton | Qt.MiddleButton |Qt.RightButton;
                    enabled: model.modelData.hidden;
                    onClicked: {
                        gameController.startGame();
                        switch(mouse.button)
                        {
                            case Qt.LeftButton:
                                gameController.revealCell(model.index);
                                break;

                            case Qt.MiddleButton:
                            case Qt.RightButton:
                                gameController.toggleFlagInCell(model.index);
                                break;
                        }
                    }
                }
            }
        }
    }

    //unten
    Rectangle {
        id: boardBottomBorder;

        width: statusBottomBorder.width;
        height: 3;

        anchors.top: board.bottom;
        anchors.horizontalCenter: statusBar.horizontalCenter;
        color: "#ffffff";
    }

    //rechts
    Rectangle {
        id: boardRightBorder;

        width: 3;
        height: board.height + 6;

        anchors.right: boardBottomBorder.right;
        anchors.verticalCenter: board.verticalCenter;
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
        height: board.height + 6;

        anchors.left: boardBottomBorder.left;
        anchors.verticalCenter: board.verticalCenter;
        color: "#808080";
    }

    //unten rand
    Rectangle {
        id: bottomOuterBorder;

        width: statusBar.width + 24;
        height: 3;

        y: boardBottomBorder.y + 9;
        anchors.horizontalCenter: statusBar.horizontalCenter;
        color: "#808080";
    }

    //rechts rand
    Rectangle {
        id: rightOuterBorder;

        width: 3;
        height: board.height + statusBar.height + 33;

        x: boardRightBorder.x + 9;
        anchors.bottom: bottomOuterBorder.top;
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
        height: board.height + statusBar.height + 36;

        x: boardLeftBorder.x - 9;
        anchors.bottom: bottomOuterBorder.bottom;
        color: "#ffffff";

        Component.onCompleted: {
            mainWindow.height = height;
            console.log("mainWindow " + mainWindow.height);
        }
    }
}
