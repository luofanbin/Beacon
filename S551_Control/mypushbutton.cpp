#include"mypushbutton.h"
#include<QDebug>

mypushButton::mypushButton(QWidget *parent):
    QPushButton(parent)
{
    connect(this,SIGNAL(clicked()),this,SLOT(ClickedBtn()));
    //this->get_data={0};
   this->setStyleSheet("QPushButton:focus{padding:-3;}");
    this->setAutoFillBackground(true);
//    connect(this,SIGNAL(pressed()),this,SLOT(pressed_dl()));
    this->setFocusPolicy(Qt::NoFocus);
    this->setStyleSheet("background:transparent;");
    this->setFlat(true);
}

void mypushButton::paintEvent(QPaintEvent *event)
{
    if(n==100)
    {
        return;
    }
    QPushButton::paintEvent(event);
    QPainter painter(this);
    QPen pen,pen1;  //设置画笔，颜色、宽度
    QString text;
    pen.setColor(Qt::white);
    pen.setWidth(2);
    pen1.setColor(Qt::black);
    pen1.setWidth(2);
    painter.setPen(pen);
    QString str;
    if(ok)
    {
        str=QString(":/image/bottombg3.png");
        //this->setStyleSheet("background-image:url(:/image/bottombg3.png)");
    }else
    {
        str=QString(":/image/bgnew3.png");
        //this->setStyleSheet("background-image:url(:/image/bgnew3.png)");
    }

    QPixmap pixmap11(str);
    QPixmap pixmap = pixmap11.scaled(188, 175);
    painter.drawPixmap(0, 0, pixmap);
    //QPainter llpainter(&pixmap);
    //this->setStyleSheet(tr("background-color: rgb(116,218,246)"));
   // if(ok)
    //{
        //this->setStyleSheet(tr("background-color: rgb(252,239,183)"));
        //painter.setPen(QPen(QColor(252,239,183),1,Qt::SolidLine));//设置画笔形式
        //painter.setBrush(QBrush(QColor(252,239,183),Qt::SolidPattern));//设置画刷形式
   // }else
    //{
        //this->setStyleSheet(tr("background-color: rgb(87,225,200)"));
       // painter.setPen(QPen(QColor(87,225,200),1,Qt::SolidLine));//设置画笔形式
        //painter.setBrush(QBrush(QColor(87,225,200),Qt::SolidPattern));//设置画刷形式
    //}
   // painter.drawRect(5,5,this->width()-10,this->height()-59);
//    painter.setPen(QPen(QColor(116,218,246),1,Qt::SolidLine));//设置画笔形式
//    painter.setBrush(QBrush(QColor(116,218,246),Qt::SolidPattern));//设置画刷形式
//    painter.drawRect(0,this->height()/8*7,this->width(),this->height()/8);

    painter.setPen(pen1);


    for(int i=0;i<rectnum;i++)
    {
        x=(get_data.Windows[i].WinPosX)*(this->width()-10)/3840+5;
        y=(get_data.Windows[i].WinPosY)*(this->height()-59-15)/2160+10;
        w=(get_data.Windows[i].WinSizeX)*(this->width()-10)/3840;
        h=(get_data.Windows[i].WinSizeY)*(this->height()-59-15)/2160;
    /*
        switch (get_data.Windows[i].SignalID) {
        case 0:
            painter.setBrush(QBrush(QColor(230,230,230),Qt::SolidPattern));//设置画刷形式
            break;
        case 1:
            painter.setBrush(QBrush(QColor(212,212,212),Qt::SolidPattern));//设置画刷形式
            break;
        case 2:
            painter.setBrush(QBrush(QColor(195,195,195),Qt::SolidPattern));//设置画刷形式
            break;
        case 3:
            painter.setBrush(QBrush(QColor(185,185,185),Qt::SolidPattern));//设置画刷形式
            break;
        case 4:
            painter.setBrush(QBrush(QColor(168,168,168),Qt::SolidPattern));//设置画刷形式
            break;
        case 5:
            painter.setBrush(QBrush(QColor(160,160,160),Qt::SolidPattern));//设置画刷形式
            break;
        case 6:
            painter.setBrush(QBrush(QColor(153,153,153),Qt::SolidPattern));//设置画刷形式
            break;
        case 7:
            painter.setBrush(QBrush(QColor(136,136,136),Qt::SolidPattern));//设置画刷形式
            break;
        case 8:
            painter.setBrush(QBrush(QColor(127,127,127),Qt::SolidPattern));//设置画刷形式
            break;
        case 9:
            painter.setBrush(QBrush(QColor(117,117,117),Qt::SolidPattern));//设置画刷形式
            break;
        case 10:
            painter.setBrush(QBrush(QColor(109,109,109),Qt::SolidPattern));//设置画刷形式
            break;
        case 11:
            painter.setBrush(QBrush(QColor(91,91,91),Qt::SolidPattern));//设置画刷形式
            break;
        default:
            break;
        }
        */
        if(get_data.Windows[i].SignalID<12)
        {
            painter.drawRect(x,y,w,h);
        }
    }

        painter.setPen(pen1);
        QFont font;
        font.setPixelSize(24);
        painter.setFont(font);
        std::string str_1=(char *)get_data.LayoutName;

        //QString s1 =QString::fromUtf8((char *)get_data.LayoutName);//这是在qlabel中显示中文的办法
        text=QString::fromStdString(str_1);
        //text=QString::fromUtf8((char *)get_data.LayoutName);
        painter.drawText(this->width()/4,this->height()-45,this->width()/2,30,4,text);

}

void mypushButton::ClickedBtn()
{
    // 触发子窗口的信号给父窗口接收。
    emit emit_btn_id(this->lay_id);
}

void mypushButton::pressed_dl()
{
   //this->setStyleSheet(tr("background-image: url(:/大按键灰色-深-01.png);"));
}



