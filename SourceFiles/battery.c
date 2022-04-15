#include "main.h"
#include "cmsis_os2.h" // ::CMSIS:RTOS2
#include "battery.h"
#include "can.h"

#define LOWVoltage 470 //uint: 0.1v
#define APP_CAN_MSG_Q_LEN 8
#define MAXCountQueue 5
extern osMessageQueueId_t appCan1SendQueueId;
extern osMessageQueueId_t appCan2SendQueueId;
osMessageQueueId_t BMU_MsgID;
osMessageQueueId_t BMS_SYSTEM_MsgID;
osMessageQueueId_t BMS_MOS_MsgID;



static uint8_t update_Date[8]={0,0,0,0,0,0,0,0};
/**
 * @brief Init battery system
 * 
 */
void InitBattery(void)
{
    osStatus_t osStatus;
    BMU_MESSAGE_T BUM_Msg;
    BMU_MsgID = osMessageQueueNew(MAXCountQueue,APP_CAN_MSG_Q_LEN,NULL);
    BMS_SYSTEM_MsgID = osMessageQueueNew(MAXCountQueue,APP_CAN_MSG_Q_LEN,NULL);
    BMS_MOS_MsgID = osMessageQueueNew(MAXCountQueue,APP_CAN_MSG_Q_LEN,NULL);
    osStatus =UpDataBatteryMsg();
    while(osStatus!=osOK) osStatus=UpDataBatteryMsg();
    BUM_Msg = GetDataBMUMsg();
    if(BUM_Msg.Group_Voltage < LOWVoltage)
        Error_Handler();
}

/**
 * @brief Send the message in order to update battery msg.
 * 
 * @return osStatus_t. Return function status.
 */
osStatus_t UpDataBatteryMsg(void)
{
//	osStatus_t osStatus = osMessageQueuePut(appCan2SendQueueId,update_Date,NULL,0);
//    return osStatus;
}

/**
 * @brief Get the Data BMU message.
 * 
 * @return BMU_MESSAGE_T 
 */
BMU_MESSAGE_T GetDataBMUMsg(void)
{
    BMU_MESSAGE_T BMU_Msg;
    osStatus_t osStatus_t = osMessageQueueGet(BMU_MsgID,&BMU_Msg,NULL,40);
    return BMU_Msg;
}

/**
 * @brief Get the data BMS System message.
 * 
 * @return BMS_SYSTEM_MESSAGE_T 
 */
BMS_SYSTEM_MESSAGE_T GetDataBMS_SystemMsg(void)
{
    BMS_SYSTEM_MESSAGE_T BMSS_Msg;
    osStatus_t osStatus_t = osMessageQueueGet(BMS_SYSTEM_MsgID,&BMSS_Msg,NULL,40);                               
    return BMSS_Msg;
}

/**
 * @brief Get the data BMS Mos message.
 * 
 * @return BMS_MOS_Temperature_T 
 */
BMS_MOS_Temperature_T GetDataBMS_MOSMsg(void)
{
    BMS_MOS_Temperature_T BMSM_Msg;
    osStatus_t osStatus_t = osMessageQueueGet(BMS_MOS_MsgID,&BMSM_Msg,NULL,40);
    return BMSM_Msg;
}
