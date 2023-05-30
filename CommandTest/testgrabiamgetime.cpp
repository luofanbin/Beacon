#include "testgrabiamgetime.h"
#include "ui_testgrabiamgetime.h"
#include <QDesktopWidget>
#include <QDebug>
#include <QGridLayout>
#include <QHBoxLayout>

TestGrabIamgeTime::TestGrabIamgeTime(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TestGrabIamgeTime)
{
    ui->setupUi(this);
    GrabIamgeStartLable=new QLabel(this);
    GrabIamgeStopLable=new QLabel(this);
    SaveCount1Lable=new QLabel(this);
//    SaveCount2Lable=new QLabel(this);
//    SaveCount3Lable=new QLabel(this);
    GrabIamgeButton=new QPushButton(this);
    GrabIamgeButton->setText("GrabImage");
    connect(GrabIamgeButton,SIGNAL(clicked(bool)),this,SLOT(on_GrabImageButton_clicked()));
    QGridLayout *gridLayout = new QGridLayout(this);
    gridLayout->addWidget(GrabIamgeStartLable,0,0,1,1);
    gridLayout->addWidget(GrabIamgeStopLable,1,0,1,1);

    QHBoxLayout *hLayout = new QHBoxLayout();
    hLayout->addWidget(SaveCount1Lable);
//    hLayout->addWidget(SaveCount2Lable);
//    hLayout->addWidget(SaveCount3Lable);
    hLayout->addWidget(GrabIamgeButton);

    gridLayout->addLayout(hLayout,2,0,1,1);
    this->setLayout(gridLayout);
    QFont font;
    font.setPointSize(50);//字体大小
    GrabIamgeStartLable ->setFont(font);//其他控件一样
    GrabIamgeStopLable ->setFont(font);//其他控件一样
    SaveCount1Lable ->setFont(font);//其他控件一样
//    SaveCount2Lable ->setFont(font);//其他控件一样
//    SaveCount3Lable ->setFont(font);//其他控件一样

    QDesktopWidget * deskTop = QApplication::desktop();
    int curMonitor = deskTop->screenNumber ( this ); // 参数是一个QWidget*
    QRect rect = deskTop->screenGeometry(1);
    this->setGeometry(rect.x() , rect.y(), rect.width(), rect.height());

    //this->setWindowFlags(Qt::FramelessWindowHint);//无边框
}

TestGrabIamgeTime::~TestGrabIamgeTime()
{
    delete ui;
}

void TestGrabIamgeTime::on_GrabImageButton_clicked()
{
    emit emitSendGrabImage();
}
