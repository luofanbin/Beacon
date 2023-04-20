#include "dilogreporthistory.h"
#include "ui_dilogreporthistory.h"
#include"testimage.h"
#include "dialogmulitescreen.h"
#include "databasecontrol.h"
#include "qsqlqueryrelatinaltablemodel.h"
#include <QMessageBox>
#include "userdefine.h"
#include "databasecontrol.h"
DilogReportHistory::DilogReportHistory(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DilogReportHistory)
{

    g_strReporType[QA_VISUAL]=tr("Daily QA");
    g_strReporType[QA_ACCEPTANCE]=tr("Acceptance");
    g_strReporType[QA_CONSTANCY]=tr("Constancy");
    g_strReporType[QA_ACCEPTANCE_NEW]=tr("Acceptance");
    g_strReporType[QA_CONSTANCY_NEW]=tr("Constancy");

    QString str_resutl=tr("- -,OK,Fail");
    g_strListResult=str_resutl.split(",");

    ui->setupUi(this);
    model = new QSqlQueryRelatinalTableModel();
     model->setEditStrategy(QSqlTableModel::OnManualSubmit);
     model->setTable("history");

    ui->ReportTableView->setSortingEnabled(true);
     //authorIdx = model->fieldIndex("author");
//     genreIdx = model->fieldIndex("genre");



       // Set the localized header captions:
     model->setHeaderData(model->fieldIndex("display_name"), Qt::Horizontal, tr("Display"));
     model->setHeaderData(model->fieldIndex("serial_number"), Qt::Horizontal, tr("SN"));

     model->setHeaderData(model->fieldIndex("modified_time"), Qt::Horizontal, tr("Modify time"));
     model->setHeaderData(model->fieldIndex("test_time"), Qt::Horizontal, tr("Test date"));
     model->setHeaderData(model->fieldIndex("operator_name"), Qt::Horizontal, tr("User"));
     model->setHeaderData(model->fieldIndex("standard_type"), Qt::Horizontal, tr("Type"));
     model->setHeaderData(model->fieldIndex("status"), Qt::Horizontal, tr("Status"));
     model->setHeaderData(model->fieldIndex("reason"), Qt::Horizontal, tr("Reason"));
        // Populate the model:

     QSqlQuery query("SELECT  * FROM history WHERE operator_name== 999");
     //   model->setQuery(query);
    if (!model->select()) {

        return;
    }

    QString histor_str="id,Display_Qa_Grayscale_Luminace"
                        ",WorkStaion_Information"
                        ",Test_Setup"
                        ",LuminanceSensor"
                        ",IllLuminaceSensor"
                        ",Display_Infor"
                        ",Visual_Evaluation_Data"
                        ",Basic_Luminance_Data"
                        ",Luminance_Deviation_Data"
                        ",Angular_View"
                        ",Chromaticity_Evaluation"
                        ",Greyscale_Chromaticity_Evaluation";
    QStringList histor_iterm=histor_str.split(",");
     // Set the model and hide the ID column:
     ui->ReportTableView->setModel(model);
    // ui.bookTable->setItemDelegate(new BookDelegate(ui.bookTable));

     QStringListIterator strIterator(histor_iterm);
     while (strIterator.hasNext())
     {
         ui->ReportTableView->setColumnHidden(model->fieldIndex(strIterator.next()), true);
     }
    ui->ReportTableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->ReportTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->ReportTableView->setShowGrid(true);
    ui->ReportTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);    // Initialize the Author combo box:
    ui->ReportTableView->setSelectionBehavior(QAbstractItemView::SelectRows);//设置选中模式

   connect(ui->buttonLoadGamma, SIGNAL(clicked()), this, SLOT(inputGamma()));
 connect(ui->buttonVisualTest,SIGNAL(clicked()),this,SLOT(showTg18Qa()));
 connect(ui->buttonAcceptanceTest,SIGNAL(clicked()),this ,SLOT(addNewAcceptance()));
 connect(ui->buttonContancyTest,SIGNAL(clicked()),this ,SLOT(addNewConstancy()));
 connect(ui->ReportTableView, SIGNAL(clicked(const QModelIndex &)), this, SLOT(rowClicked(const QModelIndex &)));
 connect(ui->ReportTableView, SIGNAL(doubleClicked(const QModelIndex &)), this, SLOT(rowDoubleClicked(const QModelIndex &)));
// connect(ui->buttonVisualTest,SIGNAL(clicked()),this,SLOT(showTg18Qa()));
 connect(ui->buttonPrintPDF,SIGNAL(clicked()),this,SLOT(printPdf()));
//ui->frameFunction->setVisible(false);
    ui->buttonDelee->hide();
    ui->buttonClose->hide();
    ui->buttonEdit->hide();
     ui->buttonPrintPDF->setEnabled(false);
ui->buttonLoadGamma->setVisible(false);

}

DilogReportHistory::~DilogReportHistory()
{
    QApplication::closeAllWindows();
    delete ui;
}
void DilogReportHistory::showTg18Qa()
{

//QDialog dlg_test;
//dlg_test.setWindowModality(Qt::ApplicationModal);
//dlg_test.showFullScreen();

//
//dlg_test.exec();
    DatabaseControl data_control;
    DisplayName_Data display_name;
    data_control.getDisplayTableInfomation( display_name );

    TestImage dlg(this);
    dlg.setTg18Type(QA_TG18_OIQ_EVERY,QA_METHOD_SINGLE);



//setWindowModality(Qt::ApplicationModal);
   // dlg.setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
  // dlg.setModal(false);
  //  dlg.showMaximized();
    dlg.setWindowModality(Qt::WindowModal);
     dlg.showFullScreen();
   // dlg.setAttribute(Qt::WA_ShowModal, true);
  int res = dlg.exec();
  //  int res;;
    if (res == QDialog::Accepted)
    {

     dlg.m_QaResult.strType=g_strReporType[QA_VISUAL];
    dlg.m_QaResult.strDisplay=display_name.DisplayName;
     dlg.m_QaResult.strSerialNumber=display_name.SN;
     dlg.m_QaResult.dateCreate=QDateTime::currentDateTime();
        data_control.addHistoryQa( dlg.m_QaResult);
        updateDataBase();
      //  ui->ReportTableView->update();
    }
    if (res == QDialog::Rejected)
    {
  //  QMessageBox::information(this, “INFORMATION”, “You clicked CANCEL button!”);
    }
}

void DilogReportHistory::on_buttonDisplayManage_clicked()
{
    DialogMuliteScreen dlg(this);
 dlg.setWindowModality(Qt::WindowModal);
   dlg.show();
    int res = dlg.exec();


}
 void DilogReportHistory::updateDataBase()
{
      model->select();
      ui->buttonPrintPDF->setEnabled(false);
 }
 void DilogReportHistory::rowDoubleClicked(const QModelIndex &index)
 {

if (!index.isValid())
    return;
DatabaseControl data_control;
QString str_infor= model->data(model->index(index.row(),5)).toString();

  //  QMessageBox::warning(this,"",str_infor);
    int n_id=0;
    n_id=model->data(model->index(index.row(),0)).toInt();
    if(str_infor==g_strReporType[QA_VISUAL])
      return ;



    StQaResult qa_result;
    StIecReport iec_report;
    if(str_infor==g_strReporType[QA_ACCEPTANCE] )
    iec_report.ReportQaType=QA_ACCEPTANCE;
    else if( str_infor==g_strReporType[QA_CONSTANCY])
     iec_report.ReportQaType=QA_CONSTANCY;
    data_control.getHistoryQa( n_id, qa_result);
    data_control.getIecReport(qa_result, iec_report);

    emit showQaIecReportTest(iec_report);


     //通过Model获取一行
    /* index

     g_strReporType[nReportType];

 case QA_VISUAL:

 case  QA_ACCEPTANCE:

 case  QA_CONSTANCY:
     QModelIndex currentt_index = ui->ReportTableView->currentIndex();
     QMessageBox::warning(this,"",QString("selset iterm:%1 current iterm:%2").arg(index.row()).arg(currentt_index.row()));

     if (index.isValid())
     {
            }
*/
 }

 void DilogReportHistory::rowClicked(const QModelIndex &index)
 {
     if (!index.isValid())
         return;
     DatabaseControl data_control;
     QString str_infor= model->data(model->index(index.row(),5)).toString();

       //  QMessageBox::warning(this,"",str_infor);
         int n_id=0;
         n_id=model->data(model->index(index.row(),0)).toInt();
         if(str_infor==g_strReporType[QA_VISUAL])
         {
           ui->buttonPrintPDF->setEnabled(false);
           return ;
         }

         ui->buttonPrintPDF->setEnabled(true);
 }



 void DilogReportHistory::addNewAcceptance()
 {
     StIecReport iec_report;
     iec_report.ReportQaType=  QA_ACCEPTANCE_NEW;
     emit showQaIecReportTest(iec_report);
 }
 void DilogReportHistory::addNewConstancy()
 {
     StIecReport iec_report;
     iec_report.ReportQaType=QA_CONSTANCY_NEW;
     emit showQaIecReportTest(iec_report);
 }

 void DilogReportHistory::printPdf()
 {

     QModelIndex index = ui->ReportTableView->selectionModel()->currentIndex();
     int iSel = index.row();

     if (!index.isValid())
         return;

     DatabaseControl data_control;
     QString str_infor= model->data(model->index(index.row(),5)).toString();

     //  QMessageBox::warning(this,"",str_infor);
     int n_id=0;
     n_id=model->data(model->index(index.row(),0)).toInt();
     if(str_infor==g_strReporType[QA_VISUAL])
         return ;

    QString fileName;
     StQaResult qa_result;
     StIecReport iec_report;
     if(str_infor==g_strReporType[QA_ACCEPTANCE] )
         iec_report.ReportQaType=QA_ACCEPTANCE;
     else if( str_infor==g_strReporType[QA_CONSTANCY])
         iec_report.ReportQaType=QA_CONSTANCY;
     data_control.getHistoryQa( n_id, qa_result);
     data_control.getIecReport(qa_result, iec_report);

     CreatePrintPdf cpPrintPdf;
     cpPrintPdf.printPreviewPdf(fileName,iec_report);
 }
void DilogReportHistory::inputGamma()
{
    QString fileName = QFileDialog::getOpenFileName(
            this,
            tr("open a file."),
            "",
            tr("gamma file(*.txt );;video files(*.txt )"));
        if (fileName.isEmpty()) {
            QMessageBox::warning(this, "Warning!", "Failed to open the video!");
        }
        else {
            testApplyIcmm(fileName);
        }


}
