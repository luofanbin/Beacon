#include "systemtray.h"
#include<QDebug>
#include<QMessageBox>
#include <QTranslator>
#include <QApplication>
#include <QDesktopWidget>
#ifdef Q_OS_WIN32
#include "cddcciwindow.h"
#endif
#ifdef Q_OS_LINUX
#include "cddccilinux.h"
#endif

SystemTray::SystemTray(QWidget *parent)
    : QWidget(parent),m_blEnable(false),m_blEnablePIP(false)
{
	m_systemTray = new QSystemTrayIcon(this);

	m_menu = new QMenu(this);
    m_actionConfig = new QAction(m_menu);

    m_actionSplotLight=new QAction(m_menu);;
    m_actionActive=new QAction(m_menu);
    m_actionLasterPen=new QAction(m_menu);
    m_actionFindMouse=new QAction(m_menu);
    m_actionScreenshot=new QAction(m_menu);
    m_actionControlPIP=new QAction(m_menu);
    m_actionClose=new QAction(m_menu);;
    m_actionAbout=new QAction(m_menu);

    m_actionSplotLight->setCheckable(true);;
    m_actionActive->setCheckable(true);;
    m_actionLasterPen->setCheckable(true);;
    m_actionFindMouse->setCheckable(true);;

    ReTranslateUi();
    m_menu->addAction(m_actionConfig);
    m_menu->addSeparator();
    m_menu->addAction(m_actionSplotLight);
        m_menu->addSeparator();
    m_menu->addAction(m_actionActive);
        m_menu->addSeparator();
    m_menu->addAction(m_actionLasterPen);
    m_menu->addAction(m_actionFindMouse);
    m_menu->addSeparator();
    m_menu->addAction(m_actionScreenshot);
    //m_menu->addAction(m_actionControlPIP);
    m_menu->addSeparator();

    m_menu->addAction(m_actionAbout);
    m_menu->addSeparator();
    m_menu->addAction(m_actionClose);

    connect(m_actionConfig, SIGNAL(triggered()), this, SIGNAL(setSetting()));
    connect(m_actionAbout, SIGNAL(triggered()), this, SLOT(showAbout()));

	m_systemTray->setContextMenu(m_menu);
    m_systemTray->setIcon(QIcon(":/system/Resources/ico.png"));
	m_systemTray->setToolTip("SystemTray Program");
	m_systemTray->show();

   //checkSoftwareFunction();
    //setGlobalShortcut();

	connect(m_systemTray, &QSystemTrayIcon::activated, this, &SystemTray::activeTray);//点击托盘，执行相应的动作
	connect(m_systemTray, &QSystemTrayIcon::messageClicked, this, &SystemTray::showWindow);//点击消息框，显示主窗口

 //   connect(m_actionSplotLight, &QAction::triggered,
   //         [=]() {qDebug() << "shortcut activated";
   //     setShutcutHot(DESKTOP_MODE_SPOLIGHT);});
//connect(m_actionSplotLight, &QAction::triggered, this, &SystemTray::showdataMessage);
    connect(m_actionSplotLight, &QAction::triggered,
            [=]() {qDebug() << "shortcut activated";
        setShutcutHot(DESKTOP_MODE_SPOLIGHT,false);});

    connect(m_actionActive, &QAction::triggered,
            [=]() {qDebug() << "shortcut activated";
        setShutcutHot(DESKTOP_MODE_ACTIVE,false);});

    connect(m_actionLasterPen, &QAction::triggered,
            [=]() {qDebug() << "shortcut activated";
        setShutcutHot(DESKTOP_MODE_LASERPEN,false);});

    connect(m_actionFindMouse, &QAction::triggered,
            [=]() {qDebug() << "shortcut activated";
        setShutcutHot(DESKTOP_MODE_WATORDROP,false);});

    connect(m_actionScreenshot, &QAction::triggered,
            [=]() {
        shot=new ScreenShot();
        shot->show();});

    connect(m_actionControlPIP, &QAction::triggered,
            [=]() {
        if(m_blEnablePIP)
           m_blEnablePIP=false;
        else
           m_blEnablePIP=true;

        emit setEnableControlPIP(m_blEnablePIP);
           });
    //connect(m_actionClose, &QAction::triggered, this, &SystemTray::closeApp);
    connect(m_actionClose, &QAction::triggered, [=](){
        shot = new ScreenShot();
        shot->close();
        emit closeApp();
    });

    shortcutSplotLight = new QxtGlobalShortcut(this);
    shortcutReadMode = new QxtGlobalShortcut(this);
    shortcutLasterPen = new QxtGlobalShortcut(this);
    shortcutFindMouse = new QxtGlobalShortcut(this);
    shortcutScreenshot = new QxtGlobalShortcut(this);
    connect(shortcutSplotLight, &QxtGlobalShortcut::activated,
            [=]() {qDebug() << "shortcut activated";
         setShutcutHot(DESKTOP_MODE_SPOLIGHT);});

    connect(shortcutReadMode, &QxtGlobalShortcut::activated,
            [=]() {qDebug() << "shortcut activated";
          setShutcutHot(DESKTOP_MODE_ACTIVE);});

    connect(shortcutLasterPen, &QxtGlobalShortcut::activated,
            [=]() {qDebug() << "shortcut activated";
        setShutcutHot(DESKTOP_MODE_LASERPEN);});

    connect(shortcutFindMouse, &QxtGlobalShortcut::activated,
            [=]() {qDebug() << "shortcut activated";
        setShutcutHot(DESKTOP_MODE_WATORDROP);});

    connect(shortcutScreenshot, &QxtGlobalShortcut::activated,
            [=]() {
        shot=new ScreenShot();
        shot->show();});


}

SystemTray::~SystemTray()
{

}
void SystemTray::setGlobalShortcut(EmDesktopModeType emType ,QString strHotKeyValue)
{
    bool bl_return;
    switch (emType) {
    case DESKTOP_MODE_SPOLIGHT:
        bl_return=shortcutSplotLight->setShortcut(QKeySequence(strHotKeyValue));
        break;
    case DESKTOP_MODE_ACTIVE:
        bl_return=shortcutReadMode->setShortcut(QKeySequence(strHotKeyValue));
        break;
    case DESKTOP_MODE_LASERPEN:
        bl_return=shortcutLasterPen->setShortcut(QKeySequence(strHotKeyValue));
        break;
    case DESKTOP_MODE_WATORDROP:
        bl_return=shortcutFindMouse->setShortcut(QKeySequence(strHotKeyValue));
        break;
    case DESKTOP_MODE_SCREENSHOT:
        bl_return=shortcutScreenshot->setShortcut(QKeySequence(strHotKeyValue));
        break;
    default:
        break;
    }

    if(!bl_return)
    {
        emit setShutcutHotKeyFail(emType);
        QMessageBox::warning(this,tr("Warning"),QString(tr("%1 shortcut key setting failed").arg(strHotKeyValue)));
    }
}

void SystemTray::setLanguage(int nLanguageType)
{
    QTranslator LanguageTranslator;
    switch (nLanguageType) {
    case English:
        LanguageTranslator.load(":/system/Resources/translation_en.qm");
        break;
    case Chinese:
        LanguageTranslator.load(":/system/Resources/translation_ch.qm");
        break;
    default:
        break;
    }
    qApp->installTranslator(&LanguageTranslator);
    ReTranslateUi();
    about_dialog.ReTranslateUi();
}

void SystemTray::setEnableControlPIPAction(bool bIsEnable)
{
    m_actionControlPIP->setDisabled(true);
    if(bIsEnable)
        m_actionControlPIP->setEnabled(true);
}

void SystemTray::changeMouseDesktop(int nScreenIndex)
{
    QDesktopWidget *desktop = QApplication::desktop();
    int n_curr_index=desktop->primaryScreen();

    if(m_blEnablePIP)
    {
        CDdcciWindow ddc_window;
        if(n_curr_index==nScreenIndex)
            ddc_window.setPipOnOff(false);
        else
            ddc_window.setPipOnOff(true);

    }
}

void SystemTray::setShutcutHot(EmDesktopModeType emType,bool blHotKey)
{
    checkSoftwareFunction();
    if(!m_blEnable)
        return;
     QAction *p_action_type=NULL;
     switch (emType) {

     case DESKTOP_MODE_SPOLIGHT:
         p_action_type=m_actionSplotLight;
         break;
     case  DESKTOP_MODE_ACTIVE:
         p_action_type=m_actionActive;
         break;
     case DESKTOP_MODE_LASERPEN:
         p_action_type=m_actionLasterPen;
         break;
     case  DESKTOP_MODE_WATORDROP:
         p_action_type=m_actionFindMouse;
         break;
      case DESKTOP_MODE_NULL:
         default:
             return ;
     }
     if(p_action_type!=NULL)
     {
         if(blHotKey)
           p_action_type->setChecked(!p_action_type->isChecked());

         emit shutcutHotKeyPress(emType,p_action_type->isChecked());
     }

 }
void SystemTray::activeTray(QSystemTrayIcon::ActivationReason reason)
{

	switch (reason)
	{
	case QSystemTrayIcon::Context:
		showMenu();
		break;
	case QSystemTrayIcon::DoubleClick:
        showMessage();//showWindow();
		break;
	case QSystemTrayIcon::Trigger:
		showMessage();
		break;
	}
}

void SystemTray::showMenu()
{
    m_menu->show();
}

void SystemTray::ReTranslateUi()
{
    m_actionConfig->setText(tr("Setting"));
    m_actionSplotLight->setText(tr("Spotlight()"));
    m_actionActive->setText(tr("Read mode"));
    m_actionLasterPen->setText(tr("Laster Pen"));
    m_actionFindMouse->setText(tr("Find Mouse"));
    m_actionScreenshot->setText(tr("Screenshot"));
    m_actionControlPIP->setText(tr("Virtual screen"));
    m_actionClose->setText(tr("Close"));
    m_actionAbout->setText(tr("About"));
}

void SystemTray::showWindow()
{
   this->show();
}

void SystemTray::showMessage()
{
  //  QPoint point_tect=QCursor::pos();
    //m_menu->move(point_tect);
  // m_menu->show();

  m_menu->exec(cursor().pos());
    return ;
	m_systemTray->showMessage("Information",//消息窗口标题
		"There is a new message!",//消息内容
        QSystemTrayIcon::MessageIcon::Information,//消息窗口图标
        2000);//消息窗口显示时长
}
void SystemTray::showdataMessage()
{
    QMessageBox::information(NULL,"time","Test");
}
void  SystemTray::showAbout()
{
    //AboutDialog about_dialog;
    about_dialog.show();
}
bool  SystemTray::checkSoftwareFunction()
{
     m_blEnable=true;
if(checkBeaconSuperdog())
{
    return true;
}

#ifdef QT_NO_DEBUG
    CDdcciWindow ddc_window;
    QVector<QString> vt_device_name;
    QString str_device_current;
    ddc_window.InitUpdate(vt_device_name,str_device_current);
    m_blEnable=true;

#else
    m_blEnable=true;
#endif
    return m_blEnable;
}

void SystemTray::closeSystemTray()
{
    delete m_systemTray;
}
bool SystemTray::checkBeaconSuperdog()
{

    return true;
}
