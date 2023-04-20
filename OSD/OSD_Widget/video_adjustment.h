#ifndef VIDEO_ADJUSTMENT_H
#define VIDEO_ADJUSTMENT_H

#include <QWidget>
#include "ui_video_adjustment.h"
#include"./IFX/mvobj.h"
#include"dp_adjustment.h"
#include "newoverlaymode.h"
#include "overlaymodes.h"

typedef enum eOverlay_INDEX_tag{
    OVERLAY_MODES =1,
    NEW_OVERLAY_MODES,
    CLEAR_OVERLAY_MODES
}eOverlay_INDEX;

class VideoAdjustment : public QWidget,public Ui_Video_Adjustment
{
    Q_OBJECT

public:
    //explicit nullptr
    VideoAdjustment(QWidget *parent = 0);
    ~VideoAdjustment();
    int doubleToInt(double d);
    bool eventFilter(QObject *obj, QEvent *event);
    void EnableControlCursor();
    void DisableControlCursor();
    bool isAnalogSignal(int nSigId);
    void slider_instaneventfiliter(); //slider控件安装一个事件过滤器
    void signal_connect_slot();
    void SetBrightnessSliderValue(stVALUE_INFO stValue);
    void SetContrastSliderValue(stVALUE_INFO stValue);
    void SetColorSliderValue(stVALUE_INFO stValue);
    void SetHueSliderValue(stVALUE_INFO stValue);
    void SetSharpnessSliderValue(stVALUE_INFO stValue);
    void SetNoiseSliderValue(stVALUE_INFO stValue);
    void SetPhaseSliderValue(stVALUE_INFO stValue);
    void SetClampwidthSliderValue(stVALUE_INFO stValue);
    void SetVFrequencyLabelValue(stVALUE_INFO stValue);
    void SetHFrequencyLabelValue(stVALUE_INFO stValue);
    void SetGammaControlValue(stVALUE_INFO stValue);
    void SetBandwidthControlValue(stVALUE_INFO stValue);
    void SetFmtPNControlValue(stVALUE_INFO stValue);
    void SetControlIsEnable(int SigInId,bool blIsValid);
    void SetInformationControlInfo(stVIDSIGIN_STATUS VidSigInStatus,QString SigInName);
    void SetHStartSliderValue(stHVStart stValue,int nMinVale,int nMaxValue);
    void SetVStartSliderValue(stHVStart stValue,int nMinVale,int nMaxValue);
    void SetAutomaticValue(int val);

    int SigInId;
    QTime mouse_no_work_time;
    DpAdjustment* dp_adjustment;
    NewOverlayMode *dlgNewOverlay;
    OverlayModes *dlgOverlayModes;
    bool Cursor_ONOFF;

    bool read_Brightness=false,read_Contrast=false,read_Color=false,read_Hue=false,read_Sharpness=false,
         read_Noise=false,read_Phase=false,read_Frequency=false,read_Clampwidth=false,read_Bandwidth=false,
         read_ColorTemp_R=false,read_ColorTemp_G=false,read_ColorTemp_B=false,read_ColorTemp_Temp=false,
         read_Scaling_Zoom=false,read_H_Scaling=false,read_Dither=false,read_Frequency_Scope=false,
         read_gamma=false,read_InputSig_ref=false,read_InputSig_live=false,read_HStart=false,read_VStart=false;
public slots:
    void Slider_Value_Changed(int value);
    void spinBox_Valie_changed(int value);
    void Double_spinBox_Valie_changed(double value);
    void CheckBox_StateChanged();
    void RadioButton_Clicked();
    void ComboBox_currentIndexChanged(int index);
    void pushButton_Clicked();
    void ToolButton_Clicked();
    void st_DP_Info(stSCAL_INPUT_DP_INFO);
    void gt_DP_Info(int sigid);
    void SetColorTempControlValue(stDISP_COLORTEMP stColorTemp);
    void SetScalingControlValue(stVIDGOUT_SCAL stScaling);
    void SetFrequencySliderValue(gtFrequency_INFO gtFrequency);
signals:
    void Set_Value(int type,stVALUE_INFO stValue);
    void Set_ColorTemp(stDISP_COLORTEMP stColorTemp);
    void Set_SCaling(stVIDGOUT_SCAL stScaling);
    void Set_AutoSetup(stAuto_INFO stValue_Info);
    void Set_PresetCfg(int type);
    void Get_DP_Info(int);
    void Set_DP_Info(stSCAL_INPUT_DP_INFO);
    void Read_CTmep_Scaing(int);
    void emitOverlayModes(int);
    void emitSetOverlayCtrlMethod(int);
};

#endif // VIDEO_ADJUSTMENT_H
