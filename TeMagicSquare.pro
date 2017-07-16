#-------------------------------------------------
#
# Project created by QtCreator 2017-07-15T17:42:12
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TeMagicSquare
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    intergeritemdelegate.cpp

HEADERS  += widget.h \
    intergeritemdelegate.h

FORMS    += widget.ui

QMAKE_CXXFLAGS += -std=c++14
