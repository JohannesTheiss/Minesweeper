#ifndef GRIDCONTROLLER_H
#define GRIDCONTROLLER_H

#include <random>
#include <numeric>
#include <iterator>

#include <QObject>

#include <QDebug>

#include "../models/CellModel.h"
#include "../models/GridModel.h"

namespace controllers
{

class GridController : public QObject
{
    Q_OBJECT

    public:
        GridController(models::GridModel *gridModel, 
                QObject *parent = nullptr);

        void increaseSurroundingBombsCount(quint64 cellIndex);
        void increaseFlagCount();
        void decreaseFlagCount();

    public slots:
        void generateGrid();

        void revealCell(quint64 index);
        void revealAllCells();
    
        void toggleFlagInCell(quint64 index);

    private:
        void updateSurroundingCell(const quint64 cellIndex,
                const quint64 numberOfColumns,
                const quint64 numberOfRow,
                const std::function<void(quint64)> updateFunction);

        models::GridModel *mGridModel;
};

} // namespace controllers

#endif // GRIDCONTROLLER_H
