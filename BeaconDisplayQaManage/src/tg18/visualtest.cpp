#include "visualtest.h"
#include "ui_visualtest.h"

VisualTest::VisualTest(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VisualTest)
{
    ui->setupUi(this);


   // ui->GrayscaleResolution_comboBox
   // ui->LumResponse_comboBox
   //  ui->LumUniformity_comboBox
    //  ui->OverallImageQuality_comboBox

   // g_strListResult

    connect(ui->comboBoxResult,SIGNAL(currentIndexChanged(int)),this,SLOT(EnableCommand(int)));
    ui->lineEdit_name->setText("");
       ui->lineEdit_reason->setText("");
       //CheckConfirmStatus();
       //CheckConfirmStatus();




       EnableCommand(0);
     this->setWindowTitle(tr("Visual test"));
}

VisualTest::~VisualTest()
{
    delete ui;
}
void VisualTest::EnableCommand(int index)
{

      //  ui->pushButton_OK->setVisible(index!=-1);
        ui->lineEdit_reason->setEnabled(index==1);
        CheckConfirmStatus();

}

void VisualTest::on_lineEdit_name_textChanged(const QString &arg1)
{

CheckConfirmStatus();

}
 void VisualTest::CheckConfirmStatus()
 {
     if(ui->comboBoxResult->currentIndex()==0)
          ui->pushButton_OK->setVisible(!ui->lineEdit_name->text().isEmpty());
     else {
         ui->pushButton_OK->setVisible((!ui->lineEdit_name->text().isEmpty()) && (!ui->lineEdit_reason->text().isEmpty()));
     }

 }

void VisualTest::on_lineEdit_reason_textChanged(const QString &arg1)
{
    CheckConfirmStatus();
}

void VisualTest::on_pushButton_OK_clicked()
{
    m_QaResult.strResult=ui->comboBoxResult->currentText();
    m_QaResult.strName=ui->lineEdit_name->text();
    m_QaResult.strReason=ui->lineEdit_reason->text();
    emit CommandOk(true);
}

void VisualTest::on_pushButton_cance_clicked()
{
    emit close();
    emit CommandOk(false);
}
