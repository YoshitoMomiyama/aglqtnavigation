#include"dbus_server.h"
#include <QDebug>

DBus_Server::DBus_Server(const QString &pathName,
                         const QString &objName,
                         const QString &serverName,
                         QObject *parent) :
  m_serverName(serverName),
  m_pathName(pathName + serverName),
  m_objName(objName + serverName)
{
    initDBus();
    initAPIs(parent);
}
DBus_Server::~DBus_Server(){}

void DBus_Server::initDBus(){

    new TestAdaptor(this);

    if (!QDBusConnection::sessionBus().registerService(m_pathName))
        qDebug() << m_pathName << "registerService() failed";

    if (!QDBusConnection::sessionBus().registerObject(m_objName, this))
        qDebug() << m_objName << "registerObject() failed";

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

void DBus_Server::initAPIs(QObject *parent){

    if(!QObject::connect(this,SIGNAL(doAddPOI(QVariant,QVariant,QVariant)),
                        parent,SLOT(addPoiIconSLOT(QVariant,QVariant,QVariant)))) {
        qDebug() << m_serverName << "cppSIGNAL:doAddPOI to qmlSLOT:addPoiIcon connect is failed";
    }

    if(!QObject::connect(this,SIGNAL(doRemovePOIs(QVariant)),
                         parent,SLOT(removePoiIconsSLOT(QVariant)))) {
        qDebug() << m_serverName << "cppSIGNAL:doRemovePOIs to qmlSLOT:removePoiIcons connect is failed";
    }
}
// Signal

// Method
void DBus_Server::addPOI(uint category_id, double poi_Lat, double poi_Lon){
    qDebug() << "call addPOI category_id: " << category_id << " poi_Lat: " << poi_Lat << " poi_Lon: " << poi_Lon;
    emit doAddPOI(poi_Lat,poi_Lon,category_id);
    return;
}
void DBus_Server::removePOIs(uint category_id){
    qDebug() << "call removePOIs category_id: " << category_id;
    emit doRemovePOIs(category_id);
    return;
}
