#ifndef QTG18RESULT_H
#define QTG18RESULT_H

#include <QWidget>
#include <QtWidgets/QComboBox>
#include<QStackedLayout>
#include "userdefine.h"
#include "qmap.h"
#include <QCheckBox>
#include <QPushButton>
class QTg18Result : public QWidget
{

Q_OBJECT
public:
    enum
    {
        TEST_HIDE,
        TEST_SHOW,
        TEST_NEXT

    };
    explicit QTg18Result(EmTg18Type emType,QWidget *parent = nullptr);

    bool  setStackItermIndex(bool blForward);
    int getStackItermCurrent();
    bool  getTg18Data(StTg18Result &stResult);
    void setPointNumber(bool blNinePoint){m_blNinePoint=blNinePoint;};
signals:
    void getSensorData(StCieLvxy &stLvxy);
    void testNextPosition(int nType);
private:
QComboBox *mp_ComboBoxResult[2];
QLineEdit *mp_LineEditData[DICOM_GSDF_GRAYSCALE_NUMBER*3];
QStackedLayout *mp_stackItermLuminance;
QCheckBox *mp_AutoRead;
QPushButton *mp_sensorButton;
void Sleep(int msec);
private:
    EmTg18Type m_emTgImageType;

    bool m_blNinePoint;
    bool m_blAutoTestLN;

public slots:
    void getSensorData();
};

#endif // QTG18RESULT_H
