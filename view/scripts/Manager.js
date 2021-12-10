
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
    mainWindow.minimumWidth = Math.max(gameModel.columns * Style.cellWidth * sizeFactor, 310 * sizeFactor) + 24;
    mainWindow.minimumHeight = gameModel.rows * Style.cellHeight * sizeFactor + statusBar.height + 36;

    // set max width and height
    mainWindow.maximumWidth = Math.max(gameModel.columns * Style.cellWidth * sizeFactor, 310 * sizeFactor) + 24;
    mainWindow.maximumHeight = gameModel.rows * Style.cellHeight * sizeFactor + statusBar.height + 36;

    // set width and height
    mainWindow.width = Math.max(gameModel.columns * Style.cellWidth * sizeFactor, 310 * sizeFactor) + 24;
    mainWindow.height = gameModel.rows * Style.cellHeight * sizeFactor + statusBar.height + 36;
}

