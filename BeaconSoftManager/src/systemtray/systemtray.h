#ifndef SYSTEMTRAY_H
#define SYSTEMTRAY_H

#include <QtWidgets/QWidget>
#include <QSystemTrayIcon>
#include <QMenu>
#include "spotlightwidget.h"
#include "cdislayorder.h"
#include "qxtglobalshortcut.h"
#include "aboutdialog.h"
#include "screenshot.h"
#include "cdislayorder.h"
#include "userdefine.h"
#include "ImageToolBase.h"
#include "ImageToolFactory.h"
#include <QLocalServer>
#include <QLocalSocket>

class SystemTray : public QWidget
{
	Q_OBJECT

public:
	SystemTray(QWidget *parent = 0);
	~SystemTray();
     bool checkSoftwareFunction();
     void closeSystemTray();
     EmLicenseType superdogLicenseType(char *info,int *nRemainingCount);
signals:
    void closeApp();
    void shutcutHotKeyPress(EmDesktopModeType emType,bool blEnable);
    void setSetting();
    void languageKeyPress(int);
    void setShutcutHotKeyFail(EmDesktopModeType emType);
    void setEnableControlPIP(bool,int);
    void displayQAManager();
    void reconfigureDisplayInfo();
public slots:
    void showdataMessage();
    void showAbout();
    void setGlobalShortcut(EmDesktopModeType emType ,QString strHotKeyValue) ;
    void setLanguage(int nLanguageType);
    void activationMagnifying();
    //void activationScreenshot();

    void on_localSocker_newConnection();
    void sendData(int nStatus);
    void setPIPControl();
    void setReadModeControl(bool blHotKey=true);
    void setActionControlPIP(bool blStatus);

protected:

    void setShutcutHot(EmDesktopModeType emType,bool blHotKey=true);

	void activeTray(QSystemTrayIcon::ActivationReason reason);
	void showWindow();//显示窗体
	void showMessage();//消息框
	void showMenu();//显示菜单
    void ReTranslateUi();
    bool setIsCheckedControlPIP(QVector<QString> strDisplay);

private:
	QSystemTrayIcon *m_systemTray;
    AboutDialog about_dialog;

	QMenu *m_menu;
    QMenu *m_tool_menu;
    QAction *m_actionQAManager;
    QAction *m_actionConfig;
    QAction *m_actionSplotLight;
    QAction *m_actionActive;
    QAction *m_actionLasterPen;
    QAction *m_actionFindMouse;
    QAction *m_actionScreenshot;
    QAction *m_actionMagnifying;
    QAction *m_actionControlPIP;
    QAction *m_actionClose;
    QAction *m_actionAbout;
    QAction *m_actionReconfigure;

    bool m_blEnable;
    bool m_blEnablePIP;
    bool m_blScreenShot;
    bool m_blMagnifying;

    QxtGlobalShortcut *shortcutSplotLight;
    QxtGlobalShortcut *shortcutReadMode;
    QxtGlobalShortcut *shortcutLasterPen;
    QxtGlobalShortcut *shortcutFindMouse;
    QxtGlobalShortcut *shortcutScreenshot;
    QxtGlobalShortcut *shortcutMagnifying;
    ScreenShot *shot;

    bool checkBeaconSuperdog();

    QLocalServer *localServer;
    QLocalSocket *localSocket;
};

#endif // SYSTEMTRAY_H
