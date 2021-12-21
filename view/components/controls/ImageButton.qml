import QtQuick 2.15
import QtQuick.Controls 2.5

import "qrc:/includes"

/* @parameters
 * id: identifier for ImageButton                                           (e.g. id: newButton;)
 * buttonImage: relative path to .png-File                                  (e.g. buttonImage: "qrc:/images/newButton.png";)
 * onClicked: { } code that should be run, when ImageButton is clicked      (e.g. onClicked: { icon.color = "purple"; })
 */
Button {
    property alias buttonImage: image.source;

    //Background
    background: Image {
        id: image;
    }
}
