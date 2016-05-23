#-------------------------------------------------
#
# Project created by QtCreator 2016-03-10T14:18:04
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

SOURCES += $$PWD/Gomoku/GomokuWindow.cpp \
    $$PWD/Gomoku/Field.cpp \
    $$PWD/Gomoku/Cell.cpp \
    $$PWD/Gomoku/CellItem.cpp

HEADERS  += $$PWD/Gomoku/GomokuWindow.hpp \
    $$PWD/Gomoku/Field.hpp \
    $$PWD/Gomoku/Cell.hpp \
    $$PWD/Gomoku/CellItem.hpp

FORMS    += $$PWD/Gomoku/GomokuWindow.ui
