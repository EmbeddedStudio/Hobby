#ifndef __BSP_MOTOR_PWM_H
#define __BSP_MOTOR_PWM_H

#include "stm32f10x.h"

/* ����1��ʾ��ǰ,0��ʾ��� */
#define M1_Forward	 	GPIOB->BSRR = GPIO_Pin_13       //BSRR��λ�Ĵ���
#define M1_Backward	 	GPIOB->BRR  = GPIO_Pin_13       //BRR��λ�����㣩�Ĵ���

/* ����1��ʾ��ǰ,0��ʾ��� */
#define M2_Forward	 	GPIOB->BSRR = GPIO_Pin_15 
#define M2_Backward	 	GPIOB->BRR  = GPIO_Pin_15

/* ����1��ʾ��ǰ,0��ʾ��� */
#define M3_Forward	 	GPIOB->BSRR = GPIO_Pin_3
#define M3_Backward	 	GPIOB->BRR  = GPIO_Pin_3

/* ����1��ʾ��ǰ,0��ʾ��� */
#define M4_Forward	 	GPIOB->BSRR = GPIO_Pin_5
#define M4_Backward	 	GPIOB->BRR  = GPIO_Pin_5



/* ���1��ͨ��2 */
#define M1_STOP         GPIOB->BSRR = GPIO_Pin_12
#define M1_RELEASE      GPIOB->BRR  = GPIO_Pin_12

/* ���2��ͨ��3 */
#define M2_STOP         GPIOB->BSRR = GPIO_Pin_14
#define M2_RELEASE      GPIOB->BRR  = GPIO_Pin_14

/* ���3 */
#define M3_STOP         GPIOB->BSRR = GPIO_Pin_4
#define M3_RELEASE      GPIOB->BRR  = GPIO_Pin_4

/* ���4 */
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

