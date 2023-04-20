#ifndef SPOTLIGHTWIDGET_H
#define SPOTLIGHTWIDGET_H
#include<windows.h>
#include <QWidget>
#include<QVector>
 #include <QVariantAnimation>
#include "qspotlightsetting.h"

class  DesktopDisplay
{
    public:
        explicit DesktopDisplay(QRect rect);
    void expondDestop(QRect rect);
    int  judgePosition(QPoint &poitCur);
    QRect getDestop(){return m_rectDestop;};
private:
    QRect m_rectDestop;
    QRect m_rectVirturalDestop;
};

class TransparentDesktopQWidget : public QWidget
{
    Q_OBJECT
public:

    explicit TransparentDesktopQWidget(QWidget *parent = nullptr);

    //void move(const QPoint &point);
    void setColor(QColor color);
    void writeSettings();
    void readSettings();
    void SendShortcutKeySig();

    void mouseMoveEvent(QMouseEvent *e);

    QSpotlightSetting dlgSpotlightSetting;
private:
    void paintEvent(QPaintEvent *event);
    void drawSpolight();
    void drawLaserpen();
   void  drawActive();
    void drawWatorDrop();
public slots:
    void onRaduisChanged(QVariant value);
    void setDesktopMode(EmDesktopModeType emModeType);
    void showWaterDrop();
   void  setSetting();
private:

    QVariantAnimation* m_waterDropAnimation;
    // 水滴变化的半径;
        int m_animationRadius;

   static  int m_radiusLasterpen;
   static  int m_radiusWaterDrop;
   static int  m_radiusSpotLight;
    // 水滴的颜色;
   static QColor m_waterDropColor;
   static  QColor m_colorSpotLight;
   static QColor m_colorLasterPen;

   static QString m_shortcutkeySpotLight;
   static QString m_shortcutkeyReadmode;
   static QString m_shortcutkeyLasterPen;
   static QString m_shortcutkeyFindMouse;
   static QString m_shortcutkeyScreenshot;
   static int  m_ActiveModeValue;

    EmDesktopModeType m_DesktopModeType;

};
class SpotlightWidget : public QWidget
{
Q_OBJECT
public:
explicit SpotlightWidget(QWidget *parent = nullptr);
~SpotlightWidget();
void updetTransparentDesktop();
void judgeMousePosition();
void checkMethodFunction();
void enableWidget();
bool getSpotlightEnable(){return m_bEnableSpotlight;};
void SendShortcutKeySig();
void setControlPIPAction();
void monitorMouseDesktop(QPoint point);

signals:
    void moveCursorPos(QPoint point);
    void setSpotlightMode(EmDesktopModeType emModeType);
    void showWaterDrop();
     void setSetting();
     void sigKeyChange(EmDesktopModeType,QString);
     void languageKeyPress(int);
     void setShutcutHotKeyFail(EmDesktopModeType emType);
     void setEnableControlPIPAction(bool);
     void changeMouseDesktop(int);

public slots:
    void moveCursorPosTo(QPoint point);
    void shutcutHotKeyPress(EmDesktopModeType emType,bool blEnable);
    void setEnableControlPIP(bool bisEnable);

protected:
    HHOOK m_mouseHook;
    QVector<TransparentDesktopQWidget*> m_vtControlSpotlight;
    QVector<DesktopDisplay*> m_vtDestopDisplay;
    bool m_bEnableSpotlight;
    bool m_bEnableReadMode;
    bool m_bEnableLasterPen;
    bool m_bEnableFindCursor;
    bool m_bEnableControlPIP;
    int m_nCurrentDestop;

    QRect m_currDesktopRect;
    int m_currDesktopIndex;

};

#endif // SPOTLIGHTWIDGET_H
