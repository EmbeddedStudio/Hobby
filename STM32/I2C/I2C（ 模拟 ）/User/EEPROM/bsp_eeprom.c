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
                return 1;       //��������   ����˵��Ӧ��
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
//                                printf("���豸Ӧ��ʱ    �������005");
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




//��������
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
                printf("����ʧ��\r\n");
               
        }
        else
        {
                printf("�����ɹ�\r\n");
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
		/* û�м�⵽EEPROM */
		printf("û�м�⵽����EEPROM!\r\n");
				
		return 0;
	}
/*------------------------------------------------------------------------------------*/  
  /* �����Ի����� */
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
		printf("дeeprom����\r\n");
		return 0;
	}
	else
	{		
		printf("дeeprom�ɹ���\r\n");
	}
  
  /*д��֮����Ҫ�ʵ�����ʱ��ȥ������Ȼ�����*/
  delay_ms(5);
/*-----------------------------------------------------------------------------------*/
  if (EEPROM_ReadData(read_buf, 0, EEPROM_SIZE) == 0)
	{
		printf("��eeprom����\r\n");
		return 0;
	}
	else
	{		
		printf("��eeprom�ɹ����������£�\r\n");
	}
/*-----------------------------------------------------------------------------------*/  
  for (i = 0; i < EEPROM_SIZE; i++)
	{
		if(read_buf[i] != write_buf[i])
		{
			printf("0x%02X ", read_buf[i]);
			printf("����:EEPROM������д������ݲ�һ��");
			return 0;
		}
    printf(" %02X", read_buf[i]);
		
		if ((i & 15) == 15)
		{
			printf("\r\n");	
		}		
	}
  printf("eeprom��д���Գɹ�\r\n");
  return 1;
}







