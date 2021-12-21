pragma Singleton
import QtQuick 2.0

QtObject {
    // Colors
    property color inputBoxBackground: "#f5f5f5"
    property color inputBoxBorder: "#595959"
    property color popupBackground: "#c0c0c0"
    property color popupBorder: "#000000"
    property color radioButton: "#595959"
    property color standardButtonBackground: "#f5f5f5"
    property color textBoxBackground: "#c0c0c0"

    // Text
    property string font: "Arial"
    property color fontColor: "#000000"
    property double smallFontSize: 8.0
    property double standardFontSize: 10.0
    property double largeFontSize: 13.0

    // Borders / Corners
    property int borderWidth: 1

    // Cell Width / Height
    property int cellWidth: 16
    property int cellHeight: 16

    // Object Width / Height (e.g. Buttons)
    property int defaultWidth: 40
    property int defaultHeight: 40
    property int standardButtonWidth: 100
    property int standardButtonHeight: 30
}
