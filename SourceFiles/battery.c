#include "main.h"
#include "cmsis_os2.h" // ::CMSIS:RTOS2
#include "battery.h"
#include "can.h"
#include "canMessage.h"
#define LOWVoltage 470 //uint: 0.1v

BMU_MESSAGE_T BUM_Msg;
BMS_SYSTEM_MESSAGE_T BMS_Sys_Msg;
BMS_MOS_Temperature_T BMS_MOS_Msg;

static uint8_t update_Date[8]={0,0,0,0,0,0,0,0};
/**
 * @brief Init battery system
 * 
 */
void InitBattery(void)
{
    UpDataBatteryMsg();
    while(BUM_Msg.Group_Voltage == 0);
    if(BUM_Msg.Group_Voltage < LOWVoltage)
        Error_Handler();
}

/**
 * @brief Send the message in order to update battery msg.
 * 
 * @return osStatus_t. Return function status.
 */
void UpDataBatteryMsg(void)
{
	CanTransmitMessage(CAN_ID_SRS_BMS,CAN_MSG_LEN,update_Date);
}

/**
 * @brief Get the Data BMU message.
 * 
 * @return BMU_MESSAGE_T 
 */
BMU_MESSAGE_T GetDataBMUMsg()
{
    return BUM_Msg;
}

void SetDataBMUMsg(uint8_t *playload)
{
    BUM_Msg.Group_Voltage = (playload[0]<<2) + playload[1];
    BUM_Msg.Soc = playload[4];
}

/**
 * @brief Get the data BMS System message.
 * 
 * @return BMS_SYSTEM_MESSAGE_T 
 */
BMS_SYSTEM_MESSAGE_T GetDataBMS_SystemMsg(void)
{
    
    return BMS_Sys_Msg;
}

void SetDataBMS_SystemMsg(uint8_t *playload)
{
    BMS_Sys_Msg.systemStatus = playload[0];
    BMS_Sys_Msg.hardwareAlarm = playload[6];
    BMS_Sys_Msg.hardwareFault  = playload[7];
}

/**
 * @brief Get the data BMS Mos message.
 * 
 * @return BMS_MOS_Temperature_T 
 */
void GetDataBMS_MOSMsg(void)
{
   
}
