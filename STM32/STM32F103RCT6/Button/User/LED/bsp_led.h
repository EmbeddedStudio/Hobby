#ifndef __BSP_LED_H
#define __BSP_LED_H

#include "stm32f10x.h"

#define LED_G_GPIO_PIN        GPIO_Pin_0	/*指定三原色的输入输出引脚*/
#define LED_B_GPIO_PIN        GPIO_Pin_1
#define LED_R_GPIO_PIN        GPIO_Pin_5
#define LED_G_GPIO_PORT       GPIOB 
#define LED_R_GPIO_PORT       GPIOB 
#define LED_B_GPIO_PORT       GPIOB 
#define LED_G_GPIO_CLK        RCC_APB2Periph_GPIOB  //对时钟进行宏替换

#define LED_G_TOGGLE     {LED_G_GPIO_PORT->ODR^=GPIO_Pin_0;}
#define LED_R_TOGGLE     {LED_R_GPIO_PORT->ODR^=GPIO_Pin_5;}

#define   ON      1
#define   OFF     0

#define  LED_R(a)   if(a)   \
	                         GPIO_ResetBits(LED_R_GPIO_PORT, LED_R_GPIO_PIN);\
                     else    GPIO_SetBits(LED_R_GPIO_PORT, LED_R_GPIO_PIN);
#define  LED_G(a)   if(a)   \
							GPIO_ResetBits(LED_G_GPIO_PORT, LED_G_GPIO_PIN);\
                    else    GPIO_SetBits(LED_G_GPIO_PORT, LED_G_GPIO_PIN);
#define  LED_B(a)   if(a)   \
	                        GPIO_ResetBits(LED_B_GPIO_PORT, LED_B_GPIO_PIN);\
                    else    GPIO_SetBits(LED_B_GPIO_PORT, LED_B_GPIO_PIN);
					

void LED_GPIO_Config (void);

#endif
