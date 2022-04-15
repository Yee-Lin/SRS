#include "main.h"
#include "moduleControl.h"
#define MotorNUM 4


void SRS_EnableVCU(void)
{
    HAL_GPIO_WritePin(VCU_GPIO_Port,VCU_Pin,GPIO_PIN_SET);
}

void SRS_DisableVCU(void)
{
    HAL_GPIO_WritePin(VCU_GPIO_Port,VCU_Pin,GPIO_PIN_RESET);
}

void SRS_EnableMotorDrive(void)
{
    HAL_GPIO_WritePin(Motor0_GPIO_Port,Motor0_Pin,GPIO_PIN_SET);
    HAL_GPIO_WritePin(Motor1_GPIO_Port,Motor1_Pin,GPIO_PIN_SET);
    HAL_GPIO_WritePin(Motor2_GPIO_Port,Motor2_Pin,GPIO_PIN_SET);
    HAL_GPIO_WritePin(Motor3_GPIO_Port,Motor3_Pin,GPIO_PIN_SET);
}

void SRS_DisableMotorDrive(void)
{
    HAL_GPIO_WritePin(Motor0_GPIO_Port,Motor0_Pin,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(Motor1_GPIO_Port,Motor1_Pin,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(Motor2_GPIO_Port,Motor2_Pin,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(Motor3_GPIO_Port,Motor3_Pin,GPIO_PIN_RESET);
}

void SRS_EnableEPS(void)
{
    HAL_GPIO_WritePin(FrontEPS_GPIO_Port,FrontEPS_Pin,GPIO_PIN_SET);
    HAL_GPIO_WritePin(RearEPS_GPIO_Port,RearEPS_Pin,GPIO_PIN_SET);
}

void SRS_DisableEPS(void)
{
    HAL_GPIO_WritePin(FrontEPS_GPIO_Port,FrontEPS_Pin,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(RearEPS_GPIO_Port,RearEPS_Pin,GPIO_PIN_RESET);
}

void SRS_EnableEBS(void)
{
    HAL_GPIO_WritePin(EBS_GPIO_Port,EBS_Pin,GPIO_PIN_SET);
}

void SRS_DisableEBS(void)
{
    HAL_GPIO_WritePin(EBS_GPIO_Port,EBS_Pin,GPIO_PIN_RESET);
}

void SRS_EnableCANRelay(void)
{
    HAL_GPIO_WritePin(Relay_GPIO_Port,Relay_Pin,GPIO_PIN_SET);
}

void SRS_DisableCANRelay(void)
{
    HAL_GPIO_WritePin(Relay_GPIO_Port,Relay_Pin,GPIO_PIN_RESET);
}

void Module_InitAll(void)
{
    SRS_DisableVCU();
    SRS_DisableMotorDrive();
    SRS_DisableEPS();
    SRS_DisableEBS();
    SRS_DisableCANRelay();
}

void Module_ShutDownAll(void)
{
    SRS_DisableVCU();
    SRS_DisableMotorDrive();
    SRS_DisableEPS();
    SRS_DisableEBS();
    SRS_DisableCANRelay();
}

void Module_StarPowerAll(void)
{
    SRS_EnableVCU();
    SRS_EnableMotorDrive();
    SRS_EnableEPS();
    SRS_EnableEBS();
    SRS_EnableCANRelay();
}