#include "../../inc/models/GameStateModel.h"

namespace models
{

GameStateModel::GameStateModel()
    : mFlagsLeft(0),
      mTimePlayed(0)
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
