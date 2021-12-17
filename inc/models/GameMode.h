#ifndef GAMEMODE_H
#define GAMEMODE_H

namespace models
{

class GameMode
{
    public:
        quint64 rows;
        quint64 columns;
        quint64 mines;

};

inline bool operator==(const GameMode &gameModeOne, const GameMode &gameModeTwo)
{
    return gameModeOne.rows == gameModeTwo.rows &&
            gameModeOne.columns == gameModeTwo.columns &&
            gameModeOne.mines == gameModeTwo.mines;
}

inline uint qHash(const models::GameMode &mode, uint seed) {
    return qHash(QString("%1:%2:%3").arg(mode.rows).arg(mode.columns).arg(mode.mines), seed);
}

}

#endif // GAMEMODE_H
