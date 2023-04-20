#include "display_1.h"
#include<QGridLayout>
#include "testimage.h"
#include "I1DisplaySensor.h"
#include "qaiecreportinformation.h"
enum{
    BEACON_SENSOR_NULL,
    BEACON_SENSOR_XRITE
};
Display_1::Display_1(QWidget *parent) : BasicDocument(parent),mp_SesnorDevice(NULL),mp_Parent(parent)
{
   // QFont font("Adobe 楷体 Std R",10,QFont::Bold);
    DispalyTabWidget=new QTabWidget(this);
  //  DispalyTabWidget->setFont(font);
    DisplayNamePage=new DisplayName(this);

    VisualEvaluationPage=new VisualEvaluation(this);

    BasicLuminancePage=new BasicLuminance_Baseline_I(this);

    LuminanceDeviationPage=new LuminanceDeviation(this);

    mp_ChromaticityEvaluationPage=new ChromaticityEvaluation(this);

     mp_LuminaceResponse=new QLuminaceResponse(this);

     mp_AngularView=new AngularView(this);

     mp_GreyscaleChromaticityEvaluationPage=new GreyscaleChromaticityEvaluation(this);
   //updateTabIterm();
/*
   DispalyTabWidget->addTab(DisplayNamePage,tr("Display information"));
   DispalyTabWidget->addTab(VisualEvaluationPage,tr("Visual evaluation"));
   DispalyTabWidget->addTab(BasicLuminancePage,tr("Basic luminance"));
   DispalyTabWidget->addTab(LuminanceDeviationPage,tr("Luminance deviation"));
   DispalyTabWidget->addTab(mp_LuminaceResponse,tr("Luminance response"));

    DispalyTabWidget->addTab(mp_AngularView,tr("Angular view"));;
*/

updateTabIterm();

    QGridLayout *MainLayout=new QGridLayout(this);
    MainLayout->addWidget(DispalyTabWidget);
    this->setLayout(MainLayout);
    connect(DisplayNamePage,SIGNAL(QaClinicalTest()),VisualEvaluationPage ,SLOT(QaClinicalTest()));
    connect(DisplayNamePage,SIGNAL(QaTestAll()),this ,SLOT(QaTestAll()));
    connect(mp_LuminaceResponse,SIGNAL(testLuminace()),this,SLOT(testLuminace()));
    connect(VisualEvaluationPage,SIGNAL(checkQaResult()),this,SIGNAL(checkQaResult()));
    connect(BasicLuminancePage,SIGNAL(checkQaResult()),this,SIGNAL(checkQaResult()));
    connect(LuminanceDeviationPage,SIGNAL(checkQaResult()),this,SIGNAL(checkQaResult()));
    connect(mp_LuminaceResponse,SIGNAL(checkQaResult()),this,SIGNAL(checkQaResult()));
    connect(LuminanceDeviationPage,SIGNAL(getSensorData(StCieLvxy&)),this,SLOT(getSensorData(StCieLvxy&)));
    connect(this,SIGNAL(notSelectSensor()),LuminanceDeviationPage,SIGNAL(notSelectSensor()));
    connect(LuminanceDeviationPage,SIGNAL(sendTestImageDataToChromaticityEvaluation(StTg18Result)),mp_ChromaticityEvaluationPage,SLOT(getDataFromTestImage(StTg18Result)));
    connect(BasicLuminancePage,SIGNAL(changedLamb(double)),mp_LuminaceResponse,SLOT(changedLamb(double)));

   }
void Display_1::updateTabIterm()
{

  for(int i=DispalyTabWidget->count()-1;i>=0;i--)
      DispalyTabWidget->removeTab(i);

    DispalyTabWidget->addTab(DisplayNamePage,tr("Display information"));
    DispalyTabWidget->addTab(VisualEvaluationPage,tr("Visual evaluation"));
    DispalyTabWidget->addTab(BasicLuminancePage,tr("Basic luminance"));


 //
    mp_AngularView->setHidden(true);
    LuminanceDeviationPage->setHidden(true);
    mp_ChromaticityEvaluationPage->setHidden(true);
    mp_GreyscaleChromaticityEvaluationPage->setHidden(true);
    StIecReport* p_iec_report=getDocument();
    switch (p_iec_report->ReportQaType)
    {
    case QA_ACCEPTANCE:
    case QA_ACCEPTANCE_NEW:
        mp_AngularView->setHidden(false);
        LuminanceDeviationPage->setHidden(false); 
        DispalyTabWidget->addTab(mp_AngularView,tr("Angular view"));;
        DispalyTabWidget->addTab(LuminanceDeviationPage,tr("Luminance deviation"));
       if(p_iec_report->DisplayInfo.DisplayNameInfo.DispalyColorIndex==1)
       {
           mp_ChromaticityEvaluationPage->setHidden(false);
           DispalyTabWidget->addTab(mp_ChromaticityEvaluationPage,tr("Chromaticity evaluation"));
       }
        break;
    default:
        break;

    }

    DispalyTabWidget->addTab(mp_LuminaceResponse,tr("Luminance response"));
    if(p_iec_report->DisplayInfo.DisplayNameInfo.DispalyColorIndex==1)
    {
        mp_GreyscaleChromaticityEvaluationPage->setHidden(false);
        DispalyTabWidget->addTab(mp_GreyscaleChromaticityEvaluationPage,tr("Greyscale chromaticity evaluation"));
    }
}
void Display_1::ui_init()
{
    DisplayNamePage->ui_init();
    VisualEvaluationPage->ui_init();
    BasicLuminancePage->ui_init();
    LuminanceDeviationPage->ui_init();

}

Display_Data Display_1::GetData()
{
    Display_Data DisplayInfo;
    DisplayInfo.DisplayNameInfo=DisplayNamePage->getData();
    DisplayInfo.VisualEvaluationInfo=VisualEvaluationPage->getData();
    DisplayInfo.BasicLuminanceInfo=BasicLuminancePage->getData();

    DisplayInfo.stGrayscaleQaInfo=mp_LuminaceResponse->getData();
    DisplayInfo.GreyscaleChromaticityInfo=mp_GreyscaleChromaticityEvaluationPage->getData();

    StIecReport* p_iec_report=getDocument();
    switch (p_iec_report->ReportQaType)
    {
    case QA_ACCEPTANCE:
    case QA_ACCEPTANCE_NEW:
         DisplayInfo.AngularViewInfo=mp_AngularView->getData();
         DisplayInfo.LuminanceDeviationInfo=LuminanceDeviationPage->getData();
         DisplayInfo.ChromaticityEvaluationInfo=mp_ChromaticityEvaluationPage->getData();
        break;
    default:
        break;

    }

    return DisplayInfo;
}

void Display_1::SetData(Display_Data *DisplayInfo)
{
//updateTabIterm();
updateTabIterm();
StIecReport* p_iec_report=getDocument();
    DisplayNamePage->setData(&DisplayInfo->DisplayNameInfo);
     VisualEvaluationPage->setData(&DisplayInfo->VisualEvaluationInfo);
     BasicLuminancePage->setData(&DisplayInfo->BasicLuminanceInfo,p_iec_report->ReportQaType);

     mp_LuminaceResponse->setData(DisplayInfo->stGrayscaleQaInfo);

    switch (p_iec_report->ReportQaType)
    {
    case QA_ACCEPTANCE:
    case QA_ACCEPTANCE_NEW:
        mp_AngularView->setData(&DisplayInfo->AngularViewInfo);
         LuminanceDeviationPage->setData(&DisplayInfo->LuminanceDeviationInfo);
         mp_GreyscaleChromaticityEvaluationPage->setData(DisplayInfo->GreyscaleChromaticityInfo,DisplayInfo->stGrayscaleQaInfo);
         mp_ChromaticityEvaluationPage->setData(&DisplayInfo->ChromaticityEvaluationInfo);
        break;
    default:
        break;

    }




   // connect(DisplayNamePage->ui.QaTestReport,)
}
void Display_1::QaTestAll()
{
     StIecReport* p_iec_report=getDocument();
    TestImage dlg_test(this);
    if(p_iec_report->ReportQaType==QA_ACCEPTANCE ||
          p_iec_report->ReportQaType==QA_ACCEPTANCE_NEW  )
    {
      dlg_test.setTg18Type(QA_TG18_OIQ_NORMAL,QA_METHOD_ACCEPTANCE_ALL);
    }
    else if(p_iec_report->ReportQaType==QA_CONSTANCY ||
            p_iec_report->ReportQaType==QA_CONSTANCY_NEW)
    {
        dlg_test.setTg18Type(QA_TG18_OIQ_NORMAL,QA_METHOD_CONSTANCY_ALL);
    }
    connect(&dlg_test,SIGNAL(getSensorData(StCieLvxy&)),this,SLOT(getSensorData(StCieLvxy&)));
    connect(this,SIGNAL(notSelectSensor()),&dlg_test,SLOT(notSelecteSensor()));
  dlg_test.setWindowModality(Qt::WindowModal);
    dlg_test.showFullScreen();

  // dlg_test.setAttribute(Qt::WA_ShowModal, true);

    int res = dlg_test.exec();
    if(res!=QDialog::Accepted)
        return ;
    getDataFromTestImage(&dlg_test);
     LuminanceDeviationPage->getDataFromTestImage(&dlg_test);
     VisualEvaluationPage->getDataFromTestImage(&dlg_test);


     if(p_iec_report->ReportQaType==QA_ACCEPTANCE ||
           p_iec_report->ReportQaType==QA_ACCEPTANCE_NEW  )
         {
             mp_AngularView->getDataFromTestImage(&dlg_test);
         }


     emit checkQaResult();
disconnect(&dlg_test,SIGNAL(getSensorData(StCieLvxy&)),this,SLOT(getSensorData(StCieLvxy&)));
disconnect(this,SIGNAL(notSelectSensor()),&dlg_test,SLOT(notSelecteSensor()));
}
void Display_1::getDataFromTestImage(TestImage* pTestImage)
{
    StTg18Result st_tg_result;
    StQaLuminace qa_luminace=mp_LuminaceResponse->getData();
    StGreyscaleChromaticityEvaluation coordinate_data=mp_GreyscaleChromaticityEvaluationPage->getData();
    Basic_Luminance_Data basi_data=BasicLuminancePage->getData();
    st_tg_result.emType=QA_TG18_LN;
    if(pTestImage->getTg18Data(st_tg_result))
    {
        qa_luminace.emCurveValue=CURVE_DICOM;
        qa_luminace.AmbientLuminace=basi_data.Lamb;
        for (int i=0;i<DICOM_GSDF_GRAYSCALE_NUMBER;i++)
        {
            qa_luminace.dbCurentLuminace[i]=st_tg_result.dataResult.dbLuminace[i];
            coordinate_data.dbCurrtCoordinate_u[i]=st_tg_result.dataResult.dbLuminace[i+DICOM_GSDF_GRAYSCALE_NUMBER];
            coordinate_data.dbCurrtCoordinate_v[i]=st_tg_result.dataResult.dbLuminace[i+2*DICOM_GSDF_GRAYSCALE_NUMBER];
        }
        basi_data.DisplayLuminanceMin=qa_luminace.dbCurentLuminace[0];
        basi_data.DisplayLuminanceMax=qa_luminace.dbCurentLuminace[DICOM_GSDF_GRAYSCALE_NUMBER-1];

        BasicLuminancePage->setData(&basi_data);
        mp_LuminaceResponse->setData(qa_luminace);
        mp_GreyscaleChromaticityEvaluationPage->setData(coordinate_data,qa_luminace);
    }

}
void  Display_1::testLuminace()
{
    TestImage dlg_test(this);
    dlg_test.setTg18Type(QA_TG18_LN,QA_METHOD_SINGLE);
    dlg_test.showFullScreen();
    connect(&dlg_test,SIGNAL(getSensorData(StCieLvxy&)),this,SLOT(getSensorData(StCieLvxy&)));
    connect(this,SIGNAL(notSelectSensor()),&dlg_test,SLOT(notSelecteSensor()));
    int res = dlg_test.exec();

    if(res!=QDialog::Accepted)
        return ;
    getDataFromTestImage(&dlg_test);
    emit checkQaResult();
    disconnect(&dlg_test,SIGNAL(getSensorData(StCieLvxy&)),this,SLOT(getSensorData(StCieLvxy&)));
    disconnect(this,SIGNAL(notSelectSensor()),&dlg_test,SLOT(notSelecteSensor()));
}
bool Display_1::getQaResult(StQaCheckCondition &stQaCondition)
{
    if(!stQaCondition.checkDataStatus())
        return false;
    if(!DisplayNamePage->getQaResult(stQaCondition))
       return false;
    if(!VisualEvaluationPage->getQaResult(stQaCondition))
       return false;
    if(!BasicLuminancePage->getQaResult(stQaCondition))
       return false;

    if(!mp_LuminaceResponse->getQaResult(stQaCondition))
       return false;

    StIecReport* p_iec_report=getDocument();
    if(p_iec_report->ReportQaType==QA_ACCEPTANCE ||
          p_iec_report->ReportQaType==QA_ACCEPTANCE_NEW  )
        {
            if(!mp_AngularView->getQaResult(stQaCondition))
               return false;
            if(!LuminanceDeviationPage->getQaResult(stQaCondition))
               return false;
            if(!mp_GreyscaleChromaticityEvaluationPage->getQaResult(stQaCondition))
               return false;
        }




    return true;
}
 void Display_1::setSensorType(int index)
{
     if(mp_SesnorDevice!=NULL)
     {
          delete mp_SesnorDevice;
          mp_SesnorDevice=NULL;
     }

     if(index==BEACON_SENSOR_XRITE)
         mp_SesnorDevice=new CI1DisplaySensor();
     if(mp_SesnorDevice!=NULL)
     {
    // ;    mp_SesnorDevice->BeginWork();
     }

 }
 void Display_1::setDisplayTestPage(int index)
 {
     DispalyTabWidget->setCurrentIndex(index);
 }
  void Display_1::getSensorData(StCieLvxy &stLvxy)
 {
      if(mp_SesnorDevice!=NULL)
          mp_SesnorDevice->GetLvxy(&stLvxy);
      else
          emit notSelectSensor();
          //QMessageBox::warning(NULL,tr("Warning"),tr("Please select proper sensor !"));

 }
void Display_1::getSensorInfo(StSensorInformation& cStInfor)
{
    if(mp_SesnorDevice!=NULL)
        mp_SesnorDevice->getSensorInfo(cStInfor);
    else
        QMessageBox::warning(NULL,tr("Warning"),tr("Please select proper sensor !"));
}
