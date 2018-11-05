TARGET = testqt
QT = quick qml
#QT += aglextras
QT += positioning
QT += dbus
CONFIG += c++11 link_pkgconfig
#PKGCONFIG += 

#HEADERS += 

HEADERS += \
    markermodel.h \
    dbus_server.h \
    dbusinterface/com.poiservice.POIContentAccessModule.h \
    dbusinterface/POIContentAccessModule_adapter.h

SOURCES += main.cpp \
    dbus_server.cpp \
    dbusinterface/POIContentAccessModule_adapter.cpp \
    dbusinterface/com.poiservice.POIContentAccessModule.cpp

RESOURCES += \
    testqt.qrc \
    images/images.qrc

include(app.pri)

DISTFILES += \
    dbusinterface/poi_contentaccessmodule.xml
