/*
 * interrupts.cpp
 *
 *  Created on: Feb 14, 2025
 *      Author: Sentry
 */

#include "main.h"
#include "leds.h"

extern TIM_HandleTypeDef htim21;
extern TIM_HandleTypeDef htim22;
extern volatile uint32_t wakeUpRequest;
extern volatile uint32_t sleeping;

extern leds ledInterface;

void EXTI4_15_IRQHandler(void)
{
  if (LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_15) != RESET)
  {
    LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_15);
    ledInterface.setShowSoc();
    if(sleeping){
        wakeUpRequest = 1;
    }
  }
}

void TIM21_IRQHandler(void)
{
  HAL_TIM_IRQHandler(&htim21);
  ledInterface.charliePlexing();
}

void TIM22_IRQHandler(void)
{
  HAL_TIM_IRQHandler(&htim22);
  if(sleeping){
      wakeUpRequest = 1;
  }
}
