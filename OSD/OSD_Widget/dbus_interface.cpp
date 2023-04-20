#include"dbus_interface.h"
#include<QDebug>
#include<QMessageBox>
DbusInterface::DbusInterface(QObject *parent)
{
    qRegisterMetaType<stSingleGrabStart_In>("stSingleGrabStart_In");
    qDBusRegisterMetaType<stSingleGrabStart_In>();

    qRegisterMetaType<stScan>("stScan");
    qDBusRegisterMetaType<stScan>();

    qRegisterMetaType<stVStart>("stVStart");
    qDBusRegisterMetaType<stVStart>();

    qRegisterMetaType<stHVStart>("stHVStart");
    qDBusRegisterMetaType<stHVStart>();

    qRegisterMetaType<stSCAL_ANALOG_MODE>("stSCAL_ANALOG_MODE");
    qDBusRegisterMetaType<stSCAL_ANALOG_MODE>();

    qRegisterMetaType<stSCAL_ANALOG_MODE_PARAMS_Index_Array>("stSCAL_ANALOG_MODE_PARAMS_Index_Array");
    qDBusRegisterMetaType<stSCAL_ANALOG_MODE_PARAMS_Index_Array>();

    qRegisterMetaType<stSCAL_ANALOG_MODE_PARAMS>("stSCAL_ANALOG_MODE_PARAMS");
    qDBusRegisterMetaType<stSCAL_ANALOG_MODE_PARAMS>();

    qRegisterMetaType<stAnalogOverlayCount>("stAnalogOverlayCount");
    qDBusRegisterMetaType<stAnalogOverlayCount>();

    qRegisterMetaType<stOverlayARRAY>("stOverlayARRAY");
    qDBusRegisterMetaType<stOverlayARRAY>();

    qRegisterMetaType<stSCAL_ANALOG_INPUT_PARAMS>("stSCAL_ANALOG_INPUT_PARAMS");
    qDBusRegisterMetaType<stSCAL_ANALOG_INPUT_PARAMS>();

    qRegisterMetaType<stTIME_INFO>("time");
    qDBusRegisterMetaType<stTIME_INFO>();

    qRegisterMetaType<stDEVCOMM_NET>("net");
    qDBusRegisterMetaType<stDEVCOMM_NET>();

    qRegisterMetaType<stVALUE_INFO>("value");
    qDBusRegisterMetaType<stVALUE_INFO>();

    qRegisterMetaType<stVIDSIGIN_STATUS>("stVIDSIGIN_STATUS");
    qDBusRegisterMetaType<stVIDSIGIN_STATUS>();

    qRegisterMetaType<stVIDSIGIN_STATUS_ARRAY>("stVIDSIGIN_STATUS_ARRAY");
    qDBusRegisterMetaType<stVIDSIGIN_STATUS_ARRAY>();

    qRegisterMetaType<stDEVCOMM_SVR>("stDEVCOMM_SVR");
    qDBusRegisterMetaType<stDEVCOMM_SVR>();

    qRegisterMetaType<stResolution_INFO>("resolution");
    qDBusRegisterMetaType<stResolution_INFO>();

    qRegisterMetaType<stDEVCOMM_HDCP>("stDEVCOMM_HDCP");
    qDBusRegisterMetaType<stDEVCOMM_HDCP>();

    qRegisterMetaType<stDEVCOMM_MAC>("stDEVCOMM_MAC");
    qDBusRegisterMetaType<stDEVCOMM_MAC>();

    qRegisterMetaType<stCfg_Ver_INFO>("stCfg_Ver_INFO");
    qDBusRegisterMetaType<stCfg_Ver_INFO>();

    qRegisterMetaType<stVIDGOUT_SCAL>("stVIDGOUT_SCAL");
    qDBusRegisterMetaType<stVIDGOUT_SCAL>();

    qRegisterMetaType<stDISP_COLORTEMP>("stDISP_COLORTEMP");
    qDBusRegisterMetaType<stDISP_COLORTEMP>();

    qRegisterMetaType<stRouter>("stRouter");
    qDBusRegisterMetaType<stRouter>();

    qRegisterMetaType<stRouter_In>("stRouter_In");
    qDBusRegisterMetaType<stRouter_In>();

    qRegisterMetaType<stRouter_Out>("stRouter_Out");
    qDBusRegisterMetaType<stRouter_Out>();

    qRegisterMetaType<gtOutSig_INFO>("gtOutSig_INFO");
    qDBusRegisterMetaType<gtOutSig_INFO>();

    qRegisterMetaType<stOutSig_INFO>("stOutSig_INFO");
    qDBusRegisterMetaType<stOutSig_INFO>();

    qRegisterMetaType<stGrabImage_INFO>("stGrabImage_INFO");
    qDBusRegisterMetaType<stGrabImage_INFO>();

    qRegisterMetaType<stAuto_INFO>("stAuto_INFO");
    qDBusRegisterMetaType<stAuto_INFO>();

    qRegisterMetaType<stSCAL_INPUT_DP_INFO>("stSCAL_INPUT_DP_INFO");
    qDBusRegisterMetaType<stSCAL_INPUT_DP_INFO>();

     qRegisterMetaType<gtFrequency_INFO>("gtFrequency_INFO");
     qDBusRegisterMetaType<gtFrequency_INFO>();

     qRegisterMetaType<stSwtNextInput_INFO>("stSwtNextInput_INFO");
     qDBusRegisterMetaType<stSwtNextInput_INFO>();

     qRegisterMetaType<gtSCAL_INPUT_DP_INFO>("gtSCAL_INPUT_DP_INFO");
     qDBusRegisterMetaType<gtSCAL_INPUT_DP_INFO>();

     qRegisterMetaType<stScan_INFO>("stScan_INFO");
     qDBusRegisterMetaType<stScan_INFO>();

     qRegisterMetaType<stSCAL_PRESET_PARAMS_INFO>("stSCAL_PRESET_PARAMS_INFO");
     qDBusRegisterMetaType<stSCAL_PRESET_PARAMS_INFO>();

     qRegisterMetaType<stOsdOnOff_Info>("stOsdOnOff_Info");
     qDBusRegisterMetaType<stOsdOnOff_Info>();

     qRegisterMetaType<PortStatus>("PortStatus");
     qDBusRegisterMetaType<PortStatus>();

     qRegisterMetaType<SwitchNextSigIn>("SwitchNextSigIn");
     qDBusRegisterMetaType<SwitchNextSigIn>();

     qRegisterMetaType<SwitchNextSigOut>("SwitchNextSigOut");
     qDBusRegisterMetaType<SwitchNextSigOut>();

     qRegisterMetaType<stGrabImageStaus_INFO>("stGrabImageStaus_INFO");
     qDBusRegisterMetaType<stGrabImageStaus_INFO>();

     qRegisterMetaType<stFans_INFO>("stFans_INFO");
     qDBusRegisterMetaType<stFans_INFO>();


    time=new mv::mvapp::time(GDBUS_MVAPP_BUS,
                                   GDBUS_MVAPP_OBJ_TIME,
                                   QDBusConnection::sessionBus());
    connect(time,SIGNAL(SigSetCalibTime(stTIME_INFO)),this,SLOT(Slot_GetCalibTime(stTIME_INFO)));
    connect(time,SIGNAL(SigSetWorkTime(int)),this,SLOT(Slot_GetWorkTime(int)));

    net=new mv::mvapp::comm::net(GDBUS_MVAPP_BUS,GDBUS_MVAPP_OBJ_NET,QDBusConnection::sessionBus());
    connect(net,SIGNAL(SignalNet(stDEVCOMM_NET)),this,SLOT(Slot_GetNetIp(stDEVCOMM_NET)));
    connect(net,SIGNAL(SignalCmdNetPort(int)),this,SLOT(Slot_GetNetPort(int)));
    connect(net,SIGNAL(SignalCmdNetSelect(int)),this,SLOT(Slot_GetNetSelect(int)));
    
    sigvin=new mv::mvapp::vidsig::vin(GDBUS_MVAPP_BUS,GDBUS_MVAPP_OBJ_VIDSIG,QDBusConnection::sessionBus());
    connect(sigvin,SIGNAL(SigVinSigScan(stScan)),this,SLOT(Slot_SigVinSigScan(stScan)));
    connect(sigvin,SIGNAL(SigVinSigScanAbort(uchar)),this,SLOT(Slot_SigVinSigScanAbort(uchar)));
    connect(sigvin,SIGNAL(SigVinSigSetAnalogType(stVALUE_INFO)),this,SLOT( Slot_SigVinSigGetAnalogType(stVALUE_INFO)));
    connect(sigvin,SIGNAL(SigVinSigSetBandWidth(stVALUE_INFO)),this,SLOT(Slot_SigVinSigGetBandWidth(stVALUE_INFO)));
    connect(sigvin,SIGNAL(SigVinSigSetClampWidth(stVALUE_INFO)),this,SLOT(Slot_SigVinSigGetClampWidth(stVALUE_INFO)));
    connect(sigvin,SIGNAL(SigVinSigSetFrequency(stVALUE_INFO)),this,SLOT(Slot_SigVinSigGetFrequency(stVALUE_INFO)));
    connect(sigvin,SIGNAL(SigVinSigSetNoiseReduction(stVALUE_INFO)),this,SLOT(Slot_SigVinSigGetNoiseReduction(stVALUE_INFO)));
    connect(sigvin,SIGNAL(SigVinSigSetPhase(stVALUE_INFO)),this,SLOT(Slot_SigVinSigGetPhase(stVALUE_INFO)));

    disp=new mv::mvapp::vidsig::disp(GDBUS_MVAPP_BUS,GDBUS_MVAPP_OBJ_VIDSIG,QDBusConnection::sessionBus());
    connect(disp,SIGNAL(SigVinDispSetCTemp(stDISP_COLORTEMP)),this,SLOT(Slot_SigVinDispGetCTemp(stDISP_COLORTEMP)));
    connect(disp,SIGNAL(SigVinDispSetColor(stVALUE_INFO)),this,SLOT(Slot_SigVinDispGetColor(stVALUE_INFO)));
    connect(disp,SIGNAL(SigVinDispSetContrast(stVALUE_INFO)),this,SLOT(Slot_SigVinDispGetContrast(stVALUE_INFO)));
    connect(disp,SIGNAL(SigVinDispSetDither(stVALUE_INFO)),this,SLOT(Slot_SigVinDispGetDither(stVALUE_INFO)));
    connect(disp,SIGNAL(SigVinDispSetGamma(stVALUE_INFO)),this,SLOT(Slot_SigVinDispGetGamma(stVALUE_INFO)));
    connect(disp,SIGNAL(SigVinDispSetHue(stVALUE_INFO)),this,SLOT(Slot_SigVinDispGetHue(stVALUE_INFO)));
    connect(disp,SIGNAL(SigVinDispSetLightness(stVALUE_INFO)),this,SLOT(Slot_SigVinDispGetLightness(stVALUE_INFO)));
    connect(disp,SIGNAL(SigVinDispSetSharpness(stVALUE_INFO)),this,SLOT(Slot_SigVinDispGetSharpness(stVALUE_INFO)));

    sigout=new mv::mvapp::vidsig::vout(GDBUS_MVAPP_BUS,GDBUS_MVAPP_OBJ_VIDSIG,QDBusConnection::sessionBus());
    connect(sigout,SIGNAL(SigVoutSigSetScaling(stVIDGOUT_SCAL)),this,SLOT(Slot_SigVoutSigGetScaling(stVIDGOUT_SCAL)));
    connect(sigout,SIGNAL(SigVoutSigSetFVFreq(stVALUE_INFO)),this,SLOT(Slot_SigVoutSigGetFVFreq(stVALUE_INFO)));
    connect(sigout,SIGNAL(SigVoutSigSetResolution(stResolution_INFO)),this,SLOT(Slot_SigVoutSigGetResolution(stResolution_INFO)));
    connect(sigout,SIGNAL(SigVoutSigSetSigFormat(stVALUE_INFO)),this,SLOT(Slot_SigVoutSigGetSigFormat(stVALUE_INFO)));
    connect(sigout,SIGNAL(SigVoutSigSetSmartLock(stVALUE_INFO)),this,SLOT(Slot_SigVoutSigGetSmartLock(stVALUE_INFO)));

    Grbi=new mv::mvapp::disp::grbi(GDBUS_MVAPP_BUS,GDBUS_MVAPP_OBJ_DISP,QDBusConnection::sessionBus());
    connect(Grbi,SIGNAL(SigSetDicomRisSvr(stDEVCOMM_SVR)),this,SLOT(Slot_SigGetDicomRisSvr(stDEVCOMM_SVR)));
    connect(Grbi,SIGNAL(SigSetDicomStorSvr(stDEVCOMM_SVR)),this,SLOT(Slot_SigGetDicomStorSvr(stDEVCOMM_SVR)));
    connect(Grbi,SIGNAL(SigSetFrozSpan(stFans_INFO)),this,SLOT(Slot_SigSetFrozSpan(stFans_INFO)));
    connect(Grbi,SIGNAL(SigSetGrabIndcatorSel(uchar)),this,SLOT(Slot_SigSetGrabIndcatorSel(uchar)));
    connect(Grbi,SIGNAL(SigSingleGrabStart(stGrabImageStaus_INFO)),this,SIGNAL(emitSingleGrabStart(stGrabImageStaus_INFO)));

    osd=new mv::mvapp::disp::osd(GDBUS_MVAPP_BUS,GDBUS_MVAPP_OBJ_DISP,QDBusConnection::sessionBus());
    connect(osd,SIGNAL(SigSetOnOff(stOsdOnOff_Info)),this,SLOT(Slot_SigOsdOnOff(stOsdOnOff_Info)));

    Router=new mv::mvapp::disp::router(GDBUS_MVAPP_BUS,GDBUS_MVAPP_OBJ_DISP,QDBusConnection::sessionBus());
    connect(Router,SIGNAL(SigSetRouter(stRouter_Out)),this,SLOT(Slot_SigGetRouter(stRouter_Out)));
    connect(Router,SIGNAL(SigSwtNextInput(SwitchNextSigOut)),this,SLOT(Slot_SigSwtNextInput(SwitchNextSigOut)));
    connect(Router,SIGNAL(SigSetRouteNotice(uchar)),this,SIGNAL(SigSetRouteNotice(uchar)));
    connect(Router,SIGNAL(SigSetSwtOutput(uchar)),this,SIGNAL(SigSetSwtOutput(uchar)));

    Dev_stat=new mv::mvapp::dev::stat(GDBUS_MVAPP_BUS,GDBUS_MVAPP_OBJ_DEV,QDBusConnection::sessionBus());
    connect(Dev_stat,SIGNAL(SigRestore(uchar)),this,SLOT(Slot_SigRestore(uchar)));
    connect(Dev_stat,SIGNAL(SigSetDevCfg(stCfg_Ver_INFO)),this,SLOT(Slot_SigGetDevCfg(stCfg_Ver_INFO)));

    Dev_Ver=new mv::mvapp::dev::ver(GDBUS_MVAPP_BUS,GDBUS_MVAPP_OBJ_DEV,QDBusConnection::sessionBus());

    OutSigPort=new mv::mvapp::vidport::vout(GDBUS_MVAPP_BUS,GDBUS_MVAPP_OBJ_VIDPORT,QDBusConnection::sessionBus());
    connect(OutSigPort,SIGNAL(SignalVoutPortSetOnoff(PortStatus)),this,SLOT(Slot_SigOutPortSetOnoff(PortStatus)));
    connect(OutSigPort,SIGNAL(SignalVOutPortSetSdiType(stOutSig_INFO)),this,SLOT(Slot_SigOutPortSetSDIType(stOutSig_INFO)));
}

void DbusInterface::run()
{
    QDBusPendingReply<stVIDSIGIN_STATUS_ARRAY> reply = sigvin->VinSigGetStatus(SigInId);
    //qdbusxml2cpp生成的Proxy类是采用异步的方式来传递Message，
    //所以需要调用waitARForFinished来等到Message执行完成
    reply.waitForFinished();
    if (reply.isValid())
    {
        stVIDSIGIN_STATUS_ARRAY value=reply.value(); 
        emit Sig_VidSigIn_GetStatus(Flag,value);
    }
    else
    {
        qDebug() << "value method called failed!";
    }
}

void DbusInterface::client_getWorkTime()
{   

    // 调用value方法
    QDBusPendingReply<int> reply = time->GetWorkTime();
    //qdbusxml2cpp生成的Proxy类是采用异步的方式来传递Message，
    //所以需要调用waitForFinished来等到Message执行完成
    reply.waitForFinished();
    if (reply.isValid())
    {
        int value = reply.value();
        stVALUE_INFO get_value;
        get_value.type=1;
        get_value.value=value;
        emit Sig_GetValue(WORK_TIME,get_value);

    }
    else
    {
        qDebug() << "value method called failed!";
    }
    return;
}

void DbusInterface::client_setWorkTime(int stTime)
{

    // 调用value方法
    QDBusPendingReply<> reply = time->SetWorkTime(stTime);
    //qdbusxml2cpp生成的Proxy类是采用异步的方式来传递Message，
    //所以需要调用waitForFinished来等到Message执行完成
    reply.waitForFinished();
    if (reply.isValid())
    {
    }
    else
    {
        qDebug() << "value method called failed!";
    }

    return;
}

int DbusInterface::client_getCalibTime()
{

    // 调用value方法
    QDBusPendingReply<stTIME_INFO> reply = time->GetCalibTime();
    //qdbusxml2cpp生成的Proxy类是采用异步的方式来传递Message，
    //所以需要调用waitForFinished来等到Message执行完成
    reply.waitForFinished();
    if (reply.isValid())
    {
        stTIME_INFO pstTime = reply.value();
        emit Sig_GetCalibTime(1,pstTime);
    }
    else
    {
        qDebug() << "value method called failed!";
    }

    return 0;
}

int DbusInterface::client_setCalibTime(stTIME_INFO pstTime)
{

    // 调用value方法
    QDBusPendingReply<> reply = time->SetCalibTime(pstTime);
    //qdbusxml2cpp生成的Proxy类是采用异步的方式来传递Message，
    //所以需要调用waitForFinished来等到Message执行完成
    reply.waitForFinished();
    if (reply.isValid())
    {
        emit Sig_SetMsg(QString("Successful calibration time"));
    }
    else
    {
        emit Sig_SetMsg(QString("Calibration time failed"));
    }

    return 0;
}

int DbusInterface::client_getNetIp(int uiNetId)
{
    // 调用value方法
    QDBusPendingReply<stDEVCOMM_NET> reply = net->GetNet(uiNetId);
    //qdbusxml2cpp生成的Proxy类是采用异步的方式来传递Message，
    //所以需要调用waitForFinished来等到Message执行完成
    reply.waitForFinished();
    if (reply.isValid())
    {
        stDEVCOMM_NET value = reply.value();
        emit Sig_GetDevcomm_Net_IP(value);

    }
    else
    {
        qDebug() << "value method called failed!";
    }
    return 0;
}

int DbusInterface::client_setNetIp(stDEVCOMM_NET pstNetIp)
{
    QDBusPendingReply<> reply = net->SetNet(pstNetIp);
    //qdbusxml2cpp生成的Proxy类是采用异步的方式来传递Message，
    //所以需要调用waitForFinished来等到Message执行完成
    reply.waitForFinished();
    if (reply.isValid())
    {
    }
    else
    {
       if(pstNetIp.uiNetIndex==1)
           emit Sig_SetMsg(QString("Setting Eth0 failed"));
       else
           emit Sig_SetMsg(QString("Setting Eth1 failed"));
    }

    return 0;
}

int DbusInterface::client_getNetMac(int uiNetId)
{
    // 调用value方法
    QDBusPendingReply<stDEVCOMM_MAC> reply = net->GetNetMac(uiNetId);
    //qdbusxml2cpp生成的Proxy类是采用异步的方式来传递Message，
    //所以需要调用waitForFinished来等到Message执行完成
    reply.waitForFinished();
    if (reply.isValid())
    {
        stDEVCOMM_MAC value = reply.value();
        emit Sig_GetDevcomm_Net_Mac(value);

    }
    else
    {
        qDebug() << "value method called failed!";
    }
    return 0;
}

int DbusInterface::client_GetCmdNetPort()
{
    // 调用value方法
    QDBusPendingReply<int> reply = net->GetCmdNetPort();
    //qdbusxml2cpp生成的Proxy类是采用异步的方式来传递Message，
    //所以需要调用waitForFinished来等到Message执行完成
    reply.waitForFinished();
    if (reply.isValid())
    {
        int value = reply.value();
        emit Sig_GetDevcomm_Net_Select_Port(1,value);
    }
    else
    {
        qDebug() << "value method called failed!";
    }
    return 0;
}

int DbusInterface::client_SetCmdNetPort(int NetProt)
{
    QDBusPendingReply<> reply = net->SetCmdNetPort(NetProt);
    //qdbusxml2cpp生成的Proxy类是采用异步的方式来传递Message，
    //所以需要调用waitForFinished来等到Message执行完成
    reply.waitForFinished();
    if (reply.isValid())
    {
    }
    else
    {
        emit Sig_SetMsg(QString("Setting CmdNetPort failed"));
    }

    return 0;
}

int DbusInterface::client_GetCmdNetSelect()
{
    // 调用value方法
    QDBusPendingReply<int> reply = net->GetCmdNetSelect();
    //qdbusxml2cpp生成的Proxy类是采用异步的方式来传递Message，
    //所以需要调用waitForFinished来等到Message执行完成
    reply.waitForFinished();
    if (reply.isValid())
    {
        int value = reply.value();
        emit Sig_GetDevcomm_Net_Select_Port(2,value);
    }
    else
    {
        qDebug() << "value method called failed!";
    }
    return 0;
}

int DbusInterface::client_SetCmdNetSelect(int NetSelect)
{
    QDBusPendingReply<> reply = net->SetCmdNetSelect(NetSelect);
    //qdbusxml2cpp生成的Proxy类是采用异步的方式来传递Message，
    //所以需要调用waitForFinished来等到Message执行完成
    reply.waitForFinished();
    if (reply.isValid())
    {
   }
    else
    {
        qDebug() << "value method called failed!";
    }

    return 0;
}


int DbusInterface::client_getDicommSvrInfo(int Svr_id)
{
    if(Svr_id==1)
    {
        // 调用value方法
        QDBusPendingReply<stDEVCOMM_SVR> reply = Grbi->GetDicomStorSvr();
        //qdbusxml2cpp生成的Proxy类是采用异步的方式来传递Message，
        //所以需要调用waitForFinished来等到Message执行完成
        reply.waitForFinished();
        if (reply.isValid())
        {
            stDEVCOMM_SVR value = reply.value();
            emit Sig_GetDevcomm_Srv(Svr_id,value);
            return 0;
        }
        else
        {
            return -1;
        }
    }else {
        // 调用value方法
        QDBusPendingReply<stDEVCOMM_SVR> reply = Grbi->GetDicomRisSvr();
        //qdbusxml2cpp生成的Proxy类是采用异步的方式来传递Message，
        //所以需要调用waitForFinished来等到Message执行完成
        reply.waitForFinished();
        if (reply.isValid())
        {
            stDEVCOMM_SVR value = reply.value();
            emit Sig_GetDevcomm_Srv(Svr_id,value);
            return 0;
        }
        else
        {
            return -1;
        }
    }
}

int DbusInterface::client_setDicommSvrInfo(int Svr_id,stDEVCOMM_SVR DicomSvrInfo)
{
        if(Svr_id==1)
        {
            // 调用value方法
            QDBusPendingReply<> reply = Grbi->SetDicomStorSvr(DicomSvrInfo);
            //qdbusxml2cpp生成的Proxy类是采用异步的方式来传递Message，
            //所以需要调用waitForFinished来等到Message执行完成
            reply.waitForFinished();
            if (reply.isValid())
            {
                return 0;
            }
            else
            {
                emit Sig_SetMsg(QString("Setting DicommSvrInfo failed"));
                return -1;
            }
        }else {
            // 调用value方法
            QDBusPendingReply<> reply = Grbi->SetDicomRisSvr(DicomSvrInfo);
            //qdbusxml2cpp生成的Proxy类是采用异步的方式来传递Message，
            //所以需要调用waitForFinished来等到Message执行完成
            reply.waitForFinished();
            if (reply.isValid())
            {
                return 0;
            }
            else
            {
                emit Sig_SetMsg(QString("Setting DicomRisSvrInfo failed"));
                return -1;
            }
        }
}

int DbusInterface::VidSigIn_GetAnalogType(int Sig_id)
{
    QDBusPendingReply<stVALUE_INFO> reply = sigvin->VinSigGetAnalogType(Sig_id);
    //qdbusxml2cpp生成的Proxy类是采用异步的方式来传递Message，
    //所以需要调用waitForFinished来等到Message执行完成
    reply.waitForFinished();
    if (reply.isValid())
    {
        stVALUE_INFO value = reply.value();
        emit Sig_GetValue(INPUT_CONFIGURATION,value);
    }
    else
    {
        qDebug() << "value method called failed!";
    }
    return 0;
}

int DbusInterface::VidSigIn_SetAnalogType(stVALUE_INFO stValue_Info)
{
    // 调用value方法
    QDBusPendingReply<> reply = sigvin->VinSigSetAnalogType(stValue_Info);
    //qdbusxml2cpp生成的Proxy类是采用异步的方式来传递Message，
    //所以需要调用waitForFinished来等到Message执行完成
    reply.waitForFinished();
    if (reply.isValid())
    {

    }
    else
    {
        qDebug() << "value method called failed!";
    }
    return 0;
}

int DbusInterface::VidSigIn_GetFmtPN(int Sig_id)
{
    QDBusPendingReply<stVALUE_INFO> reply = sigvin->VinSigGetVidFmtPN(Sig_id);
    //qdbusxml2cpp生成的Proxy类是采用异步的方式来传递Message，
    //所以需要调用waitForFinished来等到Message执行完成
    reply.waitForFinished();
    if (reply.isValid())
    {
        stVALUE_INFO value = reply.value();
        emit Sig_GetValue(VidFmtPN,value);
    }
    else
    {
        qDebug() << "value method called failed!";
    }
    return 0;
}

int DbusInterface::VidSigIn_GetDpDbgInfo(gtSCAL_INPUT_DP_INFO DP_Lane_Info,stSCAL_INPUT_DP_INFO *DPInfo)
{
    QDBusPendingReply<stSCAL_INPUT_DP_INFO> reply = sigvin->VinSigGetDpDbgInfo(DP_Lane_Info);
    //qdbusxml2cpp生成的Proxy类是采用异步的方式来传递Message，
    //所以需要调用waitForFinished来等到Message执行完成
    reply.waitForFinished();
    if (reply.isValid())
    {
        *DPInfo = reply.value();
    }
    else
    {
        qDebug() << "value method called failed!";
    }
    return 0;
}

void DbusInterface::VidSigIn_GetResolution(int Sig_id)
{
    QDBusPendingReply<stResolution_INFO> reply = sigvin->VinSigGetResolution(Sig_id);
    //qdbusxml2cpp生成的Proxy类是采用异步的方式来传递Message，
    //所以需要调用waitForFinished来等到Message执行完成
    reply.waitForFinished();
    if (reply.isValid())
    {
        stResolution_INFO value = reply.value();
        emit Sig_GetResolution(value);
    }
    else
    {
        qDebug() << "value method called failed!";
    }

    return;
}

void DbusInterface::VidSigIn_GetFrameVRreq(int Sig_id)
{
    QDBusPendingReply<stVALUE_INFO> reply = sigvin->VinSigGetFVFreq(Sig_id);
    //qdbusxml2cpp生成的Proxy类是采用异步的方式来传递Message，
    //所以需要调用waitForFinished来等到Message执行完成
    reply.waitForFinished();
    if (reply.isValid())
    {
        stVALUE_INFO value = reply.value();
        emit Sig_GetValue(SIGVIN_FVFREQ,value);

    }
    else
    {
        qDebug() << "value method called failed!";
    }
    return;
}
void DbusInterface::VidSigIn_GetFrameHRreq(int Sig_id)
{
    QDBusPendingReply<stVALUE_INFO> reply = sigvin->VinSigGetFHFreq(Sig_id);
    //qdbusxml2cpp生成的Proxy类是采用异步的方式来传递Message，
    //所以需要调用waitForFinished来等到Message执行完成
    reply.waitForFinished();
    if (reply.isValid())
    {
        stVALUE_INFO value = reply.value();
        emit Sig_GetValue(SIGVIN_FHFREQ,value);

    }
    else
    {
        qDebug() << "value method called failed!";
    }
    return;
}
void DbusInterface::VidSigIn_GetName(int Sig_id)
{

    return;
}

int DbusInterface::VidSigIn_SetName(int Sig_id)
{

    return 0;
}

int DbusInterface::VidSigIn_Scan(stScan_INFO Sigid_time)
{
    QDBusPendingReply<stVIDSIGIN_STATUS> reply = sigvin->VinSigScan(Sigid_time);
    //qdbusxml2cpp生成的Proxy类是采用异步的方式来传递Message，
    //所以需要调用waitForFinished来等到Message执行完成
    return 0;
}

void DbusInterface::VidSigIn_GetStatus(int Sig_id,int flag)
{
    SigInId=Sig_id;
    Flag=flag;
    this->start();
}

int DbusInterface::VinSigGetStatus(int nSigId,stVIDSIGIN_STATUS_ARRAY *stSigStatus)
{
    QDBusPendingReply<stVIDSIGIN_STATUS_ARRAY> reply = sigvin->VinSigGetStatus(nSigId);
    //qdbusxml2cpp生成的Proxy类是采用异步的方式来传递Message，
    //所以需要调用waitARForFinished来等到Message执行完成
    reply.waitForFinished();
    if (reply.isValid())
    {
        *stSigStatus=reply.value();
    }
    else
    {
        qDebug() << "value method called failed!";
    }
}

void DbusInterface::VidSigIn_GetLightness(int Sig_id)
{
    QDBusPendingReply<stVALUE_INFO> reply = disp->VinDispGetLightness(Sig_id);
    //qdbusxml2cpp生成的Proxy类是采用异步的方式来传递Message，
    //所以需要调用waitForFinished来等到Message执行完成
    reply.waitForFinished();
    if (reply.isValid())
    {
        stVALUE_INFO value = reply.value();
        qDebug()<<"OSD VidSigIn_GetLightness";
        emit Sig_GetValue(LIGHTNESS,value);

    }
    else
    {
        qDebug() << "value method called failed!";
    }

    return;
}

int DbusInterface::VidSigIn_SetLightness(stVALUE_INFO stValue_Info)
{
    qDebug()<<"OSD VidSigIn_SetLightness"<<stValue_Info.type;
    // 调用value方法
    QDBusPendingReply<> reply = disp->VinDispSetLightness(stValue_Info);
    //qdbusxml2cpp生成的Proxy类是采用异步的方式来传递Message，
    //所以需要调用waitForFinished来等到Message执行完成
    reply.waitForFinished();
    if (reply.isValid())
    {
    }
    else
    {
        qDebug() << "value method called failed!";
    }

    return 0;
}

int DbusInterface::VidSigIn_GetContrast(int Sig_id)
{

    QDBusPendingReply<stVALUE_INFO> reply = disp->VinDispGetContrast(Sig_id);
    //qdbusxml2cpp生成的Proxy类是采用异步的方式来传递Message，
    //所以需要调用waitForFinished来等到Message执行完成
    reply.waitForFinished();
    if (reply.isValid())
    {
        stVALUE_INFO value = reply.value();
        emit Sig_GetValue(CONTRAST,value);
    }
    else
    {
        qDebug() << "value method called failed!";
    }

    return 0;
}

int DbusInterface::VidSigIn_SetContrast(stVALUE_INFO stValue_Info)
{
    // 调用value方法
    QDBusPendingReply<> reply = disp->VinDispSetContrast(stValue_Info);
    //qdbusxml2cpp生成的Proxy类是采用异步的方式来传递Message，
    //所以需要调用waitForFinished来等到Message执行完成
    reply.waitForFinished();
    if (reply.isValid())
    {
    }
    else
    {
        qDebug() << "value method called failed!";
    }

    return 0;
}

int DbusInterface::VidSigIn_GetColor(int Sig_id)
{
    QDBusPendingReply<stVALUE_INFO> reply = disp->VinDispGetColor(Sig_id);
    //qdbusxml2cpp生成的Proxy类是采用异步的方式来传递Message，
    //所以需要调用waitForFinished来等到Message执行完成
    reply.waitForFinished();
    if (reply.isValid())
    {
        stVALUE_INFO value = reply.value();
        emit Sig_GetValue(COLOR,value);
    }
    else
    {
        qDebug() << "value method called failed!";
    }

    return 0;
}

int DbusInterface::VidSigIn_SetColor(stVALUE_INFO stValue_Info)
{
    // 调用value方法
    QDBusPendingReply<> reply = disp->VinDispSetColor(stValue_Info);
    //qdbusxml2cpp生成的Proxy类是采用异步的方式来传递Message，
    //所以需要调用waitForFinished来等到Message执行完成
    reply.waitForFinished();
    if (reply.isValid())
    {
    }
    else
    {
        qDebug() << "value method called failed!";
    }

    return 0;
}

int DbusInterface::VidSigIn_GetHue(int Sig_id)
{
    QDBusPendingReply<stVALUE_INFO> reply = disp->VinDispGetHue(Sig_id);
    //qdbusxml2cpp生成的Proxy类是采用异步的方式来传递Message，
    //所以需要调用waitForFinished来等到Message执行完成
    reply.waitForFinished();
    if (reply.isValid())
    {
        stVALUE_INFO value = reply.value();
        emit Sig_GetValue(HUE,value);
    }
    else
    {
        qDebug() << "value method called failed!";
    }

    return 0;
}

int DbusInterface::VidSigIn_SetHue(stVALUE_INFO stValue_Info)
{

    // 调用value方法
    QDBusPendingReply<> reply = disp->VinDispSetHue(stValue_Info);
    //qdbusxml2cpp生成的Proxy类是采用异步的方式来传递Message，
    //所以需要调用waitForFinished来等到Message执行完成
    reply.waitForFinished();
    if (reply.isValid())
    {

    }
    else
    {
        qDebug() << "value method called failed!";
    }

    return 0;
}

int DbusInterface::VidSigIn_GetSharpness(int Sig_id)
{
    QDBusPendingReply<stVALUE_INFO> reply = disp->VinDispGetSharpness(Sig_id);
    //qdbusxml2cpp生成的Proxy类是采用异步的方式来传递Message，
    //所以需要调用waitForFinished来等到Message执行完成
    reply.waitForFinished();
    if (reply.isValid())
    {
        stVALUE_INFO value = reply.value();
        emit Sig_GetValue(SHARPNESS,value);
    }
    else
    {
        qDebug() << "value method called failed!";
    }

    return 0;
}

int DbusInterface::VidSigIn_SetSharpness(stVALUE_INFO stValue_Info)
{
    qDebug()<<"OSD VidSigIn_SetSharpness"<<stValue_Info.value;
    // 调用value方法
    QDBusPendingReply<> reply = disp->VinDispSetSharpness(stValue_Info);
    //qdbusxml2cpp生成的Proxy类是采用异步的方式来传递Message，
    //所以需要调用waitForFinished来等到Message执行完成
    reply.waitForFinished();
    if (reply.isValid())
    {
    }
    else
    {
        qDebug() << "value method called failed!";
    }
    return 0;
}

int DbusInterface::VidSigIn_GetNoiseReduction(int Sig_id)
{
    QDBusPendingReply<stVALUE_INFO> reply = sigvin->VinSigGetNoiseReduction(Sig_id);
    //qdbusxml2cpp生成的Proxy类是采用异步的方式来传递Message，
    //所以需要调用waitForFinished来等到Message执行完成
    reply.waitForFinished();
    if (reply.isValid())
    {
        stVALUE_INFO value = reply.value();
        emit Sig_GetValue(NOISEREDUCTION,value);
    }
    else
    {
        qDebug() << "value method called failed!";
    }
    return 0;
}

int DbusInterface::VidSigIn_SetNoiseReduction(stVALUE_INFO stValue_Info)
{
    // 调用value方法
    QDBusPendingReply<> reply = sigvin->VinSigSetNoiseReduction(stValue_Info);
    //qdbusxml2cpp生成的Proxy类是采用异步的方式来传递Message，
    //所以需要调用waitForFinished来等到Message执行完成
    reply.waitForFinished();
    if (reply.isValid())
    {
    }
    else
    {
        qDebug() << "value method called failed!";
    }
    return 0;
}

int DbusInterface::VidSigIn_GetPhase(int Sig_id)
{
    QDBusPendingReply<stVALUE_INFO> reply = sigvin->VinSigGetPhase(Sig_id);
    //qdbusxml2cpp生成的Proxy类是采用异步的方式来传递Message，
    //所以需要调用waitForFinished来等到Message执行完成
    reply.waitForFinished();
    if (reply.isValid())
    {
        stVALUE_INFO value = reply.value();
        emit Sig_GetValue(PHASE,value);
    }
    else
    {
        qDebug() << "value method called failed!";
    }
    return 0;
}

int DbusInterface::VidSigIn_SetPhase(stVALUE_INFO stValue_Info)
{
    // 调用value方法
    QDBusPendingReply<> reply = sigvin->VinSigSetPhase(stValue_Info);
    //qdbusxml2cpp生成的Proxy类是采用异步的方式来传递Message，
    //所以需要调用waitForFinished来等到Message执行完成
    reply.waitForFinished();
    if (reply.isValid())
    {
    }
    else
    {
        qDebug() << "value method called failed!";
    }
    return 0;
}

int DbusInterface::VidSigIn_GetFrequency(int Sig_id,gtFrequency_INFO *stFrequency)
{
    QDBusPendingReply<gtFrequency_INFO> reply = sigvin->VinSigGetFrequency(Sig_id);
    //qdbusxml2cpp生成的Proxy类是采用异步的方式来传递Message，
    //所以需要调用waitForFinished来等到Message执行完成
    reply.waitForFinished();
    if (reply.isValid())
    {
        *stFrequency = reply.value();
        emit Sig_GtFrequency_INFO(*stFrequency);
    }
    else
    {
        qDebug() << "value method called failed!";
    }
    return 0;
}

int DbusInterface::VidSigIn_SetFrequency(stVALUE_INFO stValue_Info)
{
    // 调用value方法
    QDBusPendingReply<> reply = sigvin->VinSigSetFrequency(stValue_Info);
    //qdbusxml2cpp生成的Proxy类是采用异步的方式来传递Message，
    //所以需要调用waitForFinished来等到Message执行完成
    reply.waitForFinished();
    if (reply.isValid())
    {
    }
    else
    {
        qDebug() << "value method called failed!";
    }
    return 0;
}

int DbusInterface::VidSigIn_GetClampwidth(int Sig_id)
{
    QDBusPendingReply<stVALUE_INFO> reply = sigvin->VinSigGetClampWidth(Sig_id);
    //qdbusxml2cpp生成的Proxy类是采用异步的方式来传递Message，
    //所以需要调用waitForFinished来等到Message执行完成
    reply.waitForFinished();
    if (reply.isValid())
    {
        stVALUE_INFO value = reply.value();
        emit Sig_GetValue(CLAMPWIDTH,value);
    }
    else
    {
        qDebug() << "value method called failed!";
    }
    return 0;
}

int DbusInterface::VidSigIn_SetClampwidth(stVALUE_INFO stValue_Info)
{
    // 调用value方法
    QDBusPendingReply<> reply = sigvin->VinSigSetClampWidth(stValue_Info);
    //qdbusxml2cpp生成的Proxy类是采用异步的方式来传递Message，
    //所以需要调用waitForFinished来等到Message执行完成
    reply.waitForFinished();
    if (reply.isValid())
    {
    }
    else
    {
        qDebug() << "value method called failed!";
    }
    return 0;
}

int DbusInterface::VidSigIn_GetBandWidth(int Sig_id)
{
    QDBusPendingReply<stVALUE_INFO> reply = sigvin->VinSigGetBandWidth(Sig_id);
    //qdbusxml2cpp生成的Proxy类是采用异步的方式来传递Message，
    //所以需要调用waitForFinished来等到Message执行完成
    reply.waitForFinished();
    if (reply.isValid())
    {
        stVALUE_INFO value = reply.value();
        emit Sig_GetValue(BANDWIDTH,value);
        return 0;
    }
    else
    {
        qDebug() << "value method called failed!";
        return -1;
    }
}

int DbusInterface::VidSigIn_SetBandWidth(stVALUE_INFO stValue_Info)
{
    // 调用value方法
    QDBusPendingReply<> reply = sigvin->VinSigSetBandWidth(stValue_Info);
    //qdbusxml2cpp生成的Proxy类是采用异步的方式来传递Message，
    //所以需要调用waitForFinished来等到Message执行完成
    reply.waitForFinished();
    if (reply.isValid())
    {

    }
    else
    {
        qDebug() << "value method called failed!";
    }
    return 0;
}

int DbusInterface::VidSigIn_GetCTemp(stVALUE_INFO SigId_Flag)
{
    QDBusPendingReply<stDISP_COLORTEMP> reply = disp->VinDispGetCTemp(SigId_Flag);
    //qdbusxml2cpp生成的Proxy类是采用异步的方式来传递Message，
    //所以需要调用waitForFinished来等到Message执行完成
    reply.waitForFinished();
    if (reply.isValid())
    {
        stDISP_COLORTEMP value = reply.value();
        qDebug()<<"VidSigIn_GetCTemp:"<<value.uiCTempVal<<value.uiCTR<<value.uiCTG<<value.uiCTB;
        emit Sig_GetColorTemp(value);
        return 0;
    }
    else
    {
        qDebug() << "value method called failed!";
        return -1;
    }
}

int DbusInterface::VidSigIn_SetCTemp(stDISP_COLORTEMP stColorTemp_Info)
{
    qDebug()<<"VidSigIn_SetCTemp"<<stColorTemp_Info.uiDispSigId<<stColorTemp_Info.uiCTempVal<<stColorTemp_Info.uiCTR<<stColorTemp_Info.uiCTG<<stColorTemp_Info.uiCTB;
    // 调用value方法
    QDBusPendingReply<> reply = disp->VinDispSetCTemp(stColorTemp_Info);
    //qdbusxml2cpp生成的Proxy类是采用异步的方式来传递Message，
    //所以需要调用waitForFinished来等到Message执行完成
    reply.waitForFinished();
    if (reply.isValid())
    {

    }
    else
    {
        qDebug() << "value method called failed!";
    }
    return 0;
}

int DbusInterface::VidSigIn_GetGamma(int Sig_id)
{
    QDBusPendingReply<stVALUE_INFO> reply = disp->VinDispGetGamma(Sig_id);
    //qdbusxml2cpp生成的Proxy类是采用异步的方式来传递Message，
    //所以需要调用waitForFinished来等到Message执行完成
    reply.waitForFinished();
    if (reply.isValid())
    {
        stVALUE_INFO value = reply.value();
        qDebug()<<"OSD VidSigIn_GetGamma:"<<value.type<<value.value;
        emit Sig_GetValue(GAMMA,value);
        return 0;
    }
    else
    {
        qDebug() << "value method called failed!";
        return -1;
    }
}
int DbusInterface::VidSigIn_SetGamma(stVALUE_INFO stGammaInfo)
{
    // 调用value方法
    QDBusPendingReply<> reply = disp->VinDispSetGamma(stGammaInfo);
    //qdbusxml2cpp生成的Proxy类是采用异步的方式来传递Message，
    //所以需要调用waitForFinished来等到Message执行完成
    reply.waitForFinished();
    if (reply.isValid())
    {
    }
    else
    {
        qDebug() << "value method called failed!";
    }
    return 0;
}

int DbusInterface::VidSigIn_GetBkLight(int Sig_id)
{
    QDBusPendingReply<stVALUE_INFO> reply = disp->VinDispGetBkLight(Sig_id);
    //qdbusxml2cpp生成的Proxy类是采用异步的方式来传递Message，
    //所以需要调用waitForFinished来等到Message执行完成
    reply.waitForFinished();
    if (reply.isValid())
    {
        stVALUE_INFO value = reply.value();
        emit Sig_GetValue(CLAMPWIDTH,value);
        return 0;

    }
    else
    {
        qDebug() << "value method called failed!";
        return -1;
    }
}

int DbusInterface::VidSigIn_SetBkLight(stVALUE_INFO stValue_Info)
{
    // 调用value方法
    QDBusPendingReply<> reply = disp->VinDispSetBkLight(stValue_Info);
    //qdbusxml2cpp生成的Proxy类是采用异步的方式来传递Message，
    //所以需要调用waitForFinished来等到Message执行完成
    reply.waitForFinished();
    if (reply.isValid())
    {
        return 0;
    }
    else
    {
        qDebug() << "value method called failed!";
        return -1;
    }
}

int DbusInterface::VidSigIn_GetDither(int Sig_id)
{
    QDBusPendingReply<stVALUE_INFO> reply = disp->VinDispGetDither(Sig_id);
    //qdbusxml2cpp生成的Proxy类是采用异步的方式来传递Message，
    //所以需要调用waitForFinished来等到Message执行完成
    reply.waitForFinished();
    if (reply.isValid())
    {
        stVALUE_INFO value = reply.value();
        emit Sig_GetValue(DITHER,value);
        return 0;
    }
    else
    {
        qDebug() << "value method called failed!";
        return -1;
    }
}

int DbusInterface::VidSigIn_SetDither(stVALUE_INFO stValue_Info)
{

    // 调用value方法
    QDBusPendingReply<> reply = disp->VinDispSetDither(stValue_Info);
    //qdbusxml2cpp生成的Proxy类是采用异步的方式来传递Message，
    //所以需要调用waitForFinished来等到Message执行完成
    reply.waitForFinished();
    if (reply.isValid())
    {
        return 0;
    }
    else
    {
        qDebug() << "value method called failed!";
        return -1;
    }

}

int DbusInterface::VidSigIn_GetScaling(stVALUE_INFO Scaling_SigId_Flag)
{
    QDBusPendingReply<stVIDGOUT_SCAL> reply = sigout->VoutSigGetScaling(Scaling_SigId_Flag);
    //qdbusxml2cpp生成的Proxy类是采用异步的方式来传递Message，
    //所以需要调用waitForFinished来等到Message执行完成
    reply.waitForFinished();
    if (reply.isValid())
    {
        stVIDGOUT_SCAL value = reply.value();
        emit Sig_GetScaling(value);
        return 0;
    }
    else
    {
        qDebug() << "value method called failed!";
        return -1;
    }
}

int DbusInterface::VidSigIn_SetScaling(stVIDGOUT_SCAL stScalingInfo)
{
    // 调用value方法
    QDBusPendingReply<> reply = sigout->VoutSigSetScaling(stScalingInfo);
    //qdbusxml2cpp生成的Proxy类是采用异步的方式来传递Message，
    //所以需要调用waitForFinished来等到Message执行完成
    reply.waitForFinished();
    if (reply.isValid())
    {

        return 0;
    }
    else
    {
        qDebug() << "value method called failed!";
        return -1;
    }
}

int DbusInterface::VidSigIn_SetAutoSteup(stAuto_INFO stValue_Info)
{
    // 调用value方法
    QDBusPendingReply<> reply = disp->VinDispAutoSet(stValue_Info);
    //qdbusxml2cpp生成的Proxy类是采用异步的方式来传递Message，
    //所以需要调用waitForFinished来等到Message执行完成
    reply.waitForFinished();
    if (reply.isValid())
    {
        return 0;
    }
    else
    {
        qDebug() << "value method called failed!";
        return -1;
    }
}

int DbusInterface::VidSigIn_VinDispGetAutoSet(int *nStatus)
{
    // 调用value方法
    QDBusPendingReply<int> reply = disp->VinDispGetAutoSet();
    //qdbusxml2cpp生成的Proxy类是采用异步的方式来传递Message，
    //所以需要调用waitForFinished来等到Message执行完成
    reply.waitForFinished();
    if (reply.isValid())
    {
        *nStatus=reply.value();
        return 0;
    }
    else
    {
        qDebug() << "value method called failed!";
        return -1;
    }
}

int DbusInterface::VidSigIn_GetPresetParams(int SigId, stSCAL_PRESET_PARAMS_INFO *psPresetParams)
{
    QDBusPendingReply<stSCAL_PRESET_PARAMS_INFO> reply = disp->VinDispGetPresetParams(SigId);
    //qdbusxml2cpp生成的Proxy类是采用异步的方式来传递Message，
    //所以需要调用waitForFinished来等到Message执行完成
    reply.waitForFinished();
    if(reply.isValid())
    {
        *psPresetParams=reply.value();
//        psPresetParams->bDither=reply.value().bDither;
//        psPresetParams->uiBrightness=reply.value().uiBrightness;
//        psPresetParams->uiContrast=reply.value().uiContrast;
//        psPresetParams->uiColor=reply.value().uiColor;
//        psPresetParams->uiHue=reply.value().uiHue;
//        psPresetParams->uiSharpness=reply.value().uiSharpness;
//        psPresetParams->uiCTempVal=reply.value().uiCTempVal;
//        psPresetParams->uiCTR=reply.value().uiCTR;
//        psPresetParams->uiCTG=reply.value().uiCTG;
//        psPresetParams->uiCTB=reply.value().uiCTB;
//        psPresetParams->uiGamma=reply.value().uiGamma;
//        psPresetParams->uiScalVal=reply.value().uiScalVal;
//        psPresetParams->uiScalAdjVal=reply.value().uiScalAdjVal;
//        psPresetParams->HScaling=reply.value().HScaling;
//        psPresetParams->uiNR=reply.value().uiNR;
//        psPresetParams->uiClampwidth=reply.value().uiClampwidth;
//        psPresetParams->BandwidthValue=reply.value().BandwidthValue;
//        psPresetParams->uiVGAPhase=reply.value().uiVGAPhase;
//        psPresetParams->uiVGAHtotal=reply.value().uiVGAHtotal;
//        psPresetParams->uiVGAHtotal_Min=reply.value().uiVGAHtotal_Min;
//        psPresetParams->uiVGAHtotal_Max=reply.value().uiVGAHtotal_Max;

        return 0;
    }
    else
    {
        qDebug() << "value method called failed!";
        return -1;
    }
}

int DbusInterface::VinSigIn_GetHStart(int nSigId, stVStart *stHVStartValue)
{
    QDBusPendingReply<stVStart> reply =sigvin->VinSigGetHStart(nSigId);
    //qdbusxml2cpp生成的Proxy类是采用异步的方式来传递Message，
    //所以需要调用waitForFinished来等到Message执行完成
    reply.waitForFinished();
    if (reply.isValid())
    {
        *stHVStartValue=reply.value();
        qDebug()<<"OSD"<<stHVStartValue->nMinValue<<stHVStartValue->nMaxValue<<stHVStartValue->nVStartValue;
        return 0;
    }
    else
    {
        qDebug() << "value method called failed!";
        return -1;
    }
}

int DbusInterface::VinSigIn_SetHStart(stHVStart stHVStartValue)
{
    QDBusPendingReply<> reply =sigvin->VinSigSetHStart(stHVStartValue);
    //qdbusxml2cpp生成的Proxy类是采用异步的方式来传递Message，
    //所以需要调用waitForFinished来等到Message执行完成
    reply.waitForFinished();
    if (reply.isValid())
    {
        return 0;
    }
    else
    {
        qDebug() << "value method called failed!";
        return -1;
    }
}

int DbusInterface::VinSigIn_GetVStart(int nSigId, stVStart *stHVStartValue)
{
    QDBusPendingReply<stVStart> reply =sigvin->VinSigGetVStart(nSigId);
    //qdbusxml2cpp生成的Proxy类是采用异步的方式来传递Message，
    //所以需要调用waitForFinished来等到Message执行完成
    reply.waitForFinished();
    if (reply.isValid())
    {
        *stHVStartValue=reply.value();
        qDebug()<<"OSD"<<stHVStartValue->nMinValue<<stHVStartValue->nMaxValue<<stHVStartValue->nVStartValue;
        return 0;
    }
    else
    {
        qDebug() << "value method called failed!";
        return -1;
    }
}

int DbusInterface::VinSigIn_SetVStart(stHVStart stHVStartValue)
{
    QDBusPendingReply<> reply =sigvin->VinSigSetVStart(stHVStartValue);
    //qdbusxml2cpp生成的Proxy类是采用异步的方式来传递Message，
    //所以需要调用waitForFinished来等到Message执行完成
    reply.waitForFinished();
    if (reply.isValid())
    {
        return 0;
    }
    else
    {
        qDebug() << "value method called failed!";
        return -1;
    }
}

int DbusInterface::VinDispGetAnalogInputParams(stSCAL_ANALOG_INPUT_PARAMS *stScalAnalogInputParams)
{
    QDBusPendingReply<stSCAL_ANALOG_INPUT_PARAMS> reply =disp->VinDispGetAnalogInputParams();
    //qdbusxml2cpp生成的Proxy类是采用异步的方式来传递Message，
    //所以需要调用waitForFinished来等到Message执行完成
    reply.waitForFinished();
    if (reply.isValid())
    {
        *stScalAnalogInputParams=reply.value();
        qDebug()<<"VinDispGetAnalogInputParams:"<<stScalAnalogInputParams->uiH_Freq<<stScalAnalogInputParams->uiV_Freq<<stScalAnalogInputParams->uiV_Total;
        return 0;
    }
    else
    {
        qDebug() << "value method called failed!";
        return -1;
    }
}

int DbusInterface::VinDispSetAnalogParams(stSCAL_ANALOG_MODE_PARAMS stScalAnalogModeParams,int *nResult)
{
    QDBusPendingReply<int> reply =disp->VinDispSetAnalogParams(stScalAnalogModeParams);
    //qdbusxml2cpp生成的Proxy类是采用异步的方式来传递Message，
    //所以需要调用waitForFinished来等到Message执行完成
    reply.waitForFinished();
    if (reply.isValid())
    {
        emit emitSaveOverlayModeOk();
        *nResult=reply.value();
        return 0;
    }
    else
    {
        qDebug() << "value method called failed!";
        return -1;
    }
}

int DbusInterface::VinDispDebugAnalogParams(stSCAL_ANALOG_MODE_PARAMS stScalAnalogModeParams)
{
    QDBusPendingReply<> reply =disp->VinDispDebugAnalogParams(stScalAnalogModeParams);
    //qdbusxml2cpp生成的Proxy类是采用异步的方式来传递Message，
    //所以需要调用waitForFinished来等到Message执行完成
    reply.waitForFinished();
    if (reply.isValid())
    {
        return 0;
    }
    else
    {
        qDebug() << "value method called failed!";
        return -1;
    }
}

int DbusInterface::VinDispSetAnalogOverlay(int nSigId)
{
    QDBusPendingReply<> reply =disp->VinDispSetAnalogOverlay(nSigId);
    //qdbusxml2cpp生成的Proxy类是采用异步的方式来传递Message，
    //所以需要调用waitForFinished来等到Message执行完成
    reply.waitForFinished();
    if (reply.isValid())
    {
        return 0;
    }
    else
    {
        qDebug() << "value method called failed!";
        return -1;
    }
}

int DbusInterface::VinDispClearAnalogModeIndexTable()
{
    QDBusPendingReply<> reply =disp->VinDispClearAnalogModeIndexTable();
    //qdbusxml2cpp生成的Proxy类是采用异步的方式来传递Message，
    //所以需要调用waitForFinished来等到Message执行完成
    reply.waitForFinished();
    if (reply.isValid())
    {
        return 0;
    }
    else
    {
        qDebug() << "value method called failed!";
        return -1;
    }
}

int DbusInterface::VinDispGetAnalogOverlay(stAnalogOverlayCount *OverlayModeCount,stSCAL_ANALOG_MODE_PARAMS_Index_Array *stValue)
{
    stSCAL_ANALOG_MODE_PARAMS_Index_Array stValue1;
    QDBusReply<stAnalogOverlayCount> reply =disp->VinDispQtGetAnalogOverlay(*stValue);
    //qdbusxml2cpp生成的Proxy类是采用异步的方式来传递Message，
    //所以需要调用waitForFinished来等到Message执行完成
    //reply.waitForFinished();
    if (reply.isValid())
    {
        *OverlayModeCount=reply.value();
        return 0;
    }
    else
    {
        qDebug() << "value method called failed!";
        return -1;
    }
}

int DbusInterface::VinDispGetOverlayCtrlMethod(int *val)
{
    QDBusPendingReply<int> reply =disp->VinDispGetOverlayCtrlMethod();
    //qdbusxml2cpp生成的Proxy类是采用异步的方式来传递Message，
    //所以需要调用waitForFinished来等到Message执行完成
    reply.waitForFinished();
    if (reply.isValid())
    {
        *val=reply.value();
        qDebug()<<"VinDispGetOverlayCtrlMethod:"<<*val;
        return 0;
    }
    else
    {
        qDebug() << "value method called failed!";
        return -1;
    }
}

int DbusInterface::VinDispSetOverlayCtrlMethod(int val)
{
    QDBusPendingReply<> reply =disp->VinDispSetOverlayCtrlMethod(val);
    //qdbusxml2cpp生成的Proxy类是采用异步的方式来传递Message，
    //所以需要调用waitForFinished来等到Message执行完成
    reply.waitForFinished();
    if (reply.isValid())
    {
        return 0;
    }
    else
    {
        qDebug() << "value method called failed!";
        return -1;
    }
}

int DbusInterface::VidSigOut_GetFormat(int Sig_id)
{
    QDBusPendingReply<stVALUE_INFO> reply =sigout->VoutSigGetSigFormat(Sig_id);
    //qdbusxml2cpp生成的Proxy类是采用异步的方式来传递Message，
    //所以需要调用waitForFinished来等到Message执行完成
    reply.waitForFinished();
    if (reply.isValid())
    {
        stVALUE_INFO value = reply.value();
        emit Sig_GetValue(SIGFORMAT,value);
        return 0;
    }
    else
    {
        qDebug() << "value method called failed!";
        return -1;
    }
}

int DbusInterface::VidSigOut_SetFormat(stVALUE_INFO stValue_Info)
{
    // 调用value方法
    QDBusPendingReply<> reply = sigout->VoutSigSetSigFormat(stValue_Info);
    //qdbusxml2cpp生成的Proxy类是采用异步的方式来传递Message，
    //所以需要调用waitForFinished来等到Message执行完成
    reply.waitForFinished();
    if (reply.isValid())
    {
        return 0;
    }
    else
    {
        qDebug() << "value method called failed!";
        return -1;
    }
}

int DbusInterface::VidSigOut_GetSmartlock(int Sig_id)
{
    QDBusPendingReply<stVALUE_INFO> reply =sigout->VoutSigGetSmartLock(Sig_id);
    //qdbusxml2cpp生成的Proxy类是采用异步的方式来传递Message，
    //所以需要调用waitForFinished来等到Message执行完成
    reply.waitForFinished();
    if (reply.isValid())
    {
        stVALUE_INFO value = reply.value();
        emit Sig_GetValue(SMARTLOCK,value);
        return 0;
    }
    else
    {
        qDebug() << "value method called failed!";
        return -1;
    }
}

int DbusInterface::VidSigOut_SetSmartlock(stVALUE_INFO stValue_Info)
{
    // 调用value方法
    QDBusPendingReply<> reply = sigout->VoutSigSetSmartLock(stValue_Info);
    //qdbusxml2cpp生成的Proxy类是采用异步的方式来传递Message，
    //所以需要调用waitForFinished来等到Message执行完成
    reply.waitForFinished();
    if (reply.isValid())
    {
        return 0;
    }
    else
    {
        qDebug() << "value method called failed!";
        return -1;
    }
}

int DbusInterface::VidSigOut_GetStatus(int Sig_id)
{
    return 0;
}

int DbusInterface::VidSigOutPort_GetOnOff(stOutSig_INFO stRoutSigID,gtOutSig_INFO *gtRoutSigStatus)
{
    QDBusPendingReply<gtOutSig_INFO> reply =OutSigPort->VoutPortGetOnoff(stRoutSigID);
    //qdbusxml2cpp生成的Proxy类是采用异步的方式来传递Message，
    //所以需要调用waitForFinished来等到Message执行完成
    reply.waitForFinished();
    if (reply.isValid())
    {
        *gtRoutSigStatus = reply.value();
        //emit Sig_OutPortGetOnOff(value);
        return 0;
    }
    else
    {
        qDebug() << "value method called failed!";
        return -1;
    }
}

int DbusInterface::VidSigOutPort_SetOnOff(PortStatus portgid_id_type)
{
    // 调用value方法
    QDBusPendingReply<> reply = OutSigPort->VoutPortSetOnoff(portgid_id_type);
    //qdbusxml2cpp生成的Proxy类是采用异步的方式来传递Message，
    //所以需要调用waitForFinished来等到Message执行完成
    reply.waitForFinished();
    if (reply.isValid())
    {
        return 0;
    }
    else
    {
        qDebug() << "value method called failed!";
        return -1;
    }
}

int DbusInterface::VidOutPort_GetSDIType(int portgid_id, stOutSig_INFO *SDIType)
{
    QDBusPendingReply<stOutSig_INFO> reply =OutSigPort->VoutPortGetSdiType(portgid_id);
    //qdbusxml2cpp生成的Proxy类是采用异步的方式来传递Message，
    //所以需要调用waitForFinished来等到Message执行完成
    reply.waitForFinished();
    if (reply.isValid())
    {
        SDIType->gid= reply.value().gid;
        SDIType->sigid= reply.value().sigid;
        qDebug()<<"OSD Get SDI Type:"<<SDIType->gid<<SDIType->sigid;
        return 0;
    }
    else
    {
        qDebug() << "value method called failed!";
        return -1;
    }
}

int DbusInterface::VidOutPort_SetSDIType(stOutSig_INFO SDIType)
{
    qDebug()<<"OSD VidOutPort_SetSDIType:"<<SDIType.gid<<SDIType.sigid;
    QDBusPendingReply<> reply =OutSigPort->VoutPortSetSdiType(SDIType);
    //qdbusxml2cpp生成的Proxy类是采用异步的方式来传递Message，
    //所以需要调用waitForFinished来等到Message执行完成
    reply.waitForFinished();
    if (reply.isValid())
    {
        return 0;
    }
    else
    {
        qDebug() << "value method called failed!";
        return -1;
    }
}

int DbusInterface::VidRout_SetRouter(stRouter_In route_id_val)
{
    // 调用value方法
    QDBusPendingReply<> reply = Router->SetRouter(route_id_val);
    //qdbusxml2cpp生成的Proxy类是采用异步的方式来传递Message，
    //所以需要调用waitForFinished来等到Message执行完成
    reply.waitForFinished();
    if (reply.isValid())
    {
        return 0;
    }
    else
    {
        qDebug() << "value method called failed!";
        return -1;
    }
}

int DbusInterface::VidRout_GetRouter(uchar vidout_id,stRouter *GetRouterId)
{
    QDBusPendingReply<stRouter> reply = Router->GetRouter(vidout_id);
    //qdbusxml2cpp生成的Proxy类是采用异步的方式来传递Message，
    //所以需要调用waitForFinished来等到Message执行完成
    reply.waitForFinished();
    if (reply.isValid())
    {
        *GetRouterId = reply.value();
        return 0;
    }
    else
    {
        qDebug() << "value method called failed!";
        return -1;
    }
}

int DbusInterface::VidRout_SwtNextInput(SwitchNextSigIn route_id,stSwtNextInput_INFO *stSwtNextInput)
{
    // 调用value方法
    QDBusPendingReply<stSwtNextInput_INFO> reply = Router->SwtNextInput(route_id);
    //qdbusxml2cpp生成的Proxy类是采用异步的方式来传递Message，
    //所以需要调用waitForFinished来等到Message执行完成
    reply.waitForFinished();
    if (reply.isValid())
    {
       // qDebug()<<"pstSwtNextInput======"<<reply.value().siginid;
        stSwtNextInput->route=reply.value().route;
        stSwtNextInput->siginid=reply.value().siginid;
        stSwtNextInput->ret=reply.value().ret;
        return 0;
    }
    else
    {
        qDebug() << "value method called failed!";
        return -1;
    }
}

int DbusInterface::getGrabIndcatorSel(uchar* grab)
{
    QDBusPendingReply<uchar> reply =Grbi->GetGrabIndcatorSel();
    //qdbusxml2cpp生成的Proxy类是采用异步的方式来传递Message，
    //所以需要调用waitForFinished来等到Message执行完成
    reply.waitForFinished();
    if (reply.isValid())
    {
        *grab= reply.value();
        return 0;
    }
    else
    {
        qDebug() << "value method called failed!";
        return -1;
    }
}

int DbusInterface::getFrozSpan(uchar* time)
{
    QDBusPendingReply<uchar> reply =Grbi->GetFrozSpan();
    //qdbusxml2cpp生成的Proxy类是采用异步的方式来传递Message，
    //所以需要调用waitForFinished来等到Message执行完成
    reply.waitForFinished();
    if (reply.isValid())
    {
        *time= reply.value();
        return 0;
    }
    else
    {
        qDebug() << "value method called failed!";
        return -1;
    }
}

int DbusInterface::setFrozSpan(stFans_INFO stFrozSpan)
{
    QDBusPendingReply<> reply =Grbi->SetFrozSpan(stFrozSpan);
    //qdbusxml2cpp生成的Proxy类是采用异步的方式来传递Message，
    //所以需要调用waitForFinished来等到Message执行完成
    reply.waitForFinished();
    if (reply.isValid())
    {
        return 0;
    }
    else
    {
        qDebug() << "value method called failed!";
        return -1;
    }
}

int DbusInterface::VidRout_GetSwtOutput(uchar *OnOff)
{
    QDBusPendingReply<uchar> reply = Router->GetSwtOutput();
    //qdbusxml2cpp生成的Proxy类是采用异步的方式来传递Message，
    //所以需要调用waitForFinished来等到Message执行完成
    reply.waitForFinished();
    if (reply.isValid())
    {
        *OnOff= reply.value();
        return 0;
    }
    else
    {
        qDebug() << "value method called failed!";
        return -1;
    }
}

int DbusInterface::DevVers_GetDev_Ver(uchar id)
{
    QDBusPendingReply<stCfg_Ver_INFO> reply = Dev_Ver->GetVerCode(id);
    //qdbusxml2cpp生成的Proxy类是采用异步的方式来传递Message，
    //所以需要调用waitForFinished来等到Message执行完成
    reply.waitForFinished();
    if (reply.isValid())
    {
        stCfg_Ver_INFO value = reply.value();
        emit Sig_GetDevVer(value);
        return 0;
    }
    else
    {
        qDebug() << "value method called failed!";
        return -1;
    }
}

int DbusInterface::DevVers_GetSysCfg(uchar id)
{
    QDBusPendingReply<stCfg_Ver_INFO> reply = Dev_stat->GetDevCfg(id);
    //qdbusxml2cpp生成的Proxy类是采用异步的方式来传递Message，
    //所以需要调用waitForFinished来等到Message执行完成
    reply.waitForFinished();
    if (reply.isValid())
    {
        stCfg_Ver_INFO value = reply.value();
        emit sig_GetDevCfg(value);
        return 0;
    }
    else
    {
        qDebug() << "value method called failed!";
        return -1;
    }
}

int DbusInterface::DevVers_SetSysCfg(stCfg_Ver_INFO stDevCfg)
{
    // 调用value方法
    QDBusPendingReply<> reply = Dev_stat->SetDevCfg(stDevCfg);
    //qdbusxml2cpp生成的Proxy类是采用异步的方式来传递Message，
    //所以需要调用waitForFinished来等到Message执行完成
    reply.waitForFinished();
    if (reply.isValid())
    {
        return 0;
    }
    else
    {
        qDebug() << "value method called failed!";
        return -1;
    }
}

int DbusInterface::DevVers_GetDev_SN(uchar id)
{
    QDBusPendingReply<stCfg_Ver_INFO> reply = Dev_Ver->GetDevSN(id);
    //qdbusxml2cpp生成的Proxy类是采用异步的方式来传递Message，
    //所以需要调用waitForFinished来等到Message执行完成
    reply.waitForFinished();
    if (reply.isValid())
    {
        stCfg_Ver_INFO value = reply.value();
        value.id=eDEVSN_DEV+15;
        qDebug()<<"DevVers_GetDev_SN:"<<value.id<<value.value;
        emit Sig_GetDevVer(value);
        return 0;
    }
    else
    {
        qDebug() << "value method called failed!";
        return -1;
    }
}

int DbusInterface::Reset(uchar submod_id)
{
    QDBusPendingReply<> reply = Dev_stat->Reset(submod_id);
    //qdbusxml2cpp生成的Proxy类是采用异步的方式来传递Message，
    //所以需要调用waitForFinished来等到Message执行完成
    reply.waitForFinished();
    if (reply.isValid())
    {
        return 0;
    }
    else
    {
        qDebug() << "value method called failed!";
        return -1;
    }
}

int DbusInterface::GetOsdOnOff(uchar* OnOff)
{
    QDBusPendingReply<stOsdOnOff_Info> reply=osd->GetOnOff(eDEVFPGA_B);
    reply.waitForFinished();
    if (reply.isValid())
    {
      *OnOff=reply.value().value;
    }
    else
    {
        qDebug() << "value method called failed!";
    }
}

void DbusInterface::Slot_GetCalibTime(stTIME_INFO time)
{
    emit Sig_GetCalibTime(0,time);
}

void DbusInterface::Slot_GetWorkTime(int hours)
{
    //stVALUE_INFO get_value;
    //get_value.type=1;
    //get_value.value=hours;
    //emit Sig_GetValue(WORK_TIME,get_value);
}

void DbusInterface::Slot_GetNetIp(stDEVCOMM_NET stNet_Ip)
{
    emit Sig_GetDevcomm_Net_IP(stNet_Ip);
}

void DbusInterface::Slot_GetNetPort(int net_portnum)
{
    emit Sig_GetDevcomm_Net_Select_Port(1,net_portnum);
}

void DbusInterface::Slot_GetNetSelect(int select_netid)
{
    emit Sig_GetDevcomm_Net_Select_Port(2,select_netid);
}

void DbusInterface::Slot_SigVinSigScan(stScan VinSigStatus)
{
    emit Sig_VinScan(1,VinSigStatus);
}

void DbusInterface::Slot_SigVinSigScanAbort(uchar status)
{
    emit Sig_VinScanAbort(status);
}

void DbusInterface::Slot_SigVinSigGetAnalogType(stVALUE_INFO sigid_val)
{
    //emit Sig_GetValue(INPUT_CONFIGURATION,sigid_val);
}

void DbusInterface::Slot_SigVinSigGetBandWidth(stVALUE_INFO sigid_val)
{
    //emit Sig_GetValue(BANDWIDTH,sigid_val);
}

void DbusInterface::Slot_SigVinSigGetClampWidth(stVALUE_INFO sigid_val)
{
    //emit Sig_GetValue(CLAMPWIDTH,sigid_val);
}

void DbusInterface::Slot_SigVinSigGetFrequency(stVALUE_INFO sigid_val)
{

}

void DbusInterface::Slot_SigVinSigGetNoiseReduction(stVALUE_INFO sigid_val)
{
    //emit Sig_GetValue(NOISEREDUCTION,sigid_val);
}

void DbusInterface::Slot_SigVinSigGetPhase(stVALUE_INFO sigid_val)
{
    //emit Sig_GetValue(PHASE,sigid_val);
}

void DbusInterface::Slot_SigVinDispGetCTemp(stDISP_COLORTEMP sigid_val_r_g_b)
{
    //emit Sig_GetColorTemp(sigid_val_r_g_b);
}

void DbusInterface::Slot_SigVinDispGetColor(stVALUE_INFO sigid_val)
{
    //emit Sig_GetValue(COLOR,sigid_val);
}

void DbusInterface::Slot_SigVinDispGetContrast(stVALUE_INFO sigid_val)
{
    //emit Sig_GetValue(CONTRAST,sigid_val);
}

void DbusInterface::Slot_SigVinDispGetDither(stVALUE_INFO sigid_val)
{
    //emit Sig_GetValue(DITHER,sigid_val);
}

void DbusInterface::Slot_SigVinDispGetGamma(stVALUE_INFO sigid_val)
{
    //emit Sig_GetValue(GAMMA,sigid_val);
}

void DbusInterface::Slot_SigVinDispGetHue(stVALUE_INFO sigid_val)
{
    //emit Sig_GetValue(HUE,sigid_val);
}

void DbusInterface::Slot_SigVinDispGetLightness(stVALUE_INFO sigid_val)
{
    //emit Sig_GetValue(LIGHTNESS,sigid_val);
}

void DbusInterface::Slot_SigVinDispGetSharpness(stVALUE_INFO sigid_val)
{
    //emit Sig_GetValue(SHARPNESS,sigid_val);
}

void DbusInterface::VinDispSetAnalogModeDebug(int nOnOff)
{
    QDBusPendingReply<> reply=disp->VinDispSetAnalogModeDebug(nOnOff);
    reply.waitForFinished();
    if (reply.isValid())
    {

    }
    else
    {
        qDebug() << "value method called failed!";
    }
}

void DbusInterface::Slot_SigVoutSigGetScaling(stVIDGOUT_SCAL sigid_scalval_sizv_sizh)
{
    //emit Sig_GetScaling(sigid_scalval_sizv_sizh);
}

void DbusInterface::Slot_SigVoutSigGetFVFreq(stVALUE_INFO sigid_val)
{

}

void DbusInterface::Slot_SigVoutSigGetResolution(stResolution_INFO sigid_frameSiz)
{

}

void DbusInterface::Slot_SigVoutSigGetSmartLock(stVALUE_INFO sigid_val)
{
    emit Sig_GetValue(SMARTLOCK,sigid_val);
}

void DbusInterface::Slot_SigVoutSigGetSigFormat(stVALUE_INFO sigid_formatid)
{
    emit Sig_GetValue(SIGFORMAT,sigid_formatid);
}

void DbusInterface::Slot_SigGetDicomRisSvr(stDEVCOMM_SVR Ris_Svr_Val)
{
    emit Sig_GetDevcomm_Srv(2,Ris_Svr_Val);
}

void DbusInterface::Slot_SigGetDicomStorSvr(stDEVCOMM_SVR Store_Svr_Val)
{
    emit Sig_GetDevcomm_Srv(1,Store_Svr_Val);
}

void DbusInterface::Slot_SigSetGrabIndcatorSel(uchar span_val)
{
    emit Sig_SigSetGrabIndcatorSel(span_val);
}

void DbusInterface::Slot_SigSetFrozSpan(stFans_INFO stFrozSpan)
{
    emit Sig_SigSetFrozSpan(stFrozSpan);
}

void DbusInterface::Slot_SigGetRouter(stRouter_Out route_id_val)
{
    emit Sig_GetRouter(route_id_val);
}

void DbusInterface::Slot_SigSwtNextInput(SwitchNextSigOut route_id_val)
{
    emit Sig_SwtNextInput(route_id_val);
}

void DbusInterface::Slot_SigRestore(uchar cfg_id)
{

}

void DbusInterface::Slot_SigGetDevCfg(stCfg_Ver_INFO cfg_id_file)
{
    //emit sig_GetDevCfg(cfg_id_file);
}

void DbusInterface::Slot_SigUpdateVer(uchar ver_id_process)
{

}

void DbusInterface::Slot_SigOutPortSetOnoff(PortStatus signalportgid_id_Onoff)
{
    qDebug()<<"OSD Output OnOff"<<signalportgid_id_Onoff.RefCAT6<<signalportgid_id_Onoff.RefDVI<<signalportgid_id_Onoff.RefDP<<signalportgid_id_Onoff.RefSDI
           <<signalportgid_id_Onoff.LIVECAT6<<signalportgid_id_Onoff.LIVEDVI<<signalportgid_id_Onoff.LIVEDP<<signalportgid_id_Onoff.LIVESDI;
    emit Sig_OutPortGetOnOff(signalportgid_id_Onoff);
}

void DbusInterface::Slot_SigOutPortSetSDIType(stOutSig_INFO stSdiStatus)
{
    emit Sig_OutPortGetSdiType(stSdiStatus);
}

void DbusInterface::Slot_SigOsdOnOff(stOsdOnOff_Info osd_onoff)
{
    qDebug()<<"DbusInterface Slot_OsdOnOff:"<<osd_onoff.id<<osd_onoff.value;
    emit Sig_OsdOnOff(osd_onoff);
}
