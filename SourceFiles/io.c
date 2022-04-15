#include "main.h"
#include "io.h"

#define IO_OUTPUT_NUMBER 12
#define IO_INPUT_NUMBER 2
typedef struct
{
    GPIO_TypeDef *Port;
    uint16_t Pin;
} IO_t;

/* -------------------- Static variables ---------------------- */
static osThreadId_t appIoInputThreadId;
// IO output ports map
static IO_t IO_Output[IO_OUTPUT_NUMBER] = {
    {VCU_GPIO_Port, VCU_Pin},
    {VCU_GPIO_Port, Motor0_Pin},
    {Motor0_GPIO_Port, Motor0_Pin},
    {Motor1_GPIO_Port, Motor1_Pin},
    {Motor2_GPIO_Port, Motor2_Pin},
    {Motor3_GPIO_Port, Motor3_Pin},
    {FrontEPS_GPIO_Port, FrontEPS_Pin},
    {RearEPS_GPIO_Port, RearEPS_Pin},
    {EBS_GPIO_Port, EBS_Pin},
    {EPBS_FRONT_GPIO_Port, EPBS_FRONT_Pin},
    {EPBS_REAR_GPIO_Port, EPBS_REAR_Pin},
    {Relay_GPIO_Port,Relay_Pin}};
// IO input ports map
static IO_t IO_Input[IO_INPUT_NUMBER] = {
    {EmergencyFront_GPIO_Port, EmergencyFront_Pin},
    {EmergencyRear_GPIO_Port, EmergencyRear_Pin}};
// IO input event callback function array
static IoCallback_t ioInputCallback[IO_INPUT_NUMBER];
// Read input ports interval
static uint16_t READ_INPUT_INTERVAL = 100; // 100ms

/**
 * @brief Set or reset output IO port
 * @param ioPort IO port number
 * @param level Output status, high or low
 */
void IoControl(uint16_t ioPort, bool level)
{
    if (ioPort >= IO_OUTPUT_NUMBER)
        return;
    HAL_GPIO_WritePin(IO_Output[ioPort].Port, IO_Output[ioPort].Pin, level);
}

/**
 * @brief Thread for monitering the input IO ports
 * @param arg Pointer to the argument which was transfered to
 *  the thread while it was creating.
 * @retval None
 */
void AppIoInput(void *arg)
{
    while (true)
    {
        osDelay(READ_INPUT_INTERVAL);
        for (int i = 0; i < IO_INPUT_NUMBER; ++i)
        {
            if (ioInputCallback[i] != NULL)
                ioInputCallback[i](HAL_GPIO_ReadPin(IO_Input[i].Port, IO_Input[i].Pin));
        }
    }
}

/**
 * @brief Initialize AppIoInput thread.
 * @param None
 * @retval None
 */
void InitAppIoInput(void)
{
    for (int i = 0; i < IO_INPUT_NUMBER; ++i)
        ioInputCallback[i] = NULL;
    appIoInputThreadId = osThreadNew(AppIoInput, NULL, NULL);
//    osThreadSetPriority(appIoInputThreadId, osPriorityBelowNormal);
}

/**
 * @brief Register IO input callback function
 * Provide a method to other thread to register a callback function.
 * Everytime input IO ports are read, corresponding callback will be called,
 * and the corresponding pin state will be passed to the registered function.
 * @param callback Callback function pointer.
 * @param pin The pin the callback function will be attached.
 * @retval None
 */
void AppIoRegisterCallback(IoCallback_t callback, uint16_t pin)
{
    if (pin >= IO_INPUT_NUMBER)
        return;
    if (ioInputCallback[pin] == NULL) ioInputCallback[pin] = callback;
}
