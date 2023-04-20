#include "newoverlaymode.h"
#include "ui_newoverlaymode.h"
#include <QPainter>
#include <QDebug>
#include <QMessageBox>
NewOverlayMode::NewOverlayMode(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewOverlayMode)
{
    ui->setupUi(this);
    ui->tableWidget->setRowCount(1);
    ui->tableWidget->setColumnCount(11);
    QHeaderView *header = ui->tableWidget->verticalHeader();
    header->setHidden(true);// 隐藏行号
    QStringList headers;
    headers << QStringLiteral("Preset Name")<<QStringLiteral("H-Frequency")
            <<QStringLiteral("V-Frequency")<<QStringLiteral("V-Total")<<QStringLiteral("H-Total")<<QStringLiteral("H-Active")<<QStringLiteral("V-Active")
            <<QStringLiteral("H-Start")<<QStringLiteral("V-Start")<<QStringLiteral("ValidPortFlag")<<QStringLiteral("   Mode Type   ");
    ui->tableWidget->setHorizontalHeaderLabels(headers);
    ui->tableWidget->resizeColumnsToContents();

    comboBoxValidPortFlag=new QComboBox();
    QStringList strList;
    strList << QStringLiteral("all valid")<<QStringLiteral("VGA only")<<QStringLiteral("CVBS/S-VIDEO only");
    comboBoxValidPortFlag->addItems(strList);
    ui->tableWidget->setCellWidget(0,9,comboBoxValidPortFlag);

    checkModeType=new QCheckBox("Interlaced");
    ui->tableWidget->setCellWidget(0,10,checkModeType);

    QIcon close_button_ico(":/image/close.png");
    ui->toolButton->setIcon(close_button_ico);
}

NewOverlayMode::~NewOverlayMode()
{
    delete ui;
}

void NewOverlayMode::paintEvent(QPaintEvent *event)
{
    QPainter paint(this);
    paint.setPen(QColor(127,127,127));

    for(int i=0;i<7;i++)
    {
        paint.drawLine(rect().left(),rect().top()+i,rect().right(),rect().top()+i);
        paint.drawLine(rect().left()+i,rect().top(),rect().left()+i,rect().bottom());
        paint.drawLine(rect().left(),rect().bottom()-i,rect().right(),rect().bottom()-i);
        paint.drawLine(rect().right()-i,rect().top(),rect().right()-i,rect().bottom());
    }
}

bool NewOverlayMode::setTableData(stSCAL_ANALOG_INPUT_PARAMS stValue,stVStart stHStartValue,stVStart stVStartValue)
{
//    QTableWidgetItem *item = new QTableWidgetItem(QString("%1").arg(stValue.uiH_Freq));
//    item->setFlags(item->flags() & (~Qt::ItemIsEditable));

//    QTableWidgetItem *item1 = new QTableWidgetItem(QString("%1").arg(stValue.uiV_Freq));
//    item1->setFlags(item1->flags() & (~Qt::ItemIsEditable));

//    QTableWidgetItem *item2 = new QTableWidgetItem(QString("%1").arg(stValue.uiV_Total));
//    item2->setFlags(item2->flags() & (~Qt::ItemIsEditable));

    ui->tableWidget->setItem(0,0,new QTableWidgetItem(QString(" ")));
    ui->tableWidget->setItem(0,1,new QTableWidgetItem(QString("%1").arg(stValue.uiH_Freq)));
    ui->tableWidget->setItem(0,2,new QTableWidgetItem(QString("%1").arg(stValue.uiV_Freq)));
    ui->tableWidget->setItem(0,3,new QTableWidgetItem(QString("%1").arg(stValue.uiV_Total)));
    ui->tableWidget->setItem(0,4,new QTableWidgetItem(QString(" ")));
    ui->tableWidget->setItem(0,5,new QTableWidgetItem(QString(" ")));
    ui->tableWidget->setItem(0,6,new QTableWidgetItem(QString(" ")));
    ui->tableWidget->setItem(0,7,new QTableWidgetItem(QString("%1").arg(stHStartValue.nVStartValue)));
    ui->tableWidget->setItem(0,8,new QTableWidgetItem(QString("%1").arg(stVStartValue.nVStartValue)));
    //ui->tableWidget->setItem(0,9,new QTableWidgetItem(QString(" ")));
}

bool NewOverlayMode::getTableData(stSCAL_ANALOG_MODE_PARAMS *stValue)
{
    QString str;
    stValue->PresetName=ui->tableWidget->item(0,0)->text();
//    if(stValue->PresetName==" ")
//    {
//        str="Preset Name cannot be empty!";
//        QMessageBox::information(this, "Information", str,QMessageBox::Ok);
//        return false;
//    }
    stValue->uiH_Freq=ui->tableWidget->item(0,1)->text().toInt();
    stValue->uiV_Freq=ui->tableWidget->item(0,2)->text().toInt();
    stValue->uiV_Total=ui->tableWidget->item(0,3)->text().toInt();
    stValue->uiH_Total=ui->tableWidget->item(0,4)->text().toInt();
    if((stValue->uiH_Total<100) ||(stValue->uiH_Total>3000))
    {
        str="H-Total range from 100-3000";
        QMessageBox::information(this, "Information", str,QMessageBox::Ok);
        return false;
    }
    stValue->uiH_Active=ui->tableWidget->item(0,5)->text().toInt();
    if((stValue->uiH_Active<100) ||(stValue->uiH_Active>3000))
    {
        str="H-Active range from 100-3000";
        QMessageBox::information(this, "Information", str,QMessageBox::Ok);
        return false;
    }
    stValue->uiV_Active=ui->tableWidget->item(0,6)->text().toInt();
    if((stValue->uiV_Active<100) ||(stValue->uiV_Active>2000))
    {
        str="V-Active range from 100-2000";
        QMessageBox::information(this, "Information", str,QMessageBox::Ok);
        return false;
    }
    stValue->uiH_Start=ui->tableWidget->item(0,7)->text().toInt();
    if((stValue->uiH_Start<0) ||(stValue->uiH_Start>600))
    {
        str="H-Start range from 0-6000";
        QMessageBox::information(this, "Information", str,QMessageBox::Ok);
        return false;
    }
    stValue->uiV_Start=ui->tableWidget->item(0,8)->text().toInt();
    if((stValue->uiV_Start<0) ||(stValue->uiV_Start>200))
    {
        str="V-Start range from 0-200";
        QMessageBox::information(this, "Information", str,QMessageBox::Ok);
        return false;
    }
    stValue->uiValidPortFlag=comboBoxValidPortFlag->currentIndex();

    int nModeType=0;
//    if(ui->checkBoxGrahhics->isChecked())
//        nModeType|=MODE_GRAPHICS;

//    if(ui->checkBoxSdvideo->isChecked())
//        nModeType|=MODE_SDVIDEO;

//    if(ui->checkBoxHdvideo->isChecked())
//        nModeType|=MODE_HDVIDEO;

//    if(ui->checkBoxEdvideo->isChecked())
//        nModeType|=MODE_EDVIDEO;

//    if(ui->checkBoxSog->isChecked())
//        nModeType|=MODE_SOG;

//    if(ui->checkBoxCsync->isChecked())
//        nModeType|=MODE_CSYNC;
    if(checkModeType->isChecked())
        nModeType=4;

    stValue->ModeType=nModeType;

    return true;
}

void NewOverlayMode::on_pushButtonSave_clicked()
{
    stSCAL_ANALOG_MODE_PARAMS stValue;
    bool bl_result=getTableData(&stValue);
    if(bl_result)
    {
        ui->pushButtonSave->setEnabled(false);
        emit sendOverlayModeData(SaveOverlayData,stValue);
    }
}

void NewOverlayMode::on_pushButtonDebug_clicked()
{
    stSCAL_ANALOG_MODE_PARAMS stValue;
    bool bl_result=getTableData(&stValue);
    if(bl_result)
        emit sendOverlayModeData(DebugOverlayData,stValue);
}

void NewOverlayMode::on_toolButton_clicked()
{
    this->hide();
}

void NewOverlayMode::slotSaveOverlayModeOk()
{
    QMessageBox::StandardButton result= QMessageBox::information(this, "Information", "Save new overlaymode operation complete",QMessageBox::Ok);
    switch (result)
    {
    case QMessageBox::Ok:
        ui->pushButtonSave->setEnabled(true);
        break;
    default:
        break;
    }
}
