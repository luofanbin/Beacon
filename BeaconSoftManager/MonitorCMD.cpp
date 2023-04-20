#include "MonitorCMD.h"

BYTE bt_only_address[255];
/* refer to this table for what data packet is associated to a CMD or report */
/*todo: move this table to a "c file"*/
/*Warning: the order of items of this table must correspond to enum MONITOR_CMD_ID*/
MC_PARAM_SIZE mc_param_size_table[MC_TOTAL] = {
     {0, sizeof(PARAM_GET_ORDER_STATUS)}, /*MC_GET_ORDER_STATUS*/
   {0, sizeof(PARAM_GEN_INFO)}, /*MC_GET_GEN_INFO */
   {0, sizeof(PARAM_MONITOR_STATES)}, /*MC_GET_STATES */
    {sizeof(PARAM_CIE_CONTROL), sizeof(PARAM_CIE)},  /*MC_GET_SENSOR_DATA*/
     {sizeof(PARAM_CALIB_BYPASS_WIN_POS), 0}, /*MC_CALIB_SET_WIN_POS*/
   {sizeof(PARAM_CALIB_WIN_RGB), 0}, /*MC_CALIB_SET_WIN_RGB*/
  {0, sizeof(PARAM_AMBI_SENSOR)}, /* MC_GET_AMBI_LUMI */
	 {sizeof(PARAM_SET_BACKLIGHT), 0}, /*MC_SET_BACKLIGHT */
   {sizeof(PARAM_SAVE_BACKLIGHT_EX), 0}, /*MC_SAVE_BACKLIGHT*/
	 {4,0},//{sizeof((PARAM_LUT_DATA)), 0},      /*MC_WRITE_LUT_DATA*/
	 {4,4},//{sizeof(PARAM_LUT_DATA), sizeof(PARAM_LUT_DATA)}, /*MC_READ_LUT_DATA*/ 
	 {sizeof(PARAM_COLOR_TEMP), 0}, /*MC_SET_COLOR_TEMP*/
   {sizeof(PARAM_LUT_ATTRI), sizeof(PARAM_LUT_ATTRI)},   /*MC_GET_CURRENT_LUT_ATTRI*/
	{sizeof(PARAM_LUT_ATTRI), 0},   /*MC_SAVE_LUT_ATTRI*/
	
	{sizeof(PARAM_LUT_ENTRY_VALUE), 0}, /*MC_SET_LUT_ENTRY_VALUE*/
   {sizeof(PARAM_SN), 0}, /*MC_SAVE_SN*/
   {0, sizeof(PARAM_SN)}, /*MC_GET_SN*/

	
	 {2,0}, //{sizeof(PARAM_CO_DATA), 0},       /*MC_WRITE_CO_TABLE*/
	 {2,2},//{sizeof(PARAM_CO_DATA), sizeof(PARAM_CO_DATA)}, /*MC_READ_CO_TABLE*/

	 {2,0},//{sizeof(PARAM_I2C_DATA), 0}, /*MC_FSENSOR_I2C_WRITE write front sensor I2C, for factory use*/
    {2,2}, //{sizeof(PARAM_I2C_DATA), sizeof(PARAM_I2C_DATA)}, /* MC_FSENSOR_I2C_READ,  read front sensor I2C, for factory use*/
 
   
   {sizeof(PARAM_MATRIX), 0}, /*MC_WRITE_FSENSOR_MATRIX*/
   {0, sizeof(PARAM_MATRIX)}, /* MC_READ_FSENSOR_MATRIX */

   
  
 
	 {3,0}, //{sizeof(PARAM_GSDF_DATA), 0},       /*MC_WRITE_GSDF_DATA*/
	 {3,3},//{sizeof(PARAM_GSDF_DATA), sizeof(PARAM_GSDF_DATA)}, /*MC_READ_GSDF_DATA*/
	 {0,sizeof(MC_PARAM_GAMMA_NAME)},//MC_READ_GAMMA_NAME_INFO
	 {0,sizeof(MC_PARAM_GAMMA_NUMBER)},//MC_GET_CURRENT_GAMMA
     {sizeof(MC_PARAM_GAMMA_NUMBER),0},
     {0,sizeof(PARAM_PROTOCOL_VERSION)},  //MC_GET_PROTOCOL_INFOR,//get the protocol information
	 {0,sizeof(PARAM_GEN_BASIC_INFO)},//MC_GET_GEN_BASIC_INFO,//get the first general information
     {0,sizeof(PARAM_RESOLUTION_AND_SENSOR_POSITION)},//MC_GET_DISPLAY_RESOLUTION_AND_POSITION,//get the  display solution and position;
	 {0,sizeof(PARAM_MODEL_STRING)},//MC_GET_MODEL_STRING,//get the display model string
	 {1,sizeof(PARAM_MATRIX_PART)},//MC_READ_FSENSOR_MATRIX_PART
	 {3,sizeof(PARAM_SIMPALE_ORDER_PART)},//MC_GET_SIMPLE_ORDER_PART,//get the simple order for part information

    {2,2},
    {2,2},

    {sizeof(PARAM_ATTRIBUTE_INFORMATION),0},//MC_SET_ATTRIBUTE_INFORMATION,//get uniformity on or off
    {sizeof(PARAM_ATTRIBUTE_INFORMATION),sizeof(PARAM_ATTRIBUTE_INFORMATION)},//MC_GET_ATTRIBUTE_INFORMATION,//set uniformity on or off


    {sizeof(MC_SET_PARAM_COLOR_COMPARA),sizeof(MC_SET_PARAM_COLOR_COMPARA)},
    {0,sizeof(MC_GET_PARAM_COLOR_COMPARA)},
    {sizeof(MC_PARAM_AB_VALUE),sizeof(MC_PARAM_AB_VALUE)},
    {0,6},
    {0,sizeof(MC_GET_PARAM_AB_VALUE)},
    {sizeof(MC_PARAM_GAMMA_NUMBER),0},
    {0, 6}, /*45*/
    {0, 6}, /*46*/
    {0, 6}, /*47*/
    {0, 6}, /*48*/
    {0, 6}, /*49*/
    {0, 6}, /*50*/
    {0, 6}, /*51*/
    {0, 6}, /*52*/
    {0, 6}, /*53*/
    {0, 3}, /*MC_GET_FPGA_HYBRID_GAMMA*/
};
