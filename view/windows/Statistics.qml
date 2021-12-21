import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15

import "qrc:/includes"
import "qrc:/text"
import "qrc:/popups"

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

        ResetPopup {
            id: resetPopup;

            passedScrollview: scrollview;
            passedButton: resetButton;
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

                delegate: StatsDelegate {
                    headerR: headerRow;
                    modeL: modeLabel;
                    timeL: timeLabel;
                    gamesL: gamesLabel;
                    wonL: wonLabel;
                }
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
                resetPopup.visible = true;
                scrollview.enabled = false;
                resetButton.enabled = false;
            }
        }
    }
}
