#include <QtQml>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QTranslator>
#include <QFile>
#include <QDir>
#include <QDebug>

#include "src/driveproperties/serialproperties.h"
#include "src/serialcommunicator/serialcommunicator.h"
#include "src/buttonsmodel/buttonsmodel.h"
#include "src/fileio/fileio.h"


int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QTranslator qtLangTranslator;
    qtLangTranslator.load("QtLanguage_ru_RU", ".");
    qApp->installTranslator(&qtLangTranslator);

    SerialProperties serialProperties;
    SerialCommunicator serialCommunicator;
    FileIO fileIO;
    ButtonsModel btnsListModel;
    QFile file("default.json");
    qDebug() << QDir::currentPath();
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream t( &file );
        btnsListModel.fromJsonString(QByteArray::fromStdString(t.readAll().toStdString()));
        file.close();
    }

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("serialProperties", &serialProperties);
    engine.rootContext()->setContextProperty("serialCommunicator", &serialCommunicator);
    engine.rootContext()->setContextProperty("btnsListModel", &btnsListModel);
    engine.rootContext()->setContextProperty("fileIO", &fileIO);

    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
