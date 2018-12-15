#include "stm32f10x.h"
#include "bsp_led.h"

void delay(uint32_t count)
{
	for (;count!=0;count--);
}

int main (void)
{
	LED_GPIO_Config();
	while(1)
	{	
		GPIO_SetBits(LED_GPIO_PORT, LED_GPIO_PIN);
		delay(0xfffff);
		GPIO_ResetBits(LED_GPIO_PORT, LED_GPIO_PIN);  
		delay(0xfffff);
	}
}






