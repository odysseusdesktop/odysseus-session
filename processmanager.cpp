#include "processmanager.h"

ProcessManager::ProcessManager()
{

}

void ProcessManager::logout()
{
    /*
    QMap<QString, QProcess *>::iterator itor = systemProcesses.begin();
    while (itor != systemProcesses.end()) {
        QProcess *process = itor.value();
        process->terminate();
        if (process->state() != QProcess::NotRunning && !process->waitForFinished(2000)) {
            process->kill();
        }
        ++itor;
    }
    */

    for(QProcess* process : systemProcesses) {
        process->terminate();

        if(process->state() != QProcess::NotRunning && !process->waitForFinished(2000))
            process->kill();
    }

    QGuiApplication::exit(0);
}

void ProcessManager::loadSystemProcesses()
{
    QList<QPair<QString, QStringList>> list;
    list << qMakePair(QString("openbox"), QStringList());

    for (QPair<QString, QStringList> pair : list) {
        QProcess *process = new QProcess;
        process->setProgram(pair.first);
        process->setArguments(pair.second);
        process->start();

        qDebug() << "loadSystemProcesses(): " << pair.first << pair.second;

        systemProcesses.insert(pair.first, process);
    }
}
