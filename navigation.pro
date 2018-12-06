CONFIG += ordered
TEMPLATE = subdirs
SUBDIRS = dbus_interface \
          app

equals(DEFINES, "AGL"){
    SUBDIRS += package
}

package.depends += dbus_interface \
                   app
