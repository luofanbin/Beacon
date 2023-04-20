// I1DisplaySensor.h: interface for the CI1DisplaySensor class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_I1DISPLAYSENSOR_H__D6384AB8_964F_426A_AE81_6BB7F5FA19A7__INCLUDED_)
#define AFX_I1DISPLAYSENSOR_H__D6384AB8_964F_426A_AE81_6BB7F5FA19A7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <QObject>
#include "CieSensor.h"
extern "C"
{
#include "../../include/i1d3SDK.h"

}

#include <QLibrary>


class CI1DisplaySensor : public CCieSensor  
{

public:
    bool EndWork();
    bool GetLvxy(StCieLvxy *pLvxy);
    bool BeginWork();
     bool getSensorInfo(StSensorInformation& cStInfor);
	CI1DisplaySensor();

	virtual ~CI1DisplaySensor();
private:
	i1d3Handle m_I1d3Handle;
	i1d3Yxy_t  m_dYxyMeas;
protected:
// QLibrary m_libWinIic;

};

#endif // !defined(AFX_I1DISPLAYSENSOR_H__D6384AB8_964F_426A_AE81_6BB7F5FA19A7__INCLUDED_)
