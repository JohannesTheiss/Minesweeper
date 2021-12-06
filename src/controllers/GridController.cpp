#include "../../inc/controllers/GridController.h"


namespace controllers
{

GridController::GridController(models::GridModel *gridModel, QObject *parent)
    : QObject(parent),
      mGridModel(gridModel)
{}

void GridController::newGrid()
{
    // load settings
    
    quint64 numberOfRows = 16;
    quint64 numberOfColumns = 30;
    quint64 numberOfMines = 99;

    //mGridModel->setRows(numberOfRows);
    //mGridModel->setColumns(numberOfColumns);
    //mGridModel->setMineCount(numberOfMines);
    //mGridModel->setFlagCount(numberOfMines);

    //generateGrid(mGridModel);
}

void GridController::generateGrid()
{
    quint64 numberOfCells = mGridModel->rows() * mGridModel->columns();

    // generate the mines
    QVector<quint64> indices(numberOfCells);
    std::iota(indices.begin(), indices.end(), 0);
    long long seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(indices.begin(), indices.end(), std::default_random_engine(seed));
    QVector<quint64> mineIndices(indices.mid(0, mGridModel->mineCount()));

    // build the grid
    QVector<models::CellModel *> grid(numberOfCells);
    for (int i = 0; i < grid.size(); ++i)
    {
        // set CellModel(hidden = true, flagged = false, isBomb = false, surroundingBombs = 0)
        grid[i] = new models::CellModel(true, false, false, 0);
    }
        
    // set mines in grid
    foreach(quint64 mineIndex, mineIndices)
    {
        // set bomb
        grid[mineIndex]->setIsBomb(true);

        quint64 numberOfColumns = mGridModel->columns();
        quint64 numberOfRow = mGridModel->rows();


        updateSurroundingCell(mineIndex, numberOfColumns, numberOfRow, 
                std::bind(&GridController::increaseSurroundingBombsCount, this, std::placeholders::_1));

        /*

        // increase surrounding cells
        quint64 columnIndex = mineIndex % columns;

        bool notFirstColumn = columnIndex  > 0;
        bool notFirstRow = mineIndex >= columns; 
        bool notLastColumn = (columnIndex + 1) < columns;
        bool notLastRow = mineIndex < ((columns * rows) - columns);

        if(notFirstRow && notFirstColumn)
        {
            // increase upper left cell
            grid[mineIndex - columns - 1]->increaseSurroundingBombsCount();
        }

        if(notFirstRow)
        {
            // increase upper cell
            grid[mineIndex - columns]->increaseSurroundingBombsCount();
        }

        if(notFirstRow && notLastColumn)
        {
            // increase upper right cell
            grid[mineIndex - columns + 1]->increaseSurroundingBombsCount();
        }

        if(notLastColumn)
        {
            // increase right cell
            grid[mineIndex + 1]->increaseSurroundingBombsCount();
        }

        if(notLastColumn && notLastRow)
        {
            // increase lower right cell
            grid[mineIndex + columns + 1]->increaseSurroundingBombsCount();
        }

        if(notLastRow)
        {
            // increase lower cell
            grid[mineIndex + columns]->increaseSurroundingBombsCount();
        }

        if(notLastRow && notFirstColumn) 
        {
            // increase lower left cell
            grid[mineIndex + columns - 1]->increaseSurroundingBombsCount();
        }

        if(notFirstColumn) 
        {
            // increase left cell
            grid[mineIndex - 1]->increaseSurroundingBombsCount();
        }
        */
    }

    emit updateGrid(grid);
}


void GridController::revealCell(quint64 index)
{
    QObject *obj = mGridModel->grid().at(index);
    models::CellModel* cell = qobject_cast<models::CellModel *>(obj);

    // don't reveal flagged cells
    if(cell->flagged()) return;

    // if cell is a bomb then game over
    if(cell->isBomb())
    {
        revealAllCells();
        qDebug() << "ur a NOOB... lol";
    }
    else if(cell->hidden()) 
    {
        cell->setHidden(false);

        if(cell->surroundingBombs() == 0)
        {
            quint64 numberOfColumns = mGridModel->columns();
            quint64 numberOfRow = mGridModel->rows();

            updateSurroundingCell(index, numberOfColumns, numberOfRow, 
                    std::bind(&GridController::revealCell, this, std::placeholders::_1));
        }
    }
}

void GridController::revealAllCells()
{
    foreach(QObject* obj, mGridModel->grid())
    {
        qobject_cast<models::CellModel *>(obj)->setHidden(false);
    }
}

void GridController::toggleFlagInCell(quint64 index)
{
    QObject *obj = mGridModel->grid().at(index);
    models::CellModel* cell = qobject_cast<models::CellModel *>(obj);

    if(cell->hidden())
    {
        if(cell->flagged())
        {
            cell->setFlagged(false);
            mGridModel->increaseFlags();
        }
        else 
        {
            cell->setFlagged(true);
            mGridModel->decreaseFlags();
        }
    }
}

void GridController::increaseSurroundingBombsCount(quint64 cellIndex)
{
    qDebug() << "index: " << cellIndex;
    QObject *obj = mGridModel->grid().at(cellIndex);
    models::CellModel* cell = qobject_cast<models::CellModel *>(obj);
    qDebug() << "ende";
    //cell->setSurroundingBombs(1);
}

void GridController::updateSurroundingCell(const quint64 cellIndex,
    const quint64 numberOfColumns,
    const quint64 numberOfRow,
    const std::function<void(quint64)> updateFunction)
{
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



} // namespace controllers



