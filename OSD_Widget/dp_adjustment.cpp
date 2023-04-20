#include "dp_adjustment.h"
#include<QPainter>

DpAdjustment::DpAdjustment(QWidget *parent) : QDialog(parent)
{
    setupUi(this);
    QIcon close_button_ico(":/image/close.png");
    this->toolButton->setIcon(close_button_ico);
    timer=new QTimer;
    connect(this->Lane1checkBox,SIGNAL(clicked()),this,SLOT(checkBox_Click()));
    connect(this->Lane2checkBox,SIGNAL(clicked()),this,SLOT(checkBox_Click()));
    connect(this->Lane4checkBox,SIGNAL(clicked()),this,SLOT(checkBox_Click()));
    connect(this->Voltage_Level_checkBox,SIGNAL(clicked()),this,SLOT(checkBox_Click()));
    connect(this->Voltage_Level_checkBox_2,SIGNAL(clicked()),this,SLOT(checkBox_Click()));
    connect(this->Voltage_Level_checkBox_3,SIGNAL(clicked()),this,SLOT(checkBox_Click()));
    connect(this->Voltage_Level_checkBox_4,SIGNAL(clicked()),this,SLOT(checkBox_Click()));
    connect(this->Emphasis_Level_checkBox,SIGNAL(clicked()),this,SLOT(checkBox_Click()));
    connect(this->Emphasis_Level_checkBox_2,SIGNAL(clicked()),this,SLOT(checkBox_Click()));
    connect(this->Emphasis_Level_checkBox_3,SIGNAL(clicked()),this,SLOT(checkBox_Click()));
    connect(this->Emphasis_Level_checkBox_4,SIGNAL(clicked()),this,SLOT(checkBox_Click()));
    //connect(this->Lane_Num_comboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(CommBoxChangIndex(int)));
    connect(this->Submit_toolButton,SIGNAL(clicked()),this,SLOT(SubmitButtonClicked()));
}

DpAdjustment::~DpAdjustment()
{
}

void DpAdjustment::paintEvent(QPaintEvent *event)
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

void DpAdjustment::GetDPLinkTrainingInfo(int nFlag,stSCAL_INPUT_DP_INFO DPInfo)
{
//    if(nFlag==0)
//    {
    switch (DPInfo.uiLane_Num) {
    case 1:
       this->Lane1checkBox->setChecked(true);
       this->Lane2checkBox->setChecked(false);
       this->Lane4checkBox->setChecked(false);
        break;
    case 2:
       this->Lane2checkBox->setChecked(true);
        this->Lane1checkBox->setChecked(false);
        this->Lane4checkBox->setChecked(false);
        break;
    case 4:
       this->Lane4checkBox->setChecked(true);
        this->Lane1checkBox->setChecked(false);
        this->Lane2checkBox->setChecked(false);
        break;
    default:
        break;
    }

        switch (DPInfo.uiLane_VL) {
        case 0:
            this->Voltage_Level_checkBox->setChecked(true);
            this->Voltage_Level_checkBox_2->setChecked(false);
            this->Voltage_Level_checkBox_3->setChecked(false);
            this->Voltage_Level_checkBox_4->setChecked(false);
            this->Emphasis_Level_checkBox->setEnabled(true);
            this->Emphasis_Level_checkBox_2->setEnabled(true);
            this->Emphasis_Level_checkBox_3->setEnabled(true);
            this->Emphasis_Level_checkBox_4->setEnabled(true);
            break;
        case 1:
            this->Voltage_Level_checkBox->setChecked(false);
            this->Voltage_Level_checkBox_2->setChecked(true);
            this->Voltage_Level_checkBox_3->setChecked(false);
            this->Voltage_Level_checkBox_4->setChecked(false);
            this->Emphasis_Level_checkBox->setEnabled(true);
            this->Emphasis_Level_checkBox_2->setEnabled(true);
            this->Emphasis_Level_checkBox_3->setEnabled(true);
            this->Emphasis_Level_checkBox_4->setEnabled(false);
            break;
        case 2:
            this->Voltage_Level_checkBox->setChecked(false);
            this->Voltage_Level_checkBox_2->setChecked(false);
            this->Voltage_Level_checkBox_3->setChecked(true);
            this->Voltage_Level_checkBox_4->setChecked(false);
            this->Emphasis_Level_checkBox->setEnabled(true);
            this->Emphasis_Level_checkBox_2->setEnabled(true);
            this->Emphasis_Level_checkBox_3->setEnabled(false);
            this->Emphasis_Level_checkBox_4->setEnabled(false);
            break;
        case 3:
            this->Voltage_Level_checkBox->setChecked(false);
            this->Voltage_Level_checkBox_2->setChecked(false);
            this->Voltage_Level_checkBox_3->setChecked(false);
            this->Voltage_Level_checkBox_4->setChecked(true);
            this->Emphasis_Level_checkBox->setEnabled(true);
            this->Emphasis_Level_checkBox_2->setEnabled(false);
            this->Emphasis_Level_checkBox_3->setEnabled(false);
            this->Emphasis_Level_checkBox_4->setEnabled(false);
            break;
        default:
            break;
        }

        switch (DPInfo.uiLane_EL) {
        case 0:
            this->Emphasis_Level_checkBox->setChecked(true);
            this->Emphasis_Level_checkBox_2->setChecked(false);
            this->Emphasis_Level_checkBox_3->setChecked(false);
            this->Emphasis_Level_checkBox_4->setChecked(false);

            break;
        case 1:
            this->Emphasis_Level_checkBox->setChecked(false);
            this->Emphasis_Level_checkBox_2->setChecked(true);
            this->Emphasis_Level_checkBox_3->setChecked(false);
            this->Emphasis_Level_checkBox_4->setChecked(false);

            break;
        case 2:
            this->Emphasis_Level_checkBox->setChecked(false);
            this->Emphasis_Level_checkBox_2->setChecked(false);
            this->Emphasis_Level_checkBox_3->setChecked(true);
            this->Emphasis_Level_checkBox_4->setChecked(false);

            break;
        case 3:
            this->Emphasis_Level_checkBox->setChecked(false);
            this->Emphasis_Level_checkBox_2->setChecked(false);
            this->Emphasis_Level_checkBox_3->setChecked(false);
            this->Emphasis_Level_checkBox_4->setChecked(true);

            break;
        default:
            break;
        }

    //}

    if(DPInfo.uiLane_CR==1)
    {
        this->label_4->setText("          Clock Recovery: OK");
    }else {
       this->label_4->setText("          Clock Recovery: NG");
    }

    if(DPInfo.uiLane_EQ==1)
    {
        this->label_5->setText("Channel Equalization: OK");
    }else {
        this->label_5->setText("Channel Equalization: NG");
    }

    enableCheckBox();
}

void DpAdjustment::init()
{
    //this->Submit_toolButton->setEnabled(false);
    QPalette pe;
    pe.setColor(QPalette::WindowText,Qt::red);
    this->Prompt_Label->setPalette(pe);
    this->Prompt_Label->setText("DP Link Training on going...");
    this->show();
}

void DpAdjustment::setSubmitButtonEnable()
{
    this->Submit_toolButton->setEnabled(false);
    if(this->Voltage_Level_checkBox->isChecked())
        this->Submit_toolButton->setEnabled(true);

    if(this->Voltage_Level_checkBox_2->isChecked())
        this->Submit_toolButton->setEnabled(true);

    if(this->Voltage_Level_checkBox_3->isChecked())
        this->Submit_toolButton->setEnabled(true);

    if(this->Voltage_Level_checkBox_4->isChecked())
        this->Submit_toolButton->setEnabled(true);

    if(this->Emphasis_Level_checkBox->isChecked())
        this->Submit_toolButton->setEnabled(true);

    if(this->Emphasis_Level_checkBox_2->isChecked())
        this->Submit_toolButton->setEnabled(true);

    if(this->Emphasis_Level_checkBox_3->isChecked())
        this->Submit_toolButton->setEnabled(true);

    if(this->Emphasis_Level_checkBox_4->isChecked())
        this->Submit_toolButton->setEnabled(true);
}

void DpAdjustment::enableCheckBox()
{
//    this->Lane1checkBox->setEnabled(true);
//    this->Lane2checkBox->setEnabled(true);
//    this->Lane4checkBox->setEnabled(true);
//    this->Voltage_Level_checkBox->setEnabled(true);
//    this->Voltage_Level_checkBox_2->setEnabled(true);
//    this->Voltage_Level_checkBox_3->setEnabled(true);
//    this->Voltage_Level_checkBox_4->setEnabled(true);
//    this->Emphasis_Level_checkBox->setEnabled(true);
//    this->Emphasis_Level_checkBox_2->setEnabled(true);
//    this->Emphasis_Level_checkBox_3->setEnabled(true);
//    this->Emphasis_Level_checkBox_4->setEnabled(true);

//    this->Lane1checkBox->setChecked(false);
//    this->Lane2checkBox->setChecked(false);
//    this->Lane4checkBox->setChecked(false);
//    this->Voltage_Level_checkBox->setChecked(false);
//    this->Voltage_Level_checkBox_2->setChecked(false);
//    this->Voltage_Level_checkBox_3->setChecked(false);
//    this->Voltage_Level_checkBox_4->setChecked(false);
//    this->Emphasis_Level_checkBox->setChecked(false);
//    this->Emphasis_Level_checkBox_2->setChecked(false);
//    this->Emphasis_Level_checkBox_3->setChecked(false);
//    this->Emphasis_Level_checkBox_4->setChecked(false);
    this->groupBox->setEnabled(true);
}

void DpAdjustment::disableCheckBox()
{
//    this->Lane1checkBox->setEnabled(false);
//    this->Lane2checkBox->setEnabled(false);
//    this->Lane4checkBox->setEnabled(false);
//    this->Voltage_Level_checkBox->setEnabled(false);
//    this->Voltage_Level_checkBox_2->setEnabled(false);
//    this->Voltage_Level_checkBox_3->setEnabled(false);
//    this->Voltage_Level_checkBox_4->setEnabled(false);
//    this->Emphasis_Level_checkBox->setEnabled(false);
//    this->Emphasis_Level_checkBox_2->setEnabled(false);
//    this->Emphasis_Level_checkBox_3->setEnabled(false);
//    this->Emphasis_Level_checkBox_4->setEnabled(false);
    this->groupBox->setEnabled(false);
}

void DpAdjustment::on_toolButton_clicked()
{
    this->hide();
}

void DpAdjustment::checkBox_Click()
{
    QCheckBox* checkBox = qobject_cast<QCheckBox*>(sender());

    if (checkBox->objectName()=="Voltage_Level_checkBox")
    {
        if(this->Voltage_Level_checkBox->isChecked())
        {
            this->Voltage_Level_checkBox->setChecked(true);
            this->Voltage_Level_checkBox_2->setChecked(false);
            this->Voltage_Level_checkBox_3->setChecked(false);
            this->Voltage_Level_checkBox_4->setChecked(false);
            this->Emphasis_Level_checkBox->setEnabled(true);
            this->Emphasis_Level_checkBox_2->setEnabled(true);
            this->Emphasis_Level_checkBox_3->setEnabled(true);
            this->Emphasis_Level_checkBox_4->setEnabled(true);
        }

    }else if (checkBox->objectName()=="Voltage_Level_checkBox_2")
    {
        if(this->Emphasis_Level_checkBox_4->isChecked())
        {
            if(this->Voltage_Level_checkBox_2->isChecked())
                this->Voltage_Level_checkBox_2->setChecked(false);
            return;
        }

        if(this->Voltage_Level_checkBox_2->isChecked())
        {
            this->Voltage_Level_checkBox->setChecked(false);
            this->Voltage_Level_checkBox_3->setChecked(false);
            this->Voltage_Level_checkBox_4->setChecked(false);
            this->Emphasis_Level_checkBox->setEnabled(true);
            this->Emphasis_Level_checkBox_2->setEnabled(true);
            this->Emphasis_Level_checkBox_3->setEnabled(true);
            this->Emphasis_Level_checkBox_4->setEnabled(false);
        }
        else
        {
            this->Emphasis_Level_checkBox->setEnabled(true);
            this->Emphasis_Level_checkBox_2->setEnabled(true);
            this->Emphasis_Level_checkBox_3->setEnabled(true);
            this->Emphasis_Level_checkBox_4->setEnabled(true);
        }
    }else if (checkBox->objectName()=="Voltage_Level_checkBox_3")
    {
        if(this->Emphasis_Level_checkBox_3->isChecked() || this->Emphasis_Level_checkBox_4->isChecked())
        {
            if(this->Voltage_Level_checkBox_3->isChecked())
                this->Voltage_Level_checkBox_3->setChecked(false);
            return;
        }

        if(this->Voltage_Level_checkBox_3->isChecked())
        {
            this->Voltage_Level_checkBox_2->setChecked(false);
            this->Voltage_Level_checkBox->setChecked(false);
            this->Voltage_Level_checkBox_4->setChecked(false);
            this->Emphasis_Level_checkBox->setEnabled(true);
            this->Emphasis_Level_checkBox_2->setEnabled(true);
            this->Emphasis_Level_checkBox_3->setEnabled(false);
            this->Emphasis_Level_checkBox_4->setEnabled(false);
        }
        else
        {
            this->Emphasis_Level_checkBox->setEnabled(true);
            this->Emphasis_Level_checkBox_2->setEnabled(true);
            this->Emphasis_Level_checkBox_3->setEnabled(true);
            this->Emphasis_Level_checkBox_4->setEnabled(true);
        }

    }else if (checkBox->objectName()=="Voltage_Level_checkBox_4")
    {
        if(this->Emphasis_Level_checkBox_3->isChecked() || this->Emphasis_Level_checkBox_4->isChecked() ||
                this->Emphasis_Level_checkBox_2->isChecked())
        {
            if(this->Voltage_Level_checkBox_4->isChecked())
                this->Voltage_Level_checkBox_4->setChecked(false);
            return;
        }


        if(this->Voltage_Level_checkBox_4->isChecked())
        {
            this->Voltage_Level_checkBox_2->setChecked(false);
            this->Voltage_Level_checkBox_3->setChecked(false);
            this->Voltage_Level_checkBox->setChecked(false);
            this->Emphasis_Level_checkBox->setEnabled(true);
            this->Emphasis_Level_checkBox_2->setEnabled(false);
            this->Emphasis_Level_checkBox_3->setEnabled(false);
            this->Emphasis_Level_checkBox_4->setEnabled(false);
        }
        else
        {
            this->Emphasis_Level_checkBox->setEnabled(true);
            this->Emphasis_Level_checkBox_2->setEnabled(true);
            this->Emphasis_Level_checkBox_3->setEnabled(true);
            this->Emphasis_Level_checkBox_4->setEnabled(true);
        }

    }else if (checkBox->objectName()=="Emphasis_Level_checkBox")
    {
        if(this->Emphasis_Level_checkBox->isChecked())
        {
            this->Emphasis_Level_checkBox_2->setChecked(false);
            this->Emphasis_Level_checkBox_3->setChecked(false);
            this->Emphasis_Level_checkBox_4->setChecked(false);
            this->Voltage_Level_checkBox_3->setEnabled(true);
            this->Voltage_Level_checkBox_2->setEnabled(true);
            this->Voltage_Level_checkBox->setEnabled(true);
            this->Voltage_Level_checkBox_4->setEnabled(true);
        }

    }else if (checkBox->objectName()=="Emphasis_Level_checkBox_2")
    {
        if(this->Emphasis_Level_checkBox_2->isChecked())
        {
            this->Emphasis_Level_checkBox->setChecked(false);
            this->Emphasis_Level_checkBox_3->setChecked(false);
            this->Emphasis_Level_checkBox_4->setChecked(false);
            this->Voltage_Level_checkBox_3->setEnabled(true);
            this->Voltage_Level_checkBox_2->setEnabled(true);
            this->Voltage_Level_checkBox->setEnabled(true);
            this->Voltage_Level_checkBox_4->setEnabled(false);
        }
        else
        {
            this->Voltage_Level_checkBox_4->setEnabled(true);
        }

    }else if (checkBox->objectName()=="Emphasis_Level_checkBox_3")
    {
        if(this->Emphasis_Level_checkBox_3->isChecked())
        {
            this->Emphasis_Level_checkBox_2->setChecked(false);
            this->Emphasis_Level_checkBox->setChecked(false);
            this->Emphasis_Level_checkBox_4->setChecked(false);

            this->Voltage_Level_checkBox_3->setEnabled(false);
            this->Voltage_Level_checkBox_2->setEnabled(true);
            this->Voltage_Level_checkBox->setEnabled(true);
            this->Voltage_Level_checkBox_4->setEnabled(false);
        }
        else {

            this->Voltage_Level_checkBox_3->setEnabled(true);
            this->Voltage_Level_checkBox_4->setEnabled(true);
        }



    }else if (checkBox->objectName()=="Emphasis_Level_checkBox_4")
    {
        if(this->Emphasis_Level_checkBox_4->isChecked())
        {
            this->Emphasis_Level_checkBox_2->setChecked(false);
            this->Emphasis_Level_checkBox_3->setChecked(false);
            this->Emphasis_Level_checkBox->setChecked(false);
            this->Voltage_Level_checkBox_3->setEnabled(false);
            this->Voltage_Level_checkBox_2->setEnabled(false);
            this->Voltage_Level_checkBox->setEnabled(true);
            this->Voltage_Level_checkBox_4->setEnabled(false);
        }
        else {
            this->Voltage_Level_checkBox_2->setEnabled(true);
            this->Voltage_Level_checkBox_3->setEnabled(true);
            this->Voltage_Level_checkBox_4->setEnabled(true);
        }

    }else if (checkBox->objectName()=="Lane1checkBox")
    {
        if(!this->Lane1checkBox->isChecked())
        {
            this->Lane1checkBox->setChecked(true);
            return;
        }

        this->Lane2checkBox->setChecked(false);
        this->Lane4checkBox->setChecked(false);
         stSCAL_INPUT_DP_INFO DP_Info;
         DP_Info.uiLane_Num=1;

         DP_Info.uiLane_ID=0;
         DP_Info.uiLane_VL=0;
         DP_Info.uiLane_EL=0;
         DP_Info.uiLane_CR=0;
         DP_Info.uiLane_EQ=0;
         emit st_DP_Info(DP_Info);
         disableCheckBox();
         return;
    }else if (checkBox->objectName()=="Lane2checkBox")
    {
        if(!this->Lane2checkBox->isChecked())
        {
            this->Lane2checkBox->setChecked(true);
            return;
        }

        this->Lane1checkBox->setChecked(false);
        this->Lane4checkBox->setChecked(false);
         stSCAL_INPUT_DP_INFO DP_Info;
         DP_Info.uiLane_Num=2;

         DP_Info.uiLane_ID=0;
         DP_Info.uiLane_VL=0;
         DP_Info.uiLane_EL=0;
         DP_Info.uiLane_CR=0;
         DP_Info.uiLane_EQ=0;
         emit st_DP_Info(DP_Info);
         disableCheckBox();
         return;
    }else if (checkBox->objectName()=="Lane4checkBox")
    {
        if(!this->Lane4checkBox->isChecked())
        {
            this->Lane4checkBox->setChecked(true);
            return;
        }

        this->Lane2checkBox->setChecked(false);
        this->Lane1checkBox->setChecked(false);
         stSCAL_INPUT_DP_INFO DP_Info;
         DP_Info.uiLane_Num=4;

         DP_Info.uiLane_ID=0;
         DP_Info.uiLane_VL=0;
         DP_Info.uiLane_EL=0;
         DP_Info.uiLane_CR=0;
         DP_Info.uiLane_EQ=0;
         emit st_DP_Info(DP_Info);
         disableCheckBox();
         return;
    }

    //setSubmitButtonEnable();
}

void DpAdjustment::CommBoxChangIndex(int index)
{
  /*
    if(read_DP)
    {
        read_DP=false;
        return;
    }

    stSCAL_INPUT_DP_INFO DP_Info;
    if(index==2)
        DP_Info.uiLane_Num=4;
    else
        DP_Info.uiLane_Num=this->Lane_Num_comboBox->currentIndex()+1;
    DP_Info.uiLane_ID=0;
    DP_Info.uiLane_VL=0;
    DP_Info.uiLane_EL=0;
    DP_Info.uiLane_CR=0;
    DP_Info.uiLane_EQ=0;

    if(blIsSendSetDp)
       emit st_DP_Info(DP_Info);
       */
}

void DpAdjustment::SubmitButtonClicked()
{
    stSCAL_INPUT_DP_INFO DP_Info;
    DP_Info.uiLane_Num=4;

    DP_Info.uiLane_ID=1;

    if(this->Voltage_Level_checkBox->isChecked())
        DP_Info.uiLane_VL=0;
    else if(this->Voltage_Level_checkBox_2->isChecked())
        DP_Info.uiLane_VL=1;
    else if(this->Voltage_Level_checkBox_3->isChecked())
        DP_Info.uiLane_VL=2;
    else if(this->Voltage_Level_checkBox_4->isChecked())
        DP_Info.uiLane_VL=3;
    else
        DP_Info.uiLane_VL=255;

    if(this->Emphasis_Level_checkBox->isChecked())
        DP_Info.uiLane_EL=0;
    else if(this->Emphasis_Level_checkBox_2->isChecked())
        DP_Info.uiLane_EL=1;
    else if(this->Emphasis_Level_checkBox_3->isChecked())
        DP_Info.uiLane_EL=2;
    else if(this->Emphasis_Level_checkBox_4->isChecked())
        DP_Info.uiLane_EL=3;
    else
        DP_Info.uiLane_EL=255;

    DP_Info.uiLane_CR=0;
    DP_Info.uiLane_EQ=0;

    emit st_DP_Info(DP_Info);
    disableCheckBox();
}

void DpAdjustment::slot_DpInfoHide()
{
    QPalette pe;
    pe.setColor(QPalette::WindowText,Qt::red);
    this->Prompt_Label->setPalette(pe);
    this->Prompt_Label->setText("DP Link Training Finished");
    //this->Lane_Num_comboBox->setEnabled(true);
    //this->Submit_toolButton->setEnabled(true);
    QThread::msleep( 1000 );
    this->Prompt_Label->setText(" ");
    timer->stop();
    blIsSendSetDp=true;
}
