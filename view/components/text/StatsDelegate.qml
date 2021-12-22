import QtQuick 2.15

import "qrc:/includes"

import "qrc:/scripts/Adapter.js" as Adapter

/* @parameters
 * headerR: the headerRow in Statistics window, used to get headerRow.spacing       (e.g. headerR: headerRow;)
 * modeL: the modeLabel in headerRow                                                (e.g. modeL: modeLabel;)
 * timeL: the timeLabel in headerRow                                                (e.g. timeL: timeLabel;)
 * gamesL: the gamesLabel in headerRow                                              (e.g. gamesL: gamesLabel;)
 * wonL: the wonLabel in headerRow                                                  (e.g. wonL: wonLabel;)
 */
Item {
    id: statsDelegate;

    //properties used to properly anchor the labels below the corresponding headers
    property var headerR;
    property var modeL;
    property var timeL;
    property var gamesL;
    property var wonL;

    height: modeStat.height;

    TextLabel {
        id: modeStat;

        font.pointSize: Style.standardFontSize;
        text: Adapter.getConfigurationString(model.modelData.numberOfRows, model.modelData.numberOfColumns, model.modelData.numberOfMines);
    }

    TextLabel {
        id: timeStat;

        x: modeL.width + headerR.spacing

        font.pointSize: Style.standardFontSize;
        text: model.modelData.numberOfWins !== 0 ? Adapter.getMinutesFromSeconds(model.modelData.bestTime) : "-";
    }

    TextLabel {
        id: gamesStat;

        x: timeStat.x + timeL.width + headerR.spacing;

        font.pointSize: Style.standardFontSize;
        text: model.modelData.numberOfGamesPlayed;
    }

    TextLabel {
        id: wonStat;

        x: gamesStat.x + gamesL.width + headerR.spacing;

        font.pointSize: Style.standardFontSize;
        text: model.modelData.numberOfWins;
    }

    TextLabel {
        id: lostStat;

        x: wonStat.x + wonL.width + headerR.spacing;

        font.pointSize: Style.standardFontSize;
        text: model.modelData.numberOfDefeats;
    }
}
