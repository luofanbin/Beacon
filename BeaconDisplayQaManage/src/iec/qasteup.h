#ifndef QASTEUP_H
#define QASTEUP_H

#include <QWidget>
#include "testsetup.h"
#include "baselinesensors.h"
#include "userdefine.h"
#include "CieSensor.h"

class QaSteup : public QWidget
{
    Q_OBJECT

public:
    explicit QaSteup(QWidget *parent = 0);
    ~QaSteup();
    void ui_init();
    QASetupData GetData();
    void SetData(QASetupData *QASetupInfo);
    bool getQaResult(StQaCheckCondition &stQaCondition);

public slots:

signals:
     void  setSensor(int index);
 void getSensorInfo(StSensorInformation& cStInfor);
private:
    TestSetup *TestSetupPage;
    BaselineSensors *TestSensorsPage;

  //  BaselineSensors *BaselineSensorsPage;
};

#endif // QASTEUP_H
