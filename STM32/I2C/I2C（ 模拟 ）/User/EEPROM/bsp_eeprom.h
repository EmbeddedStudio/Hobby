#ifndef __BSP_EEPROM_H
#define __BSP_EEPROM_H

#include "stm32f10x.h"

#define EEPROM_ADDR		        0xA0		
#define EEPROM_PAGE_SIZE		  8			 
#define EEPROM_SIZE			256

/************º¯ÊýÉùÃ÷***************/
uint8_t I2C_Check(void);
uint8_t EEPROM_ReadData(uint8_t *_pReadBuf, uint16_t Address, uint16_t Size);
uint8_t EEPROM_WriteData(uint8_t *_pReadBuf, uint16_t Address, uint16_t Size);
void EEPROM_Erase(void);
uint8_t ee_Test(void) ;
//uint8_t EEPROM_writeByte(uint8_t Address,uint8_t data);

#endif /*__BSP_EEPROM_H*/


