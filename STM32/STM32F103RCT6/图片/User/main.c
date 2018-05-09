#include "stm32f10x.h"   
#include "bsp_led.h"
#include "bsp_exti.h"
#include "bsp_usart.h"

extern uint8_t flag;



int main(void)
{
	LED_GPIO_Config();
	EXTI_Config ();
	USART_Config();
	while (1);
	
	
}
