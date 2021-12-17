#include "../../inc/controllers/GameController.h"


namespace controllers
{

GameController::GameController(observers::GameObserver *gameObserver, QObject *parent)
    : QObject(parent),
      mFirstReveal(true),
      mGameStarted(false),
      mGameObserver(gameObserver)
{
    // default game configuration
    quint64 rows = 16;
    quint64 columns = 16;
    quint64 mines = 40;

    // create timer and connect it to a slot
    timer = new QTimer(this);;
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(updateTime()));
    timer->setInterval(1000); // 1 ms

    // load last configuration from json
    mJsonManager = new data::JsonManager("gameConfiguration.json");
    mJsonManager->load(mJsonObjectName, [&](QJsonValue &jsonModel) 
    {
        QJsonObject configuration = jsonModel.toObject();

        quint64 loadedRows = configuration.value("rows").toString().toULongLong();
        quint64 loadedColumns = configuration.value("columns").toString().toULongLong();
        quint64 loadedMines = configuration.value("mines").toString().toULongLong();

        // load and set the size scaling
        int loadedScaling = configuration.value("scaling").toInt();
        setScaling(loadedScaling);

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
    mGameStarted = false;

    // save game configuration to json
    mJsonManager->save(mJsonObjectName, [&](QJsonObject &jsonModel)
    {
        // save rows
        jsonModel.insert("rows", QString::number(mGameObserver->rows()));

        // save columns
        jsonModel.insert("columns", QString::number(mGameObserver->columns()));

        // save mines
        jsonModel.insert("mines", QString::number(mGameObserver->mineCount()));

        // save scaling
        jsonModel.insert("scaling", static_cast<int>(mGameObserver->scaling()));
    });

    delete mJsonManager;
}

void GameController::updateTime()
{
    mGameObserver->setTimePlayed(mGameObserver->timePlayed() + 1);
}

void GameController::revealCell(const quint64 index)
{
    models::CellModel* cell = mGameObserver->grid().at(index);

    // don't reveal flagged cells
    if(cell->flagged()) return;

    // if the first hit is a bomb
    if(cell->isBomb() && mFirstReveal)
    {
        qDebug() << "first hit is a bomb";

        // move the bomb to a new random place
        addMine();
        removeMine(index);
        mFirstReveal = false;
    }

    // if cell is a bomb then game over
    if(cell->isBomb())
    {   
        revealAllCells();
        endGame(false); // game lost = false
    }
    else if(cell->hidden()) 
    {
        if(mFirstReveal) mFirstReveal = false;
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
    foreach(models::CellModel* cell, mGameObserver->grid())
    {
        cell->setHidden(false);
    }
}

void GameController::toggleFlagInCell(const quint64 index)
{
    models::CellModel* cell = mGameObserver->grid().at(index);

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
    timer->stop();

    mGameObserver->setFlagCount(mGameObserver->mineCount());
    mGameObserver->setTimePlayed(0);

    generateGrid();
}

void GameController::startGame()
{
    if(!mGameStarted)
    {
        mFirstReveal = true;
        mGameStarted = true;

        timer->start();
    }
}

void GameController::togglePauseGame()
{
    if(mGameStarted)
    {
        if(timer->isActive())
        {
            timer->stop();
        }
        else
        {
            timer->start();
        }
    }
}

void GameController::endGame(const bool wonOrLost)
{
    if(mGameStarted)
    {
        mGameStarted = false;
        timer->stop();
        
        emit gameEnded(mGameObserver->rows(),
                mGameObserver->columns(),
                mGameObserver->mineCount(),
                mGameObserver->timePlayed(),
                wonOrLost);
    }
}

void GameController::setGameMode(const quint64 numberOfRows,
                                 const quint64 numberOfColumns,
                                 const quint64 numberOfMines)
{
    // update the model
    mGameObserver->setRows(numberOfRows);
    mGameObserver->setColumns(numberOfColumns);
    mGameObserver->setMineCount(numberOfMines);

    // initialize the game
    initGame();
}

void GameController::setScaling(const int scaling)
{
    mGameObserver->setScaling(models::SizeScaling(scaling));
}

void GameController::generateGrid()
{
    quint64 numberOfCells = mGameObserver->rows() * mGameObserver->columns();

    // build a new the grid
    QVector<models::CellModel *> grid(numberOfCells);
    for (int i = 0; i < grid.size(); ++i)
    {
        // set CellModel(hidden = true, flagged = false, isBomb = false, surroundingBombs = 0)
        grid[i] = new models::CellModel(true, false, false, 0);
    }

    // set the grid
    mGameObserver->setGrid(grid);

    generateMines();
}

void GameController::generateMines()
{
    quint64 numberOfCells = mGameObserver->rows() * mGameObserver->columns();

    QVector<quint64> indices(numberOfCells);
    std::iota(indices.begin(), indices.end(), 0); // indices: {0, 1, 2, ..., numberOfCells}
    
    // put the indices in a random order
    long long seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(indices.begin(), indices.end(), std::default_random_engine(seed));

    // get the first 'mineCount' indices from the list
    // e.g. if mineCount = 3 then get the first 3 elements from the random indices array
    QVector<quint64> mineIndices(indices.mid(0, mGameObserver->mineCount()));
    
    // set mines in grid
    foreach(quint64 mineIndex, mineIndices)
    {
        // set bomb
        mGameObserver->grid().at(mineIndex)->setIsBomb(true);

        // culc. the values surrounding cells
        updateSurroundingCell(mineIndex,
                std::bind(&GameController::increaseSurroundingBombsCount, this, std::placeholders::_1));
    }

    // update the mineIndices of the model
    mMineIndices = mineIndices;
}

quint64 GameController::addMine()
{
    quint64 numberOfCells = mGameObserver->rows() * mGameObserver->columns();
    quint64 newMineIndex = 0;

    bool mineAlreadyExists = false;
    do 
    {
        mineAlreadyExists = false;
        newMineIndex = numberOfCells * (rand() / (RAND_MAX + 1.0)); // [0, numberOfCells[

        // check if the new mine indices are already mines
        foreach(quint64 mineIndex, mMineIndices)
        {
            // min already exists
            if(newMineIndex == mineIndex)
            {
                mineAlreadyExists = true;
                break;
            }
        }
    }
    while(mineAlreadyExists);
    
    // set bomb
    mGameObserver->grid().at(newMineIndex)->setIsBomb(true);

    // culc. the values surrounding cells
    updateSurroundingCell(newMineIndex,
            std::bind(&GameController::increaseSurroundingBombsCount, this, std::placeholders::_1));

    // update the mineIndices of the model
    mMineIndices.append(newMineIndex);

    return newMineIndex;
}

void GameController::removeMine(const quint64 mineIndex)
{
    // change cell
    mGameObserver->grid().at(mineIndex)->setIsBomb(false);

    // remove from gameModel
    mMineIndices.removeOne(mineIndex);

    // decrease surrounding bomb count
    updateSurroundingCell(mineIndex,
            std::bind(&GameController::decreaseSurroundingBombsCount, this, std::placeholders::_1));
}

void GameController::increaseSurroundingBombsCount(const quint64 cellIndex)
{
    models::CellModel *cell = mGameObserver->grid().at(cellIndex);
    cell->setSurroundingBombs(cell->surroundingBombs() + 1);
}

void GameController::decreaseSurroundingBombsCount(const quint64 cellIndex)
{
    models::CellModel *cell = mGameObserver->grid().at(cellIndex);
    cell->setSurroundingBombs(cell->surroundingBombs() - 1);
}

void GameController::increaseFlagCount()
{
    mGameObserver->setFlagCount(mGameObserver->flagCount() + 1);
}

void GameController::decreaseFlagCount()
{
    mGameObserver->setFlagCount(mGameObserver->flagCount() - 1);
}

void GameController::updateSurroundingCell(const quint64 cellIndex,
    const std::function<void(quint64)> updateFunction)
{
    quint64 numberOfColumns = mGameObserver->columns();
    quint64 numberOfRow = mGameObserver->rows();
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
    if(mGameObserver->flagCount() == 0)
    {
        qDebug() << "check for win";
        bool won = true;

        for(int i = 0; i < mGameObserver->grid().size(); i++)
        {
            models::CellModel *cell = mGameObserver->grid().at(i);
            if(cell->hidden() && (!cell->isBomb() || !cell->flagged()))
            {
                won = false;
                break;
            }
        }

        auto t1 = std::chrono::high_resolution_clock::now();
        if(won)
        {
            endGame(won); // game won = true
            qDebug() << "u won the game";
        }

        auto t2 = std::chrono::high_resolution_clock::now();
        auto ms_int = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
        std::cout << "checkForWin = " << ms_int.count() << " ms"<< std::endl;
    }
}


} // namespace controllers



