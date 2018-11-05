#include"dbus_server.h"
#include <QDebug>

DBus_Server::DBus_Server(const QString &pathName,
                         const QString &objName,
                         const QString &serverName,
                         QObject *parent) :
  QObject(parent),
  m_pathNameBase(pathName),
  m_objNameBase(objName),
  m_serverName(serverName)
{
    initDBus();
}
DBus_Server::~DBus_Server(){}

void DBus_Server::initDBus(){

    new POIContentAccessModuleAdaptor(this);

    QDBusConnection	sessionBus = QDBusConnection::sessionBus();

    if(!sessionBus.registerService(m_pathNameBase + m_serverName))
        qDebug() << m_pathNameBase + m_serverName << "registerService() failed";

    if(!sessionBus.registerObject(m_objNameBase + m_serverName, this))
        qDebug() <<  m_objNameBase + m_serverName << "registerObject() failed";
}

// Signal

// Method
void DBus_Server::addPOI(uint category_id, double poi_Lat, double poi_Lon){

    return;
}
void DBus_Server::removePOIs(uint category_id){

    return;
}
