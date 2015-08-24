#-------------------------------------------------
#
# Project created by QtCreator 2015-07-29T20:58:05
#
#-------------------------------------------------

QT       += core
QT       += network
QT       -= gui

TARGET = cutehttpd
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    server.cpp \
    client.cpp \
    requestresponsehelper.cpp \
    controller.cpp

HEADERS += \
    server.h \
    client.h \
    requestresponsehelper.h \
    controller.h

RESOURCES += \
    res.qrc
