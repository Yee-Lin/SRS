#pragma once

#include "stdbool.h"

/* ---------------- CAN identify define ------------------- */
#define SUCCESS_HEARTBEAT_MAP 0x2fffff

/*------------------VCU to Other--------------------------- */
#define VCU_RcuResponse                 0x190
#define RCU_StatuFb                     0x284
#define CAN_ID_VCU_LEFT_FRONT_MOTOR     0x4A4
#define CAN_ID_VCU_LEFT_REAR_MOTOR      0x4A3
#define CAN_ID_VCU_RIGHT_FRONT_MOTOR    0x4A2
#define CAN_ID_VCU_RIGHT_REAR_MOTOR     0x4A1
#define CAN_ID_VCU_FEPS                 0x416
#define CAN_ID_VCU_REPS                 0x426

/*------------------ Motor FeedBack--------------------------- */
#define CAN_ID_RIGHT_REAR_MOTOR_VCU_FB1     0x4B1
#define CAN_ID_RIGHT_REAR_MOTOR_VCU_FB2     0x4C1
#define CAN_ID_RIGHT_FRONT_MOTOR_VCU_FB1     0x4B2
#define CAN_ID_RIGHT_FRONT_MOTOR_VCU_FB2     0x4C2
#define CAN_ID_LEFT_REAR_MOTOR_VCU_FB1     0x4B3
#define CAN_ID_LEFT_REAR_MOTOR_VCU_FB2     0x4C3
#define CAN_ID_LEFT_FRONT_MOTOR_VCU_FB1     0x4B4
#define CAN_ID_LEFT_FRONT_MOTOR_VCU_FB2     0x4C4

/*------------------ EPS FeedBack--------------------------- */
#define CAN_ID_FEPS_VCU                 0x410
#define CAN_ID_REPS_VCU                 0x420

/*------------------ Battery FeedBack--------------------------- */
#define CAN_ID_BMU_VLOTAGE              0x782   
#define CAN_ID_BMU_FAULT                0x786
#define CAN_ID_BMS_TEMPERATURE          0x788
#define CAN_ID_SRS_BMS                  0x781

/*------------------ EBSP FeedBack--------------------------- */
#define CAN_ID_SRS_EBSP                 0x440  //SRS: security redundant system, hardware watchdog.
#define CAN_ID_EBSP_VCU                 0x446



#define APP_CAN_MSG_Q_LEN 32
#define CAN_MSG_LEN 8

void InitCanMsg(void);
bool CheckHeartBeat(void);
void RefreshHeartBeat(void);
uint32_t  GetHeartBeatStatus(void);
