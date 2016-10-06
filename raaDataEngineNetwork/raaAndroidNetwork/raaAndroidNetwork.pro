#-------------------------------------------------
#
# Project created by QtCreator 2016-06-23T18:05:33
#
#-------------------------------------------------

QT       += network

QT       -= gui

TARGET = raaAndroidNetwork
TEMPLATE = lib

DEFINES += RAAANDROIDNETWORK_LIBRARY

SOURCES += raaAndroidNetwork.cpp

HEADERS += raaAndroidNetwork.h\
        raaandroidnetwork_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
