#ifndef PROCESSMANAGER_H
#define PROCESSMANAGER_H

#include <QObject>
#include <QList>
#include <QMap>
#include <QProcess>
#include <QDebug>
#include <QGuiApplication>

class ProcessManager : public QObject
{
    Q_OBJECT
public:
    ProcessManager();
    void loadSystemProcesses();
    void logout();
private:
    QMap<QString, QProcess*> systemProcesses;
};

#endif // PROCESSMANAGER_H
