#include "userdefine.h"

#include <QtSql>
#include <QStringList>
#include <QString>

QString g_strReporType[QA_OUTRANGE]={""};
QStringList g_strListResult ;
int g_nSelectRKType=0;
bool g_blInternalVersion=false;
int g_nLanguageType=0;

void testRegexCapture()
{
    QString pattern("￥(\\d+\\.?\\d*)");
    QRegExp rx(pattern);
    QString str("＄10.9,￥20.5");
    int pos = str.indexOf(rx);              // 0, position of the first match.

                               // Returns -1 if str is not found.
    // You can also use rx.indexIn(str);
    qDebug() << pos;
    if ( pos >= 0 )
    {
        qDebug() << rx.matchedLength();     // 5, length of the last matched string
                                        // or -1 if there was no match
        qDebug() << rx.capturedTexts();     // QStringList(“a=100″, ”a”, ”100″),
                                        //   0: text matching pattern
        //   1: text captured by the 1st ()
        //   2: text captured by the 2nd ()
        qDebug() << rx.cap(0);              // a=100, text matching pattern
        qDebug() << rx.cap(1);              // a, text captured by the nth ()
        qDebug() << rx.cap(2);              // 100,
        qDebug() << rx.pos(0);              // 0, position of the nth captured text
        qDebug() << rx.pos(1);              // 0
        qDebug() << rx.pos(2);              // 2

    }


}

QRect GetScreenRect(int screen) {

    DISPLAY_DEVICEW device;
    device.cb = sizeof(device);
    BOOL result = EnumDisplayDevicesW(NULL, screen, &device, 0);

    DEVMODEW device_mode;
    device_mode.dmSize = sizeof(device_mode);
    device_mode.dmDriverExtra = 0;
    result = EnumDisplaySettingsExW(device.DeviceName, ENUM_CURRENT_SETTINGS, &device_mode, 0);

    int x = device_mode.dmPosition.x;
    int y = device_mode.dmPosition.y;
    int width = device_mode.dmPelsWidth;
    int height = device_mode.dmPelsHeight;

    return { x, y,  width, height };
}

void SaveLogInfo(QString str)
{
    if(!g_blInternalVersion)
        return;
    QString fileName =  QDir::currentPath()+"/log.txt";
    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly|QIODevice::Text|QIODevice::Append))
    {

    }
    QString strLogText;
    QTextStream streamFile(&file);
    streamFile<<str;
    file.close();
}

void SaveTestLogInfo(QString str)
{
    QString fileName =  QDir::currentPath()+"/log.txt";
    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly|QIODevice::Text|QIODevice::Append))
    {

    }
    str+="\n";
    QString strLogText;
    QTextStream streamFile(&file);
    streamFile<<str;
    file.close();
}
