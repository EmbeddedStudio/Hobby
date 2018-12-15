#include "bsp_dma_mtp.h"
uint8_t aDST_Buffer[BUFFER_SIZE];
void USARTx_DMA_Config(void)
{
	DMA_InitTypeDef   DMA_InitStructure;
	RCC_AHBPeriphClockCmd(USART_TX_DMA_CLK, ENABLE);
	
	DMA_InitStructure.DMA_PeripheralBaseAddr =(uint32_t) USART_DR_ADDRESS;
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)aDST_Buffer;
	DMA_InitStructure.DMA_DIR =DMA_DIR_PeripheralDST;
	
	DMA_InitStructure.DMA_BufferSize = BUFFER_SIZE;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_MemoryDataSize =  DMA_MemoryDataSize_Byte;
	DMA_InitStructure.DMA_PeripheralDataSize =DMA_PeripheralDataSize_Byte; 
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	DMA_Init(USART_TX_DMA_CHANNEL, &DMA_InitStructure);
//	DMA_ClearFlag(DMA_FLAG_TC);
	DMA_Cmd(USART_TX_DMA_CHANNEL,ENABLE);
}

//uint8_t SendBuff[SENDBUFF_SIZE];
//void USARTx_DMA_Config(void)
//{
//		DMA_InitTypeDef DMA_InitStructure;
//	
//		// ����DMAʱ��
//		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
//		// ����DMAԴ��ַ���������ݼĴ�����ַ*/
//		DMA_InitStructure.DMA_PeripheralBaseAddr = USART_DR_ADDRESS;
//		// �ڴ��ַ(Ҫ����ı�����ָ��)
//		DMA_InitStructure.DMA_MemoryBaseAddr = (u32)SendBuff;
//		// ���򣺴��ڴ浽����	
//		DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
//		// �����С	
//		DMA_InitStructure.DMA_BufferSize = SENDBUFF_SIZE;
//		// �����ַ����	    
//		DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
//		// �ڴ��ַ����
//		DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
//		// �������ݵ�λ	
//		DMA_InitStructure.DMA_PeripheralDataSize = 
//		DMA_PeripheralDataSize_Byte;
//		// �ڴ����ݵ�λ
//		DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;	 
//		// DMAģʽ��һ�λ���ѭ��ģʽ
//		DMA_InitStructure.DMA_Mode = DMA_Mode_Normal ;
//		//DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;	
//		// ���ȼ�����	
//		DMA_InitStructure.DMA_Priority = DMA_Priority_Medium; 
//		// ��ֹ�ڴ浽�ڴ�Ĵ���
//		DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
//		// ����DMAͨ��		   
//		DMA_Init(USART_TX_DMA_CHANNEL, &DMA_InitStructure);		
//		// ʹ��DMA
//		DMA_Cmd (USART_TX_DMA_CHANNEL,ENABLE);
//}

void USART_Config (void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;      //�������ӵ���GPIO
	USART_InitTypeDef  USART_InitStructure;	   //���ô��ڳ�ʼ��
	
	// �򿪴���GPIO��ʱ��
	DEBUG_USART_GPIO_APBxClkCmd(DEBUG_USART_GPIO_CLK, ENABLE);
	// �򿪴��������ʱ��
	DEBUG_USART_APBxClkCmd(DEBUG_USART_CLK, ENABLE);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;			//�������
	GPIO_InitStructure.GPIO_Pin = DEBUG_USART_TX_GPIO_PIN;	//PA9   PA10
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(DEBUG_USART_TX_GPIO_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = DEBUG_USART_RX_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(DEBUG_USART_RX_GPIO_PORT, &GPIO_InitStructure);
	
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;		//����Ӳ��������
	USART_InitStructure.USART_Mode  =   USART_Mode_Rx | USART_Mode_Tx;			//���շ�������
	USART_InitStructure.USART_BaudRate = DEBUG_USART_BAUDRATE;				//������
	USART_InitStructure.USART_Parity = USART_Parity_No;									//У��
	USART_InitStructure.USART_StopBits = USART_StopBits_1;					//ֹͣλ
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;				//�ֳ�
	USART_Init(DEBUG_USARTx, &USART_InitStructure);
//	// �����ж����ȼ�����
//	NVIC_Configuration();
//	
//	// ʹ�ܴ��ڽ����ж�
//	USART_ITConfig(DEBUG_USARTx, USART_IT_RXNE, ENABLE);	
//	
	// ʹ�ܴ���
	USART_Cmd(DEBUG_USARTx, ENABLE);
}

	///�ض���c�⺯��printf�����ڣ��ض�����ʹ��printf����
int fputc(int ch, FILE *f)
{
		/* ����һ���ֽ����ݵ����� */
		USART_SendData(DEBUG_USARTx, (uint8_t) ch);
		
		/* �ȴ�������� */
		while (USART_GetFlagStatus(DEBUG_USARTx, USART_FLAG_TXE) == RESET);		
		
		return (ch);
}

	///�ض���c�⺯��scanf�����ڣ���д����ʹ��scanf��getchar�Ⱥ���
int fgetc(FILE *f)
{
		/* �ȴ������������� */
		while (USART_GetFlagStatus(DEBUG_USARTx, USART_FLAG_RXNE) == RESET);

		return (int)USART_ReceiveData(DEBUG_USARTx);
}
