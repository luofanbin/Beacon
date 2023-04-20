#include "qaiecreportinformation.h"
#include "ui_qaiecreportinformation.h"
#include "databasecontrol.h"
QaIecReportInformation::QaIecReportInformation(QWidget *parent) :
BasicDocument(NULL),
ui(new Ui::QaIecReportInformation)
{

ui->setupUi(this);
ui_layout();
ui_init();
connect(ui->buttonBox,SIGNAL(clicked(QAbstractButton*)),this ,SLOT(ClieckButtonBox(QAbstractButton*)));

connect(Display_1_Widget,SIGNAL(checkQaResult()),this,SLOT(checkQaResult()));
}

QaIecReportInformation::~QaIecReportInformation()
{
delete ui;
}
void QaIecReportInformation::ui_init()
{
    this->setWindowTitle(tr("Manage QA test reports"));
    QStringList headers;
    headers << QStringLiteral("Last modified") << QStringLiteral("Test date") << QStringLiteral("Standard")
            << QStringLiteral("Type") << QStringLiteral("Status");

    connect(OverviewWidget,SIGNAL(send_click_signal(int)),this,SLOT(slot_label_click(int)));
    connect(this,SIGNAL(setDisplayPage(int )),Display_1_Widget,SLOT(setDisplayTestPage(int )));
    connect(QASteupWidget,SIGNAL(setSensor(int )),Display_1_Widget,SLOT(setSensorType(int)));

    connect(QASteupWidget,SIGNAL(getSensorInfo(StSensorInformation&)),Display_1_Widget,SLOT(getSensorInfo(StSensorInformation&)));
    QPushButton *OkButton=ui->buttonBox->button(QDialogButtonBox::Ok);
    OkButton->setText(tr("OK"));
    QPushButton *CancelButton=ui->buttonBox->button(QDialogButtonBox::Cancel);
    CancelButton->setText(tr("Cancel"));
}
void QaIecReportInformation::ui_layout()
{

    OverviewWidget=new Overview(this);
    ui->tabWidget->addTab(OverviewWidget,tr("Overview"));
    QASteupWidget=new QaSteup(this);
    ui->tabWidget->addTab(QASteupWidget,tr("QA Setup"));
    WorkstationWidget=new Workstation(this);
    ui->tabWidget->addTab(WorkstationWidget,tr("Workstation"));
    Display_1_Widget=new Display_1(this);
    ui->tabWidget->addTab(Display_1_Widget,tr("Display"));


}


void QaIecReportInformation::SetData(StIecReport *CurrTestData)
{
    *getDocument()=*CurrTestData;
    getDocument()->CheckCondition.InitialConditionType(CurrTestData->ReportQaType);

    OverviewWidget->SetData(&CurrTestData->QaResult);
    QASteupWidget->SetData(&CurrTestData->QaSetupInfo);
    WorkstationWidget->SetData(&CurrTestData->WorkstationInfo);

    if(QA_ACCEPTANCE_NEW==CurrTestData->ReportQaType||
            QA_CONSTANCY_NEW==CurrTestData->ReportQaType)
    {
        Display_Data new_default;
        new_default.DisplayNameInfo=CurrTestData->DisplayInfo.DisplayNameInfo;
        new_default.LuminanceDeviationInfo.PointNumber=5;
        if(new_default.DisplayNameInfo.DiagonalSize>=23)
        {
            new_default.LuminanceDeviationInfo.PointNumber=9;
            new_default.ChromaticityEvaluationInfo.PointNumber=9;
        }
        Display_1_Widget->SetData(&new_default);

    }else
    {
        Display_1_Widget->SetData(&CurrTestData->DisplayInfo);
        //checkQaResult();
    }

    return;
}

StIecReport QaIecReportInformation::GetData()
{


    getDocument()->QaResult=OverviewWidget->GetData();
    getDocument()->QaSetupInfo=QASteupWidget->GetData();
    getDocument()->WorkstationInfo=WorkstationWidget->GetData();
   getDocument()->DisplayInfo=Display_1_Widget->GetData();

    return *getDocument();
}

void QaIecReportInformation::on_Acceptance_pushButton_clicked()
{
  //  ui->stackedWidget->setCurrentIndex(1);
    ui->tabWidget->setCurrentIndex(0);
    this->setWindowTitle(tr("Perform QA test"));
    QASteupWidget->ui_init();
    Display_1_Widget->ui_init();
}


void QaIecReportInformation::slot_label_click(int nIndex)
{
     ui->tabWidget->setCurrentIndex(3);
     StIecReport* p_iec_report=getDocument();
     switch (nIndex) {
     case INDEX_DISPLAY_INFORMATION:
     case INDEX_VISUAL_EVALUATION:
     case INDEX_BASIC_LUMINANCE:
         emit setDisplayPage(nIndex);
         break;
     case INDEX_LUMINANCE_DEVIATION:
         emit setDisplayPage(nIndex+1);
         break;
     case INDEX_LUMINANCE_RESPONSE:
         if((p_iec_report->ReportQaType==QA_ACCEPTANCE) || (p_iec_report->ReportQaType==QA_ACCEPTANCE_NEW))
         {
             if(p_iec_report->DisplayInfo.DisplayNameInfo.DispalyColorIndex==1)
                emit setDisplayPage(nIndex+2);
             else
                emit setDisplayPage(nIndex+1);
         }
         else
             emit setDisplayPage(nIndex-1);
         break;
     default:
         break;
     }
}


void QaIecReportInformation::on_OK_pushButton_clicked()
{
   // WriteDataToDatabase();
    emit showQaHistory();
}

void QaIecReportInformation::on_Cancel_pushButton_clicked()
{
    QMessageBox::StandardButton rb=QMessageBox::question(NULL, "Confirm", "Discard changes ?", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    if(rb == QMessageBox::Yes)
    {
      //  ui->stackedWidget->setCurrentIndex(0);
        this->setWindowTitle(tr("Manage QA test reports"));
    }
    emit showQaHistory();
}

void QaIecReportInformation::on_Apply_pushButton_clicked()
{
  //  WriteDataToDatabase();
}

void QaIecReportInformation::on_Close_pushButton_clicked()
{
    exit(0);
}
void QaIecReportInformation::ClieckButtonBox(QAbstractButton *button)
{
    StQaResult qa_result;

    DatabaseControl data_control;
    if(button== ui->buttonBox->button(QDialogButtonBox::Ok) ){


        if(getDocument()->ReportQaType==QA_ACCEPTANCE_NEW ||
                getDocument()->ReportQaType==QA_CONSTANCY_NEW)

        {
            if(checkDataStatus())
            {
            StIecReport CurrTestData;
            CurrTestData= GetData();
            data_control.addIecReport(CurrTestData);
            }
            else
                return ;
            //   data_control.addHistoryQa(CurrTestData.Display_1_Info.DisplayNameInfo.DisplayName,qa_result);
        }
    }


        emit showQaHistory();



}
bool QaIecReportInformation::checkDataStatus()
{
    StQaCheckCondition &stQaCondition=getDocument()->CheckCondition;
    stQaCondition.strResult="OK";
    StQaResult qa_result=OverviewWidget->GetData();

    getQaResult(stQaCondition);
    if(stQaCondition.checkDataStatus())
    {

        if(Display_1_Widget->getQaResult(stQaCondition))
            qa_result.strResult=g_strListResult[RESULT_OK];
        else
            qa_result.strResult=g_strListResult[RESULT_FAIL];

         OverviewWidget->SetData(&qa_result);
         return true;
    }
    else
    {
        QMessageBox::warning(this ,tr("Warning"),stQaCondition.strResult);
        return false;
    }



}
bool QaIecReportInformation::getQaResult(StQaCheckCondition &stQaCondition)
{
    if(!stQaCondition.checkDataStatus())
        return false;
    OverviewWidget->getQaResult(stQaCondition);
    Display_1_Widget->getQaResult(stQaCondition);

    QASteupWidget->getQaResult(stQaCondition);
    WorkstationWidget->getQaResult(stQaCondition);

}
