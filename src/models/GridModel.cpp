#include "../../inc/models/GridModel.h"

namespace models
{

GridModel::GridModel(const QVector<CellModel *> grid,
                     const quint64 rows,
                     const quint64 columns,
                     const quint64 mineCount)
    : mGrid(grid),
      mRows(rows),
      mColumns(columns),
      mMineCount(mineCount)
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

quint64 GridModel::rows()
{
    return mRows;
}

quint64 GridModel::columns()
{
    return mColumns;
}

quint64 GridModel::mineCount()
{
    return mMineCount;
}

void GridModel::setGrid(const QVector<CellModel *> grid)
{
    mGrid = grid;
    emit gridChanged();
}

void GridModel::setRows(const quint64 rows)
{
    mRows = rows;
    emit rowsChanged();
}

void GridModel::setColumns(const quint64 columns)
{
    mColumns = columns;
    emit columnsChanged();
}

void GridModel::setMineCount(const quint64 mineCount)
{
    mMineCount = mineCount;
    emit mineCountChanged();
}

} // namespace models
