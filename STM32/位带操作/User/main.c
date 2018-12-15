#include "stm32f10x.h"   
#include "bsp_led.h"

void delay(uint32_t count)
{
	for (;count!=0;count--);
}
int main(void)
{
	LED_GPIO_Config();
	while (1)
	{
		BITBAND(0)=0;
		delay(0xfffff);
		BITBAND(0)=1;
		delay(0xfffff);
		BITBAND(1)=0;
		delay(0xfffff);
		BITBAND(1)=1;
		delay(0xfffff);
		BITBAND(5)=0;
		delay(0xfffff);
		BITBAND(5)=1;
		delay(0xfffff);
		BITBAND(0)=0;
		BITBAND(5)=0;
		delay(0xfffff);
		BITBAND(0)=1;
		BITBAND(5)=1;
		delay(0xfffff);
	}
	
}

