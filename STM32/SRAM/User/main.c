#include "stm32f10x.h"   
#include "bsp_usart.h"   
#include "bsp_sram.h" 

uint8_t ad __attribute__((at(0x68000000+0x50)));

//必须定义为全局变量

int main(void)
{	
	uint32_t *p;
	
	USART_Config ();
	
	SRAM_Init();
	
	printf("\r\n SRAM测试程序\r\n");
	
	p = (uint32_t*)SRAM_BASE_ADDR;
	
	*p=0xff;	 
	
	printf("\r\n 读出的数据为：0x%x\r\n",*p);
	
	printf("\r\n ad=0x%d,ad addr=0x%x\r\n",ad,(unsigned int)&ad);
	
	
	while(1);
}

