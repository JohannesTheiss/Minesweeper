#ifndef GAMESTATEMODEL_H
#define GAMESTATEMODEL_H

#include <QObject>

namespace models
{

class GameStateModel : public QObject
{

    Q_OBJECT

    Q_PROPERTY(quint64 flagsLeft READ flagsLeft NOTIFY flagsLeftChanged)
    Q_PROPERTY(quint64 timePlayed READ timePlayed NOTIFY timePlayedChanged)

    public:
        // delete default constructor
        GameStateModel() = delete;

        // custom constructor
        GameStateModel(const quint64 flagsLeft, const quint64 timePlayed);

        // default destructor
        ~GameStateModel() = default;

        // property getters
        quint64 flagsLeft();
        quint64 timePlayed();

        // property setters
        void setFlagsLeft(const quint64 flagsLeft);
        void setTimePlayed(const quint64 timePlayed);

    signals:
        void flagsLeftChanged();
        void timePlayedChanged();

    private:

        // properties
        quint64 mFlagsLeft;
        quint64 mTimePlayed;

};

} // namespace models
#endif // GAMESTATEMODEL_H
