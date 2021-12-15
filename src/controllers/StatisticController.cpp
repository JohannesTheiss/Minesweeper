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
    loadStatistics();




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

StatisticsController::~StatisticsController()
{
    delete mJsonManager;
}

void StatisticsController::loadStatistics()
{
    quint64 index = 0;
    mJsonManager->loadArray(mJsonObjectName, [&](QJsonArray &root) 
    {
        foreach (const QJsonValue &statistics, root)
        {
            QJsonObject statisticsObject = statistics.toObject();

            // get bestTime
            quint64 bestTime = statisticsObject.value("bestTime").toString().toULongLong();

            // get numberOfWins
            quint64 numberOfWins = statisticsObject.value("numberOfWins").toString().toULongLong();

            // get numberOfDefeats
            quint64 numberOfDefeats = statisticsObject.value("numberOfDefeats").toString().toULongLong();

            // get numberOfGamesPlayed
            quint64 numberOfGamesPlayed = statisticsObject.value("numberOfGamesPlayed").toString().toULongLong();

            // get numberOfRows
            quint64 numberOfRows = statisticsObject.value("numberOfRows").toString().toULongLong();

            // get numberOfColumns
            quint64 numberOfColumns = statisticsObject.value("numberOfColumns").toString().toULongLong();

            // get numberOfMines
            quint64 numberOfMines = statisticsObject.value("numberOfMines").toString().toULongLong();

            // create a new statistics entry
            models::StatisticEntryModel *statisticEntryModel = new models::StatisticEntryModel(
                    bestTime,
                    numberOfWins, // wins
                    numberOfDefeats, // defeats
                    numberOfGamesPlayed, // gamesPlayed
                    numberOfRows,
                    numberOfColumns,
                    numberOfMines,
                    this // parent of this object
                    );

            // append to the displayed list
            mStatisticsModel->statisticEntryModelListRef()->append(statisticEntryModel);

            // set the index-statisticEntryModel-pair
            QPair<quint64, models::StatisticEntryModel*> indexEntryModelPair = qMakePair(index, statisticEntryModel);

            // append to HashMap
            // build the key
            models::GameMode key({numberOfRows, numberOfColumns, numberOfMines});
            mGameModeStatisticsMap.insert(key, indexEntryModelPair);

            qDebug() << "load: " << numberOfRows << "x" << numberOfColumns << " -> " << numberOfMines << " at: " << index;
            index++;
        }
    });

    if(index == 0)
    {
        // create the default statistics

    }

    // update the view
    emit mStatisticsModel->statisticEntryModelListChanged();
}

void StatisticsController::submitStatistics(const quint64 numberOfRows,
    const quint64 numberOfColumns,
    const quint64 numberOfMines,
    const quint64 timePlayed,
    const bool win)
{
    // build the key for the HashMap
    models::GameMode key({numberOfRows, numberOfColumns, numberOfMines});

    // try to find a value with this key
    QHash<models::GameMode, 
        QPair<quint64, models::StatisticEntryModel*>>::const_iterator 
            indexEntryModelPairIterator = mGameModeStatisticsMap.find(key);

    // holds a index in the JsonArray 
    // and a pointer to the StatisticEntryModel which is displayed
    QPair<quint64, models::StatisticEntryModel*> indexEntryModelPair;

    // check if this configuration (key) doesn't exists
    if(indexEntryModelPairIterator == mGameModeStatisticsMap.end())
    {  
        // create a new statistics entry
        models::StatisticEntryModel *statisticEntryModel = new models::StatisticEntryModel(
                0, // best time
                0, // wins
                0, // defeats
                0, // gamesPlayed
                numberOfRows,
                numberOfColumns,
                numberOfMines,
                this // parent of this object
                );

        // append to the displayed list
        mStatisticsModel->statisticEntryModelListRef()->append(statisticEntryModel);

        // set the index-statisticEntryModel-pair
        quint64 index = mStatisticsModel->statisticEntryModelListRef()->size() - 1;
        indexEntryModelPair = qMakePair(index, statisticEntryModel);

        // append to HashMap
        mGameModeStatisticsMap.insert(key, indexEntryModelPair);
    }
    else 
    {
        // the configuration (key) already exists
        // get the index-statisticEntryModel-pair
        indexEntryModelPair = indexEntryModelPairIterator.value();
    }

    if(win) 
    {
        // update the best time if it is better OR if it is the first win
        if((timePlayed < indexEntryModelPair.second->bestTime()) || indexEntryModelPair.second->numberOfWins() == 0)
        {
            indexEntryModelPair.second->setBestTime(timePlayed); 
        }

        increaseNumberOfWins(indexEntryModelPair.second);
    }
    else
    {
        // the game is lost
        increaseNumberOfDefeats(indexEntryModelPair.second);
    }

    increaseNumberOfGamesPlayed(indexEntryModelPair.second);

    // save to JSON
    save(indexEntryModelPair);

    // update the view
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

void StatisticsController::save(const QPair<quint64, models::StatisticEntryModel*> &indexEntryModelPair)
{
    models::StatisticEntryModel *statisticEntryModel = indexEntryModelPair.second;
    mJsonManager->saveToArray(mJsonObjectName, indexEntryModelPair.first, [&](QJsonObject &jsonModel)
    {
        // save best time
        jsonModel.insert("bestTime", QString::number(statisticEntryModel->bestTime()));

        // save number of wins
        jsonModel.insert("numberOfWins", QString::number(statisticEntryModel->numberOfWins()));

        // save number of defeats
        jsonModel.insert("numberOfDefeats", QString::number(statisticEntryModel->numberOfDefeats()));

        // save number of games played
        jsonModel.insert("numberOfGamesPlayed", QString::number(statisticEntryModel->numberOfGamesPlayed()));

        // save number of rows
        jsonModel.insert("numberOfRows", QString::number(statisticEntryModel->numberOfRows()));

        // save number of columns
        jsonModel.insert("numberOfColumns", QString::number(statisticEntryModel->numberOfColumns()));

        // save number of mines
        jsonModel.insert("numberOfMines", QString::number(statisticEntryModel->numberOfMines()));

        qDebug() << "save: " << statisticEntryModel->numberOfRows() << "x" << statisticEntryModel->numberOfColumns()
            << " -> " << statisticEntryModel->numberOfMines() << " at: " << (indexEntryModelPair.first);
    });
}


} // namespace controllers


