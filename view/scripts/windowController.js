
function openWindow(parent, qmlFile, params = undefined)
{
    let component = Qt.createComponent(qmlFile);
    if (params === undefined) {
        let w = component.createObject(parent);
        w.show();
    }
    else {
        let w = component.createObject(parent, params);
        w.show();
    }
}
