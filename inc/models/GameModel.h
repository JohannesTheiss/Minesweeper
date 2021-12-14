#ifndef GRAMEMODEL_H
#define GRAMEMODEL_H

#include <QObject>
#include <QVector>

#include "CellModel.h"

namespace models
{

Q_NAMESPACE
enum class SizeScaling
{
    SMALL,
    MEDIUM,
    LARGE
};
Q_ENUM_NS(SizeScaling) 

class GameModel : public QObject
{

    Q_OBJECT

    Q_PROPERTY(QVector<CellModel *> grid READ grid NOTIFY gridChanged)
    Q_PROPERTY(quint64 rows READ rows NOTIFY rowsChanged)
    Q_PROPERTY(quint64 columns READ columns NOTIFY columnsChanged)
    Q_PROPERTY(quint64 mineCount READ mineCount NOTIFY mineCountChanged)
    Q_PROPERTY(qint64 flagCount READ flagCount NOTIFY flagCountChanged)
    Q_PROPERTY(quint64 timePlayed READ timePlayed NOTIFY timePlayedChanged)
    Q_PROPERTY(models::SizeScaling scaling READ scaling NOTIFY scalingChanged)

    public:
        //delete default constructor
        GameModel() = delete;

        // custom constructor
        GameModel(const QVector<CellModel *> grid,
                  const quint64 rows,
                  const quint64 columns,
                  const quint64 mineCount,
                  const qint64 flagCount,
                  const quint64 timePlayed,
                  const SizeScaling scaling);

        // default destructor
        ~GameModel() = default;

        // property getters
        QVector<models::CellModel *> grid() const;
        quint64 rows() const;
        quint64 columns() const;
        quint64 mineCount() const;
        qint64 flagCount() const;
        quint64 timePlayed() const;
        models::SizeScaling scaling() const;

public slots:

        // property setters
        void setGrid(const QVector<models::CellModel *> grid);
        void setRows(const quint64 rows);
        void setColumns(const quint64 columns);
        void setMineCount(const quint64 mineCount);
        void setFlagCount(const qint64 flagCount);
        void setTimePlayed(const quint64 timePlayed);
        void setScaling(const models::SizeScaling scaling);

    signals:
        void gridChanged(const QVector<models::CellModel *> grid);
        void rowsChanged(const quint64 rows);
        void columnsChanged(const quint64 columns);
        void mineCountChanged(const quint64 mineCount);
        void flagCountChanged(const quint64 flagCount);
        void timePlayedChanged(const quint64 timePlayed);
        void scalingChanged(const models::SizeScaling scaling);

    private:

        // properties
        QVector<CellModel *> mGrid;
        quint64 mRows;
        quint64 mColumns;
        quint64 mMineCount;
        qint64 mFlagCount;
        quint64 mTimePlayed;
        SizeScaling mScaling;

};

} // namespace models
#endif // GRAMEMODEL_H
