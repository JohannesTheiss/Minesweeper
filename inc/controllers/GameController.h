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

        /*
         * Custom constructor for GameController-objects 
         * it creates a timer and loads/sets the last game configuration
         */
        GameController(observers::GameObserver *gameObserver,
                QObject *parent = nullptr);

        /* 
         * Custom destructor for GameController-objects
         * it saves the current game configuration to JSON
         */
        ~GameController();

    public slots:
         /*
          * Reveal the cell at the given index,
          * check if the game is won or lost
          * and may reveal surrounding cells as well
          */
        void revealCell(const quint64 index);

        // Reveal all cells on the grid
        void revealAllCells();
    
        // Toggle the flag within a cell at the given index
        void toggleFlagInCell(const quint64 index);

        /*
         * Initialize the game by 
         * end the current game,
         * reset the flag count, time played
         * and generate a new grid
         */
        void initGame();

        /*
         * Start the game by
         * reset mFirstReveal, mGameStarted
         * and start the timer
         */
        void startGame();

        // Toggle the game state between pause and play
        void togglePauseGame();

        /*
         * End the current game 
         * and submit the needed information to the statistics controller
         */
        void endGame(const bool wonOrLost);

        // Set a new game mode and initialize it
        void setGameMode(quint64 numberOfRows,
                         quint64 numberOfColumns,
                         quint64 numberOfMines);

        // Set the scaling of the application 
        void setScaling(const int scaling);

        // Increase the current time played by one
        void updateTime();

    signals:
        // Emits that the games is ended
        void gameEnded(const quint64 numberOfRow,
                const quint64 numberOfColumns,
                const quint64 numberOfMines,
                const quint64 time,
                const bool win);

    private:
        // Generate a new grid by the rows and columns from the GameModel       
        void generateGrid();

        /*
         * Generate all mines for the grid by 
         * the mine counter from the GameModel
         */
        void generateMines();

        // Add one new mine at random position in the current grid
        quint64 addMine();

        // Remove one mine at a given index from the current grid
        void removeMine(const quint64 mineIndex);

        // Increase the surrounding bombs count of a cell at a given index by one
        void increaseSurroundingBombsCount(const quint64 cellIndex);

        // Decrease the surrounding bombs count of a cell at a given index by one
        void decreaseSurroundingBombsCount(const quint64 cellIndex);

        // Increase the flag count by one
        void increaseFlagCount();

        // Decrease the flag count by one
        void decreaseFlagCount();

        /*
         * Update all surrounding cells of a given index 
         * with a given update function
         */
        void updateSurroundingCell(const quint64 cellIndex,
                const std::function<void(quint64)> updateFunction);

        // Check if the game is won
        void checkForWin();

        // mFirstReveal is needed if the first reveal is a bomb
        bool mFirstReveal;

        // Holds all indices of the mines in the current game
        QVector<quint64> mMineIndices;

        // State if the game is started
        bool mGameStarted;

        // Timer to get the time played
        QTimer *timer;

        // GameObserver for the GameModel
        observers::GameObserver *mGameObserver;

        // JsonManager properties
        data::JsonManager *mJsonManager;
        const QString mJsonObjectName = "configuration";
};

} // namespace controllers

#endif // GAMECONTROLLER_H
