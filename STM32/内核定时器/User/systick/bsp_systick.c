#include "bsp_systick.h"

#if 0
	static __ININE uint32_t SysTick_Config()
	{
				
				  if (ticks > SysTick_LOAD_RELOAD_Msk)  return (1);         //�ж�tick��ֵ�Ƿ����2^24
																			   
				  SysTick->LOAD  = (ticks & SysTick_LOAD_RELOAD_Msk) - 1;     //����reload�Ĵ�����ֵ
				  NVIC_SetPriority (SysTick_IRQn, (1<<__NVIC_PRIO_BITS) - 1); 	//�����ж����ȼ�   ����Ϊ15Ĭ��Ϊ������ȼ�
				  SysTick->VAL   = 0;                                          //����counter ��ֵΪ0
				  SysTick->CTRL  = SysTick_CTRL_CLKSOURCE_Msk | 				//����systick��ʱ��Ϊ72m
										SysTick_CTRL_TICKINT_Msk   | 
										SysTick_CTRL_ENABLE_Msk;                    /* Enable SysTick IRQ and SysTick Timer */
				  return (0);                                                 			 /* Function successful */

	}
#endif

void SysTick_Delay_ms(uint32_t ms)
{
	uint32_t i ;
	SysTick_Config(72000);
	for (i=ms;i>0;i--)
	{
		while ( !(SysTick->CTRL&(1<<16)) );
	}
	 SysTick->CTRL &=~SysTick_CTRL_ENABLE_Msk;
}
