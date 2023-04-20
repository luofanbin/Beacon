#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include"dbus_interface.h"
#include<QLabel>
#include"mvmethodosd.h"
#include"sigvinscaninfo.h"
#include"video_adjustment.h"
#include"messages.h"
#include<QTime>
#include "scanningdialog.h"

typedef struct Take_Notes_Network_Data_Info_tag{
    int uiNetIndex[2];
    int bIsDHCP[2];
    QString strIpAddr[2];
    QString strMask[2];
    QString strGate[2];
    QString strNDS1[2];
    QString strNDS2[2];
    int server_port;
    int net_select;
    QString ip[2];
    int port[2];
    QString RAETitle[2];
    QString LAETitle[2];
}TakeNotesNetworkData;

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    bool eventFilter(QObject *obj, QEvent *event);
    void slider_instaneventfiliter(); //slider控件安装一个事件过滤器
    void mouseDoubleClickEvent(QMouseEvent *event);

    void init_set();
    void ui_init();
    int Read_Timming_Cfg_File();
    int Write_Timming_Cfg_File();
    int Init_Timming_Cfg_File();
    void GetPresetParams(bool blIsValid);
    void EnableControlCursor();
    void DisableControlCursor();
    void GetDPLinkTraining();
    void setAnalogOverlayData();
    bool getVideoSettingParameters();
    bool setVideoSetting(int nMode);
    bool getSystemParameters();
    bool getNetworkParameters();

    bool read_InputSig_ref=false,read_InputSig_live=false;
    int fist_osd_on_off=0,OsdOnOff_Scan;
public slots:
    void Slot_SetSingleSel(stDispOsd_INFO setValue);
    void Slot_SetItemSpan(stDispOsd_INFO setValue);
    void Slot_SigSetGrabIndcatorSel(uchar span_val);
    void Slot_SigSetFrozSpan(stFans_INFO stFrozSpan);
    void Slot_SetOsdMsg(QString setMsg);
    void Slot_OsdOnOff(stOsdOnOff_Info OnOff);
    void slotSingleGrabStart(stGrabImageStaus_INFO stGrabImageStaus);

    void Slider_Value_Changed(int value);
    void spinBox_Valie_changed();
    void RadioButton_Clicked();
    void pushButton_Clicked();
    void CheckBox_Clicked();
    void LineEditTextChanged(QString text);


    void GetValue(int type,stVALUE_INFO stValue);
    void SetValue(int type,stVALUE_INFO stValue);//与Video_Adjust通信

    void GetCalibTime(bool ok,stTIME_INFO stTime);

    void SetAutoSetup(stAuto_INFO stValue_Info);//与Video_Adjust通信
    void SetPresetCfg(int type);

    void GetDevcomm_Srv(int Svr_id,stDEVCOMM_SVR stDevcomm_srv);
    void GetDevcomm_Net_IP(stDEVCOMM_NET stDevcomm_Net);
    void GetDevcomm_Net_Mac(stDEVCOMM_MAC stDevcomm_Net_Mac);
    void GetDevcomm_Net_Select_Port(int type,int value);
    void GetRouter(stRouter_Out route_id_val);
    void SigSwtNextInput(SwitchNextSigOut route_id_val);

    void GetDevVer(stCfg_Ver_INFO Ver_Info);
    void VidSigIn_GetStatus(int flag,stVIDSIGIN_STATUS_ARRAY stStatus);

    void VidSigIn_Scan(int ok,stScan VinSigStatus);
    void StopScan(uchar status);
    void ScanCompleted();
    void Grab_Image_Button();
    void VidSigOutPort_GetOnOff(PortStatus portgid_id_type);
    void slot_VidSigOutPortSdiType(stOutSig_INFO stSdiStatus);
    void ComboBox_currentIndexChanged(int index);

    void DateTime_Display();
    void gt_DP_INFO(int sigid);
    void st_DP_INFO(stSCAL_INPUT_DP_INFO DP_Info);
    void slot_Read_CTmep_Scaing(int CTmep_Scaing);
    void Test();
    void displayTipsInfo(QString str);

private slots:
    void on_OSD_Hide_pushButton_clicked();
    void OSD_Hide_Mouse();
    void Hide_Message();
    void on_tabWidget_currentChanged(int index);
    void slotGetAnalogOverlay(int index);
    void slotSetRouteNotice(uchar);
    void slotSetSwtOutput(uchar ucOnOff);
signals:
    void emitSetOverlayModesData(int,int,stSCAL_ANALOG_MODE_PARAMS_Index_Array);
    void emitDispalyTipsInfo(QString);
private:
    Ui::Widget *ui;
    DbusInterface* ubus_interface;
    mvMethodOsd* dbus_server;
    TakeNotesNetworkData  Network_Data;
    ScanningDialog* sigvinscan;
    VideoAdjustment* Video_Adjust;
    DisplayMessages* display_message;
    int nDisplaySmallOsdCount;
    QMutex mutex;
    QDateTime datetime;
    bool read_HStart=false,read_VStart=false,read_HTotal=false;
    int nTabIndex,nRefCurrSigId;
    bool blIsHideScanDlg;

};


#endif // WIDGET_H
