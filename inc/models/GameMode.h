#ifndef GAMEMODE_H
#define GAMEMODE_H

#include <QObject>

namespace models
{

class GameMode
{
    public:
        quint64 rows; // number of rows
        quint64 columns; // number of columns
        quint64 mines; // number of mines

};

// <summary> Compare two GameMode-objects and return 'true' if they are the same </summary>
// <param name="gameModeOne"> The left hand side of the equation </param>
// <param name="gameModeTwo"> The right hand side of the equation </param>
// <returns> 'true' if gameModeOne == gameModeTwo else 'false' </returns>
inline bool operator==(const GameMode &gameModeOne, const GameMode &gameModeTwo)
{
    return gameModeOne.rows == gameModeTwo.rows &&
            gameModeOne.columns == gameModeTwo.columns &&
            gameModeOne.mines == gameModeTwo.mines;
}

// <summary> Custom hash function for the GameMode-object, is require for the QHash </summary>
// <param name="mode"> The GameMode that needs to be hashed </param>
// <param name="seed"> Seed to improve the hash function </param>
// <returns> 'true' if gameModeOne == gameModeTwo else 'false' </returns>
inline uint qHash(const models::GameMode &mode, uint seed) {
    return qHash(QString("%1:%2:%3").arg(mode.rows).arg(mode.columns).arg(mode.mines), seed);
}

}

#endif // GAMEMODE_H
