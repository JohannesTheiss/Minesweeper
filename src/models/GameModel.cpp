#include "../../inc/models/GameModel.h"

namespace models
{

// <summary> Custom constructor for GameModel-objects </summary>
// <param name="grid"> QVector of CellModel-pointers </param>
// <param name="rows"> quint64 number of rows </param>
// <param name="columns"> quint64 number of columns </param>
// <param name="mineCount"> quint64 number of mines in the grid </param>
// <param name="flagCount"> qint64 number of flags left to set on the grid </param>
// <param name="timePlayed"> quint64 time since starting the game </param>
// <param name="scaling"> enum value for selecting the text size scaling </param>
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

// <summary> Getter for member mGrid </summary>
// <returns> QVector<CellModel *> mGrid </returns>
QVector<CellModel *> GameModel::grid() const
{
    return mGrid;
}

// <summary> Getter for member mRows </summary>
// <returns> quint64 mRows </returns>
quint64 GameModel::rows() const
{
    return mRows;
}

// <summary> Getter for member mColumns </summary>
// <returns> quint64 mColumns </returns>
quint64 GameModel::columns() const
{
    return mColumns;
}

// <summary> Getter for member mMineCount </summary>
// <returns> quint64 mMineCount </returns>
quint64 GameModel::mineCount() const
{
    return mMineCount;
}

// <summary> Getter for member mFlagCount </summary>
// <returns> qint64 mFlagCount </returns>
qint64 GameModel::flagCount() const
{
    return mFlagCount;
}

// <summary> Getter for member mTimePlayed </summary>
// <returns> quint64 mTimePlayed </returns>
quint64 GameModel::timePlayed() const
{
    return mTimePlayed;
}

// <summary> Getter for member mScaling </summary>
// <returns> enum flag from SizeScaling mScaling </returns>
models::SizeScaling GameModel::scaling() const
{
    return mScaling;
}

// <summary> Setter for member mGrid </summary>
// <param name="grid"> QVector<CellModel *> value for "mGrid" </param>
// <returns> Nothing </returns>
void GameModel::setGrid(const QVector<models::CellModel *> grid)
{
    mGrid = grid;
    emit gridChanged(mGrid);
}

// <summary> Setter for member mRows </summary>
// <param name="rows"> quint64 value for "mRows" </param>
// <returns> Nothing </returns>
void GameModel::setRows(const quint64 rows)
{
    mRows = rows;
    emit rowsChanged(mRows);
}

// <summary> Setter for member mColumns </summary>
// <param name="columns"> quint64 value for "mColumns" </param>
// <returns> Nothing </returns>
void GameModel::setColumns(const quint64 columns)
{
    mColumns = columns;
    emit columnsChanged(mColumns);
}

// <summary> Setter for member mMineCount </summary>
// <param name="mineCount"> quint64 value for "mMineCount" </param>
// <returns> Nothing </returns>
void GameModel::setMineCount(const quint64 mineCount)
{
    mMineCount = mineCount;
    emit mineCountChanged(mMineCount);
}

// <summary> Setter for member mFlagCount </summary>
// <param name="flagCount"> qint64 value for "mFlagCount" </param>
// <returns> Nothing </returns>
void GameModel::setFlagCount(const qint64 flagCount)
{
    mFlagCount = flagCount;
    emit flagCountChanged(mFlagCount);
}

// <summary> Setter for member mTimePlayed </summary>
// <param name="timePlayed"> quint64 value for "mTimePlayed" </param>
// <returns> Nothing </returns>
void GameModel::setTimePlayed(const quint64 timePlayed)
{
    mTimePlayed = timePlayed;
    emit timePlayedChanged(mTimePlayed);
}

// <summary> Setter for member mScaling </summary>
// <param name="scaling"> enum flag of SizeScaling value for "mScaling" </param>
// <returns> Nothing </returns>
void GameModel::setScaling(const models::SizeScaling scaling)
{
    mScaling = scaling;
    emit scalingChanged(mScaling);
}

} // namespace models
