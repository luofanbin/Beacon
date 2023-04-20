#ifndef MVOBJ_H
#define MVOBJ_H

#include<QObject>
#include <QtDBus/QDBusMessage>
#include <QtDBus/QDBusConnection>
#include <QtDBus/QDBusReply>
#include <QtDBus/QDBusInterface>
#include<QtDBus>
#include <QDebug>
#include <QtDBus/QDBusError>
#include<QString>

#define SYS_CONFIG_FILE_FACTORY 0
#define SYS_CONFIG_FILE_NUM 5
#define SYS_CONFIG_FILE_CURENT SYS_CONFIG_FILE_NUM+1


typedef struct stTIME_INFO_tag{
    int uiYear;
    int uiMon;
    int uiMday;
    int uiHour;
    int uiMin;
    int uiSec;

        friend QDBusArgument&operator <<(QDBusArgument&argument,const stTIME_INFO_tag&arg)
        {
            argument.beginStructure();
            argument << arg.uiYear;
            argument << arg.uiMon;
            argument << arg.uiMday;
            argument << arg.uiHour;
            argument << arg.uiMin;
            argument << arg.uiSec;
            argument.endStructure();

            return argument;

        }
        friend const QDBusArgument &operator >>(const QDBusArgument&argument, stTIME_INFO_tag&arg)
        {
            argument.beginStructure();
            argument >> arg.uiYear;
            argument >> arg.uiMon;
            argument >> arg.uiMday;
            argument >> arg.uiHour;
            argument >> arg.uiMin;
            argument >> arg.uiSec;
            argument.endStructure();

            return argument;

        }

}stTIME_INFO;
Q_DECLARE_METATYPE(stTIME_INFO);

typedef struct stVALUE_INFO_tag{
    int type;
    int value;

    friend QDBusArgument&operator <<(QDBusArgument&argument,const stVALUE_INFO_tag&arg)
    {
        argument.beginStructure();
        argument << arg.type;
        argument << arg.value;
        argument.endStructure();

        return argument;

    }
    friend const QDBusArgument &operator >>(const QDBusArgument&argument, stVALUE_INFO_tag&arg)
    {
        argument.beginStructure();
        argument >> arg.type;
        argument >> arg.value;
        argument.endStructure();

        return argument;
    }
}stVALUE_INFO;
Q_DECLARE_METATYPE(stVALUE_INFO);
typedef QList<stVALUE_INFO> stVALUE_INFO_ARRAY;
Q_DECLARE_METATYPE(stVALUE_INFO_ARRAY);


typedef struct stSTRVALUE_INFO_tag{
    int type;
    QString str_value;

    friend QDBusArgument&operator <<(QDBusArgument&argument,const stSTRVALUE_INFO_tag&arg)
    {
        argument.beginStructure();
        argument << arg.type;
        argument << arg.str_value;
        argument.endStructure();

        return argument;

    }
    friend const QDBusArgument &operator >>(const QDBusArgument&argument, stSTRVALUE_INFO_tag&arg)
    {
        argument.beginStructure();
        argument >> arg.type;
        argument >> arg.str_value;
        argument.endStructure();

        return argument;
    }
}stSTRVALUE_INFO;
Q_DECLARE_METATYPE(stSTRVALUE_INFO);

#define MAX_IPADDR_SIZE 32
#define IPADDR_FORMAT "%d.%d.%d.%d"

typedef struct stDEVCOMM_NET_tag{
    int uiNetIndex;
    int bIsDHCP;
    QString strIpAddr;
    QString strMask;
    QString strGate;
    QString strNDS1;
    QString strNDS2;

    friend QDBusArgument&operator <<(QDBusArgument&argument,const stDEVCOMM_NET_tag&arg)
    {
        argument.beginStructure();
        argument << arg.uiNetIndex;
        argument << arg.bIsDHCP;
        argument << arg.strIpAddr;
        argument << arg.strMask;
        argument << arg.strGate;
        argument << arg.strNDS1;
        argument << arg.strNDS2;
        argument.endStructure();

        return argument;

    }
    friend const QDBusArgument &operator >>(const QDBusArgument&argument, stDEVCOMM_NET_tag&arg)
    {
        argument.beginStructure();
        argument >> arg.uiNetIndex;
        argument >> arg.bIsDHCP;
        argument >> arg.strIpAddr;
        argument >> arg.strMask;
        argument >> arg.strGate;
        argument >> arg.strNDS1;
        argument >> arg.strNDS2;
        argument.endStructure();

        return argument;

    }
}stDEVCOMM_NET;
Q_DECLARE_METATYPE(stDEVCOMM_NET);

typedef struct stDEVCOMM_MAC_tag{
    int uiNetIndex;
    QString strMac;
    
    friend QDBusArgument&operator <<(QDBusArgument&argument,const stDEVCOMM_MAC_tag&arg)
    {
        argument.beginStructure();
        argument << arg.uiNetIndex;
        argument << arg.strMac;
        argument.endStructure();

        return argument;

    }
    friend const QDBusArgument &operator >>(const QDBusArgument&argument, stDEVCOMM_MAC_tag&arg)
    {
        argument.beginStructure();
        argument >> arg.uiNetIndex;
        argument >> arg.strMac;
        argument.endStructure();

        return argument;

    }
}stDEVCOMM_MAC;
Q_DECLARE_METATYPE(stDEVCOMM_MAC);

typedef struct stDEVCOMM_HDCP_tag{
    int uiNetIndex;
    int NetHdcp;
    
    friend QDBusArgument&operator <<(QDBusArgument&argument,const stDEVCOMM_HDCP_tag&arg)
    {
        argument.beginStructure();
        argument << arg.uiNetIndex;
        argument << arg.NetHdcp;
        argument.endStructure();

        return argument;

    }
    friend const QDBusArgument &operator >>(const QDBusArgument&argument, stDEVCOMM_HDCP_tag&arg)
    {
        argument.beginStructure();
        argument >> arg.uiNetIndex;
        argument >> arg.NetHdcp;
        argument.endStructure();

        return argument;

    }
}stDEVCOMM_HDCP;
Q_DECLARE_METATYPE(stDEVCOMM_HDCP);

typedef struct stDEVCOMM_SVR_tag{
    QString ip;
    int port;
    QString LAETitle;
    QString RAETitle;

    friend QDBusArgument&operator <<(QDBusArgument&argument,const stDEVCOMM_SVR_tag&arg)
    {
        argument.beginStructure();
        argument << arg.ip;
        argument << arg.port;
        argument << arg.LAETitle;
        argument << arg.RAETitle;
        argument.endStructure();

        return argument;

    }
    friend const QDBusArgument &operator >>(const QDBusArgument&argument, stDEVCOMM_SVR_tag&arg)
    {
        argument.beginStructure();
        argument >> arg.ip;
        argument >> arg.port;
        argument >> arg.LAETitle;
        argument >> arg.RAETitle;
        argument.endStructure();

        return argument;

    }

}stDEVCOMM_SVR;
Q_DECLARE_METATYPE(stDEVCOMM_SVR);

typedef struct stScan_INFO_tag{
    int sigid;
    int time;
    int cmidid;
    friend QDBusArgument&operator <<(QDBusArgument&argument,const stScan_INFO_tag&arg)
    {
        argument.beginStructure();
        argument << arg.sigid;
        argument << arg.time;
        argument << arg.cmidid;
        argument.endStructure();

        return argument;

    }
    friend const QDBusArgument &operator >>(const QDBusArgument&argument, stScan_INFO_tag&arg)
    {
        argument.beginStructure();
        argument >> arg.sigid;
        argument >> arg.time;
        argument >> arg.cmidid;
        argument.endStructure();

        return argument;
    }
}stScan_INFO;
Q_DECLARE_METATYPE(stScan_INFO);

typedef enum eDISP_COLORTEMP_tag{
    DISP_CTEMP_NATIVE =0,
    DISP_CTEMP_RGB,
    DISP_CTEMP_6500,
    DISP_CTEMP_7500,
    DISP_CTEMP_9300,
    DISP_CTEMP_10000,
    DISP_CTEMP_Cnt
}eDISP_COLORTEMP;
typedef struct stDISP_COLORTEMP_tag{
    int uiDispSigId;
    int uiCTempVal;
    int uiCTR;
    int uiCTG;
    int uiCTB;

    friend QDBusArgument&operator <<(QDBusArgument&argument,const stDISP_COLORTEMP_tag&arg)
    {
        argument.beginStructure();
        argument << arg.uiDispSigId;
        argument << arg.uiCTempVal;
        argument << arg.uiCTR;
        argument << arg.uiCTG;
        argument << arg.uiCTB;
        argument.endStructure();

        return argument;

    }
    friend const QDBusArgument &operator >>(const QDBusArgument&argument, stDISP_COLORTEMP_tag&arg)
    {
        argument.beginStructure();
        argument >> arg.uiDispSigId;
        argument >> arg.uiCTempVal;
        argument >> arg.uiCTR;
        argument >> arg.uiCTG;
        argument >> arg.uiCTB;
        argument.endStructure();

        return argument;

    }
}stDISP_COLORTEMP;
Q_DECLARE_METATYPE(stDISP_COLORTEMP);

typedef enum eDISP_GAMMA_tag{
    DISP_GAMMA_NATIVE =0,
    DISP_GAMMA_DICOM,
    DISP_GAMMA_1_8,
    DISP_GAMMA_2_0,
    DISP_GAMMA_2_2,
    DISP_GAMMA_2_4,
    DISP_GAMMA_2_6,
    DISP_GAMMA_Cnt
}eDISP_GAMMA;


typedef struct stGamma_INFO_tag{
    int id;
    double gamma;
}stGamma_INFO;

typedef enum eVIDSIGOUT_GINDEX_tag{
    eVIDSIGOUT_ALL =0,
    eVIDSIGOUT_G1,
    eVIDSIGOUT_G2,
    eVIDSIGOUT_gCnt
}eVIDSIGOUT_GINDEX;

typedef enum eDEVPORTOUT_INDEX_tag{
    eDEVPORTOUTINDEX_NULL=0,
    eDEVPORTOUT_DVI_A,
    eDEVPORTOUT_DVII_B,
    eDEVPORTOUT_DP_C,
    eDEVPORTOUT_SDI_D,
    eDEVPORTOUT_Cnt
}eDEVPORTOUT_INDEX;

typedef struct PortStatusInfo{
    unsigned char RefCAT6;//DP++
    unsigned char RefDVI;//CAT6
    unsigned char RefDP;//3G-SDI
    unsigned char RefSDI;//DVI

    unsigned char LIVECAT6;
    unsigned char LIVEDVI;
    unsigned char LIVEDP;
    unsigned char LIVESDI;
    unsigned char Status;
    int socket;
    int cmdid;
    QString strCmd;
    friend QDBusArgument&operator <<(QDBusArgument&argument,const PortStatusInfo&arg)
    {
        argument.beginStructure();
        argument << arg.RefCAT6;
        argument << arg.RefDVI;
        argument << arg.RefDP;
        argument << arg.RefSDI;
        argument << arg.LIVECAT6;
        argument << arg.LIVEDVI;
        argument << arg.LIVEDP;
        argument << arg.LIVESDI;
        argument << arg.Status;
        argument << arg.socket;
        argument << arg.cmdid;
        argument << arg.strCmd;
        argument.endStructure();

        return argument;

    }
    friend const QDBusArgument &operator >>(const QDBusArgument&argument, PortStatusInfo&arg)
    {
        argument.beginStructure();
        argument >> arg.RefCAT6;
        argument >> arg.RefDVI;
        argument >> arg.RefDP;
        argument >> arg.RefSDI;
        argument >> arg.LIVECAT6;
        argument >> arg.LIVEDVI;
        argument >> arg.LIVEDP;
        argument >> arg.LIVESDI;
        argument >> arg.Status;
        argument >> arg.socket;
        argument >> arg.cmdid;
        argument >> arg.strCmd;
        argument.endStructure();

        return argument;

    }
}PortStatus;
Q_DECLARE_METATYPE(PortStatus);

typedef enum eVIDGOUT_SCALVAL_tag{
    VIDGOUT_SCALVAL_NATIVE =0,
    VIDGOUT_SCALVAL_BESTFIT,
    VIDGOUT_SCALVAL_FULL,
    VIDGOUT_SCALVAL_ADJUST,
    VIDGOUT_SCALVAL_FourToThree,
    VIDGOUT_SCALVAL_Cnt
}eVIDGOUT_SCALVAL;
typedef struct stVIDGOUT_SCAL_tag{
    int uiSigId;
    int uiScalVal;
    int uiAdjVal;
    int uiFramWid;
    int uiFramHth;

    friend QDBusArgument&operator <<(QDBusArgument&argument,const stVIDGOUT_SCAL_tag&arg)
    {
        argument.beginStructure();
        argument << arg.uiSigId;
        argument << arg.uiScalVal;
        argument << arg.uiAdjVal;
        argument << arg.uiFramWid;
        argument << arg.uiFramHth;
        argument.endStructure();

        return argument;

    }
    friend const QDBusArgument &operator >>(const QDBusArgument&argument, stVIDGOUT_SCAL_tag&arg)
    {
        argument.beginStructure();
        argument >> arg.uiSigId;
        argument >> arg.uiScalVal;
        argument >> arg.uiAdjVal;
        argument >> arg.uiFramWid;
        argument >> arg.uiFramHth;
        argument.endStructure();

        return argument;
    }

}stVIDGOUT_SCAL;
Q_DECLARE_METATYPE(stVIDGOUT_SCAL);

typedef struct stResolution_INFO_tag{
    int id;
    int width;
    int heith;

    friend QDBusArgument&operator <<(QDBusArgument&argument,const stResolution_INFO_tag&arg)
    {
        argument.beginStructure();
        argument << arg.id;
        argument << arg.width;
        argument << arg.heith;
        argument.endStructure();

        return argument;

    }
    friend const QDBusArgument &operator >>(const QDBusArgument&argument, stResolution_INFO_tag&arg)
    {
        argument.beginStructure();
        argument >> arg.id;
        argument >> arg.width;
        argument >> arg.heith;
        argument.endStructure();

        return argument;
    }

}stResolution_INFO;
Q_DECLARE_METATYPE(stResolution_INFO);

enum {
    WORK_TIME=1,
    LIGHTNESS,
    CONTRAST,
    COLOR,
    HUE,
    SHARPNESS,
    NOISEREDUCTION,
    PHASE,
    FREQUENCY,
    CLAMPWIDTH,
    BANDWIDTH,
    INPUT_CONFIGURATION,
    SIGVIN_FVFREQ,
    SIGVIN_FHFREQ,
    DITHER,
    SMARTLOCK,
    SIGFORMAT,
    GAMMA,
    VidFmtPN,
    H_START,
    V_START,
    Cursor
};

typedef struct gtSCAL_INPUT_DP_INFO_tag{
    int SigInId;
    int uiLane_ID;


    friend QDBusArgument&operator <<(QDBusArgument&argument,const gtSCAL_INPUT_DP_INFO_tag&arg)
    {
        argument.beginStructure();
        argument << arg.SigInId;
        argument << arg.uiLane_ID;
        argument.endStructure();

        return argument;

    }
    friend const QDBusArgument &operator >>(const QDBusArgument&argument, gtSCAL_INPUT_DP_INFO_tag&arg)
    {
        argument.beginStructure();
        argument >> arg.SigInId;
        argument >> arg.uiLane_ID;
        argument.endStructure();

        return argument;
    }
}gtSCAL_INPUT_DP_INFO;
Q_DECLARE_METATYPE(gtSCAL_INPUT_DP_INFO);

typedef struct stSCAL_INPUT_DP_INFO_tag{
    int SigInId;
    int uiLane_Num;
    int uiLane_ID;
    int uiLane_VL;
    int uiLane_EL;
    int uiLane_CR;
    int uiLane_EQ;


    friend QDBusArgument&operator <<(QDBusArgument&argument,const stSCAL_INPUT_DP_INFO_tag&arg)
    {
        argument.beginStructure();
        argument << arg.SigInId;
        argument << arg.uiLane_Num;
        argument << arg.uiLane_ID;
        argument << arg.uiLane_VL;
        argument << arg.uiLane_EL;
        argument << arg.uiLane_CR;
        argument << arg.uiLane_EQ;
        argument.endStructure();

        return argument;

    }
    friend const QDBusArgument &operator >>(const QDBusArgument&argument, stSCAL_INPUT_DP_INFO_tag&arg)
    {
        argument.beginStructure();
        argument >> arg.SigInId;
        argument >> arg.uiLane_Num;
        argument >> arg.uiLane_ID;
        argument >> arg.uiLane_VL;
        argument >> arg.uiLane_EL;
        argument >> arg.uiLane_CR;
        argument >> arg.uiLane_EQ;
        argument.endStructure();

        return argument;
    }
}stSCAL_INPUT_DP_INFO;
Q_DECLARE_METATYPE(stSCAL_INPUT_DP_INFO);

typedef struct stColorKey_tag{
    unsigned char Color_R;
    unsigned char Color_G;
    unsigned char Color_B;

    friend QDBusArgument&operator <<(QDBusArgument&argument,const stColorKey_tag&arg)
    {
        argument.beginStructure();
        argument << arg.Color_R;
        argument << arg.Color_G;
        argument << arg.Color_B;
        argument.endStructure();

        return argument;

    }
    friend const QDBusArgument &operator >>(const QDBusArgument&argument, stColorKey_tag&arg)
    {
        argument.beginStructure();
        argument >> arg.Color_R;
        argument >> arg.Color_G;
        argument >> arg.Color_B;
        argument.endStructure();

        return argument;
    }
}stColorKey;
Q_DECLARE_METATYPE(stColorKey);

typedef struct stRouter_tag{
    uchar uiVidOut;
    uchar uiVidIn;
    friend QDBusArgument&operator <<(QDBusArgument&argument,const stRouter_tag&arg)
    {
        argument.beginStructure();
        argument << arg.uiVidOut;
        argument << arg.uiVidIn;
        argument.endStructure();

        return argument;

    }
    friend const QDBusArgument &operator >>(const QDBusArgument&argument, stRouter_tag&arg)
    {
        argument.beginStructure();
        argument >> arg.uiVidOut;
        argument >> arg.uiVidIn;
        argument.endStructure();

        return argument;
    }
}stRouter;
Q_DECLARE_METATYPE(stRouter);

typedef struct stRouter_In_tag{
    uchar uiVidOut;
    uchar uiVidIn;
    int socket;
    int cmdid;
    friend QDBusArgument&operator <<(QDBusArgument&argument,const stRouter_In_tag&arg)
    {
        argument.beginStructure();
        argument << arg.uiVidOut;
        argument << arg.uiVidIn;
        argument << arg.socket;
        argument << arg.cmdid;
        argument.endStructure();

        return argument;

    }
    friend const QDBusArgument &operator >>(const QDBusArgument&argument, stRouter_In_tag&arg)
    {
        argument.beginStructure();
        argument >> arg.uiVidOut;
        argument >> arg.uiVidIn;
        argument >> arg.socket;
        argument >> arg.cmdid;
        argument.endStructure();

        return argument;
    }
}stRouter_In;
Q_DECLARE_METATYPE(stRouter_In);

typedef struct stRouter_Out_tag{
    uchar uiVidOut;
    uchar uiVidIn;
    uchar status;
    int socket;
    int cmdid;
    friend QDBusArgument&operator <<(QDBusArgument&argument,const stRouter_Out_tag&arg)
    {
        argument.beginStructure();
        argument << arg.uiVidOut;
        argument << arg.uiVidIn;
        argument << arg.status;
        argument << arg.socket;
        argument << arg.cmdid;
        argument.endStructure();

        return argument;

    }
    friend const QDBusArgument &operator >>(const QDBusArgument&argument, stRouter_Out_tag&arg)
    {
        argument.beginStructure();
        argument >> arg.uiVidOut;
        argument >> arg.uiVidIn;
        argument >> arg.status;
        argument >> arg.socket;
        argument >> arg.cmdid;
        argument.endStructure();

        return argument;
    }
}stRouter_Out;
Q_DECLARE_METATYPE(stRouter_Out);

typedef QList<char> Work_List_Val;
Q_DECLARE_METATYPE(Work_List_Val);

typedef enum eDISP_PARAM_INDEX_tag{
    DISP_PARAM_RESOLUT =0,
    DISP_PARAM_PHASE,
    DISP_PARAM_GAINOFFSET,
    DISP_PARAM_GEOMETY,
    DISP_AUTO_ADJUSTMENT,
    DISP_PARAM_Cnt
}eDISP_PARAM_INDEX;

typedef struct SwitchNextSigInInfo{
    uchar id;
    int socket;
    int cmdid;
    friend QDBusArgument&operator <<(QDBusArgument&argument,const SwitchNextSigInInfo&arg)
    {
        argument.beginStructure();
        argument << arg.id;
        argument << arg.socket;
        argument << arg.cmdid;
        argument.endStructure();

        return argument;

    }
    friend const QDBusArgument &operator >>(const QDBusArgument&argument, SwitchNextSigInInfo&arg)
    {
        argument.beginStructure();
        argument >> arg.id;
        argument >> arg.socket;
        argument >> arg.cmdid;
        argument.endStructure();

        return argument;
    }
}SwitchNextSigIn;
Q_DECLARE_METATYPE(SwitchNextSigIn);

typedef struct SwitchNextSigOutInfo{
    uchar RoutId;
    uchar SigId;
    uchar Status;
    int socket;
    int cmdid;
    friend QDBusArgument&operator <<(QDBusArgument&argument,const SwitchNextSigOutInfo&arg)
    {
        argument.beginStructure();
        argument << arg.RoutId;
        argument << arg.SigId;
        argument << arg.Status;
        argument << arg.socket;
        argument << arg.cmdid;
        argument.endStructure();

        return argument;

    }
    friend const QDBusArgument &operator >>(const QDBusArgument&argument, SwitchNextSigOutInfo&arg)
    {
        argument.beginStructure();
        argument >> arg.RoutId;
        argument >> arg.SigId;
        argument >> arg.Status;
        argument >> arg.socket;
        argument >> arg.cmdid;
        argument.endStructure();

        return argument;
    }
}SwitchNextSigOut;
Q_DECLARE_METATYPE(SwitchNextSigOut);

typedef enum eVIDSIGIN_INDEX_tag{
    eVIDSIGIN_ALL =0,
    eVIDSIGIN_DVI_D3,//(CAT6_ref)
    eVIDSIGIN_DP2,//(ref)
    eVIDSIGIN_DVI_D1,
    eVIDSIGIN_DVI_A1,
    eVIDSIGIN_DVI_D2,
    eVIDSIGIN_DVI_A2,
    eVIDSIGIN_HDMI1,

    eVIDSIGIN_HDMI2,
    eVIDSIGIN_DP1,
    eVIDSIGIN_S_VIDEO1,
    eVIDSIGIN_S_VIDEO2,
    eVIDSIGIN_CVBS,
    eVIDSIGIN_SDI1,
    eVIDSIGIN_SDI2,
    eVIDSIGIN_HDMI3, //(12G_SDI)

    eVIDSIGIN_DP3,    //(live)
    eVIDSIGIN_DVI_D4, //(CAT6_live)
    eVIDSIGIN_Cnt
}eVIDSIGIN_INDEX;

typedef struct stVIDSIGIN_STATUS_tag{
    int uiSigInId;
    int bIsValid;
    int uiFrameVFreqP10;
    int uiFrameHFreqP10K;
    int uiPixelClkP10M;
    int uiFrameVActive;
    int uiFrameHActive;
    int bIsInterLace;

    friend QDBusArgument&operator <<(QDBusArgument&argument,const stVIDSIGIN_STATUS_tag&arg)
    {
        argument.beginStructure();
        argument << arg.uiSigInId;
        argument << arg.bIsValid;
        argument << arg.uiFrameVFreqP10;
        argument << arg.uiFrameHFreqP10K;
        argument << arg.uiPixelClkP10M;
        argument << arg.uiFrameVActive;
        argument << arg.uiFrameHActive;
        argument << arg.bIsInterLace;
        argument.endStructure();

        return argument;

    }
    friend const QDBusArgument &operator >>(const QDBusArgument&argument, stVIDSIGIN_STATUS_tag&arg)
    {
        argument.beginStructure();
        argument >> arg.uiSigInId;
        argument >> arg.bIsValid;
        argument >> arg.uiFrameVFreqP10;
        argument >> arg.uiFrameHFreqP10K;
        argument >> arg.uiPixelClkP10M;
        argument >> arg.uiFrameVActive;
        argument >> arg.uiFrameHActive;
        argument >> arg.bIsInterLace;
        argument.endStructure();

        return argument;
    }

}stVIDSIGIN_STATUS;
Q_DECLARE_METATYPE(stVIDSIGIN_STATUS);
typedef QList<stVIDSIGIN_STATUS> stVIDSIGIN_STATUS_ARRAY;
Q_DECLARE_METATYPE(stVIDSIGIN_STATUS_ARRAY);


typedef struct stScan_tag{
    int uiSigInId;
    int bIsValid;
    int uiFrameVFreqP10;
    int uiFrameHFreqP10K;
    int uiPixelClkP10M;
    int uiFrameVActive;
    int uiFrameHActive;
    int bIsInterLace;
    int nCmdId;

    friend QDBusArgument&operator <<(QDBusArgument&argument,const stScan_tag&arg)
    {
        argument.beginStructure();
        argument << arg.uiSigInId;
        argument << arg.bIsValid;
        argument << arg.uiFrameVFreqP10;
        argument << arg.uiFrameHFreqP10K;
        argument << arg.uiPixelClkP10M;
        argument << arg.uiFrameVActive;
        argument << arg.uiFrameHActive;
        argument << arg.bIsInterLace;
        argument << arg.nCmdId;
        argument.endStructure();

        return argument;

    }
    friend const QDBusArgument &operator >>(const QDBusArgument&argument, stScan_tag&arg)
    {
        argument.beginStructure();
        argument >> arg.uiSigInId;
        argument >> arg.bIsValid;
        argument >> arg.uiFrameVFreqP10;
        argument >> arg.uiFrameHFreqP10K;
        argument >> arg.uiPixelClkP10M;
        argument >> arg.uiFrameVActive;
        argument >> arg.uiFrameHActive;
        argument >> arg.bIsInterLace;
        argument >> arg.nCmdId;
        argument.endStructure();

        return argument;
    }

}stScan;
Q_DECLARE_METATYPE(stScan)

typedef struct stAuto_INFO_tag{
    int uiSigInId;
    int DISP_PARAM_INDEX;
    int uiValue;

    friend QDBusArgument&operator <<(QDBusArgument&argument,const stAuto_INFO_tag&arg)
    {
        argument.beginStructure();
        argument << arg.uiSigInId;
        argument << arg.DISP_PARAM_INDEX;
        argument << arg.uiValue;
        argument.endStructure();

        return argument;

    }
    friend const QDBusArgument &operator >>(const QDBusArgument&argument, stAuto_INFO_tag&arg)
    {
        argument.beginStructure();
        argument >> arg.uiSigInId;
        argument >> arg.DISP_PARAM_INDEX;
        argument >> arg.uiValue;
        argument.endStructure();

        return argument;
    }
}stAuto_INFO;
Q_DECLARE_METATYPE(stAuto_INFO);

typedef struct gtFrequency_INFO_tag{
    int uiSigInId;
    int minvlaue;
    int maxvlaue;
    int currtvalue;

    friend QDBusArgument&operator <<(QDBusArgument&argument,const gtFrequency_INFO_tag&arg)
    {
        argument.beginStructure();
        argument << arg.uiSigInId;
        argument << arg.minvlaue;
        argument << arg.maxvlaue;
        argument << arg.currtvalue;
        argument.endStructure();

        return argument;

    }
    friend const QDBusArgument &operator >>(const QDBusArgument&argument, gtFrequency_INFO_tag&arg)
    {
        argument.beginStructure();
        argument >> arg.uiSigInId;
        argument >> arg.minvlaue;
        argument >> arg.maxvlaue;
        argument >> arg.currtvalue;
        argument.endStructure();

        return argument;
    }
}gtFrequency_INFO;
Q_DECLARE_METATYPE(gtFrequency_INFO);

typedef enum eVIDSIGOUT_SIGFMT_tag{
    eVIDSIGOUT_SIGFMT_SXGA =0,
    eVIDSIGOUT_SIGFMT_WUXGA,
    eVIDSIGOUT_SIGFMT_gCnt
}eVIDSIGOUT_SIGFMT;



/*  /mv/mvapp/dev  */

typedef struct stOsdOnOff_Info_tag{
    uchar id;
    uchar value;

    friend QDBusArgument&operator <<(QDBusArgument&argument,const stOsdOnOff_Info_tag&arg)
    {
        argument.beginStructure();
        argument << arg.id;
        argument << arg.value;
        argument.endStructure();

        return argument;

    }
    friend const QDBusArgument &operator >>(const QDBusArgument&argument, stOsdOnOff_Info_tag&arg)
    {
        argument.beginStructure();
        argument >> arg.id;
        argument >> arg.value;
        argument.endStructure();

        return argument;
    }
}stOsdOnOff_Info;
Q_DECLARE_METATYPE(stOsdOnOff_Info);

typedef struct stFans_INFO_tag{
    uchar id;
    uchar value;

    friend QDBusArgument&operator <<(QDBusArgument&argument,const stFans_INFO_tag&arg)
    {
        argument.beginStructure();
        argument << arg.id;
        argument << arg.value;
        argument.endStructure();

        return argument;

    }
    friend const QDBusArgument &operator >>(const QDBusArgument&argument, stFans_INFO_tag&arg)
    {
        argument.beginStructure();
        argument >> arg.id;
        argument >> arg.value;
        argument.endStructure();

        return argument;
    }
}stFans_INFO;
Q_DECLARE_METATYPE(stFans_INFO);

typedef struct stCfg_Ver_INFO_tag{
    uchar id;
    QString value;

    friend QDBusArgument&operator <<(QDBusArgument&argument,const stCfg_Ver_INFO_tag&arg)
    {
        argument.beginStructure();
        argument << arg.id;
        argument << arg.value;
        argument.endStructure();

        return argument;

    }
    friend const QDBusArgument &operator >>(const QDBusArgument&argument, stCfg_Ver_INFO_tag&arg)
    {
        argument.beginStructure();
        argument >> arg.id;
        argument >> arg.value;
        argument.endStructure();

        return argument;
    }
}stCfg_Ver_INFO;
Q_DECLARE_METATYPE(stCfg_Ver_INFO);

typedef struct stSN_INFO_tag{
    QString id;
    QString value;

    friend QDBusArgument&operator <<(QDBusArgument&argument,const stSN_INFO_tag&arg)
    {
        argument.beginStructure();
        argument << arg.id;
        argument << arg.value;
        argument.endStructure();

        return argument;

    }
    friend const QDBusArgument &operator >>(const QDBusArgument&argument, stSN_INFO_tag&arg)
    {
        argument.beginStructure();
        argument >> arg.id;
        argument >> arg.value;
        argument.endStructure();

        return argument;
    }
}stSN_INFO;
Q_DECLARE_METATYPE(stSN_INFO);

typedef struct gtOutSig_INFO_tag{
    int gid;
    int sigid;
    int value;

    friend QDBusArgument&operator <<(QDBusArgument&argument,const gtOutSig_INFO_tag&arg)
    {
        argument.beginStructure();
        argument << arg.gid;
        argument << arg.sigid;
        argument << arg.value;
        argument.endStructure();

        return argument;

    }
    friend const QDBusArgument &operator >>(const QDBusArgument&argument, gtOutSig_INFO_tag&arg)
    {
        argument.beginStructure();
        argument >> arg.gid;
        argument >> arg.sigid;
        argument >> arg.value;
        argument.endStructure();

        return argument;
    }
}gtOutSig_INFO;
Q_DECLARE_METATYPE(gtOutSig_INFO);

typedef struct stOutSig_INFO_tag{
    int gid;
    int sigid;

    friend QDBusArgument&operator <<(QDBusArgument&argument,const stOutSig_INFO_tag&arg)
    {
        argument.beginStructure();
        argument << arg.gid;
        argument << arg.sigid;
        argument.endStructure();

        return argument;

    }
    friend const QDBusArgument &operator >>(const QDBusArgument&argument, stOutSig_INFO_tag&arg)
    {
        argument.beginStructure();
        argument >> arg.gid;
        argument >> arg.sigid;
        argument.endStructure();

        return argument;
    }
}stOutSig_INFO;
Q_DECLARE_METATYPE(stOutSig_INFO);

typedef struct stSingleGrabStart_In_tag{
    uchar id;
    int socket;
    int cmdid;

    friend QDBusArgument&operator <<(QDBusArgument&argument,const stSingleGrabStart_In_tag&arg)
    {
        argument.beginStructure();
        argument << arg.id;
        argument << arg.socket;
        argument << arg.cmdid;
        argument.endStructure();

        return argument;

    }
    friend const QDBusArgument &operator >>(const QDBusArgument&argument, stSingleGrabStart_In_tag&arg)
    {
        argument.beginStructure();
        argument >> arg.id;
        argument >> arg.socket;
        argument >> arg.cmdid;
        argument.endStructure();

        return argument;
    }
}stSingleGrabStart_In;
Q_DECLARE_METATYPE(stSingleGrabStart_In);

typedef struct stGrabImage_INFO_tag{
    uchar id;
    uchar GrabStatus;
    uchar GrabImageId;

    friend QDBusArgument&operator <<(QDBusArgument&argument,const stGrabImage_INFO_tag&arg)
    {
        argument.beginStructure();
        argument << arg.id;
        argument << arg.GrabStatus;
        argument << arg.GrabImageId;
        argument.endStructure();

        return argument;

    }
    friend const QDBusArgument &operator >>(const QDBusArgument&argument, stGrabImage_INFO_tag&arg)
    {
        argument.beginStructure();
        argument >> arg.id;
        argument >> arg.GrabStatus;
        argument >> arg.GrabImageId;
        argument.endStructure();

        return argument;
    }
}stGrabImage_INFO;
Q_DECLARE_METATYPE(stGrabImage_INFO);

typedef struct stGrabImageStaus_INFO_tag{
    uchar id;
    uchar GrabStatus;
    uchar GrabImageId;
    int socket;
    int cmdid;

    friend QDBusArgument&operator <<(QDBusArgument&argument,const stGrabImageStaus_INFO_tag&arg)
    {
        argument.beginStructure();
        argument << arg.id;
        argument << arg.GrabStatus;
        argument << arg.GrabImageId;
        argument << arg.socket;
        argument << arg.cmdid;
        argument.endStructure();

        return argument;

    }
    friend const QDBusArgument &operator >>(const QDBusArgument&argument, stGrabImageStaus_INFO_tag&arg)
    {
        argument.beginStructure();
        argument >> arg.id;
        argument >> arg.GrabStatus;
        argument >> arg.GrabImageId;
        argument >> arg.socket;
        argument >> arg.cmdid;
        argument.endStructure();

        return argument;
    }
}stGrabImageStaus_INFO;
Q_DECLARE_METATYPE(stGrabImageStaus_INFO);


typedef enum eDEVVER_INDEX_tag{
    eDEVVER_RELEASE=0,
    eDEVVER_LINUX_APP,
    eDEVVER_SCAL_A2796,
    eDEVVER_SCAL_B2796,
    eDEVVER_SCAL_C32626, //32626_INPUT
    eDEVVER_SCAL_C32626_LIVE,
    eDEVVER_SCAL_C32626_REF,
    eDEVVER_MCU_SW,
    eDEVVER_FPGA1_FW,//FPGA_REF
    eDEVVER_FPGA2_FW,//FPGA_LIVE
    eDEVVER_FPGA3_FW,//FPGA_LIVE_TO_SDI
    eDEVVER_FPGA4_FW,//FPGA_REF_TO_SDI
    eDEVVER_FPGA5_FW,//FPGA_INPUT
    eDEVVER_HARDWARE,
    eDEVVER_MCU_SUB_SW,
    eDEVVER_Cnt
}eDEVVER_INDEX;


typedef struct stSwtNextInput_INFO_tag{
    uchar route;
    uchar siginid;
    uchar ret;

    friend QDBusArgument&operator <<(QDBusArgument&argument,const stSwtNextInput_INFO_tag&arg)
    {
        argument.beginStructure();
        argument << arg.route;
        argument << arg.siginid;
        argument << arg.ret;
        argument.endStructure();

        return argument;

    }
    friend const QDBusArgument &operator >>(const QDBusArgument&argument, stSwtNextInput_INFO_tag&arg)
    {
        argument.beginStructure();
        argument >> arg.route;
        argument >> arg.siginid;
        argument >> arg.ret;
        argument.endStructure();

        return argument;
    }
}stSwtNextInput_INFO;
Q_DECLARE_METATYPE(stSwtNextInput_INFO);

typedef enum eVIDROUT_SWTNEXTINPUT_STAT_tag{
    VIDROUT_SWTNEXTINPUT_OK =0,   /*no selected input port */
    VIDROUT_SWTNEXTINPUT_NOK_INVALID_SIG,
    VIDROUT_SWTNEXTINPUT_NOK_EMPTY_SIGLIST,
    VIDROUT_SWTNEXTINPUT_STAT_Cnt
}eVIDROUT_SWTNEXTINPUT_STAT;

/*Serial No*/
typedef enum eDEVSN_INDEX_tag{
    eDEVSN_NULL =0,
    eDEVSN_DEV,
    eDEVSN_MBOARD,
    eDEVSN_IMX7,
    eDEVSN_Cnt
}eDEVSN_INDEX;

#define GRABIMG_SRCID_OSD 2

typedef enum eMVDEV_SUBMOD_ID_tag{
	eMVDEV_SUBMOD_ALL=0,  
	eMVDEV_SUBMOD_A2796,
	eMVDEV_SUBMOD_B2796,
	eMVDEV_SUBMOD_C32626, 
	eMVDEV_SUBMOD_MCU,
	eMVDEV_SUBMOD_FPGA1,
	eMVDEV_SUBMOD_FPGA2,
	eMVDEV_SUBMOD_FPGA3,
	eMVDEV_SUBMOD_Cnt,
	eMVDEV_SYSTEM_REBOOT	
}eMVDEV_SUBMOD_ID;


typedef struct stSCAL_PRESET_PARAMS_INFO_tag{
    int bDither;
    int uiBrightness;
    int uiContrast;
    int uiColor;
    int uiHue;
    int uiSharpness;
    int uiCTempVal;
    int uiCTR;
    int uiCTG;
    int uiCTB;
    int uiGamma;
    int uiScalVal;
    int uiScalAdjVal;
    int HScaling;
    int uiNR;
    int uiClampwidth;
    int BandwidthValue;	//(0 ~ 15) --- Manual, (-1) --- Auto
    int uiVGAPhase;
    int uiVGAHtotal;
    int uiVGAHtotal_Min;
    int uiVGAHtotal_Max;
    int uiHStart;
    int uiHStartMin;
    int uiHStartMax;
    int uiVStart;
    int uiVStartMin;
    int uiVStartMax;

    friend QDBusArgument&operator <<(QDBusArgument&argument,const stSCAL_PRESET_PARAMS_INFO_tag&arg)
    {
        argument.beginStructure();
        argument << arg.bDither;
        argument << arg.uiBrightness;
        argument << arg.uiContrast;
        argument << arg.uiColor;
        argument << arg.uiHue;
        argument << arg.uiSharpness;
        argument << arg.uiCTempVal;
        argument << arg.uiCTR;
        argument << arg.uiCTG;
        argument << arg.uiCTB;
        argument << arg.uiGamma;
        argument << arg.uiScalVal;
        argument << arg.uiScalAdjVal;
        argument << arg.HScaling;
        argument << arg.uiNR;
        argument << arg.uiClampwidth;
        argument << arg.BandwidthValue;
        argument << arg.uiVGAPhase;
        argument << arg.uiVGAHtotal;
        argument << arg.uiVGAHtotal_Min;
        argument << arg.uiVGAHtotal_Max;
        argument << arg.uiHStart;
        argument << arg.uiHStartMin;
        argument << arg.uiHStartMax;
        argument << arg.uiVStart;
        argument << arg.uiVStartMin;
        argument << arg.uiVStartMax;
        argument.endStructure();

        return argument;

    }
    friend const QDBusArgument &operator >>(const QDBusArgument&argument, stSCAL_PRESET_PARAMS_INFO_tag&arg)
    {
        argument.beginStructure();
        argument >> arg.bDither;
        argument >> arg.uiBrightness;
        argument >> arg.uiContrast;
        argument >> arg.uiColor;
        argument >> arg.uiHue;
        argument >> arg.uiSharpness;
        argument >> arg.uiCTempVal;
        argument >> arg.uiCTR;
        argument >> arg.uiCTG;
        argument >> arg.uiCTB;
        argument >> arg.uiGamma;
        argument >> arg.uiScalVal;
        argument >> arg.uiScalAdjVal;
        argument >> arg.HScaling;
        argument >> arg.uiNR;
        argument >> arg.uiClampwidth;
        argument >> arg.BandwidthValue;
        argument >> arg.uiVGAPhase;
        argument >> arg.uiVGAHtotal;
        argument >> arg.uiVGAHtotal_Min;
        argument >> arg.uiVGAHtotal_Max;
        argument >> arg.uiHStart;
        argument >> arg.uiHStartMin;
        argument >> arg.uiHStartMax;
        argument >> arg.uiVStart;
        argument >> arg.uiVStartMin;
        argument >> arg.uiVStartMax;
        argument.endStructure();

        return argument;
    }

}stSCAL_PRESET_PARAMS_INFO;
Q_DECLARE_METATYPE(stSCAL_PRESET_PARAMS_INFO);


typedef enum eDEVFPGA_INDEX_tag{
    eDEVFPGA_ALL =0,
    eDEVFPGA_A,  //for Video pre-selected of eDEVFPGA_B
    eDEVFPGA_B,  //K7--REF
    eDEVFPGA_C,	 //k7 --LIVE

    eDEVFPGA_Cnt
}eDEVFPGA_INDEX;


typedef struct stHVStart_tag{
    int sigid;
    int HVStartValue;

    friend QDBusArgument&operator <<(QDBusArgument&argument,const stHVStart_tag&arg)
    {
        argument.beginStructure();
        argument << arg.sigid;
        argument << arg.HVStartValue;
        argument.endStructure();

        return argument;

    }
    friend const QDBusArgument &operator >>(const QDBusArgument&argument, stHVStart_tag&arg)
    {
        argument.beginStructure();
        argument >> arg.sigid;
        argument >> arg.HVStartValue;
        argument.endStructure();

        return argument;
    }
}stHVStart;
Q_DECLARE_METATYPE(stHVStart);

typedef struct stVStart_tag{
    int sigid;
    int nMinValue;
    int nMaxValue;
    int nVStartValue;

    friend QDBusArgument&operator <<(QDBusArgument&argument,const stVStart_tag&arg)
    {
        argument.beginStructure();
        argument << arg.sigid;
        argument << arg.nMinValue;
        argument << arg.nMaxValue;
        argument << arg.nVStartValue;
        argument.endStructure();

        return argument;

    }
    friend const QDBusArgument &operator >>(const QDBusArgument&argument, stVStart_tag&arg)
    {
        argument.beginStructure();
        argument >> arg.sigid;
        argument >> arg.nMinValue;
        argument >> arg.nMaxValue;
        argument >> arg.nVStartValue;
        argument.endStructure();

        return argument;
    }
}stVStart;
Q_DECLARE_METATYPE(stVStart);

typedef struct stSCAL_ANALOG_INPUT_PARAMS_INFO_tag{
    int uiH_Freq;
    int uiV_Freq;
    int uiV_Total;

    friend QDBusArgument&operator <<(QDBusArgument&argument,const stSCAL_ANALOG_INPUT_PARAMS_INFO_tag&arg)
    {
        argument.beginStructure();
        argument << arg.uiH_Freq;
        argument << arg.uiV_Freq;
        argument << arg.uiV_Total;
        argument.endStructure();

        return argument;

    }
    friend const QDBusArgument &operator >>(const QDBusArgument&argument, stSCAL_ANALOG_INPUT_PARAMS_INFO_tag&arg)
    {
        argument.beginStructure();
        argument >> arg.uiH_Freq;
        argument >> arg.uiV_Freq;
        argument >> arg.uiV_Total;
        argument.endStructure();

        return argument;
    }
}stSCAL_ANALOG_INPUT_PARAMS;
Q_DECLARE_METATYPE(stSCAL_ANALOG_INPUT_PARAMS);

typedef struct stSCAL_ANALOG_MODE_PARAMS_tag{
    QString PresetName;
    int uiH_Freq;
    int uiV_Freq;
    int uiV_Total;
    int uiH_Total;
    int uiH_Active;
    int uiV_Active;
    int uiH_Start;
    int uiV_Start;
    int uiValidPortFlag;
    int ModeType;

    friend QDBusArgument&operator <<(QDBusArgument&argument,const stSCAL_ANALOG_MODE_PARAMS_tag&arg)
    {
        argument.beginStructure();
        argument << arg.PresetName;
        argument << arg.uiH_Freq;
        argument << arg.uiV_Freq;
        argument << arg.uiV_Total;

        argument << arg.uiH_Total;
        argument << arg.uiH_Active;
        argument << arg.uiV_Active;

        argument << arg.uiH_Start;
        argument << arg.uiV_Start;
        argument << arg.uiValidPortFlag;

        argument << arg.ModeType;
        argument.endStructure();

        return argument;

    }
    friend const QDBusArgument &operator >>(const QDBusArgument&argument, stSCAL_ANALOG_MODE_PARAMS_tag&arg)
    {
        argument.beginStructure();
        argument >> arg.PresetName;
        argument >> arg.uiV_Freq;
        argument >> arg.uiV_Total;

        argument >> arg.uiH_Total;
        argument >> arg.uiH_Active;
        argument >> arg.uiV_Active;

        argument >> arg.uiH_Start;
        argument >> arg.uiV_Start;
        argument >> arg.uiValidPortFlag;

        argument >> arg.ModeType;
        argument.endStructure();

        return argument;
    }
}stSCAL_ANALOG_MODE_PARAMS;

Q_DECLARE_METATYPE(stSCAL_ANALOG_MODE_PARAMS);


typedef struct stOverlayARRAY_tag{
    int nCount;
    int nCurrIndex;
    QByteArray qbData;

    friend QDBusArgument&operator <<(QDBusArgument&argument,const stOverlayARRAY_tag&arg)
    {
        argument.beginStructure();
        argument << arg.nCount;
        argument << arg.nCurrIndex;
        argument << arg.qbData;
        argument.endStructure();

        return argument;

    }
    friend const QDBusArgument &operator >>(const QDBusArgument&argument, stOverlayARRAY_tag&arg)
    {
        argument.beginStructure();
        argument >> arg.nCount;
        argument >> arg.nCurrIndex;
        argument >> arg.qbData;
        argument.endStructure();

        return argument;
    }
}stOverlayARRAY;
Q_DECLARE_METATYPE(stOverlayARRAY);

typedef struct stAnalogOverlayCount_tag{
    int nCount;
    int nCnrrNum;

    friend QDBusArgument&operator <<(QDBusArgument&argument,const stAnalogOverlayCount_tag&arg)
    {
        argument.beginStructure();
        argument << arg.nCount;
        argument << arg.nCnrrNum;
        argument.endStructure();

        return argument;

    }
    friend const QDBusArgument &operator >>(const QDBusArgument&argument, stAnalogOverlayCount_tag&arg)
    {
        argument.beginStructure();
        argument >> arg.nCount;
        argument >> arg.nCnrrNum;
        argument.endStructure();

        return argument;
    }
}stAnalogOverlayCount;
Q_DECLARE_METATYPE(stAnalogOverlayCount);


typedef struct stSCAL_ANALOG_MODE_PARAMS_Index_tag{
    QString PresetName;
    int uiH_Freq;
    int uiV_Freq;
    int uiV_Total;
    int uiH_Total;
    int uiH_Active;
    int uiV_Active;
    int uiH_Sync;
    int uiV_Sync;
    int uiV_Sync_Width;
    int uiValidPortFlag;
    int ModeType;
    int uiModeIndex;


    friend QDBusArgument&operator <<(QDBusArgument&argument,const stSCAL_ANALOG_MODE_PARAMS_Index_tag&arg)
    {
        argument.beginStructure();
        argument << arg.PresetName;
        argument << arg.uiH_Freq;
        argument << arg.uiV_Freq;
        argument << arg.uiV_Total;

        argument << arg.uiH_Total;
        argument << arg.uiH_Active;
        argument << arg.uiV_Active;

        argument << arg.uiH_Sync;
        argument << arg.uiV_Sync;
        argument << arg.uiV_Sync_Width;
        argument << arg.uiValidPortFlag;

        argument << arg.ModeType;
        argument << arg.uiModeIndex;
        argument.endStructure();

        return argument;

    }
    friend const QDBusArgument &operator >>(const QDBusArgument&argument, stSCAL_ANALOG_MODE_PARAMS_Index_tag&arg)
    {
        argument.beginStructure();
        argument >> arg.PresetName;
        argument >> arg.uiH_Freq;
        argument >> arg.uiV_Freq;
        argument >> arg.uiV_Total;

        argument >> arg.uiH_Total;
        argument >> arg.uiH_Active;
        argument >> arg.uiV_Active;

        argument >> arg.uiH_Sync;
        argument >> arg.uiV_Sync;
        argument >> arg.uiV_Sync_Width;
        argument >> arg.uiValidPortFlag;

        argument >> arg.ModeType;
        argument >> arg.uiModeIndex;
        argument.endStructure();

        return argument;
    }
}stSCAL_ANALOG_MODE_PARAMS_Index;
Q_DECLARE_METATYPE(stSCAL_ANALOG_MODE_PARAMS_Index);
typedef QList<stSCAL_ANALOG_MODE_PARAMS_Index> stSCAL_ANALOG_MODE_PARAMS_Index_Array;
Q_DECLARE_METATYPE(stSCAL_ANALOG_MODE_PARAMS_Index_Array);

typedef struct stSCAL_ANALOG_MODE_tag{
    int nCount;
    int nIndex;
    stSCAL_ANALOG_MODE_PARAMS_Index_Array OverlayModeList;

    friend QDBusArgument&operator <<(QDBusArgument&argument,const stSCAL_ANALOG_MODE_tag&arg)
    {
        argument.beginStructure();
        argument << arg.nCount;
        argument << arg.nIndex;
        argument << arg.OverlayModeList;

        argument.endStructure();

        return argument;

    }
    friend const QDBusArgument &operator >>(const QDBusArgument&argument, stSCAL_ANALOG_MODE_tag&arg)
    {
        argument.beginStructure();
        argument >> arg.nCount;
        argument >> arg.nIndex;
        argument >> arg.OverlayModeList;

        argument.endStructure();

        return argument;
    }
}stSCAL_ANALOG_MODE;
Q_DECLARE_METATYPE(stSCAL_ANALOG_MODE);

typedef enum eTab_INDEX_tag{
    SETTING_INDEX =0,
    NETWORK_INDEX,  //for Video pre-selected of eDEVFPGA_B
    VIDEO_REF_INDEX,  //K7--REF
    VIDEO_LIVE_INDEX,	 //k7 --LIVE
    SYSTEM_INDEX,
    VIDEO_SETTING_INDEX
}eTab_INDEX;
#endif // MVOBJ_H
