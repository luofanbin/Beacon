#include "spotlightwidget.h"
#include <QPainter>
#include<windows.h>
#include <QApplication>
#include <QPainter>
#include <QDesktopWidget>
#include<QVector>
#include "qxtglobalshortcut.h"
#include <QDebug>
#include <winuser.h>
#include<QMessageBox>
#include<QSettings>
#include<QMutex>

QPoint g_CurrentPosition=QPoint(0,0);
QPoint g_RecordPosition=QPoint(0,0);
QMutex mutex;
int nMouseMoveCount=0;
// 水滴的半径;
#define WATER_DROP_RADIUS 15


SpotlightWidget * gp_SpotlightWidget=NULL;
enum
{
    DESKTOP_NO_CHANGE,
    DESKTOP_CHANGE,
    DESKTOP_NULL
};
LRESULT CALLBACK mouseProc(int nCode,WPARAM wParam,LPARAM lParam)
{
    if(nCode == HC_ACTION) //当nCode等于HC_ACTION时，要求得到处理
    {
        /*
        if(wParam==WM_MOUSEWHEEL//屏蔽滑轮
            ||wParam==WM_RBUTTONDOWN//屏蔽鼠标右键按下
            ||wParam==WM_LBUTTONDOWN//屏蔽鼠标左键按下
            ||wParam==WM_RBUTTONUP//屏蔽鼠标右键弹起的消息
            ||wParam==WM_LBUTTONUP//屏蔽鼠标左键弹起的消息
            ||wParam==WM_MOUSEMOVE)//屏蔽鼠标的移动
        {
            return true;//如果是这些事件产生的话，就返回真，即屏蔽掉这些事件，也就是安装有同类型的其他钩子，捕获不到同样的事件
        }
*/
        if(wParam==WM_MOUSEMOVE)//屏蔽滑轮
        {
            MSLLHOOKSTRUCT *pkbhs = (MSLLHOOKSTRUCT *)lParam;
            QPoint point_cure(pkbhs->pt.x,pkbhs->pt.y);
           mutex.lock();
           g_CurrentPosition=point_cure;
           mutex.unlock();
         //  QPoint point_tect=QCursor::pos();

        //    ::SetWindowPos( 500, 500 );

#if 1
           //qDebug()<<g_CurrentPosition.x()<<g_CurrentPosition.y();
           gp_SpotlightWidget->monitorMouseDesktop(g_CurrentPosition);
           gp_SpotlightWidget->checkMethodFunction();
       #endif

        }
        if(wParam==WM_RBUTTONDOWN//屏蔽鼠标右键按下
            ||wParam==WM_LBUTTONDOWN)//屏蔽鼠标左键按下)
        {
         emit gp_SpotlightWidget->showWaterDrop();
        }
    }
    return CallNextHookEx(NULL,nCode,wParam,lParam);//否则，如果返回给下一个钩子子程处理;
}


//    explicit DesktopDisplay(QRect rect){m_rectDestop=rect;m_rectVirturalDestop=rect};
 DesktopDisplay::DesktopDisplay(QRect rect)
{
     m_rectDestop=rect;
//     m_rectDestop.adjust(1,1,-1,-1);
     m_rectVirturalDestop=rect;
 };
void DesktopDisplay::expondDestop(QRect rect)
{
    rect.adjust(-1,-1,1,1);
    if(m_rectDestop.intersects(rect) )
    {
        if(rect.top()<m_rectVirturalDestop.top())
            m_rectVirturalDestop.setTop(rect.top());

        if(rect.bottom()<m_rectVirturalDestop.bottom())
            m_rectVirturalDestop.setBottom(rect.bottom());
    }
};
int  DesktopDisplay::judgePosition(QPoint &poitCur)
{


    if(m_rectDestop.contains(poitCur,true))
        return DESKTOP_NO_CHANGE;
    if(m_rectVirturalDestop.contains(poitCur))
    {
        if(poitCur.y()<m_rectDestop.top())
            poitCur.setY(m_rectDestop.top());
        else if(poitCur.y()>m_rectDestop.bottom())
             poitCur.setY(m_rectDestop.bottom());
        return DESKTOP_CHANGE;
    }
    return  DESKTOP_NULL;
}

int TransparentDesktopQWidget::m_radiusLasterpen=15;
 int TransparentDesktopQWidget::m_radiusWaterDrop=15;
 int TransparentDesktopQWidget::m_radiusSpotLight=120;
  int TransparentDesktopQWidget::m_ActiveModeValue=90;
 QColor TransparentDesktopQWidget::m_waterDropColor=QColor(255, 120, 0, 150);    // 默认为橘黄色;
QColor TransparentDesktopQWidget::m_colorSpotLight=QColor(0, 0, 0, 80);
 QColor TransparentDesktopQWidget::m_colorLasterPen=QColor(255, 0, 0, 80);

 QString TransparentDesktopQWidget::m_shortcutkeySpotLight=QString("Ctrl+Shift+S");
 QString TransparentDesktopQWidget::m_shortcutkeyReadmode=QString("Ctrl+Shift+A");
 QString TransparentDesktopQWidget::m_shortcutkeyLasterPen=QString("Ctrl+Shift+L");
 QString TransparentDesktopQWidget::m_shortcutkeyFindMouse=QString("Ctrl+Shift+F");
 QString TransparentDesktopQWidget::m_shortcutkeyScreenshot=QString("Ctrl+Shift+D");

 TransparentDesktopQWidget::TransparentDesktopQWidget(QWidget *parent) : QWidget(parent),m_DesktopModeType(DESKTOP_MODE_NULL), m_waterDropAnimation(NULL)

 {
        //   setWindowFlags(Qt::Tool);                                       //this->setWindowFlags(Qt::WindowStaysOnTopHint);
   // this->showFullScreen();
    this->setMouseTracking(true);
    this->setAttribute(Qt::WA_TranslucentBackground);//设置背景透明
   this->setWindowFlags(Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint|Qt::Tool);//设置窗体无边框
 m_waterDropAnimation = new QVariantAnimation(this);
 connect(m_waterDropAnimation, &QVariantAnimation::valueChanged, this, &TransparentDesktopQWidget::onRaduisChanged);
    //   pic.load(":/images/map.png");//加载图像


}
void TransparentDesktopQWidget::writeSettings()
{
//    QSettings settings("BEACON","BeaconDisplayQaManage");
QSettings settings;
    settings.beginGroup("SpotlightRadius");
    settings.setValue("Lasterpen",m_radiusLasterpen);
    settings.setValue("SpotLight", m_radiusSpotLight);
    settings.setValue("WaterDrop", m_radiusWaterDrop);
    settings.endGroup();
    settings.beginGroup("SpotlightColor");
    settings.setValue("Lasterpen",m_colorLasterPen);
    settings.setValue("SpotLight", m_colorSpotLight);
    settings.setValue("WaterDrop", m_waterDropColor);
    settings.endGroup();
    settings.beginGroup("SpotlightShortcutKey");
    settings.setValue("Lasterpen",m_shortcutkeyLasterPen);
    settings.setValue("SpotLight", m_shortcutkeySpotLight);
    settings.setValue("WaterDrop", m_shortcutkeyFindMouse);
    settings.setValue("ReadMode", m_shortcutkeyReadmode);
    settings.setValue("Screenshot", m_shortcutkeyScreenshot);
    settings.endGroup();
}

void TransparentDesktopQWidget::readSettings()
{
   // QSettings settings("BEACON","BeaconDisplayQaManage");
QSettings settings;
    settings.beginGroup("SpotlightRadius");
    m_radiusLasterpen=settings.value("Lasterpen",15).toInt();
     m_radiusSpotLight=settings.value("SpotLight",100).toInt();
      m_radiusWaterDrop=settings.value("WaterDrop",15).toInt();
    settings.endGroup();
    settings.beginGroup("SpotlightColor");
    m_colorLasterPen=settings.value("Lasterpen",QColor(255, 0, 0, 80)).value<QColor>();
    m_colorSpotLight=settings.value("SpotLight",QColor(0, 0, 0, 80)).value<QColor>();
    m_waterDropColor=settings.value("WaterDrop",QColor(255, 120, 0, 150)).value<QColor>();
    settings.endGroup();
    settings.beginGroup("SpotlightShortcutKey");
    m_shortcutkeyLasterPen=settings.value("Lasterpen",QString("Ctrl+Shift+L")).toString();
    m_shortcutkeySpotLight=settings.value("SpotLight",QString("Ctrl+Shift+S")).toString();
    m_shortcutkeyFindMouse=settings.value("WaterDrop",QString("Ctrl+Shift+F")).toString();
    m_shortcutkeyReadmode=settings.value("ReadMode",QString("Ctrl+Shift+A")).toString();
    m_shortcutkeyScreenshot=settings.value("Screenshot",QString("Ctrl+Shift+D")).toString();
    settings.endGroup();
}

void TransparentDesktopQWidget::SendShortcutKeySig()
{
    emit dlgSpotlightSetting.sigKeyChange(DESKTOP_MODE_SPOLIGHT,m_shortcutkeySpotLight);
    emit dlgSpotlightSetting.sigKeyChange(DESKTOP_MODE_ACTIVE,m_shortcutkeyReadmode);
    emit dlgSpotlightSetting.sigKeyChange(DESKTOP_MODE_LASERPEN,m_shortcutkeyLasterPen);
    emit dlgSpotlightSetting.sigKeyChange(DESKTOP_MODE_WATORDROP,m_shortcutkeyFindMouse);
    emit dlgSpotlightSetting.sigKeyChange(DESKTOP_MODE_SCREENSHOT,m_shortcutkeyScreenshot);
}

void TransparentDesktopQWidget::mouseMoveEvent(QMouseEvent *e)
{
    nMouseMoveCount++;
    if(nMouseMoveCount%3==0)
    {
        mutex.lock();
        if(g_RecordPosition==g_CurrentPosition)
        {
            QString str_mode= "user32";
            std::wstring wlpstr = str_mode.toStdWString();
            HMODULE h_run_mode=GetModuleHandle(wlpstr.c_str());
            HHOOK m_mouseHook=SetWindowsHookEx(WH_MOUSE_LL,mouseProc,h_run_mode,0);
            QString str_infor=QString("the hook id id:%1 and handle:%2").arg((long)m_mouseHook).arg((long)h_run_mode);
            qDebug()<<str_infor;
        }else
            g_RecordPosition=g_CurrentPosition;
        mutex.unlock();
    }

   if(m_DesktopModeType==DESKTOP_MODE_WATORDROP)
       showWaterDrop();
}

void TransparentDesktopQWidget::onRaduisChanged(QVariant value)
{
    // 不断增加圆B的半径值,并重绘;
    m_animationRadius = value.toInt();
    update();
}
void TransparentDesktopQWidget::setDesktopMode(EmDesktopModeType emModeType)
{
    m_DesktopModeType=emModeType;
    switch (m_DesktopModeType) {
    case DESKTOP_MODE_NULL:
        hide();
        break;
    case DESKTOP_MODE_SPOLIGHT:
    case  DESKTOP_MODE_LASERPEN:
     case DESKTOP_MODE_WATORDROP:
        showFullScreen();
         break;
    case  DESKTOP_MODE_ACTIVE:    
     {
        QPoint pos = mapFromGlobal(g_CurrentPosition);
        if(this->rect().contains(pos) && m_DesktopModeType==DESKTOP_MODE_ACTIVE)
        {
            hide();
        }

        else
            showFullScreen();

      }
        break;
    default:
        break;
    };
    update();
}
void TransparentDesktopQWidget::showWaterDrop()
{
    //__super::show();
    // 通过动画类不断进行重绘;
    m_waterDropAnimation->setStartValue(0);
    m_waterDropAnimation->setEndValue(m_radiusWaterDrop);
    m_waterDropAnimation->setDuration(200);


   // connect(m_waterDropAnimation, &QVariantAnimation::finished, this, &WaterDrop::close);
    m_waterDropAnimation->start();

}
// 设置水滴的颜色;
void TransparentDesktopQWidget::setColor(QColor color)
{
    m_waterDropColor = color;
}
void TransparentDesktopQWidget::drawSpolight()
{
    QPoint cursorPos = g_CurrentPosition;
    QPainterPath OuterPath;
    OuterPath.setFillRule(Qt::WindingFill);
    OuterPath.addRect(this->rect());
    QPainterPath InnerPath;

    SetCursorPos(g_CurrentPosition.x(),g_CurrentPosition.y());
    QPoint pos = mapFromGlobal(g_CurrentPosition);
    InnerPath.addEllipse(pos, m_radiusSpotLight, m_radiusSpotLight);
    QPainterPath FillPath ;
     FillPath = OuterPath.subtracted(InnerPath);

    QPainter Painter(this);
    Painter.setRenderHint(QPainter::Antialiasing);
    Painter.fillPath(FillPath, m_colorSpotLight);}
void TransparentDesktopQWidget::drawLaserpen()
{
    QPoint cursorPos = g_CurrentPosition;
    //qDebug() << "mousePressEvent" << cursorPos;

    QPainterPath OuterPath;
    OuterPath.setFillRule(Qt::WindingFill);

    QPainterPath InnerPath;

    SetCursorPos(g_CurrentPosition.x(),g_CurrentPosition.y());
    QPoint pos = mapFromGlobal(g_CurrentPosition);
    InnerPath.addEllipse(pos, 3, 3);
    OuterPath.addEllipse(pos, m_radiusLasterpen, m_radiusLasterpen);
    QPainterPath FillPath ;

    FillPath=OuterPath.subtracted(InnerPath);
    //  FillPath=InnerPath;
    QPainter Painter(this);
    Painter.setRenderHint(QPainter::Antialiasing);
    Painter.fillPath(FillPath, m_colorLasterPen);
}
void TransparentDesktopQWidget::drawActive()
{
    QPoint cursorPos = g_CurrentPosition;
    //qDebug() << "mousePressEvent" << cursorPos;

    QPainterPath OuterPath;
    OuterPath.setFillRule(Qt::WindingFill);
    OuterPath.addRect(this->rect());
    QPainterPath InnerPath;

    QPoint pos = mapFromGlobal(g_CurrentPosition);
    QPainterPath FillPath ;
        FillPath=OuterPath;
    QPainter Painter(this);
    Painter.setRenderHint(QPainter::Antialiasing);

    Painter.fillPath(FillPath, QColor(0,0,0,m_ActiveModeValue));
}
void TransparentDesktopQWidget::drawWatorDrop()
{
    SetCursorPos(g_CurrentPosition.x(),g_CurrentPosition.y());
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QBrush(m_waterDropColor));
    QPoint pos = mapFromGlobal(g_CurrentPosition);
    // 思路就是先绘制一个固定大小的圆A，然后绘制同一圆心的透明的圆B，然后通过动画类是圆B的半径从0增长到WATER_DROP_RADIUS，以致覆盖固定的圆A;
    QPainterPath waterDropPath;
    waterDropPath.addEllipse(pos, m_radiusWaterDrop, m_radiusWaterDrop);
    QPainterPath hidePath;
    hidePath.addEllipse(pos, m_animationRadius, m_animationRadius);

    waterDropPath -= hidePath;

    QPainterPath InnerPath;
    InnerPath.addEllipse(pos, 3, 3);
    waterDropPath-=InnerPath;
    painter.drawPath(waterDropPath);
}
void TransparentDesktopQWidget::paintEvent(QPaintEvent *event)
{

    switch (m_DesktopModeType) {
    case DESKTOP_MODE_NULL:
        break;
    case DESKTOP_MODE_SPOLIGHT:
        drawSpolight();
        break;
    case  DESKTOP_MODE_LASERPEN:
        drawLaserpen();
        break;
    case  DESKTOP_MODE_ACTIVE:
        drawActive();
        break;
    case DESKTOP_MODE_WATORDROP:
        drawWatorDrop();
        break;
    default:
        break;
    };


    // Painter.strokePath(OuterPath.simplified(), QPen(Qt::black, 1));
    // Painter.strokePath(InnerPath, QPen(Qt::black, 3));
}
void TransparentDesktopQWidget::setSetting()
{
   // QSpotlightSetting w;
    dlgSpotlightSetting.setItermColor(DESKTOP_MODE_SPOLIGHT,&m_colorSpotLight);
    dlgSpotlightSetting.setItermColor(DESKTOP_MODE_LASERPEN,&m_colorLasterPen);
    dlgSpotlightSetting.setItermColor(DESKTOP_MODE_WATORDROP,&m_waterDropColor);
    dlgSpotlightSetting.setItermRadius(DESKTOP_MODE_SPOLIGHT,&m_radiusSpotLight);
    dlgSpotlightSetting.setItermRadius(DESKTOP_MODE_WATORDROP,&m_radiusWaterDrop);
    dlgSpotlightSetting.setItermRadius(DESKTOP_MODE_LASERPEN,&m_radiusLasterpen);
    dlgSpotlightSetting.setItermShortcutKey(DESKTOP_MODE_SPOLIGHT,&m_shortcutkeySpotLight);
    dlgSpotlightSetting.setItermShortcutKey(DESKTOP_MODE_ACTIVE,&m_shortcutkeyReadmode);
    dlgSpotlightSetting.setItermShortcutKey(DESKTOP_MODE_LASERPEN,&m_shortcutkeyLasterPen);
    dlgSpotlightSetting.setItermShortcutKey(DESKTOP_MODE_WATORDROP,&m_shortcutkeyFindMouse);
    dlgSpotlightSetting.setItermShortcutKey(DESKTOP_MODE_SCREENSHOT,&m_shortcutkeyScreenshot);
     dlgSpotlightSetting.setActiveValuePoint(&m_ActiveModeValue);
    dlgSpotlightSetting.show();
    update();
}


SpotlightWidget::SpotlightWidget(QWidget *parent) : QWidget(parent),m_mouseHook(NULL),
                                                    m_bEnableSpotlight(false),m_bEnableReadMode(false),
                                                    m_bEnableLasterPen(false),
                                                    m_bEnableFindCursor(false),m_bEnableControlPIP(false),
                                                    m_nCurrentDestop(0)
{

    QString str_mode= "user32";
    std::wstring wlpstr = str_mode.toStdWString();
    HMODULE h_run_mode=GetModuleHandle(wlpstr.c_str());
   // m_mouseHook =SetWindowsHookEx(WH_MOUSE_LL,mouseProc,h_run_mode,0);

//    HMODULE h_run_mode=GetModuleHandle(NULL);
    m_mouseHook =SetWindowsHookEx(WH_MOUSE_LL,mouseProc,h_run_mode,0);
    Sleep(500);
//m_mouseHook =SetWindowsHookEx(WH_MOUSE_LL,mouseProc,h_run_mode,0);
    gp_SpotlightWidget=this;
    m_vtControlSpotlight.clear();
    m_vtDestopDisplay.clear();


    QString str_infor=QString("the hook id id:%1 and handle:%2").arg((long)m_mouseHook).arg((long)h_run_mode);
   // QMessageBox::warning(NULL,"注意",str_infor);
    qDebug()<<str_infor;
    QDesktopWidget *deskWgt = QApplication::desktop();
    QRect desktop_width =deskWgt->screenGeometry();
    int n_count=deskWgt->screenCount();

    DesktopDisplay *p_desktop_new;
    for (int i=0;i<n_count;i++)
    {
        QRect desktop_temp =deskWgt->screenGeometry(i);

        TransparentDesktopQWidget* p_current =new TransparentDesktopQWidget;
        p_current->move(desktop_temp.topLeft());
        p_current->setGeometry(desktop_temp);
        //  p_current->resize(desktop_temp);
        p_current->showFullScreen();

        p_desktop_new=new  DesktopDisplay(desktop_temp);
        m_vtDestopDisplay.push_back(p_desktop_new);
        m_vtControlSpotlight.push_back(p_current);
        connect(this,SIGNAL( setSpotlightMode(EmDesktopModeType )),p_current,SLOT(setDesktopMode(EmDesktopModeType)));
        connect(this,SIGNAL( showWaterDrop( )),p_current,SLOT(showWaterDrop()));
        if(i==0)
        {
            connect(this,SIGNAL(setSetting()),p_current,SLOT(setSetting()));
            connect(&p_current->dlgSpotlightSetting,SIGNAL(sigKeyChange(EmDesktopModeType,QString)),this,SIGNAL(sigKeyChange(EmDesktopModeType,QString)));
            connect(&p_current->dlgSpotlightSetting,SIGNAL(languageKeyPress(int)),this,SIGNAL(languageKeyPress(int)));
            connect(this,SIGNAL(setShutcutHotKeyFail(EmDesktopModeType)),&p_current->dlgSpotlightSetting,SLOT(setShutcutHotKeyFail(EmDesktopModeType)));
        }

    }
    // qDebug()<<"display size"<<m_vtControlSpotlight.size();

    for (int i=0;i<n_count;i++)
    {
        foreach( p_desktop_new,m_vtDestopDisplay)
        {
            p_desktop_new->expondDestop(m_vtDestopDisplay[i]->getDestop());
        };
    };

//最小化到任务栏
    ///////////////////////////////
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);
    setWindowFlags(Qt::FramelessWindowHint);//无边框
    setAttribute(Qt::WA_TranslucentBackground);//背景透明




    /////////////////////


    connect(this,SIGNAL(moveCursorPos(QPoint )),this,SLOT( moveCursorPosTo(QPoint )),Qt::QueuedConnection);

    enableWidget();

    if(m_vtControlSpotlight.size()>0)
        m_vtControlSpotlight[0]->readSettings();


}
SpotlightWidget::~SpotlightWidget()
{
    if(m_vtControlSpotlight.size()>0)
        m_vtControlSpotlight[0]->writeSettings();
    this->setCursor(Qt::ArrowCursor);
    UnhookWindowsHook(WH_MOUSE_LL,mouseProc);
    foreach(TransparentDesktopQWidget* p_spotlight, m_vtControlSpotlight)
    {
        delete  p_spotlight;
    }
    foreach(DesktopDisplay *p_desktop_new,m_vtDestopDisplay)
    {
        delete p_desktop_new;
    };
}
void SpotlightWidget::moveCursorPosTo(QPoint point)
{
    SetCursorPos(point.x(),point.y());
}
void SpotlightWidget::updetTransparentDesktop(){

        foreach(TransparentDesktopQWidget* p_spotlight, m_vtControlSpotlight)
                p_spotlight->update();

}
void SpotlightWidget::judgeMousePosition()
{
    static int n_count=0;
  //  qDebug() << n_count++<< " mouse position x:"<<g_CurrentPosition.x()<<" y:"<<g_CurrentPosition.y();
    for(int i=0;i<m_vtDestopDisplay.size();i++)
    {

        int n_return=m_vtDestopDisplay[i]->judgePosition(g_CurrentPosition);
        if(n_return!=DESKTOP_NULL)
        {
            if(n_return==DESKTOP_CHANGE)
            {
              emit moveCursorPos(g_CurrentPosition);
            }
            if(i!=m_nCurrentDestop)
            {
                m_nCurrentDestop=i;
                enableWidget();
                break;
            // return 0;
            };
        //p_desktop_new->expondDestop(m_vtDestopDisplay[i]->getDestop());
    };

   };
}
void SpotlightWidget::checkMethodFunction()
{ 
    //用于更新聚光灯功能
    if(m_bEnableSpotlight )
       {
          updetTransparentDesktop();
       }
     else if (m_bEnableReadMode)
      {

           judgeMousePosition();
           if(m_bEnableLasterPen||m_bEnableFindCursor)
               updetTransparentDesktop();
      }
      else if ( m_bEnableLasterPen||m_bEnableFindCursor)
      {
       updetTransparentDesktop();
      }

    //判断鼠标移动问题
}


void  SpotlightWidget::enableWidget()
{
    if(m_bEnableSpotlight)
    {
        emit setSpotlightMode(DESKTOP_MODE_SPOLIGHT);
        return ;
    }
    if(m_bEnableReadMode)
    {
        // emit setSpotlightMode(DESKTOP_MODE_ACTIVE);
       for(int j=0;j<m_vtControlSpotlight.size();j++)
       {
           if(m_nCurrentDestop==j)
           {
               if(m_bEnableLasterPen)
               {
                   m_vtControlSpotlight[j]->setDesktopMode(DESKTOP_MODE_LASERPEN);
                   continue;
               }
               if(m_bEnableFindCursor)
               {
                   m_vtControlSpotlight[j]->setDesktopMode(DESKTOP_MODE_WATORDROP);
                   continue;
               }
               m_vtControlSpotlight[j]->hide();
           }
           else
               m_vtControlSpotlight[j]->setDesktopMode(DESKTOP_MODE_ACTIVE); ;
            //qDebug() << n_count++<< " mouse desktop last"<<m_nCurrentDestop<<"curret"<<i<<"size"<<m_vtControlSpotlight.size();
       };
        return ;
    }
    if(m_bEnableLasterPen)
    {
        emit setSpotlightMode(DESKTOP_MODE_LASERPEN);
        return ;
    }
    if(m_bEnableFindCursor)
    {
         emit setSpotlightMode(DESKTOP_MODE_WATORDROP);
         return;
    }
    emit setSpotlightMode(DESKTOP_MODE_NULL);

}

void SpotlightWidget::SendShortcutKeySig()
{
    if(m_vtControlSpotlight.size()>0)
        m_vtControlSpotlight[0]->SendShortcutKeySig();
}

void SpotlightWidget::setControlPIPAction()
{
    QDesktopWidget *deskWgt = QApplication::desktop();
    int n_count=deskWgt->screenCount();
    m_currDesktopIndex=deskWgt->primaryScreen();
    m_currDesktopRect=deskWgt->screenGeometry(m_currDesktopIndex);
    if(n_count==2)
        emit setEnableControlPIPAction(true);
    else
        emit setEnableControlPIPAction(false);
}

void SpotlightWidget::monitorMouseDesktop(QPoint point)
{
    QRect temp_rect;
    if(m_bEnableControlPIP)
    {
        bool blIsChange;
        if(point.x()>=m_currDesktopRect.x() && point.x()<=m_currDesktopRect.x()+m_currDesktopRect.width()
          && point.y()>=m_currDesktopRect.y() && point.y()<=m_currDesktopRect.y()+m_currDesktopRect.height())
            blIsChange=false;
        else
            blIsChange=true;


        if(blIsChange)
        {
            QDesktopWidget *deskWgt = QApplication::desktop();
            int n_count=deskWgt->screenCount();
            for(int i=0;i<n_count;i++)
            {
                temp_rect=deskWgt->screenGeometry(i);
                if(m_currDesktopRect!=temp_rect)
                {
                    m_currDesktopRect=temp_rect;
                    emit changeMouseDesktop(i);
                    return;
                }
            }
        }
    }
}

void SpotlightWidget:: shutcutHotKeyPress(EmDesktopModeType emType,bool blEnable)
{
    switch (emType) {
    case DESKTOP_MODE_SPOLIGHT:
        m_bEnableSpotlight=blEnable;
        break;
    case  DESKTOP_MODE_ACTIVE:
       m_bEnableReadMode=blEnable;
        break;
    case DESKTOP_MODE_LASERPEN:
        m_bEnableLasterPen=blEnable;
        break;
    case  DESKTOP_MODE_WATORDROP:
        m_bEnableFindCursor=blEnable;
        break;
    case DESKTOP_MODE_NULL:
    default:
        return ;
    }
    enableWidget();
}

void SpotlightWidget::setEnableControlPIP(bool bisEnable)
{

    m_bEnableControlPIP=bisEnable;
}
#if 0
bool  TransparentDesktopQWidget::event(QEvent *event)
{
///qDebug()<<"event widget begin"<<this->rect();
    if ( event->type() == QEvent::Move)
    {
        QMoveEvent *pMoveEvent = dynamic_cast<QMoveEvent *>(event);

        if (pMoveEvent != NULL)
        {
            QPoint pos = pMoveEvent->pos();
            static int n_count_times=0;

           qDebug()<<"iterms:"<<n_count_times++<<"curret: "<<pos;
        }
    }

    return QWidget::event(event);
}
void TransparentDesktopQWidget::mousePressEvent(QMouseEvent *event){
   this->windowPos = this->pos();
   this->mousePos = event->globalPos();
   this->dPos = mousePos - windowPos;
    qDebug()<<"mousePressEvent "<<this->dPos;
 }
 void TransparentDesktopQWidget::mouseMoveEvent(QMouseEvent *event){
   this->move(event->globalPos() - this->dPos);
      qDebug()<<"mouseMoveEvent "<<this->dPos;
}
#endif
