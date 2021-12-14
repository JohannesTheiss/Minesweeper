import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15

import "qrc:/text"
import "qrc:/includes"

Window {
    id: helpWindow

//    modality: Qt.WindowModal;

    title: "Minesweeper - Custom Settings";

    width: 500;
    height: 350;

    minimumWidth: 500;
    minimumHeight: 350;

    maximumWidth: 500;
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
            id: helpText

            topPadding: 15;
            leftPadding: 20;

            text: "Menu-Buttons:\n- New: Start a new Game\n- ||: Pause/Unpause Game\n- End: End the running Game and reveal all Cells\n\n" +
                  "Menu-Numbers:\n- Left: Number of Mines/Flags to set\n- Right: Time since the Start of the Game\n\n" +
                  "Controls:\n- Left-Click: Reveal Cell\n- Right-Click: Set/Unset Flag\n- Middle-Click: Unset Flag";
        }
    }
}
