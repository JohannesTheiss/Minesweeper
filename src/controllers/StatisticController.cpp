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
    
    //models::StatisticEntryModel *sem = new models::StatisticEntryModel(
                //123,
                //345, 
                //12, 
                //100, 
                //1, 
                //2, 
                //3, 
                //this);

    //models::GameMode gm({1, 2, 3});
    //qDebug() << "rows: " << gm.columns;

    //QHash<models::GameMode, QPair<quint64, models::StatisticEntryModel*>> dm;
    //mGameModeStatisticsMap[gm] = qMakePair(187, sem);

    //models::GameMode gm1({1, 2, 3});
    //qDebug() << "get: " << mGameModeStatisticsMap[gm1].second->bestTime();

    //qDebug() << QString::number(gm.rows, gm.columns);
    //QString lol = QString("%1:%2:%3").arg(88).arg(77).arg(99);
}

void StatisticsController::loadStatistics()
{

}

void StatisticsController::submitStatistics(const quint64 numberOfRow,
    const quint64 numberOfColumns,
    const quint64 numberOfMines,
    const quint64 timePlayed,
    const bool win)
{
    qDebug() << "submit statisticsModel: ";
    // build the key
    models::GameMode key({numberOfRow, numberOfColumns, numberOfMines});

    QHash<models::GameMode, 
        QPair<quint64, models::StatisticEntryModel*>>::const_iterator 
            indexEntryModelPairIterator = mGameModeStatisticsMap.find(key);

    if(win) 
    {
        // the game is won
        
        // check if this configuration doesn't exists
        if(indexEntryModelPairIterator == mGameModeStatisticsMap.end())
        {  
            // create new statistics entry
            models::StatisticEntryModel *statisticEntryModel = new models::StatisticEntryModel(
                        timePlayed, // best time
                        1, // wins
                        0, // defeats
                        1, // gamesPlayed
                        numberOfRow, // number of rows
                        numberOfColumns, // number of columns
                        numberOfMines, // number of mines
                        this // parent of this object
                        );

            // append to displayed list
            mStatisticsModel->statisticEntryModelListRef()->append(statisticEntryModel);
            
            quint64 index = mStatisticsModel->statisticEntryModelListRef()->size() - 1;

            // append to HashMap
            mGameModeStatisticsMap.insert(key, qMakePair(index, statisticEntryModel));

            qDebug() << "won index: " << index << " " << key.rows << " " << key.columns << " " << key.mines;
        }
        else
        {
            // increase the number of wins
            // and the number of games played 
            QPair<quint64, models::StatisticEntryModel*> indexEntryModelPair = indexEntryModelPairIterator.value();
            increaseNumberOfWins(indexEntryModelPair.second);
            increaseNumberOfGamesPlayed(indexEntryModelPair.second);

            // update the best time if it is better
            if(timePlayed < indexEntryModelPair.second->bestTime())
            {
                indexEntryModelPair.second->setBestTime(timePlayed); 
            }
        }

    }
    else
    {
        // the game is lost
        //
        // check if this configuration doesn't exists
        if(indexEntryModelPairIterator == mGameModeStatisticsMap.end())
        {  
            // create new statistics entry
            models::StatisticEntryModel *statisticEntryModel = new models::StatisticEntryModel(
                        0, // best time
                        0, // wins
                        1, // defeats
                        1, // gamesPlayed
                        numberOfRow, // number of rows
                        numberOfColumns, // number of columns
                        numberOfMines, // number of mines
                        this // parent of this object
                        );

            // append to displayed list
            mStatisticsModel->statisticEntryModelListRef()->append(statisticEntryModel);
            
            quint64 index = mStatisticsModel->statisticEntryModelListRef()->size() - 1;

            // append to HashMap
            mGameModeStatisticsMap.insert(key, qMakePair(index, statisticEntryModel));

            qDebug() << "lost index: " << index << " " << key.rows << " " << key.columns << " " << key.mines;
        }
        else
        {
            // increase the number of defeats
            // and the number of games played 
            QPair<quint64, models::StatisticEntryModel*> indexEntryModelPair = indexEntryModelPairIterator.value();
            increaseNumberOfDefeats(indexEntryModelPair.second);
            increaseNumberOfGamesPlayed(indexEntryModelPair.second);
        }
    }

    emit mStatisticsModel->statisticEntryModelListChanged();

}

void StatisticsController::increaseNumberOfWins(models::StatisticEntryModel *statisticEntryModel)
{
    statisticEntryModel->setNumberOfWins(statisticEntryModel->numberOfWins() + 1);
}

void StatisticsController::increaseNumberOfDefeats(models::StatisticEntryModel *statisticEntryModel)
{
    statisticEntryModel->setNumberOfDefeats(statisticEntryModel->numberOfDefeats() + 1);
}

void StatisticsController::increaseNumberOfGamesPlayed(models::StatisticEntryModel *statisticEntryModel)
{
    statisticEntryModel->setNumberOfGamesPlayed(statisticEntryModel->numberOfGamesPlayed() + 1);
}


} // namespace controllers


