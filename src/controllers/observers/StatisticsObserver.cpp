#include "../../../inc/controllers/observers/StatisticsObserver.h"

namespace observers
{

// <summary> Custom constructor for StatisticsObserver-objects
//           that builds the connection to a StatisticsModel-object</summary>
// <param name="statisticsModel"> Pointer to a StatisticsModel-object </param>
// <param name="parent"> Optional pointer to a parent object </param>
StatisticsObserver::StatisticsObserver(models::StatisticsModel *statisticsModel, QObject *parent)
    : QObject(parent),
      mStatisticsEntryModelList(&statisticsModel->statisticEntryModelListRef())
{
    initObserver(statisticsModel);
}

// <summary> Getter for value of member mStatisticsEntryModelList </summary>
// <returns> QList<models::StatisticEntryModel *> value of mStatisticsEntryModelList </returns>
QList<models::StatisticEntryModel *> StatisticsObserver::statisticEntryModelList() const
{
    return *mStatisticsEntryModelList;
}

// <summary> Getter for reference to member mStatisticsEntryModelList </summary>
// <returns> QList<models::StatisticEntryModel *> reference of mStatisticsEntryModelList </returns>
QList<models::StatisticEntryModel *> &StatisticsObserver::statisticEntryModelListRef()
{
    return *mStatisticsEntryModelList;
}

// <summary> Setter for member mStatisticsEntryModelList </summary>
// <param name="entryModelList"> QList<models::StatisticEntryModel *> value for "mStatisticsEntryModelList" </param>
// <returns> Nothing </returns>
void StatisticsObserver::setStatisticsEntryModelList(const QList<models::StatisticEntryModel *> entryModelList)
{
    emit updateModelEntryModelList(entryModelList);
}

// <summary> Slot for synchronising mStatisticsEntryModelList with StatisticsModel.mStatisticsModelEntryList </summary>
// <param name="entryModelList"> QList<models::StatisticEntryModel *> reference for "mStatisticsEntryModelList" </param>
// <returns> Nothing </returns>
void StatisticsObserver::updateObserverEntryModelList(QList<models::StatisticEntryModel *> &entryModelList)
{
    mStatisticsEntryModelList = &entryModelList;
}

// <summary> Establishes all connections between observer and model slots and signals
//           that are necessary for synchronising their data </summary>
// <param name="gameModel"> Pointer to StatisticsModel-object,
//                          which provides access to the interface of that object </param>
// <returns> Nothing </returns>
void StatisticsObserver::initObserver(const models::StatisticsModel *statisticsModel)
{
    QObject::connect(this, SIGNAL(updateModelEntryModelList(const QList<models::StatisticEntryModel *>)),
                     statisticsModel, SLOT(setStatisticsEntryModelList(const QList<models::StatisticEntryModel *>)));

    QObject::connect(statisticsModel, SIGNAL(statisticEntryModelListChanged(QList<models::StatisticEntryModel *> &)),
                     this, SLOT(updateObserverEntryModelList(QList<models::StatisticEntryModel *> &)));

    QObject::connect(this, SIGNAL(statisticEntryModelListChangedPassthrough(QList<models::StatisticEntryModel *> &)),
                     statisticsModel, SIGNAL(statisticEntryModelListChanged(QList<models::StatisticEntryModel *> &)));
}

} // namespace observers
