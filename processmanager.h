#ifndef PROCESSMANAGER_H
#define PROCESSMANAGER_H

#include <QObject>
#include <QList>
#include <QMap>
#include <QProcess>
#include <QDebug>
#include <QGuiApplication>
#include <QDBusInterface>

class ProcessManager : public QObject
{
    Q_OBJECT
    Q_CLASSINFO("Odysseus Session", "me.aren.OdysseusSession")
public:
    ProcessManager();
    void loadSystemProcesses();
    void showLauncherDBus();
public slots:
    void logout();
private:
    QMap<QString, QProcess*> systemProcesses;
};

#endif // PROCESSMANAGER_H
