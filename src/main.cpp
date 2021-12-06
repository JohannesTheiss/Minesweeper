// Qt
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <QObject>
#include <QVector>

#include <QDebug>

#include "../inc/models/CellModel.h"
#include "../inc/models/GridModel.h"

#include "../inc/controllers/GridController.h"

void connectControllerToModel(controllers::GridController &controller, models::GridModel &model)
{
    QObject::connect(&controller, SIGNAL(updateGrid(QVector<models::CellModel *>)), &model, SLOT(setGrid(QVector<models::CellModel *>)));

    // connect model with controller
    QObject::connect(&model, SIGNAL(gridChanged(QVector<models::CellModel *>)), &controller, SLOT(updateInternalGrid(QVector<models::CellModel *>)));
    QObject::connect(&model, SIGNAL(columnsChanged(quint64)), &controller, SLOT(updateInternalColumns(quint64)));
    QObject::connect(&model, SIGNAL(rowsChanged(quint64)), &controller, SLOT(updateInternalRows(quint64)));
    QObject::connect(&model, SIGNAL(mineCountChanged(quint64)), &controller, SLOT(updateInternalMineCount(quint64)));
    QObject::connect(&model, SIGNAL(flagCountChanged(quint64)), &controller, SLOT(updateInternalFlagCount(quint64)));
}

int main(int argc, char *argv[])
{
    // Define start view
    const QUrl url(QStringLiteral("qrc:/windows/MainFrame.qml"));

    // Load engine and connect it with the start view
    QGuiApplication app(argc, argv);
    app.setOrganizationName("Minesweeper");
    app.setOrganizationDomain("Minesweeper");
    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreated,
        &app,
        [url](QObject *obj, const QUrl &objUrl) 
        {
            if (!obj && url == objUrl)
            {
                QCoreApplication::exit(-1);
            }
        },
        Qt::QueuedConnection);

    // Connect frontend with backend
    // Let the frontend only know about the 
    //engine.rootContext()->setContextProperty("backend", &backend);

    // connect grid model with view
    quint64 numberOfRows = 16;
    quint64 numberOfColumns = 30;
    quint64 numberOfMines = 99;

    QVector<models::CellModel *> grid;
    models::GridModel gridModel(grid, numberOfRows, numberOfColumns, numberOfMines, numberOfMines);
    //models::GridModel gridModel(grid, 0, 0, 0, 0);
    
    controllers::GridController gridController;
    connectControllerToModel(gridController, gridModel);
    gridController.generateGrid(&gridModel);


    // connect models with view
    engine.rootContext()->setContextProperty("gridModel", &gridModel);

    // connect controller with view
    engine.rootContext()->setContextProperty("gridController", &gridController);
    
    // Load the start view
    engine.load(url);

    // Start the Application
    int execCode = app.exec();

    // save current state of the software to JSON

    return execCode;
}
