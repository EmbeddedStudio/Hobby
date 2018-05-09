#include "stm32f10x.h"   
#include "bsp_led.h"
#include "bsp_basic_tim.h"
#include "bsp_usart.h"
#include "bsp_key.h"

uint16_t time=0;

int main(void)
{
	static uint8_t flag=0;
	
	uint8_t P=0;
	
	LED_GPIO_Config();
	
	USART_Config();
	
	TIM_Init();
	
	KEY_GPIO_Config();
	
	printf("≥Ã–Ú≤‚ ‘");
	
	while (1)
	{
		
		if (Key_Scan(KEY1_GPIO_PORT,KEY1_GPIO_PIN)==KEY_ON  )
		{
			flag =~flag;
			P++;
			printf("P=%d ",P);
		}
		
		if(flag==0)
		{
			if (time==1000)
			{
				time=0;
				LED_BLUE;
			}
			else if (time==500)
			{
				LED_OFF;
			}
		}
		
		
		else
		{
			if (time==2000)
			{
				time=0;
				LED_BLUE;
			}
			else if (time==1000)
			{
				LED_OFF;
			}
		}
	}
	
}




