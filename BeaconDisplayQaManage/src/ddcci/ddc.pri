INCLUDEPATH += $$PWD
# for the curvePlo floder
SOURCES += $$PWD/cdislayorder.cpp

HEADERS  +=$$PWD/WaterDrop.h  \
          $$PWD/DdcProtocDefine.h




unix {
LIBS +=-L lib/libxml2.so \
                   -L/usr/local/lib -lxml2 \
                -L libddccontrol.a
INCLUDEPATH +=/usr/include/libxml2/
INCLUDEPATH +=./
SOURCES +=$$PWD/cddccilinux.cpp
HEADERS +=$$PWD/cddccilinux.h
}

win32 {
INCLUDEPATH +=./
#HEADERS +=DDCHelper.h
SOURCES += $$PWD/cddcciwindow.cpp
HEADERS  += $$PWD/cddcciwindow.h


}
