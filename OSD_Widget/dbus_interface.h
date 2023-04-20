#ifndef MVOSD_H
#define MVOSD_H
#include<QObject>
#include <QThread>
#include"mvobj.h"

#include"mvObjIFMethodTime.h"
#include"mvObjIFMethodComm.h"
#include"mvObjIFMethodVidSig.h"
#include"mvObjIFMethodDisp.h"
#include"mvObjIFMethodDev.h"
#include"mvObjIFMethodVidPort.h"

#define GDBUS_MVAPP_BUS "mv.mvapp.server"
#define GDBUS_MVAPP_OBJ_TIME "/mv/mvapp/time"
#define GDBUS_MVAPP_OBJ_NET "/mv/mvapp/comm"
#define GDBUS_MVAPP_OBJ_VIDSIG "/mv/mvapp/vidsig"
#define GDBUS_MVAPP_OBJ_DISP "/mv/mvapp/disp"
#define GDBUS_MVAPP_OBJ_DEV "/mv/mvapp/dev"
#define GDBUS_MVAPP_OBJ_VIDPORT "/mv/mvapp/vidport"
#define Int_  int *

class DbusInterface : public QThread
{
    Q_OBJECT
public:
    explicit DbusInterface(QObject *parent = 0);
    void run();

    //Time and Net correlation interface

    void client_getWorkTime();
    void client_setWorkTime(int stTime);
    int client_getCalibTime();
    int client_setCalibTime(stTIME_INFO pstTime);

    int client_getNetIp(int uiNetId);
    int client_setNetIp(stDEVCOMM_NET pstNetIp);
    int client_getNetMac(int uiNetId);
    int client_GetCmdNetPort();
    int client_SetCmdNetPort(int NetProt);
    int client_GetCmdNetSelect();
    int client_SetCmdNetSelect(int NetSelect);

    int client_getDicommSvrInfo(int Svr_id);
    int client_setDicommSvrInfo(int Svr_id,stDEVCOMM_SVR DicomSvrInfo);


    //Input signal function correlation interface
    int VidSigIn_GetAnalogType(int Sig_id);
    int VidSigIn_SetAnalogType(stVALUE_INFO stValue_Info);

    int VidSigIn_GetFmtPN(int Sig_id);
    int VidSigIn_GetDpDbgInfo(gtSCAL_INPUT_DP_INFO DP_Lane_Info,stSCAL_INPUT_DP_INFO *DPInfo);

    void VidSigIn_GetResolution(int Sig_id);
    void VidSigIn_GetFrameVRreq(int Sig_id);
    void VidSigIn_GetFrameHRreq(int Sig_id);

    void VidSigIn_GetName(int Sig_id);
    int VidSigIn_SetName(int Sig_id);

    int  VidSigIn_Scan(stScan_INFO Sigid_time);
    void VidSigIn_GetStatus(int Sig_id,int flag);
    int VinSigGetStatus(int nSigId,stVIDSIGIN_STATUS_ARRAY *stSigStatus);
    void VidSigIn_GetLightness(int Sig_id);
    int VidSigIn_SetLightness(stVALUE_INFO stValue_Info);

    int VidSigIn_GetContrast(int Sig_id);
    int VidSigIn_SetContrast(stVALUE_INFO stValue_Info);

    int VidSigIn_GetColor(int Sig_id);
    int VidSigIn_SetColor(stVALUE_INFO stValue_Info);

    int VidSigIn_GetHue(int Sig_id);
    int VidSigIn_SetHue(stVALUE_INFO stValue_Info);

    int VidSigIn_GetSharpness(int Sig_id);
    int VidSigIn_SetSharpness(stVALUE_INFO stValue_Info);

    int VidSigIn_GetNoiseReduction(int Sig_id);
    int VidSigIn_SetNoiseReduction(stVALUE_INFO stValue_Info);

    int VidSigIn_GetPhase(int Sig_id);
    int VidSigIn_SetPhase(stVALUE_INFO stValue_Info);

    int VidSigIn_GetFrequency(int Sig_id,gtFrequency_INFO *stFrequency);
    int VidSigIn_SetFrequency(stVALUE_INFO stValue_Info);

    int VidSigIn_GetClampwidth(int Sig_id);
    int VidSigIn_SetClampwidth(stVALUE_INFO stValue_Info);

    int VidSigIn_GetBandWidth(int Sig_id);
    int VidSigIn_SetBandWidth(stVALUE_INFO stValue_Info);

    int VidSigIn_GetCTemp(stVALUE_INFO SigId_Flag);

    int VidSigIn_GetGamma(int Sig_id);
    int VidSigIn_SetGamma(stVALUE_INFO stGammaInfo);

    int VidSigIn_GetBkLight(int Sig_id);
    int VidSigIn_SetBkLight(stVALUE_INFO stValue_Info);

    int VidSigIn_GetDither(int Sig_id);
    int VidSigIn_SetDither(stVALUE_INFO stValue_Info);

    int VidSigIn_GetScaling(stVALUE_INFO Scaling_SigId_Flag);

    int VidSigIn_SetAutoSteup(stAuto_INFO stValue_Info);
    int VidSigIn_VinDispGetAutoSet(int *nStatus);

    int VidSigIn_GetPresetParams(int SigId,stSCAL_PRESET_PARAMS_INFO *psPresetParams);
    int VinSigIn_GetHStart(int nSigId,stVStart *stHVStartValue);
    int VinSigIn_SetHStart(stHVStart stHVStartValue);
    int VinSigIn_GetVStart(int nSigId,stVStart *stHVStartValue);
    int VinSigIn_SetVStart(stHVStart stHVStartValue);
    int VinDispGetAnalogInputParams(stSCAL_ANALOG_INPUT_PARAMS *stScalAnalogInputParams);
    int VinDispSetAnalogParams(stSCAL_ANALOG_MODE_PARAMS stScalAnalogModeParams,int *nResult);
    int VinDispDebugAnalogParams(stSCAL_ANALOG_MODE_PARAMS stScalAnalogModeParams);
    int VinDispSetAnalogOverlay(int nSigId);
    int VinDispClearAnalogModeIndexTable();
    int VinDispGetAnalogOverlay(stAnalogOverlayCount *OverlayModeCount,stSCAL_ANALOG_MODE_PARAMS_Index_Array *stValue);
    int VinDispGetOverlayCtrlMethod(int *val);
    int VinDispSetOverlayCtrlMethod(int val);

    //Output signal function correlation interface
    int VidSigOut_GetFormat(int Sig_id);
    int VidSigOut_SetFormat(stVALUE_INFO stValue_Info);

    int VidSigOut_GetSmartlock(int Sig_id);
    int VidSigOut_SetSmartlock(stVALUE_INFO stValue_Info);

    int VidSigOut_GetStatus(int Sig_id);
    int VidSigOutPort_GetOnOff(stOutSig_INFO stRoutSigID,gtOutSig_INFO *gtRoutSigStatus);
    int VidSigOutPort_SetOnOff(PortStatus portgid_id_type);

    int VidOutPort_GetSDIType(int portgid_id,stOutSig_INFO* SDIType);
    int VidOutPort_SetSDIType(stOutSig_INFO SDIType);

    /*Router*/
    int VidRout_SetRouter(stRouter_In route_id_val);
    int VidRout_GetRouter(uchar vidout_id,stRouter *GetRouterId);
    int VidRout_SwtNextInput(SwitchNextSigIn route_id,stSwtNextInput_INFO *stSwtNextInput);
    int getGrabIndcatorSel(uchar* grab);
    int getFrozSpan(uchar* time);
    int setFrozSpan(stFans_INFO stFrozSpan);
    int VidRout_GetSwtOutput(uchar *OnOff);

    /*System*/
    int DevVers_GetDev_Ver(uchar id);
    int DevVers_GetSysCfg(uchar id);
    int DevVers_SetSysCfg(stCfg_Ver_INFO stDevCfg);
    int DevVers_GetDev_SN(uchar id);
    int Reset(uchar submod_id);

    int GetOsdOnOff(uchar* OnOff);

public slots:
    int VidSigIn_SetCTemp(stDISP_COLORTEMP stColorTemp_Info);
    int VidSigIn_SetScaling(stVIDGOUT_SCAL stScalingInfo);

signals:
    void Sig_GetCalibTime(bool,stTIME_INFO);
    void Sig_GetNet(stDEVCOMM_NET);
    void Sig_GetValue(int,stVALUE_INFO);
    void Sig_GetColorTemp(stDISP_COLORTEMP);
    void Sig_GetGamma(stVALUE_INFO);
    void Sig_GetScaling(stVIDGOUT_SCAL);
    void Sig_GetResolution(stResolution_INFO);
    void Sig_GetDevcomm_Srv(int,stDEVCOMM_SVR);
    void Sig_GetDevcomm_Net_IP(stDEVCOMM_NET);
    void Sig_GetDevcomm_Net_Mac(stDEVCOMM_MAC);
    void Sig_GetDevcomm_Net_Select_Port(int,int);
    void Sig_GetRouter(stRouter_Out);
    void Sig_SwtNextInput(SwitchNextSigOut);
    void Sig_GetDevVer(stCfg_Ver_INFO);
    void sig_GetDevCfg(stCfg_Ver_INFO);
    void Sig_VidSigIn_GetStatus(int,stVIDSIGIN_STATUS_ARRAY);
    void Sig_VinScan(int,stScan);
    void Sig_VinScanAbort(uchar);
    void Sig_OutPortGetOnOff(PortStatus);
    void Sig_OutPortGetSdiType(stOutSig_INFO);
    void Sig_GtFrequency_INFO(gtFrequency_INFO);
    void Sig_SigSetGrabIndcatorSel(uchar);
    void Sig_SigSetFrozSpan(stFans_INFO);
    void Sig_SetMsg(QString);
    void Sig_OsdOnOff(stOsdOnOff_Info);
    void emitSingleGrabStart(stGrabImageStaus_INFO);
    void emitSaveOverlayModeOk();
    void SigSetRouteNotice(uchar output_val);
    void SigSetSwtOutput(uchar);
public slots:
    //time
    void Slot_GetCalibTime(stTIME_INFO time);
    void Slot_GetWorkTime(int hours);

    //net
    void Slot_GetNetIp(stDEVCOMM_NET stNet_Ip);
    void Slot_GetNetPort(int net_portnum);
    void Slot_GetNetSelect(int select_netid);

    //sigvin
    void Slot_SigVinSigScan(stScan VinSigStatus);
    void Slot_SigVinSigScanAbort(uchar status);
    void Slot_SigVinSigGetAnalogType(stVALUE_INFO sigid_val);
    void Slot_SigVinSigGetBandWidth(stVALUE_INFO sigid_val);
    void Slot_SigVinSigGetClampWidth(stVALUE_INFO sigid_val);
    void Slot_SigVinSigGetFrequency(stVALUE_INFO sigid_val);
    void Slot_SigVinSigGetNoiseReduction(stVALUE_INFO sigid_val);
    void Slot_SigVinSigGetPhase(stVALUE_INFO sigid_val);

    //disp
    void Slot_SigVinDispGetCTemp(stDISP_COLORTEMP sigid_val_r_g_b);
    void Slot_SigVinDispGetColor(stVALUE_INFO sigid_val);
    void Slot_SigVinDispGetContrast(stVALUE_INFO sigid_val);
    void Slot_SigVinDispGetDither(stVALUE_INFO sigid_val);
    void Slot_SigVinDispGetGamma(stVALUE_INFO sigid_val);
    void Slot_SigVinDispGetHue(stVALUE_INFO sigid_val);
    void Slot_SigVinDispGetLightness(stVALUE_INFO sigid_val);
    void Slot_SigVinDispGetSharpness(stVALUE_INFO sigid_val);
    void VinDispSetAnalogModeDebug(int nOnOff);
    //sigout
    void Slot_SigVoutSigGetScaling(stVIDGOUT_SCAL sigid_scalval_sizv_sizh);
    void Slot_SigVoutSigGetFVFreq(stVALUE_INFO sigid_val);
    void Slot_SigVoutSigGetResolution(stResolution_INFO sigid_frameSiz);
    void Slot_SigVoutSigGetSmartLock(stVALUE_INFO sigid_val);
    void Slot_SigVoutSigGetSigFormat(stVALUE_INFO sigid_formatid);

    //Grbi
    void Slot_SigGetDicomRisSvr(stDEVCOMM_SVR Ris_Svr_Val);
    void Slot_SigGetDicomStorSvr(stDEVCOMM_SVR Store_Svr_Val);
    void Slot_SigSetGrabIndcatorSel(uchar span_val);
    void Slot_SigSetFrozSpan(stFans_INFO stFrozSpan);

    //Router
    void Slot_SigGetRouter(stRouter_Out route_id_val);
    void Slot_SigSwtNextInput(SwitchNextSigOut route_id_val);

    //Fans

    //Dev_stat
    void Slot_SigRestore(uchar cfg_id);
    void Slot_SigGetDevCfg(stCfg_Ver_INFO cfg_id_file);

    //Dev_Ver
    void Slot_SigUpdateVer(uchar ver_id_process);

    void Slot_SigOutPortSetOnoff(PortStatus signalportgid_id_Onoff);
    void Slot_SigOutPortSetSDIType(stOutSig_INFO stSdiStatus);

    //osd
    void Slot_SigOsdOnOff(stOsdOnOff_Info osd_onoff);
public:
    QDBusInterface* interface;
    mv::mvapp::time* time;
    mv::mvapp::comm::net *net;
    mv::mvapp::vidsig::vin* sigvin;
    mv::mvapp::vidsig::disp* disp;
    mv::mvapp::vidsig::vout* sigout;
    mv::mvapp::disp::grbi* Grbi;
    mv::mvapp::disp::router* Router;
    mv::mvapp::disp::osd * osd;
    mv::mvapp::dev::fans* Fans;
    mv::mvapp::dev::stat* Dev_stat;
    mv::mvapp::dev::ver* Dev_Ver;
    mv::mvapp::vidport::vout* OutSigPort;

    int SigInId,Flag;

};

#endif // MVOSD_H
