#include "systemtray.h"
#include<QDebug>
#include<QMessageBox>
#include <QTranslator>
#include <QApplication>
#include <QDesktopWidget>
#include "cddcciwindow.h"
#include <QtXml/QDomDocument>
#include <QtXml/QDomElement>
#include <regex>
#include "userdefine.h"



SystemTray::SystemTray(QWidget *parent)
    : QWidget(parent),m_blEnable(false),m_blEnablePIP(false),m_blScreenShot(true)
{
    shot=nullptr;
    m_blMagnifying=false;
    m_systemTray = new QSystemTrayIcon(this);
	m_menu = new QMenu(this);
    m_actionQAManager = new QAction(m_menu);
    m_tool_menu = new QMenu(m_menu);
    m_actionConfig = new QAction(m_tool_menu);
    m_actionSplotLight=new QAction(m_tool_menu);;
    m_actionActive=new QAction(m_tool_menu);
    m_actionLasterPen=new QAction(m_tool_menu);
    m_actionFindMouse=new QAction(m_tool_menu);
    m_actionScreenshot=new QAction(m_tool_menu);
    m_actionMagnifying=new QAction(m_tool_menu);

    m_actionClose=new QAction(m_menu);;
    m_actionAbout=new QAction(m_menu);
    m_actionReconfigure=new QAction(m_menu);

     m_actionControlPIP=new QAction(m_menu);

    m_actionSplotLight->setCheckable(true);;
    m_actionActive->setCheckable(true);;
    m_actionLasterPen->setCheckable(true);;
    m_actionFindMouse->setCheckable(true);;
    m_actionControlPIP->setCheckable(true);

    ReTranslateUi();
    //m_menu->addAction(m_actionQAManager);
    //m_menu->addSeparator();
    m_menu->addMenu(m_tool_menu);
    m_menu->addSeparator();
    m_tool_menu->addAction(m_actionConfig);
    m_tool_menu->addSeparator();
    m_tool_menu->addAction(m_actionSplotLight);
    m_tool_menu->addSeparator();
    m_tool_menu->addAction(m_actionActive);
    m_tool_menu->addSeparator();
    m_tool_menu->addAction(m_actionLasterPen);
    m_tool_menu->addAction(m_actionFindMouse);
    m_tool_menu->addSeparator();
    m_tool_menu->addAction(m_actionScreenshot);
    m_tool_menu->addAction(m_actionMagnifying);
    m_menu->addAction(m_actionControlPIP);
    m_menu->addSeparator();

    m_menu->addAction(m_actionReconfigure);
    m_menu->addSeparator();

    m_menu->addAction(m_actionAbout);
    m_menu->addSeparator();
    m_menu->addAction(m_actionClose);

    connect(m_actionConfig, SIGNAL(triggered()), this, SIGNAL(setSetting()));
    connect(m_actionReconfigure, &QAction::triggered, this,  [&](){
        emit reconfigureDisplayInfo();
        setPIPControl();
    });
    connect(m_actionQAManager, &QAction::triggered, this, [&](){
        sendData(1);
    });
    connect(m_actionAbout, SIGNAL(triggered()), this, SLOT(showAbout()));

	m_systemTray->setContextMenu(m_menu);
    m_systemTray->setIcon(QIcon(":/system/Resources/ico.png"));
    m_systemTray->setToolTip("SystemTray Program");
	m_systemTray->show();

   //checkSoftwareFunction();
    //setGlobalShortcut();

	connect(m_systemTray, &QSystemTrayIcon::activated, this, &SystemTray::activeTray);//�������̣�ִ����Ӧ�Ķ���
	connect(m_systemTray, &QSystemTrayIcon::messageClicked, this, &SystemTray::showWindow);//������Ϣ������ʾ������

 //   connect(m_actionSplotLight, &QAction::triggered,
   //         [=]() {qDebug() << "shortcut activated";
   //     setShutcutHot(DESKTOP_MODE_SPOLIGHT);});
//connect(m_actionSplotLight, &QAction::triggered, this, &SystemTray::showdataMessage);
    connect(m_actionSplotLight, &QAction::triggered,
            [=]() {qDebug() << "shortcut activated";
        setShutcutHot(DESKTOP_MODE_SPOLIGHT,false);});

    connect(m_actionActive, &QAction::triggered,
            [=]() {qDebug() << "shortcut activated";
        setReadModeControl(false);});

    connect(m_actionLasterPen, &QAction::triggered,
            [=]() {qDebug() << "shortcut activated";
        setShutcutHot(DESKTOP_MODE_LASERPEN,false);});

    connect(m_actionFindMouse, &QAction::triggered,
            [=]() {qDebug() << "shortcut activated";
        setShutcutHot(DESKTOP_MODE_WATORDROP,false);});

    connect(m_actionScreenshot, &QAction::triggered,
            [=]() {
        if(m_blScreenShot)
        {
            m_blScreenShot=false;
            if(shot!=nullptr)
            {
               shot->deleteLater();
               shot=nullptr;
            }
            shot=new ScreenShot();
            connect(shot,&ScreenShot::activationScreenshot,[=](){m_blScreenShot=true;});
            shot->show();
        }});

    connect(m_actionMagnifying, &QAction::triggered,this,&SystemTray::activationMagnifying);
    connect(m_actionControlPIP, &QAction::triggered,this,&SystemTray::setPIPControl);


    //connect(m_actionClose, &QAction::triggered, this, &SystemTray::closeApp);
    connect(m_actionClose, &QAction::triggered, [=](){
        //sendData(0);
        QThread::msleep(500);
        shot = new ScreenShot();
        shot->close();
        emit closeApp();
    });

    shortcutSplotLight = new QxtGlobalShortcut(this);
    shortcutReadMode = new QxtGlobalShortcut(this);
    shortcutLasterPen = new QxtGlobalShortcut(this);
    shortcutFindMouse = new QxtGlobalShortcut(this);
    shortcutScreenshot = new QxtGlobalShortcut(this);
    shortcutMagnifying = new QxtGlobalShortcut(this);
    connect(shortcutSplotLight, &QxtGlobalShortcut::activated,
            [=]() {qDebug() << "shortcut activated";
         setShutcutHot(DESKTOP_MODE_SPOLIGHT);});

    connect(shortcutReadMode, &QxtGlobalShortcut::activated,
            [=]() {qDebug() << "shortcut activated";
          setReadModeControl();});

    connect(shortcutLasterPen, &QxtGlobalShortcut::activated,
            [=]() {qDebug() << "shortcut activated";
        setShutcutHot(DESKTOP_MODE_LASERPEN);});

    connect(shortcutFindMouse, &QxtGlobalShortcut::activated,
            [=]() {qDebug() << "shortcut activated";
        setShutcutHot(DESKTOP_MODE_WATORDROP);});

    connect(shortcutScreenshot, &QxtGlobalShortcut::activated,
            [=]() {
        if(m_blScreenShot)
        {
            m_blScreenShot=false;
            shot=new ScreenShot();
            connect(shot,&ScreenShot::activationScreenshot,[=](){m_blScreenShot=true;});
            shot->show();
        }});

    connect(shortcutMagnifying, &QxtGlobalShortcut::activated,this,&SystemTray::activationMagnifying);

    localServer = new QLocalServer(this);
    if(!localServer->listen("MY_LOCAL_SERVER"))
    {
        QMessageBox::warning(this,tr("Warning"),tr("Failed to start service!"));
    }
    connect(localServer, SIGNAL(newConnection()), this, SLOT(on_localSocker_newConnection()));
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
    case DESKTOP_MODE_MAGNIFYING:
        bl_return=shortcutMagnifying->setShortcut(QKeySequence(strHotKeyValue));
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
    case ENGLISH:
        LanguageTranslator.load(":/system/Resources/translation_en.qm");
        break;
    case CHINESE:
        LanguageTranslator.load(":/system/Resources/translation_ch.qm");
        break;
    default:
        break;
    }
    qApp->installTranslator(&LanguageTranslator);
    ReTranslateUi();
    about_dialog.ReTranslateUi();
}


void SystemTray::activationMagnifying()
{
    if(m_blMagnifying)
        return;

    m_blMagnifying=true;
    QTimer *delay = new QTimer(this);
    connect(delay, &QTimer::timeout, this, [=](){
        ImageToolFactory factory;
        ImageToolBase* base = factory.NewTool(ImageToolFactory::TOOLS::MAGNIFYINGGLASS);
        connect(base, &ImageToolBase::clicked, this, [=](ImageToolBase::STATE state){
            if(state == ImageToolBase::STATE::CLOSE){
                m_blMagnifying=false;
                base->deleteLater();
            }
        });
        base->show();
        delay->deleteLater();
    });

    delay->start(100);
}

void SystemTray::on_localSocker_newConnection()
{
    localSocket = new QLocalSocket(this);
    localSocket = localServer->nextPendingConnection();
}

void SystemTray::sendData(int nStatus)
{
    if(localSocket==nullptr)
        return;
    char cData=nStatus;
    localSocket->write(&cData,1);
}

void SystemTray::setPIPControl()
{
    if(!m_actionControlPIP->isChecked())
    {
        emit setEnableControlPIP(m_actionControlPIP->isChecked(),0);
        return;
    }

    CDdcciWindow ddc_window;
    QVector<QString> rvtStringDeviceSN;
    ddc_window.InitUpdate(rvtStringDeviceSN);
    int nIndex;
    bool blResult=ddc_window.getDisplayPIPMode(&nIndex);
    if(!blResult)
    {
       QApplication::setQuitOnLastWindowClosed(false);
       QMessageBox::warning(this,tr("Warning"),"Please switch the monitor to PIP mode");
       m_actionControlPIP->setChecked(false);
       return;
    }

    emit setEnableControlPIP(m_actionControlPIP->isChecked(),nIndex);
}

void SystemTray::setReadModeControl(bool blHotKey)
{
    if(blHotKey)
    {
        if(m_actionActive->isChecked())
            m_actionActive->setChecked(false);
        else
            m_actionActive->setChecked(true);
    }

    CDdcciWindow ddc_window;
    QVector<QString> rvtStringDeviceSN;
    ddc_window.InitUpdate(rvtStringDeviceSN);
    bool blResult=ddc_window.getDisplayReadMode();
    if(blResult)
    {
       if(!m_actionActive->isChecked())
           ddc_window.setReadMode(0);     
    }else {
       //m_actionActive->setChecked(false);
    }
    emit shutcutHotKeyPress(DESKTOP_MODE_ACTIVE,m_actionActive->isChecked());
    return;
}

void SystemTray::setActionControlPIP(bool blStatus)
{
    m_actionControlPIP->setChecked(blStatus);
}


void SystemTray::setShutcutHot(EmDesktopModeType emType,bool blHotKey)
{
//    checkSoftwareFunction();
//    if(!m_blEnable)
//        return;
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
    m_actionQAManager->setText(tr("QA Manager"));
    m_actionSplotLight->setText(tr("Spotlight"));
    m_actionActive->setText(tr("Read mode"));
    m_actionLasterPen->setText(tr("Laster Pen"));
    m_actionFindMouse->setText(tr("Find Mouse"));
    m_actionScreenshot->setText(tr("Screenshot"));
    m_actionMagnifying->setText(tr("Magnifier"));
    m_actionControlPIP->setText(tr("Virtual screen"));
    m_actionClose->setText(tr("Close"));
    m_actionAbout->setText(tr("About"));
    m_actionReconfigure->setText(tr("Reconfigure"));
    m_tool_menu->setTitle(tr("Operating tools"));   
}

bool SystemTray::setIsCheckedControlPIP(QVector<QString> strDisplay)
{
    bool bl_result=false;


    if(bl_result)
        m_actionControlPIP->setEnabled(true);
    else
        m_actionControlPIP->setEnabled(false);

    return bl_result;
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
	m_systemTray->showMessage("Information",//��Ϣ���ڱ���
		"There is a new message!",//��Ϣ����
        QSystemTrayIcon::MessageIcon::Information,//��Ϣ����ͼ��
        2000);//��Ϣ������ʾʱ��
}
void SystemTray::showdataMessage()
{
    QMessageBox::information(NULL,"time","Test");
}
void  SystemTray::showAbout()
{
    //AboutDialog about_dialog;
    SaveTestLogInfo("display about");
    about_dialog.show();
}
bool  SystemTray::checkSoftwareFunction()
{
     m_blEnable=true;

#ifdef QT_NO_DEBUG
    CDdcciWindow ddc_window;
    QVector<QString> vt_device_name;
    QString str_device_current;
    ddc_window.InitUpdate(vt_device_name,str_device_current);
    m_blEnable=false;
    foreach(str_device_current,vt_device_name)
    {
        if(str_device_current.indexOf("BEA")>=0 ||str_device_current.indexOf("BTD")>=0)
        {
            m_blEnable=true;
            break;
        }
    }

//    int n_dispaly_count=0;
//    bool bl_result=false;
//    foreach(str_device_current,vt_device_name)
//    {
//        bl_result=setIsCheckedControlPIP(n_dispaly_count);
//        if(bl_result)
//            break;
//        n_dispaly_count++;
//    }

//    QtConcurrent::run(this,&SystemTray::setIsCheckedControlPIP,vt_device_name);



#else
    m_blEnable=true;
#endif
    return m_blEnable;
}

void SystemTray::closeSystemTray()
{
    delete m_systemTray;
}

EmLicenseType SystemTray::superdogLicenseType(char *info,int *nRemainingCount)
{
    EmLicenseType emLicenseType=LICENSE_OUTRANGE;
    int n_execution_count,n_total_count;
    std::string str=info;
    std::string::const_iterator iterStart = str.begin();
    std::string::const_iterator iterEnd = str.end();
    std::regex reg("<license>[a-z]+</license>");
    std::smatch result;
    bool bl_result=std::regex_search(iterStart,iterEnd,result,reg);
    if(bl_result)
    {
        if(strcmp(result.str(0).data(),"<license>executions</license>")==0)
        {
            reg.assign("<counter_fix>\\d+</counter_fix>");
            std::regex_search(iterStart,iterEnd,result,reg);

            std::string str2=result.str(0);
            reg.assign("\\d+");
            std::regex_search(str2,result,reg);
            n_total_count=atoi(result.str(0).data());

            reg.assign("<counter_var>\\d+</counter_var>");
            std::regex_search(iterStart,iterEnd,result,reg);

            str2=result.str(0);
            reg.assign("\\d+");
            std::regex_search(str2,result,reg);
            n_execution_count=atoi(result.str(0).data());

            *nRemainingCount=n_total_count-n_execution_count;
            emLicenseType=LICENSE_EXECUTIONS;
        }

        if(strcmp(result.str(0).data(),"<license>perpetual</license>")==0)
            emLicenseType=LICENSE_PERPETUAL;
    }

    return emLicenseType;
}

