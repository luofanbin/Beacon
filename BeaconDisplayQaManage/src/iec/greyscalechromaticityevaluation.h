#ifndef GREYSCALECHROMATICITYEVALUATION_H
#define GREYSCALECHROMATICITYEVALUATION_H

#include <QWidget>
#include<QLineEdit>
#include<QLabel>
#include "qcustomplot.h"
#include "ccurvtypemothed.h"
#include"userdefine.h"
class GreyscaleChromaticityEvaluation : public QWidget
{
    Q_OBJECT
public:
    explicit GreyscaleChromaticityEvaluation(QWidget *parent = 0);

signals:

public slots:

    void setData(const StGreyscaleChromaticityEvaluation &stGreyscaleChromaticity,const  StQaLuminace &stQaData);
    const StGreyscaleChromaticityEvaluation getData( );
    bool getQaResult(StQaCheckCondition &stQaCondition);

private:
    StGreyscaleChromaticityEvaluation m_stGreyscaleChromaticity;
    StQaLuminace m_stQaLuminace;
    QLineEdit *mp_GrayscaleLn_u[DICOM_GSDF_GRAYSCALE_NUMBER];
    QLineEdit *mp_GrayscaleLn_v[DICOM_GSDF_GRAYSCALE_NUMBER];
    //QLineEdit *mp_GrayscaleLnError[DICOM_GSDF_GRAYSCALE_NUMBER-1];
    QLineEdit *mp_GrayscaleLnDeviationMax;
    //QCustomPlot m_CurvePlot;
    //void setGsdfGraphData(Contrast_response_Data   data_buffer);
    void updateData(bool blUpate);
};

#endif // GREYSCALECHROMATICITYEVALUATION_H
