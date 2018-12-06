#ifndef DBUS_TYPES_H
#define DBUS_TYPES_H
#include <QtDBus>

#include <QMetaType>
#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QVariant>
#include <QPair>
#include <QDBusVariant>

// for org.genivi.navigationcore.MapMatchedPosition
struct qPositionPairElm{
    uint8_t key;
    QDBusVariant value;
};
Q_DECLARE_METATYPE(qPositionPairElm)

inline QDBusArgument &operator <<(QDBusArgument &argument, const qPositionPairElm &qpositionpairelm)
{
    argument.beginStructure();
    argument << qpositionpairelm.key << qpositionpairelm.value;
    argument.endStructure();
    return argument;
}

inline const QDBusArgument &operator >>(const QDBusArgument &argument, qPositionPairElm &qpositionpairelm)
{
    argument.beginStructure();
    argument >> qpositionpairelm.key;
    argument >> qpositionpairelm.value;
    argument.endStructure();
    return argument;
}

typedef QMap<int32_t,qPositionPairElm> qPosition;
Q_DECLARE_METATYPE(qPosition)

typedef QList<int32_t> qValuesToReturn;
Q_DECLARE_METATYPE(qValuesToReturn)

#endif
