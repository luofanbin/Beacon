#ifndef DISPLAYNAME_H
#define DISPLAYNAME_H

#include <QWidget>
#include "userdefine.h"
#include "basicdocument.h"
namespace Ui {
class DisplayName;
}

class DisplayName : public BasicDocument
{
    Q_OBJECT

public:
    explicit DisplayName(QWidget *parent = 0);
    ~DisplayName();
    void ui_init();
    DisplayName_Data getData();
    void setData(DisplayName_Data *DisplayPageInfo);
    bool getQaResult(StQaCheckCondition &stQaCondition);


private slots:
  //  void QaAllImage();

private:
    Ui::DisplayName *ui;
    bool m_bIsDiagnostic;
signals:
    void QaTestAll();
    void QaClinicalTest();
};

#endif // DISPLAYNAME_H
