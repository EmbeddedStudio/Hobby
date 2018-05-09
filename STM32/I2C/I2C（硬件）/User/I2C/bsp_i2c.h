#ifndef __BSP_I2C_H
#define __BSP_I2C_H

#include "stm32f10x.h"

#define        EEPROM_I2Cx                      I2C1
#define        EEPROM_I2C_APBxClock_FUN         RCC_APB1PeriphClockCmd
#define        EEPROM_I2C_CLK                   RCC_APB1Periph_I2C1
#define        EEPROM_I2C_GPIO_APBxClock_FUN    RCC_APB2PeriphClockCmd
#define        EEPROM_I2C_GPIO_CLK              RCC_APB2Periph_GPIOB     
#define        EEPROM_I2C_SCL_PORT              GPIOB   
#define        EEPROM_I2C_SCL_PIN               GPIO_Pin_6
#define        EEPROM_I2C_SDA_PORT              GPIOB 
#define        EEPROM_I2C_SDA_PIN               GPIO_Pin_7     
#define	       I2C_Speed 			400000
#define        I2Cx_OWN_ADDRESS7                0x0A
#define	       EEPROM_ADDR			0xA0

void I2C_GPIO_Config (void);
void EEPROM_Write(uint8_t addr,uint8_t data);
void ERPROM_READ(uint8_t addr,uint8_t *data,uint8_t num);
void EEPROM_Wite(void);
void EEPROM_Pare_Write(uint8_t addr,uint8_t *data,uint8_t num);

#endif /* __BSP_I2C_H */
