#ifndef OVERLAYMODES_H
#define OVERLAYMODES_H

#include <QDialog>
#include "mvobj.h"

namespace Ui {
class OverlayModes;
}
typedef enum eValidPortFlag_tag{
    ALL_VALID,
    VGA_ONLY,
    CVBS_S_VIDEO_ONLY
}eValidPortFlag;
class OverlayModes : public QDialog
{
    Q_OBJECT

public:
    explicit OverlayModes(QWidget *parent = nullptr);
    ~OverlayModes();
    void paintEvent(QPaintEvent *event); 
    bool displayLoadProgress(QString strText);
public slots:
    void on_toolButton_clicked();
    void slotOverlayModesIndex();
    void displayTableData(int nCount,int nCurrIndex,stSCAL_ANALOG_MODE_PARAMS_Index_Array stScalAnalogModeParams);
signals:
    void emitOverlayModesIndex(int);
private:
    Ui::OverlayModes *ui;
};

#endif // OVERLAYMODES_H
