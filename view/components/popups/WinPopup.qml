import QtQuick 2.15
import QtQuick.Controls 2.5

import "qrc:/text"
import "qrc:/includes"

import "qrc:/scripts/Adapter.js" as Adapter

/* @parameters
 * id: identifier for WinPopup                                              (e.g. id: winPopup;)
 * parentWindow: the window that the WinPopup is opened in                  (e.g. parentWindow: mainWindow;)
 * topAnchor: an object representing the topAnchor of the WinPopup          (e.g. topAnchor: boardTopBorder;)
 * leftAnchor: an object representing the leftAnchor of the WinPopup        (e.g. leftAnchor: boardLeftBorder;)
 */
Rectangle {
    id: winPopup;

    property var parentWindow;
    property var topAnchor;
    property var leftAnchor;

    anchors.horizontalCenter: topAnchor.horizontalCenter;
    anchors.verticalCenter: leftAnchor.verticalCenter;

    z: 90;

    width: winText.width + viewBoardButton.width + 30;
    height: winText.height + 20;

    border.width: Style.borderWidth;
    border.color: Style.popupBorder;
    color: Style.popupBackground;

    visible: parentWindow.isGameWon && !parentWindow.hideWinPopup;


    TextLabel {
        id: winText

        topPadding: 10;
        leftPadding: 10;

        font.pointSize: Style.smallFontSize * parentWindow.sizeFactor;

        text: (gameModel.timePlayed === parentWindow.bestTimeForGameMode ? "<b>New BEST TIME!</b>" : "<b>You won!</b>") +  "<br><br>" +
              "<b>Mode: </b>" + Adapter.getConfigurationString(gameModel.rows, gameModel.columns, gameModel.mineCount) + "<br><br>" +
              "<b>Best Time: </b>" + Adapter.getMinutesFromSeconds(bestTimeForGameMode)
              + "<br><br>" +
              "<b>Your Time: </b>" + Adapter.getMinutesFromSeconds(gameModel.timePlayed);
    }

    Button {
        id: viewBoardButton

        anchors.right: winPopup.right;
        anchors.bottom: winPopup.bottom;

        anchors.rightMargin: 10
        anchors.bottomMargin: 10;

        width: Style.standardButtonWidth;
        height: Style.standardButtonHeight;

        text: "View Board";

        background: Rectangle {
            anchors.fill: parent;

            color: Style.standardButtonBackground;
        }

        onClicked: {
            parentWindow.hideWinPopup = true;
        }
    }
}
