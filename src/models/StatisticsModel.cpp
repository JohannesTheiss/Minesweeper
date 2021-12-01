#include "../../inc/models/StatisticsModel.h"

namespace models
{

StatisticsModel::StatisticsModel(QList<QObject *> statisticEntryModelList, QObject *parent)
  : QObject(parent),
    mStatisticEntryModelList(statisticEntryModelList)
{
}

QList<QObject *> StatisticsModel::statisticEntryModelList()
{
    return mStatisticEntryModelList;
}


} // namespace models

