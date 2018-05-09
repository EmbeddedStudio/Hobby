#include "stm32f10x.h"   
#include "bsp_led.h"
#include "bsp_usart.h"
#include "bsp_i2c.h"

uint8_t read[10]={0};
uint8_t write[7]={1,2,3,4,5,6,7};

int main(void)
{
	uint8_t i=0;
	USART_Config ();
	printf("I2C≤‚ ‘≥Ã–Ú\n");
	I2C_GPIO_Config ();
	EEPROM_Write(1,0);
	
	EEPROM_Wite();

	EEPROM_Pare_Write(2,write,7);
	
	EEPROM_Wite();
	
	ERPROM_READ(11, read,9);
	for (i=0;i<8;i++)
	{
		printf("0x%d  ",read[i]);
	}
	while (1)
	{
		
	}
	
}

