#include "stm32f10x.h"   
#include "bsp_led.h"
#include "bsp_usart.h"


int main(void)
{	
//	char ch;
	LED_GPIO_Config ();
	USART_Config ();
	printf ("≤‚ ‘≥Ã–Ú\n");
	while (1);	
	
}

