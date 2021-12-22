import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15

import "qrc:/text"
import "qrc:/includes"

Window {
    id: helpWindow;

    title: "Minesweeper - Game Information";

    property real calcWidth: screenBorder.width + 40;
    property real calcHeight: screenBorder.height + 40;

    width: calcWidth;
    height: calcHeight;

    //window should not be resizable
    minimumWidth: calcWidth;
    minimumHeight: calcHeight;

    maximumWidth: calcWidth;
    maximumHeight: calcHeight;

    visible: true;

    color: Style.windowBackground;

    Rectangle {
        id: screenBorder;

        width: numbersGrid.width + 40;
        height: buttonsHeader.topPadding + buttonsHeader.height + buttonsGrid.height + numbersHeader.height + numbersGrid.height + controlsHeader.height + controlsGrid.height;

        x: 20;
        y: 20;

        border.width: Style.borderWidth;
        border.color: Style.popupRectBorder;

        color: Style.windowBackground;

        TextBox {
            id: headerLabel;

            x: 10;
            y: - height / 2;

            text: "Game Information";
        }

        TextLabel {
            id: buttonsHeader;

            topPadding: 15;
            leftPadding: 20;

            text: "Menu-Buttons:";
        }

        Grid {
            id: buttonsGrid;

            columns: 3;

            spacing: 5;

            anchors.top: buttonsHeader.bottom;

            topPadding: 5;
            leftPadding: 20;

            TextLabel {
                height: newButtonImage.height;
                verticalAlignment: Text.AlignVCenter;

                text: "-";
            }

            Image {
                id: newButtonImage;

                width: 40;
                height: 20;

                source: "qrc:/images/newButton.png";
            }

            TextLabel {
                height: newButtonImage.height;
                verticalAlignment: Text.AlignVCenter;

                text: ": Start a new Game";
            }

            TextLabel {
                height: pauseImage.height;
                verticalAlignment: Text.AlignVCenter;

                text: "-";
            }

            Image {
                id: pauseImage;

                anchors.leftMargin: 10;

                width: 20;
                height: 20;

                source: "qrc:/images/pauseButton.png";
            }

            TextLabel {
                height: pauseImage.height;
                verticalAlignment: Text.AlignVCenter;

                text: ": Pause/Unpause Game";
            }

            TextLabel {
                height: endImage.height;
                verticalAlignment: Text.AlignVCenter;

                text: "-";
            }

            Image {
                id: endImage;

                width: 40;
                height: 20;

                source: "qrc:/images/endButton.png";
            }

            TextLabel {
                height: endImage.height;
                verticalAlignment: Text.AlignVCenter;

                text: ": Give up and reveal all Cells";
            }
        }

        TextLabel {
            id: numbersHeader;

            anchors.top: buttonsGrid.bottom;

            topPadding: 15;
            leftPadding: 20;

            text: "Menu-Counters:";
        }

        Grid {
            id: numbersGrid;

            columns: 3;

            spacing: 5;

            anchors.top: numbersHeader.bottom;

            leftPadding: 20;

            TextLabel {
                height: flagsImage.height;
                verticalAlignment: Text.AlignVCenter;

                text: "-";
            }

            Image {
                id: flagsImage;

                width: 70;
                height: 25;

                source: "qrc:/images/helpFlag.png";
            }

            TextLabel {
                height: flagsImage.height;
                verticalAlignment: Text.AlignVCenter;

                text: ": Number of Mines/Flags left";
            }

            TextLabel {
                height: timeImage.height;
                verticalAlignment: Text.AlignVCenter;

                text: "-";
            }

            Image {
                id: timeImage;

                anchors.leftMargin: 10;

                width: 70;
                height: 25;

                source: "qrc:/images/helpTime.png";
            }

            TextLabel {
                height: timeImage.height;
                verticalAlignment: Text.AlignVCenter;

                text: ": Time elapsed since the Game started";
            }
        }

        TextLabel {
            id: controlsHeader;

            anchors.top: numbersGrid.bottom;

            topPadding: 15;
            leftPadding: 20;

            text: "Controls:";
        }

        Grid {
            id: controlsGrid;

            columns: 2;

            columnSpacing: 2;

            anchors.top: controlsHeader.bottom;

            leftPadding: 20;

            TextLabel {
                height: flagsImage.height;
                verticalAlignment: Text.AlignVCenter;

                text: "- Left-Click";
            }

            TextLabel {
                height: flagsImage.height;
                verticalAlignment: Text.AlignVCenter;

                text: ": Reveal Cell";
            }

            TextLabel {
                height: timeImage.height;
                verticalAlignment: Text.AlignVCenter;

                text: "- Right-Click";
            }

            TextLabel {
                height: timeImage.height;
                verticalAlignment: Text.AlignVCenter;

                text: ": Set/Unset Flag";
            }

            TextLabel {
                height: flagsImage.height;
                verticalAlignment: Text.AlignVCenter;

                text: "- Middle-Click";
            }

            TextLabel {
                height: flagsImage.height;
                verticalAlignment: Text.AlignVCenter;

                text: ": Set/Unset Flag";
            }
        }
    }
}
