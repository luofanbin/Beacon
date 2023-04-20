// CieSensor.h: interface for the CCieSensor class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CIESENSOR_H__950295AF_5C34_41B0_A7FC_FC47975FC82F__INCLUDED_)
#define AFX_CIESENSOR_H__950295AF_5C34_41B0_A7FC_FC47975FC82F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "userdefine.h"
typedef struct _ST_SENSOR_INFORMATION_
{
     QString strManifactor;
     QString strType;
     QString strSn;

    _ST_SENSOR_INFORMATION_()
    {
         strManifactor="";
         strType=""; ;
         strSn=""; ;

    }

}StSensorInformation;

class CCieSensor
{

public:
	//纯虚函数，用于得到CIE标准的亮度与色温。
    virtual  bool GetLvxy(StCieLvxy *pLvxy)=0;
	//打开设备
//	virtual bool Open()=0;
	//关闭设备
//	virtual bool Close()=0;
	//开始一个任务
    virtual bool BeginWork();
	//结束一个任务
    virtual bool EndWork()=0;
    virtual bool getSensorInfo(StSensorInformation& cStInfor);
	CCieSensor();
	virtual ~CCieSensor();
protected:
    bool m_blWorking;

};

#endif // !defined(AFX_CIESENSOR_H__950295AF_5C34_41B0_A7FC_FC47975FC82F__INCLUDED_)
