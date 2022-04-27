#pragma once
#include "cmsis_os2.h" // ::CMSIS:RTOS2

typedef struct 
{
    uint16_t Group_Voltage; //overall battery voltage
    uint16_t Group_Current; //overall battery current
    uint8_t Soc;    //Percentage of battery string remaining charge
    uint8_t Soh;    //Battery health percentage
}BMU_MESSAGE_T;

typedef struct
{
    uint8_t systemStatus;
    uint32_t systemFault;
    uint8_t bmsMode;
    uint8_t hardwareAlarm;
    uint8_t hardwareFault;
}BMS_SYSTEM_MESSAGE_T;

typedef struct
{ 
    uint8_t MOS_Temperature;
    uint8_t ENVIRONMENT_Temperature;
    uint8_t GROUP1_Temperature;
    uint8_t GROUP2_Temperature;
    uint8_t GROUP3_Temperature;
    uint8_t GROUP4_Temperature;
}BMS_MOS_Temperature_T;

void InitBattery(void);
void UpDataBatteryMsg(void);
BMU_MESSAGE_T GetDataBMUMsg(void);
BMS_SYSTEM_MESSAGE_T GetDataBMS_SystemMsg(void);
void GetDataBMS_MOSMsg(void);
void SetDataBMS_SystemMsg(uint8_t *playload);
void SetDataBMUMsg(uint8_t *playload);
