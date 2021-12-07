// Qt
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <QObject>
#include <QVector>

#include <QDebug>

#include "../inc/models/CellModel.h"
#include "../inc/models/GameModel.h"

#include "../inc/controllers/GameController.h"


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

    // create the GridModel
    quint64 numberOfRows = 16;
    quint64 numberOfColumns = 30;
    quint64 numberOfMines = 99;
    quint64 timePlayed = 0;
    QVector<models::CellModel *> grid;
    models::GameModel gameModel(grid, numberOfRows, numberOfColumns, numberOfMines, numberOfMines, timePlayed);
    
    // create the GridController
    controllers::GameController gameController(&gameModel, &gameModel);

    // connect models with view
    engine.rootContext()->setContextProperty("gameModel", &gameModel);

    // connect controllers with view
    engine.rootContext()->setContextProperty("gameController", &gameController);
    
    // Load the start view
    engine.load(url);

    // Start the Application
    int execCode = app.exec();

    // save current state of the software to JSON

    return execCode;
}
