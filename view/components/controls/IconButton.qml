import QtQuick 2.12
import QtQuick.Controls 2.5

import "qrc:/includes"

/* @parameters
 * id: identifier for Button                                                    (e.g. id: exitButton;)
 * icon.source: relative path to .png-File                                      (e.g. icon.source: "qrc:/check-ohne-Ring-color.png";)
 * hasBorder: boolean if the Button should have a Border with rounded corners   (e.g. hasBorder: true;)
 * toolTipText: text that should appear in the ToolTip of the Button            (e.g. toolTipText: "Exit";)
 * onClicked: { } code that should be run, when Button is clicked               (e.g. onClicked: { icon.color = "purple"; })
 */
Button {
    property alias hasBorder: rect.visible;             //deactivate Border around Button
//    property alias toolTipText: toolTipContent.text;    //pass text to ToolTip

    property int imageIndex: 0;

    width: Style.defaultWidth;
    height: Style.defaultHeight;
    icon.color: "transparent";                          //transparent so that the original color of the image is used

    //Icon should fill the Button
    icon.height: height;
    icon.width: width;
    padding: 0;

//    MouseArea {                                         //used for showing toolTips
//        id: ma;

//        anchors.fill: parent;
//        hoverEnabled: true;
//        onClicked: {                                    //pass click to Button
//            parent.onClicked();
//        }
//        propagateComposedEvents: true;
//    }

//    ToolTip {
//        id: toolTip;

//        delay: 1000;                                    //toolTip should show after a short delay

//        contentItem: Text{
//            id: toolTipContent;

//            color: Style.fontColor;
//        }

//        background: Rectangle {
//            border.color: "#808080";
//            color: "#c0c0c0";
//        }

////        visible: ma.containsMouse;                      //toolTip is shown, if MouseArea contains the Mouse
//        visible: false;
//    }

    //Background
    background: Rectangle {
        id: rect;

        anchors.fill: parent;
        color: "transparent";
        border.color: "grey";
        border.width: Style.borderWidth;
    }
}
