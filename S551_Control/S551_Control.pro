#-------------------------------------------------
#
# Project created by QtCreator 2018-02-27T11:47:33
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = S551_Control
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    mypushbutton.cpp \
    dialog.cpp

HEADERS  += mainwindow.h \
    mypushbutton.h \
    dialog.h

FORMS    += mainwindow.ui \
    dialog.ui
target.path = /home/root
INSTALLS += target
QT       += serialport

RESOURCES += \
    s551.qrc

DISTFILES +=
