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
    Q_PROPERTY(quint64 rows READ rows NOTIFY rowsChanged)
    Q_PROPERTY(quint64 columns READ columns NOTIFY columnsChanged)
    Q_PROPERTY(quint64 mineCount READ mineCount NOTIFY mineCountChanged)
    Q_PROPERTY(quint64 flagCount READ flagCount NOTIFY flagCountChanged)

    public:
        //delete default constructor
        GridModel() = delete;

        // custom constructor
        GridModel(const QVector<CellModel *> grid,
                  const quint64 rows,
                  const quint64 columns,
                  const quint64 mineCount,
                  const quint64 flagCount);

        // default destructor
        ~GridModel() = default;

    public slots:
        // property getters
        QVector<QObject *> grid();
        quint64 rows();
        quint64 columns();
        quint64 mineCount();
        quint64 flagCount();

        // property setters
        void setGrid(const QVector<models::CellModel *> grid);
        void setRows(const quint64 rows);
        void setColumns(const quint64 columns);
        void setMineCount(const quint64 mineCount);
        void setFlagCount(const quint64 flagCount);

        void increaseFlags();
        void decreaseFlags();

    signals:
        void gridChanged();
        void rowsChanged();
        void columnsChanged();
        void mineCountChanged();
        void flagCountChanged();

    private:

        // properties
        QVector<CellModel *> mGrid;
        quint64 mRows;
        quint64 mColumns;
        quint64 mMineCount;
        quint64 mFlagCount;

};

} // namespace models
#endif // GRIDMODEL_H
