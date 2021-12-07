#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <random>
#include <numeric>
#include <iterator>
#include <thread>
#include <mutex>

#include <QObject>

#include <QDebug>

#include "../models/CellModel.h"
#include "../models/GameModel.h"

namespace controllers
{

class GameController : public QObject
{
    Q_OBJECT

    public:
        GameController(models::GameModel *gameModel,
                QObject *parent = nullptr);


    public slots:
        void generateGrid(const quint64 numberOfRow,
                const quint64 numberOfColumns,
                const quint64 numberOfMines);

        void revealCell(const quint64 index);
        void revealAllCells();
    
        void toggleFlagInCell(const quint64 index);

        void startGame();
        void togglePauseGame();
        void endGame();

    private:
        void increaseSurroundingBombsCount(const quint64 cellIndex);
        void increaseFlagCount();
        void decreaseFlagCount();
        void threadedTimer();

        void updateSurroundingCell(const quint64 cellIndex,
                const std::function<void(quint64)> updateFunction);

        bool mGameStarted;
        bool mTimerRunning;
        std::thread mTimerThread;
        std::mutex mMutex;

        models::GameModel *mGameModel;
};

} // namespace controllers

#endif // GAMECONTROLLER_H
