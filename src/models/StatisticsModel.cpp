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

QList<models::StatisticEntryModel *> *StatisticsModel::statisticEntryModelListRef()
{
    return &mStatisticEntryModelList;
}

void StatisticsModel::appendToEntryList(models::StatisticEntryModel* statisticEntryModel)
{
    mStatisticEntryModelList.append(statisticEntryModel);
    emit statisticEntryModelListChanged();
}


} // namespace models

