#include "../../../inc/controllers/observers/GameObserver.h"

namespace observers
{

// <summary> Custom constructor for GameObserver-objects
//           that builds the connection to a GameModel-object</summary>
// <param name="gameModel"> Pointer to a GameModel-object </param>
// <param name="parent"> Optional pointer to a parent object </param>
GameObserver::GameObserver(const models::GameModel *gameModel, QObject *parent)
    : QObject(parent),
      mGrid(gameModel->grid()),
      mRows(gameModel->rows()),
      mColumns(gameModel->columns()),
      mMineCount(gameModel->mineCount()),
      mFlagCount(gameModel->flagCount()),
      mTimePlayed(gameModel->timePlayed()),
      mScaling(gameModel->scaling())
{
    initObserver(gameModel);
}

// <summary> Getter for member mGrid </summary>
// <returns> QVector<CellModel *> mGrid </returns>
QVector<models::CellModel *> GameObserver::grid() const
{
    return mGrid;
}

// <summary> Getter for member mRows </summary>
// <returns> quint64 mRows </returns>
quint64 GameObserver::rows() const
{
    return mRows;
}

// <summary> Getter for member mColumns </summary>
// <returns> quint64 mColumns </returns>
quint64 GameObserver::columns() const
{
    return mColumns;
}

// <summary> Getter for member mMineCount </summary>
// <returns> quint64 mMineCount </returns>
quint64 GameObserver::mineCount() const
{
    return mMineCount;
}

// <summary> Getter for member mFlagCount </summary>
// <returns> qint64 mFlagCount </returns>
qint64 GameObserver::flagCount() const
{
    return mFlagCount;
}

// <summary> Getter for member mTimePlayed </summary>
// <returns> quint64 mTimePlayed </returns>
quint64 GameObserver::timePlayed() const
{
    return mTimePlayed;
}

// <summary> Getter for member mScaling </summary>
// <returns> enum flag from SizeScaling mScaling </returns>
models::SizeScaling GameObserver::scaling() const
{
    return mScaling;
}

// <summary> Setter for member mGrid </summary>
// <param name="grid"> QVector<CellModel *> value for "mGrid" </param>
// <returns> Nothing </returns>
void GameObserver::setGrid(const QVector<models::CellModel *> grid)
{
    mGrid = grid;
    emit updateModelGrid(mGrid);
}

// <summary> Setter for member mRows </summary>
// <param name="rows"> quint64 value for "mRows" </param>
// <returns> Nothing </returns>
void GameObserver::setRows(const quint64 rows)
{
    mRows = rows;
    emit updateModelRows(mRows);
}

// <summary> Setter for member mColumns </summary>
// <param name="columns"> quint64 value for "mColumns" </param>
// <returns> Nothing </returns>
void GameObserver::setColumns(const quint64 columns)
{
    mColumns = columns;
    emit updateModelColumns(mColumns);
}

// <summary> Setter for member mMineCount </summary>
// <param name="mineCount"> quint64 value for "mMineCount" </param>
// <returns> Nothing </returns>
void GameObserver::setMineCount(const quint64 mineCount)
{
    mMineCount = mineCount;
    emit updateModelMineCount(mMineCount);
}

// <summary> Setter for member mFlagCount </summary>
// <param name="flagCount"> qint64 value for "mFlagCount" </param>
// <returns> Nothing </returns>
void GameObserver::setFlagCount(const qint64 flagCount)
{
    mFlagCount = flagCount;
    emit updateModelFlagCount(mFlagCount);
}

// <summary> Setter for member mTimePlayed </summary>
// <param name="timePlayed"> quint64 value for "mTimePlayed" </param>
// <returns> Nothing </returns>
void GameObserver::setTimePlayed(const quint64 timePlayed)
{
    mTimePlayed = timePlayed;
    emit updateModelTimePlayed(mTimePlayed);
}

// <summary> Setter for member mScaling </summary>
// <param name="scaling"> enum flag of SizeScaling value for "mScaling" </param>
// <returns> Nothing </returns>
void GameObserver::setScaling(const models::SizeScaling scaling)
{
    mScaling = scaling;
    emit updateModelScaling(mScaling);
}

// <summary> Slot for synchronising mGrid with GameModel.mGrid </summary>
// <param name="grid"> QVector<CellModel *> value for "mGrid" </param>
// <returns> Nothing </returns>
void GameObserver::updateObserverGrid(const QVector<models::CellModel *> grid)
{
    mGrid = grid;
}

// <summary> Slot for synchronising mRows with GameModel.mRows </summary>
// <param name="rows"> quint64 value for "mRows" </param>
// <returns> Nothing </returns>
void GameObserver::updateObserverRows(const quint64 rows)
{
    mRows = rows;
}

// <summary> Slot for synchronising mColumns with GameModel.mColumns </summary>
// <param name="columns"> quint64 value for "mColumns" </param>
// <returns> Nothing </returns>
void GameObserver::updateObserverColumns(const quint64 columns)
{
    mColumns = columns;
}

// <summary> Slot for synchronising mMineCount with GameModel.mMineCount </summary>
// <param name="mineCount"> quint64 value for "mMineCount" </param>
// <returns> Nothing </returns>
void GameObserver::updateObserverMineCount(const quint64 mineCount)
{
    mMineCount = mineCount;
}

// <summary> Slot for synchronising mFlagCount with GameModel.mFlagCount </summary>
// <param name="flagCount"> qint64 value for "mFlagCount" </param>
// <returns> Nothing </returns>
void GameObserver::updateObserverFlagCount(const qint64 flagCount)
{
    mFlagCount = flagCount;
}

// <summary> Slot for synchronising mTimePlayed with GameModel.mTimePlayed </summary>
// <param name="timePlayed"> quint64 value for "mTimePlayed" </param>
// <returns> Nothing </returns>
void GameObserver::updateObserverTimePlayed(const quint64 timePlayed)
{
    mTimePlayed = timePlayed;
}

// <summary> Slot for synchronising mScaling with GameModel.mScaling </summary>
// <param name="scaling"> enum flag of SizeScaling value for "mScaling" </param>
// <returns> Nothing </returns>
void GameObserver::updateObserverScaling(const models::SizeScaling scaling)
{
    mScaling = scaling;
}

// <summary> Establishes all connections between observer and model slots and signals
//           that are necessary for synchronising their data </summary>
// <param name="gameModel"> Pointer to GameModel-object,
//                          which provides access to the interface of that object </param>
// <returns> Nothing </returns>
void GameObserver::initObserver(const models::GameModel *gameModel)
{
    QObject::connect(this, SIGNAL(updateModelGrid(const QVector<models::CellModel *>)),
                     gameModel, SLOT(setGrid(const QVector<models::CellModel *>)));

    QObject::connect(gameModel, SIGNAL(gridChanged(const QVector<models::CellModel *>)),
                     this, SLOT(updateObserverGrid(const QVector<models::CellModel *>)));

    QObject::connect(this, SIGNAL(updateModelRows(const quint64)),
                     gameModel, SLOT(setRows(const quint64)));

    QObject::connect(gameModel, SIGNAL(rowsChanged(const quint64)),
                     this, SLOT(updateObserverRows(const quint64)));

    QObject::connect(this, SIGNAL(updateModelColumns(const quint64)),
                     gameModel, SLOT(setColumns(const quint64)));

    QObject::connect(gameModel, SIGNAL(columnsChanged(const quint64)),
                     this, SLOT(updateObserverColumns(const quint64)));

    QObject::connect(this, SIGNAL(updateModelMineCount(const quint64)),
                     gameModel, SLOT(setMineCount(const quint64)));

    QObject::connect(gameModel, SIGNAL(mineCountChanged(const quint64)),
                     this, SLOT(updateObserverMineCount(const quint64)));

    QObject::connect(this, SIGNAL(updateModelFlagCount(const qint64)),
                     gameModel, SLOT(setFlagCount(const qint64)));

    QObject::connect(gameModel, SIGNAL(flagCountChanged(const qint64)),
                     this, SLOT(updateObserverFlagCount(const qint64)));

    QObject::connect(this, SIGNAL(updateModelTimePlayed(const quint64)),
                     gameModel, SLOT(setTimePlayed(const quint64)));

    QObject::connect(gameModel, SIGNAL(timePlayedChanged(const quint64)),
                     this, SLOT(updateObserverTimePlayed(const quint64)));

    QObject::connect(this, SIGNAL(updateModelScaling(const models::SizeScaling)),
                     gameModel, SLOT(setScaling(const models::SizeScaling)));

    QObject::connect(gameModel, SIGNAL(scalingChanged(const models::SizeScaling)),
                     this, SLOT(updateObserverScaling(const models::SizeScaling)));
}

} // namespace observers
