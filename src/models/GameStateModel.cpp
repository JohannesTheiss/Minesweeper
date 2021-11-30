#include "../../inc/models/GameStateModel.h"

namespace models
{

GameStateModel::GameStateModel(const unsigned int flagsLeft, const unsigned int timePlayed)
    : mFlagsLeft(flagsLeft),
      mTimePlayed(timePlayed)
{
}

unsigned int GameStateModel::flagsLeft()
{
    return mFlagsLeft;
}

unsigned int GameStateModel::timePlayed()
{
    return mTimePlayed;
}

void GameStateModel::setFlagsLeft(const unsigned int flagsLeft)
{
    mFlagsLeft = flagsLeft;
    emit flagsLeftChanged();
}

void GameStateModel::setTimePlayed(const unsigned int timePlayed)
{
    mTimePlayed = timePlayed;
    emit timePlayedChanged();
}

} // namespace models
