#include "emergencyButton.h"
#include "io.h"
#include "stdbool.h"
/* -------------- Static functions ------------------ */

/* -------------- Static variables ------------------ */
// System status
static bool remoteEmergencyStop = false;
static bool frontEmergencyStop = false;
static bool rearEmergencyStop = false;

bool GetFrontEmergencyStatus(void)
{
    return frontEmergencyStop;
}

bool GetRearEmergencyStatus(void)
{
    return rearEmergencyStop;
}

bool GetRemoteEmergencyStatus(void)
{
    return remoteEmergencyStop;
}

bool GetEmergencyStatus(void)
{
	return (remoteEmergencyStop || frontEmergencyStop || rearEmergencyStop);
}

void UpdateRemoteEmergency(bool status)
{
	remoteEmergencyStop = status;
}

void SetFrontEmergencyStatus(bool status)
{
    frontEmergencyStop = status;
}

void SetRearEmergencyStatus(bool status)
{
    rearEmergencyStop = status;
}

/**
 * @brief Front emergency button status update callback function
 * @param pinState 0 - Low 1 - High
 * @retval None
 */
void UpdateFrontEmergencyStatus(bool pinState)
{
    frontEmergencyStop = pinState;
}

/**
 * @brief Rear emergency button status update callback function
 * @param pinState 0 - Low 1 - High
 * @retval None
 */
void UpdateRearEmergencyStatus(bool pinState)
{
    rearEmergencyStop = pinState;
}

/**
 * @brief Initialize emergencies
 * Register callback function for emergency IO input ports.
 * @param callback Pointer to callback function.
 * @retval None
 */
void InitEmergency(void)
{
    AppIoRegisterCallback(UpdateFrontEmergencyStatus, IO_PIN_FRONT_EMERGENCY);
    AppIoRegisterCallback(UpdateRearEmergencyStatus, IO_PIN_REAR_EMERGENCY);
} 