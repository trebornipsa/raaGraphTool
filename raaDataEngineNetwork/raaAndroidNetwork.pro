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

SOURCES += raaAndroidNetwork.cpp \
    raaNetworkClient.cpp \
    raaNetworkServer.cpp \
    raaTcpClient.cpp \
    raaTcpMsg.cpp \
    raaTcpServer.cpp \
    raaTcpThread.cpp \
    raaUdpThread.cpp \
    raaNetwork.cpp

HEADERS += raaAndroidNetwork.h\
    raaNetworkClient.h \
    raaNetworkDefs.h \
    raaNetworkServer.h \
    raaTcpClient.h \
    raaTcpMsg.h \
    raaTcpServer.h \
    raaTcpThread.h \
    raaUdpThread.h \
    raaNetwork.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

DISTFILES +=
