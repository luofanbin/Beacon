//*************************************************************************
//                             WinI2C/DDC
//                  Copyright (c) 2006-2012 Nicomsoft Ltd.
//                 Copyright (c) 2006-2012 Michael Kapustin
//                        support@nicomsoft.com
//                          www.nicomsoft.com
//
// You may not distribute any of the headers or source files of WinI2C/DDC, 
//                  see License Agreement for details
//
//*************************************************************************

//----------------------------
// DDCHELPER Header file
//----------------------------

#ifndef _DDCHELPER_H_
#define _DDCHELPER_H_
#include<windef.h>
#ifndef    _DDCAPI_
#define    DDCAPI  extern "C" __declspec(dllimport) DWORD __stdcall
#endif


#define PEDISP  DWORD


//I2C Commands 
#define I2C_READ            0x0001 // Read bufer Monolite (if Length<=128 byte)
#define I2C_WRITE           0x0002 // Write bufer Monolite (if Length<=128 byte)
#define I2C_RESET           0x0008

//Flags for WriteI2CBuf
#define NO_STOP_BIT         0x0100 //No stop bit
#define NO_ADDR_PART        0x1000 //No address part


//--------------------------------------

#define GAINTYPE_RED				0x00
#define GAINTYPE_GREEN				0x01
#define GAINTYPE_BLUE				0x02

#define POSTYPE_X					0x00
#define POSTYPE_Y					0x01

#define SIZETYPE_WIDTH				0x00
#define SIZETYPE_HEIGHT				0x01

#define TECHNOLOGY_MASKCRT			0x01
#define TECHNOLOGY_GRILLCRT			0x02
#define TECHNOLOGY_TFT				0x03
#define TECHNOLOGY_LCOS				0x04
#define TECHNOLOGY_PLASMA			0x05
#define TECHNOLOGY_OLED				0x06
#define TECHNOLOGY_EL				0x07
#define TECHNOLOGY_MEM				0x08
#define TECHNOLOGY_FED				0x09

#define POWER_ON                    0x01 
#define POWER_STANDBY               0x02
#define POWER_SUSPEND               0x03
#define POWER_OFF                   0x04

//option codes for Get/SetLibraryOption functions
#define OPT_COMMLOGIC				0x00
#define OPT_I2CFREQ					0x01
#define OPT_I2CTIMEOUT				0x02
#define OPT_RAWBUS                  0x03
#define OPT_PREFER_VISTAAPI         0x04
#define OPT_BYTE_DELAY              0x05
#define OPT_I2CVIAIRP				0x06
#define OPT_ALLOWSAMEEDID			0x07
#define OPT_NOWINAPI				0x08

//modes for OPT_COMMLOGIC option:
//try native communication and if nothing found then try video driver
#define COMMLOGIC_MODE1				0x01
//try video driver and if nothing found then try native communication
#define COMMLOGIC_MODE2				0x02
//try native communication and then try video driver
#define COMMLOGIC_MODE3				0x03
//try video driver and then try native communication
#define COMMLOGIC_MODE4				0x04
//try video driver only
#define COMMLOGIC_MODE5				0x05
//try native communication only
#define COMMLOGIC_MODE6				0x06			0x04


//options for GetEDIDOption function 
#define EDID_PNPID                  0x01
#define EDID_MANUFACTURER           0x02
#define EDID_OPTIMALRESX            0x03
#define EDID_OPTIMALRESY            0x04
#define EDID_SERIALNUMBER           0x05
#define EDID_MONITORNAME            0x06  
#define EDID_MINHFREQ               0x07
#define EDID_MAXHFREQ               0x08 
#define EDID_MINVFREQ               0x09
#define EDID_MAXVFREQ               0x0A
#define EDID_GAMMA                  0x0B
#define EDID_MANUFACTUREDATE        0x0C
#define EDID_INPUTTYPE              0x0D
#define EDID_HSIZE                  0x0E
#define EDID_VSIZE                  0x0F
#define EDID_ASPECTRATIO            0x10
#define EDID_POWERMAN               0x11
#define EDID_VERSION                0x12
#define EDID_DISPLAYTYPE            0x13 

//constants for GetI2CMode function
#define I2CMODE_PCI           0x0001
#define I2CMODE_IRP	          0x0002
#define I2CMODE_NVIDIASDK     0x0003
#define I2CMODE_ATISDK        0x0004
#define I2CMODE_INTELSDK      0x0005
#define I2CMODE_MATROXSDK     0x0006
#define I2CMODE_DDCAPI        0x0100
#define I2CMODE_UNKNOWN       0x1000

// Warnings -----------------------------------------------

#define WARN_FIRST								0x60000000

#define WARN_DRIVERNOTAVAILABLE					0x60000001

// Error codes --------------------------------------------

#define ERROR_FIRST					            0x70000000

#define ERROR_CANNOTINSTALLDRIVER	            0x70000001
#define ERROR_CANNOTUNNSTALLDRIVER 	            0x70000002
#define ERROR_CANNOTSTARTDRIVER		            0x70000003
#define ERROR_CANNOTSTOPDRIVER		            0x70000004
#define ERROR_DRIVERNOTINSTALLED	            0x70000005
#define ERROR_CANNOTOPENDRIVER		            0x70000006
#define ERROR_DRIVERNOTOPENED		            0x70000007

#define ERROR_INVALIDPARAMETER		            0x70000010
#define ERROR_I2CREAD				            0x70000011
#define ERROR_I2CWRITE				            0x70000012
#define ERROR_INVALIDEDID			            0x70000013
#define ERROR_INVALIDI2CADDRESS		            0x70000014
#define ERROR_READCAPABILITES		            0x70000015
#define ERROR_NOMOREDEVICES			            0x70000016
#define ERROR_ENUMNOTSTARTED		            0x70000017
#define ERROR_INVALIDDEVICE			            0x70000018
#define ERROR_SMALLBUFFER			            0x70000019
#define ERROR_COMMANDCODE			            0x7000001A
#define ERROR_UNKNOWN			                0x7000001B
#define ERROR_NOT_PCI_MODE			            0x7000001C
#define ERROR_UNKNOWNOPTION			            0x7000001D
#define ERROR_DATANOTFOUND			            0x7000001E
#define ERROR_UNSUPORTEDINSDVO		            0x7000001F
#define ERROR_CANNOTFINDMONITOR		            0x70000020
#define ERROR_NOTSUPPORTEDBYVISTAAPI            0x70000021


#define ERROR_NOTIMPLEMENTED		            0x70000080
#define ERROR_DEMOVERSION_NOTSUPPORTED			0x700000F0
#define ERROR_DEMOVERSION_EXPIRED				0x700000F1

#ifndef UCHAR
#define UCHAR unsigned char
#define LPUCHAR UCHAR *
#endif

// Functions -------------------------------------------------

DDCAPI InstallDriver(char *path, int autostart);
DDCAPI UninstallDriver();

DDCAPI InitDDCHelper();
DDCAPI DeinitDDCHelper();
DDCAPI GetLibraryVersion();

DDCAPI EnableLog(char *path, DWORD removeold);
DDCAPI DisableLog();
DDCAPI WriteLog(char *str);

DDCAPI EnumGetFirst(DWORD *DispIndex);
DDCAPI EnumGetNext(DWORD *DispIndex);
DDCAPI GetCachedEDID256(DWORD DispIndex, UCHAR *pEDID);
DDCAPI ReadEDID(DWORD DispIndex, PUCHAR pEDID);
DDCAPI ReadEDID256(DWORD DispIndex, UCHAR *pEDID);
DDCAPI GetEDIDOption(UCHAR *EDID, DWORD OptionIndex, char *Value, DWORD MaxCount);

DDCAPI SetLibraryOption(DWORD OptionIndex, DWORD Value);
DDCAPI GetLibraryOption(DWORD OptionIndex);

#ifndef _LITE

DDCAPI TestAddr(DWORD DispIndex, UCHAR addr);
DDCAPI ReadI2CBuf(DWORD DispIndex, UCHAR Addr, PUCHAR Buf, UCHAR Length, DWORD Flags);
DDCAPI WriteI2CBuf(DWORD DispIndex, UCHAR Addr, PUCHAR Buf, UCHAR Length, DWORD Flags);
DDCAPI DDCCIRead(DWORD DispIndex, UCHAR *Buffer, UCHAR *len);
DDCAPI DDCCIWrite(DWORD DispIndex, UCHAR *Buffer, UCHAR len);
DDCAPI GetCIValue(DWORD DispIndex, UCHAR Command, LPDWORD Value, LPDWORD MaxValue);
DDCAPI SetCIValue(DWORD DispIndex, UCHAR Command, DWORD Value);
DDCAPI SetSCL(DWORD DispIndex, DWORD State);
DDCAPI SetSDA(DWORD DispIndex, DWORD State);
DDCAPI GetSDA(DWORD DispIndex);
DDCAPI GetSCL(DWORD DispIndex);
DDCAPI IsNativeMode(DWORD DispIndex);
DDCAPI GetI2CMode(DWORD DispIndex);
DDCAPI GetVideoVendor(DWORD DispIndex);

#endif

DDCAPI DegaussMonitor(DWORD DispIndex);
DDCAPI GetMonitorCapabilitesStr(DWORD DispIndex, char *buffer, DWORD MaxLen);
DDCAPI GetMonitorCapabilitesStrLen(DWORD DispIndex);
DDCAPI GetMonitorBrightness(DWORD DispIndex, LPDWORD MinBrightness, LPDWORD CurBrightness, LPDWORD MaxBrightness);
DDCAPI GetMonitorContrast(DWORD DispIndex, LPDWORD MinContrast, LPDWORD CurContrast, LPDWORD MaxContrast);
DDCAPI GetMonitorDisplayAreaPosition(DWORD DispIndex, DWORD PosType, LPDWORD MinPosition, LPDWORD CurPosition, LPDWORD MaxPosition);
DDCAPI GetMonitorDisplayAreaSize(DWORD DispIndex, DWORD SizeType, LPDWORD MinSize, LPDWORD CurSize, LPDWORD MaxSize);
DDCAPI GetMonitorGain(DWORD DispIndex, DWORD GainType, LPDWORD MinGain, LPDWORD CurGain, LPDWORD MaxGain);
DDCAPI GetMonitorTechnologyType(DWORD DispIndex);
DDCAPI GetMonitorPowerMode(DWORD DispIndex, LPDWORD Mode);
DDCAPI RestoreMonitorFactoryDefaults(DWORD DispIndex);
DDCAPI RestoreMonitorFactoryColorDefaults(DWORD DispIndex);
DDCAPI SaveCurrentMonitorSettings(DWORD DispIndex);
DDCAPI SetMonitorBrightness(DWORD DispIndex, DWORD NewBrightness);
DDCAPI SetMonitorContrast(DWORD DispIndex, DWORD NewContrast);
DDCAPI SetMonitorDisplayAreaPosition(DWORD DispIndex, DWORD PosType, DWORD NewPosition);
DDCAPI SetMonitorDisplayAreaSize(DWORD DispIndex, DWORD SizeType, DWORD NewSize);
DDCAPI SetMonitorGain(DWORD DispIndex, DWORD GainType, DWORD NewGain);
DDCAPI SetMonitorPowerMode(DWORD DispIndex, DWORD Mode);
DDCAPI TestDDCSupport(DWORD DispIndex);

DDCAPI GetMonitorFromHMONITOR(HMONITOR Handle, DWORD *DispIndex);
DDCAPI GetMonitorFromPixel(DWORD x, DWORD y, DWORD *DispIndex);



#endif //_DDCHELPER_H_
