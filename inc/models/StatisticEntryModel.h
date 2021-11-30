#ifndef STATISTICENTRYMODEL_H
#define STATISTICENTRYMODEL_H

#include <QtGlobal>
#include <QObject>

namespace models
{

class StatisticEntryModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(quint64 bestTime READ  bestTime CONSTANT)
    Q_PROPERTY(quint64 numberOfWins READ numberOfWins CONSTANT)
    Q_PROPERTY(quint64 numberOfDefeats READ numberOfDefeats CONSTANT)
    Q_PROPERTY(quint64 numberOfGamesPlayed READ numberOfGamesPlayed CONSTANT)
    Q_PROPERTY(quint64 numberOfRows READ numberOfRows CONSTANT)
    Q_PROPERTY(quint64 numberOfColumns READ numberOfColumns CONSTANT)
    Q_PROPERTY(quint64 numberOfMines READ numberOfMines CONSTANT)

    public:
        // delete default constructor
        StatisticEntryModel() = delete;

        // custom constructor
        StatisticEntryModel(const quint64 bestTime,
                const quint64 numberOfWins, 
                const quint64 numberOfDefeats, 
                const quint64 numberOfGamesPlayed, 
                const quint64 numberOfRows, 
                const quint64 numberOfColumns, 
                const quint64 numberOfMines, 
                QObject *parent = nullptr);

        quint64 bestTime();
        quint64 numberOfWins();
        quint64 numberOfDefeats();
        quint64 numberOfGamesPlayed();
        quint64 numberOfRows();
        quint64 numberOfColumns();
        quint64 numberOfMines();

    private:
        // highscore time
        quint64 mBestTime;

        // Global statistics
        quint64 mNumberOfWins;
        quint64 mNumberOfDefeats;
        quint64 mNumberOfGamesPlayed;

        // Game settings
        quint64 mNumberOfRows;
        quint64 mNumberOfColumns;
        quint64 mNumberOfMines;
};

} // namespace models

#endif // STATISTICENTRYMODEL_H
