#include "stm32f10x.h"   
#include "bsp_led.h"
#include "bsp_systick.h"

int main(void)
{
	LED_GPIO_Config();

	while (1)
	{
		LED_R(ON) ;
		SysTick_Delay_ms(500);
		LED_R(OFF) ;
		SysTick_Delay_ms(500);
	}
		
}


