TARGET = navigation
QT = quick qml

equals(DEFINES, "AGL"){
    QT += aglextras
}

QT += positioning
QT += dbus
QT += core
CONFIG += c++11 link_pkgconfig

HEADERS += \
    markermodel.h \
    dbus_server.h \
    guidance_module.h \
    file_operation.h

SOURCES += main.cpp \
    dbus_server.cpp

RESOURCES += \
    navigation.qrc \
    images/images.qrc

DBUS_ADAPTORS += dbusinterface/com.poiservice.test.xml
DBUS_INTERFACES += dbusinterface/com.poiservice.test.xml

include(app.pri)

