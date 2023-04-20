#ifndef SPOTLIGHTWIDGET_H
#define SPOTLIGHTWIDGET_H
#include<windows.h>
#include <QWidget>
#include<QVector>
 #include <QVariantAnimation>
#include "qspotlightsetting.h"
#include "cddcciwindow.h"

// 显示器模式信息
typedef struct MonitorModeInfo_t
{
    unsigned int m_nWidth;
    unsigned int m_nHeight;

    MonitorModeInfo_t(int nWidth, int nHeight) : m_nWidth(nWidth), m_nHeight(nHeight) {}
}MonitorModeInfo;

// 显示器信息
struct MonitorInfo
{
    TCHAR szDevice[10];					// 显示器名称
    std::vector<MonitorModeInfo> m_vecModeInfo;			// 当前名称的显示器支持的分辨率模式
};

typedef std::vector<MonitorInfo> VEC_MONITORMODE_INFO;  // 所有的显示器信息

enum EM_DISPLAY_DISTRIBUTION_INFO
{
    EM_NULL,
    EM_HORIZONTAL,
    EM_VERTICAL,
    EM_HORIZONTAL_VERTICAL,

    EM_LEFT,
    EM_RIGHT,
    EM_TOP,
    EM_BOTTOM,
    EM_LEFT_RIGHT,
    EM_TOP_BOTTOM
};

class  DesktopDisplay
{
    public:
        explicit DesktopDisplay(QRect rect);
    void expondDestop(QRect rect);
    int  judgePosition(QPoint &poitCur);
    int  judgeLeftRightPosition(QPoint &poitCur);
    QRect getDestop(){return m_rectDestop;};

    QRect m_rectVirturalDestop;
    QRect m_rectVirturalDestopLeftRight;
    EM_DISPLAY_DISTRIBUTION_INFO emDistributionStatus;
    EM_DISPLAY_DISTRIBUTION_INFO emHorizontal;
    EM_DISPLAY_DISTRIBUTION_INFO emVertical;
private:
    QRect m_rectDestop;

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
    QRect saveRect;
private:
    void paintEvent(QPaintEvent *event);
    void drawSpolight();
    void drawLaserpen();
   void  drawActive();
    void drawWatorDrop();
public slots:
    void onRaduisChanged(QVariant value);
    void setDesktopMode(EmDesktopModeType emModeType);
    void setDesktopReadMode();
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
   static QString m_shortcutkeyMagnifying;
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
    void setEnableControlPIP(bool bisEnable,int nIndex);
    void checkWindowsHook();
    void reconfigureDisplayInfo();

protected:

    HHOOK m_mouseHook;
    QVector<TransparentDesktopQWidget*> m_vtControlSpotlight;
    QVector<DesktopDisplay*> m_vtDestopDisplay;
    bool m_bEnableSpotlight;
    bool m_bEnableReadMode;
    bool m_bEnableLasterPen;
    bool m_bEnableFindCursor;
    bool m_bEnableControlPIP;
    bool m_EnablePIP;
    int m_nCurrentDestop;

    QRect m_currDesktopRect;
    int m_currDesktopIndex;
    CDdcciWindow *ddc_window;
    QRect rect_Desktop,rect_VirturalDestop,rect_left,rect_right;
    QPoint m_lastPoint;
    QTimer *m_Timer;
};

#endif // SPOTLIGHTWIDGET_H
