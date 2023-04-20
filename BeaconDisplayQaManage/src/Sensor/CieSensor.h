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
	//���麯�������ڵõ�CIE��׼��������ɫ�¡�
    virtual  bool GetLvxy(StCieLvxy *pLvxy)=0;
	//���豸
//	virtual bool Open()=0;
	//�ر��豸
//	virtual bool Close()=0;
	//��ʼһ������
    virtual bool BeginWork();
	//����һ������
    virtual bool EndWork()=0;
    virtual bool getSensorInfo(StSensorInformation& cStInfor);
	CCieSensor();
	virtual ~CCieSensor();
protected:
    bool m_blWorking;

};

#endif // !defined(AFX_CIESENSOR_H__950295AF_5C34_41B0_A7FC_FC47975FC82F__INCLUDED_)
