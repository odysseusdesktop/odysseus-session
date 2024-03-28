#include <QGuiApplication>
#include <QHotkey>
#include <QDBusConnection>
#include <processmanager.h>

int main(int argc, char *argv[])
{
    QGuiApplication a(argc, argv);

    a.setQuitOnLastWindowClosed(false);

    ProcessManager processManager {};

    processManager.loadSystemProcesses();

    QHotkey hotkey(QKeySequence("Ctrl+Alt+Q"), true, &a); //The hotkey will be automatically registered
        qDebug() << "Is registered:" << hotkey.isRegistered();

        QObject::connect(&hotkey, &QHotkey::activated, qApp, [&](){
            qDebug() << "Hotkey Activated - the application will quit now";
            processManager.logout();
    });

    if (!QDBusConnection::sessionBus().registerService("me.aren.OdysseusSession")) {
        qWarning() << "Cannot register service to the D-Bus session bus.";
    }

    if (!QDBusConnection::sessionBus().registerObject("/ProcessManager", new ProcessManager(), QDBusConnection::ExportAllSlots)) {
        qWarning() << "Cannot register object to the D-Bus session bus.";
    }

    return a.exec();
}
