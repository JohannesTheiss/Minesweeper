#ifndef STATISTICSOBSERVER_H
#define STATISTICSOBSERVER_H

#include <QObject>

#include "../../models/StatisticEntryModel.h"
#include "../../models/StatisticsModel.h"

namespace observers
{

// observer-class for the StatisticsModel
class StatisticsObserver : public QObject
{
    Q_OBJECT

    public:
        StatisticsObserver(models::StatisticsModel *statisticsModel, QObject *parent = nullptr);

        ~StatisticsObserver() = default;

        // setters and getters as part of the interface
        // for any object to communicate with the model via the observer

        // getter methods
        QList<models::StatisticEntryModel *> statisticEntryModelList() const;
        QList<models::StatisticEntryModel *> &statisticEntryModelListRef();

        // setter methods
        void setStatisticsEntryModelList(const QList<models::StatisticEntryModel *> entryModelList);

    signals:
        // signals that trigger setter operation on the model
        void updateModelEntryModelList(const QList<models::StatisticEntryModel *> entryModelList);

        // passthrough signal to emit model list changed signal in order to update the view
        void statisticEntryModelListChangedPassthrough(QList<models::StatisticEntryModel *> &entryModelList);

    private slots:
        // slots that are called when values are updated in the model
        void updateObserverEntryModelList(QList<models::StatisticEntryModel *> &entryModelList);

    private:
        // initiates all connections between model and observer
        void initObserver(const models::StatisticsModel *statisticsModel);

        QList<models::StatisticEntryModel *> *mStatisticsEntryModelList;
};

} // namespace observers

#endif // STATISTICSOBSERVER_H
