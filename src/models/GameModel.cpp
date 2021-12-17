#include "../../inc/models/GameModel.h"

namespace models
{

GameModel::GameModel(const QVector<CellModel *> grid,
                     const quint64 rows,
                     const quint64 columns,
                     const quint64 mineCount,
                     const qint64 flagCount,
                     const quint64 timePlayed,
                     const SizeScaling scaling)
    : mGrid(grid),
      mRows(rows),
      mColumns(columns),
      mMineCount(mineCount),
      mFlagCount(flagCount),
      mTimePlayed(timePlayed),
      mScaling(scaling)
{
}

QVector<CellModel *> GameModel::grid() const
{
    return mGrid;
}

quint64 GameModel::rows() const
{
    return mRows;
}

quint64 GameModel::columns() const
{
    return mColumns;
}

quint64 GameModel::mineCount() const
{
    return mMineCount;
}

qint64 GameModel::flagCount() const
{
    return mFlagCount;
}

quint64 GameModel::timePlayed() const
{
    return mTimePlayed;
}

models::SizeScaling GameModel::scaling() const
{
    return mScaling;
}

void GameModel::setGrid(const QVector<models::CellModel *> grid)
{
    mGrid = grid;
    emit gridChanged(mGrid);
}

void GameModel::setRows(const quint64 rows)
{
    mRows = rows;
    emit rowsChanged(mRows);
}

void GameModel::setColumns(const quint64 columns)
{
    mColumns = columns;
    emit columnsChanged(mColumns);
}

void GameModel::setMineCount(const quint64 mineCount)
{
    mMineCount = mineCount;
    emit mineCountChanged(mMineCount);
}

void GameModel::setFlagCount(const qint64 flagCount)
{
    mFlagCount = flagCount;
    emit flagCountChanged(mFlagCount);
}

void GameModel::setTimePlayed(const quint64 timePlayed)
{
    mTimePlayed = timePlayed;
    emit timePlayedChanged(mTimePlayed);
}

void GameModel::setScaling(const models::SizeScaling scaling)
{
    mScaling = scaling;
    emit scalingChanged(mScaling);
}

} // namespace models
