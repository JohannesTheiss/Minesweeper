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

    public slots:

        void newGrid();
        void generateGrid(models::GridModel *gridModel);

        void revealCell(quint64 index);
        void revealAllCells();
    
        void toggleFlagInCell(quint64 index);


        // connections to the model
        void updateInternalGrid(QVector<models::CellModel * > grid);
        void updateInternalColumns(quint64 columns);
        void updateInternalRows(quint64 rows);
        void updateInternalMineCount(quint64 mineCount);
        void updateInternalFlagCount(quint64 flagCount);

    signals:
        QVector<models::CellModel *> updateGrid(QVector<models::CellModel *>);


    private:
        void increaseSurroundingBombsCount(const quint64 cellIndex);

        void updateSurroundingCell(const quint64 cellIndex,
                const quint64 numberOfColumns,
                const quint64 numberOfRow,
                const std::function<void(quint64)> updateFunction);

        models::GridModel *mGridModel;

        // internal copys of the model
        QVector<models::CellModel *> mGrid;
        quint64 mColumns;
        quint64 mRows;
        quint64 mMineCount;
        quint64 mFlagCount;

};

} // namespace controllers

#endif // GRIDCONTROLLER_H
