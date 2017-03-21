#include <QGuiApplication>
#include <QQmlEngine>
#include <QQuickView>
#include "frequencymonitor.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<FrequencyMonitor>("be.mindgoo.tools", 0, 1, "FrequencyMonitor");

    QQuickView view;
    view.setSource(QUrl(QStringLiteral("qrc:/main.qml")));
    view.show();

    return app.exec();
}
