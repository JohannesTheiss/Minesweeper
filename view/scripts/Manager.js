
function updateSizeScaling() {
    // ????
    mainWindow.sizeFactor = 0.5;

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
    mainWindow.sizeFactor = newScaling;

    // TODO may change this vars. to params of this function
    // set min width and height
    mainWindow.minimumWidth = Math.max(gameModel.columns * Style.cellWidth * sizeFactor, 340 * sizeFactor) + 24;
    mainWindow.minimumHeight = Math.max(gameModel.rows, 9) * Style.cellHeight * sizeFactor + statusBar.height + 36;

    // set max width and height
    mainWindow.maximumWidth = Math.max(gameModel.columns * Style.cellWidth * sizeFactor, 340 * sizeFactor) + 24;
    mainWindow.maximumHeight = Math.max(gameModel.rows, 9) * Style.cellHeight * sizeFactor + statusBar.height + 36;

    // set width and height
    mainWindow.width = Math.max(gameModel.columns * Style.cellWidth * sizeFactor, 340 * sizeFactor) + 24;
    mainWindow.height = Math.max(gameModel.rows, 9) * Style.cellHeight * sizeFactor + statusBar.height + 36;
}

function clickCell(model, mouseButton, cell) {
    gameController.startGame();
    switch(mouseButton)
    {
        case Qt.LeftButton:
            gameController.revealCell(model.index);
            if(model.modelData.isBomb) { 
                cell.buttonImage = "qrc:/cellImages/mineRed.png";
            }
            break;

        case Qt.MiddleButton:
        case Qt.RightButton:
            gameController.toggleFlagInCell(model.index);
            break;
    }
}

