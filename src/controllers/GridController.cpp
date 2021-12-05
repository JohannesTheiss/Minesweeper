#include "../../inc/controllers/GridController.h"


namespace controllers
{

void GridController::newGrid()
{
    // load settings
    
    quint64 numberOfRows = 16;
    quint64 numberOfColumns = 30;
    quint64 numberOfMines = 99;

    mGridModel->setRows(numberOfRows);
    mGridModel->setColumns(numberOfColumns);
    mGridModel->setMineCount(numberOfMines);

    generateGrid(mGridModel);
}

void GridController::generateGrid(models::GridModel *gridModel)
{
    quint64 numberOfCells = gridModel->rows() * gridModel->columns();

    // generate the mines
    QVector<quint64> indices(numberOfCells);
    std::iota(indices.begin(), indices.end(), 0);
    long long seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(indices.begin(), indices.end(), std::default_random_engine(seed));
    QVector<quint64> mineIndices(indices.begin(), indices.begin() + gridModel->mineCount());
    //QVector<quint64> mineIndices({15, 6});

    // build the grid
    QVector<models::CellModel *> grid(numberOfCells);
    for (int i = 0; i < grid.size(); ++i)
    {
        grid[i] = new models::CellModel(true, false, false, 0);
    }
        
    // set mines in grid
    foreach(quint64 mineIndex, mineIndices)
    {
        // set bomb
        grid[mineIndex]->setIsBomb(true);

        quint64 columns = gridModel->columns();
        quint64 rows = gridModel->rows();

        // increase surrounding cells
        quint64 x = mineIndex % columns;

        bool notFirstColumn = x > 0;
        bool notFirstRow = mineIndex >= columns; 
        bool notLastColumn = (x + 1) < columns;
        bool notLastRow = mineIndex < ((columns * rows) - columns);

        /*
        qDebug() << "mineIndex = " << mineIndex << " / x = " << x;
        qDebug() << "notFirstColumn = " << notFirstColumn
                << "/ notFirstRow = " << notFirstRow
                << "/ notLastColumn = " << notLastColumn
                << "/ notLastRow = " << notLastRow;
                */

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
    }


    gridModel->setGrid(grid);

    mGridModel = gridModel;
}


void GridController::revealCell(quint64 index)
{
    QObject *obj = mGridModel->grid().at(index);
    models::CellModel* cell = qobject_cast<models::CellModel *>(obj);

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
            quint64 columns = mGridModel->columns();
            quint64 rows = mGridModel->rows();

            // reveal surrounding cells
            quint64 x = index % columns;

            bool notFirstColumn = x > 0;
            bool notFirstRow = index >= columns; 
            bool notLastColumn = (x + 1) < columns;
            bool notLastRow = index < ((columns * rows) - columns);

            if(notFirstRow && notFirstColumn)
            {
                // reveal upper left cell
                revealCell(index - columns - 1);
            }

            if(notFirstRow)
            {
                // reveal upper cell
                revealCell(index - columns);
            }

            if(notFirstRow && notLastColumn)
            {
                // reveal upper right cell
                revealCell(index - columns + 1);
            }

            if(notLastColumn)
            {
                // reveal right cell
                revealCell(index + 1);
            }

            if(notLastColumn && notLastRow)
            {
                // reveal lower right cell
                revealCell(index + columns + 1);
            }

            if(notLastRow)
            {
                // reveal lower cell
                revealCell(index + columns);
            }

            if(notLastRow && notFirstColumn) 
            {
                // reveal lower left cell
                revealCell(index + columns - 1);
            }

            if(notFirstColumn) 
            {
                // reveal left cell
                revealCell(index - 1);
            }
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


} // namespace controllers
