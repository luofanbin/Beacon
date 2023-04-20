#ifndef DISPLAY_1_H
#define DISPLAY_1_H

#include <QObject>
#include <QWidget>
#include<QTabWidget>
#include "displayname.h"
#include "visualevaluation.h"
#include "basicluminance_baseline_i.h"
#include "luminancedeviation.h"
#include "qluminaceresponse.h"
#include "userdefine.h"
#include "testimage.h"
#include "CieSensor.h"
#include "angularview.h"
#include "basicdocument.h"
#include "greyscalechromaticityevaluation.h"
#include "chromaticityevaluation.h"
class Display_1 : public BasicDocument
{
    Q_OBJECT
public:
    explicit Display_1(QWidget *parent = 0);
    void ui_init();
    Display_Data GetData();
    void SetData(Display_Data *DisplayInfo);
    void getDataFromTestImage(TestImage* pTestImage);
    bool getQaResult(StQaCheckCondition &stQaCondition);


signals:
    void  checkQaResult();
    void notSelectSensor();
public slots:
    void QaTestAll();
    void testLuminace();
    void setSensorType(int index);
    void setDisplayTestPage(int index);
    void getSensorData(StCieLvxy &stLvxy);
    void getSensorInfo(StSensorInformation& cStInfor);
protected:
    void updateTabIterm();
    QTabWidget *DispalyTabWidget;
    DisplayName *DisplayNamePage;
    VisualEvaluation *VisualEvaluationPage;
    BasicLuminance_Baseline_I *BasicLuminancePage; 
    LuminanceDeviation *LuminanceDeviationPage;
    QLuminaceResponse *mp_LuminaceResponse;
    CCieSensor *mp_SesnorDevice;
    AngularView *mp_AngularView;
    GreyscaleChromaticityEvaluation *mp_GreyscaleChromaticityEvaluationPage;
    ChromaticityEvaluation *mp_ChromaticityEvaluationPage;
    QWidget* mp_Parent;
};

#endif // DISPLAY_1_H
