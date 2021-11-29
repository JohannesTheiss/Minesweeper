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


    Grid {
        id: grid
        anchors.fill: parent
        //cellWidth: 80; 
        //cellHeight: 80

        //columns: 7
        //rows: 13

        columns: 1
        rows: 14

       // model: backend.grid


        Repeater { 
            id: rep

            model: backend.grid

            /*
            TextLabel {
                id: mb

                text: "" + model.modelData
                //x: model.index * 10
            }
            */
           Button {
                text: "" + model.modelData
                onClicked: backend.lol(model.index)
            }

        }
    }

    
}
