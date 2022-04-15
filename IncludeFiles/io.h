#pragma once
#include <stdint.h>
#include "stdbool.h"
// enum IO_OUT_PORT
// {

// };

enum IO_IN_PORT
{
    IO_PIN_FRONT_EMERGENCY = 0,
    IO_PIN_REAR_EMERGENCY
};

// IO input callback function type definition
typedef void (*IoCallback_t)(bool pinState);

void IoControl(uint16_t ioPort, bool level);
void InitAppIoInput(void);
void AppIoRegisterCallback(IoCallback_t callback, uint16_t pin);
