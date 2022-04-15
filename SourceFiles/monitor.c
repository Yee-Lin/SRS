#include "main.h"
#include "monitor.h"
#include "rl_net.h" // Keil.MDK-Plus::Network:CORE

/* --------------- Static variables ---------------- */
static osMessageQueueId_t messageQueueId;
static osThreadId_t threadId;

/* --------------- Static functions ---------------- */
void ThreadMonitor(void*);


/* --------------- Global variables ---------------- */
osEventFlagsId_t motor0Event;
osEventFlagsId_t motor1Event;
osEventFlagsId_t motor2Event;
osEventFlagsId_t motor3Event;
osEventFlagsId_t frontEPSEvent;
osEventFlagsId_t rearEPSEvent;

void InitMonitor(void)
{
	messageQueueId = osMessageQueueNew(16, 16, NULL);
	threadId = osThreadNew(ThreadMonitor, NULL, NULL);
}

void ThreadMonitor(void* arg)
{
	// Initialize network interface
	netStatus status = netInitialize();
	uint8_t a[16];
	
	for (;;)
	{
		osStatus_t status = osMessageQueueGet(messageQueueId, a, NULL, osWaitForever);
		if (osOK != status) continue;
	}
}
