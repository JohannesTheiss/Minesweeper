import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15

import "qrc:/text"
import "qrc:/includes"

Window {
    id: helpWindow

//    modality: Qt.WindowModal;

    title: "Minesweeper - Custom Settings";

    width: 460;
    height: 350;

    minimumWidth: 460;
    minimumHeight: 350;

    maximumWidth: 460;
    maximumHeight: 350;

    visible: true;

    color: "#c0c0c0";

    Rectangle {
        id: screenBorder

        width: helpWindow.width - 40;
        height: helpWindow.height - 40;

        x: 20;
        y: 20;

        border.width: 1;
        border.color: "#595959";

        color: "#c0c0c0";

        TextBox {
            id: headerLabel;

            x: 10;
            y: - height / 2;

            text: "Game Information";
        }

        TextLabel {
            id: buttonsHeader

            topPadding: 15;
            leftPadding: 20;

            text: "Menu-Buttons:"

//                  \n- New: Start a new Game\n- ||: Pause/Unpause Game\n- End: Give up and reveal all Cells\n\n" +
//                  "Menu-Numbers:\n- Left: Number of Mines/Flags left\n- Right: Time since the Game started\n         Used for Highscores\n\n" +
//                  "Controls:\n- Left-Click: Reveal Cell\n- Right-Click: Set/Unset Flag\n- Middle-Click: Unset Flag";
        }

        Grid {
            id: buttonsGrid

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
            id: numbersHeader

            anchors.top: buttonsGrid.bottom;

            topPadding: 15;
            leftPadding: 20;

            text: "Menu-Numbers:"
        }

        Grid {
            id: numbersGrid

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
            id: controlsHeader

            anchors.top: numbersGrid.bottom;

            topPadding: 15;
            leftPadding: 20;

            text: "Controls:";
        }

        Grid {
            id: controlsGrid

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

                text: ": Unset Flag";
            }
        }
    }
}
