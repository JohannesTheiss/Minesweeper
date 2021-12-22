import QtQuick 2.15
import Qt.labs.platform 1.1

import Backend.Game 1.0

import "qrc:/scripts/Manager.js" as Manager

/* @parameters
 * id: identifier for MinesweeperMenuBar                                                        (e.g. id: menuBar;)
 * parentWindow: the window, that the MinesweeperMenuBar is attached to, used for resizing      (e.g. parentWindow: mainWindow;)
 * passedStatusBar: the statusBar of MainFrame, used for resizing                               (e.g. passedStatusBar: statusBar;)
 */
MenuBar {
    id: menuBar;

    property var parentWindow;
    property var passedStatusBar;

    Menu {
        //1st menu "Game"
        title: qsTr("&Game");

        MenuItem {
            //MenuOption Beginner-Difficulty, changes mode and resizes window
            icon.source: "qrc:/cellImages/empty.png";

            checkable: true;
            checked: gameModel.columns === 9 && gameModel.rows === 9 && gameModel.mineCount === 10;

            text: qsTr("&Beginner");
            onTriggered: {
                gameController.setGameMode(9, 9, 10);

                Manager.resizeWindow(parentWindow, passedStatusBar);
                Manager.resetForNewGame(parentWindow);
            }
        }
        MenuItem {
            //MenuOption Intermediate-Difficulty, changes mode and resizes window
            icon.source: "qrc:/cellImages/mine.png";

            checkable: true;
            checked: gameModel.columns === 16 && gameModel.rows === 16 && gameModel.mineCount === 40;

            text: qsTr("&Intermediate");
            onTriggered: {
                gameController.setGameMode(16, 16, 40);

                Manager.resizeWindow(parentWindow, passedStatusBar);
                Manager.resetForNewGame(parentWindow);
            }
        }
        MenuItem {
            //MenuOption Expert-Difficulty, changes mode and resizes window
            icon.source: "qrc:/cellImages/mineRed.png";

            checkable: true;
            checked: gameModel.columns === 30 && gameModel.rows === 16 && gameModel.mineCount === 99;

            text: qsTr("&Expert");
            onTriggered: {
                gameController.setGameMode(16, 30, 99);

                Manager.resizeWindow(parentWindow, passedStatusBar);
                Manager.resetForNewGame(parentWindow);
            }
        }
        MenuItem {
            //MenuOption CustomSettings, opens CustomSettings window
            text: qsTr("&Custom...")

            onTriggered: {
                Manager.openWindow(parentWindow, "qrc:/windows/CustomSettings.qml",  { parentWindow: parentWindow, parentStatusBar: passedStatusBar });
            }
        }

        MenuSeparator { }

        Menu {
            //MenuOption visual Size, contains subMenu
            title: qsTr("&Size");

            MenuItem {
                //SubMenuOption Small
                checkable: true;
                checked: gameModel.scaling === SizeScaling.SMALL

                text: qsTr("&Small")
                onTriggered: gameController.setScaling(SizeScaling.SMALL);
            }

            MenuItem {
                //SubMenuOption Medium
                checkable: true;
                checked: gameModel.scaling === SizeScaling.MEDIUM

                text: qsTr("&Medium")
                onTriggered: gameController.setScaling(SizeScaling.MEDIUM);
            }

            MenuItem {
                //SubMenuOption Large
                checkable: true;
                checked: gameModel.scaling === SizeScaling.LARGE

                text: qsTr("&Large")
                onTriggered: gameController.setScaling(SizeScaling.LARGE);

            }

            //Used for resizing of MainFrame
            Connections {
                target: gameModel
                function onScalingChanged() { Manager.updateSizeScaling(parentWindow, passedStatusBar); }
            }
        }
    }

    Menu {
        //2nd menu "Extras"
        title: qsTr("&Extras")

        MenuItem {
            //MenuOption Statistics, opens Statistics window
            icon.source: "qrc:/images/flagTransparent.png";
            text: qsTr("&Statistics");

            onTriggered: {
                Manager.openWindow(parentWindow, "qrc:/windows/Statistics.qml");
            }
        }

        MenuItem {
            //MenuOption Help, opens Help window
            icon.source: "qrc:/images/questionTransparent.png";
            text: qsTr("&Help");

            onTriggered: {
                Manager.openWindow(parentWindow, "qrc:/windows/HelpWindow.qml");
            }
        }
    }

    //Disabled 3rd menu, used for showing the board size (columns * rows) and number of mines
    Menu {
        title: qsTr(gameModel.columns + "x" + gameModel.rows + "  " + gameModel.mineCount + " Mines");
        enabled: false;
    }
}
