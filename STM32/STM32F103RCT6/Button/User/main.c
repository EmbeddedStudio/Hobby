#include "stm32f10x.h"   
#include "bsp_led.h"
#include "bsp_key.h"
#include "bsp_usart.h"

uint8_t flag=0;

void delay(uint32_t count)
{
	for (;count!=0;count--);
}

void jieshu(void)
{
	Usart_SendByte(DEBUG_USARTx,0xff);
	Usart_SendByte(DEBUG_USARTx,0xff);
	Usart_SendByte(DEBUG_USARTx,0xff);
}

int main(void)
{
	LED_GPIO_Config();
	LED_G(ON);
	KEY_GPIO_Config();
	while (1)
	{
		if ( Key_Scan(KEY1_GPIO_PORT,KEY1_GPIO_PIN) == KEY_ON )
		{
			LED_G_TOGGLE;
			if(flag<4)
			{
				flag++;
			}
		}
		if ( Key_Scan(KEY2_GPIO_PORT,KEY2_GPIO_PIN) == KEY_ON )
		{
			LED_R_TOGGLE;
			if(flag>0)
			{
				flag--;
			}
		}
		switch(flag)
		{ 
			case(0):
			{
				printf("page a1");
				jieshu();
			}
			break;
			
			case(1):
			{
				printf("page a2");
				jieshu();
			}
			break;
			
			case(2):
			{
				printf("page a3");
				jieshu();
			}	
			break;
			
			case(3):
			{
				printf("page a4");
				jieshu();
			}	
			break;
			
			case(4):
			{
				printf("page a5");
				jieshu();
			}	
			break;
		}
		
		
		
				
	}
	
}

