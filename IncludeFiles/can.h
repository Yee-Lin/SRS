#pragma once

#include <stdint.h>

/* ---------------- CAN identify define ------------------- */
#define COB_ID_M2S 0x600
#define COB_ID_S2M 0x580
#define COB_ID_MOTOR_HEARTBEAT 0x700
#define COB_ID_SET_SPEED 0x200
#define COB_ID_M2V_VOL_ERR 0x1A0
#define COB_ID_M2V_SPD_POS 0x180
#define CAN_ID_REMOTE_VCU 0x283
#define CAN_ID_VCU_REMOTE 0x190
#define CAN_ID_SONIC_TO_VCU 0x300
#define CAN_ID_VCU_TO_SONIC 0x308
#define CAN_ID_VCU_TO_LCD_TL 0x310
#define CAN_ID_VCU_TO_LCD_TR 0x311
#define CAN_ID_VCU_TO_LCD_BL 0x312
#define CAN_ID_VCU_TO_LCD_BR 0x313
#define CAN_ID_VCU_TO_IO 0x314
#define CAN_ID_IO_TO_VCU 0x315
#define CAN_ID_TEMPERATURE 0x316
#define CAN_ID_VCU_TO_IO_BRAKE 0x317
#define CAN_ID_VCU_TO_CARGO 0x318
#define CAN_ID_CARGO_TO_VCU 0x319
#define CAN_ID_CONTROL_CARGO_LID 0x31A
#define CAN_ID_CARGO_LID_FEEDBACK 0x31B
#define CAN_ID_VCU_TO_EBS 0x440
#define CAN_ID_EBS_TO_VCU 0x446

/* ---------------- Data type definition -------------------- */
#define CAN_MSG_LEN 8
typedef enum canStatus
{
    canOK,                  // Operation completed successfully.
    canError,               // Unspecified can error: run-time error but no other error message fits.
    canErrorResource,       // Resource not available.
    canReceiveQueueFull,    // Receive queue full, can't put into more messages.
    canTransmitQueueFull,   // transmit queue full, can't put into more messages.
} canStatus_t;

// Received message callback funtion type definiton.
typedef void (*CAN_Callback_t)(uint32_t id, uint32_t size, uint8_t *message);

void CanTransmit(uint32_t id, uint8_t *message, uint32_t msgLen);
void InitCan(void);
canStatus_t CanTransmitMessage(uint32_t messageID, uint32_t messageSize, const uint8_t* payload);
canStatus_t CanRegisterCallback(uint32_t messageID, uint32_t messageMask, CAN_Callback_t callback);
