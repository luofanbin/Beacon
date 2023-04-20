#include "qasteup.h"
#include<QTabWidget>
#include<QGridLayout>

QaSteup::QaSteup(QWidget *parent) :
    QWidget(parent)
{
    QFont font("Adobe 楷体 Std R",10,QFont::Bold);
    QTabWidget *DispalyTabWidget=new QTabWidget(this);
   // DispalyTabWidget->setFont(font);
    TestSetupPage=new TestSetup(this);
    DispalyTabWidget->addTab(TestSetupPage,tr("Test setup"));
    TestSensorsPage=new BaselineSensors(this);
    TestSensorsPage->flag=true;
    TestSensorsPage->UpdatePage();
    DispalyTabWidget->addTab(TestSensorsPage,tr("Test sensors"));


    QGridLayout *MainLayout=new QGridLayout(this);
    MainLayout->addWidget(DispalyTabWidget);
    this->setLayout(MainLayout);

    connect(TestSensorsPage,SIGNAL(setSensor(int )),this,SIGNAL(setSensor(int )));
    connect(TestSensorsPage,SIGNAL(getSensorInfo(StSensorInformation&)),this,SIGNAL(getSensorInfo(StSensorInformation&)));
}

QaSteup::~QaSteup()
{

}

void QaSteup::ui_init()
{
    TestSetupPage->ui_init();

}

QASetupData QaSteup::GetData()
{
    QASetupData QaSetupInfo;
    QaSetupInfo.TestSetupInfo=TestSetupPage->GetData();
    QaSetupInfo.TestSensorsInfo=TestSensorsPage->GetData();

    return QaSetupInfo;
}

void QaSteup::SetData(QASetupData *QASetupInfo)
{
    TestSetupPage->SetData(&QASetupInfo->TestSetupInfo);
    TestSensorsPage->SetData(&QASetupInfo->TestSensorsInfo);

    return;
}


bool QaSteup::getQaResult(StQaCheckCondition &stQaCondition)
{
    if(!stQaCondition.checkDataStatus())
        return false;

    TestSetupPage->getQaResult(stQaCondition);
    TestSensorsPage->getQaResult(stQaCondition);
    return true;
}


