#include "visualevaluation.h"
#include "ui_visualevaluation.h"
#include<QDate>
#include "testimage.h"
VisualEvaluation::VisualEvaluation(QWidget *parent) :
    BasicDocument(parent),
    ui(new Ui::VisualEvaluation)
{
    ui->setupUi(this);
    ui->OverallImageQuality_comboBox->clear();
    ui->OverallImageQuality_comboBox->addItems(g_strListResult);
    ui->GrayscaleResolution_comboBox->clear();
    ui->GrayscaleResolution_comboBox->addItems(g_strListResult);
    ui->LumResponse_comboBox->clear();
    ui->LumResponse_comboBox->addItems(g_strListResult);
    ui->LumUniformity_comboBox->clear();
    ui->LumUniformity_comboBox->addItems(g_strListResult);
    ui->Chromaticity_comboBox->clear();
    ui->Chromaticity_comboBox->addItems(g_strListResult);
    ui->PixelFaults_comboBox->clear();
    ui->PixelFaults_comboBox->addItems(g_strListResult);

    ui->ClinicalImageResult_comboBox->clear();
    ui->ClinicalImageResult_comboBox->addItems(g_strListResult);


    connect(ui->QaVisibleTest,SIGNAL(clicked()),this,SLOT(QaVisibleTest()));
    connect(ui->QaClinicalTest,SIGNAL(clicked()),this,SLOT(QaClinicalTest()));
}

VisualEvaluation::~VisualEvaluation()
{
    delete ui;
}

void VisualEvaluation::ui_init()
{
    QDate curr_date(QDate::currentDate());
    QString CurrDateStr=curr_date.toString("yyyy-MM-dd");
    ui->OverallImageQuality_comboBox->setCurrentIndex(0);
    ui->GrayscaleResolution_comboBox->setCurrentIndex(0);
    ui->LumResponse_comboBox->setCurrentIndex(0);
    ui->LumUniformity_comboBox->setCurrentIndex(0);
    ui->Chromaticity_comboBox->setCurrentIndex(0);
    ui->TypeA_lineEdit->setText("0");
    ui->TypeB_lineEdit->setText("0");
    ui->TypeC_lineEdit->setText("0");
    ui->PixelFaults_comboBox->setEnabled(false);
    ui->ClinicalImageResult_comboBox->setCurrentIndex(0);
    ui->ReferenceImages_lineEdit->clear();
    ui->AssessorName_lineEdit->clear();   
    ui->AssessmentNotes_textEdit->clear();

}

Visual_Evaluation_Data VisualEvaluation::getData()
{



    Visual_Evaluation_Data VisualEvaluationInfo;
    VisualEvaluationInfo.ViasulEvaluationIndex[Visual_Evaluation_Data::OVERALL_QUALITY]=ui->OverallImageQuality_comboBox->currentIndex();
    VisualEvaluationInfo.ViasulEvaluationIndex[Visual_Evaluation_Data::GRASCALE_RESOLUTION]=ui->GrayscaleResolution_comboBox->currentIndex();
    VisualEvaluationInfo.ViasulEvaluationIndex[Visual_Evaluation_Data::LUMINANCE_RESPOSE]=ui->LumResponse_comboBox->currentIndex();
    VisualEvaluationInfo.ViasulEvaluationIndex[Visual_Evaluation_Data::LUMINCE_UNIFORMITY]=ui->LumUniformity_comboBox->currentIndex();
    VisualEvaluationInfo.ViasulEvaluationIndex[Visual_Evaluation_Data::CHROMATICITY]=ui->Chromaticity_comboBox->currentIndex();
    VisualEvaluationInfo.PixelFaultsData[Visual_Evaluation_Data::PIXEL_FAULTS_TYPE_A]=ui->TypeA_lineEdit->text().toInt();
    VisualEvaluationInfo.PixelFaultsData[Visual_Evaluation_Data::PIXEL_FAULTS_TYPE_B]=ui->TypeB_lineEdit->text().toInt();
    VisualEvaluationInfo.PixelFaultsData[Visual_Evaluation_Data::PIXEL_FAULTS_TYPE_C]=ui->TypeC_lineEdit->text().toInt();
    VisualEvaluationInfo.PixelFaultsData[Visual_Evaluation_Data::PIXEL_FAULTS_TYPE_RESULT]=ui->PixelFaults_comboBox->currentIndex();
    VisualEvaluationInfo.ImageResultIndex=ui->ClinicalImageResult_comboBox->currentIndex();
    VisualEvaluationInfo.ReferenceImage=ui->ReferenceImages_lineEdit->text();
    VisualEvaluationInfo.Assessor=ui->AssessorName_lineEdit->text();

    VisualEvaluationInfo.AssessmentNotes=ui->AssessmentNotes_textEdit->toPlainText();




    return VisualEvaluationInfo;
}

void VisualEvaluation::setData(Visual_Evaluation_Data *VisualEvaluationInfo)
{

    ui->OverallImageQuality_comboBox->setCurrentIndex(VisualEvaluationInfo->ViasulEvaluationIndex[Visual_Evaluation_Data::OVERALL_QUALITY]);
    ui->GrayscaleResolution_comboBox->setCurrentIndex(VisualEvaluationInfo->ViasulEvaluationIndex[Visual_Evaluation_Data::GRASCALE_RESOLUTION]);
    ui->LumResponse_comboBox->setCurrentIndex(VisualEvaluationInfo->ViasulEvaluationIndex[Visual_Evaluation_Data::LUMINANCE_RESPOSE]);
    ui->LumUniformity_comboBox->setCurrentIndex(VisualEvaluationInfo->ViasulEvaluationIndex[Visual_Evaluation_Data::LUMINCE_UNIFORMITY]);
    ui->Chromaticity_comboBox->setCurrentIndex(VisualEvaluationInfo->ViasulEvaluationIndex[Visual_Evaluation_Data::CHROMATICITY]);
    ui->TypeA_lineEdit->setText(QString::number(VisualEvaluationInfo->PixelFaultsData[Visual_Evaluation_Data::PIXEL_FAULTS_TYPE_A]));
    ui->TypeB_lineEdit->setText(QString::number(VisualEvaluationInfo->PixelFaultsData[Visual_Evaluation_Data::PIXEL_FAULTS_TYPE_B]));
    ui->TypeC_lineEdit->setText(QString::number(VisualEvaluationInfo->PixelFaultsData[Visual_Evaluation_Data::PIXEL_FAULTS_TYPE_C]));
    ui->PixelFaults_comboBox->setCurrentIndex(VisualEvaluationInfo->PixelFaultsData[Visual_Evaluation_Data::PIXEL_FAULTS_TYPE_RESULT]);
    ui->ClinicalImageResult_comboBox->setCurrentIndex(VisualEvaluationInfo->ImageResultIndex);
    ui->ReferenceImages_lineEdit->setText(VisualEvaluationInfo->ReferenceImage);
    ui->AssessorName_lineEdit->setText(VisualEvaluationInfo->Assessor);

    ui->AssessmentNotes_textEdit->setText(VisualEvaluationInfo->AssessmentNotes);

    ui->widget_grayscale->show();
    ui->widget_response->show();
    ui->frame_pixel->show();
    ui->widget_chromaticity->show();


     ui->widget_grayscale->hide();

    if (getDocument()->ReportQaType==QA_CONSTANCY||
             getDocument()->ReportQaType==QA_CONSTANCY_NEW) {

        ui->widget_response->hide();
        ui->frame_pixel->hide();
          ui->widget_chromaticity->hide();
    }





    StQaCheckCondition stQaCondition;
    getQaResult(stQaCondition);


}
void VisualEvaluation::getDataFromTestImage(TestImage* pTestImage,bool blIsClinical)
{
    StTg18Result st_tg_result;
    Visual_Evaluation_Data evaluation=getData();
    if(!blIsClinical)
    {
        for (int i=QA_TG18_OIQ_NORMAL;i<=QA_TG18_END;i++)
        {
            st_tg_result.emType=(EmTg18Type)i;

            if(pTestImage->getTg18Data(st_tg_result))
            {
                switch (st_tg_result.emType)
                {
                case QA_TG18_OIQ_NORMAL:
                    evaluation.ViasulEvaluationIndex[Visual_Evaluation_Data::OVERALL_QUALITY]=st_tg_result.dataResult.nResult[0];
                    break;
                case QA_TG18_CT:
                    evaluation.ViasulEvaluationIndex[Visual_Evaluation_Data::LUMINANCE_RESPOSE]=st_tg_result.dataResult.nResult[0];
                    break;
                case QA_TG18_UN80_CONSTANCY:
                {
                    if (getDocument()->ReportQaType==QA_CONSTANCY||
                                 getDocument()->ReportQaType==QA_CONSTANCY_NEW)
                    evaluation.ViasulEvaluationIndex[Visual_Evaluation_Data::LUMINCE_UNIFORMITY]=st_tg_result.dataResult.nResult[0];
                }
                     break;
                case QA_TG18_UN80:
                    evaluation.ViasulEvaluationIndex[Visual_Evaluation_Data::LUMINCE_UNIFORMITY]=st_tg_result.dataResult.nResult[0];
                    evaluation.ViasulEvaluationIndex[Visual_Evaluation_Data::CHROMATICITY]=st_tg_result.dataResult.nResult[1];
                    evaluation.PixelFaultsData[Visual_Evaluation_Data::PIXEL_FAULTS_TYPE_B]=st_tg_result.dataResult.nResult[2];;
                    evaluation.PixelFaultsData[Visual_Evaluation_Data::PIXEL_FAULTS_TYPE_C]=st_tg_result.dataResult.nResult[3];;
                    //   evaluation.PixelFaultsData[Visual_Evaluation_Data::PIXEL_FAULTS_TYPE_C]=st_tg_result.dataResult.nResult[0];

                    break;
                case QA_TG18_UN10:
                    evaluation.PixelFaultsData[Visual_Evaluation_Data::PIXEL_FAULTS_TYPE_A]=st_tg_result.dataResult.nResult[0];
                    evaluation.PixelFaultsData[Visual_Evaluation_Data::PIXEL_FAULTS_TYPE_C]=qMax(st_tg_result.dataResult.nResult[1],evaluation.PixelFaultsData[Visual_Evaluation_Data::PIXEL_FAULTS_TYPE_C]);
                    ;
                    break;
                }

            }


        }
     }else //for the clinical image test
    {
    st_tg_result.emType=QA_TG18_CHEST;
    if(pTestImage->getTg18Data(st_tg_result))
        {
        evaluation.ImageResultIndex=st_tg_result.dataResult.nResult[0];

        }

    }
setData(&evaluation);
}
void VisualEvaluation::QaVisibleTest()
{
    TestImage dlg_test(this);
    if(getDocument()->ReportQaType==QA_ACCEPTANCE||
            getDocument()->ReportQaType==QA_ACCEPTANCE_NEW)
    dlg_test.setTg18Type(QA_TG18_OIQ_NORMAL,QA_METHOD_ACCEPTANCE_VISIBLE);
    else if (getDocument()->ReportQaType==QA_CONSTANCY||
             getDocument()->ReportQaType==QA_CONSTANCY_NEW) {
        dlg_test.setTg18Type(QA_TG18_OIQ_NORMAL,    QA_METHOD_CONSTANCY_VISIBLE);
    }
    dlg_test.showFullScreen();
    int res = dlg_test.exec();
    if(res!=QDialog::Accepted)
        return ;
    getDataFromTestImage(&dlg_test);
    emit checkQaResult();

}
void VisualEvaluation::QaClinicalTest()
{
    TestImage dlg_test(this);
    EmTg18MethodType emTg18MethodType;
    EmTg18Type emTg18Type;
    if(ui->checkBoxSelectBreast->isChecked())
    {
        emTg18MethodType=QA_METHOD_CLINICAL_ALL;
        emTg18Type=QA_TG18_MAM01;
    }
    else
    {
        emTg18MethodType=QA_METHOD_CLINICAL_PART;
        emTg18Type=QA_TG18_KNEE;
    }
    dlg_test.setTg18Type(emTg18Type,emTg18MethodType);
    dlg_test.showFullScreen();
    int res = dlg_test.exec();
    if(res!=QDialog::Accepted)
        return ;
    getDataFromTestImage(&dlg_test,true);
    emit checkQaResult();

}
bool VisualEvaluation::getQaResult(StQaCheckCondition &stQaCondition)
{
    if(!stQaCondition.checkDataStatus())
        return false;

    QVector<QComboBox *> combox_test;
    if(getDocument()->ReportQaType==QA_ACCEPTANCE||
            getDocument()->ReportQaType==QA_ACCEPTANCE_NEW)
    {
        combox_test.push_back( ui->OverallImageQuality_comboBox);
     #ifdef USG_QA_TG18_MP
        combox_test.push_back(ui->GrayscaleResolution_comboBox);
      #endif
        combox_test.push_back(ui->LumResponse_comboBox);
        combox_test.push_back(ui->LumUniformity_comboBox);
        combox_test.push_back(ui->Chromaticity_comboBox);
        combox_test.push_back(ui->PixelFaults_comboBox);
        combox_test.push_back(ui->ClinicalImageResult_comboBox);


    }
    else if (getDocument()->ReportQaType==QA_CONSTANCY||
             getDocument()->ReportQaType==QA_CONSTANCY_NEW)
    {

            combox_test.push_back( ui->OverallImageQuality_comboBox);
            combox_test.push_back(ui->LumUniformity_comboBox);
            combox_test.push_back(ui->ClinicalImageResult_comboBox);



    }



    bool bl_return=true;
    for (int i=0;i<combox_test.size();i++)
    {
        if(combox_test[i]->currentIndex()<1)
        {
            stQaCondition.strResult=tr("Please complete the visuale valuation test in the visual evaluation!!");
            bl_return=false;
            break;
        }
    }



    Visual_Evaluation_Data VisualEvaluationInfo=getData();
    if(VisualEvaluationInfo.PixelFaultsData[Visual_Evaluation_Data::PIXEL_FAULTS_TYPE_A]<=stQaCondition.nPixelTypeA &&
        VisualEvaluationInfo.PixelFaultsData[Visual_Evaluation_Data::PIXEL_FAULTS_TYPE_B]<=stQaCondition.nPixelTypeB &&
        VisualEvaluationInfo.PixelFaultsData[Visual_Evaluation_Data::PIXEL_FAULTS_TYPE_C]<=stQaCondition.nPixelTypeC)
        ui->PixelFaults_comboBox->setCurrentIndex(RESULT_OK);
   else
         ui->PixelFaults_comboBox->setCurrentIndex(RESULT_FAIL);


    if(getDocument()->ReportQaType==QA_ACCEPTANCE||
            getDocument()->ReportQaType==QA_ACCEPTANCE_NEW)
    {
        for(int i=Visual_Evaluation_Data::OVERALL_QUALITY;i<=Visual_Evaluation_Data::CHROMATICITY;i++)
        {
             #ifndef USG_QA_TG18_MP
            if(i==Visual_Evaluation_Data::GRASCALE_RESOLUTION)
                continue;
            #endif
            if(VisualEvaluationInfo.ViasulEvaluationIndex[i]!=RESULT_OK)
                return false;
        }

        if(VisualEvaluationInfo.PixelFaultsData[Visual_Evaluation_Data::PIXEL_FAULTS_TYPE_RESULT]!=RESULT_OK)
            return false;

            if(ui->PixelFaults_comboBox->currentIndex()!=RESULT_OK)
            return false;


    }
    else if (getDocument()->ReportQaType==QA_CONSTANCY||
             getDocument()->ReportQaType==QA_CONSTANCY_NEW)

    {
        if(VisualEvaluationInfo.ViasulEvaluationIndex[Visual_Evaluation_Data::OVERALL_QUALITY]!=RESULT_OK)
            return false;
        if(VisualEvaluationInfo.ViasulEvaluationIndex[Visual_Evaluation_Data::LUMINCE_UNIFORMITY]!=RESULT_OK)
            return false;


    }


        if(VisualEvaluationInfo.ImageResultIndex==RESULT_FAIL)
            return false;
    return bl_return;
}
