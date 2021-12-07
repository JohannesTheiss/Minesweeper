#ifndef GRAMEMODEL_H
#define GRAMEMODEL_H

#include <QObject>
#include <QVector>

#include "CellModel.h"

namespace models
{

class GameModel : public QObject
{

    Q_OBJECT

    Q_PROPERTY(QVector<CellModel *> grid READ grid NOTIFY gridChanged)
    Q_PROPERTY(quint64 rows READ rows NOTIFY rowsChanged)
    Q_PROPERTY(quint64 columns READ columns NOTIFY columnsChanged)
    Q_PROPERTY(quint64 mineCount READ mineCount NOTIFY mineCountChanged)
    Q_PROPERTY(quint64 flagCount READ flagCount NOTIFY flagCountChanged)
    Q_PROPERTY(quint64 timePlayed READ timePlayed NOTIFY timePlayedChanged)

    public:
        //delete default constructor
        GameModel() = delete;

        // custom constructor
        GameModel(const QVector<CellModel *> grid,
                  const quint64 rows,
                  const quint64 columns,
                  const quint64 mineCount,
                  const quint64 flagCount,
                  const quint64 timePlayed);

        // default destructor
        ~GameModel() = default;

    public slots:
        // property getters
        QVector<CellModel *> grid();
        quint64 rows();
        quint64 columns();
        quint64 mineCount();
        quint64 flagCount();
        quint64 timePlayed();


        // property setters
        void setGrid(const QVector<models::CellModel *> grid);
        void setRows(const quint64 rows);
        void setColumns(const quint64 columns);
        void setMineCount(const quint64 mineCount);
        void setFlagCount(const quint64 flagCount);
        void setTimePlayed(const quint64 timePlayed);

    signals:
        void gridChanged();
        void rowsChanged();
        void columnsChanged();
        void mineCountChanged();
        void flagCountChanged();
        void timePlayedChanged();

    private:

        // properties
        QVector<CellModel *> mGrid;
        quint64 mRows;
        quint64 mColumns;
        quint64 mMineCount;
        quint64 mFlagCount;
        quint64 mTimePlayed;

};

} // namespace models
#endif // GRAMEMODEL_H
