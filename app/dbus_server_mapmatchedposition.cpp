#include "dbus_server_mapmatchedposition.h"
#include <QDebug>
#include <QDBusVariant>
#include <QDBusConnectionInterface>
#include <QGeoCoordinate>

dbus_server_mapmatchedposition::dbus_server_mapmatchedposition(QObject *parent) :
    m_pathName("org.agl.naviapi"),
    m_objName("/org/genivi/navicore"),
    m_serverName("mapmatchedposition"),
    m_object(parent)
{
	setupDBus();
    setupApi();
}

dbus_server_mapmatchedposition::~dbus_server_mapmatchedposition(){
    QDBusConnection::sessionBus().unregisterObject(m_objName);
}

void dbus_server_mapmatchedposition::setupDBus()
{
    qDBusRegisterMetaType<qPositionPairElm>();
    qDBusRegisterMetaType<qPosition>();

    qDBusRegisterMetaType<qValuesToReturn>();

    if (!QDBusConnection::sessionBus().registerService(m_pathName))
        qDebug() << m_pathName << "registerService() failed";

    if (!QDBusConnection::sessionBus().registerObject(m_objName, this))
        qDebug() << m_objName << "registerObject() failed";

    new MapMatchedPositionAdaptor(this);

}

void dbus_server_mapmatchedposition::setupApi(){

}

// Method
qPosition dbus_server_mapmatchedposition::GetPosition(const qValuesToReturn &valuesToReturn){
    double Latitude =0;
    double Longitude =0;
    qPosition result;
    qPositionPairElm Pair_1,Pair_2;
    QVariant m_Variant = m_object->property("currentpostion");
    if(m_Variant.canConvert<QGeoCoordinate>()){
            QGeoCoordinate coordinate = m_Variant.value<QGeoCoordinate>();
            Latitude = coordinate.latitude();
            Longitude = coordinate.longitude();
    }

    for(int i = 0; i < valuesToReturn.size(); i++){
        switch(valuesToReturn[i]){
            case 160:
                Pair_1.key = 160;
                Pair_1.value = QDBusVariant(Latitude);
                result.insert(160,Pair_1);
                break;
            case 161:
                Pair_2.key = 161;
                Pair_2.value = QDBusVariant(Longitude);
                result.insert(161,Pair_2);
                break;
            default:
                break;
        }
    }
    return result;
}
