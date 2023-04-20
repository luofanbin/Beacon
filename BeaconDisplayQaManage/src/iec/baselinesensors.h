#ifndef BASELINESENSORS_H
#define BASELINESENSORS_H

#include <QWidget>
#include "userdefine.h"
#include "CieSensor.h"
namespace Ui {
class BaselineSensors;
}

class BaselineSensors : public QWidget
{
    Q_OBJECT

public:
    explicit BaselineSensors(QWidget *parent = 0);
    ~BaselineSensors();
    void ui_init();
    void UpdatePage();
    Baseline_Sensor_Data GetData();
    void SetData(Baseline_Sensor_Data *BaselineSensorsInfo);
  bool getQaResult(StQaCheckCondition &stQaCondition);
   bool flag=false;
public slots:
  void  getSensorInforClick();

signals:
     void  setSensor(int index);
     void getSensorInfo(StSensorInformation& cStInfor);

private:
    Ui::BaselineSensors *ui;

};

#endif // BASELINESENSORS_H
