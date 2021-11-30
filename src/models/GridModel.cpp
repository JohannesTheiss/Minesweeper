#include "../../inc/models/GridModel.h"

namespace models
{

GridModel::GridModel()
    : mGrid(),
      mRows(0),
      mColumns(0),
      mMineCount(0)
{
}

QVector<QObject *> GridModel::grid()
{
    QVector <QObject *> convertedGrid;

    // convert grid in order to make
    // it accessible by a qt frontend
    foreach(CellModel *cell, mGrid)
    {
        convertedGrid.append(cell);
    }

    return convertedGrid;
}

unsigned int GridModel::rows()
{
    return mRows;
}

unsigned int GridModel::columns()
{
    return mColumns;
}

unsigned int GridModel::mineCount()
{
    return mMineCount;
}

void GridModel::setGrid(const QVector<CellModel *> grid)
{
    mGrid = grid;
    emit gridChanged();
}

void GridModel::setRows(const unsigned int rows)
{
    mRows = rows;
    emit rowsChanged();
}

void GridModel::setColumns(const unsigned int columns)
{
    mColumns = columns;
    emit columnsChanged();
}

void GridModel::setMineCount(const unsigned int mineCount)
{
    mMineCount = mineCount;
    emit mineCountChanged();
}

} // namespace models
