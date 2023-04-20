#ifndef VISUALEVALUATION_H
#define VISUALEVALUATION_H

#include <QWidget>
#include "userdefine.h"
#include "testimage.h"
#include "basicdocument.h"
namespace Ui {
class VisualEvaluation;
}

class VisualEvaluation :public BasicDocument
{
    Q_OBJECT

public:
    explicit VisualEvaluation(QWidget *parent = 0);
    ~VisualEvaluation();
    void ui_init();
    Visual_Evaluation_Data getData();
    void setData(Visual_Evaluation_Data *VisualEvaluationPageInfo);
    void getDataFromTestImage(TestImage* pTestImage,bool blIsClinical=false);
   bool getQaResult(StQaCheckCondition &stQaCondition);

private:
    Ui::VisualEvaluation *ui;
public slots:
    void QaVisibleTest();
    void QaClinicalTest();

signals:
    void  checkQaResult();

};

#endif // VISUALEVALUATION_H
