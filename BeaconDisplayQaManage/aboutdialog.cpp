#include "aboutdialog.h"
#include "ui_aboutdialog.h"
#include<QPainter>
AboutDialog::AboutDialog(QWidget *parent) :
QDialog(parent),
ui(new Ui::AboutDialog)
{
ui->setupUi(this);
ReTranslateUi();
setAttribute(Qt::WA_QuitOnClose, false);
setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint);
}

AboutDialog::~AboutDialog()
{
    delete ui;
}

void AboutDialog::ReTranslateUi()
{
    this->setWindowTitle(tr("About BeaconDisplayQaManage"));
    ui->label_2->setText(tr("CopyRight by Li shuhui"));
    ui->label_3->setText(tr("QQ:40348105"));
    ui->label_4->setText(tr("Mobile:1351069953"));
}
void AboutDialog::paintEvent(QPaintEvent *event)
 {

    QPixmap arrayImage(":/system/Resources/beacon.png"); //图片路径
    QRect arrayRect(0,0,50,50); //截取图片区域
    QPainter painter(this);
 // painter.drawPixmap(QPoint(0,0),arrayImage); //打印图片
    painter.drawPixmap(this->rect(),arrayImage);
}
