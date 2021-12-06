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
    
        void flagCell(quint64 index);

    signals:
        QVector <models::CellModel *> updateGrid(QVector<models::CellModel *>);

    private:
        models::GridModel *mGridModel;

};

} // namespace controllers

#endif // GRIDCONTROLLER_H
