
//	DDC2B_CMD_GetTemperature=0x0D,			//Read monitor temperature
#ifndef DDC_CI_VCP_FOR_GE
#define DDC_CI_VCP_FOR_GE
typedef unsigned char       BYTE;
typedef struct
{
	BYTE btID;	
}stVcpHeadCommand;

enum
{
    VCP_CMD_OK=0,//define the communicate ok
    VCP_CMD_ERROR=-1,//define the some error
    VCP_CMD_ERROR_READ=-2,//define the i2c read error
    VCP_CMD_ERROR_WRITE=-3,//defind the i2c write error

};

//define the command VCP for the DDC-CI
enum
{
	DDC2B_CMD_GetTemperature=0x0D,			//Read monitor temperature
	DDC2B_CMD_GetBackSensorValue=0x04,		//Read backlight sensor value
    DDC2B_CMD_LuminanceTarget=0x05,		//Read/write luminance target
    DDC2B_CMD_LuminanceTargetRange=0x0E,		//Read/write luminance target range
	DDC2B_CMD_GetActiveVideoSource=0x44,	//Read current active video source
	DDC2B_CMD_GetAvailableVideoSource=0x5E,	//Read available Video source
    DDC2B_CMD_SerialNumber=0x52,			//Read serial number
	DDC2B_CMD_GetMonitorName=0x53,  		//Read monitor name(part number)
	DDC2B_CMD_GetMonitorRevisionNumber=0x18,//Read monitor revision number
	DDC2B_CMD_GetMonitorModelNumber=0x3A,	//Read monitor model number
	DDC2B_CMD_GetFirmwareVersion=0x02,  	//Read firmware version
	DDC2B_CMD_GetPanelStatus=0x01,    		//Read panel status
	DDC2B_CMD_GetRemainingLifeTime=0xED,	//Read remaining lifetime
	DDC2B_CMD_GetBacklightRunTime=0x09, 	//Read backlight run time
    DDC2B_CMD_SetWindowAble=0x45,     		//PIP window enable/Disable
    DDC2B_CMD_SetBright=0x10,               //set the display bright
    DDC2B_CMD_SetContrast=0x12              //set the display contrast
};


//	DDC2B_CMD_GetTemperature=0x0D,			//Read monitor temperature
typedef struct
{

    BYTE btTemperatureL;  //-55¡æ~+125¡æ	Data conversion is required.
    BYTE btTemperatureH;  //-55¡æ~+125¡æ	Data conversion is required.

}stVcpTemperature;


//DDC2B_CMD_GetBackSensorValue=0x04,		//Read backlight sensor value
typedef struct
{

    BYTE btSensorL;  //the high of the backlight sensor value
     BYTE btSensorH;  //the low of the backlight sensor value
	
}stVcpBackSensorValue;

//DDC2B_CMD_GetLuminanceTarget=0x05,		//Read/write luminance target
//DDC2B_CMD_SetLuminanceTarget=0x0E,		//Read/write luminance target range
typedef struct
{
	BYTE btLuminance;  //0~100	
	
}stVcpLuminanceTarget;


//DDC2B_CMD_GetActiveVideoSource=0x44,	//Read current active video source
//DDC2B_CMD_GetAvailableVideoSource=0x5E,	//Read available Video source
typedef struct
{
 	BYTE btVideoSource;  /*for DDC2B_CMD_GetActiveVideoSource
						 Bit7:DP1.1a
						 Bit6:DVI-D
						 Bit5->0Reserved,must be ignored
						 For DDC2B_CMD_GetAvailableVideoSource
                         Bit0:DP1.1a
						 Bit1:DVI-D
						 Bits2->7:Reserved,must be ignored
						*/
	
}stVcpVideoSource;


//DDC2B_CMD_SetSerialNumber=0x52,			//Read serial number
typedef struct
{
	BYTE btSerial[14];  //assicc
	
}stVcpSerialNumber;


//	DDC2B_CMD_GetMonitorName=0x53,  		//Read monitor name(part number)
typedef struct
{
	BYTE btPartNumber;  //assicc
	
}stVcpPartNumber;


//DDC2B_CMD_GetMonitorRevisionNumber=0x18,//Read monitor revision number

//DDC2B_CMD_GetFirmwareVersion=0x02,  	//Read firmware version
typedef struct
{
	BYTE btNumber;  //Range 0~99.
					//Decimal 10 represent 1.0 

	
}stVcpRevisionNumber;

//DDC2B_CMD_GetMonitorModelNumber=0x3A,	//Read monitor model number

typedef struct
{

	BYTE btDataL;					//SL Byte 01h	monitor name 2701	
    BYTE btDataH;  //MH Byte27h
	
}stVcpModeNumber;


//DDC2B_CMD_GetPanelStatus=0x01,    		//Read panel status
typedef struct
{
    BYTE btStatus;  //Bit 0=0 power on
					//Bit 0=1 power off

	
}stVcpPanelStatus;

//DDC2B_CMD_GetRemainingLifeTime=0xED,	//Read remaining lifetime
//DDC2B_CMD_GetBacklightRunTime=0x09, 	//Read backlight run time

typedef struct
{

	BYTE btTimeL;  //low of the time
    BYTE btTimeH;  //high of the time
	
}stVcpTime;


//DDC2B_CMD_SetWindowAble=0x45     		//PIP window enable/Disable

typedef struct
{
	BYTE btAble;  
					//00h:Disable
					//01h:Enable
	
}stVcpWindowAble;
//    DDC2B_CMD_SetBright=0x10,               //set the display bright
//DDC2B_CMD_SetContrast=0x12              //set the display contrast
typedef struct
{

    BYTE btValueH;
    BYTE btValue;
}stVcpValue;

#endif
