#include "bsp_eeprom.h"
#include "bsp_usart.h"
#include "bsp_i2c.h"
#include "bsp_systick.h"

uint8_t I2C_Check(void)
{
        printf("[eeprom][%d] %s enter \r\n", __LINE__, __FUNCTION__);
        if(I2C_Device(EEPROM_ADDR)==0)
        {
                I2C_Stop();
                return 1;       //器件存在   或者说响应了
        }
        else
        {
                I2C_Stop();
                return 0;
        }
}



uint8_t EEPROM_ReadData(uint8_t *_pReadBuf, uint16_t Address, uint16_t Size)
{
        
        uint16_t i;
        printf("[i2c][%d] %s  \r\n", __LINE__, __FUNCTION__);
        I2C_Start();
        I2C_SentData(EEPROM_ADDR);
//        delay_ms(1);
        if( I2C_WiteAsk !=0 )
        {
                I2C_Stop();
                printf("[i2c][%d] %s  \r\n", __LINE__, __FUNCTION__);
                return 0;
        }
        I2C_SentData((uint8_t)Address);
//        delay_ms(1);
        if( I2C_WiteAsk !=0 )
        {
                I2C_Stop();
                printf("[i2c][%d] %s  \r\n", __LINE__, __FUNCTION__);
                return 0;
        }
        I2C_Start();
        I2C_SentData(EEPROM_ADDR+1);
        if( I2C_WiteAsk !=0 )
        {
                I2C_Stop();
                printf("[i2c][%d] %s  \r\n", __LINE__, __FUNCTION__);
                return 0;
        }
        for(i=0;i<Size;i++)
        {
                _pReadBuf[i] = I2C_ReadData();
                if( i!=(Size-1) )
                {
                        I2C_Ask();
                }
                else
                {
                        I2C_Nask();
                }
        }
        I2C_Stop();
        return 1;
        
}

//uint8_t EEPROM_writeByte(uint8_t Address,uint8_t data)
//{
//        I2C_Start();
//        I2C_SentData(EEPROM_ADDR);
//        if( I2C_WiteAsk !=0 )
//        {
//                I2C_Stop();
//                printf("[i2c][%d] %s  \r\n", __LINE__, __FUNCTION__);
//                return 0;
//        }
//        I2C_SentData(Address);
//        if( I2C_WiteAsk !=0 )
//        {
//                I2C_Stop();
//                printf("[i2c][%d] %s  \r\n", __LINE__, __FUNCTION__);
//                return 0;
//        }
//        I2C_SentData(data);
//        if( I2C_WiteAsk !=0 )
//        {
//                I2C_Stop();
//                printf("[i2c][%d] %s  \r\n", __LINE__, __FUNCTION__);
//                return 0;
//        }
//        I2C_Stop();
//        return 1;
//        
//}



uint8_t EEPROM_WriteData(uint8_t *_pReadBuf, uint16_t Address, uint16_t Size)
{
        uint16_t i;
//        uint8_t m;
        for(i=0;i<Size;i++)
        {
                if( (i==0) || (Address & (EEPROM_PAGE_SIZE - 1)) == 0 )
                {
                        I2C_Stop();
//                        for(m=0;m<10;m++)
//                        {
                                I2C_Start();
                                I2C_SentData(EEPROM_ADDR);
                                delay_ms(5);
                                if( I2C_WiteAsk !=0 )
                                {
                                        I2C_Stop();
                                        printf("[i2c][%d] %s  \r\n", __LINE__, __FUNCTION__);
                                        return 0;
                                }
//                        }
//                        if(m==10)
//                        {
//                                I2C_Stop();
//                                printf("从设备应答超时    错误代码005");
//                                return 0;
//                        }
                        I2C_SentData(Address);
                        if(I2C_WiteAsk !=0);
                        {
                                I2C_Stop();
                                printf("[i2c][%d] %s  \r\n", __LINE__, __FUNCTION__);
                                return 0;
                        }      
                }
                I2C_SentData(_pReadBuf[i]);
                if(I2C_WiteAsk !=0)
                {
                        I2C_Stop();
                        printf("[i2c][%d] %s  \r\n", __LINE__, __FUNCTION__);
                        return 0;
                }
                Address++;
        }
        I2C_Stop();
        return 1;
}




//擦除函数
void EEPROM_Erase(void)
{
        uint16_t i;
        uint8_t buf[EEPROM_SIZE];
        for(i=0;i<EEPROM_SIZE;i++)
        {
                buf[i]=0xff;
        }
        if(EEPROM_WriteData(buf,0,EEPROM_SIZE)==0)
        {
                printf("擦除失败\r\n");
               
        }
        else
        {
                printf("擦除成功\r\n");
        }
}


uint8_t ee_Test(void) 
{
  uint16_t i;
  uint8_t re;
  uint8_t write_buf[EEPROM_SIZE];
  uint8_t read_buf[EEPROM_SIZE];
  
        for (i = 0; i < EEPROM_SIZE; i++)
	{		
		write_buf[i] = i;
	}
/*-----------------------------------------------------------------------------------*/  
  if (I2C_Check() == 0)
	{
		/* 没有检测到EEPROM */
		printf("没有检测到串行EEPROM!\r\n");
				
		return 0;
	}
/*------------------------------------------------------------------------------------*/  
  /* 填充测试缓冲区 */
	I2C_Start();
        delay_ms(1);
        I2C_SentData(0xa0);
        delay_ms(1);
        re=I2C_WiteAsk();
        printf("re=%d\r\n",re);
        I2C_Stop();
/*------------------------------------------------------------------------------------*/  
  if (EEPROM_WriteData(write_buf, 0, EEPROM_SIZE) == 0)
	{
		printf("写eeprom出错！\r\n");
		return 0;
	}
	else
	{		
		printf("写eeprom成功！\r\n");
	}
  
  /*写完之后需要适当的延时再去读，不然会出错*/
  delay_ms(5);
/*-----------------------------------------------------------------------------------*/
  if (EEPROM_ReadData(read_buf, 0, EEPROM_SIZE) == 0)
	{
		printf("读eeprom出错！\r\n");
		return 0;
	}
	else
	{		
		printf("读eeprom成功，数据如下：\r\n");
	}
/*-----------------------------------------------------------------------------------*/  
  for (i = 0; i < EEPROM_SIZE; i++)
	{
		if(read_buf[i] != write_buf[i])
		{
			printf("0x%02X ", read_buf[i]);
			printf("错误:EEPROM读出与写入的数据不一致");
			return 0;
		}
    printf(" %02X", read_buf[i]);
		
		if ((i & 15) == 15)
		{
			printf("\r\n");	
		}		
	}
  printf("eeprom读写测试成功\r\n");
  return 1;
}







