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
//		// 开启DMA时钟
//		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
//		// 设置DMA源地址：串口数据寄存器地址*/
//		DMA_InitStructure.DMA_PeripheralBaseAddr = USART_DR_ADDRESS;
//		// 内存地址(要传输的变量的指针)
//		DMA_InitStructure.DMA_MemoryBaseAddr = (u32)SendBuff;
//		// 方向：从内存到外设	
//		DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
//		// 传输大小	
//		DMA_InitStructure.DMA_BufferSize = SENDBUFF_SIZE;
//		// 外设地址不增	    
//		DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
//		// 内存地址自增
//		DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
//		// 外设数据单位	
//		DMA_InitStructure.DMA_PeripheralDataSize = 
//		DMA_PeripheralDataSize_Byte;
//		// 内存数据单位
//		DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;	 
//		// DMA模式，一次或者循环模式
//		DMA_InitStructure.DMA_Mode = DMA_Mode_Normal ;
//		//DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;	
//		// 优先级：中	
//		DMA_InitStructure.DMA_Priority = DMA_Priority_Medium; 
//		// 禁止内存到内存的传输
//		DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
//		// 配置DMA通道		   
//		DMA_Init(USART_TX_DMA_CHANNEL, &DMA_InitStructure);		
//		// 使能DMA
//		DMA_Cmd (USART_TX_DMA_CHANNEL,ENABLE);
//}

void USART_Config (void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;      //配置连接到的GPIO
	USART_InitTypeDef  USART_InitStructure;	   //配置串口初始化
	
	// 打开串口GPIO的时钟
	DEBUG_USART_GPIO_APBxClkCmd(DEBUG_USART_GPIO_CLK, ENABLE);
	// 打开串口外设的时钟
	DEBUG_USART_APBxClkCmd(DEBUG_USART_CLK, ENABLE);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;			//推挽输出
	GPIO_InitStructure.GPIO_Pin = DEBUG_USART_TX_GPIO_PIN;	//PA9   PA10
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(DEBUG_USART_TX_GPIO_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = DEBUG_USART_RX_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(DEBUG_USART_RX_GPIO_PORT, &GPIO_InitStructure);
	
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;		//配置硬件控制流
	USART_InitStructure.USART_Mode  =   USART_Mode_Rx | USART_Mode_Tx;			//接收发送引脚
	USART_InitStructure.USART_BaudRate = DEBUG_USART_BAUDRATE;				//波特率
	USART_InitStructure.USART_Parity = USART_Parity_No;									//校验
	USART_InitStructure.USART_StopBits = USART_StopBits_1;					//停止位
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;				//字长
	USART_Init(DEBUG_USARTx, &USART_InitStructure);
//	// 串口中断优先级配置
//	NVIC_Configuration();
//	
//	// 使能串口接收中断
//	USART_ITConfig(DEBUG_USARTx, USART_IT_RXNE, ENABLE);	
//	
	// 使能串口
	USART_Cmd(DEBUG_USARTx, ENABLE);
}

	///重定向c库函数printf到串口，重定向后可使用printf函数
int fputc(int ch, FILE *f)
{
		/* 发送一个字节数据到串口 */
		USART_SendData(DEBUG_USARTx, (uint8_t) ch);
		
		/* 等待发送完毕 */
		while (USART_GetFlagStatus(DEBUG_USARTx, USART_FLAG_TXE) == RESET);		
		
		return (ch);
}

	///重定向c库函数scanf到串口，重写向后可使用scanf、getchar等函数
int fgetc(FILE *f)
{
		/* 等待串口输入数据 */
		while (USART_GetFlagStatus(DEBUG_USARTx, USART_FLAG_RXNE) == RESET);

		return (int)USART_ReceiveData(DEBUG_USARTx);
}
