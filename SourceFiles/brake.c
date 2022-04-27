#include "main.h"
#include "cmsis_os2.h" // ::CMSIS:RTOS2
#include "brake.h"
#include "can.h"
#include "canMessage.h"

EBSP_SRS_MESSAGE_T EBSP_SRS_MSG;

static uint8_t brake_Data[8]={0x05,0,0,0,0,0,0,0};
static uint8_t release_Data[8]={0x06,0,0,0,0,0,0,0};

void Braking(void)
{
    CanTransmitMessage(CAN_ID_SRS_EBSP,CAN_MSG_LEN,brake_Data);
}

void Release(void)
{
    CanTransmitMessage(CAN_ID_SRS_EBSP,CAN_MSG_LEN,release_Data);
}

EBSP_SRS_MESSAGE_T GetDataEBSP_SRSMsg(void)
{
    return EBSP_SRS_MSG;
}
void SetDataEBSP_SRSMsg(uint8_t *playload)
{
    EBSP_SRS_MSG.current = *(uint16_t *)playload;
    EBSP_SRS_MSG.statusTurn = playload[2];
    EBSP_SRS_MSG.statusBrake = playload[3];
    EBSP_SRS_MSG.temperature = playload[4];
    EBSP_SRS_MSG.statuFault = playload[5];
    EBSP_SRS_MSG.sensorLocation = playload[6];
}

bool Get_If_BrakeStatus(void){
    if(EBSP_SRS_MSG.statusBrake == 0 && EBSP_SRS_MSG.statusBrake == 2)
        return false;
    else
        return true;
}
