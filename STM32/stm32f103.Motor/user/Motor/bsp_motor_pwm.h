#ifndef __BSP_MOTOR_PWM_H
#define __BSP_MOTOR_PWM_H

#include "stm32f10x.h"

/* 方向1表示向前,0表示向后 */
#define M1_Forward	 	GPIOB->BSRR = GPIO_Pin_13       //BSRR置位寄存器
#define M1_Backward	 	GPIOB->BRR  = GPIO_Pin_13       //BRR复位（清零）寄存器

/* 方向1表示向前,0表示向后 */
#define M2_Forward	 	GPIOB->BSRR = GPIO_Pin_15 
#define M2_Backward	 	GPIOB->BRR  = GPIO_Pin_15

/* 方向1表示向前,0表示向后 */
#define M3_Forward	 	GPIOB->BSRR = GPIO_Pin_3
#define M3_Backward	 	GPIOB->BRR  = GPIO_Pin_3

/* 方向1表示向前,0表示向后 */
#define M4_Forward	 	GPIOB->BSRR = GPIO_Pin_5
#define M4_Backward	 	GPIOB->BRR  = GPIO_Pin_5



/* 电机1用通道2 */
#define M1_STOP         GPIOB->BSRR = GPIO_Pin_12
#define M1_RELEASE      GPIOB->BRR  = GPIO_Pin_12

/* 电机2用通道3 */
#define M2_STOP         GPIOB->BSRR = GPIO_Pin_14
#define M2_RELEASE      GPIOB->BRR  = GPIO_Pin_14

/* 电机3 */
#define M3_STOP         GPIOB->BSRR = GPIO_Pin_4
#define M3_RELEASE      GPIOB->BRR  = GPIO_Pin_4

/* 电机4 */
#define M4_STOP         GPIOB->BSRR = GPIO_Pin_6
#define M4_RELEASE      GPIOB->BRR  = GPIO_Pin_6

void PWM_Init(void) ;

void PWM_M1_Forward(uint16_t val);
void PWM_M1_Backward(uint16_t val);

void PWM_M2_Forward(uint16_t val);
void PWM_M2_Backward(uint16_t val);

void PWM_M3_Forward(uint16_t val);
void PWM_M3_Backward(uint16_t val);

void PWM_M4_Forward(uint16_t val);
void PWM_M4_Backward(uint16_t val);

#endif /*__BSP_MOTOR_PWM_H*/

