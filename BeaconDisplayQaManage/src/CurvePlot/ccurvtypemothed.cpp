#include "ccurvtypemothed.h"
#include "math.h"
CCurvTypeMothed::CCurvTypeMothed()
{

}

double CCurvTypeMothed::JndToLuminance(const double &crdbLumin)
{
    // double a_=	-1.3011877;
    // double b_=	-0.025840191;
    // double c_=	0.080242636;
    // double d_=	-1.0320229E-01;
    // double e_=	1.3646699E-01;
    // double f_=	2.8745620E-02;
    // double g_=	-2.5468404E-02;
    // double h_=	-3.1978977E-03;
    // double k_=	1.2992634E-04;
    // double m_=	1.3635334E-03;




    double a_=	-1.3011877E+00;
    double b_=	-2.5840191E-02;
    double c_=	8.0242636E-02;
    double d_=	-1.0320229E-01;
    double e_=	1.3646699E-01;
    double f_=	2.8745620E-02;
    double g_=	-2.5468404E-02;
    double h_=	-3.1978977E-03;
    double k_=	1.2992634E-04;
    double m_=	1.3635334E-03;





    return pow(10,(a_+c_*log(crdbLumin)+e_*pow(log(crdbLumin),2)+
        g_*pow(log(crdbLumin),3)+m_*pow(log(crdbLumin),4))/(1+b_*log(crdbLumin)
        +d_*pow(log(crdbLumin),2)+f_*pow(log(crdbLumin),3)+
        h_*pow(log(crdbLumin),4)+k_*pow(log(crdbLumin),5)));

}

double CCurvTypeMothed::LuminanceToJnd(const double &crJnd)
{

    //
    // double iA_=71.498068;
    // double iB_=	94.593053;
    // double iC_=	41.912053;
    // double iD_=	9.8247004;
    // double iE_=	0.28175407;
    // double iF_=	-1.1878455;
    // double iG_=	-0.18014349;
    // double iH_=	0.14710899;
    // double iI_=	-0.017046845;


    double iA_=	71.498068;
    double iB_=	94.593053;
    double iC_=	41.912053;
    double iD_=	9.8247004;
    double iE_=	0.28175407;
    double iF_=	-1.1878455;
    double iG_=	-0.18014349;
    double iH_=	0.14710899;
    double iI_=	-0.017046845;



    return iA_+iB_*log10(crJnd)+
        iC_*pow(log10(crJnd),2)+iD_*pow(log10(crJnd),3)+
        iE_*pow(log10(crJnd),4)+iF_*pow(log10(crJnd),5)+
        iG_*pow(log10(crJnd),6)+iH_*pow(log10(crJnd),7)+iI_*pow(log10(crJnd),8);

}
bool CCurvTypeMothed::WorkDicomCurveData(Contrast_response_Data* pCurverData)
{

     int i;
//qAssert(pCurverData==NULL);


    const  int const_n_step=18;
    double db_std_jnd[const_n_step];//定义标准的18阶的JND值
    double db_std_lumina[const_n_step];//定义标准18阶JND的标准亮度
    //	double db_jnd_cur[const_n_step];//定义实际值亮度的JND值
    double db_cur_lumin[const_n_step];//定义实际亮度值。

    //copy the lumin to the cur_lumin
    for (i=0;i<const_n_step;i++)
    {
        db_cur_lumin[i]=pCurverData->stQaData.dbCurentLuminace[i]+pCurverData->stQaData.AmbientLuminace;
        if(db_cur_lumin[i]<0.0001)
            return false;
      //  if(i>0 && fabs(db_cur_lumin[i-1]-db_cur_lumin[i])<0.0001)
        //    return false;
    }


    //work the std jnd ant the standard jnd luminace
    db_std_jnd[0]=LuminanceToJnd(db_cur_lumin[0]);
    db_std_lumina[0]=db_cur_lumin[0];
    db_std_jnd[const_n_step-1]=LuminanceToJnd(db_cur_lumin[const_n_step-1]);
    db_std_lumina[const_n_step-1]=db_cur_lumin[const_n_step-1];
    //set the standard jnd and luminace
    for ( i=1;i<const_n_step-1;i++)
    {
        db_std_jnd[i]=db_std_jnd[0]+i*(db_std_jnd[const_n_step-1]-db_std_jnd[0])/(const_n_step-1);
        db_std_lumina[i]=JndToLuminance(db_std_jnd[i]);
    }
    /////////////////////////////////////////////////////////////////////////////
   #if 0
        for ( i=0;i<const_n_step;i++)
        {
            db_std_jnd[i]=i*15;
            switch ()
            {
            case CURVE_GAMMA:
                db_std_lumina[i]=db_cur_lumin[0]+(db_cur_lumin[const_n_step-1]-db_cur_lumin[0])*
                    pow(db_std_jnd[i]*1.0/255,m_stQaCurveAttribute.dbGamma);
                break;
            case CURVE_CIE:
                db_std_lumina[i]=pow((i*1.0/255+16)/116,3)*db_cur_lumin[const_n_step-1];
                break;
            }
            db_std_jnd[i]= LuminanceToJnd(db_std_lumina[i]);

        }
#endif

    double db_average_jnd[const_n_step-1];//定义的JND平均值增量
    double db_zero_persent[const_n_step-1];//0%的值
    double db_cur_persent[const_n_step-1];//0%的值
    double db_dicom_temp;



    double db_persent_max=0;
//	m_blIsModify=false;
    for ( i=0;i<const_n_step-1;i++)
    {
        db_dicom_temp=(db_std_lumina[i+1]-db_std_lumina[i])/(0.5*(db_std_lumina[i]+db_std_lumina[i+1]));
        db_average_jnd[i]=0.5*(db_std_jnd[i]+db_std_jnd[i+1]);
        db_zero_persent[i]=db_dicom_temp/(db_std_jnd[i+1]-db_std_jnd[i]);
        db_dicom_temp=(db_cur_lumin[i+1]-db_cur_lumin[i])/(0.5*(db_cur_lumin[i]+db_cur_lumin[i+1]));
        db_cur_persent[i]=db_dicom_temp/(db_std_jnd[i+1]-db_std_jnd[i]);
        db_dicom_temp=fabs(db_zero_persent[i]-db_cur_persent[i])/db_zero_persent[i];
        db_persent_max=fmax(db_persent_max,db_dicom_temp);
    }




    for (i = 0; i < const_n_step; i++)
    {

        pCurverData->dbCurentLuminaceInclueAmbient[i] = db_cur_lumin[i];
        pCurverData->dbStanadardLuminace[i] = db_std_lumina[i];
        pCurverData->dbJnd[i] = db_std_jnd[i];
        if (i > 0)
        {

            pCurverData->dbAverageJnd[i-1 ] = db_average_jnd[i-1];                                  //亮度对应的JND
            pCurverData->dbDevationCurrent[i - 1] = db_cur_persent[i-1];                   //Monitor曲线对应的每JND的亮度偏移率
            pCurverData->dbDevationStandard[i - 1] = db_zero_persent[i-1];                     //DICOM 3.14曲线对应每JND的亮度偏移率
            pCurverData->dbDevationPercent[i - 1] = fabs(db_zero_persent[i - 1] - db_cur_persent[i - 1]) / db_zero_persent[i - 1];
        }
    }









return true;
}
