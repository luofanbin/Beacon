#include "overlaymodes.h"
#include "ui_overlaymodes.h"
#include<QRadioButton>
#include <QPainter>
OverlayModes::OverlayModes(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OverlayModes)
{
    ui->setupUi(this);
    ui->tableWidget->setColumnCount(13);
    QHeaderView *header = ui->tableWidget->verticalHeader();
    header->setHidden(true);// 隐藏行号
    QStringList headers;
    headers << QStringLiteral(" ") << QStringLiteral("index") << QStringLiteral("Preset Name")<<QStringLiteral("H-Freq(kHz)")
            <<QStringLiteral("V-Freq(Hz)")<<QStringLiteral("H-Active")<<QStringLiteral("V-Active")<<QStringLiteral("H-Total")<<QStringLiteral("V-Total")
            <<QStringLiteral("H_Sync/V_Sync")<<QStringLiteral("V_Sync_Width")<<QStringLiteral("ValidPortFlag")<<QStringLiteral("ModeType");
    ui->tableWidget->setHorizontalHeaderLabels(headers);
    ui->tableWidget->resizeColumnsToContents();
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    QIcon close_button_ico(":/image/close.png");
    ui->toolButton->setIcon(close_button_ico);
}

OverlayModes::~OverlayModes()
{
    delete ui;
}

void OverlayModes::paintEvent(QPaintEvent *event)
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

void OverlayModes::displayTableData(int nCount,int nCurrIndex,stSCAL_ANALOG_MODE_PARAMS_Index_Array stScalAnalogModeParams)
{
    displayLoadProgress(" ");
    QRadioButton *radioButton[nCount];
    ui->tableWidget->setRowCount(nCount);
    QString strValidPortFlag;
    double dbValue;
    QString str;
    for(int i=0;i<nCount;i++)
    {
        radioButton[i]=new QRadioButton();
        radioButton[i]->setObjectName(QString("%1").arg(stScalAnalogModeParams[i].uiModeIndex));
        ui->tableWidget->setCellWidget(i,0,radioButton[i]);
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(QString("%1").arg(stScalAnalogModeParams[i].uiModeIndex)));
        ui->tableWidget->setItem(i,2,new QTableWidgetItem(stScalAnalogModeParams[i].PresetName));
        dbValue=(double)stScalAnalogModeParams[i].uiH_Freq/10;
        str=QString::number(dbValue,'f',1);
        ui->tableWidget->setItem(i,3,new QTableWidgetItem(str));
        dbValue=(double)stScalAnalogModeParams[i].uiV_Freq/10;
        str=QString::number(dbValue,'f',1);
        ui->tableWidget->setItem(i,4,new QTableWidgetItem(str));
        ui->tableWidget->setItem(i,5,new QTableWidgetItem(QString("%1").arg(stScalAnalogModeParams[i].uiH_Active)));
        ui->tableWidget->setItem(i,6,new QTableWidgetItem(QString("%1").arg(stScalAnalogModeParams[i].uiV_Active)));
        ui->tableWidget->setItem(i,7,new QTableWidgetItem(QString("%1").arg(stScalAnalogModeParams[i].uiH_Total)));
        ui->tableWidget->setItem(i,8,new QTableWidgetItem(QString("%1").arg(stScalAnalogModeParams[i].uiV_Total)));

        if(stScalAnalogModeParams[i].uiH_Sync==0)
            str="+";

        if(stScalAnalogModeParams[i].uiH_Sync==1)
            str="-";

        if(stScalAnalogModeParams[i].uiV_Sync==0)
            str+="/+";

        if(stScalAnalogModeParams[i].uiV_Sync==1)
            str+="/-";

        ui->tableWidget->setItem(i,9,new QTableWidgetItem(str));
        ui->tableWidget->setItem(i,10,new QTableWidgetItem(QString("%1").arg(stScalAnalogModeParams[i].uiV_Sync_Width)));

        switch (stScalAnalogModeParams[i].uiValidPortFlag) {
        case ALL_VALID:
             strValidPortFlag=tr("all valid");
        break;
        case VGA_ONLY+1:
            strValidPortFlag=tr("VGA only");
        break;
        case CVBS_S_VIDEO_ONLY+2:
            strValidPortFlag=tr("CVBS/S-VIDEO only");
        break;
        }
        ui->tableWidget->setItem(i,11,new QTableWidgetItem(strValidPortFlag));
        ui->tableWidget->setItem(i,12,new QTableWidgetItem(QString("%1").arg(stScalAnalogModeParams[i].ModeType)));

        if(nCurrIndex==stScalAnalogModeParams[i].uiModeIndex)
            radioButton[i]->setChecked(true);
        connect(radioButton[i],&QRadioButton::clicked,this,&OverlayModes::slotOverlayModesIndex);
    }
}

bool OverlayModes::displayLoadProgress(QString strText)
{
    QPalette pe;
    pe.setColor(QPalette::WindowText,Qt::red);
    ui->labelLoad->setPalette(pe);
    ui->labelLoad->setText(strText);
    ui->tableWidget->clearContents();
}

void OverlayModes::on_toolButton_clicked()
{
    this->hide();
}

void OverlayModes::slotOverlayModesIndex()
{
    QRadioButton* btn = qobject_cast<QRadioButton*>(sender());
    emit emitOverlayModesIndex(btn->objectName().toInt());
}
