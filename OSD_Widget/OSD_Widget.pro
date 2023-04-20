#-------------------------------------------------
#
# Project created by QtCreator 2019-02-18T15:55:46
#
#-------------------------------------------------

QT       += core gui
QT += concurrent
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OSD_Widget
TEMPLATE = app
 QT += network

SOURCES += main.cpp\
        widget.cpp \
    dbus_interface.cpp \
    mvmethodosd.cpp \
    sigvinscaninfo.cpp \
    video_adjustment.cpp \
    messages.cpp \
    dp_adjustment.cpp \
    overlaymodes.cpp \
    newoverlaymode.cpp \
    scanningdialog.cpp

HEADERS  += widget.h \
    dbus_interface.h \
    mvmethodosd.h \
    sigvinscaninfo.h \
    video_adjustment.h \
    messages.h \
    dp_adjustment.h \
    overlaymodes.h \
    newoverlaymode.h \
    scanningdialog.h

FORMS    += widget.ui \
    sigvinscaninfo.ui \
    video_adjustment.ui \
    messages.ui \
    dp_adjustment.ui \
    overlaymodes.ui \
    newoverlaymode.ui \
    scanningdialog.ui

include(./IFX/srcfile.pri)

RESOURCES += \
    osd.qrc

#QMAKE_CFLAGS += `pkg-config --cflags --libs gtk+-2.0`
#QMAKE_CXXFLAGS += $$QMAKE_CFLAGS
QT += dbus
