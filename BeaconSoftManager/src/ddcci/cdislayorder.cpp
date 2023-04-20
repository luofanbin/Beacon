#include "cdislayorder.h"
#include "DdcVcpForGe.h"
#include <string.h>
#include"DdcProtocDefine.h"
#include <QThread>
#include "userdefine.h"
#define min(a,b) ((a)>(b) ? (b):(a))

CDislayOrder::CDislayOrder()
{

}

void CDislayOrder::SentKeyControl(unsigned char chKey,bool isDoubleClick)
{
    if (isDoubleClick)
        chKey=chKey |0x80;
    else
        chKey=chKey |0x00;
    unsigned char _buff[3];
    _buff[0]=DDC_ORDER_MENU_KEY ;
    _buff[1]=chKey>>8;
    _buff[2]=chKey;
    Write(_buff,sizeof(_buff),true);

}

void CDislayOrder::setBright(int nBright )
{
    unsigned char _buff[3];
    _buff[0]=DDC_ORDER_BRIGHT;
    _buff[1]=nBright>>8;
    _buff[2]=nBright;
    Write(_buff,sizeof(_buff),true);

}

void CDislayOrder::setThreePointBright(int type,int nBright )
{
    unsigned char _buff[3];
    _buff[0]=DDC_ORDER_SET_THREE_BRIGHT;
    _buff[1]=type;
    _buff[2]=nBright;
    Write(_buff,sizeof(_buff),true);
}

void CDislayOrder::turnOnOffDisplay(bool blIsOn )
{
    int n_value=0x02;
    if (blIsOn)
        n_value=0x01;
    unsigned char _buff[3];
    _buff[0]=DDC_ORDER_CONTROL_TURN;
    _buff[1]=n_value>>8;
    _buff[2]=n_value;
    Write(_buff,sizeof(_buff),true);

}
bool CDislayOrder::getThreeBright(int &nLow,int &nMid,int &nHight )
{

    unsigned char _buff_read[sizeof(DDCBi_GetVCPFeature_ReplyCmd_t)];
    DDCBi_GetVCPFeature_ReplyCmd_t *p_vcp_return=(DDCBi_GetVCPFeature_ReplyCmd_t*)_buff_read;

    if(Read(0x07,_buff_read,sizeof(DDCBi_GetVCPFeature_ReplyCmd_t)))
    {
        nLow=p_vcp_return->a_VCPFeature.valuelow;
        nMid=p_vcp_return->a_VCPFeature.valuehi;
        nHight=p_vcp_return->a_VCPFeature.maxlow;

        return true;

    }

    return false;
}

void CDislayOrder::setPipOnOff(bool blPipOnOff)
{
    unsigned char _buff[8]={0};
    _buff[0]=0x6e;
    _buff[1]=0x51;
    _buff[2]=0x84;
    _buff[3]=0x03;
    _buff[4]=0xA4;
    _buff[5]=blPipOnOff;
    _buff[6]=0x03;
    for(int i=0;i<7;i++)
        _buff[7] ^= _buff[i];


    Write(_buff,8,false);
}

bool CDislayOrder::getDisplayPIPMode(int *nIndex)
{
    unsigned char _buff[6]={0};
    _buff[0]=0x6e;
    _buff[1]=0x51;
    _buff[2]=0x82;
    _buff[3]=0x01;
    _buff[4]=0xA4;
    for(int i=0;i<5;i++)
        _buff[5] ^= _buff[i];

    Write(_buff,8,false);

    QThread::msleep(50);
    unsigned char _readBuf[11]={0};
    Read(0x00,_readBuf,11,false);

    QString str;
    for(int i=0;i<11;i++)
    {
        if(_readBuf[i]<0x10)
            str+=("0"+QString::number(_readBuf[i],16)+" ");
        else
            str+=(QString::number(_readBuf[i],16)+" ");
    }
    str+="\n";
    SaveTestLogInfo(str);
    if(_readBuf[9]==0x03)
    {
        *nIndex=_readBuf[7];
        return true;
    }
    else
        return false;
}

bool CDislayOrder::getDisplayReadMode()
{
    unsigned char _buff[6]={0};
    _buff[0]=0x6e;
    _buff[1]=0x51;
    _buff[2]=0x82;
    _buff[3]=0x01;
    _buff[4]=0xA4;
    for(int i=0;i<5;i++)
        _buff[5] ^= _buff[i];

    Write(_buff,8,false);

    QThread::msleep(50);
    unsigned char _readBuf[11]={0};
    Read(0x00,_readBuf,11,false);

    QString str;
    for(int i=0;i<11;i++)
    {
        if(_readBuf[i]<0x10)
            str+=("0"+QString::number(_readBuf[i],16)+" ");
        else
            str+=(QString::number(_readBuf[i],16)+" ");
    }
    str+="\n";
    SaveTestLogInfo(str);
    if((_readBuf[9]==0x01) || (_readBuf[9]==0x04))
    {
        return true;
    }
    else
        return false;
}

void CDislayOrder::setReadMode(BYTE btMode)
{
    unsigned char _buff[8]={0};
    _buff[0]=0x6e;
    _buff[1]=0x51;
    _buff[2]=0x84;
    _buff[3]=0x03;
    _buff[4]=0xA7;
    _buff[5]=0x00;
    _buff[6]=btMode;
    for(int i=0;i<7;i++)
        _buff[7] ^= _buff[i];

    Write(_buff,8,false);
}

bool CDislayOrder::getBright(int &nBright )
{

    unsigned char _buff_read[sizeof(DDCBi_GetVCPFeature_ReplyCmd_t)];
    DDCBi_GetVCPFeature_ReplyCmd_t *p_vcp_return=(DDCBi_GetVCPFeature_ReplyCmd_t*)_buff_read;

    if(Read(DDC_ORDER_BRIGHT,_buff_read,sizeof(DDCBi_GetVCPFeature_ReplyCmd_t)))
    {
        nBright=p_vcp_return->a_VCPFeature.valuehi;
        nBright=nBright*256+p_vcp_return->a_VCPFeature.valuelow;
        return true;

    }

return false;
}



void CDislayOrder::setContrast(int nContrast )
{
    unsigned char _buff[3];
    _buff[0]=0x12;
    _buff[1]=nContrast>>8;
    _buff[2]=nContrast;
    Write(_buff,sizeof(_buff),true);

}

bool CDislayOrder::getContrast(int &getContrast )
{

    unsigned char _buff_read[sizeof(DDCBi_GetVCPFeature_ReplyCmd_t)];
    DDCBi_GetVCPFeature_ReplyCmd_t *p_vcp_return=(DDCBi_GetVCPFeature_ReplyCmd_t*)_buff_read;

    if(Read(0x12,_buff_read,sizeof(DDCBi_GetVCPFeature_ReplyCmd_t)))
    {
        getContrast=p_vcp_return->a_VCPFeature.valuehi;
        getContrast=getContrast*256+p_vcp_return->a_VCPFeature.valuelow;
        return true;
    }

return false;
}

void CDislayOrder::setColor(int nIterm )
{
    unsigned char _buff[3];
   // _buff[0]=0xc0;
    _buff[0]=DDC_ORDER_SET_COLOR;
    _buff[1]=nIterm>>0;
    _buff[2]=nIterm;
    Write(_buff,sizeof(_buff),true);

}
void CDislayOrder::setGamma(int nIterm )
{
    unsigned char _buff[3];
    //_buff[0]=0xc0;
    _buff[0]=DDC_ORDER_SET_GAMMA;
    _buff[1]=nIterm>>0;
    _buff[2]=nIterm;
    Write(_buff,sizeof(_buff),true);

}
