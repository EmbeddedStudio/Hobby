#include "bsp_systick.h"

#if 0
	static __ININE uint32_t SysTick_Config()
	{
				
				  if (ticks > SysTick_LOAD_RELOAD_Msk)  return (1);         //判断tick的值是否大于2^24
																			   
				  SysTick->LOAD  = (ticks & SysTick_LOAD_RELOAD_Msk) - 1;     //配置reload寄存器的值
				  NVIC_SetPriority (SysTick_IRQn, (1<<__NVIC_PRIO_BITS) - 1); 	//配置中断优先级   配置为15默认为最低优先级
				  SysTick->VAL   = 0;                                          //配置counter 的值为0
				  SysTick->CTRL  = SysTick_CTRL_CLKSOURCE_Msk | 				//配置systick的时钟为72m
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
