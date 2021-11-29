import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQml.Models 2.12
import QtQuick.Window 2.12
import QtQuick.Dialogs 1.0

import "qrc:/text"

Window {
    id: mainWindow;

    property int numOfColumns: 3;

    title: "Minesweeper";
    visible: true;
    width: 1400;
    height: 805;

    //Minimum Size
    minimumWidth: 1400;
    minimumHeight: 805;

    TextLabel {
        text: "Minesweeper lol"
    }
}
