#ifndef STATISTICSMODEL_H
#define STATISTICSMODEL_H

#include <QObject>
#include <QList>

#include "StatisticEntryModel.h"

namespace models
{

class StatisticsModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QList<models::StatisticEntryModel *> statisticEntryModelList READ statisticEntryModelList NOTIFY statisticEntryModelListChanged)

    public:
        StatisticsModel(QList<models::StatisticEntryModel *> statisticEntryModelList, 
                QObject *parent = nullptr);

        QList<models::StatisticEntryModel *> statisticEntryModelList() const;
        QList<models::StatisticEntryModel *> &statisticEntryModelListRef();

    public slots:
        void setStatisticsEntryModelList(const QList<models::StatisticEntryModel *> entryModelList);

    signals:
        void statisticEntryModelListChanged(QList<models::StatisticEntryModel *> &entryModelList);

    private:
        QList<models::StatisticEntryModel *> mStatisticEntryModelList;

};

} // namespace models

#endif // STATISTICSMODEL_H
