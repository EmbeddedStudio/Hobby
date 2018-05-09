#ifndef __BSP_TPAD_H
#define __BSP_TPAD_H

#include "stm32f10x.h"

#define   TPAD_TIM 			TIM5
#define   TPAD_TIM_APBxClock_FUN 	RCC_APB1PeriphClockCmd
#define   TPAD_TIM_CLK 			RCC_APB1Periph_TIM5
#define   TPAD_TIM_Period		0XFFFF
#define   TPAD_TIM_Prescaler 		(72-1)

// TIM ���벶��ͨ�� GPIO ��غ궨��
#define   TPAD_TIM_CH_GPIO_CLK		RCC_APB2Periph_GPIOA
#define   TPAD_TIM_CH_PORT 		GPIOA
#define   TPAD_TIM_CH_PIN 		GPIO_Pin_1
#define   TPAD_TIM_CHANNEL_x 		TIM_Channel_2

// �ж���غ궨��
#define   TPAD_TIM_IT_CCx 		TIM_IT_CC2
#define   TPAD_TIM_IRQ 			TIM5_IRQn
#define   TPAD_TIM_INT_FUN 		TIM5_IRQHandler

// ��ȡ����Ĵ���ֵ�����궨��
#define   TPAD_TIM_GetCapturex_FUN 		TIM_GetCapture2
//�����źż��Ժ����궨��
#define   TPAD_TIM_OCxPolarityConfig_FUN 	TIM_OC2PolarityConfig


// �ж���غ궨��
#define            TPAD_TIM_IT_CCx            TIM_IT_CC2
#define            TPAD_TIM_IRQ               TIM5_IRQn
#define            TPAD_TIM_INT_FUN           TIM5_IRQHandler
// ���ݰ��������µ�ʱ������ֵ����Ҫ���ݲ�ͬ��Ӳ��ʵ�ʲ��ԣ�
// ��С�������ֵ���������Ӧ�ٶ�
#define   TPAD_GATE_VAL 		70

// ���ݰ������ص�ʱ���������С�ĳ��ʱ�䣬��ͬ��Ӳ����һ���� ָ�����ȶ��� 76
#define   TPAD_DEFAULT_VAL_MIN 		70
#define   TPAD_DEFAULT_VAL_MAX		80

#define   TPAD_ON 			1
#define   TPAD_OFF			0

/********************��������*********************/
void TPAD_Reset(void);
uint8_t TPAD_Init(void);
uint16_t TPAD_Get_Val(void);
uint16_t TPAD_Get_MaxVal( uint8_t num );
uint8_t TPAD_Scan(void);
void TIM_TPAD_Init(void);
void SysTick_Delay_Ms( __IO uint32_t ms);
#endif   /*__BSP_TPAD_H*/
