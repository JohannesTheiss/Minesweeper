pragma Singleton
import QtQuick 2.0

QtObject {
    // Colors
    property color buttonBackground: "#ededed"
    property color buttonBorder: "#000000"
    property color dragSymbolColor: "#f5f5f5"
    property color highlightColorLight: "#4d4d4d"
    property color highlightColorStrong: "#747474"
    property color listElementBackground: "#242424"
    property color listElementBorder: "#191414"
    property color listHeaderBackground: "#000000"
    property color listHeaderBorder: "#181818"
    property color menuBackground: "#4d4d4d"
    property color menuHighlight: "#242424"
    property color messageBoxBackground: "#ef6f6c"
    property color queueBackground: "#181818"
    property color queueHeaderLineColor: "#1ed760"
    property color searchBoxBackground: "#181818"
    property color searchBoxBorder: "#242424"
    property color searchBoxSelection: "#f5f5f5"
    property color separatorColor: "#1ed760"
    property color sliderBackground: "#bdbebf"
    property color songListBackground: "#121212"
    property color songSliderColor: "#1ed760"
    property color toolTipBackground: "#1ed760"
    property color volumeSliderColor: "#f5f5f5"

    // Text
    property string font: "Arial"
    property color fontColor: "black"
    property double textSize: 13.0

    // Borders / Corners
    property int borderRadius: 8
    property int borderWidth: 1

    // Object Width / Height (e.g. Buttons, SongElements)
    property int defaultWidth: 40
    property int defaultHeight: 40

    // Anchors
    property int percentageEdge: 16
}
