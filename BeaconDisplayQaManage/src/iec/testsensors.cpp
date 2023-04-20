#include "testsensors.h"
#include "ui_testsensors.h"

TestSensors::TestSensors(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TestSensors)
{
    ui->setupUi(this);
}

TestSensors::~TestSensors()
{
    delete ui;
}

Test_Sensors_Data TestSensors::GetTestSensorsPageData()
{
    Test_Sensors_Data TestSetupInfo;
    TestSetupInfo.LuminceSensorInfo.MeasuringDeviceIndex=ui->Device_comboBox_1->currentIndex();
    TestSetupInfo.LuminceSensorInfo.interfaceIndex=ui->Interface_comboBox_1->currentIndex();
    TestSetupInfo.MeasuringMethodIndex=ui->MeasuringMethod_comboBox_1->currentIndex();
    TestSetupInfo.LuminceSensorInfo.Manufacturer=ui->Manufacturer_lineEdit_1->text();
    TestSetupInfo.LuminceSensorInfo.Model=ui->Model_lineEdit_1->text();
    TestSetupInfo.LuminceSensorInfo.SN=ui->SerialNumber_lineEdit_1->text();
    TestSetupInfo.LuminceSensorInfo.NextCalibraDate=ui->NextCalibration_lineEdit_1->text();
    TestSetupInfo.IIIuminceSensorInfo.MeasuringDeviceIndex=ui->Device_comboBox_2->currentIndex();
    TestSetupInfo.IIIuminceSensorInfo.interfaceIndex=ui->Interface_comboBox_2->currentIndex();
    TestSetupInfo.IIIuminceSensorInfo.Manufacturer=ui->Manufacturer_lineEdit_2->text();
    TestSetupInfo.IIIuminceSensorInfo.Model=ui->Model_lineEdit_2->text();
    TestSetupInfo.IIIuminceSensorInfo.SN=ui->SerialNumber_lineEdit_2->text();
    TestSetupInfo.IIIuminceSensorInfo.NextCalibraDate=ui->NextCalibration_lineEdit_2->text();
    TestSetupInfo.BasicLumMethodIndex=ui->BasicLumMethod_comboBox_1->currentIndex();
    TestSetupInfo.LumResponseMethodIndex=ui->LumResponseMethod_comboBox_1->currentIndex();
    TestSetupInfo.LumUniformityMethodIndex=ui->LumUniformityMethod_comboBox_1->currentIndex();

    return  TestSetupInfo;
}

void TestSensors::SetTestSensorsPageData(Test_Sensors_Data *TestSensorsInfo)
{

}
