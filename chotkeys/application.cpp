/*
 * Copyright (C) 2021 CutefishOS Team.
 *
 * Author:     Reion Wong <aj@cutefishos.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/*
 * Modified by: Aren Coşkun (arencoskun)
 * Date: 07.04.2024
 *
 * Changed what shortcuts does. (Odysseus)
 */

#include "application.h"
#include "hotkeys.h"

#include <QProcess>
#include <QDebug>
#include <QDBusInterface>

Application::Application(QObject *parent)
    : QObject(parent)
    , m_hotKeys(new Hotkeys)
{
    setupShortcuts();

    connect(m_hotKeys, &Hotkeys::pressed, this, &Application::onPressed);
    connect(m_hotKeys, &Hotkeys::released, this, &Application::onReleased);
}

void Application::setupShortcuts()
{
    m_hotKeys->registerKey(QKeySequence(Qt::CTRL + Qt::ALT + Qt::Key_Delete));
    m_hotKeys->registerKey(647); // Super
}

void Application::onPressed(QKeySequence keySeq)
{
    if (keySeq.toString() == "Ʇ") {
        QDBusInterface iface("me.aren.OdysseusLauncher", "/LauncherViewManager", "", QDBusConnection::sessionBus());
        if (iface.isValid()) {
            QDBusMessage reply = iface.call("showView");
            if (reply.type() == QDBusMessage::ErrorMessage) {
                qWarning() << "Error:" << reply.errorMessage();
            }
        } else {
            qWarning() << "Interface is not valid";
        }
    }

    if (keySeq.toString() == "Ctrl+Alt+Del") {
        QDBusInterface iface("me.aren.OdysseusSession", "/ProcessManager", "", QDBusConnection::sessionBus());
        if (iface.isValid()) {
            QDBusMessage reply = iface.call("logout");
            if (reply.type() == QDBusMessage::ErrorMessage) {
                qWarning() << "Error:" << reply.errorMessage();
            }
        } else {
            qWarning() << "Interface is not valid";
        }
    }
}

void Application::onPressedID(quint32 id) {
    qDebug() << "onPressedID: " << id;
}

void Application::onReleased(QKeySequence keySeq) {

}
