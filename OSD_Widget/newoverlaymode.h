#ifndef NEWOVERLAYMODE_H
#define NEWOVERLAYMODE_H

#include <QDialog>
#include"mvobj.h"
#include <QComboBox>
#include <QCheckBox>
namespace Ui {
class NewOverlayMode;
}
#define BIT0        0x0001
#define BIT1        0x0002
#define BIT2        0x0004
#define BIT3        0x0008
#define BIT4        0x0010
#define BIT5        0x0020
#define BIT6        0x0040
#define BIT7        0x0080
#define BIT8        0x0100
#define BIT9        0x0200
#define BIT10       0x0400
#define BIT11       0x0800
#define BIT12       0x1000
#define BIT13       0x2000
#define BIT14       0x4000
#define BIT15       0x8000
typedef enum eANALOG_MODETYPE_tag{
   MODE_GRAPHICS          = 0,     		 // Mode is Graphics
   MODE_SDVIDEO           = 1,     		 // Mode is SD Video
   MODE_HDVIDEO           = 2,    		 // Mode is HD Video
   MODE_EDVIDEO           = 3,     		 // Mode is Extended Definition Video (480p/576p/etc)
   MODE_INTERLACED        = BIT2,  		 // Mode is Interlaced
   MODE_NEG_HSYNC         = BIT3,  		 // Mode HSync is Negative
   MODE_NEG_VSYNC         = BIT4,  		 // Mode VSync is Negative
   MODE_SOG               = BIT5,  		 // Mode is SOG or Embedded sync
   MODE_CSYNC             = BIT6,  		 // Mode is Composite Sync
   MODE_CAPTURE_CROP	  = BIT7, 		 // Capture Crop Mode
   MODE_CVT			      = BIT8,  		 // CVT Mode
   MODE_ESTIMATED         = BIT9,  		 // Mode is Estimated
   MODE_OUT_RANGE         = BIT10, 		 // Signal is Out of Range
   MODE_SUB_SAMPLE        = BIT11, 		 // Sub-sample input mode
   MODE_UNKNOWN           = BIT12, 		 // Mode not found in Rom table
   MODE_VALID             = BIT13, 		 // Mode is Stable and Valid
   MODE_COMPLETE          = BIT14, 		 // Mode has been configured
   MODE_EMBEDDED_VIDEO    = BIT15, 		 // Mode is a Video Image in a Graphic signal
   //MODE_SIGNAL_MASK       = (BIT0|BIT1), // Signal Types (Graphics, SDVideo, HDVideo, etc)
} eANALOG_MODETYPE;

typedef enum eANALOG_OPATION_tag
{
    SaveOverlayData,
    DebugOverlayData
}eANALOG_OPATION;
class NewOverlayMode : public QDialog
{
    Q_OBJECT

public:
    explicit NewOverlayMode(QWidget *parent = nullptr);
    ~NewOverlayMode();
    void paintEvent(QPaintEvent *event);
    bool setTableData(stSCAL_ANALOG_INPUT_PARAMS stValue,stVStart stHStartValue,stVStart stVStartValue);
    bool getTableData(stSCAL_ANALOG_MODE_PARAMS *stValue);

signals:
    void sendOverlayModeData(int,stSCAL_ANALOG_MODE_PARAMS);

public slots:
    void slotSaveOverlayModeOk();
private slots:
    void on_pushButtonSave_clicked();
    void on_pushButtonDebug_clicked();
    void on_toolButton_clicked();    

private:
    Ui::NewOverlayMode *ui;
    QComboBox *comboBoxValidPortFlag;
    QCheckBox *checkModeType;
};

#endif // NEWOVERLAYMODE_H
