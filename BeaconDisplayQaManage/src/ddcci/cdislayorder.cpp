#include "cdislayorder.h"
#include "DdcVcpForGe.h"
#include <string.h>
#include"DdcProtocDefine.h"
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
    _buff[0]=0x03 ;
    _buff[1]=chKey>>8;
    _buff[2]=chKey;
    Write(_buff,sizeof(_buff),true);

}

void CDislayOrder::setBright(int nBright )
{
    unsigned char _buff[3];
    _buff[0]=0x10;
    _buff[1]=nBright>>8;
    _buff[2]=nBright;
    Write(_buff,sizeof(_buff),true);

}
void CDislayOrder::setThreePointBright(int type,int nBright )
{
    unsigned char _buff[3];
    _buff[0]=0x07;
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
    _buff[0]=0xD6;
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

void CDislayOrder::setPipOnOff(bool blIsOn)
{
    int n_value=0x00;
    if (blIsOn)
        n_value=0x04;
    unsigned char _buff[3];
    _buff[0]=0xA4;
    _buff[1]=n_value>>8;
    _buff[2]=n_value;
    Write(_buff,sizeof(_buff),true);
}
bool CDislayOrder::getBright(int &nBright )
{

    unsigned char _buff_read[sizeof(DDCBi_GetVCPFeature_ReplyCmd_t)];
    DDCBi_GetVCPFeature_ReplyCmd_t *p_vcp_return=(DDCBi_GetVCPFeature_ReplyCmd_t*)_buff_read;

    if(Read(0x10,_buff_read,sizeof(DDCBi_GetVCPFeature_ReplyCmd_t)))
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
    _buff[0]=0x92;
    _buff[1]=nIterm>>0;
    _buff[2]=nIterm;
    Write(_buff,sizeof(_buff),true);

}
void CDislayOrder::setGamma(int nIterm )
{
    unsigned char _buff[3];
    //_buff[0]=0xc0;
    _buff[0]=0x91;
    _buff[1]=nIterm>>0;
    _buff[2]=nIterm;
    Write(_buff,sizeof(_buff),true);
}
