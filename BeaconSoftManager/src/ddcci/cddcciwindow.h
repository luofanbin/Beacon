#ifndef CDDCCIWINDOW_H_EDID
#define CDDCCIWINDOW_H_EDID
#include "cdislayorder.h"
#include "QString"
#include "QVector"
#include <QLibrary>

typedef unsigned __LONG32 DWORD;

class CDdcciWindow : public CDislayOrder
{
public:
    CDdcciWindow();
    virtual bool InitUpdate(QVector<QString> &rvtStringDeviceName,QString &rstrCurrent);//initial the communicate way data for the write or read data
    virtual bool InitUpdate(QVector<QString> &rvtStringDeviceSN);
    virtual bool Open(const QString &rstrDeviceName);// open the device for the communication
    virtual bool Close(); //close the device handle
    virtual bool Write(unsigned char *pBuf,unsigned char nLen,bool blIsVcp=true);//write the buffer data to the device
    virtual bool Read( unsigned char ctrl,unsigned char *pBuf,unsigned char nLen ,bool blIsVcp=true);//read the buffer data to the device
    virtual int SetDisplayIndex(int dwDisplayId);
    virtual void getMonitorFromPixel(DWORD x, DWORD y, DWORD *DispIndex);
    virtual void GetMonitorBrightness(DWORD DispIndex, DWORD * MinBrightness, DWORD * CurBrightness, DWORD * MaxBrightness);
    virtual void GetMonitorContrast(DWORD DispIndex, DWORD * MinContrast, DWORD * CurContrast, DWORD * MaxContrast);
protected:
   // QLibrary m_libWinIic;

    int m_DisplayNumber=0;
    QVector<QString> m_vtDiaplayName;
void WaitMsTime(unsigned long lgWait);


};

#endif // CDDCCIWINDOW_H_EDID
