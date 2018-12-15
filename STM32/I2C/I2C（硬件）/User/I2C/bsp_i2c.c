#include "bsp_i2c.h"
#include "bsp_usart.h"

void I2C_GPIO_Config (void)
{
	GPIO_InitTypeDef  GPIO_InitStruct;      //�������ӵ���GPIO
	I2C_InitTypeDef  I2C_InitStruct;
	
	EEPROM_I2C_GPIO_APBxClock_FUN(EEPROM_I2C_GPIO_CLK,ENABLE);
	EEPROM_I2C_APBxClock_FUN(EEPROM_I2C_CLK,ENABLE);
	
	GPIO_InitStruct.GPIO_Pin = EEPROM_I2C_SCL_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_OD;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(EEPROM_I2C_SCL_PORT, & GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin = EEPROM_I2C_SDA_PIN ;
	GPIO_Init(EEPROM_I2C_SDA_PORT, & GPIO_InitStruct);
	
	I2C_InitStruct.I2C_Ack = I2C_Ack_Enable;
	I2C_InitStruct.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	I2C_InitStruct.I2C_ClockSpeed = I2C_Speed;
	I2C_InitStruct.I2C_DutyCycle = I2C_DutyCycle_2;
	I2C_InitStruct.I2C_Mode = I2C_Mode_I2C;
	I2C_InitStruct.I2C_OwnAddress1 = I2Cx_OWN_ADDRESS7;
	I2C_Init(EEPROM_I2Cx, &I2C_InitStruct);
	I2C_Cmd(EEPROM_I2Cx,ENABLE);
	
}
void EEPROM_Write(uint8_t addr,uint8_t data)
{
         //������ʼ�ź�
        I2C_GenerateSTART(EEPROM_I2Cx, 	ENABLE);
        //���EV5�¼�
        while (I2C_CheckEvent( EEPROM_I2Cx,I2C_EVENT_MASTER_MODE_SELECT)==ERROR);
         //����7λ�豸��ַ
        I2C_Send7bitAddress( EEPROM_I2Cx,EEPROM_ADDR,I2C_Direction_Transmitter);
         //���EV6�¼�
        while (I2C_CheckEvent( EEPROM_I2Cx,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)==ERROR);
         //���ʹ洢��ַ
        I2C_SendData(EEPROM_I2Cx,addr); 
          //���EV8�¼�
        while (I2C_CheckEvent( EEPROM_I2Cx,I2C_EVENT_MASTER_BYTE_TRANSMITTING )==ERROR);
         //��������
        I2C_SendData(EEPROM_I2Cx,data);
          //���EV8_2�¼�
        while (I2C_CheckEvent( EEPROM_I2Cx,I2C_EVENT_MASTER_BYTE_TRANSMITTED)==ERROR);
         //���ͽ����ź�
        I2C_GenerateSTOP(EEPROM_I2Cx, 	ENABLE); 
 }
 
 void EEPROM_Pare_Write(uint8_t addr,uint8_t *data,uint8_t num)
 {
	 //������ʼ�ź�
	I2C_GenerateSTART(EEPROM_I2Cx, 	ENABLE);
	//���EV5�¼�
	while (I2C_CheckEvent( EEPROM_I2Cx,I2C_EVENT_MASTER_MODE_SELECT)==ERROR);
	 //����7λ�豸��ַ
	I2C_Send7bitAddress( EEPROM_I2Cx,EEPROM_ADDR,I2C_Direction_Transmitter);
	 //���EV6�¼�
	while (I2C_CheckEvent( EEPROM_I2Cx,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)==ERROR);
	 //���ʹ洢��ַ
	I2C_SendData(EEPROM_I2Cx,addr); 
	  //���EV8�¼�
	while (I2C_CheckEvent( EEPROM_I2Cx,I2C_EVENT_MASTER_BYTE_TRANSMITTING )==ERROR);
	 while(num)
	 {	
		 //��������
		I2C_SendData(EEPROM_I2Cx,*data);
		  //���EV8_2�¼�
		while (I2C_CheckEvent( EEPROM_I2Cx,I2C_EVENT_MASTER_BYTE_TRANSMITTED)==ERROR);
		 data++;
		 num--;
	 }
	 //���ͽ����ź�
	I2C_GenerateSTOP(EEPROM_I2Cx,ENABLE); 
 }
 
 void ERPROM_READ(uint8_t addr,uint8_t *data,uint8_t num)
 {
	 //������ʼ�ź�
	I2C_GenerateSTART(EEPROM_I2Cx,ENABLE);
	//���EV5�¼�
	while (I2C_CheckEvent( EEPROM_I2Cx,I2C_EVENT_MASTER_MODE_SELECT)==ERROR);
	 //����7λ�豸��ַ
	I2C_Send7bitAddress( EEPROM_I2Cx,EEPROM_ADDR,I2C_Direction_Transmitter);
	 //���EV6�¼�
	while (I2C_CheckEvent( EEPROM_I2Cx,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)==ERROR);
	 //���ʹ洢��ַ
	I2C_SendData(EEPROM_I2Cx,addr); 
	  //���EV8�¼�
	while (I2C_CheckEvent( EEPROM_I2Cx,I2C_EVENT_MASTER_BYTE_TRANSMITTING )==ERROR);
	 
	 //���͵ڶ�����ʼ�ź�
	 I2C_GenerateSTART(EEPROM_I2Cx,ENABLE);
	//���EV5�¼�
	while (I2C_CheckEvent( EEPROM_I2Cx,I2C_EVENT_MASTER_MODE_SELECT)==ERROR);
	 //����7λ�豸��ַ
	I2C_Send7bitAddress( EEPROM_I2Cx,EEPROM_ADDR,I2C_Direction_Receiver);
	 //���EV6�¼�
	while (I2C_CheckEvent( EEPROM_I2Cx,I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED)==ERROR); 
	
	
	while (num)
	{
		
		if(num==1)
		{
			I2C_AcknowledgeConfig(EEPROM_I2Cx,DISABLE);
		}
		//���EV7�¼�
		while (I2C_CheckEvent( EEPROM_I2Cx,I2C_EVENT_MASTER_BYTE_RECEIVED )==ERROR);
		
		//��ȡ����
		*data=I2C_ReceiveData (EEPROM_I2Cx);
		data++;
		num--;
	}
	 //���ͽ����ź�
	I2C_GenerateSTOP(EEPROM_I2Cx,ENABLE); 
	I2C_AcknowledgeConfig(EEPROM_I2Cx,ENABLE);

 }

void EEPROM_Wite(void)
{
	do
	{
		 //������ʼ�ź�
		I2C_GenerateSTART(EEPROM_I2Cx,ENABLE);
		//���EV5�¼�
		while (I2C_GetFlagStatus ( EEPROM_I2Cx,I2C_FLAG_SB)==RESET);
		 //����7λ�豸��ַ
		I2C_Send7bitAddress( EEPROM_I2Cx,EEPROM_ADDR,I2C_Direction_Transmitter);
	}
	 //���EV6�¼�
	while (I2C_GetFlagStatus ( EEPROM_I2Cx,I2C_FLAG_ADDR)==RESET);
	I2C_GenerateSTOP(EEPROM_I2Cx,ENABLE); 

}	











