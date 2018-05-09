#include "bsp_led.h"

void LED_GPIO_Config (void)
{
	
	GPIO_InitTypeDef	 GPIO_Initstuct;
	
	RCC_APB2PeriphClockCmd(LED_GPIO_CLK, ENABLE);		//开时钟
	
	GPIO_Initstuct.GPIO_Pin = LED_GPIO_PIN;
	GPIO_Initstuct.GPIO_Mode = GPIO_Mode_Out_PP;    //设置模式为推挽输出
	GPIO_Initstuct.GPIO_Speed = GPIO_Speed_50MHz;	//设置速度
	GPIO_Init(LED_GPIO_PORT, &GPIO_Initstuct);	//		
}
