#ifndef MY_COUTOM_LABLE_H
#define MY_COUTOM_LABLE_H

#include<QLabel>
#include<QEvent>
#include "qcustomplot.h"
#include "ccurvtypemothed.h"

class My_Coutom_Lable:public QLabel
{
    Q_OBJECT
public:
    My_Coutom_Lable(QWidget *parent = 0);

public:
    void enterEvent(QEvent *e);//鼠标进入事件
    void leaveEvent(QEvent *e);//鼠标离开事件
    void mousePressEvent(QMouseEvent *event);
    virtual void paintEvent(QPaintEvent *event) override;
    void DrawingCurves();
    void addRandomGraph(QCustomPlot *pCustomPlot,Contrast_response_Data *data_buffer);

    QString text;
    int nIndex=0;
    QCustomPlot m_CurvePlot;
    bool bl_isMonitorMouse;
    bool blIsDrawOutlined;
signals:
    void send_click_signal(int);
    void hideDisplaySN();
};

#endif // MY_COUTOM_LABLE_H
