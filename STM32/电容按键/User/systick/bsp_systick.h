#ifndef  __BSP_SYSTICK_H
#define __BSP_SYSTICK_H

#include "stm32f10x.h"
#include "core_cm3.h"
void SysTick_Init(void);
void SysTick_Delay_Ms(uint32_t ms);
void TimingDelay_Decrement(void);
#endif

