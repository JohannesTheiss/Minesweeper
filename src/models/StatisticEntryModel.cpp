#include "../../inc/models/StatisticEntryModel.h"

namespace models
{

StatisticEntryModel::StatisticEntryModel(const quint64 bestTime,
                const quint64 numberOfWins, 
                const quint64 numberOfDefeats, 
                const quint64 numberOfGamesPlayed, 
                const quint64 numberOfRows, 
                const quint64 numberOfColumns, 
                const quint64 numberOfMines, 
                QObject *parent)
    : QObject(parent),
      mBestTime(bestTime),
      mNumberOfWins(numberOfWins),
      mNumberOfDefeats(numberOfDefeats),
      mNumberOfGamesPlayed(numberOfGamesPlayed),
      mNumberOfRows(numberOfRows),
      mNumberOfColumns(numberOfColumns),
      mNumberOfMines(numberOfMines)
{
}

quint64 StatisticEntryModel::bestTime()
{
    return mBestTime;
}

quint64 StatisticEntryModel::numberOfWins()
{
    return mNumberOfWins;
}

quint64 StatisticEntryModel::numberOfDefeats()
{
    return mNumberOfDefeats;
}

quint64 StatisticEntryModel::numberOfGamesPlayed()
{
    return mNumberOfGamesPlayed;
}

quint64 StatisticEntryModel::numberOfRows()
{
    return mNumberOfRows;
}

quint64 StatisticEntryModel::numberOfColumns()
{
    return mNumberOfColumns;
}

quint64 StatisticEntryModel::numberOfMines()
{
    return mNumberOfMines;
}


} // namespace models
