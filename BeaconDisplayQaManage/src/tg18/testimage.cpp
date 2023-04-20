#include "testimage.h"

#include<qmath.h>
#include <qDebug>
#include<windows.h>
#include <QApplication>
#include <QDesktopWidget>
#include "userdefine.h"
#include <QMessageBox>
int TestImage::m_nOperatorDisplay=0;
double TestImage::m_dbDotPitch=0.07;
bool TestImage::m_blNinePoint=false;

TestImage::TestImage(QWidget *parent) :
           QDialog(parent),m_autoHideWidget(m_nOperatorDisplay)

{


    setWindowModality(Qt::WindowModal);
       setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
//    m_visualTestDialg.setWindowModality(Qt::WA_ShowModal);
//   setWindowFlags(Qt::FramelessWindowHint);
    m_emTg18Type=QA_TG18_OIQ_NORMAL;
  //  ui->setupUi(this);
//this->setAttribute(Qt::WA_DeleteOnClose);
//setWindowOpacity(0.7);
//setAttribute(Qt::WA_TranslucentBackground);
//   this->window()->setAttribute(Qt::WA_TransparentForMouseEvents);
//SetWindowLong((HWND)winId(), GWL_EXSTYLE, GetWindowLong((HWND)winId(), GWL_EXSTYLE) |
  //        WS_EX_TRANSPARENT//忽略一切消息（WM_PAINT除外）
  //        | WS_EX_LAYERED); //层风格，有他才能支持半透明

  //  m_autoHideWidget.show();
    m_autoHideWidget.setFocus();
   m_autoHideWidget.setWindowFlags(m_autoHideWidget.windowFlags() | Qt::WindowStaysOnTopHint);
    setTg18Type(QA_TG18_OIQ_NORMAL,QA_METHOD_ACCEPTANCE_ALL);
m_autoHideWidget.setPointNumber(m_blNinePoint);
 // m_visualTestDialg.setParent(this);
    connect(&m_visualTestDialg,SIGNAL(CommandOk(bool)),this,SLOT(reportResult(bool)));
    connect(&m_autoHideWidget,SIGNAL(changeTg18Type(EmTg18Type ,int )),this,SLOT(changeTg18Type(EmTg18Type ,int )));
    connect(&m_autoHideWidget,SIGNAL(reportResult(bool)),this ,SLOT(reportResult(bool)));
    connect(&m_autoHideWidget,SIGNAL(getSensorData(StCieLvxy&)),this,SIGNAL(getSensorData(StCieLvxy&)));
QRect deskRt=  QApplication::desktop()->screenGeometry(m_nOperatorDisplay);;
 this->move(deskRt.topLeft());
  qDebug()<<deskRt;
}


TestImage::~TestImage()
{

}
enum
{
    EmPositionTopLeft=0,
    EmPositionTopRight,
    EmPositionBottomLeft,
    EmPositionBottomRight,
    EmPositionCenter,
};
void drawWhitBlackWindows(QPainter *painter,QRect rectPosition,double dbScale)
{
    QRect rect_center(0,0,rectPosition.width()/2,rectPosition.height()/4);

    QRect rect_middle(0,0,rectPosition.width(),rectPosition.height()/2);
    rect_middle.moveBottomLeft(rectPosition.bottomLeft());

    rect_center.moveBottom(rectPosition.top()+rectPosition.height()/4);
    rect_center.moveLeft(rectPosition.left()+rectPosition.width()/4);
    painter->fillRect(rectPosition,QColor(13,13,13));
    painter->fillRect(rect_middle,QColor(242,242,242));

    painter->fillRect(rect_center,QColor(242,242,242));
    rect_center.moveTop(rect_middle.top());
    painter->fillRect(rect_center,QColor(13,13,13));


};
void drawCrosstalkbars(QPainter *painter,QRect rectPosition,double dbScale)
{
    QImage resultPixmap(rectPosition.width()/2,rectPosition.height(),QImage::Format_RGB32);
    QPainter painter_lines(&resultPixmap);
    QRect rect_current(0,0,rectPosition.width()/2,rectPosition.height()/2);
    QRect rect_view(0,rectPosition.height()/2,rectPosition.width()/2,rectPosition.height());

    painter_lines.fillRect(rect_current,Qt::white);
    int n_line_height=3*dbScale;
    int n_line_width=256*dbScale;

  QRect rect_bar(0,0,n_line_height,rectPosition.height()/2);
  rect_bar.moveTopRight(rect_current.topRight());
    QRect rect_line;
    int n_pos=0;
    for (int i=n_line_width;i>=1;i/=2)
    {
      rect_line.setSize(QSize(i,n_line_height));
      rect_line.moveTopRight(QPoint(rect_current.width()-n_line_height*4,(n_pos+2)*n_line_height));
       painter_lines.fillRect(rect_line,Qt::black);
      n_pos++;

    }
     painter_lines.fillRect(rect_bar,QColor(249,249,249));

   // rect_current.moveTop(rectPosition.height()/2);
    painter_lines.save();
painter_lines.setViewport(rect_view);
    painter_lines.fillRect(rect_current,Qt::black);


    //painter_lines.translate(rectPosition.topLeft());

int n_times=n_pos;
n_pos=0;
    for (int i=n_line_width;i>=1;i/=2)
    {
      rect_line.setSize(QSize(i,n_line_height));
      rect_line.moveTopRight(QPoint(rect_current.width()-n_line_height*4,((n_times-n_pos)+2)*n_line_height));
       painter_lines.fillRect(rect_line,Qt::white);
      n_pos++;

    }
  painter_lines.fillRect(rect_bar,QColor(6,6,6));

 painter_lines.restore();
 painter->drawImage(rectPosition.x(),rectPosition.y(),resultPixmap);
 QImage imge_miro=resultPixmap.mirrored(true,false);
     painter->setBrush(QBrush(Qt::white));  //白色取反则是黑色
     //painter->setCompositionMode(QPainter::CompositionMode_Difference);
 painter->drawImage(rectPosition.center().x(),rectPosition.y(),imge_miro);

painter_lines.save();
}
void drawLinePairs(QPainter *painter,QRect rectPosition,int nType,double dbScale)
{
     dbScale=1;

    QImage resultPixmap(rectPosition.width(),rectPosition.height(),QImage::Format_RGB32);
    QPainter painter_lines(&resultPixmap);
    QRect rect_current(0,0,rectPosition.width()/2,rectPosition.height());
     QRect rect_view(rectPosition.width()/2,0,rectPosition.width(),rectPosition.height());
    QPen pen_current;
painter_lines.save();
    for (int j=0;j<2*dbScale;j++)
    {
        pen_current.setWidth(1*dbScale);
        if(j==0)
       {
            pen_current.setColor(Qt::white);
            painter_lines.fillRect(rect_current,Qt::black);
        }
        else
        {
           // rect_current.moveLeft(rectPosition.width()/2);
            painter_lines.setViewport(rect_view);
            pen_current.setColor(QColor(130,130,130));
            painter_lines.fillRect(rect_current,QColor(127,127,127));
        }
        painter_lines.setPen(pen_current);


        for (int i=0;i<rect_current.width()/2;i+=(2*dbScale))
        {
           painter_lines.drawLine(i,0,i,rect_current.height()/2);
           painter_lines.drawLine(0,i+rect_current.height()/2+2,rect_current.width()/2,i+rect_current.height()/2+2);
        }
         pen_current.setWidth(1*dbScale);

         painter_lines.setPen(pen_current);

         //     painter_lines.setPen(Qt::white);
        for (int i=rect_current.width()/2;i<rect_current.width();i+=(4*dbScale))
        {
            painter_lines.drawLine(i,0,i,rect_current.height()/2);
            painter_lines.drawLine(i+1,0,i+1,rect_current.height()/2);
            painter_lines.drawLine(rect_current.width()/2+1,i+2,rect_current.width(),i+2);
            painter_lines.drawLine(rect_current.width()/2+1,i+3,rect_current.width(),i+3);
        }
}
    painter_lines.restore();


   // painter_lines.setViewport(rectPosition);
  //   QRect rect_test(0,0,rectPosition.width()/2,rectPosition.height());
 //   painter_lines.fillRect(rect_test,Qt::black);
    painter_lines.end();
    QImage image_draw;
    switch (nType) {

    case EmPositionTopLeft:
    case EmPositionCenter:
        image_draw=resultPixmap;
         break  ;


    case EmPositionTopRight:
         image_draw=resultPixmap.mirrored(true,false);
        break;
   case EmPositionBottomLeft:
         image_draw=resultPixmap.mirrored(false,true);
         break;
   case EmPositionBottomRight:
         image_draw=resultPixmap.mirrored(true,true);
         break;
    default:
      break;
    }
    painter->drawImage(rectPosition,image_draw);
      pen_current.setWidth(2);
      pen_current.setColor(QColor(63,63,63));
      painter->setPen(pen_current);
      rectPosition.adjust(-1,-1,1,1);
     painter->drawRect(rectPosition);

}
void drawQualityText(QPainter *painter,QRect rectPosition,int nType)
{
    painter->save();
    int n_arrag[3]={0,128,255};
    int n_arrag_text[3]={15,143,240};
    painter->fillRect(rectPosition,QColor(n_arrag[nType],n_arrag[nType],n_arrag[nType]));


    QFont font("Arial", 15);
     font.setBold(true);
    QString str_temp="  QUALITY  ";
    QString str_control=" CONTROL ";
     QString str_char;
   font.setBold(true);
    font.setPixelSize(rectPosition.width()/str_temp.length()*2);
    painter->setFont(font);
    QFontMetrics metrics = painter->fontMetrics();
    int n_x;
    int n_y;
    n_y=metrics.height()/2;
    int n_color_begin=n_arrag_text[nType];
    for (int i=0;i<7;i++)
    {
        n_x=rectPosition.width()/2-metrics.width(str_temp)/2;
        str_char=str_temp.at(i+2);
        if(nType==2)
             n_color_begin=n_arrag_text[nType]+i;
         else
             n_color_begin=n_arrag_text[nType]-i;
        painter->setPen(QColor(n_color_begin,n_color_begin,n_color_begin));
        painter->drawText(rectPosition.x()+n_x+ metrics.width(str_temp.left(i+2)),rectPosition.top()+n_y*2,str_char);
        str_char=str_control.at(i+1);
        if(nType==2)
             n_color_begin=n_arrag_text[nType]+i+7;
         else
             n_color_begin=n_arrag_text[nType]-i-7;

          n_x=rectPosition.width()/2-metrics.width(str_control)/2;
        painter->setPen(QColor(n_color_begin,n_color_begin,n_color_begin));
        painter->drawText(rectPosition.x()+n_x+metrics.width(str_control.left(i+1)),rectPosition.top()+n_y*4,str_char);

    }
  //  metrics.width(str_temp);
  //  painter->drawText(rectPosition,Qt::AlignCenter|Qt::AlignTop,str_char);

    painter->restore();

}
void drawPatchRect(QPainter *painter,QRect rectPosition,QColor color,int nWidth)
{
     //  painter->save();
    //画底色
       painter->fillRect(rectPosition,color);
       QRect rect_temp(rectPosition.topLeft(),QSize(nWidth,nWidth));
               int n_color=color.green()+4;
     //画左上与右下角
       painter->fillRect(rect_temp,QColor(n_color,n_color,n_color));
       rect_temp.moveBottomRight(rectPosition.bottomRight());
       painter->fillRect(rect_temp,QColor(n_color,n_color,n_color));
       rect_temp.moveTopRight(rectPosition.topRight());
   //画左下与右上角
       n_color=color.green()-4;
       painter->fillRect(rect_temp,QColor(n_color,n_color,n_color));
       rect_temp.moveBottomLeft(rectPosition.bottomLeft());
       painter->fillRect(rect_temp,QColor(n_color,n_color,n_color));
     //  painter->restore();


}
void drawPatchRectCircle(QPainter *painter,QRect rectPosition,QColor color,int nWidth,int diameter)
{
    //painter->save();
    //画底色
    painter->fillRect(rectPosition,color);
    QRect rect_temp(rectPosition.topLeft(),QSize(nWidth,nWidth));
    int n_color=color.green()+4;
    //画左上与右下角
    painter->fillRect(rect_temp,QColor(n_color,n_color,n_color));
    rect_temp.moveBottomRight(rectPosition.bottomRight());
    painter->fillRect(rect_temp,QColor(n_color,n_color,n_color));
    rect_temp.moveTopRight(rectPosition.topRight());
    //画左下与右上角
    n_color=color.green()-4;
    painter->fillRect(rect_temp,QColor(n_color,n_color,n_color));
    rect_temp.moveBottomLeft(rectPosition.bottomLeft());
    painter->fillRect(rect_temp,QColor(n_color,n_color,n_color));
    painter->restore();

    //画中间圆
    //painter->save();
    QPen current_pen;
    current_pen.setColor(QColor(color.green()-2,color.green()-2,color.green()-2));
    current_pen.setWidth(1);
    painter->setPen(current_pen);
    QBrush brush(QColor(color.green()-2,color.green()-2,color.green()-2));
    painter->setBrush(brush);
    QRect  rect_left_centre(rectPosition.right()-rectPosition.width()/2-diameter/2,rectPosition.bottom()-rectPosition.height()/2-diameter/2,diameter,diameter);
    int startAngle = 90 * 16;//起始角度
    int spanAngle = 180 * 16;//覆盖的角度，绘制方向为逆时针方向
    painter->drawPie(rect_left_centre, startAngle, spanAngle);

    current_pen.setColor(QColor(color.green()+2,color.green()+2,color.green()+2));
    current_pen.setWidth(1);;
    painter->setPen(current_pen);
    brush=QBrush(QColor(color.green()+2,color.green()+2,color.green()+2));
    painter->setBrush(brush);
    QRect  rect_right_centre(rectPosition.right()-rectPosition.width()/2-diameter/2,rectPosition.bottom()-rectPosition.height()/2-diameter/2,diameter,diameter);
    startAngle = -90 * 16;//起始角度
    spanAngle = 180* 16;//覆盖的角度，绘制方向为逆时针方向
    painter->drawPie(rect_right_centre, startAngle, spanAngle);
    //painter->restore();
}

void TestImage::drawTg18Oiq(QPainter &painter)
{

    painter.begin(this);
    painter.setPen(QPen(QColor(0,0,0),4,Qt::SolidLine));//设置画笔形式
    painter.setBrush(QBrush(Qt::black
                       ,Qt::SolidPattern));//设置画刷形式
    painter.drawRect(0,0,width(),height());
    painter.setPen(QPen(QColor(255,255,255),Qt::SolidLine));
    painter.drawLine(0,0,0,height());
    painter.end();

}
void TestImage::paintEvent(QPaintEvent *event)
{
  QPainter painter(this);




  switch (m_emTg18Type) {
  case QA_TG18_OIQ_EVERY:
  case QA_TG18_OIQ_NORMAL:
      drawTg18Oiq(painter);
      break;
#ifdef USG_QA_TG18_MP

  case  QA_TG18_MP:

      break;
#endif
    case  QA_TG18_CT:
        drawTg18Ct(painter);
        break;
    case  QA_TG18_UN80_CONSTANCY:
    case  QA_TG18_UN80:
        drawTg18Un(painter,QColor(204,204,204));
        break;
    case  QA_TG18_UN10:
         drawTg18Un(painter,QColor(26,26,26));
        break;
    case  QA_TG18_LN:
        drawTg18Ln(painter,m_nStep+1);
        break;
    case  QA_TG18_UNL80:
        drawTG18Unl(painter,QColor(204,204,204));
        break;
    case  QA_TG18_UNL10:
        drawTG18Unl(painter,QColor(26,26,26));
        break;
  case  QA_TG18_ANG:
      drawTg18Ang(painter,m_dbDotPitch);
      break; 
    case  QA_TG18_END:
        break;
  case  QA_TG18_CHEST:
      drawTg18Chest(painter);
      break;
  case  QA_TG18_KNEE:
      drawTg18Knee(painter);
      break;
  case  QA_TG18_MAM01:
      drawTg18Mam01(painter);
      break;
  case  QA_TG18_MAM02:
       drawTg18Mam02(painter);
      break;


  }




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
         QWidget::paintEvent(event);
}
void TestImage::mousePressEvent(QMouseEvent *e)
{
  //鼠标左键

  if(e->button() == Qt::LeftButton)
  {
 // m_ptPress = e->pos();
  qDebug() << pos() << e->pos() ;
 // m_bPressed = m_areaMovable.contains(m_ptPress);
  if(m_emTg18Type==QA_TG18_OIQ_EVERY)
  {
    // m_visualTestDialg.setWindowModality(Qt::WindowModal);
      m_visualTestDialg.show();
       m_visualTestDialg.raise();
  }


}

}
 void TestImage::reportResult(bool blOk)
 {

     if(blOk)
     {
      m_QaResult=m_visualTestDialg.m_QaResult;

       done(Accepted);
     }
     else
        done(Rejected);
 }
 void TestImage::setTg18Type(EmTg18Type emType,EmTg18MethodType emMethod)
 {
     m_emMethodType=emMethod;
    m_emTg18Type=emType;
    if(m_emTg18Type!=QA_TG18_OIQ_EVERY)
    {
        m_autoHideWidget.show();
        m_autoHideWidget.hideWidget();
    }
    else
    {
         m_autoHideWidget.hide();
    }
    m_autoHideWidget.initQaIterm(emType,emMethod);
}


void TestImage::changeTg18Type(EmTg18Type emTgType,int nStep)
{
    if(m_emMethodType==QA_METHOD_SINGLE)
    {
        if(m_emTg18Type!=emTgType)
            reportResult(true);
    }
    m_emTg18Type=emTgType;
    m_nStep=nStep;
    update();
}

void TestImage::notSelecteSensor()
{
    QMessageBox::warning(NULL,tr("Warning"),tr("Please select proper sensor !"));
}
void TestImage::drawTg18Ct(QPainter &painter)
{
    painter.begin(this);
    painter.setPen(QPen(QColor(0,0,0),4,Qt::SolidLine));//设置画笔形式
    painter.setBrush(QBrush(Qt::black
                       ,Qt::SolidPattern));//设置画刷形式
    painter.drawRect(0,0,width(),height());
    painter.setPen(QPen(QColor(255,255,255),Qt::SolidLine));
    painter.drawLine(width()-1,0,width()-1,height());
    painter.end();

}

void TestImage::drawTg18Ln(QPainter &painter, int step)
{
    painter.begin(this);
    painter.setPen(QPen(QColor(0,0,0),4,Qt::SolidLine));//设置画笔形式
    painter.setBrush(QBrush(Qt::black
                       ,Qt::SolidPattern));//设置画刷形式
    painter.drawRect(0,0,width(),height());
    painter.setPen(QPen(QColor(255,255,255),Qt::SolidLine));
    painter.drawLine(0,0,0,height());
    painter.drawLine(width()-1,0,width()-1,height());
    painter.end();
}

void TestImage::drawTg18Un(QPainter &painter, QColor color)
{
    painter.begin(this);
    painter.setPen(QPen(QColor(0,0,0),4,Qt::SolidLine));//设置画笔形式
    painter.setBrush(QBrush(Qt::black
                       ,Qt::SolidPattern));//设置画刷形式
    painter.drawRect(0,0,width(),height());
    painter.setPen(QPen(QColor(255,255,255),Qt::SolidLine));
    painter.drawLine(0,0,0,height());
    painter.drawLine(1,0,1,height());
    painter.end();
}
void TestImage::drawTG18Unl(QPainter &painter, QColor color)
{
    painter.begin(this);
    painter.setPen(QPen(QColor(0,0,0),4,Qt::SolidLine));//设置画笔形式
    painter.setBrush(QBrush(Qt::black
                       ,Qt::SolidPattern));//设置画刷形式
    painter.drawRect(0,0,width(),height());
    painter.setPen(QPen(QColor(255,255,255),Qt::SolidLine));
    painter.drawLine(width()-1,0,width()-1,height());
    painter.drawLine(width()-2,0,width()-2,height());
    painter.end();
}
bool TestImage::getTg18Data(StTg18Result &stResult)
{
    return  m_autoHideWidget.getTg18Data(stResult );

}
void TestImage::drawTg18Ad(QPainter &painter)
{
    QColor background=QColor(0,0,0);

    int RGB_DATA[7][7] = { 10,30,60,90,115,138,171,
                           17,37,67,91,122,147,178,
                           23,45,75,98,130,155,179,
                           24,52,76,105,130,155,188,
                           30,53,77,106,130,154,188,
                           31,53,83,105,138,162,195,
                           30,60,91,114,139,163,196 };

    double db_scale=1;//qMin(height(),width())/1024;
    if(qMin(height(),width())<1024)
           db_scale=qMin(height(),width())/1024.0;
     else
          db_scale=(qMin(height(),width())/1024);

    double center_big_rect_width=420*db_scale;
    double center_smoll_rect_width=center_big_rect_width/7;
    QRect rect_client=rect();
    painter.fillRect(rect_client,background);

    QPen pen;
    pen.setColor(QColor(196,196,196));
    pen.setWidth(1);
    painter.setPen(pen);

    QRect rect_center=QRect(rect_client.width()/2-center_big_rect_width/2,rect_client.height()/2-center_big_rect_width/2,
                            center_big_rect_width,center_big_rect_width);

    painter.drawRect(rect_center);

    pen.setWidth(2);
    painter.setPen(pen);
    for(int i=0;i<6;i++)
    {
        painter.drawLine(rect_center.left()+center_big_rect_width/7*(i+1),rect_center.top()+1,
                         rect_center.left()+center_big_rect_width/7*(i+1),rect_center.bottom());

        painter.drawLine(rect_center.left()+1,rect_center.top()+center_big_rect_width/7*(i+1),
                         rect_center.right(),rect_center.top()+center_big_rect_width/7*(i+1));
    }

    for (int m = 0; m < 7; m++)
    {
         for (int i = 1; i <= 14; i++)
         {
             painter.setPen(QPen(QColor(RGB_DATA[m][0],RGB_DATA[m][0],RGB_DATA[m][0]),1,Qt::SolidLine));//设置画笔形式
             painter.drawLine(rect_center.left()+1,rect_center.top()+center_smoll_rect_width*m+center_smoll_rect_width/15*i-0.5,
                              rect_center.left()+rect_center.width()/7-2,rect_center.top()+center_smoll_rect_width*m+center_smoll_rect_width/15*i-0.5);
             painter.drawLine(rect_center.left()+1,rect_center.top()+center_smoll_rect_width*m+center_smoll_rect_width/15*i+0.5,
                              rect_center.left()+rect_center.width()/7-2,rect_center.top()+center_smoll_rect_width*m+center_smoll_rect_width/15*i+0.5);

             painter.setPen(QPen(QColor(RGB_DATA[m][1],RGB_DATA[m][1],RGB_DATA[m][1]),1,Qt::SolidLine));//设置画笔形式
             painter.drawLine(rect_center.left()+rect_center.width()/7+1,rect_center.top()+center_smoll_rect_width*m+center_smoll_rect_width/15*i-0.5,
                              rect_center.left()+rect_center.width()/7*2-2,rect_center.top()+center_smoll_rect_width*m+center_smoll_rect_width/15*i-0.5);
             painter.drawLine(rect_center.left()+rect_center.width()/7+1,rect_center.top()+center_smoll_rect_width*m+center_smoll_rect_width/15*i+0.5,
                              rect_center.left()+rect_center.width()/7*2-2,rect_center.top()+center_smoll_rect_width*m+center_smoll_rect_width/15*i+0.5);

             painter.setPen(QPen(QColor(RGB_DATA[m][2],RGB_DATA[m][2],RGB_DATA[m][2]),1,Qt::SolidLine));//设置画笔形式
             painter.drawLine(rect_center.left()+rect_center.width()/7*2+1,rect_center.top()+center_smoll_rect_width*m+center_smoll_rect_width/15*i-0.5,
                              rect_center.left()+rect_center.width()/7*3-2,rect_center.top()+center_smoll_rect_width*m+center_smoll_rect_width/15*i-0.5);
             painter.drawLine(rect_center.left()+rect_center.width()/7*2+1,rect_center.top()+center_smoll_rect_width*m+center_smoll_rect_width/15*i+0.5,
                              rect_center.left()+rect_center.width()/7*3-2,rect_center.top()+center_smoll_rect_width*m+center_smoll_rect_width/15*i+0.5);

             painter.setPen(QPen(QColor(RGB_DATA[m][3],RGB_DATA[m][3],RGB_DATA[m][3]),1,Qt::SolidLine));//设置画笔形式
             painter.drawLine(rect_center.left()+rect_center.width()/7*3+1,rect_center.top()+center_smoll_rect_width*m+center_smoll_rect_width/15*i-0.5,
                              rect_center.left()+rect_center.width()/7*4-2,rect_center.top()+center_smoll_rect_width*m+center_smoll_rect_width/15*i-0.5);
             painter.drawLine(rect_center.left()+rect_center.width()/7*3+1,rect_center.top()+center_smoll_rect_width*m+center_smoll_rect_width/15*i+0.5,
                              rect_center.left()+rect_center.width()/7*4-2,rect_center.top()+center_smoll_rect_width*m+center_smoll_rect_width/15*i+0.5);

             painter.setPen(QPen(QColor(RGB_DATA[m][4],RGB_DATA[m][4],RGB_DATA[m][4]),1,Qt::SolidLine));//设置画笔形式
             painter.drawLine(rect_center.left()+rect_center.width()/7*4+1,rect_center.top()+center_smoll_rect_width*m+center_smoll_rect_width/15*i-0.5,
                              rect_center.left()+rect_center.width()/7*5-2,rect_center.top()+center_smoll_rect_width*m+center_smoll_rect_width/15*i-0.5);
             painter.drawLine(rect_center.left()+rect_center.width()/7*4+1,rect_center.top()+center_smoll_rect_width*m+center_smoll_rect_width/15*i+0.5,
                              rect_center.left()+rect_center.width()/7*5-2,rect_center.top()+center_smoll_rect_width*m+center_smoll_rect_width/15*i+0.5);

             painter.setPen(QPen(QColor(RGB_DATA[m][5],RGB_DATA[m][5],RGB_DATA[m][5]),1,Qt::SolidLine));//设置画笔形式
             painter.drawLine(rect_center.left()+rect_center.width()/7*5+1,rect_center.top()+center_smoll_rect_width*m+center_smoll_rect_width/15*i-0.5,
                              rect_center.left()+rect_center.width()/7*6-2,rect_center.top()+center_smoll_rect_width*m+center_smoll_rect_width/15*i-0.5);
             painter.drawLine(rect_center.left()+rect_center.width()/7*5+1,rect_center.top()+center_smoll_rect_width*m+center_smoll_rect_width/15*i+0.5,
                              rect_center.left()+rect_center.width()/7*6-2,rect_center.top()+center_smoll_rect_width*m+center_smoll_rect_width/15*i+0.5);

             painter.setPen(QPen(QColor(RGB_DATA[m][6],RGB_DATA[m][6],RGB_DATA[m][6]),1,Qt::SolidLine));//设置画笔形式
             painter.drawLine(rect_center.left()+rect_center.width()/7*6+1,rect_center.top()+center_smoll_rect_width*m+center_smoll_rect_width/15*i-0.5,
                              rect_center.right(),rect_center.top()+center_smoll_rect_width*m+center_smoll_rect_width/15*i-0.5);
             painter.drawLine(rect_center.left()+rect_center.width()/7*6+1,rect_center.top()+center_smoll_rect_width*m+center_smoll_rect_width/15*i+0.5,
                              rect_center.right(),rect_center.top()+center_smoll_rect_width*m+center_smoll_rect_width/15*i+0.5);
         }
    }

    pen.setWidth(4);
    painter.setPen(pen);
    QString str_prompt;
    double n_x, n_y;
    for (int i = 0; i <7; i++)
    {
        str_prompt=QString("%1").arg(i+1);
        n_x = rect_center.left()+center_smoll_rect_width*i+center_smoll_rect_width/2;
        n_y = rect_center.top()-center_smoll_rect_width/4;
        painter.drawText(n_x,n_y,str_prompt);

        str_prompt=QString("%1").arg(i);
        n_x = rect_center.left()-center_smoll_rect_width/4;
        n_y = rect_center.top()+center_smoll_rect_width*i+center_smoll_rect_width/5*3;
        painter.drawText(n_x, n_y, str_prompt);
    }

    painter.save();
    QString str_temp;
    str_temp=QString(" TG18-CT Pattern ");
    QRect rect_text=QRect(rect_client.width()/2-rect_client.right()/16,0,rect_client.right()/8,rect_client.height()/32);
    QFont font("Arial", 17);
    font.setBold(true);
    font.setPixelSize(rect_text.width()/str_temp.length()*2);
    painter.setFont(font);
    painter.drawText(rect_text,Qt::AlignCenter|Qt::TextWordWrap,str_temp);

    font.setPointSize(12);
    str_temp=" Copyright@2019 by BEACON ";
    font.setPixelSize(rect_text.width()/str_temp.length()*2);
    painter.setFont(font);
    rect_text=QRect(rect_client.width()/2-rect_client.right()/16,rect_client.height()/32,rect_client.right()/8,rect_client.height()/32);
    painter.drawText(rect_text,Qt::AlignCenter|Qt::TextWordWrap,"Version 8.0, 05/23\nCopyright@2019 by BEACON");
    painter.restore();
}
void drawQuadrant(QPainter *painter,QRect rect,double db_scale)
{
    int first_quadrant_rect_width=2*db_scale;
    int second_quadrant_rect_width=3*db_scale;
    int third_quadrant_rect_width=4*db_scale;
    int fourth_quadrant_rect_width=6*db_scale;
    int Rect_Border_Width=9*db_scale;

    QPen curr_pen;
    curr_pen.setColor(Qt::white);
    curr_pen.setWidth(Rect_Border_Width);
    painter->setPen(curr_pen);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(QColor(225,225,225));
    painter->setBrush(brush);
    painter->drawRect(rect);

    QRect rect_temp;
    for(int i=0;i<4;i++)
    {
        if(i==0)
        {
            curr_pen.setColor(QColor(231,231,231));
            brush.setColor(QColor(231,231,231));
        }else if(i==1)
        {
            curr_pen.setColor(QColor(233,233,233));
            brush.setColor(QColor(233,233,233));
        }else if(i==2)
        {
            curr_pen.setColor(QColor(235,235,235));
            brush.setColor(QColor(235,235,235));
        }else
        {
            curr_pen.setColor(QColor(238,238,238));
            brush.setColor(QColor(238,238,238));
        }
         painter->setBrush(brush);
         curr_pen.setWidth(1);
         painter->setPen(curr_pen);

         rect_temp=QRect(rect.left()+rect.width()/5,rect.top()+rect.height()/5*(i+1),first_quadrant_rect_width,first_quadrant_rect_width);
         painter->drawRect(rect_temp);

         rect_temp=QRect(rect.left()+rect.width()/5*2,rect.top()+rect.height()/5*(i+1),second_quadrant_rect_width,second_quadrant_rect_width);
         painter->drawRect(rect_temp);

         rect_temp=QRect(rect.left()+rect.width()/5*3,rect.top()+rect.height()/5*(i+1),third_quadrant_rect_width,third_quadrant_rect_width);
         painter->drawRect(rect_temp);

         rect_temp=QRect(rect.left()+rect.width()/5*4,rect.top()+rect.height()/5*(i+1),fourth_quadrant_rect_width,fourth_quadrant_rect_width);
         painter->drawRect(rect_temp);
    }
}
void TestImage::drawTg18Afc(QPainter &painter)
{
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    //painter.save();
    //线性渐变，渐变开始，和结束点
    QColor background=QColor(225,225,225);
    double db_scale=1;//qMin(height(),width())/1024;
    if(qMin(height(),width())<1024)
           db_scale=qMin(height(),width())/1024.0;
     else
          db_scale=(qMin(height(),width())/1024);

    int first_quadrant_rect_width=2*db_scale;
    int second_quadrant_rect_width=3*db_scale;
    int third_quadrant_rect_width=4*db_scale;
    int fourth_quadrant_rect_width=6*db_scale;
    int Big_Rect_Border_Width=6*db_scale;
    int Small_Rect_Border_Width=9*db_scale;

    QRect rect_client=rect();
    painter.fillRect(rect_client,background);

    QPen curr_pen;
    curr_pen.setColor(Qt::white);
    curr_pen.setWidth(Big_Rect_Border_Width);

    painter.setPen(curr_pen);
    painter.drawRect(rect_client);

    curr_pen.setWidth(2);
    painter.setPen(curr_pen);
    for(int i=0;i<16;i++)
    {
        painter.drawLine(rect_client.left(),rect_client.top()+(double)rect_client.height()/16*i,
                         rect_client.right(),rect_client.top()+(double)rect_client.height()/16*i);

        painter.drawLine(rect_client.left()+(double)rect_client.width()/16*i,rect_client.top(),
                         rect_client.left()+(double)rect_client.width()/16*i,rect_client.bottom());
    }

    int m,n;
    QRect rect_temp;
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            if(first_quadrant_rect_width>0)
            {
                m = (rand() % (rect_client.width()/16))/first_quadrant_rect_width;    //产生5以内的随机数
                n=(rand() % (rect_client.height()/16))/first_quadrant_rect_width;
                rect_temp=QRect(rect_client.width()/16*j+m*first_quadrant_rect_width,rect_client.height()/16*i+n*first_quadrant_rect_width,first_quadrant_rect_width,first_quadrant_rect_width);
                painter.fillRect(rect_temp,QColor(231,231,231));
            }

            if(second_quadrant_rect_width>0)
            {
                m = (rand() % (rect_client.width()/16))/second_quadrant_rect_width;    //产生5以内的随机数
                n=(rand() % (rect_client.height()/16))/second_quadrant_rect_width;
                rect_temp=QRect(rect_client.width()/2+rect_client.width()/16*j+m*second_quadrant_rect_width,rect_client.height()/16*i+n*second_quadrant_rect_width,second_quadrant_rect_width,second_quadrant_rect_width);
                painter.fillRect(rect_temp,QColor(233,233,233));
            }

            if(third_quadrant_rect_width>0)
            {
                m = (rand() % (rect_client.width()/16))/third_quadrant_rect_width;    //产生5以内的随机数
                n=(rand() % (rect_client.height()/16))/third_quadrant_rect_width;
                rect_temp=QRect(rect_client.width()/16*j+m*third_quadrant_rect_width,rect_client.height()/2+rect_client.height()/16*i+n*third_quadrant_rect_width,third_quadrant_rect_width,third_quadrant_rect_width);
                painter.fillRect(rect_temp,QColor(235,235,235));
            }

            if(fourth_quadrant_rect_width>0)
            {
                m = (rand() % (rect_client.width()/16))/fourth_quadrant_rect_width;    //产生5以内的随机数
                n=(rand() % (rect_client.height()/16))/fourth_quadrant_rect_width;
                rect_temp=QRect(rect_client.width()/2+rect_client.width()/16*j+m*fourth_quadrant_rect_width,rect_client.height()/2+rect_client.height()/16*i+n*fourth_quadrant_rect_width,fourth_quadrant_rect_width,fourth_quadrant_rect_width);
                painter.fillRect(rect_temp,QColor(238,238,238));
            }
        }
    }

    curr_pen.setWidth(Small_Rect_Border_Width);
    painter.setPen(curr_pen);
    painter.drawLine((double)rect_client.width()/2-Small_Rect_Border_Width/2,rect_client.top(),(double)rect_client.width()/2-Small_Rect_Border_Width/2,rect_client.bottom());
    painter.drawLine(rect_client.left(),(double)rect_client.height()/2-Small_Rect_Border_Width/2,rect_client.right(),(double)rect_client.height()/2-Small_Rect_Border_Width/2);

    double m_x=0,m_y=0,m_width=(double)rect_client.width()/8,m_height=(double)rect_client.height()/8;
    rect_temp=QRect(m_x,m_y,m_width,m_height);
    drawQuadrant(&painter,rect_temp,db_scale);

    m_x=rect_client.right()-(double)rect_client.width()/8;
    rect_temp=QRect(m_x,m_y,m_width,m_height);
    drawQuadrant(&painter,rect_temp,db_scale);

    m_x=(double)rect_client.width()/2-(double)rect_client.width()/16;
    m_y=(double)rect_client.height()/2-(double)rect_client.height()/16;
    rect_temp=QRect(m_x,m_y,m_width,m_height);
    drawQuadrant(&painter,rect_temp,db_scale);

    m_x=0;
    m_y=rect_client.bottom()-(double)rect_client.height()/8;
    rect_temp=QRect(m_x,m_y,m_width,m_height);
    drawQuadrant(&painter,rect_temp,db_scale);

    m_x=rect_client.right()-(double)rect_client.width()/8;
    m_y=rect_client.bottom()-(double)rect_client.height()/8;
    rect_temp=QRect(m_x,m_y,m_width,m_height);
    drawQuadrant(&painter,rect_temp,db_scale);

    m_x=(double)rect_client.right()/2-(double)rect_client.width()/16;
    m_y=rect_client.top();
    m_height=(double)rect_client.height()/16;
    rect_temp=QRect(m_x,m_y,m_width,m_height);
    painter.fillRect(rect_temp,QColor(255,255,255));

    QString str_temp=" TG18-AFC Pattern ";
    QRect rect_text;
    //rect_text=QRect(QPoint(rect_client.right()/2-luminance_patch_rect_width,0),(QSize(luminance_patch_rect_width*2,luminance_patch_rect_width/2)));
    rect_text.setSize(QSize(m_width,m_height/2));
    rect_text.moveTopLeft(rect_temp.topLeft());
    QFont font("Arial", 17);
    font.setBold(true);
    font.setPixelSize(rect_text.width()/str_temp.length()*2);
    painter.setFont(font);
    painter.setPen(Qt::black);
    painter.drawText(rect_text,Qt::AlignCenter|Qt::TextWordWrap,str_temp);

    font.setPointSize(10);
    str_temp=" Copyright@2019 by BEACON ";
    font.setPixelSize(rect_text.width()/str_temp.length()*2);
    painter.setFont(font);
    rect_text.moveBottomLeft(rect_temp.bottomLeft());
    painter.drawText(rect_text,Qt::AlignCenter|Qt::TextWordWrap,"Version 8.0, 05/23\nCopyright@2019 by BEACON");
}

void TestImage::drawTg18Ang(QPainter &painter,double dot_pitch)
{
    painter.begin(this);
    painter.setPen(QPen(QColor(0,0,0),4,Qt::SolidLine));//设置画笔形式
    painter.setBrush(QBrush(Qt::black
                       ,Qt::SolidPattern));//设置画刷形式
    painter.drawRect(0,0,width(),height());
    painter.setPen(QPen(QColor(255,255,255),Qt::SolidLine));
    painter.drawLine(0,0,0,height());
    painter.drawLine(1,0,1,height());
    painter.drawLine(width()-1,0,width()-1,height());
    painter.drawLine(width()-2,0,width()-2,height());
    painter.end();
}

void TestImage::drawTg18Bn(QPainter &painter, int step)
{
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    //painter.save();
    //线性渐变，渐变开始，和结束点
    QColor background=QColor(0,0,0);
    double db_scale=1;//qMin(height(),width())/1024;
    if(qMin(height(),width())<1024)
           db_scale=qMin(height(),width())/1024.0;
     else
          db_scale=(qMin(height(),width())/1024);

    int center_rect_width=324*db_scale;
    int center_rect_color=(step-1)*15;

    QRect rect_client =rect();
     //画背景
    painter.fillRect(rect_client,background);

    QRect rect_centre(rect_client.right()/2-center_rect_width/2,rect_client.bottom()/2-center_rect_width/2,center_rect_width,center_rect_width);
    QPen current_pen;
    current_pen.setColor(QColor(center_rect_color,center_rect_color,center_rect_color));
    current_pen.setWidth(1);
    painter.setPen(current_pen);
    QBrush current_brush(QColor(center_rect_color,center_rect_color,center_rect_color));
    painter.setBrush(current_brush);
    painter.drawRect(rect_centre);
}

void TestImage::drawTg18Chest(QPainter &painter)
{
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);

    int inamge_width=qMin(height(),width());

    QRect rect_client =rect();
painter.fillRect(rect_client,QColor(0,0,0));
    QPixmap pix;
    pix.load(":/image/TG18-CHEST.2k.bmp");
    painter.drawPixmap(rect_client.right()/2-inamge_width/2,rect_client.bottom()/2-inamge_width/2,inamge_width,inamge_width,pix);
}

void TestImage::drawTg18Knee(QPainter &painter)
{
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);

    int inamge_width=qMin(height(),width());

    QRect rect_client =rect();
painter.fillRect(rect_client,QColor(0,0,0));
    QPixmap pix;
    pix.load(":/image/TG18-KNEE.2k.bmp");
    painter.drawPixmap(rect_client.right()/2-inamge_width/2,rect_client.bottom()/2-inamge_width/2,inamge_width,inamge_width,pix);
}

void TestImage::drawTg18Mam01(QPainter &painter)
{
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);

    int inamge_width=qMin(height(),width());

    QRect rect_client =rect();
    painter.fillRect(rect_client,QColor(0,0,0));
    QPixmap pix;
    pix.load(":/image/TG18-MAM01.2k.bmp");
    painter.drawPixmap(rect_client.right()/2-inamge_width/2,rect_client.bottom()/2-inamge_width/2,inamge_width,inamge_width,pix);
}

void TestImage::drawTg18Mam02(QPainter &painter)
{
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);

    int inamge_width=qMin(height(),width());

    QRect rect_client =rect();
    painter.fillRect(rect_client,QColor(0,0,0));
    QPixmap pix;
    pix.load(":/image/TG18-MAM02.2k.bmp");
    painter.drawPixmap(rect_client.right()/2-inamge_width/2,rect_client.bottom()/2-inamge_width/2,inamge_width,inamge_width,pix);
}
void TestImage::drawTg18Gd(QPainter &painter)
{
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    //painter.save();
    //线性渐变，渐变开始，和结束点
    QColor background=QColor(128,128,128);
    double db_scale=1;//qMin(height(),width())/1024;
    if(qMin(height(),width())<1024)
           db_scale=qMin(height(),width())/1024.0;
     else
          db_scale=(qMin(height(),width())/1024);

    int quadrant_circle_radius=224*db_scale;
    int diagonal_axial_lines_color=64;
    int line_pair_width=10;
    int line_pair_height=2;
    int line_pair_color_white=255;
    int line_pair_color_black=0;

    //画背景
    QRect rect_back=rect();
    painter.fillRect(rect_back,background);

    //画轴线
    QPen current_pen;
    current_pen.setColor(QColor(diagonal_axial_lines_color,diagonal_axial_lines_color,diagonal_axial_lines_color));
    current_pen.setWidth(1);
    painter.setPen(current_pen);


    painter.drawLine(QPoint(rect_back.left()+rect_back.width()/4,rect_back.top()),
                         QPoint(rect_back.left()+rect_back.width()/4,rect_back.bottom()));
    painter.drawLine(QPoint(rect_back.right()-rect_back.width()/4,rect_back.top()),
                         QPoint(rect_back.right()-rect_back.width()/4,rect_back.bottom()));


    painter.drawLine(QPoint(rect_back.left(),rect_back.top()+rect_back.height()/4),
                     QPoint(rect_back.right(),rect_back.top()+rect_back.height()/4));
    painter.drawLine(QPoint(rect_back.left(),rect_back.bottom()-rect_back.height()/4),
                     QPoint(rect_back.right(),rect_back.bottom()-rect_back.height()/4));

    //画对角线
    painter.drawLine(QPoint(rect_back.left()+rect_back.width()/2,rect_back.top()),
                     QPoint(rect_back.left(),rect_back.top()+rect_back.height()/2));
    painter.drawLine(QPoint(rect_back.right(),rect_back.top()),
                     QPoint(rect_back.left(),rect_back.bottom()));
    painter.drawLine(QPoint(rect_back.left()+rect_back.width()/2,rect_back.bottom()),
                     QPoint(rect_back.right(),rect_back.top()+rect_back.height()/2));

    painter.drawLine(QPoint(rect_back.left()+rect_back.width()/2,rect_back.bottom()),
                     QPoint(rect_back.left(),rect_back.top()+rect_back.height()/2));
    painter.drawLine(QPoint(rect_back.right(),rect_back.bottom()),
                     QPoint(rect_back.left(),rect_back.top()));
    painter.drawLine(QPoint(rect_back.left()+rect_back.width()/2,rect_back.top()),
                     QPoint(rect_back.right(),rect_back.top()+rect_back.height()/2));

    //画圆
    painter.drawEllipse(QPoint(rect_back.left()+rect_back.width()/4,rect_back.top()+rect_back.height()/4),quadrant_circle_radius,quadrant_circle_radius);
    painter.drawEllipse(QPoint(rect_back.right()-rect_back.width()/4,rect_back.top()+rect_back.height()/4),quadrant_circle_radius,quadrant_circle_radius);
    painter.drawEllipse(QPoint(rect_back.left()+rect_back.width()/4,rect_back.bottom()-rect_back.height()/4),quadrant_circle_radius,quadrant_circle_radius);
    painter.drawEllipse(QPoint(rect_back.right()-rect_back.width()/4,rect_back.bottom()-rect_back.height()/4),quadrant_circle_radius,quadrant_circle_radius);

    QPen white_pen,black_pen;
    white_pen.setColor(QColor(line_pair_color_white,line_pair_color_white,line_pair_color_white));
    white_pen.setWidth(2);
    black_pen.setColor(QColor(line_pair_color_black,line_pair_color_black,line_pair_color_black));
    black_pen.setWidth(2);

    for(int i=0;i<rect_back.height()/2;i++)
    {
        if(i%2==0)
            painter.setPen(black_pen);
        else
            painter.setPen(white_pen);

        painter.drawLine(QPoint(rect_back.left(),rect_back.top()+line_pair_height*i),
                         QPoint(rect_back.left()+line_pair_width,rect_back.top()+line_pair_height*i));
        painter.drawLine(QPoint(rect_back.right(),rect_back.top()+line_pair_height*i),
                         QPoint(rect_back.right()-line_pair_width,rect_back.top()+line_pair_height*i));
    }

    for(int i=0;i<rect_back.width()/2;i++)
    {
        if(i%2==0)
            painter.setPen(black_pen);
        else
            painter.setPen(white_pen);

        painter.drawLine(QPoint(rect_back.left()+line_pair_height*i,rect_back.top()),
                         QPoint(rect_back.left()+line_pair_height*i,rect_back.top()+line_pair_width));
        painter.drawLine(QPoint(rect_back.left()+line_pair_height*i,rect_back.bottom()),
                         QPoint(rect_back.left()+line_pair_height*i,rect_back.bottom()-line_pair_width));
    }
}

void TestImage::drawTg18Gv(QPainter &painter, double dot_pitch)
{
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    //painter.save();
    //线性渐变，渐变开始，和结束点
    QColor background=QColor(0,0,0);
    double db_scale=1;//qMin(height(),width())/1024;
    if(qMin(height(),width())<1024)
           db_scale=qMin(height(),width())/1024.0;
     else
          db_scale=(qMin(height(),width())/1024);

    int white_annulus_color=255;
    int inner_diametra=1*10/dot_pitch;
    int outer_diametra=20*10/dot_pitch;
    int low_contrast_disk_color_begin=2;
    int low_contrast_disk_color_step=2;
    int low_contrast_disk_angle=18;
    int low_contrast_disk_step=72;
    QRect rect_client =rect();
     //画背景
    painter.fillRect(rect_client,background);

    painter.save();
    painter.setPen(QColor(white_annulus_color,white_annulus_color,white_annulus_color));
    painter.setBrush(QColor(white_annulus_color,white_annulus_color,white_annulus_color));

    QPainterPath bigCircle;
    bigCircle.addEllipse(rect_client.right()/2-outer_diametra/2,rect_client.bottom()/2-outer_diametra/2,outer_diametra,outer_diametra);

    QPainterPath smallCircle;
    smallCircle.addEllipse(rect_client.right()/2-inner_diametra/2,rect_client.bottom()/2-inner_diametra/2, inner_diametra, inner_diametra);

    QPainterPath path = bigCircle - smallCircle;
    painter.drawPath(path);
    painter.restore();

    //
    double disk_center_x,disk_center_y,smallCircle_x,smallCircle_y;
//    painter.setPen(QColor(255,0,0));
//    painter.setBrush(QColor(255,0,0));
    for(int i=0;i<5;i++)
    {
        painter.setPen(QColor(low_contrast_disk_color_begin+low_contrast_disk_color_step*i,low_contrast_disk_color_begin+low_contrast_disk_color_step*i,
                              low_contrast_disk_color_begin+low_contrast_disk_color_step*i));
        painter.setBrush(QColor(low_contrast_disk_color_begin+low_contrast_disk_color_step*i,low_contrast_disk_color_begin+low_contrast_disk_color_step*i,
                                low_contrast_disk_color_begin+low_contrast_disk_color_step*i));
        smallCircle_x=rect_client.right()/2+inner_diametra/2*cos((low_contrast_disk_angle+low_contrast_disk_step*i)*3.14/180);
        smallCircle_y=rect_client.bottom()/2+inner_diametra/2*sin((low_contrast_disk_angle+low_contrast_disk_step*i)*3.14/180);
        disk_center_x=smallCircle_x-inner_diametra/8*cos((low_contrast_disk_angle+low_contrast_disk_step*i)*3.14/180);
        disk_center_y=smallCircle_y-inner_diametra/8*sin((low_contrast_disk_angle+low_contrast_disk_step*i)*3.14/180);
        painter.drawEllipse(QPoint(disk_center_x+1,disk_center_y+1),inner_diametra/8,inner_diametra/8);
    }
}

void TestImage::drawTg18Gvn(QPainter &painter, double dot_pitch)
{
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    //painter.save();
    //线性渐变，渐变开始，和结束点
    QColor background=QColor(0,0,0);
    double db_scale=1;//qMin(height(),width())/1024;
    if(qMin(height(),width())<1024)
           db_scale=qMin(height(),width())/1024.0;
     else
          db_scale=(qMin(height(),width())/1024);

    int white_annulus_color=255;
    int inner_diametra=1*10/dot_pitch;
    int outer_diametra=20*10/dot_pitch;
    int low_contrast_disk_color_begin=2;
    int low_contrast_disk_color_step=2;
    int low_contrast_disk_angle=18;
    int low_contrast_disk_step=72;
    QRect rect_client =rect();
     //画背景
    painter.fillRect(rect_client,background);

    painter.save();
    painter.setPen(QColor(0,0,0));
    painter.setBrush(QColor(0,0,0));

   // QPainterPath bigCircle;
   // bigCircle.addEllipse(rect_client.right()/2-outer_diametra/2,rect_client.bottom()/2-outer_diametra/2,outer_diametra,outer_diametra);

    QPainterPath smallCircle;
    smallCircle.addEllipse(rect_client.right()/2-inner_diametra/2,rect_client.bottom()/2-inner_diametra/2, inner_diametra, inner_diametra);

    QPainterPath path =smallCircle;
    painter.drawPath(path);
    painter.restore();

    double disk_center_x,disk_center_y,smallCircle_x,smallCircle_y;
    for(int i=0;i<5;i++)
    {
        painter.setPen(QColor(low_contrast_disk_color_begin+low_contrast_disk_color_step*i,low_contrast_disk_color_begin+low_contrast_disk_color_step*i,
                              low_contrast_disk_color_begin+low_contrast_disk_color_step*i));
        painter.setBrush(QColor(low_contrast_disk_color_begin+low_contrast_disk_color_step*i,low_contrast_disk_color_begin+low_contrast_disk_color_step*i,
                                low_contrast_disk_color_begin+low_contrast_disk_color_step*i));
        smallCircle_x=rect_client.right()/2+inner_diametra/2*cos((low_contrast_disk_angle+low_contrast_disk_step*i)*3.14/180);
        smallCircle_y=rect_client.bottom()/2+inner_diametra/2*sin((low_contrast_disk_angle+low_contrast_disk_step*i)*3.14/180);
        disk_center_x=smallCircle_x-inner_diametra/8*cos((low_contrast_disk_angle+low_contrast_disk_step*i)*3.14/180);
        disk_center_y=smallCircle_y-inner_diametra/8*sin((low_contrast_disk_angle+low_contrast_disk_step*i)*3.14/180);
        painter.drawEllipse(QPoint(disk_center_x+1,disk_center_y+1),inner_diametra/8,inner_diametra/8);
    }
}
void TestImage::setDisplayPhysicalProperty(DisplayName_Data displayData)
{
    m_nOperatorDisplay=displayData.DisplayID-1;
    m_dbDotPitch=displayData.PixelPitch;
    if(fabs(m_dbDotPitch)<0.000001)
        m_dbDotPitch=0.000001;
    m_blNinePoint=(displayData.DiagonalSize>=23.0);
    m_autoHideWidget.setPointNumber(m_blNinePoint);
}
