#ifndef BASICLUMINANCE_BASELINE_I_H
#define BASICLUMINANCE_BASELINE_I_H

#include <QWidget>
#include "userdefine.h"
#include <QButtonGroup>
#include "basicdocument.h"
#include"userdefine.h"
namespace Ui {
class BasicLuminance_Baseline_I;
}


class BasicLuminance_Baseline_I : public BasicDocument
{
    Q_OBJECT

public:
    explicit BasicLuminance_Baseline_I(QWidget *parent = 0);
    ~BasicLuminance_Baseline_I();
    void ui_init();
    Basic_Luminance_Data getData();
    void setData(Basic_Luminance_Data *BasicLuminanceInfo,EmReportQaType  ReportQaType=QA_VISUAL);
bool getQaResult(StQaCheckCondition &stQaCondition);
signals:
    void  checkQaResult();
    void  changedLamb(double);
private slots:
    void editIIluminanceE0(QString strE0);
    void editDiffusionCoefficient(QString strRD);
    void editLamb(QString strLamb);
private:
    Ui::BasicLuminance_Baseline_I *ui;
    QButtonGroup *mp_GroupAmbient;
    void  initialOtherValue();
};

#endif // BASICLUMINANCE_BASELINE_I_H
