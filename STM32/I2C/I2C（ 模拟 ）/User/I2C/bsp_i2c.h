#ifndef __BSP_I2C_H
#define __BSP_I2C_H

#include "stm32f10x.h"

#define I2C_SCL_PIN         GPIO_Pin_6	
#define I2C_SDA_PIN         GPIO_Pin_7
#define I2C_GPIO_PORT       GPIOB 
#define I2C_GPIO_CLK        RCC_APB2Periph_GPIOB 

/*************i2c总线的宏定义*****************/
//#if0
#define I2C_SCL_1()         GPIO_SetBits(I2C_GPIO_PORT, I2C_SCL_PIN)
#define I2C_SCL_0()         GPIO_ResetBits(I2C_GPIO_PORT, I2C_SCL_PIN)
#define I2C_SDA_1()         GPIO_SetBits(I2C_GPIO_PORT, I2C_SDA_PIN)
#define I2C_SDA_0()         GPIO_ResetBits(I2C_GPIO_PORT, I2C_SDA_PIN)
//#else
//#define I2C_SCL_1()  I2C_GPIO_PORT->BSRR = I2C_SCL_PIN				/* SCL = 1 */
//#define I2C_SCL_0()  I2C_GPIO_PORT->BRR = I2C_SCL_PIN				/* SCL = 0 */

//#define I2C_SDA_1()  I2C_GPIO_PORT->BSRR = I2C_SDA_PIN				/* SDA = 1 */
//#define I2C_SDA_0()  I2C_GPIO_PORT->BRR = I2C_SDA_PIN
//#endif


//IDR电平输入寄存器  是查看引脚电平状态用的寄存器，ODR是引脚电平输出的寄存器。读取SDA总线的状态
#define I2C_SDA_READ()  ((I2C_GPIO_PORT->IDR & I2C_SDA_PIN) != 0)

/**************函数声明**************/
void I2C_GPIO_Init(void);
void Delay(void);
void I2C_Start(void);
void I2C_Stop(void);
void I2C_Ask(void);
void I2C_Nask(void);
void I2C_SentData(uint8_t Data);
uint8_t I2C_WiteAsk(void);
uint8_t I2C_Device(uint8_t Address);
uint8_t I2C_ReadData(void);
void I2C_In_GPIO_Config (void);
void I2C_Out_GPIO_Config (void);


#endif /*__BSP_I2C_H*/

