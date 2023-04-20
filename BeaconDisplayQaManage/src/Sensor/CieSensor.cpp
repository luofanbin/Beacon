// CieSensor.cpp: implementation of the CCieSensor class.
//
//////////////////////////////////////////////////////////////////////


#include "CieSensor.h"
#include <QObject>
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCieSensor::CCieSensor(): m_blWorking(false)
{

}

CCieSensor::~CCieSensor()
{
	//自动关闭设备

}

bool CCieSensor::BeginWork()
{
	m_blWorking=true;
	return true;
}
bool CCieSensor::getSensorInfo(StSensorInformation& cStInfor)
{
    StSensorInformation st_curret;
    cStInfor=st_curret;
    return true;

}
