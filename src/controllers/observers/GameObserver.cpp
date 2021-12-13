#include "../../../inc/controllers/observers/GameObserver.h"

namespace observers
{

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

QVector<models::CellModel *> GameObserver::grid() const
{
    return mGrid;
}

quint64 GameObserver::rows() const
{
    return mRows;
}

quint64 GameObserver::columns() const
{
    return mColumns;
}

quint64 GameObserver::mineCount() const
{
    return mMineCount;
}

qint64 GameObserver::flagCount() const
{
    return mFlagCount;
}

quint64 GameObserver::timePlayed() const
{
    return mTimePlayed;
}

models::SizeScaling GameObserver::scaling() const
{
    return mScaling;
}

void GameObserver::setGrid(const QVector<models::CellModel *> grid)
{
    mGrid = grid;
    emit updateModelGrid(mGrid);
}

void GameObserver::setRows(const quint64 rows)
{
    mRows = rows;
    emit updateModelRows(mRows);
}

void GameObserver::setColumns(const quint64 columns)
{
    mColumns = columns;
    emit updateModelColumns(mColumns);
}

void GameObserver::setMineCount(const quint64 mineCount)
{
    mMineCount = mineCount;
    emit updateModelMineCount(mMineCount);
}

void GameObserver::setFlagCount(const qint64 flagCount)
{
    mFlagCount = flagCount;
    emit updateModelFlagCount(mFlagCount);
}

void GameObserver::setTimePlayed(const quint64 timePlayed)
{
    mTimePlayed = timePlayed;
    emit updateModelTimePlayed(mTimePlayed);
}

void GameObserver::setScaling(const models::SizeScaling scaling)
{
    mScaling = scaling;
    emit updateModelScaling(mScaling);
}

void GameObserver::updateObserverGrid(const QVector<models::CellModel *> grid)
{
    mGrid = grid;
}

void GameObserver::updateObserverRows(const quint64 rows)
{
    mRows = rows;
}

void GameObserver::updateObserverColumns(const quint64 columns)
{
    mColumns = columns;
}

void GameObserver::updateObserverMineCount(const quint64 mineCount)
{
    mMineCount = mineCount;
}

void GameObserver::updateObserverFlagCount(const qint64 flagCount)
{
    mFlagCount = flagCount;
}

void GameObserver::updateObserverTimePlayed(const quint64 timePlayed)
{
    mTimePlayed = timePlayed;
}

void GameObserver::updateObserverScaling(const models::SizeScaling scaling)
{
    mScaling = scaling;
}

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
