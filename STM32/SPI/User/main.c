#include "stm32f10x.h"   
#include "bsp_usart.h"   
#include "bsp_spi.h" 

uint8_t buff[4096];

int main(void)
{	
	uint32_t ID;
	uint16_t i;
	
	USART_Config ();
	
	SPI_FLASH_Init();
	
	printf("SPI≤‚ ‘≥Ã–Ú\n");
	
	ID = SPI_FLASH_ReadByte();
	
	printf("\r\n ID=0x%x\r\n",ID);
	
	SPI_Erase(0);
	SPI_Wite_Erase();
	
	SPI_Read_Data(0 , buff,4096);
	
	for(i=0;i<4096;i++)
	{
		printf("0x%x ",buff[i]);
		if (i%10==0)
		{
			printf("\r\n");
		}
	}
	
	while(1);
}

