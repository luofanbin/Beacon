#include "cddcciwindow.h"
#include <QMessageBox>
#include <QDebug>
 #include <QCoreApplication>
//#include "DDCHelper.h"
#include <qthread.h>
#include <QMutex>
#include <QWaitCondition>
#include "userdefine.h"
#define S_OK  0
typedef unsigned long       DWORD;
typedef int                 BOOL;
//typedef unsigned char UCHAR;
//typedef UCHAR*  PUCHAR;
typedef DWORD*  LPDWORD;


extern "C"    //由于是C版的dll文件，在C++中引入其头文件要加extern "C" {},注意
{
#include "DDCHelper.h"
}


/*
typedef DWORD (*Pf_InitDDCHelper)();
typedef DWORD (*pf_InstallDriver)(char *, int );
typedef DWORD (*pf_EnumGetFirst)(DWORD*);
typedef DWORD (*pf_EnumGetNext)(DWORD*);
typedef DWORD (*pf_GetCachedEDID256)(DWORD , UCHAR*);
typedef DWORD (*pf_GetEDIDOption)(UCHAR*, DWORD , char *, int );
typedef DWORD (*pf_DDCCIRead)(DWORD , UCHAR *, UCHAR *);
typedef DWORD (*pf_DDCCIWrite)(DWORD , UCHAR *, UCHAR );
typedef DWORD  (*pf_SetVcpValue)(DWORD , UCHAR , DWORD );
typedef DWORD  (*pf_GetVcpValue)(DWORD , UCHAR , LPDWORD , LPDWORD );
typedef DWORD (*pf_SetLibraryOption)(DWORD OptionIndex, DWORD Value) ;
*/

DWORD MyDisplay[100];
int    MyDisplayCount=0;
void CDdcciWindow::WaitMsTime(unsigned long lgWait)
{
    QMutex mutex;
    QWaitCondition sleep;
    mutex.lock();
    sleep.wait(&mutex, lgWait);
    mutex.unlock();


}
CDdcciWindow::CDdcciWindow():m_DisplayNumber(0)
{


    QMessageBox msgBox;


#if 0
if(!m_libWinIic.load())
{
    msgBox.setText("not load the dll");
    msgBox.exec();
}
#endif

   // Pf_InitDDCHelper pf_initddchelper=(Pf_InitDDCHelper)m_libWinIic.resolve("InitDDCHelper");
   // pf_InstallDriver pf_installdriver=(pf_InstallDriver)m_libWinIic.resolve("InstallDriver");
   // m_libWinIic;
    int n_count=0;
        int res=9;


        do
        {
            res=InitDDCHelper();



            if (res != S_OK)
            {
                //	AfxMessageBox("初使化InstallDriver");
                QString      filepath;
                QString     str_file;

               QString file=QCoreApplication::applicationDirPath();//获取当前应用程序路径
               filepath=QString("%1/ddcdrv.sys").arg(file);

//filepath.toLatin1().data(
                res= InstallDriver(filepath.toLatin1().data(), 0) ;
                if (res > WARN_FIRST)
                {
                    QMessageBox msgBox;
                     msgBox.setText("Warning: Cannot open driver, probably driver is not installed or busy by another application.");

                    if (res == WARN_DRIVERNOTAVAILABLE)
                        msgBox.exec();
                }

            }
            n_count++;


            if (res == S_OK)
                res = InitDDCHelper();

        } while (res!=S_OK &&n_count<3);

   // SetLibraryOption(OPT_I2CFREQ,100*1000);

    char buffer_max[255]={0};
   //  GetMonitorCapabilitesStr(0, char *buffer, DWORD MaxLen);
    DWORD MaxLen= GetMonitorCapabilitesStrLen(0);

    GetMonitorCapabilitesStr(0, buffer_max,  MaxLen);




}


#define OPT_NOWINAPI 0x08
bool CDdcciWindow::InitUpdate(QVector<QString> &rvtStringDeviceName,QString &rstrCurrent)//initial the communicate way data for the write or read data
{

    int n_count=sizeof(UCHAR);
    n_count=sizeof(DWORD);
 int n_result;
    QMessageBox message_infor;
    QMessageBox msgBox;
    rvtStringDeviceName.clear();
m_vtDiaplayName.clear();;
char TmpStr[128*4]={0};
BYTE EDID[256*2]={0};
char desc[256*2]={0};
 QString str_i2c_dir;
         QString str_item;
    MyDisplayCount = 0;
    m_DisplayNumber=0;

//SetLibraryOption(0x00,4);
 //pf_setLibraryOption(OPT_NOWINAPI,0);
      str_i2c_dir=rstrCurrent;
     rstrCurrent="";
DWORD dw_return_status;

MyDisplayCount=0;
   if (EnumGetFirst(&(MyDisplay[MyDisplayCount])) == S_OK)
     {

        do
       {


          ReadEDID(MyDisplay[MyDisplayCount], EDID);
//dw_return_status=pf_enumnext(&MyDisplay[MyDisplayCount]);
 // pf_getedid256(MyDisplay[MyDisplayCount], EDID);


        //  msgBox.setText(QString("count %1").arg(MyDisplayCount,0,10));
      //    msgBox.exec();
     GetEDIDOption(EDID, EDID_PNPID, desc, 128);
     char desc_manufacture[256*2]={0};
     GetEDIDOption(EDID, EDID_MANUFACTURER, desc_manufacture, 128);
        //  desc[0]=MyDisplayCount;

 #if 1

      //  msgBox.setText(QString("count %1").arg(MyDisplayCount,0,10));
       // msgBox.exec();

      strcpy(TmpStr, desc);
     str_item=TmpStr;
               "ddsds";//QString("%1:%2").arg(MyDisplayCount).arg(desc);
           rvtStringDeviceName.push_back(str_item);
#if 1

           if(str_i2c_dir.compare(str_item)==0 ||str_i2c_dir=="")
            {

               rstrCurrent=str_item;

               m_DisplayNumber=MyDisplayCount;

            }


#endif

#endif
          MyDisplayCount++;
          dw_return_status=EnumGetNext(&(MyDisplay[MyDisplayCount]));
            }while (dw_return_status == S_OK);
            n_result=n_result;
    }


    if (rstrCurrent!= "") {
          //   QByteArray ba = rstrCurrent.toLatin1();

            // m_blIsOpen=true;
         }



    m_vtDiaplayName=rvtStringDeviceName;
    return true;
}

bool CDdcciWindow::InitUpdate(QVector<QString> &rvtStringDeviceSN)
{
    int n_count=sizeof(UCHAR);
    n_count=sizeof(DWORD);

    QMessageBox message_infor;
    QMessageBox msgBox;
    rvtStringDeviceSN.clear();
    m_vtDiaplayName.clear();;
    char TmpStr[128*4]={0};
    BYTE EDID[256*2]={0};
    char desc[256*2]={0};
    QString str_i2c_dir;
    QString str_item;
    MyDisplayCount = 0;
    m_DisplayNumber=0;

    //SetLibraryOption(0x00,4);

    DWORD dw_return_status;

    MyDisplayCount=0;
    if (EnumGetFirst(&(MyDisplay[MyDisplayCount])) == S_OK)
    {

        do
        {


            ReadEDID(MyDisplay[MyDisplayCount], EDID);
            GetEDIDOption(EDID, EDID_MONITORNAME, desc, 128);
            char desc_manufacture[256*2]={0};
            GetEDIDOption(EDID, EDID_SERIALNUMBER, desc_manufacture, 128);

#if 1


            strcpy(TmpStr, desc);
            str_item=TmpStr;
            rvtStringDeviceSN.push_back(str_item);

            strcpy(TmpStr, desc_manufacture);
            str_item=TmpStr;
            rvtStringDeviceSN.push_back(str_item);


#if 1



#endif

#endif
            MyDisplayCount++;
            dw_return_status=EnumGetNext(&(MyDisplay[MyDisplayCount]));
        }while (dw_return_status == S_OK);

    }
    return true;
}

bool CDdcciWindow::Open(const QString &rstrDeviceName)// open the device for the communication
{

    m_blIsOpen=false;

    for (int i=0;i<m_vtDiaplayName.size();i++)
   {
        if(m_vtDiaplayName[i].compare(rstrDeviceName)==0 )
        {
            m_DisplayNumber=i;
            m_blIsOpen=true;
            break;

        }
    }
return m_blIsOpen;
}

bool CDdcciWindow::Close() //close the device handle
{

  //  Pf_InitDDCHelper pf_unintialHelper=(Pf_InitDDCHelper)m_libWinIic.resolve("DeinitDDCHelper");
  //  Pf_InitDDCHelper pf_uninstalldrive=(Pf_InitDDCHelper)m_libWinIic.resolve("UninstallDriver");

      DeinitDDCHelper();
       UninstallDriver();
 //return ddcci_close(&m_stMonitor)==0 ? true:false;
       return true;
}

bool CDdcciWindow::Write(unsigned char *pBuf,unsigned char nLen,bool blIsVcp)//write the buffer data to the device
{
    int n_result;
    int n_reboot;
    unsigned char ch_write[255]={0};
    //memset(ch_write,0,255);
    ch_write[0]=DDCCI_COMMAND_WRITE;
    memcpy(&ch_write[1],pBuf,nLen);
    DWORD wd_write=ch_write[2];
    wd_write=(wd_write<<8)|ch_write[3];

     // wd_write=0x9603;
    //pf_SetVcpValue pf_ddc_set_vcp=(pf_SetVcpValue)m_libWinIic.resolve("SetCIValue");
   //   pf_DDCCIWrite pf_ddcwrite=(pf_DDCCIWrite)m_libWinIic.resolve("DDCCIWrite");
    if(blIsVcp)
    {
      n_result=SetCIValue(MyDisplay[m_DisplayNumber], ch_write[1],wd_write);


    }
    else
    {
        UCHAR uAddr=(ch_write[1]>>1);
        n_result=WriteI2CBuf(MyDisplay[m_DisplayNumber],uAddr,&ch_write[2],nLen-1,NO_STOP_BIT);
        //n_result=DDCCIWrite(MyDisplay[m_DisplayNumber],&ch_write[4],nLen-3);
        //qDebug()<<n_result;
    }
    n_reboot=n_result;
    return n_reboot==DDCCI_STATUS_OK ? true:false;
}

bool CDdcciWindow::Read( unsigned char ctrl,unsigned char *pBuf,unsigned char nLen ,bool blIsVcp)//read the buffer data to the device
{
  //  pf_GetVcpValue pf_ddc_getVcpValue=(pf_GetVcpValue)m_libWinIic.resolve("GetCIValue");
   // pf_DDCCIWrite pf_ddcwrite=(pf_DDCCIWrite)m_libWinIic.resolve("DDCCIWrite");
    //pf_DDCCIRead pf_ddcread=(pf_DDCCIRead)m_libWinIic.resolve("DDCCIRead");
    int n_result=0;
    unsigned char _buf[3];
    unsigned char _buf_read[255]={0};
    //memset(_buf_read,0,255);
    unsigned char _len_read=128;
    _buf[0]=0xc2;
    _buf[1]=0x1c;
    _buf[1]=0x63;
    DWORD dw_value;
    DWORD dw_max;

    if(blIsVcp)
    {
        n_result=GetCIValue(MyDisplay[m_DisplayNumber],ctrl,&dw_max,&dw_value);
        pBuf[4]=dw_value>>8;
        pBuf[5]=dw_value;
        pBuf[6]=dw_max>>8;
        pBuf[7]=dw_max;

        return n_result == DDCCI_STATUS_OK ? true:false;

    }


//    if(n_result==DDCCI_STATUS_OK)
//    {
//        if(blIsVcp)
//         n_result= DDCCIWrite(MyDisplay[m_DisplayNumber],_buf,sizeof(_buf));
//        else
//         n_result= DDCCIWrite(MyDisplay[m_DisplayNumber],_buf,3);
//   }

    if(n_result==DDCCI_STATUS_OK)
    {
        WaitMsTime(40);
        UCHAR uAddr=(0x6e>>1);
        n_result=ReadI2CBuf(MyDisplay[m_DisplayNumber],uAddr,(UCHAR*)_buf_read,_len_read,NO_STOP_BIT);
        //qDebug()<<" ";
        memcpy(pBuf,_buf_read,nLen);
    }


    return n_result == DDCCI_STATUS_OK ? true:false;
}

int CDdcciWindow::SetDisplayIndex(int dwDisplayId)
{
    m_DisplayNumber=dwDisplayId;
    return m_DisplayNumber;
}

void CDdcciWindow::getMonitorFromPixel(DWORD x, DWORD y, DWORD *DispIndex)
{
    GetMonitorFromPixel(x,y,DispIndex);
}

void CDdcciWindow::GetMonitorBrightness(DWORD DispIndex, DWORD *MinBrightness, DWORD *CurBrightness, DWORD *MaxBrightness)
{
    GetMonitorBrightness(DispIndex,MinBrightness,CurBrightness,MaxBrightness);
}

void CDdcciWindow::GetMonitorContrast(DWORD DispIndex, DWORD *MinContrast, DWORD *CurContrast, DWORD *MaxContrast)
{
    GetMonitorContrast(DispIndex,MinContrast,CurContrast,MaxContrast);
}
