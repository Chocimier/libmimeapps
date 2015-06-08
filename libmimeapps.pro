#-------------------------------------------------
#
# Project created by QtCreator
#
#-------------------------------------------------

QT       -= core gui

TARGET = mimeapps
TEMPLATE = lib

DEFINES += LIBMIMEAPPS_LIBRARY

SOURCES += DesktopEntry.cpp \
    Tools.cpp \
    Index.cpp

HEADERS += DesktopEntry.h \
    Tools.h \
	Index.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
