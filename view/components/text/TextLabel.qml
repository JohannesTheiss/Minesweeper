import QtQuick 2.15

import "qrc:/includes"

/* @parameters
 * id: identifier for TextLabel                         (e.g. id: flagsLabel;)
 * width: width of the TextLabel                        (e.g. width: 100;)
 * text: text that should be shown in the TextLabel     (e.g. text: gameModel.flagCount;)
 */
Text {
    font.family: Style.font;
    font.pointSize: Style.largeFontSize;
    color: Style.fontColor;
    clip: true;
}
