// Qt
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

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

    // Load the start view
    engine.load(url);

    // Start the Application
    int execCode = app.exec();

    // save current state of the software to JSON

    return execCode;
}
