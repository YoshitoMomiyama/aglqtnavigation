/*
 * Copyright (C) 2016 The Qt Company Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *	  http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#if defined(AGL)
#include <QtAGLExtras/AGLApplication>
#else
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#endif
#include <QtCore/QDebug>
#include <QtCore/QCommandLineParser>
#include <QtCore/QUrlQuery>
#include <QtCore/QSettings>
#include <QtGui/QGuiApplication>
#include <QtQml/QQmlApplicationEngine>
#include <QtQml/QQmlContext>
#include <QtQuickControls2/QQuickStyle>
#include <QQuickWindow>
#include <QTimerEvent>
#include <QtDBus/QDBusConnection>
#include "markermodel.h"
#include "dbus_server.h"
#include "guidance_module.h"
#include "file_operation.h"

int main(int argc, char *argv[])
{

    // for dbusIF
    QString pathBase = "com.poiservice.";
    QString objBase = "/com/poiservice/";
    QString	serverName = "test";

    if (!QDBusConnection::sessionBus().isConnected()) {
        qWarning("Cannot connect to the D-Bus session bus.\n"
                 "Please check your system settings and try again.\n");
        return 1;
    }

#if defined(AGL)
    AGLApplication app(argc, argv);
    app.setApplicationName("navigation");
    app.setupApplicationRole("navigation");
#else
    QGuiApplication app(argc, argv);
    app.setApplicationName("navigation");
#endif

    QQmlApplicationEngine engine;

    MarkerModel model;
    engine.rootContext()->setContextProperty("markerModel", &model);

    Guidance_Module guidance;
    engine.rootContext()->setContextProperty("guidanceModule", &guidance);

    File_Operation file;
    engine.rootContext()->setContextProperty("fileOperation", &file);

    engine.load(QUrl(QStringLiteral("qrc:/navigation.qml")));
    QObject *map = engine.rootObjects().first()->findChild<QObject*>("map");
    DBus_Server dbus(pathBase,objBase,serverName,map);

    return app.exec();
}

