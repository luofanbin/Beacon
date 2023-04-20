#ifndef CHROMATICITYEVALUATION_H
#define CHROMATICITYEVALUATION_H

#include <QWidget>
#include "userdefine.h"
#include "testimage.h"
namespace Ui {
class ChromaticityEvaluation;
}

class ChromaticityEvaluation : public QWidget
{
    Q_OBJECT

public:
    explicit ChromaticityEvaluation(QWidget *parent = 0);
    ~ChromaticityEvaluation();
    StChromaticityEvaluation getData();
    void setData(StChromaticityEvaluation *pChromaticityEvaluationInfo);
    bool getQaResult(StQaCheckCondition &stQaCondition);
    void showDeviationPoint();
    //void getDataFromTestImage(TestImage* pTestImage);

public slots:
    void getDataFromTestImage(StTg18Result st_tg_result);
private:
    void initialOtherValue();
    Ui::ChromaticityEvaluation *ui;
    bool m_blNinePoint;
};

#endif // CHROMATICITYEVALUATION_H
