#ifndef GRIDCONTROLLER_H
#define GRIDCONTROLLER_H

#include <random>
#include <numeric>

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
        void generateGrid(models::GridModel &gridModel);

        void revealCell(quint64 index);
    
    private:
        models::GridModel *mGridModel;

};

} // namespace controllers

#endif // GRIDCONTROLLER_H
