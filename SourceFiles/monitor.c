#include "main.h"
#include "monitor.h"
#include "rl_net.h" // Keil.MDK-Plus::Network:CORE
#include "battery.h"
#include "vcu.h"
#include "moduleControl.h"
#include "canMessage.h"
#include "brake.h"
#include "errorHandle.h"

#define LowBattery 480  //48V
#define TIMER_PERIOD 100  //100ms
/* --------------- Static variables ---------------- */
static osMessageQueueId_t messageQueueId;
static osThreadId_t threadId;
static osTimerId_t timerId;

BMU_MESSAGE_T BMU_Msg;

/* --------------- Static functions ---------------- */
void ThreadMonitor(void*);
static void TimerCallBack(void);

/* --------------- Global variables ---------------- */


void InitMonitor(void)
{
	messageQueueId = osMessageQueueNew(16, 16, NULL);
	threadId = osThreadNew(ThreadMonitor, NULL, NULL);
	timerId = osTimerNew(TimerCallBack,osTimerPeriodic,NULL,NULL);
//	osTimerStart(timerId,TIMER_PERIOD);
}

void ThreadMonitor(void* arg)
{
	// Initialize network interface
	netStatus status = netInitialize();
	
	for (;;)
	{
		osDelay(100);
	}
}

void TimerCallBack(void){
	static uint8_t time100ms; 
	if(CheckHeartBeat()){
		time100ms = 0;
	}
	else{
		time100ms++;
		if(time100ms > 5){
			Module_ShutDownAll();
			Braking();
		}
	}
}

void xxxInit(void)
{
	Module_ShutDownAll();
	BMU_Msg = GetDataBMUMsg();
	while (BMU_Msg.Group_Voltage < LowBattery);
		SetFaultStatus(Error100);
	SRS_EnableVCU();
	SRS_EnableEPS();
	SRS_EnableEBS();
	osDelay(200);
	while (GetHeartBeatStatus() != 0x2f00ff){
		SetFaultStatus(Warning100);
	}
	SRS_EnableMotorDrive();
	osDelay(200);
	while (GetHeartBeatStatus() != SUCCESS_HEARTBEAT_MAP)
	{
		if(Get_If_BrakeStatus()  == false)
			Braking();
	}
}
