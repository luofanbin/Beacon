#include "applywindowsicm.h"
#include<QDebug>
#define WINVER 0x0500        //为 Windows98 和 Windows 2000 及更新版本改变为适当的值。
// Insert your headers here
#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers

#include <windows.h>
#include<wingdi.h>
applyWindowsIcm::applyWindowsIcm()
{
}
bool applyWindowsIcm::applyLutTable(vtTableGamma &vtTable)
{
    WORD dw_lut_table[256*3];
    for (int i=0;i<256;i++)
    {
        dw_lut_table[i]=vtTable[i].lgGammaR;
        dw_lut_table[i+1*256]=vtTable[i].lgGammaG;
        dw_lut_table[2*256+i]=vtTable[i].lgGammaB;
      //  qDebug()<<"step:"<<i<<" RGB("<<vtTable[i].lgGammaR<<vtTable[i].lgGammaG<<vtTable[i].lgGammaB<<")";
    }

    HDC hdc_temp = ::GetDC(NULL);
    BOOL bl_status=	::SetDeviceGammaRamp(hdc_temp,dw_lut_table);

}

