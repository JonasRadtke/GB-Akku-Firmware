/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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
#include "stm32l0xx_hal.h"
#include "stm32l0xx_ll_system.h"
#include "stm32l0xx_ll_gpio.h"
#include "stm32l0xx_ll_exti.h"
#include "stm32l0xx_ll_bus.h"
#include "stm32l0xx_ll_cortex.h"
#include "stm32l0xx_ll_rcc.h"
#include "stm32l0xx_ll_utils.h"
#include "stm32l0xx_ll_pwr.h"
#include "stm32l0xx_ll_dma.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
void delayTickMS(uint32_t x);
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
void EXTI4_15_IRQHandler(void);
void TIM21_IRQHandler(void);
void TIM22_IRQHandler(void);
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define NCHARGE_EN_Pin LL_GPIO_PIN_0
#define NCHARGE_EN_GPIO_Port GPIOA
#define POWER_SEL_Pin LL_GPIO_PIN_2
#define POWER_SEL_GPIO_Port GPIOA
#define BT1_Pin LL_GPIO_PIN_15
#define BT1_GPIO_Port GPIOA
#define BT1_EXTI_IRQn EXTI4_15_IRQn
#define LED3_Pin LL_GPIO_PIN_3
#define LED3_GPIO_Port GPIOB
#define LED2_Pin LL_GPIO_PIN_4
#define LED2_GPIO_Port GPIOB
#define LED1_Pin LL_GPIO_PIN_5
#define LED1_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
