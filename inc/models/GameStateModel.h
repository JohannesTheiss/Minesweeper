#ifndef GAMESTATEMODEL_H
#define GAMESTATEMODEL_H

#include <QObject>

namespace models
{

class GameStateModel : public QObject
{

    Q_OBJECT

    Q_PROPERTY(unsigned int flagsLeft READ flagsLeft NOTIFY flagsLeftChanged)
    Q_PROPERTY(unsigned int timePlayed READ timePlayed NOTIFY timePlayedChanged)

    public:
        // delete default constructor
        GameStateModel() = delete;

        // custom constructor
        GameStateModel(const unsigned int flagsLeft, const unsigned int timePlayed);

        // default destructor
        ~GameStateModel() = default;

        // property getters
        unsigned int flagsLeft();
        unsigned int timePlayed();

        // property setters
        void setFlagsLeft(const unsigned int flagsLeft);
        void setTimePlayed(const unsigned int timePlayed);

    signals:
        void flagsLeftChanged();
        void timePlayedChanged();

    private:

        // properties
        unsigned int mFlagsLeft;
        unsigned int mTimePlayed;

};

} // namespace models
#endif // GAMESTATEMODEL_H
