#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QPainter>
#include<QImage>
#include<QDebug>
#include<QRect>
#include<QDesktopWidget>
#include<QPixmap>
#include<QPushButton>
#include<QToolButton>
#include<QTime>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#pragma execution_character_set("utf-8")
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QDesktopWidget* desktopWidget = QApplication::desktop();
    //获取可用桌面大小
    QRect deskRect = desktopWidget->availableGeometry();
    //获取设备屏幕大小
    QRect screenRect = desktopWidget->screenGeometry();
    //this->setStyleSheet("background-image:url(:/image/style1.jpg)");
    g_nActScreenX = screenRect.width();
    g_nActScreenY = screenRect.height();
    ui->label->setFrameStyle(QFrame::NoFrame);
    ui->label->setGeometry(0,0,220,45);
    QPalette pe;
    pe.setColor(QPalette::WindowText,Qt::white);

    QString s1 =QString::fromUtf8(" DSA 手术显示控制终端");//这是在qlabel中显示中文的办法
    ui->label->setText(s1);
    ui->label->setPalette(pe);


    ui->label_2->setGeometry(g_nActScreenX-45,17,30,18);
    ui->label_2->setStyleSheet(tr("background-image: url(:/image/通信2.png);"));

    ui->label_3->setFrameStyle(QFrame::NoFrame);
    ui->label_3->setGeometry(g_nActScreenX-215,g_nActScreenY-29,215,20);
    s1 =QString::fromUtf8("@巨烽显示科技提供技术支持 400-1818-992");
    ui->label_3->setText(s1);
    ui->label_3->setPalette(pe);
    ui->label_3->setFocusPolicy(Qt::NoFocus);
    ui->label_3->setStyleSheet("background:transparent;");
    //ui->label_3->setFlat(true);

    ui->label_4->setGeometry(g_nActScreenX-295,g_nActScreenY-47,80,80);
    ui->label_4->setStyleSheet(tr("background-image: url(:/image/LOGO4.png);"));
    //ui->label_4->setStyleSheet(tr("background-color: rgb(0,0,0)"));;
//    ui->pushButton->setStyleSheet(tr("background-color: rgb(116,218,170)"));
//    ui->pushButton->setEnabled(false);
    ui->pushButton_3->setGeometry(g_nActScreenX-36,g_nActScreenY-70,31,31);
    ui->pushButton_3->setStyleSheet(tr("background-color: rgb(116,218,246)"));
    //ui->pushButton_3->setStyleSheet(tr("background-image: url(:/右翻页-浅-01.png);border:none;"));
    //ui->pushButton_3->setIcon(QIcon(":/右翻页-01-02.png"));
    //ui->pushButton_3->setIconSize(QSize(60, 60));
    ui->pushButton_3->setHidden(true);
    //ui->pushButton_3->setFocusPolicy(Qt::NoFocus);
    //ui->pushButton_3->setStyleSheet("background:transparent;");
    //ui->pushButton_3->setStyleSheet(tr("QPushButton{background: transparent;}"));
    //ui->pushButton_3->setFlat(true);
    ui->pushButton_2->setGeometry(5,g_nActScreenY-70,31,31);
    //ui->pushButton_2->setIcon(QIcon(":/左翻页-01_2.png"));
    //ui->pushButton_2->setIconSize(QSize(60, 60));
    ui->pushButton_2->setStyleSheet(tr("background-color: rgb(116,218,246)"));
    ui->pushButton_2->setHidden(true);
    //ui->pushButton_2->setStyleSheet(tr("background-image: url(:/左翻页-浅-01.png);border:none;"));
    //ui->pushButton_2->setStyleSheet(tr("QPushButton{background: transparent;}"));
    //ui->pushButton_2->setFocusPolicy(Qt::NoFocus);
    //ui->pushButton_2->setStyleSheet("background:transparent;");
    //ui->pushButton_2->setFlat(true);
    paint=new QPainter;
    push1=new mypushButton(this);
    push1->setGeometry(10,g_nActScreenY/8+40-g_nActScreenY/8+g_nActScreenY/15,(g_nActScreenX-50)/4,g_nActScreenY/4*3/2-50);
    push1->setHidden(true);
    push2=new mypushButton(this);
    push2->setGeometry((g_nActScreenX-50)/4+20,g_nActScreenY/8+40-g_nActScreenY/8+g_nActScreenY/15,(g_nActScreenX-50)/4,g_nActScreenY/4*3/2-50);
    push2->setHidden(true);
    push3=new mypushButton(this);
    push3->setGeometry(2*(g_nActScreenX-50)/4+30,g_nActScreenY/8+40-g_nActScreenY/8+g_nActScreenY/15,(g_nActScreenX-50)/4,g_nActScreenY/4*3/2-50);
    push3->setHidden(true);
    push4=new mypushButton(this);
    push4->setGeometry(3*(g_nActScreenX-50)/4+40,g_nActScreenY/8+40-g_nActScreenY/8+g_nActScreenY/15,(g_nActScreenX-50)/4,g_nActScreenY/4*3/2-50);
    push4->setHidden(true);
    push5=new mypushButton(this);
    push5->setGeometry(10,g_nActScreenY-g_nActScreenY/8-g_nActScreenY/4*3/2+10,(g_nActScreenX-50)/4,g_nActScreenY/4*3/2-50);
    push5->setHidden(true);
    push6=new mypushButton(this);
    push6->setGeometry((g_nActScreenX-50)/4+20,g_nActScreenY-g_nActScreenY/8-g_nActScreenY/4*3/2+10,(g_nActScreenX-50)/4,g_nActScreenY/4*3/2-50);
    push6->setHidden(true);
    push7=new mypushButton(this);
    push7->setGeometry(2*(g_nActScreenX-50)/4+30,g_nActScreenY-g_nActScreenY/8-g_nActScreenY/4*3/2+10,(g_nActScreenX-50)/4,g_nActScreenY/4*3/2-50);
    push7->setHidden(true);
    push8=new mypushButton(this);
    push8->setGeometry(3*(g_nActScreenX-50)/4+40,g_nActScreenY-g_nActScreenY/8-g_nActScreenY/4*3/2+10,(g_nActScreenX-50)/4,g_nActScreenY/4*3/2-50);
    push8->setHidden(true);

    push9=new mypushButton(this);
    push9->setGeometry(10,g_nActScreenY/8+40-g_nActScreenY/8+g_nActScreenY/15,(g_nActScreenX-50)/4,g_nActScreenY/4*3/2-50);
    push9->setHidden(true);
    push10=new mypushButton(this);
    push10->setGeometry((g_nActScreenX-50)/4+20,g_nActScreenY/8+40-g_nActScreenY/8+g_nActScreenY/15,(g_nActScreenX-50)/4,g_nActScreenY/4*3/2-50);
    push10->setHidden(true);
    push11=new mypushButton(this);
    push11->setGeometry(2*(g_nActScreenX-50)/4+30,g_nActScreenY/8+40-g_nActScreenY/8+g_nActScreenY/15,(g_nActScreenX-50)/4,g_nActScreenY/4*3/2-50);
    push11->setHidden(true);
    push12=new mypushButton(this);
    push12->setGeometry(3*(g_nActScreenX-50)/4+40,g_nActScreenY/8+40-g_nActScreenY/8+g_nActScreenY/15,(g_nActScreenX-50)/4,g_nActScreenY/4*3/2-50);
    push12->setHidden(true);
    push13=new mypushButton(this);
    push13->setGeometry(10,g_nActScreenY-g_nActScreenY/8-g_nActScreenY/4*3/2+10,(g_nActScreenX-50)/4,g_nActScreenY/4*3/2-50);
    push13->setHidden(true);
    push14=new mypushButton(this);
    push14->setGeometry((g_nActScreenX-50)/4+20,g_nActScreenY-g_nActScreenY/8-g_nActScreenY/4*3/2+10,(g_nActScreenX-50)/4,g_nActScreenY/4*3/2-50);
    push14->setHidden(true);
    push15=new mypushButton(this);
    push15->setGeometry(2*(g_nActScreenX-50)/4+30,g_nActScreenY-g_nActScreenY/8-g_nActScreenY/4*3/2+10,(g_nActScreenX-50)/4,g_nActScreenY/4*3/2-50);
    push15->setHidden(true);
    push16=new mypushButton(this);
    push16->setGeometry(3*(g_nActScreenX-50)/4+40,g_nActScreenY-g_nActScreenY/8-g_nActScreenY/4*3/2+10,(g_nActScreenX-50)/4,g_nActScreenY/4*3/2-50);
    push16->setHidden(true);

    push17=new mypushButton(this);
    push17->setGeometry(10,g_nActScreenY/8+40-g_nActScreenY/8+g_nActScreenY/15,(g_nActScreenX-50)/4,g_nActScreenY/4*3/2-50);
    push17->setHidden(true);
    push18=new mypushButton(this);
    push18->setGeometry((g_nActScreenX-50)/4+20,g_nActScreenY/8+40-g_nActScreenY/8+g_nActScreenY/15,(g_nActScreenX-50)/4,g_nActScreenY/4*3/2-50);
    push18->setHidden(true);
    push19=new mypushButton(this);
    push19->setGeometry(2*(g_nActScreenX-50)/4+30,g_nActScreenY/8+40-g_nActScreenY/8+g_nActScreenY/15,(g_nActScreenX-50)/4,g_nActScreenY/4*3/2-50);
    push19->setHidden(true);
    push20=new mypushButton(this);
    push20->setGeometry(3*(g_nActScreenX-50)/4+40,g_nActScreenY/8+40-g_nActScreenY/8+g_nActScreenY/15,(g_nActScreenX-50)/4,g_nActScreenY/4*3/2-50);
    push20->setHidden(true);
    push21=new mypushButton(this);
    push21->setGeometry(10,g_nActScreenY-g_nActScreenY/8-g_nActScreenY/4*3/2+10,(g_nActScreenX-50)/4,g_nActScreenY/4*3/2-50);
    push21->setHidden(true);
    push22=new mypushButton(this);
    push22->setGeometry((g_nActScreenX-50)/4+20,g_nActScreenY-g_nActScreenY/8-g_nActScreenY/4*3/2+10,(g_nActScreenX-50)/4,g_nActScreenY/4*3/2-50);
    push22->setHidden(true);
    push23=new mypushButton(this);
    push23->setGeometry(2*(g_nActScreenX-50)/4+30,g_nActScreenY-g_nActScreenY/8-g_nActScreenY/4*3/2+10,(g_nActScreenX-50)/4,g_nActScreenY/4*3/2-50);
    push23->setHidden(true);
    push24=new mypushButton(this);
    push24->setGeometry(3*(g_nActScreenX-50)/4+40,g_nActScreenY-g_nActScreenY/8-g_nActScreenY/4*3/2+10,(g_nActScreenX-50)/4,g_nActScreenY/4*3/2-50);
    push24->setHidden(true);

    push25=new mypushButton(this);
    push25->setGeometry(10,g_nActScreenY/8+40-g_nActScreenY/8+g_nActScreenY/15,(g_nActScreenX-50)/4,g_nActScreenY/4*3/2-50);
    push25->setHidden(true);
    push26=new mypushButton(this);
    push26->setGeometry((g_nActScreenX-50)/4+20,g_nActScreenY/8+40-g_nActScreenY/8+g_nActScreenY/15,(g_nActScreenX-50)/4,g_nActScreenY/4*3/2-50);
    push26->setHidden(true);
    push27=new mypushButton(this);
    push27->setGeometry(2*(g_nActScreenX-50)/4+30,g_nActScreenY/8+40-g_nActScreenY/8+g_nActScreenY/15,(g_nActScreenX-50)/4,g_nActScreenY/4*3/2-50);
    push27->setHidden(true);
    push28=new mypushButton(this);
    push28->setGeometry(3*(g_nActScreenX-50)/4+40,g_nActScreenY/8+40-g_nActScreenY/8+g_nActScreenY/15,(g_nActScreenX-50)/4,g_nActScreenY/4*3/2-50);
    push28->setHidden(true);
    push29=new mypushButton(this);
    push29->setGeometry(10,g_nActScreenY-g_nActScreenY/8-g_nActScreenY/4*3/2+10,(g_nActScreenX-50)/4,g_nActScreenY/4*3/2-50);
    push29->setHidden(true);
    push30=new mypushButton(this);
    push30->setGeometry((g_nActScreenX-50)/4+20,g_nActScreenY-g_nActScreenY/8-g_nActScreenY/4*3/2+10,(g_nActScreenX-50)/4,g_nActScreenY/4*3/2-50);
    push30->setHidden(true);
    push31=new mypushButton(this);
    push31->setGeometry(2*(g_nActScreenX-50)/4+30,g_nActScreenY-g_nActScreenY/8-g_nActScreenY/4*3/2+10,(g_nActScreenX-50)/4,g_nActScreenY/4*3/2-50);
    push31->setHidden(true);
    push32=new mypushButton(this);
    push32->setGeometry(3*(g_nActScreenX-50)/4+40,g_nActScreenY-g_nActScreenY/8-g_nActScreenY/4*3/2+10,(g_nActScreenX-50)/4,g_nActScreenY/4*3/2-50);
    push32->setHidden(true);

    connect(push1,SIGNAL(emit_btn_id(int)),this,SLOT(push1_function(int)));
    connect(push2,SIGNAL(emit_btn_id(int)),this,SLOT(push1_function(int)));
    connect(push3,SIGNAL(emit_btn_id(int)),this,SLOT(push1_function(int)));
    connect(push4,SIGNAL(emit_btn_id(int)),this,SLOT(push1_function(int)));
    connect(push5,SIGNAL(emit_btn_id(int)),this,SLOT(push1_function(int)));
    connect(push6,SIGNAL(emit_btn_id(int)),this,SLOT(push1_function(int)));
    connect(push7,SIGNAL(emit_btn_id(int)),this,SLOT(push1_function(int)));
    connect(push8,SIGNAL(emit_btn_id(int)),this,SLOT(push1_function(int)));

    connect(push9,SIGNAL(emit_btn_id(int)),this,SLOT(push1_function(int)));
    connect(push10,SIGNAL(emit_btn_id(int)),this,SLOT(push1_function(int)));
    connect(push11,SIGNAL(emit_btn_id(int)),this,SLOT(push1_function(int)));
    connect(push12,SIGNAL(emit_btn_id(int)),this,SLOT(push1_function(int)));
    connect(push13,SIGNAL(emit_btn_id(int)),this,SLOT(push1_function(int)));
    connect(push14,SIGNAL(emit_btn_id(int)),this,SLOT(push1_function(int)));
    connect(push15,SIGNAL(emit_btn_id(int)),this,SLOT(push1_function(int)));
    connect(push16,SIGNAL(emit_btn_id(int)),this,SLOT(push1_function(int)));

    connect(push17,SIGNAL(emit_btn_id(int)),this,SLOT(push1_function(int)));
    connect(push18,SIGNAL(emit_btn_id(int)),this,SLOT(push1_function(int)));
    connect(push19,SIGNAL(emit_btn_id(int)),this,SLOT(push1_function(int)));
    connect(push20,SIGNAL(emit_btn_id(int)),this,SLOT(push1_function(int)));
    connect(push21,SIGNAL(emit_btn_id(int)),this,SLOT(push1_function(int)));
    connect(push22,SIGNAL(emit_btn_id(int)),this,SLOT(push1_function(int)));
    connect(push23,SIGNAL(emit_btn_id(int)),this,SLOT(push1_function(int)));
    connect(push24,SIGNAL(emit_btn_id(int)),this,SLOT(push1_function(int)));

    connect(push25,SIGNAL(emit_btn_id(int)),this,SLOT(push1_function(int)));
    connect(push26,SIGNAL(emit_btn_id(int)),this,SLOT(push1_function(int)));
    connect(push27,SIGNAL(emit_btn_id(int)),this,SLOT(push1_function(int)));
    connect(push28,SIGNAL(emit_btn_id(int)),this,SLOT(push1_function(int)));
    connect(push29,SIGNAL(emit_btn_id(int)),this,SLOT(push1_function(int)));
    connect(push30,SIGNAL(emit_btn_id(int)),this,SLOT(push1_function(int)));
    connect(push31,SIGNAL(emit_btn_id(int)),this,SLOT(push1_function(int)));
    connect(push32,SIGNAL(emit_btn_id(int)),this,SLOT(push1_function(int)));


    mypushButton_list<<push1<<push2<<push3<<push4<<push5<<push6<<push7<<push8
                         <<push9<<push10<<push11<<push12<<push13<<push14<<push15<<push16
                         <<push17<<push18<<push19<<push20<<push21<<push22<<push23<<push24
                         <<push25<<push26<<push27<<push28<<push29<<push30<<push31<<push32;

    serial = new QSerialPort(this);
    tem_buf.clear();
    initPort();
    prv_time=QTime::currentTime();
    //连接信号槽
    connect(serial, SIGNAL(readyRead()),this, SLOT(Read_Data()));
    connect(this,SIGNAL(isok(bool)),this,SLOT(SendCmd(bool)));
    //ui->pushButton_2->setFlat(true);
    ui->pushButton_2->setFocusPolicy(Qt::NoFocus);
    //ui->pushButton_2->setStyleSheet("background:transparent;");
   //ui->pushButton_2->setStyleSheet("QPushButton{border-radius:5px;border-width:0px;}");
    //ui->pushButton_3->setFlat(true);
    ui->pushButton_3->setFocusPolicy(Qt::NoFocus);
    //ui->pushButton_3->setStyleSheet("QPushButton{border-radius:5px;border-width:0px;}");

    //ui->pushButton_3->setStyleSheet("background:tra//nsparent;");
}

MainWindow::~MainWindow()
{
    //delete serial;
    delete ui;
}

void MainWindow::initPort()
{
    //serial_1->setPortName("ttymxc1");
    serial->setPortName("ttymxc1");
    //qDebug()<<ui->comboBox->currentText();
    //以读写方式打开串口
    if(serial->open(QIODevice::ReadWrite))
    {
        //设置波特率
        serial->setBaudRate(QSerialPort::Baud115200);
        //设置数据位
        serial->setDataBits(QSerialPort::Data8);
        //设置校验位
        serial->setParity(QSerialPort::NoParity);
        //设置流控制
        serial->setFlowControl(QSerialPort::NoFlowControl);
        //设置停止位
        serial->setStopBits(QSerialPort::OneStop);
        serial->setDataTerminalReady(true);

        qDebug()<<"Open serial OK!";
        //每秒读一次
        timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()), this, SLOT(SendConnectCmd()));
        timer->start(2000);
    }
    qint64 n;
    QByteArray buf_1;
    buf_1.append(0x07);
    buf_1.append(0xc2);
    buf_1.append(0xc2);
    buf_1.append(0x79);
    buf_1.append(0x01);
    buf_1.append(0xff);
    buf_1.append(0xfc);
    n=serial->write(buf_1);
    cur_time=QTime::currentTime();
    //qDebug()<<n<<buf_1.data();

}

void MainWindow::sleep(int n)
{
    QTime time=QTime::currentTime().addMSecs(n);
    while(QTime::currentTime()<time)
    {
        QCoreApplication::processEvents(QEventLoop::AllEvents,100);
    }
}

void MainWindow::paintEvent(QPaintEvent *e)
{


    paint->begin(this);
    paint->setPen(QPen(QColor(9,238,238),2,Qt::SolidLine));//设置画笔形式
    paint->setBrush(QBrush(QColor(9,238,238)
                       ,Qt::SolidPattern));//设置画刷形式
    paint->drawRect(0,0,g_nActScreenX,g_nActScreenY/12);
    paint->drawRect(0,g_nActScreenY/19*18,g_nActScreenX,g_nActScreenY/15);
    paint->setPen(QPen(QColor(31,184,216),2,Qt::SolidLine));//设置画笔形式
    paint->setBrush(QBrush(QColor(31,184,216)
                       ,Qt::SolidPattern));//设置画刷形式
    paint->drawRect(0,g_nActScreenY/15,g_nActScreenX,g_nActScreenY-g_nActScreenY/12-g_nActScreenY/18+10);
    x_width=g_nActScreenX-300;
    y_height=g_nActScreenY-g_nActScreenY/6-40-22;
    paint->end();

    //paint->drawPixmap(0,0,width(),height(),QPixmap(":/image/style1.jpg"));
}

void MainWindow::push1_function(int n)
{
    if(prv_time.addSecs(1)>QTime::currentTime())
    {
        return;
    }
    tem_time=QTime::currentTime();
    prv_time=QTime::currentTime();
    if(n==cur_id)
    {
        return;
    }
    tem_buf.clear();
    int num;
    QByteArray buf_1;
    buf_1.append(0x07);
    buf_1.append(0xc2);
    buf_1.append(0xc2);
    buf_1.append(0x7d);
    buf_1.append(0x01);
    buf_1.append(n & 0xff);
    buf_1.append(0xf7-(n&0xff));
    num=serial->write(buf_1);
    //qDebug()<<num<<buf_1.toHex();
}

void MainWindow::Read_Data()
{
    int num;
    QByteArray buf_1;
    QByteArray buf_2;
    buf_1 = serial->readAll();
    //qDebug()<<"buf_2:"<<buf_1[0];
    if(ok_3==1)
    {
        tem_buf.append(buf_1);
        if(tem_buf.length()>=4)
        {
            ok_3=0;
            ok_4=0;
            buf_1.clear();
            buf_1.append(tem_buf);
            tem_buf.clear();
        }
    }
    char data[181]={0};
    memcpy(data,buf_1.data(),buf_1.length());
    qDebug()<<"buf_1:"<<buf_1.toHex();
    if((int)data[3]==0x61 && (int)data[0]==0x09)
    {
        if(buf_1.length()==0x09)
        {
            ok_2=ok_1;
            flag=0;
            return;
        }else
        {
            flag=1;
            buf.append(buf_1);
        }
    }
    else if((int)data[3]==0x79 && (int)data[0]==0x09)
    {
        if(ui->label_2->styleSheet()==tr("background-image: url(:/image/通信2.png);"))
        {
            ui->label_2->setStyleSheet(tr("background-image: url(:/image/通信1.png)"));
        }
        if(buf_1.length()==0x09)
        {
            if(ok_5==1)
            {
                ok_2=ok_1;
                ok_5=0;
            }
            data_handle(data);
            flag_1=0;
            return;
        }else
        {
            flag_1=1;
            buf.append(buf_1);
        }

    }else if((int)data[3]==0x7d)
    {
        if(buf_1.length()==0x07)
        {
            if((int)data[5]==0x03)
            {
                buf_2.append(0x07);
                buf_2.append(0xc2);
                buf_2.append(0xc2);
                buf_2.append(0x79);
                buf_2.append(0x01);
                buf_2.append(0xff);
                buf_2.append(0xfc);
                serial->write(buf_2);
            }
            return;
        }else
        {
            flag_2=1;
            buf.append(buf_1);
        }
    }else if((int)data[3]==0x79 && (int)data[0]==0xb5)
    {
        if(buf_1.length()==0xb5)
        {
            flag_3=0;
            data_handle_new(data);
            emit isok(true);
            return;
        }else
        {
            flag_3=1;
            buf.append(buf_1);
        }
    }else{
        if(flag_3==1)
        {
            buf_1.length();
            buf.append(buf_1);
            if(buf.length()==0xb5)
            {
                flag_3=0;
                memset(data,0,0xb5);
                memcpy(data,buf.data(),buf.length());
                buf.clear();
                data_handle_new(data);
                emit isok(true);
            }
            return;
        }else if(flag==1)
        {
            buf.append(buf_1);
            if(buf.length()==0x09)
            {
                num=buf.length();
                flag=0;
                memset(data,0,0x09);
                memcpy(data,buf.data(),buf.length());
                buf.clear();
                ok_2=ok_1;
            }
            return;
        }else if(flag_1==1)
        {
            buf.append(buf_1);
            if(ui->label_2->styleSheet()==tr("background-image: url(:/image/通信2.png);"))
            {
                ui->label_2->setStyleSheet(tr("background-image: url(:/image/通信1.png)"));
            }
            if(buf.length()==0x09)
            {
                if(ok_5==1)
                {
                    ok_2=ok_1;
                    ok_5=0;
                }
                num=buf.length();
                memset(data,0,0x09);
                memcpy(data,buf.data(),buf.length());
                buf.clear();
                data_handle(data);
                flag_1=0;
            }
            return;
        }else if(flag_2==1)
        {
            buf.append(buf_1);
            if(buf.length()==0x07)
            {
                num=buf.length();
                memset(data,0,0x07);
                memcpy(data,buf.data(),buf.length());
                buf.clear();
                flag_2=0;
                if((int)data[5]==0x03)
                {
                    buf_2.append(0x07);
                    buf_2.append(0xc2);
                    buf_2.append(0xc2);
                    buf_2.append(0x79);
                    buf_2.append(0x01);
                    buf_2.append(0xff);
                    buf_2.append(0xfc);
                    serial->write(buf_2);
                }
            }
            return;
        }
        if((buf_1.length()<4) && (ok_4==0))
        {
            if(tem_buf.length()>0)
            {
                return;
            }
            //qDebug()<<"tem_bu";
            tem_buf.append(buf_1);
            ok_3=1;
            ok_4=1;
        }

    }
}

void MainWindow::data_handle(char *data)
{
            laynum=(int)data[6];
            cur_lay=(int)data[7];
            //qDebug()<<"cur_lay"<<cur_lay<<laynum;
            int id=cur_lay;
            int n=0;
            if(laynum!=displayNumchanged)
            {
                conunt=0;
                if(laynum<displayNumchanged)
                {
                   n= displayNumchanged-laynum;
                   for(int m=0;m<n;m++)
                   {
                       mypushButton_list[laynum+m]->setHidden(true);
                   }
                }
                for(int i=0;i<laynum;i++)
                {
                    if(mypushButton_list[i]->lay_id==cur_id)
                    {

                        mypushButton_list[i]->ok=0;
                        mypushButton_list[i]->update();
                    }
                }
            }
            //qDebug()<<"cur_lay"<<cur_lay<<laynum;
            if(conunt!=0)
            {
                if(cur_lay==cur_id)
                {
                    return;
                }
                for(int i=0;i<laynum;i++)
                {
                    if(mypushButton_list[i]->lay_id==cur_id)
                    {

                        mypushButton_list[i]->ok=0;
                        mypushButton_list[i]->update();
                    }
                }

            }
            cur_id=cur_lay;
            //for(int j=0;j<laynum;j++)
            //{
                //if(mypushButton_list[j]->lay_id==cur_lay)
                //{
                    //mypushButton_list[j]->ok=1;
                    //mypushButton_list[j]->update();
                //}
            //}
            mypushButton_list[cur_lay]->ok=1;
            mypushButton_list[cur_lay]->update();
            if(conunt==0)
            {
                if(laynum<=8)
                {
                    pagnumsum=0;
                    ui->pushButton_2->setHidden(true);
                    ui->pushButton_3->setHidden(true);
                }else if(laynum>8&&laynum<=16)
                {
                    pagnumsum=1;
                    ui->pushButton_2->setHidden(false);
                    ui->pushButton_3->setHidden(false);
                }else if(laynum>16&&laynum<=24)
                {
                    pagnumsum=2;
                    ui->pushButton_2->setHidden(false);
                    ui->pushButton_3->setHidden(false);
                }else if(laynum>24&&laynum<=32)
                {
                    pagnumsum=3;
                    ui->pushButton_2->setHidden(false);
                    ui->pushButton_3->setHidden(false);
                }
                for(int k=0;k<32;k++)
                {
                    mypushButton_list[k]->setHidden(true);
                }
                pagnum=(id)/8;
                for(int i=0+(8*pagnum);i<(pagnum+1)*8;i++)
                {
                    if(i<laynum)
                   {
                       mypushButton_list[i]->setHidden(false);
                   }
                }
            }else
            {
                if((id/8)!=pagnum)
                {
                    for(int k=0;k<32;k++)
                    {
                        mypushButton_list[k]->setHidden(true);
                    }
                    pagnum=id/8;
                    for(int i=0+(8*pagnum);i<(pagnum+1)*8;i++)
                    {
                        if(i<laynum)
                            mypushButton_list[i]->setHidden(false);
                    }
                }
            }
            if(laynum>0 && conunt==0)
            {
                emit isok(true);
                displayNumchanged=laynum;
                conunt++;
                tem_id_1=0;
            }

}

void MainWindow::SendCmd(bool ok)
{
    QByteArray buf_1;
    char ckecknum;
    if(ok)
    {
        if(tem_id_1<laynum)
        {
            buf_1.clear();
            buf_1.append(0x07);
            buf_1.append(0xc2);
            buf_1.append(0xc2);
            buf_1.append(0x79);
            buf_1.append(0x01);
            buf_1.append(tem_id_1 & 0xff);
//            for(int i=0;i<6;i++)
//            {
//                ckecknum+=buf_1.at(i);
//            }
//            ckecknum=0x100-ckecknum;
            buf_1.append(0xfb-(tem_id_1 & 0xff));
            serial->write(buf_1);
            //qDebug()<<"2222"<<laynum;
            //tem_id_1++;
        }
    }
}

void MainWindow::SendConnectCmd()
{
    if(cur_time.addSecs(10)>QTime::currentTime())
    {
        return;
    }
    if(tem_time.addSecs(1)>QTime::currentTime())
    {
        return;
    }

    if(ok_1!=ok_2)
    {
        if(ok_1-ok_2>2)
        {
            ui->label_2->setStyleSheet(tr("background-image: url(:/image/通信2.png);"));
        }
    }else
    {
        if(ui->label_2->styleSheet()==tr("background-image: url(:/image/通信2.png);"))
        {
            ui->label_2->setStyleSheet(tr("background-image: url(:/image/通信1.png)"));
        }
    }
    QByteArray buf_1;
    buf_1.clear();
    buf_1.append(0x07);
    buf_1.append(0xc2);
    buf_1.append(0xc2);
    buf_1.append(0x79);
    buf_1.append(0x01);
    buf_1.append(0xff);
    buf_1.append(0xfc);
    ok_5=1;
    serial->write(buf_1);
    qDebug()<<buf_1.toHex();
    if(ok_1==32)
    {
        ok_1=0;
    }
    ok_1++;
}

void MainWindow::data_handle_new(char *data)
{
    int num;
    RetLayDetailbuffer alltata={0};
    memcpy(&alltata,data,sizeof(RetLayDetailbuffer));
    Read_All_Data.All_Data[alltata.LayoutData.LayoutID]=alltata;
    num=alltata.LayoutData.LayoutID;
//    qDebug()<<"layid:"<<alltata.LayoutData.LayoutID;
   // qDebug()<<alltata.LayoutData.LayoutID<<alltata.LayoutData.ValidData;
    if(alltata.LayoutData.ValidData==0)
    {
        return;
    }
    for(int i=0;i<alltata.LayoutData.WinNum;i++)
    {
       //memcpy(&mypushButton_list[alltata.LayoutData.LayoutID]->get_data.Windows[i],&alltata.LayoutData.Windows[i],sizeof(Win_Attri_t));
       memcpy(&mypushButton_list[tem_id_1]->get_data,&alltata.LayoutData,sizeof(Layout_Attri_t));
       mypushButton_list[tem_id_1]->rectnum=alltata.LayoutData.WinNum;
       mypushButton_list[tem_id_1]->n=tem_id_1;
       mypushButton_list[tem_id_1]->lay_id=alltata.LayoutData.LayoutID;
       // qDebug()<<alltata.LayoutData.LayoutID;
    }
//    if(laynum<=8)
//    {

//           if(num<laynum/2)
//           {
//            mypushButton_list[alltata.LayoutData.LayoutID]->setGeometry(g_nActScreenX/(laynum/2)*num+10*(num+1),
//                                                                       g_nActScreenY/8+25,g_nActScreenX/(laynum/2),g_nActScreenY/4*3/2-50);
//           }else
//           {
//            mypushButton_list[alltata.LayoutData.LayoutID]->setGeometry(g_nActScreenX/(laynum/2)*(num-laynum/2)+10*(num-laynum/2+1),
//                                                                          g_nActScreenY/8+25+g_nActScreenY/4*3/2,g_nActScreenX/(laynum/2),g_nActScreenY/4*3/2-50);
//           }

//    }
    if(alltata.LayoutData.LayoutID==cur_lay)
    {
        mypushButton_list[tem_id_1]->ok=1;
    }
    mypushButton_list[tem_id_1]->update();
    tem_id_1++;
}
void MainWindow::on_pushButton_3_clicked()
{
    if(pagnum==pagnumsum)
    {
        for(int i=0+(8*pagnum);i<(pagnum+1)*8;i++)
        {
           mypushButton_list[i]->setHidden(true);
        }
        pagnum=0;
        for(int i=0+(8*pagnum);i<(pagnum+1)*8;i++)
        {
           if(i<laynum)
             mypushButton_list[i]->setHidden(false);
        }
        return;
    }
    for(int i=0+(8*pagnum);i<(pagnum+1)*8;i++)
    {
       mypushButton_list[i]->setHidden(true);
    }
    pagnum++;
    for(int i=0+(8*pagnum);i<(pagnum+1)*8;i++)
    {
       if(i<laynum)
         mypushButton_list[i]->setHidden(false);
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    if(pagnum==0)
    {
        for(int i=0+(8*pagnum);i<(pagnum+1)*8;i++)
        {
           mypushButton_list[i]->setHidden(true);
        }
        pagnum=pagnumsum;
        for(int i=0+(8*pagnum);i<(pagnum+1)*8;i++)
        {
           mypushButton_list[i]->setHidden(false);
        }
        return;
    }
    for(int i=0+(8*pagnum);i<(pagnum+1)*8;i++)
    {
       mypushButton_list[i]->setHidden(true);
    }
    pagnum--;
    for(int i=0+(8*pagnum);i<(pagnum+1)*8;i++)
    {
       mypushButton_list[i]->setHidden(false);
    }
}

void MainWindow::on_pushButton_3_pressed()
{
    //ui->pushButton_3->setStyleSheet(tr("background-image: url(:/右翻页-深-01.png);"));
}

void MainWindow::on_pushButton_3_released()
{
    //ui->pushButton_3->setStyleSheet(tr("background-image: url(:/右翻页-浅-01.png);"));
}

void MainWindow::on_pushButton_2_pressed()
{
    //ui->pushButton_2->setStyleSheet(tr("background-image: url(:/左翻页-深-01.png);"));
}

void MainWindow::on_pushButton_2_released()
{
    //ui->pushButton_2->setStyleSheet(tr("background-image: url(:/左翻页-浅-01.png);"));
}
