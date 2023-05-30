#-------------------------------------------------
#
# Project created by QtCreator 2020-02-28T22:59:28
#
#-------------------------------------------------

QT       += core gui
QT += network
QT += concurrent
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CommandTest
TEMPLATE = app

CONFIG += c++11

SOURCES += main.cpp\
        widget.cpp \
    testgrabiamgetime.cpp

HEADERS  += widget.h \
    testgrabiamgetime.h \
    sntl_adminapi.h

FORMS    += widget.ui \
    testgrabiamgetime.ui

