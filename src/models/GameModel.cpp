#include "../../inc/models/GameModel.h"

#include <QDebug>

namespace models
{

GameModel::GameModel(const QVector<CellModel *> grid,
                     const quint64 rows,
                     const quint64 columns,
                     const quint64 mineCount,
                     const qint64 flagCount,
                     const quint64 timePlayed,
                     const SizeScaling scaling,
                     const QVector<quint64> mineIndices)
    : mGrid(grid),
      mRows(rows),
      mColumns(columns),
      mMineCount(mineCount),
      mFlagCount(flagCount),
      mTimePlayed(timePlayed),
      mScaling(scaling),
      mMineIndices(mineIndices)
{
}

void GameModel::appendToMineIndices(quint64 mineIndex)
{
    mMineIndices.append(mineIndex);
    emit mineIndicesChanged();
}

void GameModel::removeFromMineIndices(const quint64 mineIndex)
{
    mMineIndices.removeOne(mineIndex);
    emit mineIndicesChanged();
}

QVector<CellModel *> GameModel::grid()
{
    return mGrid;
}

quint64 GameModel::rows()
{
    return mRows;
}

quint64 GameModel::columns()
{
    return mColumns;
}

quint64 GameModel::mineCount()
{
    return mMineCount;
}

qint64 GameModel::flagCount()
{
    return mFlagCount;
}

quint64 GameModel::timePlayed()
{
    return mTimePlayed;
}

models::SizeScaling GameModel::scaling()
{
    return mScaling;
}

QVector<quint64> GameModel::mineIndices()
{
    return mMineIndices;
}

void GameModel::setGrid(const QVector<models::CellModel *> grid)
{
    mGrid = grid;
    emit gridChanged();
}

void GameModel::setRows(const quint64 rows)
{
    mRows = rows;
    emit rowsChanged();
}

void GameModel::setColumns(const quint64 columns)
{
    mColumns = columns;
    emit columnsChanged();
}

void GameModel::setMineCount(const quint64 mineCount)
{
    mMineCount = mineCount;
    emit mineCountChanged();
}

void GameModel::setFlagCount(const qint64 flagCount)
{
    mFlagCount = flagCount;
    emit flagCountChanged();
}

void GameModel::setTimePlayed(const quint64 timePlayed)
{
    mTimePlayed = timePlayed;
    emit timePlayedChanged();
}

void GameModel::setScaling(const models::SizeScaling scaling)
{
    mScaling = scaling;
    emit scalingChanged();
}

void GameModel::setMineIndices(const QVector<quint64> mineIndices)
{
    mMineIndices = mineIndices;
}

} // namespace models
