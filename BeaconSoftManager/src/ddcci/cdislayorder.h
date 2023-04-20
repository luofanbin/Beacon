#ifndef CDISLAYORDER_H
#define CDISLAYORDER_H

#include "DdcVcpForGe.h"
#include "QString"
#include "QVector"

#define DDCCI_COMMAND_READ	0x01	/* read ctrl value */
#define DDCCI_REPLY_READ	0x02	/* read ctrl value reply */
#define DDCCI_COMMAND_WRITE	0x03	/* write ctrl value */
#define DDCCI_STATUS_OK            0x00    /*communicate ok */


#define CMD_SET_KEY        0x96   /* for the menu control key*/
class CDislayOrder
{
public:
    CDislayOrder();
    virtual bool InitUpdate(QVector<QString> &rvtStringDeviceName,QString &rstrCurrent)=0;//initial the communicate way data for the write or read data
    virtual bool Open(const QString &rstrDeviceName)=0;// open the device for the communication
    virtual bool Close()=0; //close the device handle
    void SentKeyControl(unsigned char chKey,bool isDoubleClick);
    void setBright(int nBright );
    void setThreePointBright(int type,int nBright );
    void setContrast(int nContrast );
    bool getBright(int &nBright );
    void turnOnOffDisplay(bool blIsOn );
    bool getContrast(int &getContrast );
    void setGamma(int nIterm );
    void setColor(int nIterm);
    bool getThreeBright(int &nLow,int &nMid,int &nHight );
    void setPipOnOff(bool blPipOnOff);
    bool getDisplayPIPMode(int *nIndex);
    bool getDisplayReadMode();
    void setReadMode(BYTE btMode);

protected:

    bool m_blIsOpen;

    virtual bool Write(unsigned char *pBuf,unsigned char nLen,bool blIsVcp=true)=0;//write the buffer data to the device
    virtual bool Read( unsigned char ctrl,unsigned char *pBuf,unsigned char nLen ,bool blIsVcp=true)=0;//read the buffer data to the device


};

#endif // CDISLAYORDER_H
