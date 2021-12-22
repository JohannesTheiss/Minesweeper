#ifndef GAMEOBSERVER_H
#define GAMEOBSERVER_H

#include <QObject>

#include "../../models/CellModel.h"
#include "../../models/GameModel.h"

namespace observers
{

// observer-class for the GameModel
class GameObserver : public QObject
{
    Q_OBJECT

    public:
        GameObserver(const models::GameModel *gameModel, QObject *parent = nullptr);

        ~GameObserver() = default;

        // setters and getters as part of the interface
        // for any object to communicate with the model via the observer

        // getter methods
        QVector<models::CellModel *> grid() const;
        quint64 rows() const;
        quint64 columns() const;
        quint64 mineCount() const;
        qint64 flagCount() const;
        quint64 timePlayed() const;
        models::SizeScaling scaling() const;

        // setter methods
        void setGrid(const QVector<models::CellModel *> grid);
        void setRows(const quint64 rows);
        void setColumns(const quint64 columns);
        void setMineCount(const quint64 mineCount);
        void setFlagCount(const qint64 flagCount);
        void setTimePlayed(const quint64 timePlayed);
        void setScaling(const models::SizeScaling scaling);

    signals:
        // signals that trigger setter operation on the model
        void updateModelGrid(const QVector<models::CellModel *> grid);
        void updateModelRows(const quint64 rows);
        void updateModelColumns(const quint64 columns);
        void updateModelMineCount(const quint64 mineCount);
        void updateModelFlagCount(const qint64 flagCount);
        void updateModelTimePlayed(const quint64 timePlayed);
        void updateModelScaling(const models::SizeScaling scaling);

    private slots:
        // slots that are called when values are updated in the model
        void updateObserverGrid(const QVector<models::CellModel *> grid);
        void updateObserverRows(const quint64 rows);
        void updateObserverColumns(const quint64 columns);
        void updateObserverMineCount(const quint64 mineCount);
        void updateObserverFlagCount(const qint64 flagCount);
        void updateObserverTimePlayed(const quint64 timePlayed);
        void updateObserverScaling(const models::SizeScaling scaling);

    private:
        // initiates all connections between model and observer
        void initObserver(const models::GameModel *gameModel);

        QVector<models::CellModel *> mGrid;
        quint64 mRows;
        quint64 mColumns;
        quint64 mMineCount;
        qint64 mFlagCount;
        quint64 mTimePlayed;
        models::SizeScaling mScaling;
};

} // namespace observers

#endif // GAMEOBSERVER_H
