#-------------------------------------------------
#
# Project created by QtCreator 2016-04-04T12:44:06
#
#-------------------------------------------------

QT       += core gui network

CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = IsitMessenger
TEMPLATE = app

include(plugins/plugins.pri)

SOURCES += main.cpp\
        MainWindow.cpp \
    ServerDiscovery.cpp \
    Server.cpp \
    LocalClient.cpp \
    RemoteClient.cpp \
    Plugin.cpp

HEADERS  += MainWindow.hpp \
    ServerDiscovery.hpp \
    Server.hpp \
    LocalClient.hpp \
    RemoteClient.hpp \
    Plugin.hpp

FORMS    += MainWindow.ui
