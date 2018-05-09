#include "stm32f10x.h"   
#include "bsp_usart.h"   
#include "bsp_spi.h" 
#include "ff.h"	

uint8_t buff[4096];

FATFS  fsobject;

int main(void)
{	
	FRESULT res;
	uint32_t ID;
	
	USART_Config ();
	
	SPI_FLASH_Init();
	
	printf("FATFS≤‚ ‘≥Ã–Ú\n");
	
	if(0==FR_NO_FILESYSTEM)
	{
		f_mkfs("1:",0,0);
	}
	
	res=f_mount(&fsobject,"1:",1);
	
	printf("rse=%d",res);
	
	ID = SPI_FLASH_ReadByte();
	
	printf("\r\n ID=0x%x\r\n",ID);
	
	SPI_Erase(0);
	SPI_Wite_Erase();

	
	while(1);
}
