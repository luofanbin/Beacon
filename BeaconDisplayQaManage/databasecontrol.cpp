#include "databasecontrol.h"
#include "testimage.h"
#include <QApplication>
#include <QScreen>
#include <QDesktopWidget>
QSqlDatabase DatabaseControl::m_dateBase;
typedef enum
{
    DATA_TYPE_VARCHAR=0, //varchar
    DATA_TYPE_INTEGER,//integer
    DATA_TYPE_DOUBLE,//double
    DATA_TYPE_DATETIME,//datetime

}EmDataType;
typedef struct
{
    QString name;
    EmDataType type;

}StDataBaseItem;
StDataBaseItem Table_History_Table[]={
{"test_time",DATA_TYPE_DATETIME}
,{"display_name",DATA_TYPE_VARCHAR}
,{"serial_number",DATA_TYPE_VARCHAR}
,{"operator_name",DATA_TYPE_VARCHAR}
,{"standard_type",DATA_TYPE_VARCHAR}
,{"status",DATA_TYPE_VARCHAR}
,{"reason",DATA_TYPE_VARCHAR}
,{"Display_Qa_Grayscale_Luminace",DATA_TYPE_INTEGER}
,{"WorkStaion_Information",DATA_TYPE_INTEGER}
,{"Test_Setup",DATA_TYPE_INTEGER}
,{"LuminanceSensor",DATA_TYPE_INTEGER}
,{"IllLuminaceSensor",DATA_TYPE_INTEGER}
,{"Display_Infor",DATA_TYPE_INTEGER}
,{"Visual_Evaluation_Data",DATA_TYPE_INTEGER}
,{"Basic_Luminance_Data",DATA_TYPE_INTEGER}
,{"Luminance_Deviation_Data",DATA_TYPE_INTEGER}
,{"Angular_View",DATA_TYPE_INTEGER}
,{"Chromaticity_Evaluation",DATA_TYPE_INTEGER}
,{"Greyscale_Chromaticity_Evaluation",DATA_TYPE_INTEGER}
 };

StDataBaseItem Table_Angular_View[]={
{"top_left",DATA_TYPE_INTEGER}
,{"top_mid",DATA_TYPE_INTEGER}
,{"top_right",DATA_TYPE_INTEGER}
,{"middle_left",DATA_TYPE_INTEGER}
,{"middle_center",DATA_TYPE_INTEGER}
,{"middle_right",DATA_TYPE_INTEGER}
,{"bottom_left",DATA_TYPE_INTEGER}
,{"bottom_middle",DATA_TYPE_INTEGER}
,{"bottom_right",DATA_TYPE_INTEGER}
,{"average_value",DATA_TYPE_DOUBLE}
};

StDataBaseItem Table_Chromaticity_Evaluation[]={
{"PointNumber",DATA_TYPE_INTEGER}
,{"top_left_u",DATA_TYPE_DOUBLE}
,{"top_mid_u",DATA_TYPE_DOUBLE}
,{"top_right_u",DATA_TYPE_DOUBLE}
,{"middle_left_u",DATA_TYPE_DOUBLE}
,{"middle_center_u",DATA_TYPE_DOUBLE}
,{"middle_right_u",DATA_TYPE_DOUBLE}
,{"bottom_left_u",DATA_TYPE_DOUBLE}
,{"bottom_middle_u",DATA_TYPE_DOUBLE}
,{"bottom_right_u",DATA_TYPE_DOUBLE}
,{"top_left_v",DATA_TYPE_DOUBLE}
,{"top_mid_v",DATA_TYPE_DOUBLE}
,{"top_right_v",DATA_TYPE_DOUBLE}
,{"middle_left_v",DATA_TYPE_DOUBLE}
,{"middle_center_v",DATA_TYPE_DOUBLE}
,{"middle_right_v",DATA_TYPE_DOUBLE}
,{"bottom_left_v",DATA_TYPE_DOUBLE}
,{"bottom_middle_v",DATA_TYPE_DOUBLE}
,{"bottom_right_v",DATA_TYPE_DOUBLE}
,{"other_display_u",DATA_TYPE_DOUBLE}
,{"other_display_v",DATA_TYPE_DOUBLE}
};

StDataBaseItem Table_Greyscale_Chromaticity_Evaluation[]={
{"LN01_u",DATA_TYPE_DOUBLE}
,{"LN02_u",DATA_TYPE_DOUBLE}
,{"LN03_u",DATA_TYPE_DOUBLE}
,{"LN04_u",DATA_TYPE_DOUBLE}
,{"LN05_u",DATA_TYPE_DOUBLE}
,{"LN06_u",DATA_TYPE_DOUBLE}
,{"LN07_u",DATA_TYPE_DOUBLE}
,{"LN08_u",DATA_TYPE_DOUBLE}
,{"LN09_u",DATA_TYPE_DOUBLE}
,{"LN10_u",DATA_TYPE_DOUBLE}
,{"LN11_u",DATA_TYPE_DOUBLE}
,{"LN12_u",DATA_TYPE_DOUBLE}
,{"LN13_u",DATA_TYPE_DOUBLE}
,{"LN14_u",DATA_TYPE_DOUBLE}
,{"LN15_u",DATA_TYPE_DOUBLE}
,{"LN16_u",DATA_TYPE_DOUBLE}
,{"LN17_u",DATA_TYPE_DOUBLE}
,{"LN18_u",DATA_TYPE_DOUBLE}
,{"LN01_v",DATA_TYPE_DOUBLE}
    ,{"LN02_v",DATA_TYPE_DOUBLE}
    ,{"LN03_v",DATA_TYPE_DOUBLE}
    ,{"LN04_v",DATA_TYPE_DOUBLE}
    ,{"LN05_v",DATA_TYPE_DOUBLE}
    ,{"LN06_v",DATA_TYPE_DOUBLE}
    ,{"LN07_v",DATA_TYPE_DOUBLE}
    ,{"LN08_v",DATA_TYPE_DOUBLE}
    ,{"LN09_v",DATA_TYPE_DOUBLE}
    ,{"LN10_v",DATA_TYPE_DOUBLE}
    ,{"LN11_v",DATA_TYPE_DOUBLE}
    ,{"LN12_v",DATA_TYPE_DOUBLE}
    ,{"LN13_v",DATA_TYPE_DOUBLE}
    ,{"LN14_v",DATA_TYPE_DOUBLE}
    ,{"LN15_v",DATA_TYPE_DOUBLE}
    ,{"LN16_v",DATA_TYPE_DOUBLE}
    ,{"LN17_v",DATA_TYPE_DOUBLE}
    ,{"LN18_v",DATA_TYPE_DOUBLE}
};

DatabaseControl::DatabaseControl()
{


}
bool CreateDataBaseTable(QString strTableName,StDataBaseItem dataItem[],int nCount)
{

    QString str_create_table=QString("create table %1(id integer primary key").arg(strTableName);
    QString str_const_type[]={
        "varchar"
         ,"integer"
         ,"double"
         ,"datetime"
    };
    for (int i=0;i<nCount;i++)
    {
        str_create_table+=QString(" ,%1 %2").arg(dataItem[i].name).arg(str_const_type[dataItem[i].type]);
    }
     str_create_table+=")";
    QSqlQuery q;

    if (!q.exec(QLatin1String(str_create_table.toLatin1())))
        return false;
    return true;

}
QVariant addTableData(QString strTableName,StDataBaseItem dataItem[],int nCount,stSqlOperatorBase* pOperatorBase)
{

    QSqlQuery q;

    QString str_add_head=QString("insert into %1(%2").arg(strTableName).arg(dataItem[0].name);
    QString str_add_end="values(?";

    for (int i=1;i<nCount;i++)
    {

        str_add_head+=QString(" ,%1 ").arg(dataItem[i].name);
        str_add_end+=QString(",?");
    }

     QString str_order=QString("%1) %2)").arg(str_add_head).arg(str_add_end);
    // operator_name varchar,standard_type varchar, status varchar,reason
     qDebug()<<str_order;
    if (!q.prepare(QLatin1String(str_order.toLatin1())))
        return 0;//q.lastErrorId();

    pOperatorBase->intialPointer();
    if(pOperatorBase->pDateTimeBegin!=NULL)
    {
        for (int i=0;i<pOperatorBase->nDataTimeCount;i++)
        {
            QString str_time=pOperatorBase->pDateTimeBegin[i].toString("yyyy-dd-MM hh:mm:ss");
            q.addBindValue(pOperatorBase->pDateTimeBegin[i]);
        }
    }
    if(pOperatorBase->pStringBegin!=NULL)
    {
        for (int i=0;i<pOperatorBase->nStringCount;i++)
        {
            QString str_time=pOperatorBase->pStringBegin[i];
            q.addBindValue(pOperatorBase->pStringBegin[i]);
        }
    }
    if(pOperatorBase->pIntBegin!=NULL)
    {
        for (int i=0;i<pOperatorBase->nIntCount;i++)
        {
            q.addBindValue(pOperatorBase->pIntBegin[i]);
        }
    }
    if(pOperatorBase->pDoubleBegin!=NULL)
    {
        for (int i=0;i<pOperatorBase->nDoubleCount;i++)
        {
            q.addBindValue(pOperatorBase->pDoubleBegin[i]);
        }
    }
    q.exec();
    return q.lastInsertId();

}
bool getTableData(QString strTableName,StDataBaseItem dataItem[],int nCount,const int nId,stSqlOperatorBase* pOperatorBase)
{



    QSqlQuery query;
    if(nId!=0)
       query.exec(QString("select * from %1 where id=%2").arg(strTableName).arg(nId));
    else
        query.exec(QString("select * from %1 order by id desc limit 1").arg(strTableName));


    if (query.next())
    {
       pOperatorBase->intialPointer();
        int n_all_begin_count=0;
        if(pOperatorBase->pDateTimeBegin!=NULL)
        {
            for (int i=0;i<pOperatorBase->nDataTimeCount;i++)
            {
                pOperatorBase->pDateTimeBegin[i]=query.value(dataItem[i].name).toDateTime();
            }
        }
        n_all_begin_count=pOperatorBase->nDataTimeCount;
        if(pOperatorBase->pStringBegin!=NULL)
        {
            for (int i=0;i<pOperatorBase->nStringCount;i++)
            {
                pOperatorBase->pStringBegin[i]=query.value(dataItem[i+n_all_begin_count].name).toString();
            }
        }
         n_all_begin_count+=pOperatorBase->nStringCount;
        if(pOperatorBase->pIntBegin!=NULL)
        {
            for (int i=0;i<pOperatorBase->nIntCount;i++)
            {
                pOperatorBase->pIntBegin[i]=query.value(dataItem[i+n_all_begin_count].name).toInt();
            }
        }
        n_all_begin_count+=pOperatorBase->nIntCount;
        if(pOperatorBase->pDoubleBegin!=NULL)
        {
            for (int i=0;i<pOperatorBase->nDoubleCount;i++)
            {
                  pOperatorBase->pDoubleBegin[i]=query.value(dataItem[i+n_all_begin_count].name).toDouble();
            }
        }

        return true;
    }


    return false;

}
bool  DatabaseControl::addIecReport(const StIecReport& IecReport )
{
    StQaResult qa_result;
   qa_result=IecReport.QaResult;
   if(IecReport.ReportQaType<QA_OUTRANGE && IecReport.ReportQaType>=0)
    {
        qa_result.strType=g_strReporType[IecReport.ReportQaType];
    }
    switch (IecReport.ReportQaType) {
    case QA_VISUAL:
        break;
    case  QA_CONSTANCY_NEW:
    case  QA_ACCEPTANCE_NEW:
    {

        qa_result.nWorkStationInformation=addWorkstationInfomation(IecReport.WorkstationInfo ).toInt();
        qa_result.nTestSetup=addTestSetup(IecReport.QaSetupInfo.TestSetupInfo ).toInt();

        qa_result.nLuminanceSensor= addSensorInfomation(IecReport.QaSetupInfo.TestSensorsInfo.LuminceSensorInfo).toInt();
        qa_result.nIlluminanceSensor=addSensorInfomation(IecReport.QaSetupInfo.TestSensorsInfo.IIIuminceSensorInfo).toInt();
        qa_result.nDisplayInfor=   addDisplayNameInfomation(IecReport.DisplayInfo.DisplayNameInfo).toInt();
        if(IecReport.ReportQaType==QA_ACCEPTANCE_NEW ||
                 IecReport.ReportQaType==QA_CONSTANCY_NEW)
        {
        qa_result.nVisualEvaluationData= addVisualEvaluation(IecReport.DisplayInfo.VisualEvaluationInfo).toInt();
        qa_result.nBasicLuminanceData=   addBasicLuminanceData(IecReport.DisplayInfo.BasicLuminanceInfo).toInt();
        qa_result.nLuminanceDeviationData=  addLuminanceDeviationData(IecReport.DisplayInfo.LuminanceDeviationInfo).toInt();
        qa_result.nDisplayQaGrayscaleLuminace= addQaLuminance(IecReport.DisplayInfo.stGrayscaleQaInfo).toInt();
        qa_result.nGreyscaleChromaticityEvaluation= addGreyscaleChromaticityEvaluation(IecReport.DisplayInfo.GreyscaleChromaticityInfo).toInt();
         qa_result.nAngularView= addAngularView(IecReport.DisplayInfo.AngularViewInfo).toInt();
        qa_result.nChromaticityEvaluation=addChromaticityEvaluation(IecReport.DisplayInfo.ChromaticityEvaluationInfo).toInt();
        }
    }
    break;
    case  QA_CONSTANCY:
        break;
    default:
        return -1;

    }
    qa_result.strDisplay=IecReport.DisplayInfo.DisplayNameInfo.DisplayName;
    qa_result.strSerialNumber=IecReport.DisplayInfo.DisplayNameInfo.SN;
     qa_result.dateCreate=QDateTime::currentDateTime();
    addHistoryQa(qa_result);

}
bool DatabaseControl::getIecReport(const StQaResult &QaResult, StIecReport& IecReport)
{
    IecReport.QaResult=QaResult;
    if(QaResult.nWorkStationInformation>=0)
        getWorkstationInfomation(QaResult.nWorkStationInformation,IecReport.WorkstationInfo);

    if(QaResult.nTestSetup>=0)
        getTestSetup(QaResult.nTestSetup,IecReport.QaSetupInfo.TestSetupInfo );
    if(QaResult.nLuminanceSensor>=0)
        getSensorInfomation(QaResult.nLuminanceSensor,IecReport.QaSetupInfo.TestSensorsInfo.LuminceSensorInfo);
    if(QaResult.nIlluminanceSensor>=0)
        getSensorInfomation(QaResult.nIlluminanceSensor,IecReport.QaSetupInfo.TestSensorsInfo.IIIuminceSensorInfo);
    if(QaResult.nDisplayInfor>=0)
    {
        getDisplayNameInfomation(QaResult.nDisplayInfor,IecReport.DisplayInfo.DisplayNameInfo);
        if(QaResult.nDisplayInfor==0)
            getDisplayTableInfomation(IecReport.DisplayInfo.DisplayNameInfo);


    }
    if(QaResult.nVisualEvaluationData>=0)
        getVisualEvaluation(QaResult.nVisualEvaluationData,IecReport.DisplayInfo.VisualEvaluationInfo);

    if(QaResult.nBasicLuminanceData>=0)
        getBasicLuminanceData(QaResult.nBasicLuminanceData,IecReport.DisplayInfo.BasicLuminanceInfo);
    if(QaResult.nLuminanceDeviationData>=0)
        getLuminanceDeviationData(QaResult.nLuminanceDeviationData,IecReport.DisplayInfo.LuminanceDeviationInfo);
    if(QaResult.nDisplayQaGrayscaleLuminace>=0)
        getQaLuminance(QaResult.nDisplayQaGrayscaleLuminace,IecReport.DisplayInfo.stGrayscaleQaInfo);

    if(QaResult.nAngularView>=0)
        getAngularView(QaResult.nAngularView,IecReport.DisplayInfo.AngularViewInfo);
    if(QaResult.nChromaticityEvaluation>=0)
        getChromaticityEvaluation(QaResult.nChromaticityEvaluation,IecReport.DisplayInfo.ChromaticityEvaluationInfo);
    if(QaResult.nGreyscaleChromaticityEvaluation>=0)
        getGreyscaleChromaticityEvaluation(QaResult.nGreyscaleChromaticityEvaluation,IecReport.DisplayInfo.GreyscaleChromaticityInfo);
    if(IecReport.ReportQaType==QA_ACCEPTANCE_NEW)
    {
        getDisplayTableInfomation(IecReport.DisplayInfo.DisplayNameInfo);

    }
}

QVariant DatabaseControl::addHistoryQa(const StQaResult &QaResult)
{

    return addTableData("History",Table_History_Table,sizeof(Table_History_Table)/sizeof(StDataBaseItem),(stSqlOperatorBase* )&QaResult);
/*
    StQaResult st_qa_result;
   // getTableData("test_table_create",Table_History_Table,sizeof(Table_History_Table)/sizeof(StDataBaseItem),0,(stSqlOperatorBase* )&st_qa_result);


    QSqlQuery q;
    // operator_name varchar,standard_type varchar, status varchar,reason
    if (!q.prepare(QLatin1String("insert into History(display_name,serial_number"
                                 ", test_time"
                                 ",operator_name"
                                 ",standard_type"
                                 ",status"
                                 ",reason"
                             ", Display_Qa_Grayscale_Luminace"
                             ",WorkStaion_Information"
                             ",Test_Setup "
                             ",LuminanceSensor"
                             ",IllLuminaceSensor"
                             ",Display_Infor"
                             ",Visual_Evaluation_Data"
                             ",Basic_Luminance_Data"
                             ",Luminance_Deviation_Data)"
                             " values(?, ?,?,?,?,?,?,?,   ?,?,?,?,?,?,?,?)")))
        return 0;//q.lastErrorId();
    q.addBindValue(QaResult.strDisplay);
    q.addBindValue(QaResult.strSerialNumber);
    q.addBindValue(QDateTime::currentDateTime().toString("yyyy-dd-MM hh:mm:ss"));
    q.addBindValue(QaResult.strName);
    q.addBindValue(QaResult.strType);
    q.addBindValue(QaResult.strResult);
    q.addBindValue(QaResult.strReason);

    q.addBindValue(QaResult.nDisplayQaGrayscaleLuminace);

    q.addBindValue(QaResult.nWorkStationInformation);
    q.addBindValue(QaResult.nTestSetup);
    q.addBindValue(QaResult.nLuminanceSensor);
    q.addBindValue(QaResult.nIlluminanceSensor);
    q.addBindValue(QaResult.nDisplayInfor);
    q.addBindValue(QaResult. nVisualEvaluationData);
    q.addBindValue(QaResult.nBasicLuminanceData);
    q.addBindValue(QaResult.nLuminanceDeviationData);
    q.exec();
    return q.lastInsertId();
    */
}
bool DatabaseControl::getHistoryQa( const int nId, StQaResult &QaResult)
{
return getTableData("History",Table_History_Table,sizeof(Table_History_Table)/sizeof(StDataBaseItem),nId,(stSqlOperatorBase* )&QaResult);

  /*
    QSqlQuery q;
    // operator_name varchar,standard_type varchar, status varchar,reason
    if (!q.prepare(QLatin1String("insert into History(display_name,modified_time"
                                 ", test_time"
                                 ",operator_name"
                                 ",standard_type"
                                 ",status"
                                 ",reason"
                                 ", Display_Qa_Grayscale_Luminace"
                                 ",WorkStaion_Information"
                                 ",Test_Setup "
                                 ",LuminanceSensor"
                                 ",IllLuminaceSensor"
                                 ",Display_Infor"
                                 ",Visual_Evaluation_Data"
                                 ",Basic_Luminance_Data"
                                 ",Luminance_Deviation_Data)"
                                 " values(?, ?,?,?,?,?,?,?,   ?,?,?,?,?,?,?,?)")))
        return 0;//q.lastErrorId();
    */
/*
    QSqlQuery query;
    if(nId!=0)
       query.exec(QString("select * from History where id=%1").arg(nId));
    else
        query.exec(QString("select * from History order by id desc limit 1"));


    if (query.next())
    {
        QaResult.dateCreate=query.value("test_time").toDateTime();
        QaResult.strName=query.value("operator_name").toString();
        QaResult.strSerialNumber=query.value("serial_number").toString();
        QaResult.strType=query.value("standard_type").toString();
        QaResult.strResult=query.value("status").toString();
        QaResult.strReason=query.value("reason").toString()  ;
        QaResult.nDisplayQaGrayscaleLuminace=query.value("Display_Qa_Grayscale_Luminace").toInt() ;
        QaResult.nWorkStationInformation=query.value("WorkStaion_Information").toInt();
        QaResult.nTestSetup=query.value("Test_Setup").toInt();
        QaResult.nLuminanceSensor=query.value("LuminanceSensor").toInt();
        QaResult.nIlluminanceSensor=query.value("IllLuminaceSensor").toInt();
        QaResult.nDisplayInfor=query.value("Display_Infor").toInt();
        QaResult. nVisualEvaluationData=query.value("Visual_Evaluation_Data").toInt();
        QaResult.nBasicLuminanceData=query.value("Basic_Luminance_Data").toInt();
        QaResult.nLuminanceDeviationData=query.value("Luminance_Deviation_Data").toInt();





        return true;
    }
    return false;

*/

}
QVariant DatabaseControl::addQaLuminance( const StQaLuminace &stQaData)
{
    QSqlQuery q;
    if (!q.prepare(QLatin1String("insert into Display_Qa_Grayscale_Luminace(Curve_Type ,Ambient \
                                ,Gamma_Value  ,LN01 ,LN02  ,LN03  ,LN04  ,LN05  ,LN06  ,LN07  ,LN08 \
                                 ,LN09  ,LN10  ,LN11  ,LN12  ,LN13  ,LN14  ,LN15  ,LN16  ,LN17  ,LN18) \
                                 values(?, ?,?,?,?,?,?,? ,?, ?,?,?,?,?,?,?  ,?,? ,?,?,? )")))
        return -1;//q.lastErrorId();

    q.addBindValue(stQaData.emCurveValue);
    q.addBindValue(stQaData.AmbientLuminace);
    q.addBindValue(stQaData.dbGamma);
    for (int i=0;i<DICOM_GSDF_GRAYSCALE_NUMBER;i++) {
        q.addBindValue(stQaData.dbCurentLuminace[i]);
    }
    q.exec();
    return q.lastInsertId();
}

bool DatabaseControl::getQaLuminance( const int Id,StQaLuminace &stQaData)
{
   /* QSqlQuery q;
    if (!q.prepare(QLatin1String("insert into Display_Qa_Grayscale_Luminace(Curve_Type ,Ambient \
                                ,Gamma_Value  ,LN01 ,LN02  ,LN03  ,LN04  ,LN05  ,LN06  ,LN07  ,LN08 \
                                 ,LN09  ,LN10  ,LN11  ,LN12  ,LN13  ,LN14  ,LN15  ,LN16  ,LN17  ,LN18) \
                                 values(?, ?,?,?,?,?,?,? ,?, ?,?,?,?,?,?,?  ,?,? ,?,?,? )")))
        return -1;//q.lastErrorId();
*/

    QSqlQuery query;


    if(Id!=0)
        query.exec(QString("select * from  Display_Qa_Grayscale_Luminace where id=%1").arg(Id));
    else
        query.exec(QString("select * from Display_Qa_Grayscale_Luminace order by id desc limit 1"));
    if (query.next())
    {
        stQaData.emCurveValue=static_cast<emCurveType>(query.value("Curve_Type").toInt());
        stQaData.AmbientLuminace=query.value("Ambient").toDouble();
        stQaData.dbGamma=query.value("Gamma_Value").toDouble();
        for (int i=0;i<DICOM_GSDF_GRAYSCALE_NUMBER;i++)
        {
            stQaData.dbCurentLuminace[i]=query.value(QString("LN%1").arg(i+1,2,10,QChar('0'))).toDouble();
        }
        return true;
    }else
        return false;

}
QVariant DatabaseControl::addWorkstationInfomation(const Workstation_Data &stWorkStationInfo )
{


    QSqlQuery q;
    if (!q.prepare(QLatin1String("insert into WorkStaion_Information(WorkstationName ,WorkstationID \
                                ,Location,Description,ComputerName,Manufacturer,SN ,ImagingDev) \
                               values(?, ?,?,?,?,?,?,? )")))
        return -1;//q.lastErrorId();
    QString *p_string=(QString *)&stWorkStationInfo;
    for (int i=0;i<sizeof(Workstation_Data)/sizeof (QString);i++) {
        q.addBindValue(*p_string++);
    }

    q.exec();
    return q.lastInsertId();
}
bool DatabaseControl::getWorkstationInfomation(const int Id, Workstation_Data &stWorkStationInfo )
{

  /*
    QSqlQuery q;
    if (!q.prepare(QLatin1String("insert into WorkStaion_Information(WorkstationName ,WorkstationID \
                                ,Location,Description,ComputerName,Manufacturer,SN ,ImagingDev\
                                 ,OperatorName  ,OperatorID  ,OperatorAddr  ,ContactName  ,ContactPosition  ,ContactNotes) \
                               values(?, ?,?,?,?,?,?,? )")))
        return -1;//q.lastErrorId();
*/
  QSqlQuery query;



  if(Id!=0)
      query.exec(QString("select * from WorkStaion_Information where id=%1").arg(Id));
  else
      query.exec(QString("select * from WorkStaion_Information order by id desc limit 1"));
  if (query.next())
  {

      stWorkStationInfo.WorkstationName=query.value("WorkstationName").toString();
      stWorkStationInfo.WorkstationID=query.value("WorkstationID").toString();
      stWorkStationInfo.Location=query.value("Location").toString();
      stWorkStationInfo.Description=query.value("Description").toString();
      stWorkStationInfo.ComputerName=query.value("ComputerName").toString();
      stWorkStationInfo.Manufacturer=query.value("Manufacturer").toString();
      stWorkStationInfo.SN=query.value("SN").toString();
      stWorkStationInfo.ImagingDev=query.value("ImagingDev").toString();

      return true;
  }
  return false;
}

QVariant DatabaseControl::addTestSetup(const Test_Setup_Data &stTestSetup )
{
    QSqlQuery q;
    //create the test step data
    if (!q.prepare(QLatin1String("insert into Test_Setup(TestCompany ,Tester "
                                 ",TestReason "
                                 ",TestDate "                                
                                 ",TestSetup "
                                 ",DisplayCalibratedIndex "
                                 ",QASoftwareVendor "
                                 ",QASoftwareName "
                                 ",QASoftwareVersion )"
                                 "values(?,?,?,?,?,?,?,? , ?)" )))
        return -1;



    q.addBindValue(stTestSetup.TestCompany);
    q.addBindValue(stTestSetup.Tester);
    q.addBindValue(stTestSetup.TestReason);
    q.addBindValue(stTestSetup.TestDate);
    q.addBindValue(stTestSetup.TestSetup);
    q.addBindValue(stTestSetup.DisplayCalibratedIndex);
    q.addBindValue(stTestSetup.QASoftwareVendor);
    q.addBindValue(stTestSetup.QASoftwareName);
    q.addBindValue(stTestSetup.QASoftwareVersion);

    q.exec();
    return q.lastInsertId();}
bool DatabaseControl::getTestSetup( const int Id,Test_Setup_Data &stTestSetup )
{
    /*QSqlQuery q;
    //create the test step data
    if (!q.prepare(QLatin1String("insert into Test_Setup(TestCompany ,Tester "
                                 ",TestReason "
                                 ",TestDate "                                 
                                 ",TestSetup "
                                 ",DisplayCalibratedIndex "
                                 ",QASoftwareVendor "
                                 ",QASoftwareName "
                                 ",QASoftwareVersion "
                                 ",PresetIndex "
                                 ",WorkstationClass "
                                 ",Min_Lmax "
                                 ",Min_r "
                                 ",Min_a "
                                 ",MaxGSDFError "
                                 ",MaxDevSingleDisplay )"
                                 "values(?,?,?,?,?,?,?,? , ?,?,?,?,?,?,?,? ,?)" )))
        return -1;
    */

    QSqlQuery query;


    if(Id!=0)
        query.exec(QString("select * from Test_Setup where id=%1").arg(Id));
    else
        query.exec(QString("select * from Test_Setup order by id desc limit 1"));

    if (query.next())
    {
        stTestSetup.TestCompany=query.value("TestCompany").toString();;
        stTestSetup.Tester=query.value("Tester").toString();
        stTestSetup.TestReason=query.value("TestReason").toString();
        stTestSetup.TestDate=query.value("TestDate").toString();       
        stTestSetup.TestSetup=query.value("TestSetup").toString();
        stTestSetup. DisplayCalibratedIndex=query.value("DisplayCalibratedIndex").toInt();
        stTestSetup.QASoftwareVendor=query.value("QASoftwareVendor").toString();
        stTestSetup.QASoftwareName=query.value("QASoftwareName").toString();
        stTestSetup.QASoftwareVersion=query.value("QASoftwareVersion").toString();


        return true;
    }
    return false;




}

QVariant DatabaseControl::addSensorInfomation(const Device_Sensor &stSensorInfo )
{
    ;

    QSqlQuery q;
    if (!q.prepare(QLatin1String("insert   into Sensor_Infor(MeasuringDeviceIndex ,interfaceIndex \
                                ,SensorType,Manufacturer,Model,SN) \
                               values(?, ?,?,?,?,?)")))
        return -1;//q.lastErrorId();

    q.addBindValue(stSensorInfo.MeasuringDeviceIndex);
    q.addBindValue(stSensorInfo.interfaceIndex);
    q.addBindValue(stSensorInfo.SensorType);
    q.addBindValue(stSensorInfo.Manufacturer);
    q.addBindValue(stSensorInfo.Model);
    q.addBindValue(stSensorInfo.SN);

    q.exec();
    return q.lastInsertId();
}
bool DatabaseControl::getSensorInfomation(  const int Id,Device_Sensor &stSensorInfo )
{


   /* QSqlQuery q;
    if (!q.prepare(QLatin1String("insert or replace into Sensor_Infor(MeasuringDeviceIndex ,interfaceIndex \
                                ,SensorType,Manufacturer,Model,SN) \
                               values(?, ?,?,?,?,?)")))
        return -1;//q.lastErrorId();
*/

  QSqlQuery query;



   if(Id!=0)
       query.exec(QString("select * from Sensor_Infor where id=%1 ").arg(Id));
   else
       query.exec(QString("select * from Sensor_Infor where SensorType=%1 order by id desc limit 1 ").arg(stSensorInfo.SensorType));


   if (query.next())
   {
       stSensorInfo.MeasuringDeviceIndex=query.value("MeasuringDeviceIndex").toInt();;
       stSensorInfo.interfaceIndex=query.value("interfaceIndex").toInt();
       stSensorInfo.Manufacturer=query.value("Manufacturer").toString();
       stSensorInfo.Model=query.value("Model").toString();
       stSensorInfo.SN=query.value("SN").toString();
       stSensorInfo.SensorType=static_cast<EmSensorType>(query.value("SensorType").toInt());
       return true;
   }
   return false;


}

QVariant DatabaseControl::addDisplayNameInfomation(const DisplayName_Data &stDisplayName )
{
    QSqlQuery q;
    //create the display name
    if (!q.prepare(QLatin1String("insert or replace into Display_Name(DisplayName,DisplayID"
                                 ",DisplayManufacturer "
                                 ",ModelName "
                                 ",SN  "
                                 ",DisplayController "
                                 ",DriverVersion "
                                 ",DisplayTypeIndex"
                                 ",DispalyColorIndex "
                                 ",DiagonalSize "
                                 ",DisplayWidth "
                                 ",DisplayHeight "
                                 ",PixelPitch "
                                 ",DisplayOrentationIndex "
                                 ",Diagnostic) "
                                 " values(?,?,?,?,?,?,?,? , ?,?,?,?,?,?,?)" )))
        return -1;


    q.addBindValue(stDisplayName.DisplayName);
    q.addBindValue(stDisplayName.DisplayID);
    q.addBindValue(stDisplayName.DisplayManufacturer);
    q.addBindValue(stDisplayName.ModelName);;
    q.addBindValue(stDisplayName.SN);;
    q.addBindValue(stDisplayName.DisplayController);
    q.addBindValue(stDisplayName.DriverVersion);
    q.addBindValue(stDisplayName.DisplayTypeIndex);
    q.addBindValue(stDisplayName.DispalyColorIndex);
    q.addBindValue(stDisplayName.DiagonalSize);
    q.addBindValue( stDisplayName.DisplayWidth);
    q.addBindValue(stDisplayName.DisplayHeight);
    q.addBindValue( stDisplayName.PixelPitch);
    q.addBindValue(stDisplayName.DisplayOrentationIndex);
    q.addBindValue(stDisplayName.blIsDiagnostic);
    q.exec();
    return q.lastInsertId();
}
bool DatabaseControl::getDisplayNameInfomation( const int Id,DisplayName_Data &stDisplayName )
{
  /*  QSqlQuery q;
    //create the display name
    if (!q.prepare(QLatin1String("insert or replace into Display_Name(DisplayName,DisplayID"
                                 ",DisplayManufacturer "
                                 ",ModelName "
                                 ",SN  "
                                 ",DisplayController "
                                 ",DriverVersion "
                                 ",DisplayTypeIndex"
                                 ",DispalyColorIndex "
                                 ",DiagonalSize "
                                 ",DisplayWidth "
                                 ",DisplayHeight "
                                 ",PixelPitch "
                                 ",DisplayOrentationIndex  "
                                 ",TestResultIndex  )"
                                 " values(?,?,?,?,?,?,?,? , ?,?,?,?,?,?,?)" )))
        return -1;
    */
  QSqlQuery query;

  if(Id!=0)
      query.exec(QString("select * from Display_Name where id=%1").arg(Id));
  else
      query.exec(QString("select * from Display_Name order by id desc limit 1"));

  if (query.next())
  {
      stDisplayName.DisplayName=query.value("DisplayName").toString();
      stDisplayName.DisplayID=query.value("DisplayID").toInt();
      stDisplayName.DisplayManufacturer=query.value("DisplayManufacturer").toString();
      stDisplayName.ModelName=query.value("ModelName").toString();;
      stDisplayName.SN=query.value("SN").toString();;
      stDisplayName.DisplayController=query.value("DisplayController").toString();
      stDisplayName.DriverVersion=query.value("DriverVersion").toString();
      stDisplayName.DisplayTypeIndex=query.value("DisplayTypeIndex").toInt();
      stDisplayName.DispalyColorIndex=query.value("DispalyColorIndex").toInt();
      stDisplayName.DiagonalSize=query.value("DiagonalSize").toDouble();
      stDisplayName.DisplayWidth=query.value("DisplayWidth").toInt();
      stDisplayName.DisplayHeight=query.value("DisplayHeight").toInt();
      stDisplayName.PixelPitch=query.value("PixelPitch").toDouble();
      stDisplayName.DisplayOrentationIndex=query.value("DisplayOrentationIndex").toInt();
      stDisplayName.blIsDiagnostic=query.value("Diagnostic").toBool();
      return true;
  }
  return false;


}
bool DatabaseControl::getDisplayTableInfomation(DisplayName_Data &stDisplayName )
{
     QSqlQuery query;

        query.exec(QString("select * from Display_Table where Operated=\"Actived\""));


    if (query.next())
    {
        stDisplayName.DisplayName=query.value("DisplayName").toString();
                 //  stDisplayName.DisplayID
       stDisplayName.DisplayID=query.value("No").toInt();
        stDisplayName.DisplayManufacturer=query.value("Manufacturer").toString();
        stDisplayName.ModelName=query.value("Model_name").toString();;
        stDisplayName.SN=query.value("Serial_No").toString();;
         stDisplayName.DispalyColorIndex=query.value("Color").toInt();
         stDisplayName.DiagonalSize=query.value("Diagonal").toDouble();
        stDisplayName.blIsDiagnostic=query.value("Diagnostic").toBool();

                   QRect rect_all=QApplication::desktop()->screenGeometry(stDisplayName.DisplayID-1);
                   stDisplayName.DisplayWidth=rect_all.width();
                   stDisplayName.DisplayHeight=rect_all.height();

                   //计算点距离
                   if(rect_all.width()>10)
                   {
                       stDisplayName.PixelPitch=sqrtf(pow(stDisplayName.DiagonalSize*25.4,2)/(1+powf(1.0*rect_all.height()/rect_all.width(),2)))/rect_all.width();

                   }
                   else
                   {
                  stDisplayName.PixelPitch=0.0078;
                  }


         TestImage test_image;
         test_image.setDisplayPhysicalProperty(stDisplayName);
        return true;
    }
    return false;

}
QVariant DatabaseControl::addVisualEvaluation(const Visual_Evaluation_Data &stVisualEvaluation )
{

    QSqlQuery q;


    //create the display name
    if (!q.prepare(QLatin1String("insert or replace into Visual_Evaluation_Data(OverallQuality,GrascaleResolution"
                                 ",LuminanceRespose "
                                 ",LuminanceUniformity "
                                 ",Chromaticity  "
                                 ",PixelFaultsTypeA "
                                 ",PixelFaultsTypeB "
                                 ",PixelFaultsTypeC" ""
                                 ",PixelFaultsResult  "
                                 ",ImageResultIndex  "
                                 ",ReferenceImage  "
                                 ",Assessor  "
                                  ",AssessmentNote)"
                                 " values(?,?,?,?,?,?,?,? , ?,?,?,?,?)" )))
        return -1;
    q.addBindValue(stVisualEvaluation.ViasulEvaluationIndex[Visual_Evaluation_Data::OVERALL_QUALITY]);
    q.addBindValue(stVisualEvaluation.ViasulEvaluationIndex[Visual_Evaluation_Data::GRASCALE_RESOLUTION]);
    q.addBindValue(stVisualEvaluation.ViasulEvaluationIndex[Visual_Evaluation_Data::LUMINANCE_RESPOSE]);
    q.addBindValue(stVisualEvaluation.ViasulEvaluationIndex[Visual_Evaluation_Data::LUMINCE_UNIFORMITY]);;
    q.addBindValue(stVisualEvaluation.ViasulEvaluationIndex[Visual_Evaluation_Data::CHROMATICITY]);;
    q.addBindValue(stVisualEvaluation.PixelFaultsData[Visual_Evaluation_Data::PIXEL_FAULTS_TYPE_A]);
    q.addBindValue(stVisualEvaluation.PixelFaultsData[Visual_Evaluation_Data::PIXEL_FAULTS_TYPE_B]);
    q.addBindValue(stVisualEvaluation.PixelFaultsData[Visual_Evaluation_Data::PIXEL_FAULTS_TYPE_C]);
    q.addBindValue(stVisualEvaluation.PixelFaultsData[Visual_Evaluation_Data::PIXEL_FAULTS_TYPE_RESULT]);
    q.addBindValue(stVisualEvaluation.ImageResultIndex);
    q.addBindValue( stVisualEvaluation.ReferenceImage);
    q.addBindValue(stVisualEvaluation.Assessor);

    q.addBindValue( stVisualEvaluation.AssessmentNotes);

    q.exec();
    return q.lastInsertId();

}
bool DatabaseControl::getVisualEvaluation(const int Id, Visual_Evaluation_Data &stVisualEvaluation )
{

  /*
    //create the display name
    if (!q.prepare(QLatin1String("insert or replace into Visual_Evaluation_Data(OverallQuality,GrascaleResolution"
                                 ",LuminanceRespose "
                                 ",LuminanceUniformity "
                                 ",Chromaticity  "
                                 ",PixelFaultsTypeA "
                                 ",PixelFaultsTypeB "
                                 ",PixelFaultsTypeC" ""
                                 ",PixelFaultsResult  "
                                 ",ImageResultIndex  "
                                 ",ReferenceImage  "
                                 ",Assessor  "

                                  ",AssessmentNote"
                                 ",OverallVisualEvaluationIndex )"
                                 " values(?,?,?,?,?,?,?,? , ?,?,?,?,?,?)" )))
        return -1;
*/

    QSqlQuery query;

    if(Id!=0)
        query.exec(QString("select * from Visual_Evaluation_Data where id=%1").arg(Id));
    else
        query.exec(QString("select * from Visual_Evaluation_Data order by id desc limit 1"));

    if (query.next())
    {
        stVisualEvaluation.ViasulEvaluationIndex[Visual_Evaluation_Data::OVERALL_QUALITY]=query.value("OverallQuality").toInt();
        stVisualEvaluation.ViasulEvaluationIndex[Visual_Evaluation_Data::GRASCALE_RESOLUTION]=query.value("GrascaleResolution").toInt();
        stVisualEvaluation.ViasulEvaluationIndex[Visual_Evaluation_Data::LUMINANCE_RESPOSE]=query.value("LuminanceRespose").toInt();
        stVisualEvaluation.ViasulEvaluationIndex[Visual_Evaluation_Data::LUMINCE_UNIFORMITY]=query.value("LuminanceUniformity").toInt();;
        stVisualEvaluation.ViasulEvaluationIndex[Visual_Evaluation_Data::CHROMATICITY]=query.value("Chromaticity").toInt();;
        stVisualEvaluation.PixelFaultsData[Visual_Evaluation_Data::PIXEL_FAULTS_TYPE_A]=query.value("PixelFaultsTypeA").toInt();
        stVisualEvaluation.PixelFaultsData[Visual_Evaluation_Data::PIXEL_FAULTS_TYPE_B]=query.value("PixelFaultsTypeB").toInt();
        stVisualEvaluation.PixelFaultsData[Visual_Evaluation_Data::PIXEL_FAULTS_TYPE_C]=query.value("PixelFaultsTypeC").toInt();
        stVisualEvaluation.PixelFaultsData[Visual_Evaluation_Data::PIXEL_FAULTS_TYPE_RESULT]=query.value("PixelFaultsResult").toInt();
        stVisualEvaluation.ImageResultIndex=query.value("ImageResultIndex").toInt();
        stVisualEvaluation.ReferenceImage=query.value("ReferenceImage").toString();
        stVisualEvaluation.Assessor=query.value("Assessor").toString();      
        stVisualEvaluation.AssessmentNotes=query.value("AssessmentNote").toString();

        return true;
    }
    return false;


}

QVariant DatabaseControl::addBasicLuminanceData(const Basic_Luminance_Data &stLuminaceData )
{

    QSqlQuery q;


    //create the display name
    if (!q.prepare(QLatin1String("insert  into Basic_Luminance_Data(llluminanceE0,details"
                                 ",DiffusionCoefficient "
                                 ",Lamb "
                                 ",AmbientType  "
                                 ",DisplayLuminanceMin "
                                 ",DisplayLuminanceMax "
                                 ",BasicLuminanceIndex)"
                                 " values(?,?,?,?,?,?,?,?)" )))
        return -1;
    q.addBindValue(stLuminaceData.llluminanceE0);
    q.addBindValue(stLuminaceData.details);
    q.addBindValue(stLuminaceData.DiffusionCoefficient);
    q.addBindValue(stLuminaceData.Lamb);
    q.addBindValue(stLuminaceData.AmbientType);
    q.addBindValue(stLuminaceData.DisplayLuminanceMin);
    q.addBindValue(stLuminaceData.DisplayLuminanceMax);
    q.addBindValue(stLuminaceData.BasicLuminanceIndex);
    q.exec();
    return q.lastInsertId();

}
bool DatabaseControl::getBasicLuminanceData(const int Id, Basic_Luminance_Data &stLuminaceData )
{

  /*  QSqlQuery q;
    //create the display name
    if (!q.prepare(QLatin1String("insert  into Basic_Luminance_Data(llluminanceE0,details"
                                 ",DiffusionCoefficient "
                                 ",Lamb "
                                 ",AmbientType  "
                                 ",DisplayLuminanceMin "
                                 ",DisplayLuminanceMax "
                                 ",BasicLuminanceIndex)"
                                 " values(?,?,?,?,?,?,?,?)" )))
        return    q.exec();*/
    QSqlQuery query;

    if(Id!=0)
        query.exec(QString("select * from Basic_Luminance_Data where id=%1").arg(Id));
    else
        query.exec(QString("select * from Basic_Luminance_Data order by id desc limit 1"));

    if (query.next())
    {


        stLuminaceData.llluminanceE0=query.value("llluminanceE0").toDouble();
        stLuminaceData.details=query.value("details").toString();
        stLuminaceData.DiffusionCoefficient=query.value("DiffusionCoefficient").toDouble();
        stLuminaceData.Lamb=query.value("Lamb").toDouble();
        stLuminaceData.AmbientType=query.value("AmbientType").toInt();
        stLuminaceData.DisplayLuminanceMin=query.value("DisplayLuminanceMin").toDouble();
        stLuminaceData.DisplayLuminanceMax=query.value("DisplayLuminanceMax").toDouble();
        stLuminaceData.BasicLuminanceIndex=query.value("BasicLuminanceIndex").toInt();
        return true;
    }
    return false;

}


QVariant DatabaseControl::addLuminanceDeviationData(const Luminance_Deviation_Data &stLuminaceDeviationData )
{

    QSqlQuery q;


    //create the display name
    if (!q.prepare(QLatin1String("insert  into Luminance_Deviation_Data(TopLeftLum,TopMiddleLum,TopRightLum"
                                 ", MiddleLeftLum"
                                 ",CenterLum "
                                 ", MiddleRightLum"
                                 ",BottomLeftLum"
                                  ",BottomMiddleLum"
                                 ",BottomRightLum"
                                 ",SingleDisplayResultIndex"
                                 ",HLmax  "
                                 ",LLmax "
                                 ",AllDisplayResultIndex"
                                 ",PointNumber)"
                                 " values(?,?,?,?,?,?,?,?, ?, ?,?,?,?, ? )" )))
        return -1;
    q.addBindValue(stLuminaceDeviationData.TopLeftLum);
    q.addBindValue(stLuminaceDeviationData.TopMiddleLum);
    q.addBindValue(stLuminaceDeviationData.TopRightLum);
    q.addBindValue(stLuminaceDeviationData.MiddleLeftLum);
    q.addBindValue(stLuminaceDeviationData.CenterLum);
     q.addBindValue(stLuminaceDeviationData.MiddleRightLum);
    q.addBindValue(stLuminaceDeviationData.BottomLeftLum);
    q.addBindValue(stLuminaceDeviationData.BottomMiddleLum);
    q.addBindValue(stLuminaceDeviationData.BottomRightLum);
    q.addBindValue(stLuminaceDeviationData.SingleDisplayResultIndex);
    q.addBindValue(stLuminaceDeviationData.HLmax);
    q.addBindValue(stLuminaceDeviationData.LLmax);
    q.addBindValue(stLuminaceDeviationData.AllDisplayResultIndex);
   q.addBindValue(stLuminaceDeviationData.PointNumber);
    q.exec();
    return q.lastInsertId();
}
bool DatabaseControl::getLuminanceDeviationData(const int Id, Luminance_Deviation_Data &stLuminaceDeviationData )
{




   /* //create the display name
    if (!q.prepare(QLatin1String("insert  into Luminance_Deviation_Data(TopLeftLum,TopRightLum"
                                 ",CenterLum "
                                 ",BottomLeftLum"
                                 ",BottomRightLum"
                                 ",SingleDisplayResultIndex"
                                 ",HLmax  "
                                 ",LLmax "
                                 ",AllDisplayResultIndex)"
                                 " values(?,?,?,?,?,?,?,?, ?)" )))
        return -1;*/

   QSqlQuery query;


   if(Id!=0)
       query.exec(QString("select * from Luminance_Deviation_Data where id=%1").arg(Id));
   else
       query.exec(QString("select * from Luminance_Deviation_Data order by id desc limit 1"));
   if (query.next())
   {
       stLuminaceDeviationData.TopLeftLum=query.value("TopLeftLum").toDouble();
       stLuminaceDeviationData.TopMiddleLum=query.value("TopMiddleLum").toDouble();
    stLuminaceDeviationData.TopRightLum=query.value("TopRightLum").toDouble();
     stLuminaceDeviationData.MiddleLeftLum=query.value("MiddleLeftLum").toDouble();
    stLuminaceDeviationData.CenterLum=query.value("BottomLeftLum").toDouble();
   stLuminaceDeviationData.MiddleRightLum=query.value("MiddleRightLum").toDouble();
    stLuminaceDeviationData.BottomLeftLum=query.value("BottomRightLum").toDouble();
    stLuminaceDeviationData.BottomMiddleLum=query.value("BottomMiddleLum").toDouble();
    stLuminaceDeviationData.BottomRightLum=query.value("BottomRightLum").toDouble();
    stLuminaceDeviationData.SingleDisplayResultIndex=query.value("SingleDisplayResultIndex").toInt();
    stLuminaceDeviationData.HLmax=query.value("HLmax").toDouble();
    stLuminaceDeviationData.LLmax=query.value("LLmax").toDouble();
    stLuminaceDeviationData.AllDisplayResultIndex=query.value("AllDisplayResultIndex").toInt();
   stLuminaceDeviationData.PointNumber=query.value("PointNumber").toInt();
    return true;
   }
   return false;


}

QVariant DatabaseControl::addAngularView(const StAngularView &stAngularView )
{
return addTableData("Angular_View",Table_Angular_View,sizeof(Table_Angular_View)/sizeof(StDataBaseItem),(stSqlOperatorBase* )&stAngularView);



}

QVariant DatabaseControl::addChromaticityEvaluation(const StChromaticityEvaluation &stChromaticityEvaluation)
{
     return addTableData("Chromaticity_Evaluation",Table_Chromaticity_Evaluation,sizeof(Table_Chromaticity_Evaluation)/sizeof(StDataBaseItem),(stSqlOperatorBase* )&stChromaticityEvaluation);
}

QVariant DatabaseControl::addGreyscaleChromaticityEvaluation(const StGreyscaleChromaticityEvaluation &stQaData)
{
     return addTableData("Greyscale_Chromaticity_Evaluation",Table_Greyscale_Chromaticity_Evaluation,sizeof(Table_Greyscale_Chromaticity_Evaluation)/sizeof(StDataBaseItem),(stSqlOperatorBase* )&stQaData);
}

bool DatabaseControl::getGreyscaleChromaticityEvaluation(const int Id, const StGreyscaleChromaticityEvaluation &stQaData)
{
    return  getTableData("Greyscale_Chromaticity_Evaluation",Table_Greyscale_Chromaticity_Evaluation,sizeof(Table_Greyscale_Chromaticity_Evaluation)/sizeof(StDataBaseItem),Id,(stSqlOperatorBase* )&stQaData);
}

bool DatabaseControl::getChromaticityEvaluation(const int Id, StChromaticityEvaluation &stChromaticityEvaluation)
{
    return  getTableData("Chromaticity_Evaluation",Table_Chromaticity_Evaluation,sizeof(Table_Chromaticity_Evaluation)/sizeof(StDataBaseItem),Id,(stSqlOperatorBase* )&stChromaticityEvaluation);
}
bool DatabaseControl::getAngularView(const int Id, StAngularView &stAngularView )
 {
   return  getTableData("Angular_View",Table_Angular_View,sizeof(Table_Angular_View)/sizeof(StDataBaseItem),Id,(stSqlOperatorBase* )&stAngularView);

}

QSqlError DatabaseControl::initDb()
{
    m_dateBase = QSqlDatabase::addDatabase("QSQLITE");
    //  db.setDatabaseName(":memory:");
    m_dateBase.setDatabaseName("./qa_report.db");
    if (!m_dateBase.open())
        return m_dateBase.lastError();

    QStringList strTables = m_dateBase.tables();
    if (strTables.contains("History"))
    {
        qDebug() << "Yes";


    }
    else {
            QSqlQuery q;
                   //create Angular_View talbe for the display test
              if(!CreateDataBaseTable("Angular_View",Table_Angular_View,sizeof(Table_Angular_View)/sizeof(StDataBaseItem)))
                  return q.lastError();

              if(!CreateDataBaseTable("Chromaticity_Evaluation",Table_Chromaticity_Evaluation,sizeof(Table_Chromaticity_Evaluation)/sizeof(StDataBaseItem)))
                  return q.lastError();

              if(!CreateDataBaseTable("Greyscale_Chromaticity_Evaluation",Table_Greyscale_Chromaticity_Evaluation,sizeof(Table_Greyscale_Chromaticity_Evaluation)/sizeof(StDataBaseItem)))
                  return q.lastError();

                //create History talbe for the display test
              if(!CreateDataBaseTable("History",Table_History_Table,sizeof(Table_History_Table)/sizeof(StDataBaseItem)))
                  return q.lastError();

        /*
        if (!q.exec(QLatin1String("create table History(id integer primary key"
                                  ",display_name varchar"
                                  ",serial_number varchar"
                                  ",test_time date  "
                                  ",operator_name varchar"
                                  ",standard_type varchar"
                                  ",status varchar"
                                  ",reason varchar"
                                  ",Display_Qa_Grayscale_Luminace integer"
                                  ",WorkStaion_Information integer"
                                  ",Test_Setup integer"
                                  ",LuminanceSensor integer"
                                  ",IllLuminaceSensor integer"
                                  ",Display_Infor integer"
                                  ",Visual_Evaluation_Data integer"
                                  ",Basic_Luminance_Data integer"
                                  ",Luminance_Deviation_Data integer)")))
            return q.lastError();
*/
        if (!q.exec(QLatin1String("create table Display_Table(id integer primary key,Operated varchar,No integer,Diagnostic bool,DisplayName varchar,Manufacturer varchar,Model_name varchar,"
                                  " Serial_No varchar,Diagonal varchar,Color bool)")))
            return q.lastError();

        if (!q.exec(QLatin1String("create table Display_Qa_Grayscale_Luminace(id integer primary key,Curve_Type integer,Ambient double"
                                  ",Gamma_Value double"
                                  ",LN01 double"
                                  ",LN02 double"
                                  ",LN03 double"
                                  ",LN04 double"
                                  ",LN05 double"
                                  ",LN06 double"
                                  ",LN07 double"
                                  ",LN08 double"
                                  ",LN09 double"
                                  ",LN10 double"
                                  ",LN11 double"
                                  ",LN12 double"
                                  ",LN13 double"
                                  ",LN14 double"
                                  ",LN15 double"
                                  ",LN16 double"
                                  ",LN17 double"
                                  ",LN18 double)" )))
            return q.lastError();

        //create the workstation infrmation

        if (!q.exec(QLatin1String("create table WorkStaion_Information(id integer primary key,WorkstationName varchar,WorkstationID varchar"
                                  ",Location varchar"
                                  ",Description varchar"
                                  ",ComputerName varchar"
                                  ",Manufacturer varchar"
                                  ",SN varchar"
                                  ",ImagingDev varchar )" )))
            return q.lastError();




        //create the test step data
        if (!q.exec(QLatin1String("create table Test_Setup(id integer primary key,TestCompany varchar,Tester varchar"
                                  ",TestReason varchar"
                                  ",TestDate varchar"                                 
                                  ",TestSetup varchar"
                                  ",DisplayCalibratedIndex integer"
                                  ",QASoftwareVendor varchar"
                                  ",QASoftwareName varchar"
                                  ",QASoftwareVersion varchar)" )))
            return q.lastError();


        //create the sensor information
        if (!q.exec(QLatin1String("create table Sensor_Infor(id integer primary key,MeasuringDeviceIndex integer,interfaceIndex integer"
                                  ",SensorType integer"
                                  ",Manufacturer varchar"
                                  ",Model varchar"
                                  ",SN varchar, UNIQUE(Model, SN))" )))
            return q.lastError();



        //create the display name
        if (!q.exec(QLatin1String("create table Display_Name(id integer primary key,DisplayName varchar,DisplayID integer"
                                  ",DisplayManufacturer varchar"
                                  ",ModelName varchar"
                                  ",SN varchar "
                                  ",DisplayController varchar "
                                  ",DriverVersion varchar "
                                  ",DisplayTypeIndex integer"
                                  ",DispalyColorIndex integer "
                                  ",DiagonalSize double "
                                  ",DisplayWidth integer "
                                  ",DisplayHeight integer "
                                  ",PixelPitch double "
                                  ",DisplayOrentationIndex integer "
                                  ",Diagnostic bool"
                                  ",UNIQUE(DisplayName,ModelName, SN))" )))
            return q.lastError();


        //create the Visual_Evaluation_Data
        if (!q.exec(QLatin1String("create table Visual_Evaluation_Data(id integer primary key,OverallQuality integer,GrascaleResolution integer"
                                  ",LuminanceRespose integer"
                                  ",LuminanceUniformity integer"
                                  ",Chromaticity integer "
                                  ",PixelFaultsTypeA integer "
                                  ",PixelFaultsTypeB integer "
                                  ",PixelFaultsTypeC integer"
                                  ",PixelFaultsResult integer "
                                  ",ImageResultIndex integer "
                                  ",ReferenceImage varchar "
                                  ",Assessor varchar "
                                   ",AssessmentNote varchar)" )))
            return q.lastError();




        //create the Basic_Luminance_Data
        if (!q.exec(QLatin1String("create table Basic_Luminance_Data(id integer primary key,llluminanceE0 double,details varchar"
                                  ",DiffusionCoefficient double"
                                  ",Lamb double"
                                  ",AmbientType integer "
                                  ",DisplayLuminanceMin double "
                                  ",DisplayLuminanceMax double "
                                  ",BasicLuminanceIndex integer)" )))
            return q.lastError();




        //create the Luminance_Deviation_Data
        if (!q.exec(QLatin1String("create table Luminance_Deviation_Data(id integer primary key,TopLeftLum double,TopMiddleLum double,TopRightLum double"
                                  ",MiddleLeftLum double"
                                  ",CenterLum double"
                                  ",MiddleRightLum double"
                                  ",BottomLeftLum double"
                                  ",BottomMiddleLum double"
                                  ",BottomRightLum double "
                                  ",SingleDisplayResultIndex integer "
                                  ",HLmax double "
                                  ",LLmax double"
                                  ",AllDisplayResultIndex integer"
                                  ",PointNumber integer)" )))
            return q.lastError();
        qDebug() << "no";


    }

    return QSqlError();
    }
