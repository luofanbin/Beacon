#include "greyscalechromaticityevaluation.h"

GreyscaleChromaticityEvaluation::GreyscaleChromaticityEvaluation(QWidget *parent) : QWidget(parent)
{
    QLabel *p_dicom_ln[DICOM_GSDF_GRAYSCALE_NUMBER];
    QLabel *p_dicom_ln_unit[DICOM_GSDF_GRAYSCALE_NUMBER];
    QLabel *p_dicom_ln_unit_two[DICOM_GSDF_GRAYSCALE_NUMBER];
    QString str_temp;
    QGridLayout *p_gsdf_layout=new QGridLayout;
//    QLabel *p_lable_temp=new QLabel(tr("u'"));
//     p_gsdf_layout->addWidget(p_lable_temp,0,1);
//     p_lable_temp=new QLabel(tr("v'"));
//     p_gsdf_layout->addWidget(p_lable_temp,0,3);
     QLabel *p_labe=new QLabel(tr("GSDF error"));
     p_labe->setAlignment(Qt::AlignCenter);
//     p_gsdf_layout->addWidget(p_labe,0,5);

    for (int i=0;i<DICOM_GSDF_GRAYSCALE_NUMBER;i++)
    {
        mp_GrayscaleLn_u[i]=new QLineEdit;
        mp_GrayscaleLn_u[i]->setStyleSheet("background-color:rgba(255,255,255,255)");
        mp_GrayscaleLn_u[i]->setReadOnly(true);
         mp_GrayscaleLn_u[i]->setFixedWidth(100);
        mp_GrayscaleLn_v[i]=new QLineEdit;
       mp_GrayscaleLn_v[i]->setReadOnly(true);//setEnabled(false);
       mp_GrayscaleLn_v[i]->setStyleSheet("background-color:rgba(255,255,255,255)");
       mp_GrayscaleLn_v[i]->setFixedWidth(100);
        str_temp=QString(tr("LN%1:  u'")).arg(i+1,2,10,QChar('0'));
        mp_GrayscaleLn_u[i]->setAlignment(Qt::AlignRight);
        mp_GrayscaleLn_v[i]->setAlignment(Qt::AlignRight);
        p_dicom_ln[i]=new QLabel(str_temp);
        p_dicom_ln[i]->setFixedWidth(100);
        p_dicom_ln[i]->setAlignment(Qt::AlignRight);
        p_dicom_ln_unit[i]=new QLabel(tr("  v'"));
        p_dicom_ln_unit[i]->setFixedWidth(50);
        p_dicom_ln_unit[i]->setAlignment(Qt::AlignRight);
       p_dicom_ln_unit_two[i]=new QLabel(tr("  "));
        p_gsdf_layout->addWidget(p_dicom_ln[i],i,0);
        p_gsdf_layout->addWidget(mp_GrayscaleLn_u[i],i,1);
        p_gsdf_layout->addWidget(p_dicom_ln_unit[i],i,2);
        p_gsdf_layout->addWidget(mp_GrayscaleLn_v[i],i,3);
        //p_gsdf_layout->addWidget(p_dicom_ln_unit_two[i],i+1,4);
//        if(i>0)
//        {
//            mp_GrayscaleLnError[i-1]=new QLineEdit("0%");
//            mp_GrayscaleLnError[i-1]->setStyleSheet("background-color:rgba(255,255,255,255)");
//            mp_GrayscaleLnError[i-1]->setReadOnly(true);
//            mp_GrayscaleLnError[i-1]->setAlignment(Qt::AlignRight);
//            p_gsdf_layout->addWidget(mp_GrayscaleLnError[i-1],i+1,5);
//        }
//        else {

//        }
    }
     p_labe=new QLabel(tr("Max.deviation"));

     p_labe->setAlignment(Qt::AlignRight);
    mp_GrayscaleLnDeviationMax=new QLineEdit("0%");
    mp_GrayscaleLnDeviationMax->setReadOnly(true);
    mp_GrayscaleLnDeviationMax->setAlignment(Qt::AlignRight);
    mp_GrayscaleLnDeviationMax->setFixedWidth(100);
    p_gsdf_layout->addWidget(p_labe,DICOM_GSDF_GRAYSCALE_NUMBER+1,1,1,2);
    p_gsdf_layout->addWidget(mp_GrayscaleLnDeviationMax,DICOM_GSDF_GRAYSCALE_NUMBER+1,3);

     p_labe=new QLabel(tr("Discarded measurements:(L<5 cd/m2)"));
     p_labe->setAlignment(Qt::AlignLeft);
    p_gsdf_layout->addWidget(p_labe,DICOM_GSDF_GRAYSCALE_NUMBER+2,1,1,5);

    p_labe=new QLabel(tr("Requirements:Max.deviation<0.01"));
    p_labe->setAlignment(Qt::AlignLeft);
    p_gsdf_layout->addWidget(p_labe,DICOM_GSDF_GRAYSCALE_NUMBER+3,1,1,5);

//    p_labe=new QLabel(tr("Test images"));
//    p_labe->setAlignment(Qt::AlignLeft);
//    p_gsdf_layout->addWidget(p_labe,DICOM_GSDF_GRAYSCALE_NUMBER+4,1);

//    QPushButton *p_test_ln=new QPushButton(tr("Start"));
//    p_gsdf_layout->addWidget(p_test_ln,DICOM_GSDF_GRAYSCALE_NUMBER+4,2,1,2);
    QHBoxLayout *p_left_layout=new QHBoxLayout;
    p_left_layout->addLayout(p_gsdf_layout);
    p_left_layout->addStretch();
    setLayout(p_left_layout);
}

void GreyscaleChromaticityEvaluation::setData(const StGreyscaleChromaticityEvaluation &stGreyscaleChromaticity,const StQaLuminace &stQaData)
{
    m_stGreyscaleChromaticity=stGreyscaleChromaticity;
    m_stQaLuminace=stQaData;

//    QMessageBox::information(NULL,"iterm",QString("return:%1").arg(n_return));
    updateData(false);
}

const StGreyscaleChromaticityEvaluation GreyscaleChromaticityEvaluation::getData()
{
    updateData(true);
    return m_stGreyscaleChromaticity;
}

bool GreyscaleChromaticityEvaluation::getQaResult(StQaCheckCondition &stQaCondition)
{
    if(!stQaCondition.checkDataStatus())
        return false;
//    StQaLuminace st_qa_luminace=getData();
//    for(int i=0;i<DICOM_GSDF_GRAYSCALE_NUMBER;i++)
//    {
//        if(fabs(m_stQaLuminace.dbCurentLuminace[i])<0.0006)
//        {
//            stQaCondition.strResult=tr("Please enter QA luminace in the luminance response!");
//            return false;
//        }

//    }


    if( mp_GrayscaleLnDeviationMax->text().toDouble()>stQaCondition.dbChormaticityGreyscaleDevation)
        return false;
    return true;
}

void GreyscaleChromaticityEvaluation::updateData(bool blUpate)
{
    if(blUpate)//由控键到数组
    {
       // m_stQaLuminace.emCurveValue=CURVE_DICOM;
        for(int i=0;i<DICOM_GSDF_GRAYSCALE_NUMBER;i++)
        {
            m_stGreyscaleChromaticity.dbCurrtCoordinate_u[i]= mp_GrayscaleLn_u[i]->text().toDouble();
            m_stGreyscaleChromaticity.dbCurrtCoordinate_v[i]= mp_GrayscaleLn_v[i]->text().toDouble();
        }

    }
    else//由数组到控键
    {
        double db_max_deviation=0;
        double db_deviation=0;
        for (int i=0;i<DICOM_GSDF_GRAYSCALE_NUMBER;i++) {
            mp_GrayscaleLn_u[i]->setText(QString("%1").arg(m_stGreyscaleChromaticity.dbCurrtCoordinate_u[i]));
            mp_GrayscaleLn_v[i]->setText(QString("%1").arg(m_stGreyscaleChromaticity.dbCurrtCoordinate_v[i]));
            if(m_stQaLuminace.dbCurentLuminace[i]>=5)
            {
                db_deviation=sqrt(qPow((m_stGreyscaleChromaticity.dbCurrtCoordinate_u[i]-m_stGreyscaleChromaticity.dbCurrtCoordinate_u[DICOM_GSDF_GRAYSCALE_NUMBER-1]),2)+
                        qPow((m_stGreyscaleChromaticity.dbCurrtCoordinate_v[i]-m_stGreyscaleChromaticity.dbCurrtCoordinate_v[DICOM_GSDF_GRAYSCALE_NUMBER-1]),2));
                db_max_deviation=db_deviation>db_max_deviation ? db_deviation:db_max_deviation;
            }
        }
        mp_GrayscaleLnDeviationMax->setText(QString::number(db_max_deviation,'f',4));
    }
}
