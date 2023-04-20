INCLUDEPATH += $$PWD
# for the tg18 floder
SOURCES += \
            $$PWD/BaseWidget.cpp \
            $$PWD/testimage.cpp \
            $$PWD/AutoHideWidget.cpp \
            $$PWD/visualtest.cpp \
            $$PWD/qmultscreen.cpp \
             $$PWD/checkdelegate.cpp \
            $$PWD/qtg18result.cpp

HEADERS  += \
            $$PWD/BaseWidget.h \
            $$PWD/testimage.h \
            $$PWD/AutoHideWidget.h \
            $$PWD/visualtest.h \
            $$PWD/qmultscreen.h \
             $$PWD/checkdelegate.h \
            $$PWD/qtg18result.h
FORMS += \
    $$PWD/visualtest.ui \

RESOURCES += \
    $$PWD/image.qrc
CONFIG += resources_big
