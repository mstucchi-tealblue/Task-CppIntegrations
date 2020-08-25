#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "contactlist.h"
#include "contactmodel.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    qmlRegisterType<ContactModel>("ContactM",1,0,"ContactModel");
    qmlRegisterUncreatableType<ContactList>("ContactM",1,0,"ContactList",QStringLiteral("ContactList should not be created in QML"));

    ContactList contactList;
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty(QStringLiteral("contactList"),&contactList);


    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
