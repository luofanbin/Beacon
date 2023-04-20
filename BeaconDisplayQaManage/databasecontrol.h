#ifndef DATABASECONTROL_H
#define DATABASECONTROL_H
#include "userdefine.h"

class DatabaseControl
{
public:
DatabaseControl();
//设置数据
 QSqlError initDb();
QVariant addHistoryQa(  const StQaResult &QaResult);
bool getHistoryQa( const int nId, StQaResult &QaResult);
bool addIecReport(const StIecReport& IecReport);
bool getIecReport(const StQaResult &QaResult, StIecReport& IecReport);
bool getDisplayTableInfomation(DisplayName_Data &stDisplayName );
//获取数据
  protected:
 QVariant addQaLuminance( const StQaLuminace &stQaData);
 QVariant addWorkstationInfomation(const Workstation_Data &stWorkStationInfo );
 QVariant addLuminanceDeviationData(const Luminance_Deviation_Data &stLuminaceDeviationData );
 QVariant addBasicLuminanceData(const Basic_Luminance_Data &stLuminaceData );
 QVariant addVisualEvaluation(const Visual_Evaluation_Data &stVisualEvaluation );
 QVariant addDisplayNameInfomation(const DisplayName_Data &stDisplayName );
 QVariant addSensorInfomation(const Device_Sensor &stSensorInfo );
 QVariant addTestSetup(const Test_Setup_Data &stTestSetup );
 QVariant addAngularView(const StAngularView &stAngularView );
 QVariant addChromaticityEvaluation(const StChromaticityEvaluation &stChromaticityEvaluation );
 QVariant addGreyscaleChromaticityEvaluation(const StGreyscaleChromaticityEvaluation &stQaData);
 bool getGreyscaleChromaticityEvaluation(const int Id, const StGreyscaleChromaticityEvaluation &stQaData );
 bool getChromaticityEvaluation(const int Id, StChromaticityEvaluation &stChromaticityEvaluation );
 bool getAngularView(const int Id, StAngularView &stAngularView );
 bool getLuminanceDeviationData(const int Id,Luminance_Deviation_Data &stLuminaceDeviationData );
 bool getBasicLuminanceData(const int Id, Basic_Luminance_Data &stLuminaceData );
 bool getVisualEvaluation(const int Id, Visual_Evaluation_Data &stVisualEvaluation );
 bool getDisplayNameInfomation(const int Id, DisplayName_Data &stDisplayName );
 bool getSensorInfomation(const int Id, Device_Sensor &stSensorInfo );
 bool getTestSetup( const int Id,Test_Setup_Data &stTestSetup );
 bool getQaLuminance(  const int Id,StQaLuminace &stQaData);
 bool getWorkstationInfomation(const int Id, Workstation_Data &stWorkStationInfo );


 protected:
     static QSqlDatabase m_dateBase;//建立数据库
};

#endif // DATABASECONTROL_H
