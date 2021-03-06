// Qt
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QObject>

// Models
#include "../inc/models/CellModel.h"
#include "../inc/models/GameModel.h"
#include "../inc/models/StatisticEntryModel.h"
#include "../inc/models/StatisticsModel.h"

// Observers
#include "../inc/controllers/observers/GameObserver.h"
#include "../inc/controllers/observers/StatisticsObserver.h"

// Controllers
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

    // create the GridModel
    QVector<models::CellModel *> grid;
    models::GameModel gameModel(grid, 0, 0, 0, 0, 0, models::SizeScaling::SMALL);
    
    // create GameModel-observer
    observers::GameObserver gameObserver(&gameModel);

    // create the GridController
    controllers::GameController gameController(&gameObserver);

    // create the StatisticsModel
    QList<models::StatisticEntryModel *> sList;
    models::StatisticsModel statisticsModel(sList);

    // create the StatisticsObserver
    observers::StatisticsObserver statisticsObserver(&statisticsModel);

    // create the StatisticsController
    controllers::StatisticsController statisticsController(&statisticsObserver);

    // connect gameController.gameEnded with statisticsController.createStatistic
    QObject::connect(&gameController, SIGNAL(gameEnded(const quint64,
                const quint64,
                const quint64,
                const quint64,
                const bool)), &statisticsController, SLOT(createStatistic(const quint64,
                const quint64,
                const quint64,
                const quint64,
                const bool)));

    // connect models with view
    engine.rootContext()->setContextProperty("gameModel", &gameModel);
    engine.rootContext()->setContextProperty("statisticsModel", &statisticsModel);

    // connect the models::SizeScaling enum with view
    qmlRegisterUncreatableMetaObject(
      models::staticMetaObject, 
      "Backend.Game",
      1, 0,
      "SizeScaling",
      "Error: On Size enums" 
    );

    // connect controllers with view
    engine.rootContext()->setContextProperty("gameController", &gameController);
    engine.rootContext()->setContextProperty("statisticsController", &statisticsController);
    
    // Load the start view
    engine.load(url);

    // Start the Application
    int execCode = app.exec();
    
    // if the Application is closed
    // save the running game as lose
    gameController.endGame(false);

    return execCode;
}
