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
        // Custom constructor for StatisticsModel-objects
        StatisticsModel(QList<models::StatisticEntryModel *> statisticEntryModelList, 
                QObject *parent = nullptr);

        // Getter for value of member mStatisticEntryModelList
        QList<models::StatisticEntryModel *> statisticEntryModelList() const;

        // Getter for reference to member mStatisticEntryModelList
        QList<models::StatisticEntryModel *> &statisticEntryModelListRef();

    public slots:
        // Setter for member mStatisticEntryModelList
        void setStatisticsEntryModelList(const QList<models::StatisticEntryModel *> entryModelList);

    signals:
        void statisticEntryModelListChanged(QList<models::StatisticEntryModel *> &entryModelList);

    private:
        QList<models::StatisticEntryModel *> mStatisticEntryModelList;

};

} // namespace models

#endif // STATISTICSMODEL_H
