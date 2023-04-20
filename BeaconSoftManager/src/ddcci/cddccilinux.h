#ifndef CDDCCILINUX_H
#define CDDCCILINUX_H
#include "cdislayorder.h"
extern "C"
{
#include "ddcci.h"
}
class CDdcciLinux : public CDislayOrder
{
public:
    CDdcciLinux();
    virtual bool InitUpdate(QVector<QString> &rvtStringDeviceName,QString &rstrCurrent);//initial the communicate way data for the write or read data
    virtual bool Open(QString &rstrDeviceName);// open the device for the communication
    virtual bool Close(); //close the device handle
    virtual bool Write(unsigned char *pBuf,unsigned char nLen,bool blIsVcp=true);//write the buffer data to the device
    virtual bool Read( unsigned char ctrl,unsigned char *pBuf,unsigned char nLen,bool blIsVcp =true);//read the buffer data to the device
private:
    struct monitor m_stMonitor;

};

#endif // CDDCCILINUX_H
