import QtQuick 2.15
import QtQuick.Controls 2.5
import QtQuick.Window 2.15

import "qrc:/includes"

/* @parameters
 * id: identifier for InputBox                                                              (e.g. id: nameInput)
 * width: width of the InputBox                                                             (e.g. width: 100)
 * placeholderText: text that should be shown in the InputBox if nothing else is entered    (e.g. placeholderText: "Please enter x ...")
 */
TextField {
    height: Style.defaultHeight
    color: Style.fontColor
    font.family: Style.font
    font.pointSize: Style.textSize

    selectByMouse: true                                 //allows for text to be selected inside InputBox
    mouseSelectionMode: TextInput.SelectCharacters
    selectionColor: "grey"


    //Background
    background: Rectangle {
        anchors.fill: parent
        color: "#f5f5f5"/*Style.inputBoxBackground*/
        border.color: "#595959"
        border.width: Style.borderWidth
    }
}
