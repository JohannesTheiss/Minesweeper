import QtQuick 2.15
import QtQuick.Controls 2.5

import "qrc:/includes"

/* @parameters
 * id: identifier for Button                                                    (e.g. id: exitButton;)
 * icon.source: relative path to .png-File                                      (e.g. icon.source: "qrc:/check-ohne-Ring-color.png";)
 * onClicked: { } code that should be run, when Button is clicked               (e.g. onClicked: { icon.color = "purple"; })
 */
Button {
    property alias buttonImage: image.source;

    visible: true;

//    MouseArea {                                         //used for showing toolTips
//        id: ma;

//        anchors.fill: parent;
//        hoverEnabled: true;
//        onClicked: {                                    //pass click to Button
//            parent.onClicked();
//        }
//    }

    //Background
    background: Image {
        id: image;
    }
}
