#include "../../inc/controllers/GameController.h"


namespace controllers
{

// <summary> Custom constructor for GameController-objects
//           it creates a timer and loads/sets the last game configuration </summary>
// <param name="gameObserver"> Pointer to a GameObserver-object </param>
// <param name="parent"> Optional pointer to a parent object </param>
GameController::GameController(observers::GameObserver *gameObserver, QObject *parent)
    : QObject(parent),
      mFirstReveal(true),
      mGameStarted(false),
      mGameObserver(gameObserver)
{
    // default game configuration
    quint64 rows = 9;
    quint64 columns = 9;
    quint64 mines = 10;

    // create timer and connect it to a slot
    timer = new QTimer(this);;
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(updateTime()));
    timer->setInterval(1000); // 1 ms

    // load last configuration from json
    mJsonManager = new data::JsonManager("gameConfiguration.json");
    mJsonManager->load(mJsonObjectName, [&](QJsonValue &jsonModel) 
    {
        QJsonObject configuration = jsonModel.toObject();

        // set to the last configuration
        rows = configuration.value("rows").toString().toULongLong();
        columns = configuration.value("columns").toString().toULongLong();
        mines = configuration.value("mines").toString().toULongLong();

        // load and set the size scaling
        setScaling(configuration.value("scaling").toInt());
    });

    setGameMode(rows, columns, mines);
}

// <summary> Custom destructor for GameController-objects
//           it saves the current game configuration to JSON</summary>
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

// <summary> Reveal the cell at the given index,
//           check if the game is won or lost
//           and may reveal surrounding cells as well</summary>
// <param name="index"> Index of cell to reveal </param>
// <returns> Nothing </returns>
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

// <summary> Reveal all cells on the grid </summary>
// <returns> Nothing </returns>
void GameController::revealAllCells()
{
    foreach(models::CellModel* cell, mGameObserver->grid())
    {
        cell->setHidden(false);
    }
}

// <summary> Toggle the flag within a cell at the given index </summary>
// <param name="index"> Index of a cell to toggle the flag at </param>
// <returns> Nothing </returns>
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

// <summary> Initialize the game by 
//           end the current game,
//           reset the flag count, time played
//           and generate a new grid </summary>
// <returns> Nothing </returns>
void GameController::initGame()
{
    endGame(false);

    mGameStarted = false;
    timer->stop();

    mGameObserver->setFlagCount(mGameObserver->mineCount());
    mGameObserver->setTimePlayed(0);

    generateGrid();
}

// <summary> Start the game by
//           reset mFirstReveal, mGameStarted
//           and start the timer </summary>
// <returns> Nothing </returns>
void GameController::startGame()
{
    if(!mGameStarted)
    {
        mFirstReveal = true;
        mGameStarted = true;

        timer->start();
    }
}

// <summary> Toggle the game state between pause and play </summary>
// <returns> Nothing </returns>
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

// <summary> End the current game 
//           and submit the needed information to the statistics controller </summary>
// <param name="wonOrLost"> Is 'true' if the game is won, otherwise 'false' </param>
// <returns> Nothing </returns>
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

// <summary> Set a new game mode and initialize it </summary>
// <param name="numberOfRows"> The new number of rows </param>
// <param name="numberOfColumns"> The new number of columns </param>
// <param name="numberOfMines"> The new number of mines </param>
// <returns> Nothing </returns>
void GameController::setGameMode(quint64 numberOfRows,
                                 quint64 numberOfColumns,
                                 quint64 numberOfMines)
{
    if(numberOfRows == 0)
    {
        numberOfRows = 1;
    }

    if(numberOfColumns == 0) 
    {
        numberOfColumns = 1;
    }

    if(numberOfMines >= (numberOfRows * numberOfRows))
    {
        numberOfMines = (numberOfRows * numberOfColumns) - 1;
    }

    // update the model
    mGameObserver->setRows(numberOfRows);
    mGameObserver->setColumns(numberOfColumns);
    mGameObserver->setMineCount(numberOfMines);

    // initialize the game
    initGame();
}

// <summary> Set the scaling of the application </summary>
// <param name="scaling"> Enum for the scaling </param>
// <returns> Nothing </returns>
void GameController::setScaling(const int scaling)
{
    mGameObserver->setScaling(models::SizeScaling(scaling));
}

// <summary> Increase the current time played by one </summary>
// <returns> Nothing </returns>
void GameController::updateTime()
{
    mGameObserver->setTimePlayed(mGameObserver->timePlayed() + 1);
}

// <summary> Generate a new grid by 
//           the rows and columns from the GameModel </summary>
// <returns> Nothing </returns>
void GameController::generateGrid()
{
    quint64 numberOfCells = mGameObserver->rows() * mGameObserver->columns();

    // build a new the grid
    QVector<models::CellModel *> grid(numberOfCells);
    for (int i = 0; i < grid.size(); ++i)
    {
        grid[i] = new models::CellModel(
                true,  // hidden
                false, // flagged
                false, // isBomb
                0      // surroundingBombs
                );
    }

    // set the grid to the model
    mGameObserver->setGrid(grid);

    // generate all mines for the new grid
    generateMines();
}

// <summary> Generate all mines for the grid by 
//           the mine counter from the GameModel </summary>
// <returns> Nothing </returns>
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

        // increase the value of the surrounding cell by one
        updateSurroundingCell(mineIndex,
                std::bind(&GameController::increaseSurroundingBombsCount, this, std::placeholders::_1));
    }

    // update the mineIndices
    mMineIndices = mineIndices;
}

// <summary> Add one new mine at random position in the current grid </summary>
// <returns> Index of the new mine </returns>
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

// <summary> Remove one mine at a given index 
//           from the current grid </summary>
// <param name="mineIndex"> Index of the mine that will be removed</param>
// <returns> Nothing </returns>
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

// <summary> Increase the surrounding bombs count
//           of a cell at a given index by one</summary>
// <param name="cellIndex"> Index of the cell that will get the increase </param>
// <returns> Nothing </returns>
void GameController::increaseSurroundingBombsCount(const quint64 cellIndex)
{
    models::CellModel *cell = mGameObserver->grid().at(cellIndex);
    cell->setSurroundingBombs(cell->surroundingBombs() + 1);
}

// <summary> Decrease the surrounding bombs count
//           of a cell at a given index by one</summary>
// <param name="cellIndex"> Index of the cell that will get the decrease </param>
// <returns> Nothing </returns>
void GameController::decreaseSurroundingBombsCount(const quint64 cellIndex)
{
    models::CellModel *cell = mGameObserver->grid().at(cellIndex);
    cell->setSurroundingBombs(cell->surroundingBombs() - 1);
}

// <summary> Increase the flag count by one </summary>
// <returns> Nothing </returns>
void GameController::increaseFlagCount()
{
    mGameObserver->setFlagCount(mGameObserver->flagCount() + 1);
}

// <summary> Decrease the flag count by one </summary>
// <returns> Nothing </returns>
void GameController::decreaseFlagCount()
{
    mGameObserver->setFlagCount(mGameObserver->flagCount() - 1);
}

// <summary> Update all surrounding cells of a given index 
//           with a given update function </summary>
// <param name="cellIndex"> Cell index to update the surrounding cells </param>
// <returns> Nothing </returns>
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

// <summary> Check if the game is won </summary>
// <returns> Nothing </returns>
void GameController::checkForWin()
{
    if(mGameObserver->flagCount() == 0)
    {
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

        if(won)
        {
            endGame(won); // game won = true
        }
    }
}


} // namespace controllers

