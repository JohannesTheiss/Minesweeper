#include "../inc/Grid.h"


Grid::Grid(QObject *parent) : QAbstractTableModel(parent)
{
    table.append({"x","x","x","x","x","x","x"});
    table.append({"x","x","x","x","x","x","x"});
    table.append({"x","x","x","x","x","x","x"});
    table.append({"x","x","x","x","x","x","x"});
    table.append({"x","x","x","x","x","x","x"});
    table.append({"x","x","x","x","x","x","x"});
    table.append({"x","x","x","x","x","x","x"});
    table.append({"x","x","x","x","x","x","x"});
    table.append({"x","x","x","x","x","x","x"});
    table.append({"x","x","x","x","x","x","x"});
    table.append({"x","x","x","x","x","x","x"});
    table.append({"x","x","x","x","x","x","x"});
    table.append({"x","x","x","x","x","x","x"});
    table.append({"x","x","x","x","x","x","x"});
}


QVector<QVector<QString>> Grid::grid()
{
    return table;
}

int Grid::rowCount(const QModelIndex &) const
{
    return table.size();//Number of rows
}

int Grid::columnCount(const QModelIndex &) const
{
    return table.at(0).size();//Columns
}

QVariant Grid::data(const QModelIndex &index, int role) const
{
    switch (role) {
    case TableDataRole:
    {
        return  table.at(index.row()).at(index.column());
    }
    case HeadingRole:
    {
        if( index.row()==0){
            return true;
        }else{
            return false;
        }
    }
    default:
        break;
    }

    return QVariant();
}

QHash<int, QByteArray> Grid::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[TableDataRole] = "tabledata";
    roles[HeadingRole] = "heading";
    return roles;
}


void Grid::lol(int index)
{
    table[index][0] = "0";
    qDebug() << "hallo";


    emit gridChanged();
}

