#ifndef STATISTICSMODEL_H
#define STATISTICSMODEL_H

#include <QObject>
#include <QList>

#include "StatisticEntryModel.h"

namespace models
{

struct GameMode
{
    quint64 rows;
    quint64 columns;
    quint64 mines;
};

class StatisticsModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QList<models::StatisticEntryModel *> statisticEntryModelList READ statisticEntryModelList NOTIFY statisticEntryModelListChanged)

    public:
        StatisticsModel(QList<models::StatisticEntryModel *> statisticEntryModelList, 
                QObject *parent = nullptr);

        QList<models::StatisticEntryModel *> statisticEntryModelList();


    signals:
        void statisticEntryModelListChanged();

    private:
        QList<models::StatisticEntryModel *> mStatisticEntryModelList;

};

} // namespace models

#endif // STATISTICSMODEL_H
