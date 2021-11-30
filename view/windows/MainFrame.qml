import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQml.Models 2.12
import QtQuick.Window 2.12
import QtQuick.Dialogs 1.0

import "qrc:/controls"
import "qrc:/includes"
import "qrc:/text"

Window {
    id: mainWindow;

    property int nWidth: 30;
    property int mHeight: 16;

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
    height: leftOuterBorder.height + 21;

    //Minimum Size
    minimumWidth: width;
    minimumHeight: height;

    maximumWidth: width;
    maximumHeight: height;

    color: "#c0c0c0";

    Rectangle {
        id: menuBar;

        width: topOuterBorder.width;
        height: 20;

        anchors.horizontalCenter: statusBar.horizontalCenter;

        color: "#ffffff";

        Row {
            anchors.fill: parent;

            anchors.leftMargin: 5;
            anchors.topMargin: 2;

            TextLabel {
                id: gameButton;
                width: 35;
                font.pointSize: 8.0;
                text: "Game";
            }
            TextLabel {
                id: statisticsButton;
                width: 50;
                font.pointSize: 8.0;
                text: "Statistics";
            }
            TextLabel {
                id: helpButton;
                width: 30;
                font.pointSize: 8.0;
                text: "Help";
            }
        }
    }

    Rectangle {
        id: statusBar;

        width: Math.max(board.width, 310);
        height: Style.defaultHeight;

        anchors.horizontalCenter: parent.horizontalCenter;

        y: 33;

        color: "#c0c0c0";

        TextLabel {
            id: flagsLabel;

            width: 30;
            x: 10;

            anchors.verticalCenter: statusBar.verticalCenter;
            verticalAlignment: Text.AlignVCenter;

            font.family: "Consolas";
            color: "blue";

            text: "099";
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
                for (let i = 0; i < nWidth * mHeight; i++) {
                    cellRepeater.itemAt(i).buttonImage = "qrc:/cellImages/cell.png";
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
                if (imageIndex === 0) {
                    icon.source = "qrc:/images/play.png";
                    toolTipText = "Play";
                    imageIndex = 1;
                    pauseScreen.visible = true;
                }else {
                    icon.source = "qrc:/images/pause.png";
                    toolTipText = "Pause";
                    imageIndex = 0;
                    pauseScreen.visible = false;
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
            onClicked: { console.log("loiloloi ez"); }
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

            width: 30;
            x: statusBar.width - 40;

            anchors.verticalCenter: statusBar.verticalCenter;
            verticalAlignment: Text.AlignVCenter;

            font.family: "Consolas";
            color: "blue";

            text: "000";
        }
    }

    Item {
        id: pauseScreen

        width: boardTopBorder.width - 6;
        height: boardLeftBorder.height - 6;

        anchors.top: boardTopBorder.bottom;
        anchors.left: boardLeftBorder.right;

        z: 3;

        visible: false;

        MouseArea {                     //don't pass clicks through pauseScreen
            anchors.fill: parent;
        }

        Rectangle {
            anchors.fill: parent
            color: "black"
            opacity: 0.5
        }

        Rectangle {
            width: pauseText.width;
            height: pauseText.height;

            anchors.centerIn: parent;

            color: "grey";

            TextLabel {
                id: pauseText

                height: Math.min(boardBottomBorder.y - boardTopBorder.y - 3, Style.defaultHeight);

                anchors.centerIn: parent;

                verticalAlignment: Text.AlignVCenter;
                horizontalAlignment: Text.AlignHCenter;

                color: "blue";
                fontSizeMode: Text.Fit;
                font.pointSize: 30;

                text: "PAUSED";
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

        columns: nWidth;
        rows: mHeight;

        columnSpacing: 0
        rowSpacing: 0;
        spacing: 0;

        anchors.top: boardTopBorder.bottom;
        x: statusBar.x;

        Repeater {
            id: cellRepeater;

            model: nWidth * mHeight;

            ImageButton {

                x: 100;
                y: 100;

                buttonImage: "qrc:/cellImages/cell.png";

                onClicked: { buttonImage = "qrc:/cellImages/empty.png"; }
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
    }
}
