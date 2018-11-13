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

#ifdef AGL
#define USE_QTAGLEXTRAS			0
#define USE_QLIBWINDOWMANAGER	1
#else
#define USE_QTAGLEXTRAS			0
#define USE_QLIBWINDOWMANAGER	0
#endif

#if	USE_QTAGLEXTRAS
#include <QtAGLExtras/AGLApplication>
#elif USE_QLIBWINDOWMANAGER
#include <qlibwindowmanager.h>
#include <qlibhomescreen.h>
#include <string>
#include <ilm/ivi-application-client-protocol.h>
#include <wayland-client.h>
//#else	// for only libwindowmanager
//#include <libwindowmanager.h>
//#include <libhomescreen.hpp>
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
//#include <string>
//#include <ilm/ivi-application-client-protocol.h>
//#include <wayland-client.h>
//#include "wmhandler.h"
#include <QtDBus/QDBusConnection>
#include "markermodel.h"
#include "dbus_server.h"
#include "guidance_module.h"

//#if !USE_QTAGLEXTRAS && !USE_QLIBWINDOWMANAGER
//using namespace std;
//const char *main_role = "navigation";
//long port = 1700;
//LibWindowmanager *wm;
//string token = string("hello");
//int init_wm(LibWindowmanager *wm)
//{
//	if(wm->init(port, token.c_str()) != 0) {
//		return -1;
//	}
//	int id = wm->requestSurface(main_role);
//	fprintf(stderr, "[navigation]get surface(%d)\n", id);
//	if(id < 0) {
//		return -1;
//	}else{
//		char buf[65];   // surface id is under 64bit(1.84E19,) so 65 is sufficient for buffer
//		snprintf(buf, 65, "%d", id);
//		setenv("QT_IVI_SURFACE_ID", buf, 1);
//	}
//	WMHandler wmh;
//	wmh.on_visible = [](const char* role, bool visible){
//		;
//	};
//	wmh.on_sync_draw = [wm](const char* role, const char* area, Rect rect) {
//		fprintf(stderr, "[navigation]endDraw(%s)\n", role);
//		wm->endDraw(role);
//	};
//	wm->setEventHandler(wmh);
//	return 0;
//}
//int init_hs(LibHomeScreen* hs)
//{
//	if(hs->init(port, token.c_str())!=0){
//		return -1;
//	}
//	hs->set_event_handler(LibHomeScreen::Event_TapShortcut, [](json_object *object){
//		const char *application_name = json_object_get_string(
//			json_object_object_get(object, "application_name"));
//		if(strcmp(application_name, "navigation") == 0)
//		{
//			fprintf(stderr, "[navigation]activateWindow @ TapShortcut)\n");
//			wm->activateWindow(main_role);
//		}
//	});
//	return 0;
//}
//#endif

int main(int argc, char *argv[])
{
	
    // for dbusIF
    QString pathBase = "org.agl.";
    QString objBase = "/org/agl/";
    QString	serverName = "naviapi";

    if (!QDBusConnection::sessionBus().isConnected()) {
        qWarning("Cannot connect to the D-Bus session bus.\n"
                 "Please check your system settings and try again.\n");
        return 1;
    }
	
#if	USE_QTAGLEXTRAS
	AGLApplication app(argc, argv);
	app.setApplicationName("navigation");
	app.setupApplicationRole("navigation");
 	app.load(QUrl(QStringLiteral("qrc:/navigation.qml")));
	
#elif USE_QLIBWINDOWMANAGER
	QGuiApplication app(argc, argv);
	QString myname = QString("navigation");
	int port = 1700;
	QString token = "hello";
	QCoreApplication::setOrganizationDomain("LinuxFoundation");
	QCoreApplication::setOrganizationName("AutomotiveGradeLinux");
	QCoreApplication::setApplicationName(myname);
	QCoreApplication::setApplicationVersion("0.1.0");
	QCommandLineParser parser;
	parser.addPositionalArgument("port", app.translate("main", "port for binding"));
	parser.addPositionalArgument("secret", app.translate("main", "secret for binding"));
	parser.addHelpOption();
	parser.addVersionOption();
	parser.process(app);
	QStringList positionalArguments = parser.positionalArguments();
	if (positionalArguments.length() == 2) {
		port = positionalArguments.takeFirst().toInt();
		token = positionalArguments.takeFirst();
    }
	fprintf(stderr, "[navigation]app_name: %s, port: %d, token: %s.\n",
					myname.toStdString().c_str(),
					port,
					token.toStdString().c_str());
	// QLibWM
	QLibWindowmanager* qwmHandler = new QLibWindowmanager();
	int res;
	if((res = qwmHandler->init(port,token)) != 0){
		fprintf(stderr, "[navigation]init qlibwm err(%d)\n", res);
		return -1;
	}
	if((res = qwmHandler->requestSurface(myname)) != 0) {
		fprintf(stderr, "[navigation]request surface err(%d)\n", res);
		return -1;
	}
    qwmHandler->set_event_handler(QLibWindowmanager::Event_SyncDraw, [qwmHandler, myname](json_object *object) {
		qwmHandler->endDraw(myname);
	});
    qwmHandler->set_event_handler(QLibWindowmanager::Event_Visible, [qwmHandler, myname](json_object *object) {
        ;
    });
    qwmHandler->set_event_handler(QLibWindowmanager::Event_Invisible, [qwmHandler, myname](json_object *object) {
        ;
    });
	// QLibHS
	QLibHomeScreen* qhsHandler = new QLibHomeScreen();
	qhsHandler->init(port, token.toStdString().c_str());
	qhsHandler->set_event_handler(QLibHomeScreen::Event_TapShortcut, [qwmHandler, myname](json_object *object){
		json_object *appnameJ = nullptr;
		if(json_object_object_get_ex(object, "application_name", &appnameJ))
		{
			const char *appname = json_object_get_string(appnameJ);
			if(QString::compare(myname, appname, Qt::CaseInsensitive) == 0)
			{
				qDebug("Surface %s got tapShortcut\n", appname);
				json_object *para, *area;
				json_object_object_get_ex(object, "parameter", &para);
				json_object_object_get_ex(para, "area", &area);
				const char *displayArea = json_object_get_string(area);
				qDebug("Surface %s got tapShortcut area\n", displayArea);
				qwmHandler->activateWindow(myname, QString(QLatin1String(displayArea)));
			}
		}
	});
	// Load qml
	QQmlApplicationEngine engine;
	MarkerModel model;
	engine.rootContext()->setContextProperty("markerModel", &model);
	Guidance_Module guidance;
	engine.rootContext()->setContextProperty("guidanceModule", &guidance);
	
	engine.load(QUrl(QStringLiteral("qrc:/navigation.qml")));
 	QObject *root = engine.rootObjects().first();
	QQuickWindow *window = qobject_cast<QQuickWindow *>(root);
	QObject::connect(window, SIGNAL(frameSwapped()), qwmHandler, SLOT(slotActivateSurface()));
	
	QObject *map = engine.rootObjects().first()->findChild<QObject*>("map");
	DBus_Server dbus(pathBase,objBase,serverName,map);
	
#else	// for only libwindowmanager
	QGuiApplication app(argc, argv);
    app.setApplicationName("navigation");
//	if(argc > 2){
//		port = strtol(argv[1], NULL, 10);
//		token = argv[2];
//	}
//	fprintf(stderr, "[navigation]app_name: %s, port: %d, token: %s.\n", main_role, port, token.c_str());
//	// LibWM
//	wm = new LibWindowmanager();
//	if(init_wm(wm)!=0){
//		fprintf(stderr, "[navigation]init_wm failed\n");
//		return -1;
//	}else{
//		fprintf(stderr, "[navigation]init_wm OK\n");
//	}
//	// LibHS
//	LibHomeScreen *hs = new LibHomeScreen();
//	if(init_hs(hs)!=0){
//		fprintf(stderr, "[navigation]init_hs failed\n");
//		return -1;
//	}else{
//		fprintf(stderr, "[navigation]init_hs OK\n");
//	}
//	WmHandler *wmh = new WmHandler();
//	wmh->init(wm, main_role);
	// Load qml
	QQmlApplicationEngine engine;

    MarkerModel model;
    engine.rootContext()->setContextProperty("markerModel", &model);

    Guidance_Module guidance;
    engine.rootContext()->setContextProperty("guidanceModule", &guidance);

    engine.load(QUrl(QStringLiteral("qrc:/navigation.qml")));
    QObject *map = engine.rootObjects().first()->findChild<QObject*>("map");
    DBus_Server dbus(pathBase,objBase,serverName,map);

#endif
	
	return app.exec();
}

