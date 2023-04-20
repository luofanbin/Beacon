#include "angularview.h"
#include "ui_angularview.h"

AngularView::AngularView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AngularView)
{
    ui->setupUi(this);

    connect(ui->StartTest,SIGNAL(clicked()),this,SLOT(QaVisibleTest()));
}

AngularView::~AngularView()
{
    delete ui;
}
StAngularView AngularView::getData()
{
    StAngularView angular_view;
    angular_view.nTopLeft=ui->TopLeftlineEdit->text().toInt();
    angular_view.nTopMiddle=ui->TopMiddlelineEdit->text().toInt();
    angular_view.nTopRight=ui->TopRightlineEdit->text().toInt();

    angular_view.nMiddleLeft=ui->MiddleLeftlineEdit->text().toInt();
    angular_view.nMiddleCenter=ui->MiddleCenterlineEdit->text().toInt();
    angular_view.nMiddleRight=ui->MiddleRightlineEdit->text().toInt();

    angular_view.nBottomLeft=ui->BottomLeftlineEdit->text().toInt();
    angular_view.nBottomMiddle=ui->BottomMiddlelineEdit->text().toInt();
    angular_view.nBottomRight=ui->BottomRightlineEdit->text().toInt();
    angular_view.getAverage();
    angular_view.dbAverageValue=ui->AveragelineEdit->text().toDouble();
return angular_view;
}
void AngularView::setData(StAngularView *pAngularViewInfo)
{
    ui->TopLeftlineEdit->setText(QString::number(pAngularViewInfo->nTopLeft));
    ui->TopMiddlelineEdit->setText(QString::number(pAngularViewInfo->nTopMiddle));
    ui->TopRightlineEdit->setText(QString::number(pAngularViewInfo->nTopRight));

    ui->MiddleLeftlineEdit->setText(QString::number(pAngularViewInfo->nMiddleLeft));
    ui->MiddleCenterlineEdit->setText(QString::number(pAngularViewInfo->nMiddleCenter));
    ui->MiddleRightlineEdit->setText(QString::number(pAngularViewInfo->nMiddleRight));

    ui->BottomLeftlineEdit->setText(QString::number(pAngularViewInfo->nBottomLeft));
    ui->BottomMiddlelineEdit->setText(QString::number(pAngularViewInfo->nBottomMiddle));
    ui->BottomRightlineEdit->setText(QString::number(pAngularViewInfo->nBottomRight));
   pAngularViewInfo->getAverage();
    ui->AveragelineEdit->setText(QString::number(pAngularViewInfo->dbAverageValue,'f',2));

}
bool AngularView::getQaResult(StQaCheckCondition &stQaCondition)
{


        if(!stQaCondition.checkDataStatus())
            return false;

        if(ui->TopLeftlineEdit->text().isEmpty() ||
            ui->TopMiddlelineEdit->text().isEmpty()||
                ui->TopRightlineEdit->text().isEmpty()||
            ui->MiddleLeftlineEdit->text().isEmpty() ||
            ui->MiddleCenterlineEdit->text().isEmpty()||
            ui->MiddleRightlineEdit->text().isEmpty())
            {
            stQaCondition.strResult=tr("Please fill in angular view information!");
            return false;
            }


        StAngularView angular_view=getData();



       if(angular_view.dbAverageValue<stQaCondition.dbAverageView)
       {

           return false;
       }

    return true;

}
void AngularView::QaVisibleTest()
{
    TestImage dlg_test(this);
    dlg_test.setTg18Type(QA_TG18_ANG,QA_METHOD_SINGLE);
    dlg_test.showFullScreen();
    int res = dlg_test.exec();
    if(res!=QDialog::Accepted)
        return ;
    getDataFromTestImage(&dlg_test);
    emit checkQaResult();
}
void AngularView::getDataFromTestImage(TestImage* pTestImage)
{
    StTg18Result st_tg_result;
    StAngularView angular_data=getData();
    angular_data.intialPointer();
    int  *p_uniform=angular_data.pIntBegin;
    st_tg_result.emType=QA_TG18_ANG;
    if( pTestImage->getTg18Data(st_tg_result))
    {
        for (int i=0;i<=9;i++)
        {

            *p_uniform=st_tg_result.dataResult.nResult[i];
            p_uniform++;

        }
        setData(&angular_data);
    }
}
