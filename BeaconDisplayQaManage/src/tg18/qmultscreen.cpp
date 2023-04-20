#include "qmultscreen.h"
#include <QPainter>
#include <QApplication>
#include <QScreen>
#include <QDesktopWidget>
#include<QDebug>
#include<QLabel>
QMultScreen::QMultScreen(QWidget *parent) : QFrame(parent)
{
  //  setAutoFillBackground(true);
    // 使用 Highlight 作为背景色
  //  setBackgroundRole(QPalette::Highlight);
    nCurrActiveScreenId=0;
   StScreen screen;
//setWindowFlags(Qt::FramelessWindowHint);
   QDesktopWidget * deskTop = QApplication::desktop();
      int curMonitor = deskTop->screenCount (  ); // 参数是一个QWidget*

                                                  //让程序无边框

   //    setWindowFlags( Qt::FramelessWindowHint );
    //让程序背景透明
        //   setAttribute(Qt::WA_TranslucentBackground, true);

      int nScreenCount = QApplication::desktop()->screenCount();
      QRect rect_all;
      for (int i=0;i<curMonitor;i++)
      {
         screen.rectScreen= deskTop->screenGeometry(i);
    //     screen.rectScreen.setRect(screen.rectScreen.left(),screen.rectScreen.bottom(),screen.rectScreen.width(),screen.rectScreen.height()) ;
         m_vtScreen.push_back(screen);
         rect_all.operator|=(screen.rectScreen);

      }
  //    m_nActScreenY = screenRect.height();
  // this->setStyleSheet("QWidget{background:#ff0000;} QWidget:hover{background:#00ff00;}");

      //获取系统设置的屏幕个数（屏幕拷贝方式该值为1）
  //    int g_nScreenCount = desktopWidget->screenCount();
}
QMultScreen::~QMultScreen()
{

}
void QMultScreen::paintEvent(QPaintEvent *event)
{

    //Q_UNUSED(event);
#if 0
    QPainter painter(this);

    QPen pen(Qt::red);

    painter.setPen(pen);

    painter.drawRect(0,0,100,100);

    painter.drawLine(0,0, 100, 100);

       painter.setViewport(0, 0, 100 ,100 );

       painter.setWindow(0, 0,100,100);

   // qDebug() << "set viewport:\t x = " << painter.viewport().width() << "y = "

           //  << painter.viewport().height();

   // qDebug() << "set window:\t x = " << painter.window().width() << "y = "
  //
        //     << painter.window().height();

    painter.drawRect(50,50, 500, 500);

    painter.drawLine(100,0, 0, 100);



    return;
#endif
#if 1
    QPainter painter(this);

    QPen pen(Qt::white);

    painter.setPen(pen);
 painter.fillRect(rect(),QColor(200,200,200));
    QRect rect_all;
    foreach(StScreen screen,m_vtScreen)
    {

//        IdentificationDisplayDlg.setGeometry(screen.rectScreen.x(),
//                                             screen.rectScreen.y(),
//                                             screen.rectScreen.width(),
//                                             screen.rectScreen.height());
//        IdentificationDisplayDlg.show();

        rect_all|=screen.rectScreen;
    }
    double db_scal_x=rect().width()*1.0/rect_all.width()/2;
    double db_scal_y=rect().height()*1.0/rect_all.height()/2;

   qDebug() << "set viewport:\t x"<<db_scal_x<<"set viewport:\t y"<<db_scal_y;
   painter.setViewport(rect().width()/4,rect().height()/4,width(),height());
  //  painter.setWindow(rect_all);
    QColor color_buffer[5]={QColor(200,100,200),QColor(255,255,200),QColor(255,60,255),QColor(255,55,55)
                           ,QColor(0,0,255)};
    int n_iterm=0;
    color_buffer[1]=QColor(255,255,0);

   // painter.drawRect(50,50, 500, 500);
    QFont font("Arial", 15);
    font.setBold(true);
    QString str_temp="1";
    QString str_control=" CONTROL ";
    QString str_char;
    font.setBold(true);

  //  painter.drawLine(100,0, 0, 100);
    foreach(StScreen screen,m_vtScreen)
    {
        QRect rect_current=screen.rectScreen;
        rect_current.setLeft(rect_current.left()*db_scal_x);
        rect_current.setRight(rect_current.right()*db_scal_x);
        rect_current.setTop(rect_current.top()*db_scal_y);
        rect_current.setBottom(rect_current.bottom()*db_scal_y);
       // painter.drawRect(rect_current);
        if(n_iterm==nCurrActiveScreenId)
            painter.fillRect(rect_current,QColor(0,255,0));
        else
            painter.fillRect(rect_current,color_buffer[n_iterm]);
     //   painter.drawLine(screen.rectScreen.topLeft(),screen.rectScreen.bottomRight());


        n_iterm++;

        font.setPixelSize(qMin(rect_current.width(),rect_current.height()));
        painter.setFont(font);
        painter.setPen(QColor(255,0,0));
        QFontMetrics metrics = painter.fontMetrics();
        QString str_item=QString("%1").arg(n_iterm);
        painter.drawText(rect_current.center().x()-metrics.width(str_item)/2,rect_current.center().y()+metrics.width(str_item)/2,str_item);


    }

  //  painter.fillRect(rect(),QColor(255,0,255));
 // painter;
  //  drawTg18Oiq(painter);
#if 0
    QPainter painter(this);

        QPen pen(Qt::red);

        painter.setPen(pen);

        qDebug() << "viewport:\t x = " << painter.viewport().width() << "y = "

                 << painter.viewport().height();

        qDebug() << "window:\t\t x = " << painter.window().width() << "y = "

                 << painter.window().height();

        painter.drawRect(0,0,100,100);

        painter.drawLine(0,0, 100, 100);

    //    painter.setViewport(0, 0, 100 ,100 );

        painter.setWindow(0, 0,100,100);

        qDebug() << "set viewport:\t x = " << painter.viewport().width() << "y = "

                 << painter.viewport().height();

        qDebug() << "set window:\t x = " << painter.window().width() << "y = "

                 << painter.window().height();

        painter.drawRect(50,50, 50, 50);

         painter.drawLine(100,0, 0, 100);
#endif

#if 1


            //  painter.drawText(rect_text,Qt::AlignHCenter|Qt::AlignTop,"Copyright©BEACON");

            /*
        QConicalGradient conicalGradient(10+50,  230 + 50,0);
        //创建了一个QConicalGradient对象实例，参数分别为中心坐标和初始角度
        conicalGradient.setColorAt(0,Qt::green);
        conicalGradient.setColorAt(0.2,Qt::white);
        conicalGradient.setColorAt(0.4,Qt::blue);
        conicalGradient.setColorAt(0.6,Qt::red);
        conicalGradient.setColorAt(0.8,Qt::yellow);
        conicalGradient.setColorAt(1.0,Qt::green);
        //设置渐变的颜色和路径比例
        painter.setBrush(QBrush(conicalGradient));
        painter.drawEllipse(10, 230, 100, 100);//在相应的坐标画出来
        painter.restore();

        painter.save();
        QConicalGradient conicalGradient2(width()/2, height()/2, 90);
        conicalGradient2.setColorAt(0, QColor(45, 204, 112));
        conicalGradient2.setColorAt(1.0, QColor(51, 152, 219));
        painter.setPen(QPen(QBrush(conicalGradient2), 30));
        painter.drawEllipse(QRectF((width()/2 - 65), (height()/2 - 65), 130, 130));
        painter.restore();

        //QPainterPath画圆角矩形
        painter.save();
        const qreal radius = 26;
        QPainterPath path;
        QRectF rect = QRect(150, 10, 100, 100);
        QLinearGradient myGradient(rect.topLeft(), rect.bottomRight());
        myGradient.setColorAt(0.0,Qt::green);
        myGradient.setColorAt(0.9,Qt::yellow);
        path.moveTo(rect.topRight() - QPointF(radius, 0));
        path.lineTo(rect.topLeft() + QPointF(radius, 0));
        path.quadTo(rect.topLeft(), rect.topLeft() + QPointF(0, radius));
        path.lineTo(rect.bottomLeft() + QPointF(0, -radius));
        path.quadTo(rect.bottomLeft(), rect.bottomLeft() + QPointF(radius, 0));
        path.lineTo(rect.bottomRight() - QPointF(radius, 0));
        path.quadTo(rect.bottomRight(), rect.bottomRight() + QPointF(0, -radius));
        path.lineTo(rect.topRight() + QPointF(0, radius));
        path.quadTo(rect.topRight(), rect.topRight() + QPointF(-radius, -0));
        painter.setBrush(myGradient);
        painter.fillPath(path, QColor(Qt::green));
        painter.drawPath(path);
        */


#endif

#endif
         //    QWidget::paintEvent(event);
}

void QMultScreen::mousePressEvent(QMouseEvent *event)
{
    QRect rect_all;
    foreach(StScreen screen,m_vtScreen)
    {
        rect_all|=screen.rectScreen;
    }
    double db_scal_x=rect().width()*1.0/rect_all.width()/2;
    double db_scal_y=rect().height()*1.0/rect_all.height()/2;

    int n_mouse_x=event->x()-rect().width()/4;
    int n_mouse_y=event->y()-rect().height()/4;
    int n_iterm=0;
    foreach(StScreen screen,m_vtScreen)
    {
        QRect rect_current=screen.rectScreen;
        rect_current.setLeft(rect_current.left()*db_scal_x);
        rect_current.setRight(rect_current.right()*db_scal_x);
        rect_current.setTop(rect_current.top()*db_scal_y);
        rect_current.setBottom(rect_current.bottom()*db_scal_y);

        if((n_mouse_x>rect_current.left()) && (n_mouse_x<rect_current.right()) &&
           (n_mouse_y>rect_current.top()) &&(n_mouse_y<rect_current.bottom()))
        {
            emit currentActiveScrrenIdChanged(n_iterm);
        }
        n_iterm++;
    }
}
