#include "../../inc/models/StatisticsModel.h"

namespace models
{

StatisticsModel::StatisticsModel(QList<models::StatisticEntryModel *> statisticEntryModelList,
    QObject *parent)
  : QObject(parent),
    mStatisticEntryModelList(statisticEntryModelList)
{
}

QList<models::StatisticEntryModel *> StatisticsModel::statisticEntryModelList() const
{
    return mStatisticEntryModelList;
}

QList<models::StatisticEntryModel *> &StatisticsModel::statisticEntryModelListRef()
{
    return mStatisticEntryModelList;
}

void StatisticsModel::setStatisticsEntryModelList(const QList<models::StatisticEntryModel *> entryModelList)
{
    mStatisticEntryModelList = entryModelList;
    emit statisticEntryModelListChanged(mStatisticEntryModelList);
}


} // namespace models

