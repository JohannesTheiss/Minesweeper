import QtQuick 2.12

import "qrc:/includes"

/* @parameters
 * id: identifier for TextLabel                         (e.g. id: nameLabel;)
 * width: width of the TextLabel                        (e.g. width: 100;)
 * text: text that should be shown in the TextLabel     (e.g. text: "Name:";)
 */
Text {
    height: Style.defaultHeight;
    font.family: Style.font;
    font.pointSize: Style.textSize;
    color: Style.fontColor;
    verticalAlignment: Text.AlignVCenter;
    clip: true;
    elide: Text.ElideRight;
}
