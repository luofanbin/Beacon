#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
//#include <QTranslator>
#include "dilogreporthistory.h"
#include<QStackedWidget>
#include "qaiecreportinformation.h"
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
   private:
    DilogReportHistory m_dilogReportHistory;
    QStackedWidget * mp_MainWidget;
    QaIecReportInformation m_QaIecInformation;
    void changeEvent(QEvent *event);
protected slots:

    void QaHistory();
    void showQaIecReportTest(StIecReport &IecReport);

private:


};

#endif // MAINWINDOW_H
