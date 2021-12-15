import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15

import "qrc:/text"
import "qrc:/includes"

import "qrc:/scripts/Adapter.js" as Adapter

Window {
    id: customSettings

    //modality: Qt.WindowModal;

    title: "Minesweeper - Statistics";

    width: 545;
    height: 350;

    minimumWidth: 545;
    minimumHeight: 350;

    maximumWidth: 545;
    maximumHeight: 350;

    visible: true;

    color: "#c0c0c0";

    Component.onCompleted: {
        console.log("modeLabelWidth " + modeLabel.width)
        console.log("headerWidth " + headerLine.width)
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

            text: "Statistics";
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

//            width: headerRow.width;
            height: 1;

            anchors.top: headerRow.bottom;
            anchors.topMargin: 5;
            anchors.left: modeLabel.left;
            anchors.leftMargin: modeLabel.leftPadding;
            anchors.right: headerRow.right;

            color: "#000000";
        }

        ListModel {
            id: timeModel;
            

            //ListElement {
                //mode: "Beginner";
                //time: 20;
                //games: 1;
                //won: 1;
            //}

            //ListElement {
                //mode: "Intermediate";
                //time: 20;
                //games: 1;
                //won: 1;
            //}

            //ListElement {
                //mode: "Expert";
                //time: 20;
                //games: 1;
                //won: 1;
            //}

            //ListElement {
                //mode: "999x999 - 999 Mines";
                //time: 20;
                //games: 1;
                //won: 1;
            //}
        }

        ScrollView {
            id: scrollview

            anchors {top: headerLine.bottom; right: parent.right; left: parent.left; bottom: parent.bottom; topMargin: 5;
                    bottomMargin: 10; leftMargin: 20;/*leftMargin: Window.window.width / Style.percentageEdge*/}
            x: Window.window.width / Style.percentageEdge
            ScrollBar.vertical.policy: ScrollBar.AsNeeded
            ScrollBar.vertical.interactive: true
            ScrollBar.horizontal.interactive: false
            bottomPadding: 5

            ButtonGroup {                                                   //used for checking if all CheckBoxes of the PatientElements are checked
                id: patientCheckGroup

                exclusive: false
            }

            ListView {                                                      //holds the PatientElements
                id: listview
                orientation: Qt.Vertical

                anchors.fill: parent
                clip: true
                spacing: 25

                //model: timeModel;
                model: statisticsModel.statisticEntryModelList;

                delegate: /*PatientElement {                                  //fills the PatientElements with data from backend.patientList
                    parentWindow: patientList
                    numOfLabels: numOfColumns
                    listModel: model
                }*/
//                Row {
//                    spacing: 25;

//                    TextLabel {
//                        text: mode;
//                    }

//                    TextLabel {
//                        text: time;
//                    }

//                    TextLabel {
//                        text: games;
//                    }

//                    TextLabel {
//                        text: won;
//                    }

//                    TextLabel {
//                        text: games - won;
//                    }
//                }

                Item {
                    TextLabel {
                        id: modeStat;

                        //text: model.modelData.numberOfColumns + "x" + model.modelData.numberOfRows + " " + model.modelData.numberOfMines + " Mines";
                        text: Adapter.getConfigurationString(model.modelData.numberOfRows, model.modelData.numberOfColumns, model.modelData.numberOfMines);

                        width: timeLabel.x - modeLabel.x + modeLabel.leftPadding;

                        horizontalAlignment: Text.AlignLeft

                        font.pointSize: 10;

                        anchors.left: headerLine.left;
                    }

                    TextLabel {
                        id: timeStat

                        x: 133;

                        text: model.modelData.bestTime;

                        font.pointSize: 10;

                    }

                    TextLabel {
                        id: gamesStat;

                        x: timeStat.x + timeLabel.width + headerRow.spacing;

                        text: model.modelData.numberOfGamesPlayed;

                        anchors.left: gamesLabel.left;
                    }

                    TextLabel {
                        id: wonStat;

                        x: gamesStat.x + gamesLabel.width + headerRow.spacing;

                        //text: won;
                        text: model.modelData.numberOfWins;

                        anchors.left: wonLabel.left;
                    }

                    TextLabel {
                        id: lostStat;

                        x: wonStat.x + wonLabel.width + headerRow.spacing;

                        //text: games - won;
                        text: model.modelData.numberOfDefeats;

                        anchors.left: lostLabel.left;
                    }
                }
            }
        }
    }
}
