#-------------------------------------------------
#
# Project created by QtCreator 2019-09-05T10:01:38
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT +=sql widgets printsupport
QT += sql widgets widgets
TARGET = BeaconDisplayQAManager
TEMPLATE = app
QT       += core gui
UI_DIR = ./tmp/ui
MOC_DIR = ./tmp/moc
OBJECTS_DIR = ./tmp/obj
RCC_DIR = ./tmp/rcc


#requires(qtConfig(tableview)
# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11


include("src/src.pri")

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    dialogmulitescreen.cpp \
    dilogreporthistory.cpp \
    userdefine.cpp \
    qsqlqueryrelatinaltablemodel.cpp \
    databasecontrol.cpp \
    spotlightwidget.cpp \
    qspotlightsetting.cpp \
    aboutdialog.cpp \
    lineeditshortcutkey.cpp \
    languagechoice.cpp



HEADERS += \
        mainwindow.h \
   dialogmulitescreen.h \
    dilogreporthistory.h \
    userdefine.h \
    qsqlqueryrelatinaltablemodel.h \
    databasecontrol.h \
    spotlightwidget.h \
    qspotlightsetting.h \
    aboutdialog.h \
    lineeditshortcutkey.h \
    languagechoice.h  \





# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

FORMS += \
    dilogreporthistory.ui \
    dialogmulitescreen.ui \
    qspotlightsetting.ui \
    aboutdialog.ui \
    languagechoice.ui

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lib/ -li1d3SDK
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/lib/ -li1d3SDK



win32 {
LIBS+= -L$$PWD/ -lDDCHelper
LIBS+= -L$$PWD/lib/ -lGdi32

}
RESOURCES += \
    picture.qrc


TRANSLATIONS = translation_ch.ts translation_en.ts

DISTFILES +=




INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lib/ -ldog_windows_3159508
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/lib/ -ldog_windows_3159508

#win32:CONFIG(release, debug|release): LIBS += $$PWD/lib/chkstk.obj
#else:win32:CONFIG(debug, debug|release): LIBS += $$PWD/lib/chkstk.obj






win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lib/ -ldog_windows_demo
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/lib/ -ldog_windows_demo

