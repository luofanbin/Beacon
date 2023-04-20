#ifndef QAIECREPORTINFORMATION_H
#define QAIECREPORTINFORMATION_H

#include <QWidget>
#include <QWidget>
#include <QStringList>
#include<QMouseEvent>
#include<QComboBox>
#include<QTextEdit>
#include<QVector>


#include"qasteup.h"
#include"overview.h"
#include"display_1.h"
#include"workstation.h"
#include "basicdocument.h"
#include"userdefine.h"
namespace Ui {
class QaIecReportInformation;
}

class QaIecReportInformation : public BasicDocument
{
Q_OBJECT

public:
    void SetData(StIecReport *CurrTestData);
    StIecReport GetData();
   bool getQaResult(StQaCheckCondition &stQaCondition);

   
explicit QaIecReportInformation(QWidget *parent = nullptr);
~QaIecReportInformation();
 signals:
     void showQaHistory();
     void setDisplayPage(int index);
private:
Ui::QaIecReportInformation *ui;

void ui_init();//界面初始化
void ui_layout();

public slots:
    void slot_label_click(int nIndex);

private slots:
    void on_Acceptance_pushButton_clicked();
    void on_OK_pushButton_clicked();
    void on_Cancel_pushButton_clicked();
    void on_Apply_pushButton_clicked();
    void on_Close_pushButton_clicked();
   // void on_Dispaly_Setup_pushButton_clicked();
    void ClieckButtonBox(QAbstractButton *button);
    bool checkDataStatus();

protected:
    QaSteup *QASteupWidget;
    Overview *OverviewWidget;
    Workstation * WorkstationWidget;
    Display_1 *Display_1_Widget;
    //StIecReport m_stIecReport;

};

#endif // QAIECREPORTINFORMATION_H
