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
}

StatisticsController::~StatisticsController()
{
    delete mJsonManager;
}

void StatisticsController::loadStatistics()
{
    bool jsonIsEmpty = true;
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

            models::GameMode key({numberOfRows, numberOfColumns, numberOfMines});
            createGameModeStatistics(
                    key, 
                    bestTime,
                    numberOfWins,
                    numberOfDefeats,
                    numberOfGamesPlayed);
        }

        jsonIsEmpty = false;
    });

    if(jsonIsEmpty)
    {
        // create the default statistics
        createDefaultGameModeStatistics();
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
        indexEntryModelPair = createGameModeStatistics(key);
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

void StatisticsController::resetStatistics()
{
    mStatisticsModel->statisticEntryModelListRef()->clear();
    mGameModeStatisticsMap.clear();
    createDefaultGameModeStatistics();

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
        mapStatisticEntryModelToJsonObject(statisticEntryModel, jsonModel);
    });
}

void StatisticsController::mapStatisticEntryModelToJsonObject(models::StatisticEntryModel *statisticEntryModel, 
        QJsonObject &jsonModel)
{
    // map best time
    jsonModel.insert("bestTime", QString::number(statisticEntryModel->bestTime()));

    // map number of wins
    jsonModel.insert("numberOfWins", QString::number(statisticEntryModel->numberOfWins()));

    // map number of defeats
    jsonModel.insert("numberOfDefeats", QString::number(statisticEntryModel->numberOfDefeats()));

    // map number of games played
    jsonModel.insert("numberOfGamesPlayed", QString::number(statisticEntryModel->numberOfGamesPlayed()));

    // map number of rows
    jsonModel.insert("numberOfRows", QString::number(statisticEntryModel->numberOfRows()));

    // map number of columns
    jsonModel.insert("numberOfColumns", QString::number(statisticEntryModel->numberOfColumns()));

    // map number of mines
    jsonModel.insert("numberOfMines", QString::number(statisticEntryModel->numberOfMines()));
}

void StatisticsController::createDefaultGameModeStatistics()
{
    int n = 3;
    models::GameMode keys[] = {{9, 9, 10}, {16, 16, 40}, {16, 30, 99}};
    models::StatisticEntryModel *entryModels[n];

    for(int i = 0; i < n; ++i)
    {
        QPair<quint64, models::StatisticEntryModel*> defaultGameModeStatistics = createGameModeStatistics(keys[i]);

        entryModels[i] = defaultGameModeStatistics.second;
    }

    mJsonManager->replaceArray(mJsonObjectName, [&](QJsonArray &jsonArray)
    {
        // save the default game mode statistics
        for(int i = 0; i < n; ++i)
        {
            QJsonObject bufferObject;
            mapStatisticEntryModelToJsonObject(entryModels[i], bufferObject);

            jsonArray.push_back(QJsonValue(bufferObject));
        }
    });
}

QPair<quint64, models::StatisticEntryModel*> StatisticsController::createGameModeStatistics(models::GameMode &gameMode,
    const quint64 bestTime,
    const quint64 numberOfWins,
    const quint64 numberOfDefeats,
    const quint64 numberOfGamesPlayed)
{
    models::StatisticEntryModel *statisticEntryModel = new models::StatisticEntryModel(
        bestTime, // best time
        numberOfWins, // wins
        numberOfDefeats, // defeats
        numberOfGamesPlayed, // gamesPlayed
        gameMode.rows,
        gameMode.columns,
        gameMode.mines,
        this // parent of this object
        );

    // append to the displayed list
    mStatisticsModel->statisticEntryModelListRef()->append(statisticEntryModel);

    // set the index-statisticEntryModel-pair
    quint64 index = mStatisticsModel->statisticEntryModelListRef()->size() - 1;
    QPair<quint64, models::StatisticEntryModel*> indexEntryModelPair = qMakePair(index, statisticEntryModel);

    // append to HashMap
    mGameModeStatisticsMap.insert(gameMode, indexEntryModelPair);

    return indexEntryModelPair;
}


} // namespace controllers


