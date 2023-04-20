#include "workstation.h"
#include "ui_workstation.h"

Workstation::Workstation(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Workstation)
{
    ui->setupUi(this);
}

Workstation::~Workstation()
{
    delete ui;
}

void Workstation::ui_init()
{

}

Workstation_Data Workstation::GetData()
{
    Workstation_Data WorkstationPageInfo;
    WorkstationPageInfo.WorkstationName=ui->WorkstationName_lineEdit->text();
    WorkstationPageInfo.WorkstationID=ui->WorkstationID_lineEdit->text();
    WorkstationPageInfo.Location=ui->Location_Room_lineEdit->text();
    WorkstationPageInfo.Description=ui->Description_lineEdit->text();
    WorkstationPageInfo.ComputerName=ui->ComputerName_lineEdit->text();
    WorkstationPageInfo.Manufacturer=ui->WorkstationManufacturer_lineEdit->text();
    WorkstationPageInfo.SN=ui->WorkstationSN_lineEdit->text();
    WorkstationPageInfo.ImagingDev=ui->ImagingDevice_lineEdit->text();
  //  WorkstationPageInfo.OperatorName=ui->OperatorName_lineEdit->text();
  //  WorkstationPageInfo.OperatorID=ui->OperatorID_lineEdit->text();
 //   WorkstationPageInfo.OperatorAddr=ui->OperatorAddr_textEdit->toPlainText();
  //  WorkstationPageInfo.ContactName=ui->ContactName_lineEdit->text();
  //  WorkstationPageInfo.ContactPosition=ui->ContactPosition_lineEdit->text();
  //  WorkstationPageInfo.ContactNotes=ui->ContactNotes_textEdit->toPlainText();

    return WorkstationPageInfo;
}

void Workstation::SetData(Workstation_Data *WorkstationPageInfo)
{
    ui->WorkstationName_lineEdit->setText(WorkstationPageInfo->WorkstationName);
    ui->WorkstationID_lineEdit->setText(WorkstationPageInfo->WorkstationID);
    ui->Location_Room_lineEdit->setText(WorkstationPageInfo->Location);
    ui->Description_lineEdit->setText(WorkstationPageInfo->Description);
    ui->ComputerName_lineEdit->setText(WorkstationPageInfo->ComputerName);
    ui->WorkstationManufacturer_lineEdit->setText(WorkstationPageInfo->Manufacturer);
    ui->WorkstationSN_lineEdit->setText(WorkstationPageInfo->SN);
    ui->ImagingDevice_lineEdit->setText(WorkstationPageInfo->ImagingDev);

    return;
}

bool Workstation::getQaResult(StQaCheckCondition &stQaCondition)
{
    if(!stQaCondition.checkDataStatus())
        return false;

    Workstation_Data work_data;
    work_data=GetData();
    if(work_data.WorkstationName.isEmpty() ||work_data.WorkstationID.isEmpty()||
        work_data.Location.isEmpty()|| work_data.ComputerName.isEmpty()  )
    {
        stQaCondition.strResult="Please fill the workstation information!";
        return false ;
    }

    return true;
}
