#include "main.h"
#include "cmsis_os2.h" // ::CMSIS:RTOS2
#include "brake.h"
#include "can.h"

extern osMessageQueueId_t appCan1SendQueueId;
extern osMessageQueueId_t appCan2SendQueueId;





static uint8_t brake_Data[8]={0x05,0,0,0,0,0,0,0};
static uint8_t release_Data[8]={0x06,0,0,0,0,0,0,0};

osStatus_t Braking(void)
{
//    osStatus_t osStatus = osMessageQueuePut(appCan2SendQueueId,brake_Data,NULL,0);
//    return osStatus;
}
osStatus_t Release(void)
{
//    osStatus_t osStatus = osMessageQueuePut(appCan2SendQueueId,release_Data,NULL,0);
//    return osStatus;
}

