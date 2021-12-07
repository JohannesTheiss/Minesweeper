#include "../../inc/controllers/GridController.h"


namespace controllers
{

GridController::GridController(models::GridModel *gridModel, QObject *parent)
    : QObject(parent),
      mGridModel(gridModel)
{
    // TODO what if the rows and columns are 0
    // generate a first grid
    generateGrid(mGridModel->rows(), mGridModel->columns(), mGridModel->mineCount());
}

void GridController::generateGrid(const quint64 numberOfRow,
                const quint64 numberOfColumns,
                const quint64 numberOfMines)
{
    // update the model
    mGridModel->setRows(numberOfRow);
    mGridModel->setColumns(numberOfColumns);
    mGridModel->setMineCount(numberOfMines);
    mGridModel->setFlagCount(numberOfMines);
    quint64 numberOfCells = mGridModel->rows() * mGridModel->columns();

    // generate the mines
    QVector<quint64> indices(numberOfCells);
    std::iota(indices.begin(), indices.end(), 0);
    long long seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(indices.begin(), indices.end(), std::default_random_engine(seed));
    QVector<quint64> mineIndices(indices.mid(0, mGridModel->mineCount()));

    // build a new the grid
    QVector<models::CellModel *> grid(numberOfCells);
    for (int i = 0; i < grid.size(); ++i)
    {
        // set CellModel(hidden = true, flagged = false, isBomb = false, surroundingBombs = 0)
        grid[i] = new models::CellModel(true, false, false, 0);
    }

    // set the grid
    mGridModel->setGrid(grid);
        
    // set mines in grid
    foreach(quint64 mineIndex, mineIndices)
    {
        // set bomb
        grid[mineIndex]->setIsBomb(true);

        // culc. the values surrounding cells
        updateSurroundingCell(mineIndex,
                std::bind(&GridController::increaseSurroundingBombsCount, this, std::placeholders::_1));
    }
}


void GridController::revealCell(const quint64 index)
{
    models::CellModel* cell = mGridModel->grid().at(index);

    // TODO if first hit is a bomb...

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

        // if there are no surrounding bombs
        if(cell->surroundingBombs() == 0)
        {
            // reveal surrounding cells
            updateSurroundingCell(index,
                    std::bind(&GridController::revealCell, this, std::placeholders::_1));
        }
    }
}

void GridController::revealAllCells()
{
    foreach(models::CellModel* cell, mGridModel->grid())
    {
        cell->setHidden(false);
    }
}

void GridController::toggleFlagInCell(const quint64 index)
{
    models::CellModel* cell = mGridModel->grid().at(index);

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

void GridController::increaseSurroundingBombsCount(const quint64 cellIndex)
{
    models::CellModel *cell = mGridModel->grid().at(cellIndex);
    cell->setSurroundingBombs(cell->surroundingBombs() + 1);
}

void GridController::increaseFlagCount()
{
    mGridModel->setFlagCount(mGridModel->flagCount() + 1);
}

void GridController::decreaseFlagCount()
{
    mGridModel->setFlagCount(mGridModel->flagCount() - 1);
}

void GridController::updateSurroundingCell(const quint64 cellIndex,
    const std::function<void(quint64)> updateFunction)
{
    quint64 numberOfColumns = mGridModel->columns();
    quint64 numberOfRow = mGridModel->rows();
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



