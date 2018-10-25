TARGET = testqt
QT = quick qml
#QT += aglextras
QT += positioning
CONFIG += c++11 link_pkgconfig
#PKGCONFIG += 

#HEADERS += 

HEADERS += \
    markermodel.h

SOURCES += main.cpp

RESOURCES += \
    testqt.qrc \
    images/images.qrc

include(app.pri)

