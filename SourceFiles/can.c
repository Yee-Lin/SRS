/**
  ******************************************************************************
  * @file           : can.c
  * @brief          : CAN functions and thread
  ******************************************************************************
  * 
  *
  ******************************************************************************
  */
#include "cmsis_os2.h" // ::CMSIS:RTOS2
#include <main.h>
#include <string.h>
#include <stdbool.h>
#include "can.h"

#define RECEIVE_QUEUE_LEN	32
#define TRANSMIT_QUEUE_LEN	32

// ----------- CAN handle ----------------------------
extern CAN_HandleTypeDef hcan1;

/* --------------- static variables ----------------- */
static osThreadId_t threadIdCanReceive;
static osThreadId_t threadIdCanTransmit;
static osMutexId_t mutexRegister;
#define CAN_FILTER_NUMBER	28
static CAN_Callback_t callbacks[CAN_FILTER_NUMBER];
static uint32_t callbacksIndex;

// ----------- Message queue ------------------------
static osMessageQueueId_t queueIdCanReceive;
static osMessageQueueId_t queueIdCanTransmit;

// Message struct used to transmit and receive in message queue.
typedef struct
{
	uint32_t messageID;
	uint32_t messageSize;
	uint8_t payload[CAN_MSG_LEN];
} CAN_Message_t;

typedef struct
{
	CAN_RxHeaderTypeDef rxHead;
	uint8_t payload[CAN_MSG_LEN];
} CAN_ReceivedMessage_t;


/* ----------------- static functions ----------------*/
static HAL_StatusTypeDef CanConfigAndStart(void);
static void app_can_send(void* arg);
static void app_can(void const* arg);
static void CanReceiveThread(void* arg);
static void CanTransmitThread(void* arg);

/**
  * @brief  Rx FIFO_0 Pending callback function.
  *         Rx FIFO_0 Pending callback function, get a can message at canRxMessage 
  *         and the can head at rxMsgHead. Set the os event flags to notify the
  *         thread app_can.
  * @param  hcan CAN_HandleTypeDef*
  * @retval None
  */
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
	if (hcan->Instance == CAN1)
	{
		CAN_ReceivedMessage_t canMessage;
		if (HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &canMessage.rxHead, canMessage.payload) == HAL_OK)
		{
			canMessage.rxHead.FilterMatchIndex <<= 1;	// Match index is indepent for each FIFO
			osMessageQueuePut(queueIdCanReceive, &canMessage, NULL, 0);
		}
		else 
		{
			hcan->State = HAL_CAN_STATE_READY;
			HAL_CAN_ResetError(hcan);
		}
	}
}

/**
  * @brief  Rx FIFO_1 Pending callback function.
  *         Rx FIFO_1 Pending callback function, get a can message at canRxMessage 
  *         and the can head at rxMsgHead. Set the os event flags to notify the
  *         thread app_can.
  * @param  hcan CAN_HandleTypeDef*
  * @retval None
  */
void HAL_CAN_RxFifo1MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
	if (hcan->Instance == CAN1)
	{
		CAN_ReceivedMessage_t canMessage;
		if (HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO1, &canMessage.rxHead, canMessage.payload) == HAL_OK)
		{
			canMessage.rxHead.FilterMatchIndex <<= 1;	// Match index is indepent for each FIFO
			++canMessage.rxHead.FilterMatchIndex;
			osMessageQueuePut(queueIdCanReceive, &canMessage, NULL, 0);
		}
		else 
		{
			hcan->State = HAL_CAN_STATE_READY;
			HAL_CAN_ResetError(hcan);
		}
	}
}

void InitCan(void)
{
	mutexRegister = osMutexNew(NULL);
	for(int i = 0; i < CAN_FILTER_NUMBER; ++i) callbacks[i] = NULL;
	HAL_StatusTypeDef status = HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING);
	status = HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO1_MSG_PENDING);
	status = HAL_CAN_Start(&hcan1);
	queueIdCanReceive = osMessageQueueNew(RECEIVE_QUEUE_LEN, sizeof(CAN_ReceivedMessage_t), NULL);
	queueIdCanTransmit = osMessageQueueNew(TRANSMIT_QUEUE_LEN, sizeof(CAN_Message_t), NULL);
	threadIdCanReceive = osThreadNew((osThreadFunc_t)CanReceiveThread, NULL, NULL);
	threadIdCanTransmit = osThreadNew((osThreadFunc_t)CanTransmitThread, NULL, NULL);
}

void CanReceiveThread(void* arg)
{
	CAN_ReceivedMessage_t message;
	for (;;)
	{
		osStatus_t status = osMessageQueueGet(queueIdCanReceive, &message, NULL, osWaitForever);
		if(osOK != status) continue;
		uint32_t index = message.rxHead.FilterMatchIndex;
		if(index >= CAN_FILTER_NUMBER) continue;
		if(callbacks[index] == NULL) continue;
		callbacks[index](message.rxHead.StdId, message.rxHead.DLC, message.payload); 
	}
}

void CanTransmitThread(void* arg)
{
	CAN_Message_t message;
	CAN_TxHeaderTypeDef txMsgHead;
	for(;;)
	{
		osStatus_t status = osMessageQueueGet(queueIdCanTransmit, &message, NULL, osWaitForever);
		if(osOK != status) continue;
		txMsgHead.IDE = CAN_ID_STD;
		txMsgHead.RTR = CAN_RTR_DATA;
		txMsgHead.TransmitGlobalTime = DISABLE;
		txMsgHead.DLC = message.messageSize;
		txMsgHead.StdId = message.messageID;
		HAL_CAN_StateTypeDef canState = HAL_CAN_GetState(&hcan1);
		if (HAL_CAN_STATE_READY != canState && HAL_CAN_STATE_LISTENING != canState) continue;
		while (true)
		{
			uint32_t txMailBox;
			HAL_StatusTypeDef result = HAL_CAN_AddTxMessage(&hcan1, &txMsgHead, message.payload, &txMailBox);
			if (HAL_OK == result) break;
			else osDelay(2);
		}
	}
}

canStatus_t CanTransmitMessage(uint32_t messageID, uint32_t messageSize, const uint8_t* payload)
{
	CAN_Message_t message = {.messageID = messageID, .messageSize = messageSize};
	memcpy(message.payload, payload, CAN_MSG_LEN);
	osStatus_t status = osMessageQueuePut(queueIdCanTransmit, &message, NULL, 0);
	if(osOK == status) return canOK;
	else if(osErrorResource == status) return canTransmitQueueFull;
	else return canError;
}

canStatus_t CanRegisterCallback(uint32_t messageID, uint32_t messageMask, CAN_Callback_t callback)
{
	osMutexAcquire(mutexRegister, osWaitForever);
	if (CAN_FILTER_NUMBER == callbacksIndex || callbacks[callbacksIndex] != NULL)
	{
		osMutexRelease(mutexRegister);
		return canErrorResource;
	}
	callbacks[callbacksIndex] = callback;
	CAN_FilterTypeDef sFilterConfig;
	sFilterConfig.FilterBank = callbacksIndex;
	sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
	sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
	sFilterConfig.FilterIdHigh = messageID << 5;
	sFilterConfig.FilterIdLow = CAN_ID_STD | CAN_RTR_DATA;
	sFilterConfig.FilterMaskIdHigh = messageMask << 5;
	sFilterConfig.FilterMaskIdLow = 0xFFFF;
	sFilterConfig.FilterActivation = ENABLE;
	sFilterConfig.SlaveStartFilterBank = 0;
	if(callbacksIndex & 0x01) sFilterConfig.FilterFIFOAssignment = CAN_RX_FIFO1;
	else sFilterConfig.FilterFIFOAssignment = CAN_RX_FIFO0;
	++callbacksIndex;

	HAL_StatusTypeDef status = HAL_CAN_ConfigFilter(&hcan1, &sFilterConfig);
	osMutexRelease(mutexRegister);
	if(HAL_OK == status) return canOK;
	else return canError;
}

