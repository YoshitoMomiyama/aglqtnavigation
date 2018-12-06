#ifndef DBUS_RECEIVER_H
#define DBUS_RECEIVER_H

#include <QtDBus/QDBusConnection>
#include <QtCore/QObject>
#include <QtDBus/QtDBus>

#include "org.genivi.navigationcore.mapmatchedposition_adaptor.h"
#include "org.genivi.navigationcore.mapmatchedposition_interface.h"

class dbus_server_mapmatchedposition : public QObject
{
	Q_OBJECT

    QString	m_pathName;
    QString	m_objName;
	QString m_serverName;
    QObject *m_object;

public:
    dbus_server_mapmatchedposition(QObject *parent = 0);
    ~dbus_server_mapmatchedposition();

public slots:
    qPosition GetPosition(const qValuesToReturn &valuesToReturn);

private:
	void setupDBus();
    void setupApi();

};

#endif // DBUS_RECEIVER_H

