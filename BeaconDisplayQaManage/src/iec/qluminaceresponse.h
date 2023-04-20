#ifndef QLUMINACERESPONSE_H
#define QLUMINACERESPONSE_H

#include <QWidget>
#include<QLineEdit>
#include<QLabel>
#include "qcustomplot.h"
#include "ccurvtypemothed.h"
#include"userdefine.h"

class QLuminaceResponse : public QWidget
{
Q_OBJECT
public:
explicit QLuminaceResponse(QWidget *parent = nullptr);

signals:
void testLuminace();
void  checkQaResult();
public slots:

    void setData(const StQaLuminace &stQaData );
    const StQaLuminace getData( );
    bool getQaResult(StQaCheckCondition &stQaCondition);
    void changedLamb(double dbAmbient);
private:
    StQaLuminace m_stQaLuminace;
    QLineEdit *mp_GrayscaleLn[DICOM_GSDF_GRAYSCALE_NUMBER];
    QLineEdit *mp_GrayscaleLnInclueAmbient[DICOM_GSDF_GRAYSCALE_NUMBER];
    QLineEdit *mp_GrayscaleLnError[DICOM_GSDF_GRAYSCALE_NUMBER-1];
    QLineEdit *mp_GrayscaleLnErrorMax;
    QCustomPlot m_CurvePlot;
    void setGsdfGraphData(Contrast_response_Data   data_buffer);
    void updateData(bool blUpate);
};

#endif // QLUMINACERESPONSE_H
