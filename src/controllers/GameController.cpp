#include "../../inc/controllers/GameController.h"


namespace controllers
{

GameController::GameController(models::GameModel *gameModel, QObject *parent)
    : QObject(parent),
      mGameStarted(false),
      mTimerRunning(false),
      mGameModel(gameModel)
{
    // default game configuration
    quint64 rows = 16;
    quint64 columns = 16;
    quint64 mines = 40;

    // load last configuration from json
    mJsonManager = new data::JsonManager("gameConfiguration.json");
    mJsonManager->load(mJsonObjectName, [&](QJsonValue &jsonModel) 
    {
        QJsonObject configuration = jsonModel.toObject();

        quint64 loadedRows = configuration.value("rows").toString().toULongLong();
        quint64 loadedColumns = configuration.value("columns").toString().toULongLong();
        quint64 loadedMines = configuration.value("mines").toString().toULongLong();

        // if the configuration not empty
        if(loadedRows != 0 && loadedColumns != 0 && loadedMines != 0)
        {
            // set to the last configuration
            rows = loadedRows;
            columns = loadedColumns;
            mines = loadedMines;
        }
    });

    setGameMode(rows, columns, mines);
}

GameController::~GameController()
{
    if(mTimerThread.joinable())
    {
        mGameStarted = false;
        mTimerThread.join();
    }

    // save game configuration to json
    mJsonManager->save(mJsonObjectName, [&](QJsonObject &jsonModel)
    {
        // save rows
        jsonModel.insert("rows", QString::number(mGameModel->rows()));

        // save columns
        jsonModel.insert("columns", QString::number(mGameModel->columns()));

        // save mines
        jsonModel.insert("mines", QString::number(mGameModel->mineCount()));
    });

    delete mJsonManager;
}

void GameController::revealCell(const quint64 index)
{
    models::CellModel* cell = mGameModel->grid().at(index);

    // TODO if first hit is a bomb...

    // don't reveal flagged cells
    if(cell->flagged()) return;

    // if cell is a bomb then game over
    if(cell->isBomb())
    {   
        revealAllCells();
        endGame();
        qDebug() << "ur a NOOB... lol";
    }
    else if(cell->hidden()) 
    {
        cell->setHidden(false);

        // if there are no surrounding bombs
        if(cell->surroundingBombs() == 0)
        {
            // reveal surrounding cells
            updateSurroundingCell(index,
                    std::bind(&GameController::revealCell, this, std::placeholders::_1));
        }

        checkForWin();
    }
}

void GameController::revealAllCells()
{
    foreach(models::CellModel* cell, mGameModel->grid())
    {
        cell->setHidden(false);
    }
}

void GameController::toggleFlagInCell(const quint64 index)
{
    models::CellModel* cell = mGameModel->grid().at(index);

    if(cell->hidden())
    {
        if(cell->flagged())
        {
            cell->setFlagged(false);
            increaseFlagCount();
        }
        else 
        {
            cell->setFlagged(true);
            decreaseFlagCount();
        
            checkForWin();
        }
    }
}

void GameController::initGame()
{
    mGameStarted = false;
    mTimerRunning = false;
    mGameModel->setFlagCount(mGameModel->mineCount());
    mGameModel->setTimePlayed(0);
    if(mTimerThread.joinable())
    {
        mTimerThread.join();
    }
    generateGrid();
}

void GameController::startGame()
{
    if(!mGameStarted)
    {
        mGameStarted = true;
        mTimerRunning = true;

        mTimerThread = std::thread(&GameController::threadedTimer, this);
    }
}

void GameController::togglePauseGame()
{
    if(mGameStarted)
    {
        mTimerRunning = !mTimerRunning;
    }
}

void GameController::endGame()
{
    if(mGameStarted)
    {
        mGameStarted = false;
        mTimerRunning = false;

        mTimerThread.join();
    }
}

void GameController::setGameMode(const quint64 numberOfRows,
                                 const quint64 numberOfColumns,
                                 const quint64 numberOfMines)
{
    // update the model
    mGameModel->setRows(numberOfRows);
    mGameModel->setColumns(numberOfColumns);
    mGameModel->setMineCount(numberOfMines);

    // initialize the game
    initGame();
}

void GameController::generateGrid()
{
    quint64 numberOfCells = mGameModel->rows() * mGameModel->columns();

    // generate the mines
    QVector<quint64> indices(numberOfCells);
    std::iota(indices.begin(), indices.end(), 0);
    long long seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(indices.begin(), indices.end(), std::default_random_engine(seed));
    QVector<quint64> mineIndices(indices.mid(0, mGameModel->mineCount()));

    // build a new the grid
    QVector<models::CellModel *> grid(numberOfCells);
    for (int i = 0; i < grid.size(); ++i)
    {
        // set CellModel(hidden = true, flagged = false, isBomb = false, surroundingBombs = 0)
        grid[i] = new models::CellModel(true, false, false, 0);
    }

    // set the grid
    mGameModel->setGrid(grid);

    // set mines in grid
    foreach(quint64 mineIndex, mineIndices)
    {
        // set bomb
        grid[mineIndex]->setIsBomb(true);

        // culc. the values surrounding cells
        updateSurroundingCell(mineIndex,
                std::bind(&GameController::increaseSurroundingBombsCount, this, std::placeholders::_1));
    }
}

void GameController::increaseSurroundingBombsCount(const quint64 cellIndex)
{
    models::CellModel *cell = mGameModel->grid().at(cellIndex);
    cell->setSurroundingBombs(cell->surroundingBombs() + 1);
}

void GameController::increaseFlagCount()
{
    mGameModel->setFlagCount(mGameModel->flagCount() + 1);
}

void GameController::decreaseFlagCount()
{
    mGameModel->setFlagCount(mGameModel->flagCount() - 1);
}

void GameController::threadedTimer()
{
    while(mGameStarted)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));

        if(mTimerRunning)
        {
            mMutex.lock();
            mGameModel->setTimePlayed(mGameModel->timePlayed() + 1);
            mMutex.unlock();
        }
    }
}

void GameController::updateSurroundingCell(const quint64 cellIndex,
    const std::function<void(quint64)> updateFunction)
{
    quint64 numberOfColumns = mGameModel->columns();
    quint64 numberOfRow = mGameModel->rows();
    quint64 columnIndex = cellIndex % numberOfColumns;

    bool notFirstColumn = columnIndex > 0;
    bool notFirstRow = cellIndex >= numberOfColumns; 
    bool notLastColumn = (columnIndex + 1) < numberOfColumns;
    bool notLastRow = cellIndex < ((numberOfColumns * numberOfRow) - numberOfColumns);

    if(notFirstRow && notFirstColumn)
    {
        // upper left cell
        updateFunction(cellIndex - numberOfColumns - 1);
    }

    if(notFirstRow)
    {
        // upper cell
        updateFunction(cellIndex - numberOfColumns);
    }

    if(notFirstRow && notLastColumn)
    {
        // upper right cell
        updateFunction(cellIndex - numberOfColumns + 1);
    }

    if(notLastColumn)
    {
        // right cell
        updateFunction(cellIndex + 1);
    }

    if(notLastColumn && notLastRow)
    {
        // lower right cell
        updateFunction(cellIndex + numberOfColumns + 1);
    }

    if(notLastRow)
    {
        // lower cell
        updateFunction(cellIndex + numberOfColumns);
    }

    if(notLastRow && notFirstColumn) 
    {
        // lower left cell
        updateFunction(cellIndex + numberOfColumns - 1);
    }

    if(notFirstColumn) 
    {
        // left cell
        updateFunction(cellIndex - 1);
    }
}

void GameController::checkForWin()
{

    // check if the game is won now
    if(mGameModel->flagCount() == 0)
    {
        qDebug() << "check for win";
        bool won = true;


        //foreach(models::CellModel *cell, mGameModel->grid())
        for(int i = 0; i < mGameModel->grid().size(); i++) 
        {
            //if(cell->hidden() && (!cell->isBomb() || !cell->flagged()))
            //if(mGameModel->grid().at(i)->hidden() && (!mGameModel->grid().at(i)->isBomb() || !mGameModel->grid().at(i)->flagged()))
            models::CellModel *cell = mGameModel->grid().at(i);
            if(cell->hidden() && (!cell->isBomb() || !cell->flagged()))
            {
                won = false;
                break;
            }

        }


        auto t1 = std::chrono::high_resolution_clock::now();
        if(won)
        {
            endGame();
            qDebug() << "u won the game";
        }

        auto t2 = std::chrono::high_resolution_clock::now();
        auto ms_int = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
        std::cout << "checkForWin = " << ms_int.count() << " ms"<< std::endl;
    }
}


} // namespace controllers



