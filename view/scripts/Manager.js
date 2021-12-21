
function updateSizeScaling(passedWindow, passedStatusBar) {
    // get the new scaling factor
    let newScaling = 1;
    switch(gameModel.scaling) {
        case SizeScaling.SMALL:
            newScaling = 1.0;
            break;

        case SizeScaling.MEDIUM:
            newScaling = 1.5;
            break;

        case SizeScaling.LARGE:
            newScaling = 2.0;
            break;
    }

    // set new windows scaling
    passedWindow.sizeFactor = newScaling;

    resizeWindow(passedWindow, passedStatusBar);
}

function clickCell(model, mouseButton, cell) {
    gameController.startGame();
    switch(mouseButton)
    {
        case Qt.LeftButton:
            if(!model.modelData.flagged) {
                gameController.revealCell(model.index);

                if(model.modelData.isBomb) { 
                    cell.buttonImage = "qrc:/cellImages/mineRed.png";
                }
            }
            break;

        case Qt.MiddleButton:
        case Qt.RightButton:
            gameController.toggleFlagInCell(model.index);
            break;
    }
}

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

function resizeWindow(passedWindow, passedStatusBar)
{
    const newWidth = Math.max(gameModel.columns * Style.cellWidth * passedWindow.sizeFactor, 340 * passedWindow.sizeFactor) + 24;
    const newHeight = Math.max(gameModel.rows, 9) * Style.cellHeight * passedWindow.sizeFactor + passedStatusBar.height + 36;

    passedWindow.minimumWidth = passedWindow.maximumWidth = newWidth;
    passedWindow.minimumHeight = passedWindow.maximumHeight = newHeight;

    passedWindow.width = newWidth;
    passedWindow.height = newHeight;
}

function resetForNewGame(passedWindow)
{
    passedWindow.isGameWon = false;
    passedWindow.hideWinPopup = false;
}
