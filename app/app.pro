TARGET = navigation
QT = quick qml

equals(DEFINES, "AGL"){
    QT += aglextras
    PKGCONFIG += qlibhomescreen qlibwindowmanager
}

QT += positioning
QT += dbus
QT += core
CONFIG += c++11 link_pkgconfig

HEADERS += \
    markermodel.h \
    dbus_server.h \
    guidance_module.h \
    file_operation.h \
    dbus_server_mapmatchedposition.h

SOURCES += main.cpp \
    dbus_server.cpp \
    file_operation.cpp \
    dbus_server_mapmatchedposition.cpp

RESOURCES += \
    navigation.qrc \
    images/images.qrc

LIBS += $$OUT_PWD/../dbus_interface/libdbus_interface.a
INCLUDEPATH += $$OUT_PWD/../dbus_interface

include(app.pri)

DISTFILES +=


