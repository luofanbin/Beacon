// I1DisplaySensor.cpp: implementation of the CI1DisplaySensor class.
//
//////////////////////////////////////////////////////////////////////



#include "I1DisplaySensor.h"
#include <QObject>
#include <QMessageBox>
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
#include <QMessageBox>
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CI1DisplaySensor::CI1DisplaySensor():CCieSensor(),m_I1d3Handle(NULL)
{
//m_libWinIic("dll/i1d3SDK.dll")
 //   if(!m_libWinIic.load())
   // {
  //      QMessageBox::warning(NULL,"Warning","not load the dll");

  //  }
  i1d3Initialize();
}

CI1DisplaySensor::~CI1DisplaySensor()
{

}

bool CI1DisplaySensor::BeginWork()
{
	if (!m_blWorking)
	{
		i1d3Destroy();
		i1d3Initialize();
		if (i1d3GetNumberOfDevices()==0)
		{
               QMessageBox::warning(NULL,QObject::tr("Error"),QObject::tr("No i1d3 devices found!"));
				return false;

		}

		 i1d3Status_t status_err=i1d3GetDeviceHandle(0, &m_I1d3Handle);
		if(status_err != i1d3Success)
		{
          QString s=QString( QObject::tr("Error %1")).arg(status_err);
            QMessageBox::warning(NULL, QObject::tr("Warning"),s);

			return false;
		}

		if (i1d3DeviceOpen(m_I1d3Handle) != i1d3Success)
		{
			unsigned char key[] = { 0xD4,0x9F,0xD4,0xA4,0x59,0x7E,0x35,0xCF };
			i1d3OverrideDeviceDefaults(NULL,NULL,key);
			status_err=i1d3DeviceOpen(m_I1d3Handle);
		}
		
		if(status_err != i1d3Success)
		{
            QString s=QString( QObject::tr("Error opening i1d3!  Error %1")).arg(status_err);
            QMessageBox::warning(NULL, QObject::tr("Warning"),s);

			m_blWorking=false;
			return false;
		}
		else
			m_blWorking=true;
	}

	return m_blWorking;
}

bool CI1DisplaySensor::GetLvxy(StCieLvxy *pLvxy)
{

	i1d3Status_t status_err;
    if (BeginWork())
	{
		i1d3Yxy_t i1_lvxy;
		i1d3LumUnits_t lum_unit;
	//	i1d3MeasMode_t i1d3_mode=;
		status_err=i1d3Measure(m_I1d3Handle,lum_unit,i1d3MeasModeLCD,&i1_lvxy);
		if (status_err!=i1d3Success)
		{


            QString s=QString( QObject::tr("Error %1")).arg(status_err);
              QMessageBox::warning(NULL, QObject::tr("Warning"),s);
			return false;
		}
		else
		{
			pLvxy->dbLumin=i1_lvxy.Y;
			pLvxy->dbX=i1_lvxy.x;
			pLvxy->dbY=i1_lvxy.y;
            return true;
		}
		
	}
return false;
}

bool CI1DisplaySensor::EndWork()
{

	return true;
}
bool CI1DisplaySensor::getSensorInfo(StSensorInformation& cStInfor)
{
    if (BeginWork())
    {
         i1d3DEVICE_INFO device_infor;
        if(i1d3GetDeviceInfo(m_I1d3Handle,&device_infor)==i1d3Success)
        {
            cStInfor.strManifactor=device_infor.strProductName;
            cStInfor.strType=device_infor.usProductType;
        }
        else
           return false;
        char ch_sn[22]={0};
        if(i1d3GetSerialNumber (m_I1d3Handle,ch_sn)==i1d3Success)
        {
            cStInfor.strSn=ch_sn;

        }
        else
           return false;
    }
    return true;
}
