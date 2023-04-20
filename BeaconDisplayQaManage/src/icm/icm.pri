INCLUDEPATH += $$PWD
# for the curvePlo floder
SOURCES += $$PWD/applyicm.cpp \
            $$PWD/applywindowsicm.cpp

HEADERS  +=$$PWD/applyicm.h  \
          $$PWD/applywindowsicm.h


#win32: LIBS +=-lGdi32.lib
