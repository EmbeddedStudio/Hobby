#include "stm32f10x.h"   
#include "bsp_led.h"
#include "bsp_usart.h"
#include "bsp_tpad.h"

int main(void)
{	

	TIM_TPAD_Init();
	LED_GPIO_Config ();
	USART_Config ();
	printf ("µÁ»›∞¥º¸≤‚ ‘≥Ã–Ú\n");
	while ( TPAD_Init() )		
	{
		while (1) 
		{
			 if ( TPAD_Scan() == TPAD_ON )
			 {
				LED_RED;
				SysTick_Delay_Ms(1000);
				 LED_OFF;
			 }
		}
	}
}









