#include "../../inc/controllers/GameController.h"


namespace controllers
{

GameController::GameController(models::GameModel *gameModel, QObject *parent)
    : QObject(parent),
      mGameStarted(false),
      mTimerRunning(false),
      mGameModel(gameModel)
{
    // TODO 1. load from json , 2. set game mode and 3. init game
    initGame();
}

GameController::~GameController()
{
    if(mTimerThread.joinable())
    {
        mTimerThread.join();
    }

    // TODO save game configuration to json
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

} // namespace controllers



