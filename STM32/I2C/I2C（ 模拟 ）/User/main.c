#include "stm32f10x.h"   
#include "bsp_led.h"
#include "bsp_usart.h"
#include "bsp_i2c.h"
#include "bsp_eeprom.h"
#include "bsp_systick.h"

int main(void)
{	
//        uint8_t i;
//        uint8_t readbuff[8];
        uint8_t rec;
        LED_GPIO_Config();
        LED_BLUE;
        USART_Config();
        systick_init();
        printf("eeprom 软件模拟i2c测试例程 \r\n");

        I2C_Start();
        delay_ms(1);
        I2C_SentData(0xa0);
        rec=I2C_WiteAsk();
        printf("rec1=%d\r\n",rec);
//        I2C_SentData(0x22);
//        rec=I2C_WiteAsk();
//        printf("rec2=%d\r\n",rec);
//        I2C_Stop();
        
//        EEPROM_writeByte(100,20);
//        delay_ms(10);
//        EEPROM_ReadData(readbuff,100,8);
//        printf("读出的数据");
//        for(i=0;i<8;i++)
//        {
//                printf("%d  ",readbuff[i]);
//        }
        
//        if(ee_Test() == 1)
//  	{
//		LED_GREEN;
//	}
//        else
//        {
//                LED_RED;
//        }
        
        
        while(1)
        {
               ;
        }
}

