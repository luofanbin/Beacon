#include "luminancedeviation.h"
#include "ui_luminancedeviation.h"
#include "testimage.h"
LuminanceDeviation::LuminanceDeviation(QWidget *parent) :
   BasicDocument(parent),
    ui(new Ui::LuminanceDeviation)
{
    ui->setupUi(this);
    ui->LumUniformity_comboBox->clear();
    ui->LumUniformity_comboBox->addItems(g_strListResult);
    ui->Multiple_LumUniformity_comboBox->clear();
    ui->Multiple_LumUniformity_comboBox->addItems(g_strListResult);

    m_blNinePoint=false;
    showDeviationPoint();
    connect(ui->TestUniformity,SIGNAL(clicked()),this ,SLOT(testUinform()));

}

LuminanceDeviation::~LuminanceDeviation()
{
    delete ui;
}

void LuminanceDeviation::ui_init()
{
    ui->TopLeftLum_lineEdit->clear();
        ui->TopRightLum_lineEdit->clear();
        ui->BottomLeftLum_lineEdit->clear();
        ui->BottomRightLum_lineEdit->clear();
        ui->MaxDeviation_lineEdit->setText("0.0000");
        ui->MaxDeviation_lineEdit->setEnabled(false);
        ui->LumUniformity_comboBox->setEnabled(false);
        ui->HighestLmax_lineEdit->setText("0.0000");
        ui->HighestLmax_lineEdit->setEnabled(false);
        ui->LowestLmax_lineEdit->setText("0.0000");
        ui->LowestLmax_lineEdit->setEnabled(false);
        ui->MaxDeviation_lineEdit_2->setText("0.0000");
        ui->MaxDeviation_lineEdit_2->setEnabled(false);
        ui->Multiple_LumUniformity_comboBox->setEnabled(false);
}

Luminance_Deviation_Data LuminanceDeviation::getData()
{
    Luminance_Deviation_Data LuminanceDeviationInfo;
    LuminanceDeviationInfo.TopLeftLum=ui->TopLeftLum_lineEdit->text().toDouble();
    LuminanceDeviationInfo.TopMiddleLum=ui->TopMiddLum_lineEdit->text().toDouble();
    LuminanceDeviationInfo.TopRightLum=ui->TopRightLum_lineEdit->text().toDouble();
     LuminanceDeviationInfo.MiddleLeftLum=ui->Middle_left_lineEdit->text().toDouble();
    LuminanceDeviationInfo.CenterLum=ui->Center_lineEdit->text().toDouble();
    LuminanceDeviationInfo.MiddleRightLum=ui->Middle_right_lineEdit->text().toDouble();
    LuminanceDeviationInfo.BottomLeftLum=ui->BottomLeftLum_lineEdit->text().toDouble();
    LuminanceDeviationInfo.BottomMiddleLum=ui->Bottom_middle_lineEdit->text().toDouble();
    LuminanceDeviationInfo.BottomRightLum=ui->BottomRightLum_lineEdit->text().toDouble();

    LuminanceDeviationInfo.SingleDisplayResultIndex=ui->LumUniformity_comboBox->currentIndex();
    LuminanceDeviationInfo.HLmax=ui->HighestLmax_lineEdit->text().toDouble();
    LuminanceDeviationInfo.LLmax=ui->LowestLmax_lineEdit->text().toDouble();

    LuminanceDeviationInfo.AllDisplayResultIndex=ui->Multiple_LumUniformity_comboBox->currentIndex();

    LuminanceDeviationInfo.PointNumber=m_blNinePoint ? 9:5;
    return LuminanceDeviationInfo;
}

void LuminanceDeviation::setData(Luminance_Deviation_Data *LuminanceDeviationInfo)
{
    ui->TopLeftLum_lineEdit->setText(QString::number(LuminanceDeviationInfo->TopLeftLum,'f',4));
    ui->TopMiddLum_lineEdit->setText(QString::number(LuminanceDeviationInfo->TopMiddleLum,'f',4));
    ui->TopRightLum_lineEdit->setText(QString::number(LuminanceDeviationInfo->TopRightLum,'f',4));
     ui->Middle_left_lineEdit->setText(QString::number(LuminanceDeviationInfo->MiddleLeftLum,'f',4));
    ui->Center_lineEdit->setText(QString::number(LuminanceDeviationInfo->CenterLum,'f',4));
    ui->Middle_right_lineEdit->setText(QString::number(LuminanceDeviationInfo->MiddleRightLum,'f',4));
    ui->BottomLeftLum_lineEdit->setText(QString::number(LuminanceDeviationInfo->BottomLeftLum,'f',4));
    ui->Bottom_middle_lineEdit->setText(QString::number(LuminanceDeviationInfo->BottomMiddleLum,'f',4));
    ui->BottomRightLum_lineEdit->setText(QString::number(LuminanceDeviationInfo->BottomRightLum,'f',4));

    ui->LumUniformity_comboBox->setCurrentIndex(LuminanceDeviationInfo->SingleDisplayResultIndex);
    ui->HighestLmax_lineEdit->setText(QString::number(LuminanceDeviationInfo->HLmax,'f',4));
    ui->LowestLmax_lineEdit->setText(QString::number(LuminanceDeviationInfo->LLmax,'f',4));

    ui->Multiple_LumUniformity_comboBox->setCurrentIndex(LuminanceDeviationInfo->AllDisplayResultIndex);
    m_blNinePoint=(LuminanceDeviationInfo->PointNumber==9);

     ui->multiple_deviation_widget->hide();
    initialOtherValue();
    showDeviationPoint();
    return;
}
 void LuminanceDeviation::initialOtherValue()
{
     Luminance_Deviation_Data LuminanceDeviationInfo=getData();

     double *p_data=&LuminanceDeviationInfo.TopLeftLum;
     double db_min=*p_data;
     double db_max=*p_data;
     for (int i=0;i<9;i++)
     {

         if((!m_blNinePoint)&&(i%2==1) )
             continue;
         db_min=qMin(db_min,p_data[i]);
         db_max=qMax(db_max,p_data[i]);


     }
     StQaCheckCondition &stQaCondition=getDocument()->CheckCondition;
     if(db_min>0.0001)
     {
         ui->MaxDeviation_lineEdit->setText(QString::number(200*(db_max-db_min)/(db_min+db_max),'f',2));


        if(stQaCondition.dbUniformDevation>=ui->MaxDeviation_lineEdit->text().toDouble())
            ui->LumUniformity_comboBox->setCurrentIndex(1);
        else
            ui->LumUniformity_comboBox->setCurrentIndex(2);
     }
     if(LuminanceDeviationInfo.LLmax>0.001)
     {
         ui->MaxDeviation_lineEdit_2->setText(QString::number(200*(LuminanceDeviationInfo.HLmax-LuminanceDeviationInfo.LLmax)/(LuminanceDeviationInfo.LLmax+-LuminanceDeviationInfo.HLmax),'f',2));

         if(stQaCondition.dbMultipleDeviation>=ui->MaxDeviation_lineEdit_2->text().toDouble())
             ui->Multiple_LumUniformity_comboBox->setCurrentIndex(1);
         else
             ui->Multiple_LumUniformity_comboBox->setCurrentIndex(2);




     }


 }
  void LuminanceDeviation::getDataFromTestImage(TestImage* pTestImage)
 {
      StTg18Result st_tg_result;
      Luminance_Deviation_Data uniform_data=getData();
      double *p_uniform=&uniform_data.TopLeftLum;
      st_tg_result.emType=QA_TG18_UNL80;
      if( pTestImage->getTg18Data(st_tg_result))
      {
         int n_step=2;
         if(m_blNinePoint)
              n_step=1;
          for (int i=0;i<=9;i+=n_step)
          {

              *p_uniform=st_tg_result.dataResult.dbLuminace[i];
              p_uniform+=n_step;

          }
          setData(&uniform_data);
          emit sendTestImageDataToChromaticityEvaluation(st_tg_result);
      }

  }
 void LuminanceDeviation::testUinform()
 {

     TestImage dlg_test(this);
     dlg_test.setTg18Type(QA_TG18_UNL80,QA_METHOD_SINGLE);

     connect(&dlg_test,SIGNAL(getSensorData(StCieLvxy&)),this,SIGNAL(getSensorData(StCieLvxy&)));
     connect(this,SIGNAL(notSelectSensor()),&dlg_test,SLOT(notSelecteSensor()));
     dlg_test.showFullScreen();
     int res = dlg_test.exec();
     if(res!=QDialog::Accepted)
         return ;
     getDataFromTestImage(&dlg_test);
     disconnect(&dlg_test,SIGNAL(getSensorData(StCieLvxy&)),this,SIGNAL(getSensorData(StCieLvxy&)));
     disconnect(this,SIGNAL(notSelectSensor()),&dlg_test,SLOT(notSelecteSensor()));
     emit checkQaResult();

 }
 void  LuminanceDeviation::showDeviationPoint()
 {

        ui->lable_top_middle_1->setVisible(m_blNinePoint);
        ui->lable_top_middle_2->setVisible(m_blNinePoint);
        ui->lable_top_middle_3->setVisible(m_blNinePoint);
        ui->TopMiddLum_lineEdit->setVisible(m_blNinePoint);

        ui->lable_middle_left_1->setVisible(m_blNinePoint);
        ui->lable_middle_left_2->setVisible(m_blNinePoint);
        ui->lable_middle_left_3->setVisible(m_blNinePoint);

        ui->Middle_left_lineEdit->setVisible(m_blNinePoint);

        ui->lable_middle_right_1->setVisible(m_blNinePoint);
        ui->lable_middle_right_2->setVisible(m_blNinePoint);
        ui->lable_middle_right_3->setVisible(m_blNinePoint);
        ui->Middle_right_lineEdit->setVisible(m_blNinePoint);

        ui->label_bottom_middle_1->setVisible(m_blNinePoint);
        ui->label_bottom_middle_2->setVisible(m_blNinePoint);
        ui->label_bottom_middle_3->setVisible(m_blNinePoint);
        ui->Bottom_middle_lineEdit->setVisible(m_blNinePoint);



 }
 bool LuminanceDeviation::getQaResult(StQaCheckCondition &stQaCondition)
 {
     if(!stQaCondition.checkDataStatus())
         return false;
     Luminance_Deviation_Data luminacne_deviation=getData();
     if(luminacne_deviation.CenterLum<10)
     {
         stQaCondition.strResult=tr("Please complete deviation information!" );
          return false;
     }
     
     if(ui->MaxDeviation_lineEdit->text().toDouble()>stQaCondition.dbUniformDevation)
         return false;
     return true;
 }
