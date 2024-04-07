#include <QGuiApplication>
#include <QDBusConnection>
#include <processmanager.h>
#include <QFile>
#include <QTextStream>
#include <QDir>
#include <QtGui/6.2.4/QtGui/private/qtx11extras_p.h>
#include <X11/Xlib.h>
#include <QHotkey>

void MessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg) {
    QString txt;
    switch (type) {
        case QtDebugMsg:
            txt = QString("Debug: %1").arg(msg);
            break;
        case QtWarningMsg:
            txt = QString("Warning: %1").arg(msg);
            break;
        case QtCriticalMsg:
            txt = QString("Critical: %1").arg(msg);
            break;
        case QtFatalMsg:
            txt = QString("Fatal: %1").arg(msg);
            break;
        case QtInfoMsg:
            txt = QString("Info: %1").arg(msg);
            break;
    }

    QFile outFile(QDir::homePath() + "/odysseus-session.log");
    outFile.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream ts(&outFile);
    ts << txt << "\n";
}

int main(int argc, char *argv[]) {
    QGuiApplication a(argc, argv);

    qInstallMessageHandler(MessageHandler); // Install the handler

    a.setQuitOnLastWindowClosed(false);

    ProcessManager processManager{};

    processManager.loadSystemProcesses();

    // Register the service to the D-Bus session bus
    if (!QDBusConnection::sessionBus().registerService("me.aren.OdysseusSession")) {
        qWarning() << "Cannot register service to the D-Bus session bus.";
    }

    // Register the object to the D-Bus session bus
    if (!QDBusConnection::sessionBus().registerObject("/ProcessManager", new ProcessManager(), QDBusConnection::ExportAllSlots)) {
        qWarning() << "Cannot register object to the D-Bus session bus.";
    }

    return a.exec();
}
