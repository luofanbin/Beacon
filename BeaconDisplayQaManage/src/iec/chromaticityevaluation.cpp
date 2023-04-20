#include "chromaticityevaluation.h"
#include "ui_chromaticityevaluation.h"

ChromaticityEvaluation::ChromaticityEvaluation(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChromaticityEvaluation)
{
    ui->setupUi(this);
    m_blNinePoint=false;
    showDeviationPoint();
}

ChromaticityEvaluation::~ChromaticityEvaluation()
{
    delete ui;
}

StChromaticityEvaluation ChromaticityEvaluation::getData()
{
    StChromaticityEvaluation chromaticity_evaluation;
    chromaticity_evaluation.dbTopLeftU=ui->TopLeftUlineEdit->text().toDouble();
    chromaticity_evaluation.dbTopLeftV=ui->TopLeftVlineEdit->text().toDouble();
    chromaticity_evaluation.dbTopMiddleU=ui->TopMiddleUlineEdit->text().toDouble();
    chromaticity_evaluation.dbTopMiddleV=ui->TopMiddleVlineEdit->text().toDouble();
    chromaticity_evaluation.dbTopRightU=ui->TopRightUlineEdit->text().toDouble();
    chromaticity_evaluation.dbTopRightV=ui->TopRightVlineEdit->text().toDouble();
    chromaticity_evaluation.dbMiddleLeftU=ui->MiddleLeftUlineEdit->text().toDouble();
    chromaticity_evaluation.dbMiddleLeftV=ui->MiddleLeftVlineEdit->text().toDouble();
    chromaticity_evaluation.dbCenterU=ui->CentreUlineEdit->text().toDouble();
    chromaticity_evaluation.dbCenterV=ui->CentreVlineEdit->text().toDouble();
    chromaticity_evaluation.dbMiddleRightU=ui->MiddleRightUlineEdit->text().toDouble();
    chromaticity_evaluation.dbMiddleRightV=ui->MiddleRightVlineEdit->text().toDouble();
    chromaticity_evaluation.dbBottomLeftU=ui->BottomLeftUlineEdit->text().toDouble();
    chromaticity_evaluation.dbBottomLeftV=ui->BottomLeftVlineEdit->text().toDouble();
    chromaticity_evaluation.dbBottomMiddlU=ui->BottomMiddleUlineEdit->text().toDouble();
    chromaticity_evaluation.dbBottomMiddlV=ui->BottomMiddleVlineEdit->text().toDouble();
    chromaticity_evaluation.dbBottomRightU=ui->BottomRightUlineEdit->text().toDouble();
    chromaticity_evaluation.dbBottomRightV=ui->BottomRightVlineEdit->text().toDouble();

    chromaticity_evaluation.dbOtherDisplayCenterU=ui->OtherDisplayCentreUlineEdit->text().toDouble();
    chromaticity_evaluation.dbOtherDisplayCenterV=ui->OtherDisplayCentreVlineEdit->text().toDouble();

    chromaticity_evaluation.PointNumber=m_blNinePoint ? 9:5;
    return chromaticity_evaluation;
}

void ChromaticityEvaluation::setData(StChromaticityEvaluation *pChromaticityEvaluationInfo)
{
    ui->TopLeftUlineEdit->setText(QString::number(pChromaticityEvaluationInfo->dbTopLeftU,'f',4));
    ui->TopLeftVlineEdit->setText(QString::number(pChromaticityEvaluationInfo->dbTopLeftV,'f',4));

    ui->TopMiddleUlineEdit->setText(QString::number(pChromaticityEvaluationInfo->dbTopMiddleU,'f',4));
    ui->TopMiddleVlineEdit->setText(QString::number(pChromaticityEvaluationInfo->dbTopMiddleV,'f',4));

    ui->TopRightUlineEdit->setText(QString::number(pChromaticityEvaluationInfo->dbTopRightU,'f',4));
    ui->TopRightVlineEdit->setText(QString::number(pChromaticityEvaluationInfo->dbTopRightV,'f',4));

    ui->MiddleLeftUlineEdit->setText(QString::number(pChromaticityEvaluationInfo->dbMiddleLeftU,'f',4));
    ui->MiddleLeftVlineEdit->setText(QString::number(pChromaticityEvaluationInfo->dbMiddleLeftV,'f',4));

    ui->CentreUlineEdit->setText(QString::number(pChromaticityEvaluationInfo->dbCenterU,'f',4));
    ui->CentreVlineEdit->setText(QString::number(pChromaticityEvaluationInfo->dbCenterV,'f',4));

    ui->MiddleRightUlineEdit->setText(QString::number(pChromaticityEvaluationInfo->dbMiddleRightU,'f',4));
    ui->MiddleRightVlineEdit->setText(QString::number(pChromaticityEvaluationInfo->dbMiddleRightV,'f',4));

    ui->BottomLeftUlineEdit->setText(QString::number(pChromaticityEvaluationInfo->dbBottomLeftU,'f',4));
    ui->BottomLeftVlineEdit->setText(QString::number(pChromaticityEvaluationInfo->dbBottomLeftV,'f',4));

    ui->BottomMiddleUlineEdit->setText(QString::number(pChromaticityEvaluationInfo->dbBottomMiddlU,'f',4));
    ui->BottomMiddleVlineEdit->setText(QString::number(pChromaticityEvaluationInfo->dbBottomMiddlV,'f',4));

    ui->BottomRightUlineEdit->setText(QString::number(pChromaticityEvaluationInfo->dbBottomRightU,'f',4));
    ui->BottomRightVlineEdit->setText(QString::number(pChromaticityEvaluationInfo->dbBottomRightV,'f',4));

    ui->MianDisplayCentreUlineEdit->setText(QString::number(pChromaticityEvaluationInfo->dbCenterU,'f',4));
    ui->MianDisplayCentreVlineEdit->setText(QString::number(pChromaticityEvaluationInfo->dbCenterV,'f',4));

    ui->OtherDisplayCentreUlineEdit->setText(QString::number(pChromaticityEvaluationInfo->dbOtherDisplayCenterU,'f',4));
    ui->OtherDisplayCentreVlineEdit->setText(QString::number(pChromaticityEvaluationInfo->dbOtherDisplayCenterV,'f',4));

    m_blNinePoint=(pChromaticityEvaluationInfo->PointNumber==9);

    ui->multiple_deviation_widget->hide();
    initialOtherValue();
    showDeviationPoint();
}

bool ChromaticityEvaluation::getQaResult(StQaCheckCondition &stQaCondition)
{
    if(!stQaCondition.checkDataStatus())
        return false;

    if(ui->TopLeftUlineEdit->text().isEmpty() ||
        ui->TopLeftVlineEdit->text().isEmpty()||
        ui->TopRightUlineEdit->text().isEmpty()||
        ui->TopRightVlineEdit->text().isEmpty() ||
        ui->CentreUlineEdit->text().isEmpty()||
        ui->CentreVlineEdit->text().isEmpty()||
        ui->BottomLeftUlineEdit->text().isEmpty()||
        ui->BottomLeftVlineEdit->text().isEmpty()||
        ui->BottomRightUlineEdit->text().isEmpty()||
        ui->BottomRightVlineEdit->text().isEmpty())
        {
        stQaCondition.strResult=tr("Please fill in chromaticity evaluation information!");
        return false;
        }


    StChromaticityEvaluation chromaticity_evaluation=getData();



//   if(angular_view.dbAverageValue<stQaCondition.dbAverageView)
//   {

//       return false;
//   }

    return true;
}

void ChromaticityEvaluation::showDeviationPoint()
{
    ui->lable_top_middle_1->setVisible(m_blNinePoint);
    ui->lable_top_middle_2->setVisible(m_blNinePoint);
    ui->lable_top_middle_3->setVisible(m_blNinePoint);
    ui->TopMiddleUlineEdit->setVisible(m_blNinePoint);
    ui->TopMiddleVlineEdit->setVisible(m_blNinePoint);

    ui->lable_middle_left_1->setVisible(m_blNinePoint);
    ui->lable_middle_left_2->setVisible(m_blNinePoint);
    ui->lable_middle_left_3->setVisible(m_blNinePoint);
    ui->MiddleLeftUlineEdit->setVisible(m_blNinePoint);
    ui->MiddleLeftVlineEdit->setVisible(m_blNinePoint);

    ui->lable_middle_right_1->setVisible(m_blNinePoint);
    ui->lable_middle_right_2->setVisible(m_blNinePoint);
    ui->lable_middle_right_3->setVisible(m_blNinePoint);
    ui->MiddleRightUlineEdit->setVisible(m_blNinePoint);
    ui->MiddleRightVlineEdit->setVisible(m_blNinePoint);

    ui->label_bottom_middle_1->setVisible(m_blNinePoint);
    ui->label_bottom_middle_2->setVisible(m_blNinePoint);
    ui->label_bottom_middle_3->setVisible(m_blNinePoint);
    ui->BottomMiddleUlineEdit->setVisible(m_blNinePoint);
    ui->BottomMiddleVlineEdit->setVisible(m_blNinePoint);
}

void ChromaticityEvaluation::getDataFromTestImage(StTg18Result st_tg_result)
{
//    StTg18Result st_tg_result;
    StChromaticityEvaluation uniform_data=getData();
    double *p_uniform=&uniform_data.dbTopLeftU;
//    st_tg_result.emType=QA_TG18_UNL80;
//    if( pTestImage->getTg18Data(st_tg_result))
//    {
       int n_step=2;
       if(m_blNinePoint)
            n_step=1;
        for (int i=0;i<=9;i+=n_step)
        {

            *p_uniform=st_tg_result.dataResult.dbLuminace[i+DICOM_GSDF_GRAYSCALE_NUMBER];
            p_uniform+=n_step;

        }
        if(!m_blNinePoint)
            p_uniform-=1;
        for (int i=0;i<=9;i+=n_step)
        {

            *p_uniform=st_tg_result.dataResult.dbLuminace[i+2*DICOM_GSDF_GRAYSCALE_NUMBER];
            p_uniform+=n_step;

        }
        setData(&uniform_data);
        //    }
}

void ChromaticityEvaluation::initialOtherValue()
{
    StChromaticityEvaluation stChromaticityEvaluation=getData();

    double *p_data_u=&stChromaticityEvaluation.dbTopLeftU;
    double *p_data_v=&stChromaticityEvaluation.dbTopLeftV;
    double db_deviation=0;
    double db_max_deviation=0;
    for (int i=0;i<9;i++)
    {

        if((!m_blNinePoint)&&(i%2==1) )
            continue;

        for(int j=0;j<9;j++)
        {
            if((!m_blNinePoint)&&(j%2==1) )
                continue;
            db_deviation=sqrt(pow((p_data_u[j]-p_data_u[i]),2)+pow((p_data_v[j]-p_data_v[i]),2));
            db_max_deviation=qMax(db_max_deviation,db_deviation);
        }
    }
    if(db_max_deviation>0)
        ui->MaxDeviationlineEdit->setText(QString::number(db_max_deviation,'f',4));

    if(stChromaticityEvaluation.dbOtherDisplayCenterU>0.001)
    {
        db_max_deviation=sqrt(pow((stChromaticityEvaluation.dbCenterU-stChromaticityEvaluation.dbOtherDisplayCenterU),2)+pow((stChromaticityEvaluation.dbCenterV-stChromaticityEvaluation.dbOtherDisplayCenterV),2));
        ui->DeviationlineEdit->setText(QString::number(db_max_deviation,'f',4));
    }
}
