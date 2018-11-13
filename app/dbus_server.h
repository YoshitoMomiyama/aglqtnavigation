#ifndef DBUS_SERVER_H
#define DBUS_SERVER_H
#include "naviapi_interface.h"
#include "naviapi_adaptor.h"
#include <QtQml/QQmlApplicationEngine>

class DBus_Server : public QObject{

    Q_OBJECT

    QString m_serverName;
    QString m_pathName;
    QString m_objName;

public:
    DBus_Server(const QString &pathName,
                const QString &objName,
                const QString &serverName,
                QObject *parent = nullptr);
    ~DBus_Server();

private:
    void initDBus();
    void initAPIs(QObject*);

signals:
    void doAddPOI(QVariant,QVariant,QVariant);
    void doRemovePOIs(QVariant);

private slots:
    void addPOI(uint category_id, double poi_Lat, double poi_Lon);
    void removePOIs(uint category_id);
};
#endif // DBUS_SERVER_H
