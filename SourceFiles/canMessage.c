#include "main.h"
#include "canMessage.h"
#include "can.h"


/* bit0:CAN_ID_VCU_FEPS  1:CAN_ID_VCU_REPS   2:CAN_ID_FEPS_VCU   3:CAN_ID_REPS_VCU
4:CAN_ID_VCU_LEFT_FRONT_MOTOR   5:CAN_ID_VCU_LEFT_REAR_MOTOR    6:CAN_ID_VCU_RIGHT_FRONT_MOTOR
7:CAN_ID_VCU_RIGHT_REAR_MOTOR   8:CAN_ID_BMU_VLOTAGE    9:CAN_ID_BMU_FAULT
10:CAN_ID_BMS_TEMPERATURE   11:CAN_ID_EBSP_SRS */
uint16_t HeartBeatMap = 0x0000u;

void VcuMsgCallBack(uint32_t canID, uint32_t size, uint8_t* message){
    if(canID == CAN_ID_VCU_FEPS){
        HeartBeatMap &= 0x0001;
    }
    else if (canID == CAN_ID_VCU_REPS){
        HeartBeatMap &= 0x0002;
    }
    
}

void EpsMsgCallBack(uint32_t canID, uint32_t size, uint8_t* message){
    if(canID == CAN_ID_FEPS_VCU){
        HeartBeatMap &= 0x0004;
    }
    else if (canID == CAN_ID_REPS_VCU){
        HeartBeatMap &= 0x0008;
    }
}

void MotorMsgCallBack(uint32_t canID, uint32_t size, uint8_t* message){
    if(canID == CAN_ID_VCU_LEFT_FRONT_MOTOR){
        HeartBeatMap &= 0x0010;
    }
    else if(canID == CAN_ID_VCU_LEFT_REAR_MOTOR){
        HeartBeatMap &= 0x0020;
    }
    else if(canID == CAN_ID_VCU_RIGHT_FRONT_MOTOR){
        HeartBeatMap &= 0x0040;
    }
    else if(canID == CAN_ID_VCU_RIGHT_REAR_MOTOR){
        HeartBeatMap &= 0x0080;
    }

}

void EbsMsgCallBack(uint32_t canID, uint32_t size, uint8_t* message){

}

void BatteryMsgCallBack(uint32_t canID, uint32_t size, uint8_t* message){
    if(canID == CAN_ID_BMU_VLOTAGE){
        HeartBeatMap &= 0x0100;
    }
    else if(canID == CAN_ID_BMU_FAULT){
        HeartBeatMap &= 0x0200;
    }
    else if(canID == CAN_ID_BMS_TEMPERATURE){
        HeartBeatMap &= 0x0400;
    }
}

void EbspMsgCallBack(uint32_t canID, uint32_t size, uint8_t* message){
     if(canID == CAN_ID_EBSP_SRS){
         HeartBeatMap &= 0x0800;
    }
}

void InitCanMsg(void)
{
	CanRegisterCallback(CAN_ID_EBSP_SRS, 0xFFFFFFF8, EbspMsgCallBack);

	CanRegisterCallback(CAN_ID_VCU_LEFT_FRONT_MOTOR, 0xFFFFFFF8, MotorMsgCallBack);
    CanRegisterCallback(CAN_ID_VCU_LEFT_REAR_MOTOR, 0xFFFFFFF8, MotorMsgCallBack);
    CanRegisterCallback(CAN_ID_VCU_RIGHT_FRONT_MOTOR, 0xFFFFFFF8, MotorMsgCallBack);
    CanRegisterCallback(CAN_ID_VCU_RIGHT_REAR_MOTOR, 0xFFFFFFF8, MotorMsgCallBack);

    CanRegisterCallback(CAN_ID_VCU_FEPS, 0xFFFFFFF8, VcuMsgCallBack);
    CanRegisterCallback(CAN_ID_VCU_REPS, 0xFFFFFFF8, VcuMsgCallBack);

    CanRegisterCallback(CAN_ID_FEPS_VCU, 0xFFFFFFF8, EpsMsgCallBack);
    CanRegisterCallback(CAN_ID_REPS_VCU, 0xFFFFFFF8, EpsMsgCallBack);

    CanRegisterCallback(CAN_ID_BMU_VLOTAGE, 0xFFFFFFF8, BatteryMsgCallBack);
    CanRegisterCallback(CAN_ID_BMU_FAULT, 0xFFFFFFF8, BatteryMsgCallBack);
    CanRegisterCallback(CAN_ID_BMS_TEMPERATURE, 0xFFFFFFF8, BatteryMsgCallBack);

}