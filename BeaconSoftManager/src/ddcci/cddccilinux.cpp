#include "cddccilinux.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
CDdcciLinux::CDdcciLinux()
{

}
 bool CDdcciLinux::InitUpdate(QVector<QString> &rvtStringDeviceName,QString &rstrCurrent)//initial the communicate way data for the write or read data
 {
     rvtStringDeviceName.clear();


     /*
         QMessageBox msgBox;
         msgBox.setText("The document has been modified.");
         msgBox.exec();
         */
         /* filedescriptor and name of device */
          char* fn = NULL;
         char *datadir = NULL;
             int verbosity = 0;

             ddcci_verbosity(verbosity);
           //  if (!ddcci_init(datadir)) {
                 printf(_("Unable to initialize ddcci library.\n"));
           //      return false;
         //    }


             struct monitorlist* monlist;
             struct monitorlist* current;

             monlist = ddcci_probe();

             printf(_("Detected monitors :\n"));

             current = monlist;
             //close the i2c device handle
           //  m_stMonitor.
             if(m_blIsOpen)
                 ddcci_close(&m_stMonitor);
             //save the current i2c dir
             QString str_i2c_dir=rstrCurrent;
             rstrCurrent="";
             //clear all the item of the comboboxDevice

            // ui->comboBoxDevice->addItem("dev:2");
            //  ui->comboBoxDevice->addItem("dev:3");
             while (current != NULL)
             {
                 printf(_(" - Device: %s\n"), current->filename);
                 printf(_("   DDC/CI supported: %s\n"), current->supported ? _("Yes") : _("No"));
                 printf(_("   Monitor Name: %s\n"), current->name);
                 printf(_("   Input type: %s\n"), current->digital ? _("Digital") : _("Analog"));

                 if(current->supported)
                 {
                     ;
                     rvtStringDeviceName.push_back(QString (current->filename));

                     if(str_i2c_dir.compare(current->filename)==0 ||rstrCurrent=="")
                     {
                        rstrCurrent=QString(current->filename);

                     }
                 }

                 if ((!fn) && (current->supported))
                 {
                     printf(_("  (Automatically selected)\n"));
                     fn =(char*) malloc(strlen(current->filename)+1);
                     strcpy(fn, current->filename);
                 }

                 current = current->next;
             }

        if (rstrCurrent!= "") {
                 QByteArray ba = rstrCurrent.toLatin1();
                 m_blIsOpen=(ddcci_open(&m_stMonitor,ba.data(),0)==0);
             }

             ddcci_free_list(monlist);
 }

 bool CDdcciLinux::Open(QString &rstrDeviceName)// open the device for the communication
 {
     if(m_blIsOpen)
     {
         ddcci_close(&m_stMonitor);
     m_blIsOpen=false;
     }
     if (rstrDeviceName!= "") {
              QByteArray ba = rstrDeviceName.toLatin1();
              m_blIsOpen=(ddcci_open(&m_stMonitor,ba.data(),0)==0);
          }
    return m_blIsOpen;
 }

 bool CDdcciLinux::Close() //close the device handle
 {
  return ddcci_close(&m_stMonitor)==0 ? true:false;
 }

 bool CDdcciLinux::Write(unsigned char *pBuf,unsigned char nLen,bool blIsVcp)//write the buffer data to the device
 {
     int n_result;
     if(blIsVcp)
       n_result=ddcci_write(&m_stMonitor,pBuf,nLen);
      else
       n_result=ddcci_raw_writectrl(&m_stMonitor,pBuf,nLen);

     return n_result>=0 ? true:false;
 }

 bool CDdcciLinux:: Read( unsigned char ctrl,unsigned char *pBuf,unsigned char nLen,bool blIsVcp )//read the buffer data to the device
 {
     int n_result=0;

     if (blIsVcp)
       n_result=ddcci_read(&m_stMonitor,pBuf,nLen);
      else
        n_result=ddcci_raw_readctrl(&m_stMonitor,ctrl,pBuf,nLen);
   return n_result >=0 ? true:false;
 }
