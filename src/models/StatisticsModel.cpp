#include "../../inc/models/StatisticsModel.h"

namespace models
{

StatisticsModel::StatisticsModel(QList<models::StatisticEntryModel *> statisticEntryModelList,
    QObject *parent)
  : QObject(parent),
    mStatisticEntryModelList(statisticEntryModelList)
{
}

QList<models::StatisticEntryModel *> StatisticsModel::statisticEntryModelList()
{
    return mStatisticEntryModelList;
}


} // namespace models

