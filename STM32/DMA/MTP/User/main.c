#include "stm32f10x.h"   
#include "bsp_led.h"
#include "bsp_dma_mtp.h"

extern uint8_t aDST_Buffer[BUFFER_SIZE];

int main(void)
{
	uint16_t i=0;
	LED_GPIO_Config ();
	
	for (i;i<BUFFER_SIZE;i++)
	{
		aDST_Buffer[i]='A';
	}
	USART_Config ();
	USARTx_DMA_Config();
	USART_DMACmd(DEBUG_USARTx , USART_DMAReq_Tx, ENABLE);
	while (1)
	{
		LED_GREEN;
	}
	  
}

