
/*
 * Auto generated Run-Time-Environment Configuration File
 *      *** Do not modify ! ***
 *
 * Project: 'SRS' 
 * Target:  'Target STM32F407VET6' 
 */

#ifndef RTE_COMPONENTS_H
#define RTE_COMPONENTS_H


/*
 * Define the Device Header File: 
 */
#define CMSIS_device_header "stm32f4xx.h"

/* ARM::CMSIS:RTOS2:Keil RTX5:Library:5.5.3 */
#define RTE_CMSIS_RTOS2                 /* CMSIS-RTOS2 */
        #define RTE_CMSIS_RTOS2_RTX5            /* CMSIS-RTOS2 Keil RTX5 */
/* Keil.ARM Compiler::Compiler:Event Recorder:DAP:1.5.1 */
#define RTE_Compiler_EventRecorder
          #define RTE_Compiler_EventRecorder_DAP
/* Keil.ARM Compiler::Compiler:I/O:File:File System:1.2.0 */
#define RTE_Compiler_IO_File            /* Compiler I/O: File */
          #define RTE_Compiler_IO_File_FS         /* Compiler I/O: File (File System) */
/* Keil.MDK-Plus::File System:CORE:LFN Debug:6.14.4 */
#define RTE_FileSystem_Core             /* File System Core */
          #define RTE_FileSystem_LFN              /* File System with Long Filename support */
          #define RTE_FileSystem_Debug            /* File System Debug Version */
/* Keil.MDK-Plus::File System:Drive:Memory Card:6.14.4 */
#define RTE_FileSystem_Drive_MC_0       /* File System Memory Card Drive 0 */

/* Keil.MDK-Plus::Network:CORE:IPv4 Release:7.16.0 */
#define RTE_Network_Core                /* Network Core */
          #define RTE_Network_IPv4                /* Network IPv4 Stack */
          #define RTE_Network_Release             /* Network Release Version */
/* Keil.MDK-Plus::Network:Interface:ETH:7.16.0 */
#define RTE_Network_Interface_ETH_0     /* Network Interface ETH 0 */

/* Keil.MDK-Plus::Network:Socket:TCP:7.16.0 */
#define RTE_Network_Socket_TCP          /* Network Socket TCP */
/* Keil.MDK-Plus::Network:Socket:UDP:7.16.0 */
#define RTE_Network_Socket_UDP          /* Network Socket UDP */
/* Keil::CMSIS Driver:Ethernet MAC:2.9 */
#define RTE_Drivers_ETH_MAC0            /* Driver ETH_MAC0 */
/* Keil::CMSIS Driver:Ethernet PHY:DP83848C:6.2.0 */
#define RTE_Drivers_PHY_DP83848C        /* Driver PHY DP83848C */
/* Keil::CMSIS Driver:MCI:2.10 */
#define RTE_Drivers_MCI0                /* Driver MCI0 */
/* Keil::Device:STM32Cube Framework:STM32CubeMX:1.1.0 */
#define RTE_DEVICE_FRAMEWORK_CUBE_MX
/* Keil::Device:STM32Cube HAL:Common:1.7.13 */
#define RTE_DEVICE_HAL_COMMON
/* Keil::Device:STM32Cube HAL:Cortex:1.7.13 */
#define RTE_DEVICE_HAL_CORTEX
/* Keil::Device:STM32Cube HAL:DMA:1.7.13 */
#define RTE_DEVICE_HAL_DMA
/* Keil::Device:STM32Cube HAL:ETH:1.7.13 */
#define RTE_DEVICE_HAL_ETH
/* Keil::Device:STM32Cube HAL:GPIO:1.7.13 */
#define RTE_DEVICE_HAL_GPIO
/* Keil::Device:STM32Cube HAL:PWR:1.7.13 */
#define RTE_DEVICE_HAL_PWR
/* Keil::Device:STM32Cube HAL:RCC:1.7.13 */
#define RTE_DEVICE_HAL_RCC
/* Keil::Device:STM32Cube HAL:SD:1.7.13 */
#define RTE_DEVICE_HAL_SD
/* Keil::Device:STM32Cube HAL:TIM:1.7.13 */
#define RTE_DEVICE_HAL_TIM
/* Keil::Device:Startup:2.6.3 */
#define RTE_DEVICE_STARTUP_STM32F4XX    /* Device Startup for STM32F4 */


#endif /* RTE_COMPONENTS_H */
