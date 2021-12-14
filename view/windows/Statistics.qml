import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15

import "qrc:/text"
import "qrc:/includes"

import "qrc:/scripts/Adapter.js" as Adapter

Window {
    id: statisticsWindow

    title: "Minesweeper - Statistics";

    width: 545;
    height: 365;

    minimumWidth: 545;
    minimumHeight: 365;

    maximumWidth: 545;
    maximumHeight: 365;

    visible: true;

    color: "#c0c0c0";

    Rectangle {
        id: screenBorder

        width: statisticsWindow.width - 40;
        height: statisticsWindow.height - 40;

        x: 20;
        y: 20;

        border.width: 1;
        border.color: "#595959";

        color: "#c0c0c0";

        TextBox {
            id: headerLabel;

            x: 10;
            y: - height / 2;

            text: "Statistics";
        }

        Rectangle {
            id: resetAccept;

            anchors.centerIn: parent;
            z: 90;

            width: 400;
            height: 150;

            border.width: 2;
            border.color: "#000000";
            color: "#c0c0c0";

            visible: false;

            TextLabel {
                anchors.centerIn: parent;

                horizontalAlignment: Text.AlignHCenter;

                text: "You are about to delete all saved statistics.\nAre you sure?";
            }

            Button {
                id: acceptButton

                anchors.right: cancelButton.left;
                anchors.bottom: parent.bottom;

                anchors.rightMargin: 10
                anchors.bottomMargin: 10;

                width: 100;
                height: 30;

                text: "Accept";

                background: Rectangle {
                    anchors.fill: parent;

                    color: "#f5f5f5";
                }

                onClicked: {
                    resetAccept.visible = false;
                    scrollview.enabled = true;
                    resetButton.enabled = true;
                }
            }

            Button {
                id: cancelButton

                anchors.right: parent.right;
                anchors.bottom: parent.bottom;

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
                    resetAccept.visible = false;
                    scrollview.enabled = true;
                    resetButton.enabled = true;
                }
            }
        }

        TextLabel {
            id: modeLabel

            leftPadding: 20;
            topPadding: 20;

            font.pointSize: 10;

            text: "Mode"
        }

        Row {
            id: headerRow;

            anchors.top: modeLabel.top;
            anchors.left: modeLabel.right;

            leftPadding: 100;
            topPadding: 20;

            spacing: 15;

            TextLabel {
                id: timeLabel

                font.pointSize: 10;

                text: "Best Time"
            }

            TextLabel {
                id: gamesLabel

                font.pointSize: 10;

                text: "Games Played"
            }

            TextLabel {
                id: wonLabel

                font.pointSize: 10;

                text: "Games Won"
            }

            TextLabel {
                id: lostLabel

                font.pointSize: 10;

                text: "Games Lost"
            }
        }

        Rectangle {
            id: headerLine;

            height: 1;

            anchors.top: headerRow.bottom;
            anchors.topMargin: 5;
            anchors.left: modeLabel.left;
            anchors.leftMargin: modeLabel.leftPadding;
            anchors.right: headerRow.right;

            color: "#000000";
        }

        Component {
            id: statsDelegate

            Item {
                id: ma

                height: modeStat.height;

                TextLabel {
                    id: modeStat;

                    font.pointSize: 10;
                    text: mode;
                }

                TextLabel {
                    id: timeStat;

                    x: 133;

                    font.pointSize: 10;
                    text: time;
                }

                TextLabel {
                    id: gamesStat;

                    x: timeStat.x + timeLabel.width + headerRow.spacing;

                    font.pointSize: 10;
                    text: games;
                }

                TextLabel {
                    id: wonStat;

                    x: gamesStat.x + gamesLabel.width + headerRow.spacing;

                    font.pointSize: 10;
                    text: won;
                }

                TextLabel {
                    id: lostStat;

                    x: wonStat.x + wonLabel.width + headerRow.spacing;

                    font.pointSize: 10;
                    text: games - won;
                }
            }
        }

     ScrollView {
            id: scrollview;

            anchors { top: headerLine.bottom; right: headerLine.right; left: headerLine.left;
                    bottom: screenBorder.bottom; topMargin: 5; bottomMargin: 55; }
            ScrollBar.vertical.policy: ScrollBar.AsNeeded;
            ScrollBar.vertical.interactive: true;
            ScrollBar.horizontal.visible : false;
            bottomPadding: 10;

            ListView {
                id: listview;

                orientation: Qt.Vertical;
                anchors.fill: parent;
                clip: true;
                spacing: 5;

                model: timeModel;

                delegate: statsDelegate;
            }
        }
        
         Button {
            id: resetButton

            anchors.right: screenBorder.right;
            anchors.bottom: screenBorder.bottom;

            anchors.rightMargin: 10
            anchors.bottomMargin: 10;

            width: 100;
            height: 30;

            text: "Reset Stats";

            background: Rectangle {
                anchors.fill: parent;

                color: "#f5f5f5";
            }

            onClicked: {
                resetAccept.visible = true;
                scrollview.enabled = false;
                resetButton.enabled = false;
            }
        }
    }
}
