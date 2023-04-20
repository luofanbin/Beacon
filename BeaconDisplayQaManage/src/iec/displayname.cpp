#include "displayname.h"
#include "ui_displayname.h"
#include "testimage.h"
DisplayName::DisplayName(QWidget *parent) :
    BasicDocument(parent),
    ui(new Ui::DisplayName)
{
    ui->setupUi(this);
    connect(ui->QaAllTest,SIGNAL(clicked()),this,SIGNAL(QaTestAll()));
    ui->DisplayName_lineEdit->setReadOnly(true);
    ui->DisplayID_lineEdit->setReadOnly(true);
    ui->DisplayMenufacturer_lineEdit->setReadOnly(true);
    ui->DisplayModelName_lineEdit->setReadOnly(true);
    ui->DisplaySerialNum_lineEdit->setReadOnly(true);
    ui->DisplayColor_comboBox->setEnabled(false);
   connect(ui->QaClinicalTest,SIGNAL(clicked()),this,SIGNAL(QaClinicalTest()));
    ui->frame_2->setVisible(false);
}

DisplayName::~DisplayName()
{
    delete ui;
}

void DisplayName::ui_init()
{
    ui->DisplayName_lineEdit->setText(tr("Display 1"));
}

DisplayName_Data DisplayName::getData()
{
    DisplayName_Data DisplayPageInfo;
    DisplayPageInfo.DisplayName=ui->DisplayName_lineEdit->text();
    DisplayPageInfo.DisplayID=ui->DisplayID_lineEdit->text().toInt();
    DisplayPageInfo.DisplayManufacturer=ui->DisplayMenufacturer_lineEdit->text();
    DisplayPageInfo.ModelName=ui->DisplayModelName_lineEdit->text();
    DisplayPageInfo.SN=ui->DisplaySerialNum_lineEdit->text();
    DisplayPageInfo.DisplayController=ui->DisplayController_lineEdit->text();
    DisplayPageInfo.DriverVersion=ui->DriverVersion_lineEdit->text();
    DisplayPageInfo.DispalyColorIndex=ui->DisplayColor_comboBox->currentIndex();
    DisplayPageInfo.DisplayTypeIndex=ui->DisplayType_comboBox->currentIndex();
    DisplayPageInfo.DiagonalSize=ui->DiagonalCm_lineEdit->text().toDouble();
    DisplayPageInfo.DisplayWidth=ui->ResolutionX_lineEdit->text().toInt();
    DisplayPageInfo.DisplayHeight=ui->ResolutionY_lineEdit->text().toInt();
    DisplayPageInfo.PixelPitch=ui->PixelPitch_lineEdit->text().toDouble();
    DisplayPageInfo.DisplayOrentationIndex=ui->DisplayOrientation_comboBox->currentIndex();
    DisplayPageInfo.blIsDiagnostic=m_bIsDiagnostic;
    return DisplayPageInfo;
}

void DisplayName::setData(DisplayName_Data *DisplayPageInfo)
{
    ui->DisplayName_lineEdit->setText(DisplayPageInfo->DisplayName);
    ui->DisplayID_lineEdit->setText(QString::number(DisplayPageInfo->DisplayID));
    ui->DisplayMenufacturer_lineEdit->setText(DisplayPageInfo->DisplayManufacturer);
    ui->DisplayModelName_lineEdit->setText(DisplayPageInfo->ModelName);
    ui->DisplaySerialNum_lineEdit->setText(DisplayPageInfo->SN);
    ui->DisplayController_lineEdit->setText(DisplayPageInfo->DisplayController);
    ui->DriverVersion_lineEdit->setText(DisplayPageInfo->DriverVersion);
    ui->DisplayColor_comboBox->setCurrentIndex(DisplayPageInfo->DispalyColorIndex);
    ui->DisplayType_comboBox->setCurrentIndex(DisplayPageInfo->DisplayTypeIndex);
    ui->DiagonalCm_lineEdit->setText(QString::number(DisplayPageInfo->DiagonalSize,10,2));
    ui->ResolutionX_lineEdit->setText(QString::number(DisplayPageInfo->DisplayWidth));
    ui->ResolutionY_lineEdit->setText(QString::number(DisplayPageInfo->DisplayHeight));

    ui->DisplayOrientation_comboBox->setCurrentIndex(DisplayPageInfo->DisplayOrentationIndex);

    ui->PixelPitch_lineEdit->setText(QString::number(DisplayPageInfo->PixelPitch,10,5));
    m_bIsDiagnostic=DisplayPageInfo->blIsDiagnostic;
    return;
}

bool DisplayName::getQaResult(StQaCheckCondition &stQaCondition)
{
    if(!stQaCondition.checkDataStatus())
        return false;
    return true;
}

