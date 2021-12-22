#include "../../inc/models/StatisticEntryModel.h"

namespace models
{

// <summary> Custom constructor for StatisticEntryModel </summary>
// <param name="bestTime"> quint64 number of seconds that narks the best time
//                         a user needed to finish the game </param>
// <param name="numberOfWins"> quint64 number of wins in the current configuration </param>
// <param name="numberOfDefeats"> quint64 number of defeats in the current configuration </param>
// <param name="numberOfGamesPlayed"> quint64 number of games played in the current configuration </param>
// <param name="numberOfRows"> quint64 number of rows </param>
// <param name="numberOfColumns"> quint64 number of columns </param>
// <param name="numberOfMines"> quint64 number of mines </param>
// <param name="parent"> Optional pointer to a parent object </param>
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

// <summary> Getter for member mBestTime </summary>
// <returns> quint64 mBestTime </returns>
quint64 StatisticEntryModel::bestTime()
{
    return mBestTime;
}

// <summary> Getter for member mNumberOfWins </summary>
// <returns> quint64 mNumberOfWins </returns>
quint64 StatisticEntryModel::numberOfWins()
{
    return mNumberOfWins;
}

// <summary> Getter for member mNumberOfDefeats </summary>
// <returns> quint64 mNumberOfMines </returns>
quint64 StatisticEntryModel::numberOfDefeats()
{
    return mNumberOfDefeats;
}

// <summary> Getter for member mNumberOfGamesPlayed </summary>
// <returns> quint64 mNumberOfGamesPlayed </returns>
quint64 StatisticEntryModel::numberOfGamesPlayed()
{
    return mNumberOfGamesPlayed;
}

// <summary> Getter for member mNumberOfRows </summary>
// <returns> quint64 mNumberOfRows </returns>
quint64 StatisticEntryModel::numberOfRows()
{
    return mNumberOfRows;
}

// <summary> Getter for member mNumberOfColumns </summary>
// <returns> quint64 mNumberOfColumns </returns>
quint64 StatisticEntryModel::numberOfColumns()
{
    return mNumberOfColumns;
}

// <summary> Getter for member mNumberOfMines </summary>
// <returns> quint64 mNumberOfMines </returns>
quint64 StatisticEntryModel::numberOfMines()
{
    return mNumberOfMines;
}

// <summary> Setter for member mBestTime </summary>
// <param name="bestTime"> quint64 value for "mBestTime" </param>
// <returns> Nothing </returns>
void StatisticEntryModel::setBestTime(const quint64 bestTime)
{
    mBestTime = bestTime;
    emit bestTimeChanged();
}

// <summary> Setter for member mNumberOfWins </summary>
// <param name="numberOfWins"> quint64 value for "mNumberOfWins" </param>
// <returns> Nothing </returns>
void StatisticEntryModel::setNumberOfWins(const quint64 numberOfWins)
{
    mNumberOfWins = numberOfWins;
    emit numberOfWinsChanged();
}

// <summary> Setter for member mNumberOfDefeats </summary>
// <param name="numberOfDefeats"> quint64 value for "mNumberOfDefeats" </param>
// <returns> Nothing </returns>
void StatisticEntryModel::setNumberOfDefeats(const quint64 numberOfDefeats)
{
    mNumberOfDefeats = numberOfDefeats;
    emit numberOfDefeatsChanged();
}

// <summary> Setter for member mNumberOfGamesPlayed </summary>
// <param name="numberOfGamesPlayed"> quint64 value for "mNumberOfGamesPlayed" </param>
// <returns> Nothing </returns>
void StatisticEntryModel::setNumberOfGamesPlayed(const quint64 numberOfGamesPlayed)
{
    mNumberOfGamesPlayed = numberOfGamesPlayed;
    emit numberOfGamesPlayedChanged();
}


} // namespace models
