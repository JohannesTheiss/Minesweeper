import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15

import "qrc:/text"
import "qrc:/includes"

import "qrc:/scripts/Adapter.js" as Adapter

Window {
    id: statisticsWindow

    title: "Minesweeper - Statistics";

    width: screenBorder.width + 40
    height: screenBorder.height + 40

    minimumWidth: screenBorder.width + 40
    minimumHeight: screenBorder.height + 40

    maximumWidth: screenBorder.width + 40
    maximumHeight: screenBorder.height + 40

    visible: true;

    color: "#c0c0c0";

    Rectangle {
        id: screenBorder

        width: headerRow.width + headerRow.anchors.leftMargin*2;
        height: 325

        
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

            border.width: 1;
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

                    statisticsController.resetStatistics();
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

        Row {
            id: headerRow;

            anchors.top: screenBorder.top;
            anchors.left: screenBorder.left;

            anchors.leftMargin: 20;
            topPadding: 20;

            spacing: 15;

            TextLabel {
                id: modeLabel

                font.pointSize: 10;
                rightPadding: 100;

                text: "Mode"
            }

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
            anchors.left: headerRow.left;
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
                    text: Adapter.getConfigurationString(model.modelData.numberOfRows, model.modelData.numberOfColumns, model.modelData.numberOfMines);
                }

                TextLabel {
                    id: timeStat;

                    x: modeLabel.width + headerRow.spacing

                    font.pointSize: 10;
                    text: model.modelData.numberOfWins !== 0 ? Adapter.getMinutesFromSeconds(model.modelData.bestTime) : "-";
                }

                TextLabel {
                    id: gamesStat;

                    x: timeStat.x + timeLabel.width + headerRow.spacing;

                    font.pointSize: 10;
                    text: model.modelData.numberOfGamesPlayed;
                }

                TextLabel {
                    id: wonStat;

                    x: gamesStat.x + gamesLabel.width + headerRow.spacing;

                    font.pointSize: 10;
                    text: model.modelData.numberOfWins;
                }

                TextLabel {
                    id: lostStat;

                    x: wonStat.x + wonLabel.width + headerRow.spacing;

                    font.pointSize: 10;
                    text: model.modelData.numberOfDefeats;
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

                model: statisticsModel.statisticEntryModelList;

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
