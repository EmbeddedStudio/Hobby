#include "stm32f10x.h"   
#include "bsp_led.h"
#include "bsp_basic_tim.h"
#include "bsp_usart.h"

uint16_t time=0;


		
void jieshu(void)
{
	Usart_SendByte(USART1,0xff);
	Usart_SendByte(USART1,0xff);
	Usart_SendByte(USART1,0xff);
}

void ShiZhong_Init(void)
{
	printf("n0.val=23");
	jieshu();
	printf("n1.val=59");
	jieshu();
	printf("n2.val=50");
	jieshu();
}

int main(void)
{
	uint8_t miao=50;
	
	uint8_t shi=23;
	
	uint8_t fen=59;
	
	LED_GPIO_Config();
	
	USART_Config();
	
	TIM_Init();

	ShiZhong_Init();
	
	
	while (1)
	{
		if (time==1000)
		{  
			miao++;
			if(miao<60)
			{
				printf("n2.val=%d",miao);
				jieshu();
			}
			else 
			{
				miao=0;
				printf("n2.val=%d",miao);
				jieshu();
				fen++;
				if(fen<60)
				{
					printf("n1.val=%d",fen);
					jieshu();
				}
				else
				{
					fen=0;
					printf("n1.val=%d",fen);
					jieshu();
					shi++;
					if(shi<24)
					{
						printf("n0.val=%d",shi);
						jieshu();
					}
					else
					{
						shi=0;
						printf("n0.val=%d",shi);
						jieshu();
						
					}
				}
				
			}
		time=0;
		}	
		
	}	
}

