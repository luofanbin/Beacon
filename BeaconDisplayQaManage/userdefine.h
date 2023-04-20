#ifndef USERDEFINE_H
#define USERDEFINE_H
#include <QtSql>
#include <QStringList>
#include <QSharedDataPointer>

#define SOFTWARE_VERSION 1.1
//#define USG_QA_TG18_MP

//setting the dicom test grayscale number for the 18 number
#define DICOM_GSDF_GRAYSCALE_NUMBER 18


typedef enum
{
    QA_VISUAL,
    QA_ACCEPTANCE,
    QA_CONSTANCY,
    QA_ACCEPTANCE_NEW,
    QA_CONSTANCY_NEW,
    QA_OUTRANGE

}EmReportQaType;
typedef   enum
{
    REPORT_HISTORY,
    REPORT_NEW
}EmReportType;
enum
{
    RESULT_NO_SELECTED,
    RESULT_OK,
    RESULT_FAIL,
    RESULT_OUTRANGE

};
typedef   enum
{
    QA_TG18_OIQ_NORMAL,
#ifdef USG_QA_TG18_MP
    QA_TG18_MP,
#endif
    QA_TG18_CT,
    QA_TG18_UN80,

    QA_TG18_UN10,
    QA_TG18_LN,
    QA_TG18_UNL80,
    QA_TG18_UNL10,
    QA_TG18_ANG,    
    QA_TG18_CHEST,
    QA_TG18_KNEE,
    QA_TG18_MAM01,
    QA_TG18_MAM02,
    QA_TG18_OIQ_EVERY,
    QA_TG18_UN80_CONSTANCY,
    QA_TG18_END
}EmTg18Type;
typedef enum
{
    QA_METHOD_ACCEPTANCE_ALL,
    QA_METHOD_ACCEPTANCE_VISIBLE,
    QA_METHOD_CONSTANCY_ALL,
    QA_METHOD_CONSTANCY_VISIBLE,
    QA_METHOD_SINGLE,
    QA_METHOD_CLINICAL_ALL,
    QA_METHOD_CLINICAL_PART

}EmTg18MethodType;
typedef enum
{
    SENSOR_LUMINANCE,
    SENSOR_ILLuMINANCE
}EmSensorType;
typedef union
{
    int nResult[9];
    double dbLuminace[DICOM_GSDF_GRAYSCALE_NUMBER*3];
}UnTg18TypeResult;
typedef struct
{
    EmTg18Type emType;
    UnTg18TypeResult dataResult;
}StTg18Result;
typedef struct _ST_QA_CHECK_CONDITION_
{

    int nPixelTypeA;
    int nPixelTypeB;
    int nPixelTypeC;
    double dbSafeCoefficient;
    double dbContrast;
    double dbLuminaceMax;
    double dbUniformDevation;
    double dbChormaticityGreyscaleDevation;
    double dbLuinacneDevation;
   
    double dbMultipleDeviation;
    double dbChromaticityDeviation;
     double dbMultipleChromaticityDeviation;
    double dbBasciLuminaceR=250;

    double dbAverageView=0.85;
    QString strResult;
    _ST_QA_CHECK_CONDITION_()
    {
        nPixelTypeA=0;
        nPixelTypeB=0;
        nPixelTypeC=0;

         dbSafeCoefficient=0.4;
         dbContrast=0;
         dbLuminaceMax=0;
         dbUniformDevation=0;
         dbLuinacneDevation=0;
          dbBasciLuminaceR=250;
          dbSafeCoefficient=0.4;
          dbAverageView=0.85;
          dbLuminaceMax=170;
          dbMultipleDeviation=0.1;
          dbChromaticityDeviation=0.0046;
          dbMultipleChromaticityDeviation=0.0029;
          dbChormaticityGreyscaleDevation=0.01;
         strResult="OK";
    }
    void InitialConditionType(EmReportQaType qaType)
    {

        switch (qaType)
        {
        case QA_ACCEPTANCE:
        case QA_ACCEPTANCE_NEW:
        case QA_CONSTANCY:
        case QA_CONSTANCY_NEW:
        {
            nPixelTypeA=1;
            nPixelTypeB=1;
            nPixelTypeC=2;
            dbAverageView=0.9;
            dbBasciLuminaceR=250;
            dbSafeCoefficient=0.4;
            dbLuminaceMax=170;
            dbLuinacneDevation=0.15;
             dbChromaticityDeviation=0.0046;
             dbMultipleChromaticityDeviation=0.0029;
             dbMultipleDeviation=0.1;
            dbChromaticityDeviation=0.0046;
            dbMultipleChromaticityDeviation=0.0029;
           dbUniformDevation=30;
           dbChormaticityGreyscaleDevation=0.01;
       }
                break;


        default:
            break;

        }

    }
    bool checkDataStatus(){return strResult=="OK";}
}StQaCheckCondition;

struct stSqlOperatorBase
{
      QDateTime* pDateTimeBegin;
      QString* pStringBegin;
      int*  pIntBegin;
      double* pDoubleBegin;
      int nDataTimeCount;
      int nStringCount;
      int nIntCount;
      int nDoubleCount;
      QDateTime* getDateTimeBegin(){return pDateTimeBegin; }
      QString* getStringBegin(){return pStringBegin; }
      int* getIntBegin(){return pIntBegin;}
      double* getDoubleBegin(){return pDoubleBegin; }
      virtual void intialPointer()
      {
          pDateTimeBegin=NULL;
           pStringBegin=NULL;
           pIntBegin=NULL;
           pDoubleBegin=NULL;
           nDataTimeCount=0;
            nStringCount=0;
            nIntCount=0;
            nDoubleCount=0;

      };
      stSqlOperatorBase()
      {

     intialPointer();
      }
       stSqlOperatorBase& operator=( stSqlOperatorBase& data)
      {
          this->intialPointer();
          data.intialPointer();
          if(pDateTimeBegin!=NULL)
          {
              for (int i=0;i<nDataTimeCount;i++)
              {
                 pDateTimeBegin[i]=data.pDateTimeBegin[i];
              }
          }
          if(pStringBegin!=NULL)
          {
              for (int i=0;i<nStringCount;i++)
              {
                pStringBegin[i]=data.pStringBegin[i];
              }
          }
          if(pIntBegin!=NULL)
          {
              for (int i=0;i<nIntCount;i++)
              {
                  pIntBegin[i]=data.pIntBegin[i];

              }
          }
          if(pDoubleBegin!=NULL)
          {
              for (int i=0;i<nDoubleCount;i++)
              {
                  pDoubleBegin[i]=data.pDoubleBegin[i];

              }
          }
          intialPointer();
      }


};


typedef struct _ST_QA_RESULT_ :public stSqlOperatorBase
{
    QDateTime dateCreate;
     QString strDisplay;
     QString strSerialNumber;
    QString strName;
    QString strType;
    QString strResult;
    QString strReason;

    int nDisplayQaGrayscaleLuminace;
    int nWorkStationInformation;
    int nTestSetup;
    int nLuminanceSensor;
    int nIlluminanceSensor;
    int  nDisplayInfor;
    int  nVisualEvaluationData;
    int nBasicLuminanceData;
    int nLuminanceDeviationData;
    int nAngularView;
    int nChromaticityEvaluation;
    int nGreyscaleChromaticityEvaluation;
     _ST_QA_RESULT_()
    {
     dateCreate=QDateTime::currentDateTime();
         strName="";
         strSerialNumber="";
         strReason="";
         strType="";
         strDisplay="";
         strResult="";
        nDisplayQaGrayscaleLuminace=0;
        nWorkStationInformation=0;
        nTestSetup=0;
        nDisplayInfor=0;
        nVisualEvaluationData=0;
        nBasicLuminanceData=0;
        nLuminanceDeviationData=0;
         nLuminanceSensor=0;
         nIlluminanceSensor=0;
         nAngularView=0;
         nChromaticityEvaluation=0;
         nGreyscaleChromaticityEvaluation=0;
         intialPointer();
    };
    virtual void intialPointer()
    {
stSqlOperatorBase::intialPointer();
        pDateTimeBegin=&dateCreate;
        pStringBegin=&strDisplay;
        pIntBegin=&nDisplayQaGrayscaleLuminace;
        pDoubleBegin=NULL;
        nDataTimeCount=1;
        nStringCount=6;
        nIntCount=12;
        nDoubleCount=0;
    }

     _ST_QA_RESULT_& operator=(const _ST_QA_RESULT_& data)
     {
         this->dateCreate=data.dateCreate;
         this->strDisplay=data.strDisplay;
         this->strSerialNumber=data.strSerialNumber;
         this->strName=data.strName;
         this->strType=data.strType;
         this->strResult=data.strResult;
         this->strReason=data.strReason;
         this->nDisplayQaGrayscaleLuminace=data.nDisplayQaGrayscaleLuminace;
         this->nWorkStationInformation=data.nWorkStationInformation;
         this->nTestSetup=data.nTestSetup;
         this->nLuminanceSensor=data.nLuminanceSensor;
         this->nIlluminanceSensor=data.nIlluminanceSensor;
         this->nDisplayInfor=data.nDisplayInfor;
         this->nVisualEvaluationData=data.nVisualEvaluationData;
         this->nBasicLuminanceData=data.nBasicLuminanceData;
         this->nLuminanceDeviationData=data.nLuminanceDeviationData;
         this->nAngularView=data.nAngularView;
         this->nChromaticityEvaluation=data.nChromaticityEvaluation;
         this->nGreyscaleChromaticityEvaluation=data.nGreyscaleChromaticityEvaluation;
     }

}StQaResult;

typedef struct _ST_ANGULAR_VIEW_ :public stSqlOperatorBase
{

    int nTopLeft;
    int nTopMiddle;
    int nTopRight;
    int  nMiddleLeft;
    int  nMiddleCenter;
    int nMiddleRight;
    int nBottomLeft;
    int nBottomMiddle;
    int nBottomRight;
    double dbAverageValue;
     _ST_ANGULAR_VIEW_():stSqlOperatorBase()
    {

          nTopLeft=0;
          nTopMiddle=0;
          nTopRight=0;
           nMiddleLeft=0;
           nMiddleCenter=0;
          nMiddleRight=0;
          nBottomLeft=0;
          nBottomMiddle=0;
          nBottomRight=0;
        dbAverageValue=0.0;;
         intialPointer();
    };
    virtual void intialPointer()
    {
      stSqlOperatorBase::intialPointer();

        pIntBegin=&nTopLeft;
        pDoubleBegin=&dbAverageValue;

        nIntCount=9;
        nDoubleCount=1;
    }
     double getAverage()
     {
         intialPointer();
         dbAverageValue=0;
         for (int i=0;i<nIntCount;i++) {
             dbAverageValue+=(double)pIntBegin[i];
         }
         dbAverageValue=dbAverageValue/9;
         return dbAverageValue;

     }
 _ST_ANGULAR_VIEW_& operator=(const _ST_ANGULAR_VIEW_& data)
         {
             this->nTopLeft=data.nTopLeft;
               this->nTopMiddle=data.nTopMiddle;
               this->nTopRight=data.nTopRight;
                this->nMiddleLeft=data. nMiddleLeft;
                this->nMiddleCenter=data. nMiddleCenter;
              this-> nMiddleRight=data.nMiddleRight;
               this->nBottomLeft=data.nBottomLeft;
               this->nBottomMiddle=data.nBottomMiddle;
               this->nBottomRight=data.nBottomRight;
              this-> dbAverageValue=data.dbAverageValue;
             intialPointer();
         }

}StAngularView;

typedef struct _ST_CHROMATICITY_EVALUATION :public stSqlOperatorBase
{
    int PointNumber;

    double dbTopLeftU;
    double dbTopMiddleU;
    double dbTopRightU;
    double dbMiddleLeftU;
    double dbCenterU;
    double dbMiddleRightU;
    double dbBottomLeftU;
    double dbBottomMiddlU;
    double dbBottomRightU;

    double dbTopLeftV;
    double dbTopMiddleV;
    double dbTopRightV;
    double dbMiddleLeftV;
    double dbCenterV;
    double dbMiddleRightV;
    double dbBottomLeftV;
    double dbBottomMiddlV;
    double dbBottomRightV;

    double dbOtherDisplayCenterU;
    double dbOtherDisplayCenterV;
     _ST_CHROMATICITY_EVALUATION():stSqlOperatorBase()
    {
         PointNumber=0;
         dbTopLeftU=0.0;
         dbTopMiddleU=0.0;
         dbTopRightU=0.0;
         dbMiddleLeftU=0.0;
         dbCenterU=0.0;
         dbMiddleRightU=0.0;
         dbBottomLeftU=0.0;
         dbBottomMiddlU=0.0;
         dbBottomRightU=0.0;

         dbTopLeftV=0.0;
         dbTopMiddleV=0.0;
         dbTopRightV=0.0;
         dbMiddleLeftV=0.0;
         dbCenterV=0.0;
         dbMiddleRightV=0.0;
         dbBottomLeftV=0.0;
         dbBottomMiddlV=0.0;
         dbBottomRightV=0.0;
         dbOtherDisplayCenterU=0.0;
         dbOtherDisplayCenterV=0.0;
         intialPointer();
    };
    virtual void intialPointer()
    {
      stSqlOperatorBase::intialPointer();

      pIntBegin=&PointNumber;
      pDoubleBegin=&dbTopLeftU;
      nIntCount=1;
      nDoubleCount=20;
    }
//     double getAverage()
//     {
//         intialPointer();
//         dbAverageValue=0;
//         for (int i=0;i<nIntCount;i++) {
//             dbAverageValue+=(double)pIntBegin[i];
//         }
//         dbAverageValue=dbAverageValue/9;
//         return dbAverageValue;

//     }
 _ST_CHROMATICITY_EVALUATION& operator=(const _ST_CHROMATICITY_EVALUATION& data)
 {
     this->PointNumber=data.PointNumber;
     this->dbTopLeftU=data.dbTopLeftU;
     this->dbTopMiddleU=data.dbTopMiddleU;
     this->dbTopRightU=data.dbTopRightU;
     this->dbMiddleLeftU=data.dbMiddleLeftU;
     this->dbCenterU=data.dbCenterU;
     this->dbMiddleRightU=data.dbMiddleRightU;
     this->dbBottomLeftU=data.dbBottomLeftU;
     this->dbBottomMiddlU=data.dbBottomMiddlU;
     this->dbBottomRightU=data.dbBottomRightU;

     this->dbTopLeftV=data.dbTopLeftV;
     this->dbTopMiddleV=data.dbTopMiddleV;
     this->dbTopRightV=data.dbTopRightV;
     this->dbMiddleLeftV=data.dbMiddleLeftV;
     this->dbCenterV=data.dbCenterV;
     this->dbMiddleRightV=data.dbMiddleRightV;
     this->dbBottomLeftV=data.dbBottomLeftV;
     this->dbBottomMiddlV=data.dbBottomMiddlV;
     this->dbBottomRightV=data.dbBottomRightV;
     this->dbOtherDisplayCenterU=data.dbOtherDisplayCenterU;
     this->dbOtherDisplayCenterV=data.dbOtherDisplayCenterV;
     intialPointer();
 }

}StChromaticityEvaluation;

typedef struct _ST_GREYSCALE_CHROMATICITY_EVALUATION :public stSqlOperatorBase
{
    double dbCurrtCoordinate_u[DICOM_GSDF_GRAYSCALE_NUMBER];
    double dbCurrtCoordinate_v[DICOM_GSDF_GRAYSCALE_NUMBER];

     _ST_GREYSCALE_CHROMATICITY_EVALUATION():stSqlOperatorBase()
    {
         for(int i=0;i<DICOM_GSDF_GRAYSCALE_NUMBER;i++)
         {
             dbCurrtCoordinate_u[i]=0.0;
             dbCurrtCoordinate_v[i]=0.0;
         }
         intialPointer();
    };
    virtual void intialPointer()
    {
      stSqlOperatorBase::intialPointer();

        pDoubleBegin=&dbCurrtCoordinate_u[0];
        nDoubleCount=36;
    }
//     double getAverage()
//     {
//         intialPointer();
//         dbAverageValue=0;
//         for (int i=0;i<nIntCount;i++) {
//             dbAverageValue+=(double)pIntBegin[i];
//         }
//         dbAverageValue=dbAverageValue/9;
//         return dbAverageValue;

//     }
 _ST_GREYSCALE_CHROMATICITY_EVALUATION& operator=(const _ST_GREYSCALE_CHROMATICITY_EVALUATION& data)
 {
     for(int i=0;i<DICOM_GSDF_GRAYSCALE_NUMBER;i++)
     {
         this->dbCurrtCoordinate_u[i]=data.dbCurrtCoordinate_u[i];
         this->dbCurrtCoordinate_v[i]=data.dbCurrtCoordinate_v[i];
     }
     intialPointer();
 }

}StGreyscaleChromaticityEvaluation;

//定义Gamma曲线类型
typedef enum _EM_CURVE_TYPE_
{
    CURVE_GAMMA=0,//标准的gamma曲线类型
    CURVE_DICOM, //标准的Dicom曲线标准
    CURVE_CIE,	 //标准的CIE曲线标准
    CURVE_OUT_RANGE //定义类型上限
}emCurveType;



typedef struct _ST_AQ_LUMINANCE_
{
     emCurveType emCurveValue;	//定义标准Gamma曲线类型
     double AmbientLuminace;
     double dbGamma;
    double dbCurentLuminace[DICOM_GSDF_GRAYSCALE_NUMBER];

    _ST_AQ_LUMINANCE_()
    {
        emCurveValue=CURVE_DICOM;
        AmbientLuminace=0;
        dbGamma=2.2;

        for(int i=0;i<DICOM_GSDF_GRAYSCALE_NUMBER;i++)
        {
            dbCurentLuminace[i]=0.0;
        }
    }

}StQaLuminace;


typedef struct
{
    int OverallTestResultIndex;
    int AutoTestCommentIndex;
    QString TestCommentStr;
}OverviewData; //Overview页面

typedef struct
{
    QString TestCompany;
    QString Tester;
    QString TestReason;
    QString TestDate;
    QString TestId;
    QString TestSetup;
    int DisplayCalibratedIndex;

    QString QASoftwareVendor;
    QString QASoftwareName;
    QString QASoftwareVersion;

}Test_Setup_Data; //Test setup页面

typedef struct _DEVICE_SENSOR_
{
    int MeasuringDeviceIndex;
    int interfaceIndex;
    QString Manufacturer;
    QString Model;
    QString SN;
    EmSensorType SensorType;
     _DEVICE_SENSOR_()
    {
        MeasuringDeviceIndex=0;
        interfaceIndex=0;
        Manufacturer="";
        Model="";
        SN="";

    }

 }Device_Sensor;


typedef struct _BASELINE_SENSOR_DATA_
{

    Device_Sensor LuminceSensorInfo;
    Device_Sensor IIIuminceSensorInfo;
    _BASELINE_SENSOR_DATA_()
    {
        LuminceSensorInfo.SensorType=SENSOR_LUMINANCE;
        IIIuminceSensorInfo.SensorType=SENSOR_ILLuMINANCE;
    }

}Baseline_Sensor_Data; //Test sensor与Baseline sensors页面

typedef struct
{
    Test_Setup_Data TestSetupInfo;
    Baseline_Sensor_Data TestSensorsInfo;
    Baseline_Sensor_Data BaselineSensorsInfo;
}QASetupData;

typedef struct
{
    QString WorkstationName;
    QString WorkstationID;
    QString Location;
    QString Description;
    QString ComputerName;
    QString Manufacturer;
    QString SN;
    QString ImagingDev;   
}Workstation_Data;//Workstation页面数据

typedef struct _DISPLAY_NAME_DATA_
{
    QString DisplayName;
    int DisplayID;
    QString DisplayManufacturer;
    QString ModelName;
    QString SN;
    QString DisplayController;
    QString DriverVersion;
    int DisplayTypeIndex;
    int DispalyColorIndex;
    double DiagonalSize;
    int DisplayWidth;
    int DisplayHeight;
    double PixelPitch;
    int DisplayOrentationIndex;
    bool blIsDiagnostic;

_DISPLAY_NAME_DATA_()
{
     DisplayName="";
     DisplayID=0;
    QString DisplayManufacturer="";
    QString ModelName="";
    QString SN="";
    QString DisplayController="";
    QString DriverVersion="";
     DisplayTypeIndex=0;
     DispalyColorIndex=0;
     DiagonalSize=0;
     DisplayWidth=0;
     DisplayHeight=0;
     PixelPitch=0;
     DisplayOrentationIndex=0;
     blIsDiagnostic=false;

}
}DisplayName_Data;//Dispaly页面


typedef struct _VISUAL_EVALUATION_DATA_
{
    enum
    {
        OVERALL_QUALITY,
        GRASCALE_RESOLUTION,
        LUMINANCE_RESPOSE,
        LUMINCE_UNIFORMITY,
        CHROMATICITY

    };
    enum
    {
        PIXEL_FAULTS_TYPE_A=0,
        PIXEL_FAULTS_TYPE_B,
        PIXEL_FAULTS_TYPE_C,
        PIXEL_FAULTS_TYPE_RESULT
    };
    int ViasulEvaluationIndex[5];
    int PixelFaultsData[4];

    int ImageResultIndex;
    QString ReferenceImage;
    QString Assessor;   
    QString AssessmentNotes;

    _VISUAL_EVALUATION_DATA_()
    {

         ViasulEvaluationIndex[0]=0;
         ViasulEvaluationIndex[1]=0;
         ViasulEvaluationIndex[2]=0;
         ViasulEvaluationIndex[3]=0;
         ViasulEvaluationIndex[4]=0;
         PixelFaultsData[0]=0;
         PixelFaultsData[1]=0;
         PixelFaultsData[2]=0;
         PixelFaultsData[3]=0;
         ImageResultIndex=0;
         ReferenceImage="";
         Assessor="";

         AssessmentNotes="";


    }
}Visual_Evaluation_Data;//Visual evaluation页面


typedef struct _BASIC_LUMINANCE_DATA_
{



    double llluminanceE0;
    QString details;
    double DiffusionCoefficient;
    double Lamb;
    int AmbientType;
    double DisplayLuminanceMin;
    double DisplayLuminanceMax;
    int BasicLuminanceIndex;
    _BASIC_LUMINANCE_DATA_()
    {
         llluminanceE0=0;
         details="";
         DiffusionCoefficient=0;
         Lamb=0;
         AmbientType=0;
         DisplayLuminanceMin=0;
         DisplayLuminanceMax=0;
         BasicLuminanceIndex=0;

    }
}Basic_Luminance_Data;//Basic luminanace与baseline I页面

typedef struct _LUMINANCE_DEVIATION_DATA_
{
    double TopLeftLum;
    double TopMiddleLum;
    double TopRightLum;
     double MiddleLeftLum;
    double CenterLum;
     double MiddleRightLum;
    double BottomLeftLum;
    double BottomMiddleLum;
    double BottomRightLum;   
    int SingleDisplayResultIndex;
    double HLmax;
    double LLmax;    
    int AllDisplayResultIndex;
    int PointNumber;
    _LUMINANCE_DEVIATION_DATA_()
    {
         TopLeftLum=0;
         TopMiddleLum=0;
         TopRightLum=0;
         MiddleLeftLum=0;
         CenterLum=0;
         MiddleRightLum=0;
         BottomLeftLum=0;
         BottomMiddleLum=0;
         BottomRightLum=0;
         SingleDisplayResultIndex=0;
         HLmax=0;
         LLmax=0;
         AllDisplayResultIndex=0;
         PointNumber=9;
    }

}Luminance_Deviation_Data;//Luminance deviation页面

typedef struct
{
    DisplayName_Data DisplayNameInfo;
    Visual_Evaluation_Data VisualEvaluationInfo;
    Basic_Luminance_Data BasicLuminanceInfo;    
    Luminance_Deviation_Data LuminanceDeviationInfo;
    StQaLuminace stGrayscaleQaInfo;
    StAngularView AngularViewInfo;
    StChromaticityEvaluation ChromaticityEvaluationInfo;
    StGreyscaleChromaticityEvaluation GreyscaleChromaticityInfo;
}Display_Data;

typedef struct
{

    EmReportQaType  ReportQaType;
    StQaCheckCondition CheckCondition;
    OverviewData OverviewInfo;
    QASetupData QaSetupInfo;
    Workstation_Data WorkstationInfo;
    Display_Data DisplayInfo;
    StQaResult QaResult;

}StIecReport;//Dispaly页面


typedef struct _STRUCT_CIE_LVXY_
{
    double dbLumin;
    double dbX;
    double dbY;
    /*
    struct _STRUCT_CIE_LVXY_()
    {
        dbLumin=0.0;
        dbX=0.0;
        dbY=0.0;

    }
    */
}StCieLvxy;
typedef struct _STRUCT_COLOR_GAMMA_
{
    long lgGammaR;
    long lgGammaG;
    long lgGammaB;
  //  public:
   // friend QDataStream& operator<<(QDataStream &out, _STRUCT_COLOR_GAMMA_ &pColor_gamma);
   // friend QDataStream& operator>>(QDataStream &intput, _STRUCT_COLOR_GAMMA_ &pColor_gamma);



}StructGamma;
typedef enum
{
    INDEX_DISPLAY_INFORMATION,
    INDEX_VISUAL_EVALUATION,
    INDEX_BASIC_LUMINANCE,
    INDEX_LUMINANCE_DEVIATION,
    INDEX_LUMINANCE_RESPONSE,
}EmDisplayPageIndex;

void get3DlutData();
void testRegexCapture();
void testApplyIcmm(QString strFileName);
extern QString g_strReporType[];
extern QStringList g_strListResult;
extern  unsigned char *tPCM_INPUTGAMMA[] ;

#endif // USERDEFINE_H
