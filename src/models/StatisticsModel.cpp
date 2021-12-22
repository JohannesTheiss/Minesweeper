#include "../../inc/models/StatisticsModel.h"

namespace models
{

// <summary> Custom constructor for StatisticsModel-objects </summary>
// <param name="statisticEntryModelList"> QList of StatisticEntryModel pointers </param>
// <param name="parent"> Optional pointer to a parent object </param>
StatisticsModel::StatisticsModel(QList<models::StatisticEntryModel *> statisticEntryModelList,
    QObject *parent)
  : QObject(parent),
    mStatisticEntryModelList(statisticEntryModelList)
{
}

// <summary> Getter for value of member mStatisticEntryModelList </summary>
// <returns> QList<models::StatisticEntryModel *> value of mStatisticsEntryModelList </returns>
QList<models::StatisticEntryModel *> StatisticsModel::statisticEntryModelList() const
{
    return mStatisticEntryModelList;
}

// <summary> Getter for reference to member mStatisticEntryModelList </summary>
// <returns> QList<models::StatisticEntryModel *> reference of mStatisticsEntryModelList </returns>
QList<models::StatisticEntryModel *> &StatisticsModel::statisticEntryModelListRef()
{
    return mStatisticEntryModelList;
}

// <summary> Setter for member mStatisticEntryModelList </summary>
// <param name="entryModelList"> QList<models::StatisticEntryModel *> value for "mStatisticEntryModelList" </param>
// <returns> Nothing </returns>
void StatisticsModel::setStatisticsEntryModelList(const QList<models::StatisticEntryModel *> entryModelList)
{
    mStatisticEntryModelList = entryModelList;
    emit statisticEntryModelListChanged(mStatisticEntryModelList);
}


} // namespace models

