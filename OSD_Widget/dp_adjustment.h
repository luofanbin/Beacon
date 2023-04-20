#ifndef DP_ADJUSTMENT_H
#define DP_ADJUSTMENT_H

#include <QDialog>
#include "./IFX/mvobj.h"
#include "ui_dp_adjustment.h"

class DpAdjustment : public QDialog,public Ui_DP_Adjustment
{
    Q_OBJECT

public:
    DpAdjustment(QWidget *parent = nullptr);
    ~DpAdjustment();
    void paintEvent(QPaintEvent *event);
    bool read_DP=false;
    void GetDPLinkTrainingInfo(int nFlag,stSCAL_INPUT_DP_INFO DPInfo);
    void init();
    void setSubmitButtonEnable();
    void enableCheckBox();
    void disableCheckBox();

    bool blIsSendSetDp;
public slots:
    void on_toolButton_clicked();
    void checkBox_Click();
    void CommBoxChangIndex(int index);
    void SubmitButtonClicked();
    void slot_DpInfoHide();

signals:
    void st_DP_Info(stSCAL_INPUT_DP_INFO);
    void gt_DP_Info(int);

public:
    QTimer* timer;
};

#endif // DP_ADJUSTMENT_H
