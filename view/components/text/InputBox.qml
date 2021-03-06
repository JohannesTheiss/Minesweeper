import QtQuick 2.15
import QtQuick.Controls 2.5
import QtQuick.Window 2.15

import "qrc:/includes"

/* @parameters
 * id: identifier for InputBox                                                              (e.g. id: widthInput;)
 * width: width of the InputBox                                                             (e.g. width: 100;)
 * placeholderText: text that should be shown in the InputBox if nothing else is entered    (e.g. placeholderText: gameModel.columns;)
 */
TextField {
    height: Style.defaultHeight
    color: Style.fontColor
    font.family: Style.font
    font.pointSize: Style.largeFontSize

    selectByMouse: true                                 //allows for text to be selected inside InputBox
    mouseSelectionMode: TextInput.SelectCharacters
    selectionColor: "grey"

    //Background
    background: Rectangle {
        anchors.fill: parent
        color: Style.inputBoxBackground;
        border.color: Style.inputBoxBorder;
        border.width: Style.borderWidth
    }
}
