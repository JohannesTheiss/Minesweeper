#ifndef STATISTICSCONTROLLER_H
#define STATISTICSCONTROLLER_H

#include <QObject>
#include <QHash> 
#include <QPair> 
#include <QString> 

#include <QDebug>

#include "../data/JsonManager.h"

#include "../models/StatisticsModel.h"
#include "../models/StatisticEntryModel.h"
#include "../models/GameMode.h"

namespace controllers
{

class StatisticsController : public QObject
{
    Q_OBJECT

    public:
        StatisticsController(models::StatisticsModel *statisticsModel,
                QObject *parent = nullptr);

        ~StatisticsController();

    public slots:
        void loadStatistics();

        void submitStatistics(const quint64 numberOfRow,
                const quint64 numberOfColumns,
                const quint64 numberOfMines,
                const quint64 time,
                const bool win);

    private:
        void increaseNumberOfWins(models::StatisticEntryModel *statisticEntryModel);
        void increaseNumberOfDefeats(models::StatisticEntryModel *statisticEntryModel);
        void increaseNumberOfGamesPlayed(models::StatisticEntryModel *statisticEntryModel);

        void save(const QPair<quint64, models::StatisticEntryModel*> &indexEntryModelPair);

        QHash<models::GameMode, QPair<quint64, models::StatisticEntryModel*>> mGameModeStatisticsMap;
        models::StatisticsModel *mStatisticsModel;

        data::JsonManager *mJsonManager;
        const QString mJsonObjectName = "statistics";


};

} // namespace controllers

#endif // STATISTICSCONTROLLER_H
