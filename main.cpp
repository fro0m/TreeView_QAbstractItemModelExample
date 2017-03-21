#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <treemodel.h>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<TreeModel>("ggh.model", 1, 0, "TestModel");
    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
