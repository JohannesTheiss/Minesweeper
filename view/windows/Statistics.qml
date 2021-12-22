import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15

import "qrc:/includes"
import "qrc:/text"
import "qrc:/popups"

import "qrc:/scripts/Adapter.js" as Adapter

Window {
    id: statisticsWindow;

    title: "Minesweeper - Statistics";

    property real calcWidth: screenBorder.width + 40;
    property real calcHeight: screenBorder.height + 40;

    width: calcWidth;
    height: calcHeight;

    minimumWidth: calcWidth;
    minimumHeight: calcHeight;

    maximumWidth: calcWidth;
    maximumHeight: calcHeight;

    visible: true;

    color: Style.windowBackground;

    Rectangle {
        id: screenBorder;

        width: headerRow.width + headerRow.anchors.leftMargin * 2;
        height: 325;
        
        x: 20;
        y: 20;

        border.width: Style.borderWidth;
        border.color: Style.popupRectBorder;

        color: Style.windowBackground;

        TextBox {
            id: headerLabel;

            x: 10;
            y: - height / 2;

            text: "Statistics";
        }

        ResetPopup {                                        //resetPopup is opened when resetButton is clicked
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
                id: modeLabel;

                font.pointSize: Style.standardFontSize;
                rightPadding: 100;
                text: "Mode";
            }

            TextLabel {
                id: timeLabel;

                font.pointSize: Style.standardFontSize;
                text: "Best Time";
            }

            TextLabel {
                id: gamesLabel;

                font.pointSize: Style.standardFontSize;
                text: "Games Played";
            }

            TextLabel {
                id: wonLabel;

                font.pointSize: Style.standardFontSize;
                text: "Games Won";
            }

            TextLabel {
                id: lostLabel;

                font.pointSize: Style.standardFontSize;
                text: "Games Lost";
            }
        }

        Rectangle {
            id: headerLine;

            height: 1;

            anchors.top: headerRow.bottom;
            anchors.topMargin: 5;
            anchors.left: headerRow.left;
            anchors.right: headerRow.right;

            color: Style.statisticsHeaderline;
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
            id: resetButton;

            anchors.right: screenBorder.right;
            anchors.bottom: screenBorder.bottom;

            anchors.rightMargin: 10;
            anchors.bottomMargin: 10;

            width: Style.standardButtonWidth;
            height: Style.standardButtonHeight;

            text: "Reset Stats";

            background: Rectangle {
                anchors.fill: parent;

                color: Style.standardButtonBackground;
            }

            onClicked: {
                resetPopup.visible = true;                  //opens resetPopup
                scrollview.enabled = false;                 //disables scrollview while resetPopup is visible
                resetButton.enabled = false;                //disables itself while resetPopup is visible
            }
        }
    }
}
