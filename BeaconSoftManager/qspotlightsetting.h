#ifndef QSPOTLIGHTSETTING_H
#define QSPOTLIGHTSETTING_H

#include <QDialog>
//#include "spotlightwidget.h"
#include "lineeditshortcutkey.h"
#include<windows.h>
#include <QTranslator>
namespace Ui {
class QSpotlightSetting;
}
typedef enum
{
    DESKTOP_MODE_NULL,
    DESKTOP_MODE_SPOLIGHT,
    DESKTOP_MODE_ACTIVE,
    DESKTOP_MODE_LASERPEN,
    DESKTOP_MODE_WATORDROP,
    DESKTOP_MODE_SCREENSHOT,
    DESKTOP_MODE_MAGNIFYING
}EmDesktopModeType;
class QSpotlightSetting : public QDialog
{
Q_OBJECT

public:
explicit QSpotlightSetting(QWidget *parent = nullptr);
~QSpotlightSetting();
    void ControlLayout();
void setItermColor(EmDesktopModeType type,QColor *pcolor);
void setItermRadius(EmDesktopModeType type,int  *pRadius);
void setItermShortcutKey(EmDesktopModeType type,QString  *pstrShortcutKey);
void setActiveValuePoint(int *pValue);
void setSigName(QVector<QString> rvtStringDeviceSN);
void setLanguageType(int nIndex);
int getReadModeSignal();

//QCheckboxCombo *SignalComboBox;
private slots:
void setSpotlightColor();
void setWatordropColor();
void setLasterpenColor();
void setSpotlightValue(int nValue);
void setLasterpenValue(int nValue);
void setWatordropValue(int nValue);
void setActiveValue(int nValue);
void setSpotlightShortcutKey(QString strValue);
void setReadodeShortcutKey(QString strValue);
void setLasterpenShortcutKey(QString strValue);
void setFindmouseShortcutKey(QString strValue);
void setScreenshotShortcutKey(QString strValue);
void setMagnifyingShortcutKey(QString strValue);
void RestoreDefaultSettings();
void close();


public slots:
    void setLanguage();
    void setShutcutHotKeyFail(EmDesktopModeType emType);
signals:
    void sigKeyChange(EmDesktopModeType,QString);
    void languageKeyPress(int);
private:
    void showColorButton();
    void ReTranslateUi(int nIndex);
Ui::QSpotlightSetting *ui;
QColor *mp_colorSpotlight;
QColor *mp_colorLasterpen;
QColor *mp_colorFindMouse;
int *mp_SpotlightRadius;
int *mp_LasterpenRadius;
int *mp_watordropRadius;
int *mp_ActiveModeValue;
QString *mp_SpotlightShortcutKey;
QString *mp_ReadModeShortcutKey;
QString *mp_LasterpenShortcutKey;
QString *mp_FindMouseShortcutKey;
QString *mp_ScreenshotShortcutKey;
QString *mp_MagnifyingShortcutKey;



LineEditShortcutKey *m_SpotlightShortcutKey,*m_ReadmodeShortcutKey,
                    *m_LasterpenShortcutKey,*m_FindMouseShortcutKey,
                    *m_ScreenshotShortcutKey,*m_MagnifyingShortcutKey;


};

#endif // QSPOTLIGHTSETTING_H
