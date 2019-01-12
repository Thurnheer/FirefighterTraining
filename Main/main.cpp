#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "sqleventmodel.h"
#include "JahreskalenderParser.hpp"
#include "IcalGenerator.hpp"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    qmlRegisterType<SqlEventModel>("ch.ihrefeuerwehr.eventModel", 1, 0, "SqlEventModel");
    qmlRegisterType<JahreskalenderParser>("ch.ihrefeuerwehr.xlsParser", 1, 0, "JahreskalenderParser");
    qmlRegisterType<IcalGenerator>("ch.ihrefeuerwehr.icalGenerator", 1, 0, "IcalGenerator");
    engine.load(QUrl(QStringLiteral("qrc:FirefighterTrainingPlaner/qml/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
