
function resolveImage(cell) {
    let imageUrl = "qrc:/cellImages/cell.png";

    if(cell.flagged) {
        imageUrl = "qrc:/cellImages/flag.png";
    }

    // if revealed
    if(!cell.hidden) {
        if(cell.isBomb) {
            testTimer.running = false;
            imageUrl = "qrc:/cellImages/mine.png";
        }
        else {
            switch(cell.surroundingBombs) {
                case 0:
                    imageUrl = "qrc:/cellImages/empty.png";
                    break;
                case 1:
                    imageUrl = "qrc:/cellImages/one.png";
                    break;
                case 2:
                    imageUrl = "qrc:/cellImages/two.png";
                    break;
                case 3:
                    imageUrl = "qrc:/cellImages/three.png";
                    break;
                case 4:
                    imageUrl = "qrc:/cellImages/four.png";
                    break;
                case 5:
                    imageUrl = "qrc:/cellImages/five.png";
                    break;
                case 6:
                    imageUrl = "qrc:/cellImages/six.png";
                    break;
                case 7:
                    imageUrl = "qrc:/cellImages/seven.png";
                    break;
                case 8:
                    imageUrl = "qrc:/cellImages/eight.png";
                    break;
            }
        }
    }

    return imageUrl;
}
