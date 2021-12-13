// Qt
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <QObject>
#include <QVector>

#include <QDebug>

#include "../inc/models/CellModel.h"
#include "../inc/models/GameModel.h"
#include "../inc/models/StatisticEntryModel.h"
#include "../inc/models/StatisticsModel.h"

#include "../inc/controllers/observers/GameObserver.h"

#include "../inc/controllers/GameController.h"
#include "../inc/controllers/StatisticsController.h"


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
    QVector<models::CellModel *> grid;
    models::GameModel gameModel(grid, 0, 0, 0, 0, 0, models::SizeScaling::SMALL);
    
    // create GameModel-observer
    observers::GameObserver gameObserver(&gameModel);

    // create the GridController
    controllers::GameController gameController(&gameObserver);

    // create the StatisticsModel
    quint64 bestTime = 187;
    quint64 numberOfWins = 187;
    quint64 numberOfDefeats = 1;
    quint64 numberOfGamesPlayed = 1;
    quint64 numberOfRows = 5;
    quint64 numberOfColumns = 5;
    quint64 numberOfMines = 10;
    models::StatisticEntryModel sem(bestTime,
            numberOfWins,
            numberOfDefeats,
            numberOfGamesPlayed,
            numberOfRows,
            numberOfColumns,
            numberOfMines);
    QList<models::StatisticEntryModel *> sList({ &sem });
    models::StatisticsModel statisticsModel(sList);

    // create the StatisticsController
    controllers::StatisticsController statisticsController(&statisticsModel);
    QObject::connect(&gameController, SIGNAL(submitStatistics(const quint64,
                const quint64,
                const quint64,
                const quint64,
                const bool)), &statisticsController, SLOT(submitStatistics(const quint64,
                const quint64,
                const quint64,
                const quint64,
                const bool)));

    // connect models with view
    engine.rootContext()->setContextProperty("gameModel", &gameModel);
    engine.rootContext()->setContextProperty("statisticsModel", &statisticsModel);

    // connect enum with view
    qmlRegisterUncreatableMetaObject(
      models::staticMetaObject, 
      "Backend.Game",
      1, 0,
      "SizeScaling",
      "Error: On Size enums" 
    );

    // connect controllers with view
    engine.rootContext()->setContextProperty("gameController", &gameController);
    
    // Load the start view
    engine.load(url);


    // key

    //std::pair<int,int> p = std::make_pair(10,20);
    //QHash<std::pair<int, int>, int> hash;
    //hash[p] = 187;
    //std::cout << hash[std::make_pair(10,20)] << std::endl;
    

    // Start the Application
    int execCode = app.exec();

    // save current state of the software to JSON

    return execCode;
}
