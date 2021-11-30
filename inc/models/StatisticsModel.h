#ifndef STATISTICSMODEL_H
#define STATISTICSMODEL_H

#include <QObject>
#include <QList>

namespace models
{

class StatisticsModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QList<QObject *> statisticEntryModelList READ statisticEntryModelList NOTIFY statisticEntryModelListChanged)

    public:
        StatisticsModel(QList<QObject *> statisticEntryModelList, QObject *parent = nullptr);

        QList<QObject *> statisticEntryModelList();

    signals:
        void statisticEntryModelListChanged();

    private:
        QList<QObject *> mStatisticEntryModelList;

};

} // namespace models

#endif // STATISTICSMODEL_H
