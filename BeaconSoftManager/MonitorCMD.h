#ifndef _MONITORCMD_H_

#define _MONITORCMD_H_
#define ALL_PROTOCOL_DEFINE
#include <windows.h>
#include <QString>
/*
1.8(2019-10-25)
1.7(2017-1-10)
1.update the new protocol version with 4.0
2.communicate step please use the MC_GET_PROTOCOL_INFOR first when the command is success.use the MC_GET_GEN_BASIC_INFO
2.add  the struct MC_PARAM_GAMMA_NAME_OFFSET command


1.4(2016-6-24)
1���������м���Э��
MC_GET_PROTOCOL_INFOR,//get the protocol information
MC_GET_GEN_BASIC_INFO,//get the first general information
MC_GET_DISPLAY_RESOLUTION_AND_POSITION,//get the  display solution and position;
MC_GET_MODEL_STRING,//get the display model string
MC_READ_FSENSOR_MATRIX_PART, //read RGB->CIE partmatrix
MC_GET_SIMPLE_ORDER_PART,//get the simple order for part information


1.3(2015-4-20)
�޸�������sensor��Э��Ϊ����sensorЭ�飬�ֱ����Զ�ȡǰ��sensor�뱳��sensor������
1��2��2014-9-28)
������������ֱ��Ƕ�ȡ��ʾ���ڲ�GAMMA������Ϣ���õ������õ�ǰGAMMA���У�����������
MC_READ_GAMMA_NAME_INFO��  MC_GET_CURRENT_GAMMA��MC_SET_CURRENT_GAMMA,
1.1��2014-4-23��
�޸����еĴ��淽ʽ��������Э��ͳһ������λ��ǰ����λ�ں���ʽ��
1��0��2013-9-28��
������������Ѿ�������



*/
#define COMMUNICATE_TYPE_USB 1

#define  PROTOCL_FOR_MAX_READ_LENGHT(x)\
 int n_data_read_max=55;\
 int n_data_write_max=55;\
switch (x)\
{\
case 0x00:\
    n_data_read_max=55;\
    break;\
case 0x01:\
    n_data_read_max=22;\
    break;\
case 0x02:\
    n_data_read_max=112;\
    n_data_write_max=112;\
    break;\
case 0x03:\
    n_data_read_max=22;\
    n_data_write_max=22;\
    break;\
case 0x04:\
    n_data_read_max=52;\
    n_data_write_max=52;\
    break;\
default:\
    n_data_read_max = 22; \
}

//if(g_CommnunicateType==COMMUNICATE_TYPE_USB)
//{n_data_read_max=52;n_data_write_max=52;}

#define COMPARE_TABLES_PAIRS_FOR_LUMINANCE  DEGREE_OF_POLYNOMIAL
//#define COMPARE_TABLES_EVERY_PAKT_LEN_MAX 58
#define REPORT_DATA_BEGIN 3

//typedef unsigned char BYTE;
//typedef unsigned short WORD;
//typedef unsigned __LONG32 ULONG;
//typedef unsigned __LONG32 DWORD;
//typedef unsigned char byte;
//#define MAX_PATH 260
///this for the ddc_ci_dtat begin
#define DDC_CI_DATA_BEGIN 1 
//#define TRANSPORT_EVERY_DATA_LEN_MAX 56
#define TRANSPORT_EVERY_DATA_LEN_MAX 112

#define ORDER_PART_DATE_LEN   26

/*constants*/

#define STR_SIZE_SN 25
#define STR_SIZE_MODEL 13



//#define MAX_PKT_SIZE 64
#define MAX_PKT_SIZE 128
#define MAX_BYTE_LEN 256
typedef struct{
	
	BYTE LenWrite; //д���������
	BYTE LenRead;//��Ҫ�������ݳ���
	BYTE id;  //����
}MC_HEADER;

typedef struct{
	BYTE id;  //����
}MC_HEADER_DDC_CI;





typedef enum{
	  MC_GET_ORDER_STATUS=0,//check the  order status,if Mcu receive any order use this test order is no error
	  MC_GET_GEN_INFO, /*read inherent info of the monitor firmware, such as model, panel 
										 type firmware version etc*/

	  /*this command shall be responded as quick as possible so the host can use it to check sanity of the monitor*/
	  MC_GET_STATES, /* read monitor states, including power state, 
									 sync state, current CMD being executed etc */
	 MC_GET_SENSOR_DATA, /* read front sensor*/
	 MC_CALIB_SET_WIN_POS,  /*set calibration window*/
	 MC_CALIB_SET_WIN_RGB,  /*set calibration window rgb level*/
	  /*1a*/
	MC_GET_AMBI_LUMI, /* read ambient sensor*/  

	MC_SET_BACKLIGHT, /* change current backlight settings for calibration*/
	MC_SAVE_BACKLIGHT, /* save backlight settings*/  
	MC_WRITE_LUT_DATA, /* write LUT data */
	 MC_READ_LUT_DATA=10, /* read LUT data */
#ifdef ALL_PROTOCOL_DEFINE
	 MC_SET_COLOR_TEMP, /* set color temp*/  //not use 
	 MC_GET_CURRENT_LUT_ATTRI, /*get attribute of  a LUT */
	 MC_SAVE_LUT_ATTRI,  /*set attribute of a LUT */ 

	 MC_SET_LUT_ENTRY_VALUE, /* set value for the lut entry*/
 
	  MC_SAVE_SN, /*set serial number*/
	  MC_GET_SN, /*read serial number*/  
	  MC_WRITE_CO_TABLE, /* write co table  */
	  MC_READ_CO_TABLE, /* read co table*/

	  MC_FSENSOR_I2C_WRITE, /* write front sensor I2C, for factory use*/
	  MC_FSENSOR_I2C_READ, /* read front sensor I2C, for factory use*/

 
	  MC_WRITE_FSENSOR_MATRIX, /*write RGB->CIE matrix*/
	  MC_READ_FSENSOR_MATRIX, /*read RGB->CIE matrix*/
 
	  MC_WRITE_GSDF_DATA, /* write GSDF data*/
  
	  /*1b*/

	  MC_READ_GSDF_DATA, /* read GSDF data*/
#endif
	  MC_READ_GAMMA_NAME_INFO=25,//read the lut gamma information in the display
	  MC_GET_CURRENT_GAMMA,//Get the current gamma number of the string which MC_READ_GAMMA_NAME_INFO fallback
	  MC_SET_CURRENT_GAMMA,
	  MC_GET_PROTOCOL_INFOR,//get the protocol information
	  MC_GET_GEN_BASIC_INFO,//get the first general information
	  MC_GET_DISPLAY_RESOLUTION_AND_POSITION,//get the  display solution and position;
	  MC_GET_MODEL_STRING,//get the display model string
 #ifdef ALL_PROTOCOL_DEFINE 
	  MC_READ_FSENSOR_MATRIX_PART, /*read RGB->CIE partmatrix*/
	  MC_GET_SIMPLE_ORDER_PART,//get the simple order for part information
#endif 

      MC_SET_ATTRIBUTE_INFORMATION=36,
      MC_GET_ATTRIBUTE_INFORMATION,

      MC_SET_COLOR_COMPARE_DATA,
      MC_GET_COLOR_COMPARE_DATA,

      MC_Set_AB_VALUE_DATA,
      MC_Get_BACKLIGHT_LUMIN,
      MC_Get_AB_VALUE_DATA,
      MC_Set_BACKLIGHT_VALUE,

      MC_GET_ORDER_DDCCI_STATUS,//check the  order status,if Mcu receive any order use this test order is no error

      MC_GET_FPGA_HYBRID_GAMMA=0x36,
      MC_TOTAL
}MONITOR_CMD_ID;





//MC_GET_ORDER_STATUS,//check the  order status,if Mcu receive any order use this test order is no error
//if the PC2DDC send any other order,MCU receive the order and set status to 0x01,
// waiting  for PC send the MC_GET_ORDER_STATUS order to read the order status,MCU  send the last order status,and must
//set the status to 0x00. 
typedef struct
{
	BYTE btStatus; //1 for the ok
				   // 0 for error
}PARAM_GET_ORDER_STATUS;


typedef enum{	
   LC_GAMMA,
   LC_DICOM,   
   LC_CIE,//not use
   LC_OTHER /*curves that are not defined above*/ ,
   LC_USE_DEFINE_GUID
}LUT_CURVE;




typedef enum{
	
   M_MONO,
   M_COLOR,   	
   M_COLOR_TO_MONO,     
   
}MODEL_TYPE;//if the MODEL_TYPE| 0x08  this display only support to calibration


typedef enum{

   P_NEC,
   P_IDT,   	

   P_LG,
   P_SAMSUNG,   	
   	
   P_SHARP,

   P_AUO,
   P_CMO,
   
}PANEL_TYPE;



typedef enum{

	LUT_DATA_RTD_PACKED,
	LUT_DATA_UNPACKED,
	LUT_DATA_ATHENA_PACKED,
	LUT_DATA_RTD_2796


}LUT_DATA_FORMAT;

typedef enum{
	
		E_NONE, 	
		E_CHECKSUM,
		E_EXECUTION,   	
		
}ERROR_CODE;

typedef enum{
	CW_NONE,  /*close window*/
    CW_FRONT_SENSOR,	 //ʹУ���Ĳ˵�������sensor����λ��
	CW_CENTER,//ʹУ���Ĳ˵�������������  
	CW_FRONT_SENSOR_AND_CENTER, //ʹУ���Ĳ˵������������ļ�sensorλ��ͬʱ����
	CW_USER_DEFINE,		//�����û���ʹ�ô��ڣ�ʹ��ʾ������У������QA״̬
	CW_BYPASS_PATCH_MODE ,  //������ʾ���Լ�����Bypassͼ��  ��MC_CALIB_SET_WIN_RGB ��������  ��1������0x01����0x02
    CW_LUT_PATCH_MODE ,    //���ڲ�������LUT��ͼ��   //��MC_CALIB_SET_WIN_RGB ��������  ��1������0x01����0x02��1������

    CW_LUT_VCP =0xD6       //����ʾ������ģʽ�£������ȷ���DDCCI����ָ��VCP=0xD6[0xD6��0x01]
}CALIB_WIN_TYPE;

typedef enum{
	    DICOM_200=0x01,
		DICOM_250=0x02,
		DICOM_300=0x04,
		DICOM_350=0x08,
		DICOM_400=0x10,
		DICOM_450=0x20,
		DICOM_500=0x40,
		DICOM_550=0x80,
		
		DICOM_600=0x0100,
		DICOM_650=0x0200,
		DICOM_700=0x0400,
		DICOM_750=0x0800,
		DICOM_800=0x1000,
		DICOM_850=0x2000,
		DICOM_900=0x4000,
		DICOM_950=0x8000, 
		
}DICOM_SUPPORT_TYPE;
typedef enum{
		COLOR_TEMPERATURE_4000K=0x01,
		COLOR_TEMPERATURE_5000K=0x02,
		COLOR_TEMPERATURE_6500K=0x04,
		COLOR_TEMPERATURE_7500K=0x08,
		COLOR_TEMPERATURE_8200K=0x10,
		COLOR_TEMPERATURE_9300K=0x20,
		COLOR_TEMPERATURE_10000K=0x40,
		COLOR_TEMPERATURE_11500K=0x80, 
		COLOR_TEMPERATURE_13000K=0x0100,
		COLOR_TEMPERATURE_14000K=0x0200,



}COLOR_TEMPERATURE_SUPPORT_TYPE;

typedef enum{
    _DDCCI_BYPASS_PARAMTER,
    _DDCCI_COLOR1_PARAMTER,
    _DDCCI_COLOR2_PARAMTER,
}DDCCI_GAMMA_ADJUST_SET_PANEL_LUX_RANGE_PARAMTER;


/*
   params for MC_SAVE_SN (cmd)
                  MC_GET_SN (report)
*/
typedef struct{

   BYTE monitor_sn[STR_SIZE_SN]; 
					
}PARAM_SN;

/*
   params for MC_GET_MODEL_STRING (cmd)
   */
typedef struct
{
	BYTE model_string[STR_SIZE_MODEL];  
}PARAM_MODEL_STRING;

/*params for MC_GET_GEN_INFO*/	
typedef struct{
				BYTE version[2]; /*for the protocol version [0], major, [1], minor current version 1.3 */ 
				BYTE model; /*enum MODEL_TYPE */				
				BYTE sensor;   /*bit[0]:  have front sensor? 1 =yes, 0 = no 
								 bit[1]: have ambient sensor? 1 = yes 0 = no.
								bit[2]: have back sensor? 1 = yes 0 = no.
							*/
				BYTE screen_reflection_factor[2]; /*the reflection factor of the screen, in 1/1000*/// not use								
				
				BYTE lut_compression_mode; /*compression mode of LUT please see the LUT_DATA_FORMAT define*/								
				
				BYTE lut_step_max[2]; /* LUT step max value*///��������ֵ���磲������������������ʵ�ʽ���������	
				
				//[0] low byte
				//[1] hight byte
				
				BYTE lut_value_max[2]; /* LUT  max value*/	//	ֵ��������ֵ��1020��4096	
				//[0] low byte
				//[1] hight byte
				
				BYTE lut_gamma_size[2]; /**///���壬ѹ��֮��lut,�ܵ��ֽڳ���
				//[0] low byte
				//[1] hight byte
				
				BYTE bt_dicom_support[2];//define the support dicom  see the DICOM_SUPPORT_TYPE
				BYTE bt_color_temperature_support[2];//define the support color temperature  see the COLOR_TEMPERATURE_SUPPORT_TYPE
				BYTE bt_luminance_max[2];//m2
				BYTE scaler_fw_ver[2]; /*[0], major, [1], minor*/   
				BYTE model_string[STR_SIZE_MODEL];  
				BYTE sn_string[STR_SIZE_SN];
				
				
}PARAM_GEN_INFO;

/*params for MC_GET_GEN_BASIC_INFO*/	//for the height 1.4 version
typedef struct{
				BYTE version[2]; /*for the protocol version [0], major, [1], minor current version 1.3 */ 
				BYTE model; /*enum MODEL_TYPE */				
				BYTE sensor;   /*bit[0]:  have front sensor? 1 =yes, 0 = no 
								 bit[1]: have ambient sensor? 1 = yes 0 = no.
								bit[2]: have back sensor? 1 = yes 0 = no.
							*/
				BYTE screen_reflection_factor[2]; /*the reflection factor of the screen, in 1/1000*/// not use								
				
				BYTE lut_compression_mode; /*compression mode of LUT please see the LUT_DATA_FORMAT define*/								
				
				BYTE lut_step_max[2]; /* LUT step max value*///��������ֵ���磲������������������ʵ�ʽ���������	
				
				//[0] low byte
				//[1] hight byte
				
				BYTE lut_value_max[2]; /* LUT  max value*/	//	ֵ��������ֵ��1020��4096	
				//[0] low byte
				//[1] hight byte
				
				BYTE lut_gamma_size[2]; /**///���壬ѹ��֮��lut,�ܵ��ֽڳ���
				//[0] low byte
				//[1] hight byte
				
				BYTE bt_dicom_support[2];//define the support dicom  see the DICOM_SUPPORT_TYPE
				BYTE bt_color_temperature_support[2];//define the support color temperature  see the COLOR_TEMPERATURE_SUPPORT_TYPE
				BYTE bt_luminance_max[2];//m2
				BYTE scaler_fw_ver[2]; /*[0], major, [1], minor*/  	
				
				
}PARAM_GEN_BASIC_INFO;


//lut gamma ����
typedef struct{

   BYTE Luminance[2];  /* in cd/m2*/
				//[0] low byte
				 //[1] hight byte
				
   BYTE backlight;	//�˵�����ֵ��ֵ��0 ~255
   BYTE ambi[2];/*in lux*/ //���廷������ֵ��
			//[0] low byte
			 //[1] hight byte
   BYTE curve;//gamma���ͣ��뿴LUT_CURVE����
   BYTE btGamma;  /* btGamma= ((gamma x 100) - 100), valid only when curve == LC_GAMMA*/
}LUT_ATTRI;

//lut gamma ����
typedef struct {
    BYTE curve;//gamma���ͣ��뿴emCurveType����
    BYTE backlight[2];	//�˵�����ֵ��ֵ��0 ~255
                        //[0] low byte
                        //[1] hight byte
    BYTE value[2];/*   value*100 if the type is not LC_USE_DEFINE_GUID
                  gamma value for the LC_GAMMA,
                       ambient for teh LC_DICOM,
                       the curve GUID for the LC_USE_DEFINE_GUID*/ //���廷������ֵ��
                            //[0] low byte
                            //[1] hight byte
    BYTE MaxLuminance[2];   // in cd/m2 *10
                            //[0] low byte
                            //[1] hight byte
    BYTE contrast[2];  //
                        //[0] low byte
                        //[1] hight byte


}LUT_ATTRI_EXTEN;

/*
     MC_GET_LUT_ATTRI
     MC_SAVE_LUT_ATTRI
*/
//the MC_GET_LUT_ATTRI for PC2DDC 
typedef struct{

   BYTE lut_id; // 0: for the user gamma, other for the define gamma user for the  panel

}PARAM_LUT_ID;

//the MC_GET_LUT_ATTRI for DDC2PC
//and the MC_SAVE_LUT_ATTRI
typedef struct{
   BYTE lut_id; 
   LUT_ATTRI_EXTEN lut_attri;
}PARAM_LUT_ATTRI;

//MC_GET_STATES
typedef struct{

   BYTE power_sync; /*bit[1:0] power state 0 = power off, 1 = power on*/
                    /*bit[2] sync state 0 = no sync 1 = sync*/					
   
   BYTE color_temp;  /*color temp being used*/					
					
}PARAM_MONITOR_STATES;


/* params for MC_GET_AMBI_LUMI (report)*/
typedef struct{
	
    BYTE ambi_lux[2];
				//[0] low byte
				 //[1] hight byte
}PARAM_AMBI_SENSOR;





/*
   params for MC_SET_BACKLIGHT(cmd)
*/
typedef struct{

   BYTE backlight[2]; /*0 (dark) - 255 (bright)*/

}PARAM_SET_BACKLIGHT;


/*
   params for MC_SAVE_BACKLIGHT (cmd) 
*/
typedef struct{

   BYTE lut_id; /*the lut number*/
   BYTE backlight; /*0 (dark) - 255 (bright)*/
   
}PARAM_SAVE_BACKLIGHT;

//version 5.0
typedef struct{

   BYTE lut_id; /*the lut number*/
   BYTE backlight[2]; /*0 (dark) - 255 (bright)*/

}PARAM_SAVE_BACKLIGHT_EX;


/*
   params for MC_SET_LUT_ENTRY_VALUE (cmd)
*/
typedef struct{

   BYTE entry_index[2]; 
					//[0] low byte
					 //[1] hight byte
						//һ������ʾ������һ��ȫ�ڻ��棬Ȼ����ֵΪ0
   
   BYTE r[2]; /*byte 1 is most significant*/
	
   BYTE g[2]; /*byte 1 is most significant*/

   BYTE b[2]; /*byte 1 is most significant*/
   
}PARAM_LUT_ENTRY_VALUE;



/*
   params for MC_WRITE_LUT_DATA (cmd)
                  MC_READ_LUT_DATA (report)
*/
typedef struct{
	BYTE btDataLen; /*bytes of real btData length */

   BYTE lut_id; /*the lut id*///user gamma,always is 0
   BYTE offset[2];
   BYTE btData[TRANSPORT_EVERY_DATA_LEN_MAX];
   
}PARAM_LUT_DATA;

typedef struct{
   BYTE lut_id; /*the lut id*///user gamma,always is 0
   BYTE checksum[2];

}PARAM_LUT_CHECKSUM;
/*params for MC_WRITE_LUT_DATA (cmd)
                  MC_READ_CO_TABLE (report)
*/
typedef struct{

   BYTE btDataLen; /*bytes of real btData length */
   BYTE offset; 
   BYTE btData[TRANSPORT_EVERY_DATA_LEN_MAX];
   
}PARAM_CO_DATA;


/*params for MC_FSENSOR_I2C_WRITE (cmd)
                  MC_FSENSOR_I2C_READ (report)
*/
typedef struct{

   BYTE btDataLen; /*bytes of real btData length */
   BYTE dev_addr; 
   BYTE btData[TRANSPORT_EVERY_DATA_LEN_MAX];
   
}PARAM_I2C_DATA;



/*
   params for MC_GET_SENSOR_DATA(cmd)
*/
  typedef struct{
  
BYTE btContorl; //0x00 for MCU read data from front sensor data 
				//0x01 for PC read the MCU data which for the front sensor
				//0x20 for the back sensor to begin test the brightness luminance (update for hui 2015-4-20)
				//0x21 for the back sensor to read the data						  (update for hui 2015-4-20)
				//ע�⣬ÿһ��0x01֮ǰ������һ��0x00���ƣ�����ʱ400ms���ϡ�
	
}PARAM_CIE_CONTROL;



/*
   params for MC_GET_SENSOR_DATA(report)
*/ 
typedef struct{

	//[0] low byte
	
   BYTE X[4]; /*float *10000 */ //��λ��ǰ����λ�ں���
   BYTE Y[4]; /*float *10000*/ 
   BYTE Z[4]; /*float *10000 */ 
   
}PARAM_CIE;


/*
   params for MC_WRITE_FSENSOR_MATRIX(cmd)
*/
typedef struct{

   BYTE r[3][4]; /*float *10000 ȡ��*/  //��λ��ǰ����λ�ں�
   BYTE g[3][4]; /*float*100000*/
   BYTE b[3][4]; /*float*10000 */
   
}PARAM_MATRIX;


typedef struct{

   BYTE color_temp; 
   
}PARAM_COLOR_TEMP;





/*
   params for MC_CALIB_SET_WIN_POS(cmd)
*/
typedef struct{

   BYTE win_type; /*type CALIB_WIN_TYPE*/ 
}PARAM_CALIB_WIN_POS;

typedef struct{

   BYTE win_type; /*type CALIB_WIN_TYPE*/
   BYTE calib_set;
}PARAM_CALIB_BYPASS_WIN_POS;

/*
   params for MC_CALIB_SET_WIN_RGB(cmd)
*///ʹ��ODS����ͬһɫ����
typedef struct{

	//[0] low byte
	//[1] hight byte
   BYTE r[2]; /*we use word here in case some scalers have high color depth*/
   BYTE g[2]; 
   BYTE b[2]; 
   
}PARAM_CALIB_WIN_RGB;


//MC_READ_GAMMA_NAME_INFO,//read the lut gamma information in the display

typedef struct{

	BYTE offset;//the string offset","
	//when version >4.0 the max is 22 for every park

}MC_PARAM_GAMMA_NAME_OFFSET;


typedef struct{

	BYTE param_name_string[MAX_BYTE_LEN];//include all the gamma name which the display have divide by the ","
                                            //Gamma and color temperature separation by ";"
	//when version >4.0 the max is 22 for every park

}MC_PARAM_GAMMA_NAME;

//MC_GET_CURRENT_GAMMA,//Get the current gamma number of the string which MC_READ_GAMMA_NAME_INFO feedback
// MC_SET_CURRENT_GAMMA,

typedef struct{

    BYTE param_number;//the gamma name number in the display ,0-4bit is gamma,5-7bit is color temperature

}MC_PARAM_GAMMA_NUMBER;

typedef struct{

    BYTE btIndex;//the gamma name number in the display ,0-4bit is gamma,5-7bit is color temperature
    BYTE aValue[4];
    BYTE bValue[4];
}MC_PARAM_AB_VALUE;

typedef struct{
    BYTE aValue[4];
    BYTE bValue[4];
}MC_GET_PARAM_AB_VALUE;

typedef struct{
    BYTE id;
    BYTE max_luminace[4];
    BYTE min_luminace[4];
}MC_SET_PARAM_COLOR_COMPARA;

typedef struct{
    BYTE luminace_value[33];
}MC_GET_PARAM_COLOR_COMPARA;


//MC_GET_PROTOCOL_INFOR,//get the protocol information
//typedef struct
//{
//	BYTE protocol_version[2]; /*for the protocol version [0], major, [1], minor current version 1.3 */
//	BYTE type;//for the chip //��������II�ö�ȡ���ݵĳ��ȣ�Ŀǰ
//	/*
//								0x00:  Write:55 Read : 55
//								0x01 : Write:55 Read:22
//								0x02 : Write : 112 Read : 112
//								0x03 : Write : 22 Read : 22//1.8Э���汾����
//								����:  Write : 55 Read : 22
		
//		*/
//	BYTE chipLabel[10];//for the chip label for the different operator
//	BYTE reserved[5];
//    bool IsRightChipLabel(QString strChip)
//	{
//		char chip_name[11]={0};
//		memcpy(chip_name,chipLabel,10);
//        QString str_name(chip_name);
//        return strChip.compare(str_name)==0;
//	}
//}PARAM_PROTOCOL_VERSION;


//MC_GET_PROTOCOL_INFOR,//get the protocol information
typedef struct
{
    BYTE protocol_version[2]; /*for the protocol version [0], major, [1], minor current version 1.3 */
    BYTE type;//for the chip //��������II�ö�ȡ���ݵĳ��ȣ�Ŀǰ
    /*
                                0x00:  Write:55 Read : 55
                                0x01 : Write:55 Read:22
                                0x02 : Write : 112 Read : 112
                                0x03 : Write : 22 Read : 22//1.8Э���汾����
                                ����:  Write : 55 Read : 22

        */
    BYTE chipLabel[10];//for the chip label for the different operator
    BYTE brightMax[2];
    BYTE reserved[3];
    bool IsRightChipLabel(QString strChip)
    {
        char chip_name[11]={0};
        memcpy(chip_name,chipLabel,10);
        QString str_name(chip_name);

        return strChip.compare(str_name)==0;
    }
}PARAM_PROTOCOL_VERSION;

#ifdef ALL_PROTOCOL_DEFINE

	/*
	   params for error report
	*/
	typedef struct{

	   BYTE error; /*type ERROR_CODE*/

	}PARAM_ERROR;






	typedef struct{

       int param_size_cmd;
       int param_size_report;
   
	}MC_PARAM_SIZE;



	/*params for MC_WRITE_GSDF_DATA (cmd)
	MC_READ_GSDF_DATA (report)
	mcu �ṩ����8088���ֽڣ�
	�ռ䣬ǰ4���ֽڴ����ռ���ʵ��ʹ�õ��ֽ�����
	*/
	typedef struct{
	
		BYTE btDataLen; /*bytes of real btData length */
		BYTE offset[2]; /*byte 1 is most significant*/
		BYTE btData[TRANSPORT_EVERY_DATA_LEN_MAX];
	
	
	}PARAM_GSDF_DATA;




	   //MC_READ_FSENSOR_MATRIX_PART, /*read RGB->CIE partmatrix*/

	typedef struct{
	   BYTE btChannel; //0 for r,1 for g, 2 fro b
	   BYTE data[3][4]; /*float *10000 ȡ��*/  //��λ��ǰ����λ�ں� 
   
	}PARAM_MATRIX_PART;


	//MC_GET_SIMPLE_ORDER_PART,//get the Order SIMPLE_data information
	typedef struct
	{
		BYTE btOrder;//read simpleorder
		BYTE btDataLen; /*bytes of real btData length */
		BYTE offset; /**/
		BYTE btData[ORDER_PART_DATE_LEN];

	}PARAM_SIMPALE_ORDER_PART;


	 //MC_GET_DISPLAY_RESOLUTION_AND_POSITION,//get the  display solution and position;
    typedef struct
    {
        WORD dw_default_resolution_width;//display default resolution width
        WORD dw_default_resolution_height;//display default resolution height

        WORD dw_real_resolution_width;//display real resolution width
        WORD dw_real_resolution_height;//display real resolution height

        WORD dw_sensor_window_x;//sensor window x;
        WORD dw_sensor_window_y;//sensor window y;
        WORD dw_sensor_window_width;//sensor window width
        WORD dw_sensor_window_height;//sensor window height

    }PARAM_RESOLUTION_AND_SENSOR_POSITION;
	/*
	MONITOR_CMD_ID table_cmds_with_param_ex[] ={
		MC_WRITE_LUT_DATA,
			MC_WRITE_CO_TABLE,
			MC_FSENSOR_I2C_WRITE,
	};

	MONITOR_CMD_ID table_reports_with_param_ex[] ={
		MC_READ_LUT_DATA,
			MC_READ_CO_TABLE,
			MC_FSENSOR_I2C_READ,
	};

	*/


	extern MC_PARAM_SIZE mc_param_size_table[MC_TOTAL] ;


    //	MC_GET_ATTRIBUTE_INFORMATION,//get the attribute information data
    //		MC_SET_ATTRIBUTE_INFORMATION,//set the  attribute information data
        enum
        {
            BEACON_DISPLAY_MODE_NULL=0,
            BEACON_DISPLAY_MODE_UNIFORMITY = 1, //for control uniformity on or off
            BEACON_DISPLAY_MODE_COLORSPALCE = 2,//for control COLORSPALCE on or off
        };
        enum
        {
            BEACON_DISPLAY_STATUS_OFF=0,
            BEACON_DISPLAY_STATUS_ON ,
        };
        typedef struct
        {
            BYTE mode;//the display mode item
            BYTE status; /*bytes of real btData length */
            //BYTE btData[10];//unused

        }PARAM_ATTRIBUTE_INFORMATION;

  #endif 
#endif



