#ifndef GRID_H
#define GRID_H

#include <QObject>
#include <QAbstractTableModel>
#include <QDebug>


class Grid : public QAbstractTableModel
{
    Q_OBJECT

    Q_PROPERTY(QVector<QVector<QString>> grid READ grid NOTIFY gridChanged)

    enum TableRoles{
        TableDataRole = Qt::UserRole + 1,
        HeadingRole
    };

    public:
        explicit Grid(QObject *parent = nullptr);
        
        int rowCount(const QModelIndex & = QModelIndex()) const override;

        int columnCount(const QModelIndex & = QModelIndex()) const override;

        QVariant data(const QModelIndex &index, int role) const override;

        QHash<int, QByteArray> roleNames() const override;

        QVector<QVector<QString>> grid();

    signals:
        void gridChanged();

    public slots:
        void lol(int index);


    private:
        QVector<QVector<QString>> table;
};

#endif // GRID_H
