/**
  ******************************************************************************
  * @file           : app_main.c
  * @brief          : Main thread, handle commands
  ******************************************************************************
  * Main thread which handle commands and messages from remote controller and
  * central computer. Calulate detail datas for hub moters.
  * 
  ******************************************************************************
  */
#include "rl_net.h" // Keil.MDK-Plus::Network:CORE
#include "main.h"
#include "string.h"
#include "can.h"
#include "app_main.h"
#include "battery.h"
#include "cmsis_os2.h" // ::CMSIS:RTOS2


/* --------------- Static functions ---------------- */

/* --------------- Extern functions ----------------- */

/* --------------- Static variables ---------------- */
static const uint32_t UPDATE_FLAG = 0x55555555U;

static osMessageQueueId_t appMainMsgQueueId;
static osThreadId_t threadId;

// Periodic timer with a period of 100ms
static osTimerId_t periodicTimer;

// Network parameters

uint8_t testMsg[8]={0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa,0xaa};
uint8_t time1;
/**
 * @brief Main thread, handle commands from remote controller and upper computer
 * @param arg Pointer to an incoming parameter when creating the thread.
 * @return none
 */
void app_main(void *arg)
{
		
//	osThreadId_t osThIdCan1 = osThreadNew(app_can1, NULL, NULL);
//	osThreadId_t osThIdCan2 = osThreadNew(app_can2, NULL, NULL);
//	osThreadId_t osThIdCan1Send = osThreadNew(app_can1_send, NULL, NULL);
//	osThreadId_t osThIdCan2Send = osThreadNew(app_can2_send, NULL, NULL);
//	InitMonitor();
	while (true)
	{
//		CanTransmit(0x88, testMsg, 8);
		time1++;
		osDelay(100);
	}
}



/**
 * @brief Initalize app_main
 * Create thrade and set its priority.
 */
void InitAppMain(void)
{
	threadId = osThreadNew(app_main, NULL, NULL);
	osThreadSetPriority(threadId, osPriorityNormal1);
}


