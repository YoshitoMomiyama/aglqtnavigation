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
    dbus_server.h

SOURCES += main.cpp \
    dbus_server.cpp

RESOURCES += \
    testqt.qrc \
    images/images.qrc

DBUS_ADAPTORS += dbusinterface/com.poiservice.test.xml
DBUS_INTERFACES += dbusinterface/com.poiservice.test.xml

include(app.pri)

