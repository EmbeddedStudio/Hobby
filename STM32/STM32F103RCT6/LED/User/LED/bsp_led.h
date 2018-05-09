#ifndef __BSP_LED_H
#define __BSP_LED_H

#include "stm32f10x.h"

#define LED_GPIO_PIN        GPIO_Pin_2	
#define LED_GPIO_PORT       GPIOA 
#define LED_GPIO_CLK        RCC_APB2Periph_GPIOA  

#define   ON     1
#define   OFF    0

//#define  LED(a)   if(a)   \
//				GPIO_SetBits(LED_GPIO_PORT, LED_GPIO_PIN);\
//                    else GPIO_ResetBits(LED_GPIO_PORT, LED_GPIO_PIN);    //低电平


void LED_GPIO_Config (void);

#endif
