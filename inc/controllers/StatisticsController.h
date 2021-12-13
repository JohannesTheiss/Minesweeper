#ifndef STATISTICSCONTROLLER_H
#define STATISTICSCONTROLLER_H

#include <QObject>
#include <QHash> 
#include <QPair> 

#include <QDebug>

#include "../data/JsonManager.h"

#include "../models/StatisticsModel.h"
#include "../models/StatisticEntryModel.h"

namespace controllers
{

class StatisticsController : public QObject
{
    Q_OBJECT

    public:
        StatisticsController(models::StatisticsModel *statisticsModel,
                QObject *parent = nullptr);

    public slots:
        void loadStatistics();

        void submitStatistics(const quint64 numberOfRow,
                const quint64 numberOfColumns,
                const quint64 numberOfMines,
                const quint64 time,
                const bool win);

    signals:

    private:

        inline uint qHash(models::GameMode &mode) {
            return qHash(QString(mode.rows));
        }

        QHash<models::GameMode, QPair<quint64, models::StatisticEntryModel*>> mGameModeStatisticsMap;
        models::StatisticsModel *mStatisticsModel;

        data::JsonManager *mJsonManager;
        const QString mJsonObjectName = "statistics";


};

} // namespace controllers

#endif // STATISTICSCONTROLLER_H
