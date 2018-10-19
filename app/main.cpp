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

int main(int argc, char *argv[])
{
#if defined(AGL)
    AGLApplication app(argc, argv);
    app.setApplicationName("testqt");
    app.setupApplicationRole("testqt");

    app.load(QUrl(QStringLiteral("qrc:/testqt.qml")));
    return app.exec();
#else
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    app.setApplicationName("testqt");

    engine.load(QUrl(QStringLiteral("qrc:/testqt.qml")));
    return app.exec();
#endif
}

