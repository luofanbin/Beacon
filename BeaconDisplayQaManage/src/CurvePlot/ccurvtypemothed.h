#ifndef CCURVTYPEMOTHED_H
#define CCURVTYPEMOTHED_H
#include"string"
#include"userdefine.h"

typedef struct _CONTRAST_RESPONSE_DATA_
{
    StQaLuminace stQaData;   
    double dbCurentLuminaceInclueAmbient[DICOM_GSDF_GRAYSCALE_NUMBER];
    double dbStanadardLuminace[DICOM_GSDF_GRAYSCALE_NUMBER];
    double dbJnd[DICOM_GSDF_GRAYSCALE_NUMBER];    //亮度对应的JND
    double dbAverageJnd[DICOM_GSDF_GRAYSCALE_NUMBER-1];    //亮度对应的平均JND
    double dbDevationCurrent[DICOM_GSDF_GRAYSCALE_NUMBER-1];                   //Monitor曲线对应的每JND的亮度偏移率
    double dbDevationStandard[DICOM_GSDF_GRAYSCALE_NUMBER-1];                     //DICOM 3.14曲线对应每JND的亮度偏移率
    double dbDevationPercent[DICOM_GSDF_GRAYSCALE_NUMBER-1];
    std::string  strCurverType;

    _CONTRAST_RESPONSE_DATA_()
        {
            for(int i=0;i<DICOM_GSDF_GRAYSCALE_NUMBER;i++)
            {
                dbCurentLuminaceInclueAmbient[i]=0;
                dbStanadardLuminace[i]=0;
                dbJnd[i]=0;
                if(i<DICOM_GSDF_GRAYSCALE_NUMBER-1)
                {
                  dbAverageJnd[i]=0;
                  dbDevationCurrent[i]=0;
                  dbDevationStandard[i]=0;
                  dbDevationPercent[i]=0;
                 }
            }

        }



}Contrast_response_Data;


class CCurvTypeMothed
{
public:
    CCurvTypeMothed();
    double JndToLuminance(const double &crdbLumin);
    double LuminanceToJnd(const double &crJnd);
    bool WorkDicomCurveData(Contrast_response_Data* pCurverData);
};

#endif // CCURVTYPEMOTHED_H
