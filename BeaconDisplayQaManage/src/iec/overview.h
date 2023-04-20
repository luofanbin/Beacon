#ifndef OVERVIEW_H
#define OVERVIEW_H

#include <QObject>
#include <QWidget>
#include"my_coutom_lable.h"
#include"userdefine.h"
#include "basicdocument.h"
#include<QFormLayout>
class Overview : public BasicDocument
{
    Q_OBJECT
public:
    explicit Overview(QWidget *parent = 0);
    void ui_layout();
    void resizeEvent(QResizeEvent *event);
    StQaResult GetData();
    void SetData(StQaResult *OverviewInfo);
   bool getQaResult(StQaCheckCondition &stQaCondition);
   void updatePageContent();
signals:
  void send_click_signal(int);
public slots:

public:
    QComboBox *Overall_Test_Result_Box,*Auto_Test_Comment_Box;
    QTextEdit *Test_Comment_TextEdit;
    QFrame  *Line1;
    My_Coutom_Lable *p_coutom_lable[5];
    QFormLayout * p_formLayout;
    QLabel *p_Label[5];
};

#endif // OVERVIEW_H
