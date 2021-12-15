
function resolveImage(cell) {
    let imageUrl = "qrc:/cellImages/cell.png";

    if(cell.flagged) {
        imageUrl = "qrc:/cellImages/flag.png";
    }

    // if revealed
    if(!cell.hidden) {
        if(cell.isBomb) {
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

function timeToString(secs) {
    if(secs === undefined) return '000';
    return (secs < 100 ? '0' : '') + (secs < 10 ? '0' : '') + secs;
}

// convert milliseconds to "minutes:seconds" format
// ms: milliseconds
function getMinutesFromMS(ms) {
//    if (ms < 0)
//        return "0:00";

    let minutes = Math.floor(ms / 60000);
    let seconds = Math.floor(((ms % 60000) / 1000));
    return minutes + ":" + (seconds < 10 ? '0' : '') + seconds;
}

function getMinutesFromSeconds(s) {
//    if (ms < 0)
//        return "0:00";

    let offset = 590;

    s = s + 590;

    let minutes = Math.floor(s / 60);
    let seconds = Math.floor(s % 60);
    return (minutes < 10 ? '0' : '') + minutes + ":" + (seconds < 10 ? '0' : '') + seconds;
}

function flagsToString(flags) {
    if(flags < 0) {
        return flags > -10 ? "-0" + Math.abs(flags) : flags;
    }
    else {
        return flags < 10 ? "00" + flags : (flags < 100 ? "0" + flags : flags);
    }
}

function getConfigurationString(rows, columns, mines) {
    let displayString = "";
    if(rows === 9 && columns === 9 && mines === 10) {
        displayString = "Beginner";
    }
    else if(rows === 16 && columns === 16 && mines === 40) {
        displayString = "Intermediate";
    }
    else if(rows === 16 && columns === 30 && mines === 99) {
        displayString = "Expert";
    }

    // default way of displaying
    if(displayString === "") {
        displayString = columns + "x" + rows + " - " + mines + " Mines";
    }
    
    return displayString;
}

