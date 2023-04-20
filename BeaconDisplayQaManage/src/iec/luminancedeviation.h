#ifndef LUMINANCEDEVIATION_H
#define LUMINANCEDEVIATION_H

#include <QWidget>
#include "userdefine.h"
#include "testimage.h"
#include "basicdocument.h"
namespace Ui {
class LuminanceDeviation;
}

class LuminanceDeviation : public  BasicDocument
{
    Q_OBJECT

public:
    explicit LuminanceDeviation(QWidget *parent = 0);
    ~LuminanceDeviation();
    void ui_init();
    Luminance_Deviation_Data getData();
    void setData(Luminance_Deviation_Data *LuminanceDeviationInfo);
    void getDataFromTestImage(TestImage* pTestImage);
    bool getQaResult(StQaCheckCondition &stQaCondition);
    void showDeviationPoint();
signals:
    void  checkQaResult();
    void getSensorData(StCieLvxy &stLvxy);
    void sendTestImageDataToChromaticityEvaluation(StTg18Result);
    void notSelectSensor();
private:
    void initialOtherValue();
    Ui::LuminanceDeviation *ui;
    bool m_blNinePoint;
public slots:
    void testUinform();
};

#endif // LUMINANCEDEVIATION_H
