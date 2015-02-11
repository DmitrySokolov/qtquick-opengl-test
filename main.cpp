//------------------------------------------------------------------------------
//      Created : 2015-2-11
//       Author : Dmitry Sokolov <mr.dmitry.sokolov@gmail.com>
//  Description :
//------------------------------------------------------------------------------

#include <QApplication>
#include <QQmlApplicationEngine>
#include "customitem.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    qmlRegisterType<CustomItem>("My.Controls", 1, 0, "CustomItem");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
