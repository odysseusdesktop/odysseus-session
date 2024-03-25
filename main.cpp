#include <QGuiApplication>
#include <QHotkey>
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

    return a.exec();
}
