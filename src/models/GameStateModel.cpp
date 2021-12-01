#include "../../inc/models/GameStateModel.h"

namespace models
{

GameStateModel::GameStateModel(const quint64 flagsLeft, const quint64 timePlayed)
    : mFlagsLeft(flagsLeft),
      mTimePlayed(timePlayed)
{
}

quint64 GameStateModel::flagsLeft()
{
    return mFlagsLeft;
}

quint64 GameStateModel::timePlayed()
{
    return mTimePlayed;
}

void GameStateModel::setFlagsLeft(const quint64 flagsLeft)
{
    mFlagsLeft = flagsLeft;
    emit flagsLeftChanged();
}

void GameStateModel::setTimePlayed(const quint64 timePlayed)
{
    mTimePlayed = timePlayed;
    emit timePlayedChanged();
}

} // namespace models
