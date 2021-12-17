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
        StatisticsController(observers::StatisticsObserver *statisticsObserver,
                QObject *parent = nullptr);

        ~StatisticsController();

    public slots:
        void loadStatistics();

        void submitStatistics(const quint64 numberOfRow,
                const quint64 numberOfColumns,
                const quint64 numberOfMines,
                const quint64 time,
                const bool win);

        void resetStatistics();

    private:
        void increaseNumberOfWins(models::StatisticEntryModel *statisticEntryModel);
        void increaseNumberOfDefeats(models::StatisticEntryModel *statisticEntryModel);
        void increaseNumberOfGamesPlayed(models::StatisticEntryModel *statisticEntryModel);

        void save(const QPair<quint64, models::StatisticEntryModel*> &indexEntryModelPair);
        void mapStatisticEntryModelToJsonObject(models::StatisticEntryModel *statisticEntryModel, 
                QJsonObject &jsonModel);
        void createDefaultGameModeStatistics();
        QPair<quint64, models::StatisticEntryModel*> createGameModeStatistics(models::GameMode &gameMode,
                const quint64 bestTime = 0,
                const quint64 numberOfWins = 0,
                const quint64 numberOfDefeats = 0,
                const quint64 numberOfGamesPlayed = 0);

        QHash<models::GameMode, QPair<quint64, models::StatisticEntryModel*>> mGameModeStatisticsMap;
        observers::StatisticsObserver *mStatisticsObserver;

        data::JsonManager *mJsonManager;
        const QString mJsonObjectName = "statistics";


};

} // namespace controllers

#endif // STATISTICSCONTROLLER_H
