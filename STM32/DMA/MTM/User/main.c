#include "stm32f10x.h"   
#include "bsp_led.h"
#include "bsp_dma_mtm.h"

void delay(uint32_t count)
{
	for (;count!=0;count--);
}
int main(void)
{
	uint8_t  state=0;
	LED_GPIO_Config();
	LED_YELLOW ;
	
	DMA_Config();
	delay(0xffffFF);
	/* 等待DMA传输完成 */
	  while(DMA_GetFlagStatus(DMA_FLAG_TC)==RESET)
	  {	    
	  }
	state=Buffercmp(aSRC_Const_Buffer, aDST_Buffer, BUFFER_SIZE);
	if (state==0)
	{
		LED_RED;
	}
	else
	{
		LED_GREEN;
	}
	while (1)
	{
	}
}

