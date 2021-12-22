#include "../../inc/controllers/StatisticsController.h"


namespace controllers
{

// <summary> Custom constructor for StatisticsController-objects
//           it creates the JsonManager and loads the statistics </summary>
// <param name="statisticsObserver"> Pointer to a StatisticsObserver-object </param>
// <param name="parent"> Optional pointer to a parent object </param>
StatisticsController::StatisticsController(observers::StatisticsObserver *statisticsObserver,
    QObject *parent)
    : QObject(parent),
      mStatisticsObserver(statisticsObserver)
{
    mJsonManager = new data::JsonManager("statistics.json");

    // load all statistic from json
    loadStatistics();
}

// <summary> Custom destructor for StatisticsController-objects
//           it deletes the JsonManager</summary>
StatisticsController::~StatisticsController()
{
    delete mJsonManager;
}

// <summary> Load all statistics from JSON
//           and if it is empty, create the default game mode statistics </summary>
// <returns> Nothing </returns>
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
    emit mStatisticsObserver->statisticEntryModelListChangedPassthrough(
                mStatisticsObserver->statisticEntryModelListRef());
}

// <summary> Create a new statistic with given the information </summary>
// <param name="numberOfRows"> The number of rows for this statistic </param>
// <param name="numberOfColumns"> The number of columns for this statistic </param>
// <param name="numberOfMines"> The number of mines for this statistic </param>
// <param name="timePlayed"> The time played for this statistic </param>
// <param name="win"> Is 'true' if the game is won, else 'false' </param>
// <returns> Nothing </returns>
void StatisticsController::createStatistic(const quint64 numberOfRows,
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
    emit mStatisticsObserver->statisticEntryModelListChangedPassthrough(
                mStatisticsObserver->statisticEntryModelListRef());

    emit gameEnded(indexEntryModelPair.second->bestTime(), win); 
}

// <summary> Reset all statistic and create the default game mode statistics </summary>
// <returns> Nothing </returns>
void StatisticsController::resetStatistics()
{
    mStatisticsObserver->statisticEntryModelListRef().clear();
    mGameModeStatisticsMap.clear();
    createDefaultGameModeStatistics();

    // update the view
    emit mStatisticsObserver->statisticEntryModelListChangedPassthrough(
                mStatisticsObserver->statisticEntryModelListRef());
}

// <summary> Increase the number of wins by one </summary>
// <param name="statisticEntryModel"> The statistics entry model to save the new win count to </param>
// <returns> Nothing </returns>
void StatisticsController::increaseNumberOfWins(models::StatisticEntryModel *statisticEntryModel)
{
    statisticEntryModel->setNumberOfWins(statisticEntryModel->numberOfWins() + 1);
}

// <summary> Increase the number of defeats by one </summary>
// <param name="statisticEntryModel"> The statistics entry model to save the new defeat count to </param>
// <returns> Nothing </returns>
void StatisticsController::increaseNumberOfDefeats(models::StatisticEntryModel *statisticEntryModel)
{
    statisticEntryModel->setNumberOfDefeats(statisticEntryModel->numberOfDefeats() + 1);
}

// <summary> Increase the number of games played by one </summary>
// <param name="statisticEntryModel"> The statistics entry model to save the new games played count to </param>
// <returns> Nothing </returns>
void StatisticsController::increaseNumberOfGamesPlayed(models::StatisticEntryModel *statisticEntryModel)
{
    statisticEntryModel->setNumberOfGamesPlayed(statisticEntryModel->numberOfGamesPlayed() + 1);
}

// <summary> Save a new statistics object to JSON </summary>
// <param name="indexEntryModelPair"> Holds the index in the JSON-Array to insert the StatisticEntryModel </param>
// <returns> Nothing </returns>
void StatisticsController::save(const QPair<quint64, models::StatisticEntryModel*> &indexEntryModelPair)
{
    models::StatisticEntryModel *statisticEntryModel = indexEntryModelPair.second;
    mJsonManager->saveToArray(mJsonObjectName, indexEntryModelPair.first, [&](QJsonObject &jsonModel)
    {
        mapStatisticEntryModelToJsonObject(statisticEntryModel, jsonModel);
    });
}

// <summary> Maps the StatisticEntryModel to a QJsonObject </summary>
// <param name="statisticEntryModel"> StatisticEntryModel that will be mapped </param>
// <param name="jsonModel"> The result QJsonObject with the StatisticEntryModel information </param>
// <returns> Nothing </returns>
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

// <summary> Create the default game mode statistic,
//           for Beginner, Intermediate and Expert </summary>
// <returns> Nothing </returns>
void StatisticsController::createDefaultGameModeStatistics()
{
    const int numberOfDefaultGameModes = 3;
    models::GameMode keys[] = {
        {9, 9, 10},   // Beginner
        {16, 16, 40}, // Intermediate
        {16, 30, 99}  // Expert
    };
    models::StatisticEntryModel *entryModels[numberOfDefaultGameModes];

    for(int i = 0; i < numberOfDefaultGameModes; ++i)
    {
        QPair<quint64, models::StatisticEntryModel*> defaultGameModeStatistics = createGameModeStatistics(keys[i]);

        entryModels[i] = defaultGameModeStatistics.second;
    }

    // save the defaultGameModeStatistics to JSON
    mJsonManager->replaceArray(mJsonObjectName, [&](QJsonArray &jsonArray)
    {
        // save the default game mode statistics
        for(int i = 0; i < numberOfDefaultGameModes; ++i)
        {
            QJsonObject bufferObject;
            mapStatisticEntryModelToJsonObject(entryModels[i], bufferObject);

            jsonArray.push_back(QJsonValue(bufferObject));
        }
    });
}

// <summary> Create a new game mode statistic with given information </summary>
// <param name="gameMode"> The game mode for the statistic </param>
// <param name="bestTime"> Optional if there is a new best time</param>
// <param name="numberOfWins"> Optional the number of wins in this game mode </param>
// <param name="numberOfDefeats"> Optional the number of defeats in this game mode </param>
// <param name="numberOfGamesPlayed"> Optional the number of games played in the game mode </param>
// <returns> QPair of the index in the JSON-Array and the StatisticEntryModel-object which is displayed </returns>
QPair<quint64, models::StatisticEntryModel*> StatisticsController::createGameModeStatistics(
    models::GameMode &gameMode,
    const quint64 bestTime,
    const quint64 numberOfWins,
    const quint64 numberOfDefeats,
    const quint64 numberOfGamesPlayed)
{
    models::StatisticEntryModel *statisticEntryModel = new models::StatisticEntryModel(
        bestTime,
        numberOfWins,
        numberOfDefeats,
        numberOfGamesPlayed,
        gameMode.rows,
        gameMode.columns,
        gameMode.mines,
        this // parent of this object
        );

    // append to the displayed list
    mStatisticsObserver->statisticEntryModelListRef().append(statisticEntryModel);

    // set the index-statisticEntryModel-pair
    quint64 index = mStatisticsObserver->statisticEntryModelListRef().size() - 1;
    QPair<quint64, models::StatisticEntryModel*> indexEntryModelPair = qMakePair(index, statisticEntryModel);

    // append to HashMap
    mGameModeStatisticsMap.insert(gameMode, indexEntryModelPair);

    return indexEntryModelPair;
}


} // namespace controllers
