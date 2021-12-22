pragma Singleton
import QtQuick 2.0

QtObject {
    // Colors
    property color counterBlue: "#0000ff"
    property color counterRed: "#ff0000"
    property color customWindowBorderLight: "#ffffff"
    property color customWindowBorderDark: "#808080"
    property color inputBoxBackground: "#f5f5f5"
    property color inputBoxBorder: "#595959"
    property color pauseColor: "#0000ff"
    property color popupBackground: "#c0c0c0"
    property color popupBorder: "#000000"
    property color popupRectBorder: "#595959"
    property color radioButton: "#595959"
    property color standardButtonBackground: "#f5f5f5"
    property color statisticsHeaderline: "#000000"
    property color textBoxBackground: "#c0c0c0"
    property color windowBackground: "#c0c0c0"

    // Text
    property string counterFont: "Consolas"
    property string font: "Arial"
    property color fontColor: "#000000"
    property double smallFontSize: 8.0
    property double standardFontSize: 10.0
    property double largeFontSize: 13.0
    property double pauseFontSize: 30.0

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
    property int menuButtonWidth: 30
    property int menuButtonHeight: 30
}
