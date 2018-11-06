#include"dbus_server.h"
#include <QDebug>

DBus_Server::DBus_Server(const QString &pathName,
                         const QString &objName,
                         const QString &serverName,
                         QObject *parent) :
  QObject(parent),
  m_serverName(serverName),
  m_pathName(pathName + serverName),
  m_objName(objName + serverName)
{
    initDBus();
}
DBus_Server::~DBus_Server(){}

void DBus_Server::initDBus(){

    new TestAdaptor(this);

    if (!QDBusConnection::sessionBus().registerService(m_pathName))
        qDebug() << m_pathName << "registerService() failed";

    if (!QDBusConnection::sessionBus().registerObject(m_objName, this))
        qDebug() << m_objName << "registerObject() failed";

//    com::poiservice::test *iface;
//    iface = new com::poiservice::test(m_pathName,m_objName,QDBusConnection::sessionBus(),this);

    if (!QDBusConnection::sessionBus().connect(
                m_pathName,
                m_objName,
                com::poiservice::test::staticInterfaceName(),
                "addPOI",
                this,
                SLOT(addPOI(uint , double , double )))) {	//slot
        qDebug() << m_serverName << "sessionBus.connect():addPOI failed";
    }

    if (!QDBusConnection::sessionBus().connect(
                m_pathName,
                m_objName,
                com::poiservice::test::staticInterfaceName(),
                "removePOIs",
                this,
                SLOT(removePOIs(uint)))) {	//slot
        qDebug() << m_serverName << "sessionBus.connect():removePOIs failed";
    }
}

// Signal

// Method
void DBus_Server::addPOI(uint category_id, double poi_Lat, double poi_Lon){
    qDebug() << "call addPOI category_id: " << category_id << " poi_Lat: " << poi_Lat << " poi_Lon: " << poi_Lon;
    return;
}
void DBus_Server::removePOIs(uint category_id){
    qDebug() << "call removePOIs category_id: " << category_id;
    return;
}
