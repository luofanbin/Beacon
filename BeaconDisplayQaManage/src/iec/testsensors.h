#ifndef TESTSENSORS_H
#define TESTSENSORS_H

#include <QWidget>

namespace Ui {
class TestSensors;
}

typedef struct
{
    int MeasuringDeviceIndex;
    int interfaceIndex;
    QString Manufacturer;
    QString Model;
    QString SN;
    QString NextCalibraDate;
}IIIumince_Sensor;

typedef struct
{
    IIIumince_Sensor LuminceSensorInfo;
    int MeasuringMethodIndex;
    IIIumince_Sensor IIIuminceSensorInfo;
    int BasicLumMethodIndex;
    int LumResponseMethodIndex;
    int LumUniformityMethodIndex;
}Test_Sensors_Data; //Test sensor页面数据


class TestSensors : public QWidget
{
    Q_OBJECT

public:
    explicit TestSensors(QWidget *parent = 0);
    ~TestSensors();
    Test_Sensors_Data GetTestSensorsPageData();
    void SetTestSensorsPageData(Test_Sensors_Data *TestSensorsInfo);

private:
    Ui::TestSensors *ui;
};

#endif // TESTSENSORS_H
