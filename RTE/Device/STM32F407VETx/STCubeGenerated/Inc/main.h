/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdbool.h>
#include <stdint.h>
#include <cmsis_os2.h>
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define VCU_Pin GPIO_PIN_0
#define VCU_GPIO_Port GPIOB
#define EmergencyFront_Pin GPIO_PIN_1
#define EmergencyFront_GPIO_Port GPIOB
#define EmergencyRear_Pin GPIO_PIN_2
#define EmergencyRear_GPIO_Port GPIOB
#define Motor0_Pin GPIO_PIN_7
#define Motor0_GPIO_Port GPIOE
#define Motor1_Pin GPIO_PIN_8
#define Motor1_GPIO_Port GPIOE
#define Motor2_Pin GPIO_PIN_9
#define Motor2_GPIO_Port GPIOE
#define Motor3_Pin GPIO_PIN_10
#define Motor3_GPIO_Port GPIOE
#define FrontEPS_Pin GPIO_PIN_11
#define FrontEPS_GPIO_Port GPIOE
#define RearEPS_Pin GPIO_PIN_12
#define RearEPS_GPIO_Port GPIOE
#define EBS_Pin GPIO_PIN_13
#define EBS_GPIO_Port GPIOE
#define EPBS_FRONT_Pin GPIO_PIN_14
#define EPBS_FRONT_GPIO_Port GPIOE
#define EPBS_REAR_Pin GPIO_PIN_15
#define EPBS_REAR_GPIO_Port GPIOE
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
