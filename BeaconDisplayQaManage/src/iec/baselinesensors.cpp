#include "baselinesensors.h"
#include "ui_baselinesensors.h"

BaselineSensors::BaselineSensors(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BaselineSensors)
{
    ui->setupUi(this);
    connect(ui->Device_comboBox,SIGNAL(currentIndexChanged(int )),this,SIGNAL(setSensor(int )));
   connect(ui->pushReadSensorInor,SIGNAL(clicked()),this,SLOT(getSensorInforClick()));
   connect(this,SIGNAL(getSensorInfo(StSensorInformation&)),this,SLOT(getSensorInfotest(StSensorInformation&)));
}

BaselineSensors::~BaselineSensors()
{
    delete ui;
}

void BaselineSensors::ui_init()
{

    ui->Device_comboBox->setCurrentIndex(6);
    ui->Manufacturer_lineEdit->clear();
    ui->Model_lineEdit->clear();
    ui->SerialNumber_lineEdit->clear();

     ui->Manufacturer_lineEdit_2->clear();
    ui->Model_lineEdit_2->clear();
    ui->SerialNumber_lineEdit_2->clear();

}

void BaselineSensors::UpdatePage()
{

    update();
}

Baseline_Sensor_Data BaselineSensors::GetData()
{
    Baseline_Sensor_Data BaselineSensorsInfo;
      BaselineSensorsInfo.LuminceSensorInfo.MeasuringDeviceIndex=ui->Device_comboBox->currentIndex();
   //BaselineSensorsInfo.LuminceSensorInfo.interfaceIndex=ui->Device_comboBox->currentIndex();
     BaselineSensorsInfo.LuminceSensorInfo.Manufacturer=ui->Manufacturer_lineEdit->text();
    BaselineSensorsInfo.LuminceSensorInfo.Model=ui->Model_lineEdit->text();
    BaselineSensorsInfo.LuminceSensorInfo.SN=ui->SerialNumber_lineEdit->text();

    BaselineSensorsInfo.IIIuminceSensorInfo.Manufacturer=ui->Manufacturer_lineEdit_2->text();
    BaselineSensorsInfo.IIIuminceSensorInfo.Model=ui->Model_lineEdit_2->text();
    BaselineSensorsInfo.IIIuminceSensorInfo.SN=ui->SerialNumber_lineEdit_2->text();


    return BaselineSensorsInfo;
}

void BaselineSensors::SetData(Baseline_Sensor_Data *BaselineSensorsInfo)
{

    ui->Device_comboBox->setCurrentIndex(BaselineSensorsInfo->LuminceSensorInfo.MeasuringDeviceIndex);
   // ui->Interface_comboBox->setCurrentIndex(BaselineSensorsInfo->LuminceSensorInfo.interfaceIndex;
    ui->Manufacturer_lineEdit->setText(BaselineSensorsInfo->LuminceSensorInfo.Manufacturer);
    ui->Model_lineEdit->setText(BaselineSensorsInfo->LuminceSensorInfo.Model);
    ui->SerialNumber_lineEdit->setText(BaselineSensorsInfo->LuminceSensorInfo.SN);

      ui->Manufacturer_lineEdit_2->setText(BaselineSensorsInfo->IIIuminceSensorInfo.Manufacturer);
    ui->Model_lineEdit_2->setText(BaselineSensorsInfo->IIIuminceSensorInfo.Model);
    ui->SerialNumber_lineEdit_2->setText(BaselineSensorsInfo->IIIuminceSensorInfo.SN);

    emit setSensor(ui->Device_comboBox->currentIndex());
    return;
}
bool BaselineSensors::getQaResult(StQaCheckCondition &stQaCondition)
{
    if(!stQaCondition.checkDataStatus())
        return false;
    if(ui->Device_comboBox->currentIndex()<1)
     {
        stQaCondition.strResult=tr("Please select the sensor device for text luminace!");
        return false;
    }

    if(ui->Manufacturer_lineEdit->text().isEmpty() ||
        ui->Model_lineEdit->text().isEmpty()||
            ui->SerialNumber_lineEdit->text().isEmpty())
        {
        stQaCondition.strResult=tr("Please fill in device information!");
        return false;
        }



    return true;
}
 void  BaselineSensors::getSensorInforClick()
 {
     StSensorInformation sensor_infor;
     emit getSensorInfo(sensor_infor);

     ui->Manufacturer_lineEdit->setText(sensor_infor.strManifactor);
             ui->Model_lineEdit->setText(sensor_infor.strType);
                 ui->SerialNumber_lineEdit->setText(sensor_infor.strSn);
 }
