#include "main.h"
#include "canMessage.h"
#include "can.h"
#include "battery.h"
#include "eps.h"
#include "vcu.h"
#include "motorDrive.h"
uint32_t HeartBeatMap = 0x00000000u;


void VcuMsgCallBack(uint32_t canID, uint32_t size, uint8_t* message){
    if(canID == CAN_ID_VCU_FEPS){
        HeartBeatMap &= 0x0001;
        SetDataVCU_EPSMsg(message,FrontEPS);
    }

    else if (canID == CAN_ID_VCU_REPS){
        HeartBeatMap &= 0x0002;
        SetDataVCU_EPSMsg(message,RearEPS);
    }
    else if (canID == VCU_RcuResponse){
        HeartBeatMap &= 0x0004;
        SetDataVCU_RcuResponseMsg(message);
    }
    else if (canID == RCU_StatuFb){
        HeartBeatMap &= 0x0008;
        SetDataRCU_StatuFbMsg(message);
    }
    else if(canID == CAN_ID_VCU_LEFT_FRONT_MOTOR){
        HeartBeatMap &= 0x0010;
        SetDataVCU_MOTORMsg(message,LEFT_FRONT_MOTOR);
    }

    else if(canID == CAN_ID_VCU_LEFT_REAR_MOTOR){
        HeartBeatMap &= 0x0020;
        SetDataVCU_MOTORMsg(message,LEFT_REAR_MOTOR);
    }

    else if(canID == CAN_ID_VCU_RIGHT_FRONT_MOTOR){
        HeartBeatMap &= 0x0040;
        SetDataVCU_MOTORMsg(message,RIGHT_FRONT_MOTOR);
    }

    else if(canID == CAN_ID_VCU_RIGHT_REAR_MOTOR){
        HeartBeatMap &= 0x0080;
        SetDataVCU_MOTORMsg(message,RIGHT_REAR_MOTOR);
    }
}

void MotorMsgCallBack(uint32_t canID, uint32_t size, uint8_t* message)
{
    if(canID == CAN_ID_LEFT_FRONT_MOTOR_VCU_FB1){
        HeartBeatMap &= 0x0100;
       SetDataMotor_VCUFB1Msg(message,0);
    }

    else if (canID == CAN_ID_LEFT_FRONT_MOTOR_VCU_FB2){
        HeartBeatMap &= 0x0200;
       SetDataMotor_VCUFB2Msg(message,0);
    }
    else if (canID == CAN_ID_RIGHT_FRONT_MOTOR_VCU_FB1){
        HeartBeatMap &= 0x0400;
        SetDataMotor_VCUFB1Msg(message,1);
    }
    else if (canID == CAN_ID_RIGHT_FRONT_MOTOR_VCU_FB2){
        HeartBeatMap &= 0x0800;
        SetDataMotor_VCUFB2Msg(message,1);
    }
    else if(canID == CAN_ID_LEFT_REAR_MOTOR_VCU_FB1){
        HeartBeatMap &= 0x1000;
        SetDataMotor_VCUFB1Msg(message,2);
    }

    else if(canID == CAN_ID_LEFT_REAR_MOTOR_VCU_FB2){
        HeartBeatMap &= 0x2000;
       SetDataMotor_VCUFB2Msg(message,2);
    }

    else if(canID == CAN_ID_RIGHT_REAR_MOTOR_VCU_FB1){
        HeartBeatMap &= 0x4000;
        SetDataMotor_VCUFB1Msg(message,3);
    }

    else if(canID == CAN_ID_RIGHT_REAR_MOTOR_VCU_FB2){
        HeartBeatMap &= 0x8000;
        SetDataMotor_VCUFB2Msg(message,3);
    }
}

void EpsMsgCallBack(uint32_t canID, uint32_t size, uint8_t* message){

    if(canID == CAN_ID_FEPS_VCU){
        HeartBeatMap &= 0x10000;
        SetDataEPS_VCUMsg(message,FrontEPS);
    }

    else if (canID == CAN_ID_REPS_VCU){
        HeartBeatMap &= 0x20000;
        SetDataEPS_VCUMsg(message,RearEPS);
    }
}

void BatteryMsgCallBack(uint32_t canID, uint32_t size, uint8_t* message){
    if(canID == CAN_ID_BMU_VLOTAGE){
        HeartBeatMap &= 0x40000;
        SetDataBMUMsg(message);
    }
    else if(canID == CAN_ID_BMU_FAULT){
        HeartBeatMap &= 0x80000;
    }
    else if(canID == CAN_ID_BMS_TEMPERATURE){
        HeartBeatMap &= 0x100000;
    }
}

void EbspMsgCallBack(uint32_t canID, uint32_t size, uint8_t* message){
     if(canID == CAN_ID_EBSP_VCU){
         HeartBeatMap &= 0x200000;
    }
}

void EbsMsgCallBack(uint32_t canID, uint32_t size, uint8_t* message)
{

}

void InitCanMsg(void)
{
	CanRegisterCallback(CAN_ID_EBSP_VCU, 0xFFFFFFF8, EbspMsgCallBack);

	CanRegisterCallback(CAN_ID_VCU_LEFT_FRONT_MOTOR, 0xFFFFFFF8, VcuMsgCallBack);
    CanRegisterCallback(CAN_ID_VCU_LEFT_REAR_MOTOR, 0xFFFFFFF8, VcuMsgCallBack);
    CanRegisterCallback(CAN_ID_VCU_RIGHT_FRONT_MOTOR, 0xFFFFFFF8, VcuMsgCallBack);
    CanRegisterCallback(CAN_ID_VCU_RIGHT_REAR_MOTOR, 0xFFFFFFF8, VcuMsgCallBack);

    CanRegisterCallback(CAN_ID_RIGHT_REAR_MOTOR_VCU_FB1, 0xFFFFFFF8, VcuMsgCallBack);
    CanRegisterCallback(CAN_ID_RIGHT_FRONT_MOTOR_VCU_FB1, 0xFFFFFFF8, VcuMsgCallBack);
    CanRegisterCallback(CAN_ID_LEFT_REAR_MOTOR_VCU_FB1, 0xFFFFFFF8, VcuMsgCallBack);
    CanRegisterCallback(CAN_ID_LEFT_FRONT_MOTOR_VCU_FB1, 0xFFFFFFF8, VcuMsgCallBack);
    CanRegisterCallback(CAN_ID_RIGHT_REAR_MOTOR_VCU_FB2, 0xFFFFFFF8, VcuMsgCallBack);
    CanRegisterCallback(CAN_ID_RIGHT_FRONT_MOTOR_VCU_FB2, 0xFFFFFFF8, VcuMsgCallBack);
    CanRegisterCallback(CAN_ID_LEFT_REAR_MOTOR_VCU_FB2, 0xFFFFFFF8, VcuMsgCallBack);
    CanRegisterCallback(CAN_ID_LEFT_FRONT_MOTOR_VCU_FB2, 0xFFFFFFF8, VcuMsgCallBack);

    CanRegisterCallback(CAN_ID_VCU_FEPS, 0xFFFFFFF8, VcuMsgCallBack);
    CanRegisterCallback(CAN_ID_VCU_REPS, 0xFFFFFFF8, VcuMsgCallBack);

    CanRegisterCallback(VCU_RcuResponse, 0xFFFFFFF8, VcuMsgCallBack);
    CanRegisterCallback(RCU_StatuFb, 0xFFFFFFF8, VcuMsgCallBack);

    CanRegisterCallback(CAN_ID_FEPS_VCU, 0xFFFFFFF8, EpsMsgCallBack);
    CanRegisterCallback(CAN_ID_REPS_VCU, 0xFFFFFFF8, EpsMsgCallBack);

    CanRegisterCallback(CAN_ID_BMU_VLOTAGE, 0xFFFFFFF8, BatteryMsgCallBack);
    CanRegisterCallback(CAN_ID_BMU_FAULT, 0xFFFFFFF8, BatteryMsgCallBack);
    CanRegisterCallback(CAN_ID_BMS_TEMPERATURE, 0xFFFFFFF8, BatteryMsgCallBack);
    InitCan();
}

bool CheckHeartBeat(void)
{
    if(HeartBeatMap == SUCCESS_HEARTBEAT_MAP )
        return true;
    else
        return false;
}

void RefreshHeartBeat(void)
{
    HeartBeatMap = 0x00000000u;
}

uint32_t  GetHeartBeatStatus(void)
{
    return HeartBeatMap;
}

