#include "MagnifyingGlass.h"
#include "ButtonTool.h"
#include <QMouseEvent>
#include <QPaintEvent>
#include <QShowEvent>
#include <QPainter>
#include <QApplication>
#include <QDesktopWidget>
#include <QScreen>
#include <QDebug>
#include <QtMath>

#include "ProcessObject.h"
#include "userdefine.h"

MagnifyingGlass::MagnifyingGlass(QWidget *parent)
    : ImageToolBase(parent)
    , m_qZoomRatio(2.0)
{
    InitUi();

    InitProperty();
}

MagnifyingGlass::~MagnifyingGlass()
{

}

void MagnifyingGlass::InitUi()
{
    showFullScreen();

    m_pZoom = new QWidget(this);
    m_pZoom->setObjectName("Zoom");

    m_pButtonTool = new ButtonTool(this);
    m_pButtonTool->InitButtons({ "LampButton","SwitchButton","CloseButton"});//"AddButton","ReduceButton"
    m_pButtonTool->setVisible(false);
//"CutButton",

}

void MagnifyingGlass::InitProperty()
{
    this->setWindowFlags(Qt::FramelessWindowHint);
    setAutoFillBackground(true);
    QPalette pal = palette();
    pal.setColor(QPalette::Background,Qt::transparent);
    setPalette(pal);
    setWindowOpacity(1);
    setAttribute(Qt::WA_TranslucentBackground);

    //添加自定义类控制
    setAttribute(Qt::WA_StyledBackground,true);

    //获取程序当前运行目录
    //QString path = QCoreApplication::applicationDirPath();

    QFile resourceqss(":/ImageTools/qss/ImageToolBase.qss");
    resourceqss.open(QFile::ReadOnly);
    this->setStyleSheet(resourceqss.readAll());
    resourceqss.close();

    m_bLight = true;
    SetLightState("OpenLight");
    m_pButtonTool->SetLampToolTip(m_bLight);
    m_pButtonTool->SetAddZoomRatio(m_qZoomRatio);
    m_pButtonTool->SetReduceZoomRatio(m_qZoomRatio);
    //SetLightState("CloseLight");

    connect(m_pButtonTool, &ButtonTool::clicked, this, [=](ButtonTool::STATE state){
        switch (state) {
            case ButtonTool::STATE::CUT: {
                m_bCut = !m_bCut;
                update();
                break;
            }
            case ButtonTool::STATE::LAMP: {
                m_bLight = !m_bLight;
                if(m_bLight)
                {
                    m_pButtonTool->SetLampToolTip(m_bLight);
                    SetLightState("OpenLight");
                    update();
                } else {
                    m_pButtonTool->SetLampToolTip(m_bLight);
                    SetLightState("CloseLight");
                    update();
                }

                break;
            }
            case ButtonTool::STATE::CLOSE: {
                emit clicked(STATE::CLOSE);
                this->hide();
                break;
            }
            case ButtonTool::STATE::ADD: {
            m_qZoomRatio+=0.5;
            if(m_qZoomRatio>4)
                m_qZoomRatio=4;
            m_pButtonTool->SetAddZoomRatio(m_qZoomRatio);
            m_pButtonTool->SetReduceZoomRatio(m_qZoomRatio);
            update();
            break;
            }
            case ButtonTool::STATE::REDUCE: {
            m_qZoomRatio-=0.5;
            if(m_qZoomRatio<1.5)
                m_qZoomRatio=1.5;
            m_pButtonTool->SetAddZoomRatio(m_qZoomRatio);
            m_pButtonTool->SetReduceZoomRatio(m_qZoomRatio);
            update();
            break;
            }
            case ButtonTool::STATE::SWITCH: {
            m_bCut = !m_bCut;
            update();
            break;
           }
        }
    });

    // 初始化 处理屏幕的对象 并初始化 可活动范围
    QDesktopWidget * deskTop = QApplication::desktop();
    int nWidth=0,nHeight=0;
    QRect currRect;
    m_nScreenX=0;
    m_nScreenY=0;
    dbScX=1.0;
    dbScY=1.0;
    int nMonitorNum = deskTop->screenCount();
    int n_left=0,n_right=0,n_top=0,n_bottom=0;
    for(int i=0;i<nMonitorNum;i++)
    {
        currRect= deskTop->screenGeometry(i);
        qDebug()<<"i"<<currRect;
        n_left=n_left>currRect.left()?currRect.left():n_left;
        n_right=n_right>currRect.right()?n_right:currRect.right();
        n_top=n_top>currRect.top()?currRect.top():n_top;
        n_bottom=n_bottom>currRect.bottom()?n_bottom:currRect.bottom();
        m_nScreenX=qMin(m_nScreenX,currRect.x());
        m_nScreenY=qMin(m_nScreenY,currRect.y());

    }
    nWidth=n_right-n_left+1;
    nHeight=n_bottom-n_top+1;
    m_pScreen = new ProcessObject;
    m_pScreen->Move(QPoint(m_nScreenX,m_nScreenY));
    m_pScreen->SetMaxParentSize(QSize(nWidth,nHeight));
    m_pScreen->SetMaxWidth(nWidth);
    m_pScreen->SetMaxHeight(nHeight);

    m_pFullScreen = new QPixmap;
    m_bInit =true;
}

bool MagnifyingGlass::ZoomIsInArea(QPoint pos)
{
    if(pos.x() > m_pZoom->x()
            && pos.x() < m_pZoom->x() + m_pZoom->width()
            && pos.y() > m_pZoom->y()
            && pos.y() < m_pZoom->y() + m_pZoom->height())
    {
        return true;
    }
    return false;
}

void MagnifyingGlass::mousePressEvent(QMouseEvent *event)
{
    if(this->ZoomIsInArea(event->pos()))
    {
        m_pScreen->SetState(ProcessObject::STATE::ZOOM);
        m_pButtonTool->setVisible(false);
        this->setCursor(Qt::SizeFDiagCursor);
    }
    else if(m_pScreen->IsInArea(event->pos()))
    {
        m_pScreen->SetState(ProcessObject::STATE::MOVE);
        m_pZoom->setVisible(false);
        m_pButtonTool->setVisible(false);
        this->setCursor(Qt::SizeAllCursor);
    }

    m_qMovePos = event->pos();
}

void MagnifyingGlass::mouseMoveEvent(QMouseEvent *event)
{
    QPoint pos(m_nScreenX+event->pos().x(),m_nScreenY+event->pos().y());
    QDesktopWidget * deskTop = QApplication::desktop();
    int nMonitorNum = deskTop->screenCount();
    QRect currRect;
//    for(int i=0;i<nMonitorNum;i++)
//    {
//        currRect= GetScreenRect(i);

//        if((pos.x()>=currRect.x()) && ((pos.x())<=currRect.right())
//          && ((pos.y())>=currRect.y())  && ((pos.y())<=currRect.bottom()))
//        {
//            if((GetScreenRect(i).width() != deskTop->screenGeometry(i).width()) || (GetScreenRect(i).height() != deskTop->screenGeometry(i).height()))
//            {
//                //dbScX=(double)GetScreenRect(i).width()/deskTop->screenGeometry(i).width();
//                //dbScY=(double)GetScreenRect(i).height()/deskTop->screenGeometry(i).height();
//            }
//        }
//    }

    if(m_pScreen->GetState() == ProcessObject::STATE::MOVE)
    {
        QPoint pos(event->x() - m_qMovePos.x(), event->y() - m_qMovePos.y());
        m_pScreen->Move(pos);
        m_qMovePos = event->pos();
    } else if(m_pScreen->GetState() == ProcessObject::STATE::ZOOM)
    {
        QPoint pos(event->x() - m_qMovePos.x(), event->y() - m_qMovePos.y());
        int w = m_pScreen->width() + pos.x();
        int h = m_pScreen->height() + pos.y();
        m_pScreen->SetGeometry(m_pScreen->x(),
                               m_pScreen->y(),
                               w, h);
        m_qMovePos = event->pos();
    }
    update();
}

void MagnifyingGlass::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event)
    if(m_pScreen->GetState() == ProcessObject::STATE::MOVE)
    {
        m_pScreen->SetState(ProcessObject::STATE::SELECT);
        m_pZoom->setVisible(true);
        m_pButtonTool->setVisible(true);
    } if(m_pScreen->GetState() == ProcessObject::STATE::ZOOM)
    {
        m_pScreen->SetState(ProcessObject::STATE::SELECT);
        m_pScreen->SetStart(m_pScreen->GetLeftTopPos());
        m_pScreen->SetEnd(m_pScreen->GetRightBottomPos());
        m_pButtonTool->setVisible(true);
    }
    this->setCursor(Qt::ArrowCursor);
}

void MagnifyingGlass::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::HighQualityAntialiasing);
    int x = m_pScreen->x();
    int y = m_pScreen->y();
    int w = m_pScreen->width();
    int h = m_pScreen->height();

    QPen pen;
    pen.setColor(QColor(0,0,0,0));
    painter.setPen(pen);

    QPixmap backgroundscreen(m_pScreen->GetMaxParentWidget(), m_pScreen->GetMaxParentHeight());
    //用给定的颜色填充像素图
    backgroundscreen.fill(MaskLayerColor);
    painter.drawPixmap(0,0, *m_pBackgroundScreen);
    painter.drawPixmap(0,0, backgroundscreen);



    if(w != 0 && h != 0)
    {
//        if(m_bCut)
//        {
            int side = qMin(w, h);
            // x,y 的坐标换算比例
            float scale_x = float(x)/float(m_pScreen->GetMaxParentWidget()-side);
            float scale_y = float(y)/float(m_pScreen->GetMaxParentHeight()-side);
            m_pScreen->SetGeometry(m_pScreen->x(), m_pScreen->y(), side, side);
            QTransform transform;
            transform.translate(x*dbScX, y*dbScY);
            transform.scale(m_qZoomRatio, m_qZoomRatio);
            QPixmap pix = m_pFullScreen->copy((x + static_cast<int>(float(side)/float(m_qZoomRatio)*scale_x))*dbScX,
                                              (y + static_cast<int>(float(side)/float(m_qZoomRatio)*scale_y))*dbScY,
                                              static_cast<int>(float(side)/float(m_qZoomRatio))*dbScX,
                                              static_cast<int>(float(side)/float(m_qZoomRatio))*dbScY);
            QBrush brush(pix);
            brush.setTransform(transform);
            painter.setBrush(brush);

            if(m_bCut)
                painter.drawRect(x, y, side, side);
            else
                painter.drawEllipse(x, y, side, side);

            int circle_centerx = x + side/2;
            int circle_centery = y + side/2;
            int r = side/2;
            int x1,y1;
            if(m_bCut)
            {
                x1=x + side;
                y1=y + side;
            }else {
                x1 = static_cast<int>(double(circle_centerx) + double(r) * qCos(45.0));
                y1 = static_cast<int>(double(circle_centery) + double(r) * qSin(45.0));
            }

            m_pZoom->move(x1-m_pZoom->width()/2, y1-m_pZoom->height()/2);
            //m_pZoom->show();

//        } else {
//            // x,y 的坐标换算比例
//            float scale_x = float(x)/float(m_pScreen->GetMaxParentWidget()-w);
//            float scale_y = float(y)/float(m_pScreen->GetMaxParentHeight()-h);
//            QTransform transform;
//            transform.translate(x, y);
//            transform.scale(m_qZoomRatio, m_qZoomRatio);
//            QPixmap pix = m_pFullScreen->copy(x + static_cast<int>(float(w)/float(m_qZoomRatio)*scale_x),
//                                              y + static_cast<int>(float(h)/float(m_qZoomRatio)*scale_y),
//                                              static_cast<int>(float(w)/float(m_qZoomRatio)),
//                                              static_cast<int>(float(h)/float(m_qZoomRatio)));
//            QBrush brush(pix);
//            brush.setTransform(transform);
//            painter.setBrush(brush);
//            painter.drawPixmap(x, y, m_pFullScreen->copy(x, y, w, h));
//            painter.drawRect(x, y, w, h);

//            m_pZoom->move(x+w-m_pZoom->width()/2, y+h-m_pZoom->height()/2);
//            //m_pZoom->show();

//        }
        // 动态变更按钮组位置
        int maxheight = m_pScreen->GetMaxParentHeight();
        int distance_y_bottom = maxheight - (y+h);
        int distance_y_top = m_pScreen->y();
        if(distance_y_bottom <= m_pButtonTool->height() + 7 && distance_y_top <= m_pButtonTool->height() + 7)
        {
            m_pButtonTool->move(x+w-m_pButtonTool->width(), y+h-m_pButtonTool->height()-7);
        } else if(distance_y_bottom<= m_pButtonTool->height() + 7)
        {
            m_pButtonTool->move(x+w-m_pButtonTool->width(), y - m_pButtonTool->height() - 7);
        } else {
            m_pButtonTool->move(x+w-m_pButtonTool->width(), y+h+7);
        }
    }

}

void MagnifyingGlass::showEvent(QShowEvent *event)
{
    Q_UNUSED(event)
    if(m_bInit)
    {
        int wide = m_pScreen->GetMaxParentHeight()/4;

        int x = QCursor().pos().x()-wide;
        if(x<0)
            x=wide;

        qDebug()<<"x:"<<x;
                //(m_pScreen->GetMaxParentWidget() - wide)/2;
        int y = QCursor().pos().y()-wide;
        if(y<0)
            y=wide;

        qDebug()<<x<<y;
                //(m_pScreen->GetMaxParentHeight() - wide)/2;

       // QCursor().pos()
//        m_pScreen->SetStart(QPoint(x,y));

//        m_pScreen->SetGeometry(x, y, wide, wide);
        m_pScreen->SetStart(QPoint(x,y));
        m_pScreen->SetGeometry(x,y, wide, wide);


        // QT5.6 获取主屏幕大小 - 全屏大小
        QScreen *screen = QApplication::primaryScreen();
        *m_pFullScreen = screen->grabWindow(
                                           QApplication::desktop()->winId(),
                                           m_nScreenX,
                                           m_nScreenY,
                                           m_pScreen->GetMaxParentWidget(),
                                           m_pScreen->GetMaxParentHeight()
                                       );


        m_pBackgroundScreen = new QPixmap(*m_pFullScreen);

        resize(m_pScreen->GetMaxParentWidget(), m_pScreen->GetMaxParentHeight());
        move(m_nScreenX, m_nScreenY);
        QCursor::setPos(QPoint(x+m_nScreenX+wide/2,y+m_nScreenY+wide/2));
        update();
        m_pZoom->show();
        m_pButtonTool->setVisible(true);

    }
}

void MagnifyingGlass::keyPressEvent(QKeyEvent *event)
{
    //Esc键取消截图
    if(event->key() == Qt::Key_Escape)
    {
        //emit activationScreenshot();
        emit clicked(STATE::CLOSE);
        this->hide();
        //this->close();
    }
}
