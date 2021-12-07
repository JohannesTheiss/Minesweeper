import QtQuick 2.15
import QtQuick.Controls 2.5
import QtQuick.Window 2.12

import "qrc:/includes"

/* @parameters
 * id: identifier for TextBox                       (e.g. id: nameBox)
 * width: width of the TextBox                      (e.g. width: 100)
 * text: text that should be shown in the TextBox   (e.g. text: "Max Mustermann")
 */
TextField {
    id: textField

    height: Style.defaultHeight
    font.family: Style.font
    font.pointSize: Style.textSize
    color: Style.fontColor

    readOnly: true                              //nothing should be entered in TextBox

    //Background
    background: Rectangle {
        color: Style.textBoxBackground
        width: textField.width + 5;
    }
}

