#include "../../inc/controllers/StatisticsController.h"


namespace controllers
{


StatisticsController::StatisticsController(models::StatisticsModel *statisticsModel,
    QObject *parent)
    : QObject(parent),
      mStatisticsModel(statisticsModel)
{
    mJsonManager = new data::JsonManager("statistics.json");


    // load from json

    // build the HashMap
    
    models::StatisticEntryModel *sem = new models::StatisticEntryModel(
                123,
                345, 
                12, 
                100, 
                1, 
                2, 
                3, 
                this);

    models::GameMode gm({1, 2, 3});

    //QHash<models::GameMode, QPair<quint64, models::StatisticEntryModel*>> dm;
    QHash<models::GameMode, int> dm;
    //dm[gm] = 1;

}

void StatisticsController::loadStatistics()
{

}

void StatisticsController::submitStatistics(const quint64 numberOfRow,
    const quint64 numberOfColumns,
    const quint64 numberOfMines,
    const quint64 time,
    const bool win)
{
    qDebug() << "submit statisticsModel";
    if(win) 
    {

    }
    else
    {

    }
}


} // namespace controllers


