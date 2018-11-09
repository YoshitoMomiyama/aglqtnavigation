TEMPLATE = subdirs
SUBDIRS = app

equals(DEFINES, "AGL"){
    SUBDIRS += package
}

package.depends += app
