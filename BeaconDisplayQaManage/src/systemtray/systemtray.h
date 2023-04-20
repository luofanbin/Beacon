#ifndef SYSTEMTRAY_H
#define SYSTEMTRAY_H

#include <QtWidgets/QWidget>
#include <QSystemTrayIcon>
#include <QMenu>
#include "languagechoice.h"
#include "spotlightwidget.h"
#include "cdislayorder.h"
#include "qxtglobalshortcut.h"
#include "aboutdialog.h"
#include "screenshot.h"
class SystemTray : public QWidget
{
	Q_OBJECT

public:
	SystemTray(QWidget *parent = 0);
	~SystemTray();
     bool checkSoftwareFunction();
     void closeSystemTray();
signals:
    void closeApp();
    void shutcutHotKeyPress(EmDesktopModeType emType,bool blEnable);
    void setSetting();
    void languageKeyPress(int);
    void setShutcutHotKeyFail(EmDesktopModeType emType);
    void setEnableControlPIP(bool);
 public slots:
     void showdataMessage();
    void  showAbout();
    void  setGlobalShortcut(EmDesktopModeType emType ,QString strHotKeyValue) ;
    void setLanguage(int nLanguageType);
    void setEnableControlPIPAction(bool bIsEnable);
    void changeMouseDesktop(int nScreenIndex);

protected:

    void setShutcutHot(EmDesktopModeType emType,bool blHotKey=true);

	void activeTray(QSystemTrayIcon::ActivationReason reason);
	void showWindow();//显示窗体
	void showMessage();//消息框
	void showMenu();//显示菜单
    void ReTranslateUi();

private:
	QSystemTrayIcon *m_systemTray;
    AboutDialog about_dialog;

	QMenu *m_menu;
    QAction *m_actionConfig;
    QAction *m_actionSplotLight;
    QAction *m_actionActive;
    QAction *m_actionLasterPen;
    QAction *m_actionFindMouse;
    QAction *m_actionScreenshot;
    QAction *m_actionControlPIP;
    QAction *m_actionClose;
    QAction *m_actionAbout;

    bool m_blEnable;
    bool m_blEnablePIP;

    QxtGlobalShortcut *shortcutSplotLight;
    QxtGlobalShortcut *shortcutReadMode;
    QxtGlobalShortcut *shortcutLasterPen;
    QxtGlobalShortcut *shortcutFindMouse;
    QxtGlobalShortcut *shortcutScreenshot;
    ScreenShot *shot;
    bool checkBeaconSuperdog();
};

#endif // SYSTEMTRAY_H
