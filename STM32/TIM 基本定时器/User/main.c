#include "stm32f10x.h"   
#include "bsp_led.h"
#include "bsp_basic_tim.h"

uint16_t time=0;

int main(void)
{
	LED_GPIO_Config();
	
	TIM_Init();
	while (1)
	{
		if (time==1000)
		{
			LED_RED_TOGGLE;
		}
		
	}
	
}

