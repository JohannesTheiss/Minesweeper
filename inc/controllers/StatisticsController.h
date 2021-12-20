#ifndef STATISTICSCONTROLLER_H
#define STATISTICSCONTROLLER_H

#include <QObject>
#include <QHash> 
#include <QPair> 
#include <QString> 

#include <QDebug>

#include "../data/JsonManager.h"

#include "observers/StatisticsObserver.h"

#include "../models/StatisticEntryModel.h"
#include "../models/StatisticsModel.h"
#include "../models/GameMode.h"

namespace controllers
{

class StatisticsController : public QObject
{
    Q_OBJECT

    public:
        /*
         * Custom constructor for StatisticsController-objects
         * it creates the JsonManager and loads the statistics
         */
        StatisticsController(observers::StatisticsObserver *statisticsObserver,
                QObject *parent = nullptr);

        /*
         * Custom destructor for StatisticsController-objects
         * it deletes the JsonManager
         */
        ~StatisticsController();

    public slots:

        /*
         * Load all statistics from JSON
         * and if it is empty, create the default game mode statistics
         */
        void loadStatistics();

        // Create a new statistic with given the information
        void createStatistic(const quint64 numberOfRow,
                const quint64 numberOfColumns,
                const quint64 numberOfMines,
                const quint64 time,
                const bool win);

        // Reset all statistic and create the default game mode statistics
        void resetStatistics();

    signals:
        // Emits that the games is ended and the statistics are created
        void gameEnded(const quint64 bestTime, const bool won);
    
    private:
        // Increase the number of wins by one
        void increaseNumberOfWins(models::StatisticEntryModel *statisticEntryModel);

        // Increase the number of defeats by one
        void increaseNumberOfDefeats(models::StatisticEntryModel *statisticEntryModel);

        // Increase the number of games played by one
        void increaseNumberOfGamesPlayed(models::StatisticEntryModel *statisticEntryModel);

        // Save a new statistics object to JSON 
        void save(const QPair<quint64, models::StatisticEntryModel*> &indexEntryModelPair);

        // Maps the StatisticEntryModel to a QJsonObject
        void mapStatisticEntryModelToJsonObject(models::StatisticEntryModel *statisticEntryModel, 
                QJsonObject &jsonModel);

        /*
         * Create the default game mode statistic,
         * for Beginner, Intermediate and Expert
         */
        void createDefaultGameModeStatistics();

        // Create a new game mode statistic with given information 
        QPair<quint64, models::StatisticEntryModel*> createGameModeStatistics(models::GameMode &gameMode,
                const quint64 bestTime = 0,
                const quint64 numberOfWins = 0,
                const quint64 numberOfDefeats = 0,
                const quint64 numberOfGamesPlayed = 0);

        /*
         * The GameMode-Statistics-Map is a hash table with:
         *     Key: GameMode := {numberOfRow, numberOfColumns, numberOfMines}
         *     Value: Is a QPair with:
         *         FIRST:  the index of the statisticEntryModel within the JSON-Array 
         *                 (so that it can be changed fast)
         *         SECOND: a pointer to the statisticEntryModel itself as it is displayed on the frontend
         */
        QHash<models::GameMode, QPair<quint64, models::StatisticEntryModel*>> mGameModeStatisticsMap;

        // StatisticsObserver for the StatisticsModel
        observers::StatisticsObserver *mStatisticsObserver;

        // JsonManager properties
        data::JsonManager *mJsonManager;
        const QString mJsonObjectName = "statistics";
};

} // namespace controllers

#endif // STATISTICSCONTROLLER_H
