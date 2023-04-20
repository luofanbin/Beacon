#include "testsetup.h"
#include "ui_testsetup.h"
#include<QDate>

TestSetup::TestSetup(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TestSetup)
{
    ui->setupUi(this);

    ui_init();
}

TestSetup::~TestSetup()
{
    delete ui;
}

void TestSetup::ui_init()
{
    QDate curr_date(QDate::currentDate());
    QString CurrDateStr=curr_date.toString("yyyy-MM-dd");


    ui->TestSetup_textEdit->setText(tr("Darkened room, the light dimmed to lowest level, doors closed."));

    ui->TestDate->setDate(QDate::currentDate());

}

Test_Setup_Data TestSetup::GetData()
{
    Test_Setup_Data SaveTestData;
    SaveTestData.TestCompany=ui->PerformedBy_textEdit->toPlainText();
    SaveTestData.Tester=ui->Tester_lineEdit->text();
    SaveTestData.TestReason=ui->TestReason_lineEdit->text();
    SaveTestData.TestDate=ui->TestDate->text();
    SaveTestData.TestSetup=ui->TestSetup_textEdit->toPlainText();
    SaveTestData.DisplayCalibratedIndex=ui->DisplayCalibrated_comboBox->currentIndex();
     SaveTestData.QASoftwareVendor=ui->Vendor_lineEdit->text();
    SaveTestData.QASoftwareName=ui->QaSoftwareName_lineEdit->text();
    SaveTestData.QASoftwareVersion=ui->QaSoftwareVersion_lineEdit->text();


    return SaveTestData;
}

void TestSetup::SetData(Test_Setup_Data *TestSetupInfo)
{
    ui->PerformedBy_textEdit->setText(TestSetupInfo->TestCompany);



    ui->PerformedBy_textEdit->setText(TestSetupInfo->TestCompany);
   ui->TestReason_lineEdit->setText(TestSetupInfo->TestReason);
    ui->Tester_lineEdit->setText(TestSetupInfo->Tester);
    ui->TestDate->setDate(QDate::fromString(TestSetupInfo->TestDate,"yyyy-MM-dd"));
      ui->TestSetup_textEdit->setText(TestSetupInfo->TestSetup);
    ui->DisplayCalibrated_comboBox->setCurrentIndex(TestSetupInfo->DisplayCalibratedIndex);
    ui->Vendor_lineEdit->setText(tr("BEACON"));
    ui->QaSoftwareName_lineEdit->setText(tr("BeaconDisplayQAManager"));
    ui->QaSoftwareVersion_lineEdit->setText(QString(" %1").arg(double(SOFTWARE_VERSION),0,  'f', 2, QLatin1Char( '0' )));



}



bool TestSetup::getQaResult(StQaCheckCondition &stQaCondition)
{

    if(!stQaCondition.checkDataStatus())
        return false;
  //  if(ui->Preset_comboBox->currentIndex()<1)
    {
     //   stQaCondition.strResult=tr("Please select the preset type!");
     //   return false;
    }

    if(ui->Tester_lineEdit->text().isEmpty() ||
        ui->Vendor_lineEdit->text().isEmpty())
    {
        stQaCondition.strResult=tr("Please fill in tester information!");
        return false;
    }

    return true;
}
