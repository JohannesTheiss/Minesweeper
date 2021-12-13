#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <random>
#include <numeric>
#include <iterator>

#include <iostream>
#include <QTimer>

#include <QObject>

#include <QDebug>

#include "../data/JsonManager.h"

#include "observers/GameObserver.h"

#include "../models/CellModel.h"
#include "../models/GameModel.h"

namespace controllers
{

class GameController : public QObject
{
    Q_OBJECT

    public:
        GameController(observers::GameObserver *gameObserver,
                QObject *parent = nullptr);

        ~GameController();


    public slots:
        void revealCell(const quint64 index);
        void revealAllCells();
    
        void toggleFlagInCell(const quint64 index);

        void initGame();
        void startGame();
        void togglePauseGame();
        void endGame();

        void setGameMode(const quint64 numberOfRows,
                         const quint64 numberOfColumns,
                         const quint64 numberOfMines);
        void setScaling(const int scaling);

        void updateTime();

    private:
        void generateGrid();
        void generateMines();
        quint64 addMine();
        void removeMine(const quint64 mineIndex);

        void increaseSurroundingBombsCount(const quint64 cellIndex);
        void decreaseSurroundingBombsCount(const quint64 cellIndex);
        void increaseFlagCount();
        void decreaseFlagCount();

        void updateSurroundingCell(const quint64 cellIndex,
                const std::function<void(quint64)> updateFunction);

        void checkForWin();

        bool mFirstReveal;
        bool mGameStarted;
        QTimer *timer;

        QVector<quint64> mMineIndices;
        observers::GameObserver *mGameObserver;
        data::JsonManager *mJsonManager;

        const QString mJsonObjectName = "configuration";
};

} // namespace controllers

#endif // GAMECONTROLLER_H
