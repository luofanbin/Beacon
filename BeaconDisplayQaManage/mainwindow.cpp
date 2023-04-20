#include "mainwindow.h"


#include <QtSql>
#include"QMessageBox"
#include"testimage.h"
#include "databasecontrol.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{


    QString windwo_tilet=QString(tr("BeaconDisplayQAManager"))+QString(" %1").arg(double(SOFTWARE_VERSION),0,  'f', 2, QLatin1Char( '0' ) );
    setWindowTitle(windwo_tilet);
    mp_MainWidget=new QStackedWidget;;
    mp_MainWidget->addWidget(&m_dilogReportHistory);
    mp_MainWidget->addWidget(&m_QaIecInformation);
    this->setCentralWidget(mp_MainWidget);

   // mp_MainWidget->setCurrentWidget(&m_QaIecInformation);
    mp_MainWidget->setCurrentWidget(&m_dilogReportHistory);

    connect(&m_QaIecInformation,SIGNAL(showQaHistory()),this,SLOT(QaHistory()));
    connect(&m_dilogReportHistory,SIGNAL(showQaIecReportTest(StIecReport &)),this,SLOT(showQaIecReportTest(StIecReport &)));
resize(800,600);
}

MainWindow::~MainWindow()
{
QApplication::closeAllWindows();
}

void MainWindow::changeEvent(QEvent *event)
{
        if(event -> type() == QEvent::LanguageChange)
        {

        }
}
void MainWindow::QaHistory()
{
    m_dilogReportHistory.updateDataBase();
    mp_MainWidget->setCurrentWidget(&m_dilogReportHistory);
}

void MainWindow::showQaIecReportTest(StIecReport &IecReport)
{
    if (IecReport.ReportQaType==QA_ACCEPTANCE_NEW||IecReport.ReportQaType==QA_CONSTANCY_NEW)
   {
       DatabaseControl data_control;
       StQaResult qa_result;

       data_control.getIecReport(qa_result, IecReport);



   }

   m_QaIecInformation.SetData(&IecReport);
   mp_MainWidget->setCurrentWidget(&m_QaIecInformation);

}
