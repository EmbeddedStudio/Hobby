#include "stm32f10x.h"   
#include "bsp_led.h"
#include "bsp_usart.h"


int main(void)
{	
	char ch;
	LED_GPIO_Config ();
	USART_Config ();
	printf ("测试程序\n");
	while (1)		
	{
		ch=getchar();
		printf("接收到的字符：%c\n",ch);
		switch (ch)
		{
			case 'R':LED_RED;
			break;
			case 'G':LED_GREEN;
			break;
			case 'B':LED_BLUE;
			break;
			default:LED_OFF;
			break;		
		}
	}
}

