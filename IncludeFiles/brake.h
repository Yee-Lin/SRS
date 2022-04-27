#pragma once

#include "stdbool.h"
typedef struct 
{
    uint16_t current;
    uint8_t statusTurn;
    uint8_t statusBrake;
    uint8_t temperature;
    uint8_t statuFault;
    uint8_t sensorLocation;
}EBSP_SRS_MESSAGE_T;

void Braking(void);
void Release(void);
EBSP_SRS_MESSAGE_T GetDataEBSP_SRSMsg(void);
void SetDataEBSP_SRSMsg(uint8_t *playload);
bool Get_If_BrakeStatus(void);
