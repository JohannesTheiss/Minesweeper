import QtQuick 2.15

/* @parameters
 * id: identifier for CustomMouseArea                                                       (e.g. id: maBeginner;)
 * radioButton: the radioButton that the CustomMouseArea should check and be anchored to    (e.g. radioButton: beginnerRadio;)
 */
MouseArea {
    id: ma;

    property var radioButton;

    width: 430;                                     //needed width to cover the radioButton and the attached row
    height: radioButton.height;

    x: radioButton.x
    y: radioButton.y
    z: 90;

    onClicked: {
        if(!radioButton.checked) {                  //pass click and focus to radioButton
            radioButton.toggle();
            radioButton.onClicked();
            radioButton.forceActiveFocus();
        }
    }
}
