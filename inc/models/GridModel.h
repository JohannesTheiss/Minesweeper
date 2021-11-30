#ifndef GRIDMODEL_H
#define GRIDMODEL_H

#include <QObject>
#include <QVector>

#include "CellModel.h"

namespace models
{

class GridModel : public QObject
{

    Q_OBJECT

    Q_PROPERTY(QVector<QObject *> grid READ grid NOTIFY gridChanged)
    Q_PROPERTY(unsigned int rows READ rows NOTIFY rowsChanged)
    Q_PROPERTY(unsigned int columns READ columns NOTIFY columnsChanged)
    Q_PROPERTY(unsigned int mineCount READ mineCount NOTIFY mineCountChanged)

    public:
        //delete default constructor
        GridModel() = delete;

        // custom constructor
        GridModel(const QVector<CellModel *> grid,
                  const unsigned int rows,
                  const unsigned int columns,
                  const unsigned int mineCount);

        // default destructor
        ~GridModel() = default;

        // property getters
        QVector<QObject *> grid();
        unsigned int rows();
        unsigned int columns();
        unsigned int mineCount();

        // property setters
        void setGrid(const QVector<CellModel *> grid);
        void setRows(const unsigned int rows);
        void setColumns(const unsigned int columns);
        void setMineCount(const unsigned int mineCount);

    signals:
        void gridChanged();
        void rowsChanged();
        void columnsChanged();
        void mineCountChanged();

    private:

        // properties
        QVector<CellModel *> mGrid;
        unsigned int mRows;
        unsigned int mColumns;
        unsigned int mMineCount;

};

} // namespace models
#endif // GRIDMODEL_H
