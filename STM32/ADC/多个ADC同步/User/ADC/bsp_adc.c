#include "bsp_adc.h"

__IO uint16_t ADC_ConvertedValue[NOFCHANEL]={0};

static void ADCx_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	// ADCx_1 GPIO 初始化
	ADCx_1_GPIO_APBxClock_FUN ( ADCx_1_GPIO_CLK, ENABLE );
	GPIO_InitStruct.GPIO_Pin = ADCx_1_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(ADCx_1_PORT, &GPIO_InitStruct);

	// ADCx_2 GPIO 初始化
	ADCx_1_GPIO_APBxClock_FUN ( ADCx_2_GPIO_CLK, ENABLE );
	GPIO_InitStruct.GPIO_Pin = ADCx_2_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(ADCx_2_PORT, &GPIO_InitStruct);	
}

static void ADC_Mode_Config(void)
{
	DMA_InitTypeDef DMA_InitStruct;
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	
	// 复位DMA控制器
	DMA_DeInit(ADC_DMA_CHANNEL);
	
	// 配置 DMA 初始化结构体
	// 外设基址为：ADC 数据寄存器地址
	DMA_InitStruct.DMA_PeripheralBaseAddr = ( uint32_t ) ( & ( ADCx_1->DR ) );
	
	// 存储器地址，实际上就是一个内部SRAM的变量
	DMA_InitStruct.DMA_MemoryBaseAddr = (uint32_t)ADC_ConvertedValue;
	
	// 数据源来自外设
	DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralSRC;
	
	// 缓冲区大小为1，缓冲区的大小应该等于存储器的大小
	DMA_InitStruct.DMA_BufferSize = NOFCHANEL;
	
	// 外设寄存器只有一个，地址不用递增
	DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Disable;

	// 存储器地址固定
	DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Enable; 
	
	// 外设数据大小为半字，即两个字节
	DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word;
	
	// 存储器数据大小也为半字，跟外设数据大小相同
	DMA_InitStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_Word;
	
	// 循环传输模式
	DMA_InitStruct.DMA_Mode = DMA_Mode_Circular;	
	
	// DMA 传输通道优先级为高，当使用一个DMA通道时，优先级设置不影响
	DMA_InitStruct.DMA_Priority = DMA_Priority_High;
	
	// 禁止存储器到存储器模式，因为是从外设到存储器
	DMA_InitStruct.DMA_M2M = DMA_M2M_Disable;
	
	// 初始化DMA
	DMA_Init(ADC_DMA_CHANNEL, &DMA_InitStruct);
	
	// 使能 DMA 通道
	DMA_Cmd(ADC_DMA_CHANNEL , ENABLE);
	
	
	ADC_InitTypeDef  ADC_InitStruct;
	ADCx_1_APBxClock_FUN(ADCx_1_CLK,ENABLE);
	// 连续转换模式 
	ADC_InitStruct.ADC_ContinuousConvMode =  ENABLE ;
	// 转换结果右对齐
	ADC_InitStruct.ADC_DataAlign =   ADC_DataAlign_Right ;
	// 不用外部触发转换，软件开启即可
	ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None ; 
	// 双ADC的规则同步
	ADC_InitStruct.ADC_Mode =  ADC_Mode_RegSimult ; 
	// 转换通道6个
	ADC_InitStruct.ADC_NbrOfChannel = NOFCHANEL ;
	// 扫描模式，多通道要
	ADC_InitStruct.ADC_ScanConvMode =  ENABLE ;
	ADC_Init(ADCx_1, &ADC_InitStruct);	
	// 配置ADC时钟Ｎ狿CLK2的8分频，即9MHz
	RCC_ADCCLKConfig(RCC_PCLK2_Div8); 	
	// 配置ADC 通道的转换顺序和采样时间
	ADC_RegularChannelConfig(ADCx_1, ADCx_1_CHANNEL, 1, 
	                         ADC_SampleTime_239Cycles5);	
	// 使能ADC DMA 请求
	ADC_DMACmd(ADCx_1, ENABLE);
	
	
	//ADC2
	ADCx_2_APBxClock_FUN(ADCx_2_CLK,ENABLE);
	// 连续转换模式 
	ADC_InitStruct.ADC_ContinuousConvMode =  ENABLE ;
	// 转换结果右对齐
	ADC_InitStruct.ADC_DataAlign =   ADC_DataAlign_Right ;
	// 不用外部触发转换，软件开启即可
	ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	// 双ADC的规则同步
	ADC_InitStruct.ADC_Mode =  ADC_Mode_RegSimult ; 
	// 转换通道6个
	ADC_InitStruct.ADC_NbrOfChannel = NOFCHANEL ;
	// 扫描模式，多通道要
	ADC_InitStruct.ADC_ScanConvMode =  ENABLE ;
	ADC_Init(ADCx_2, &ADC_InitStruct);	
	// 配置ADC时钟为PCLK2的8分频，即9MHz
	RCC_ADCCLKConfig(RCC_PCLK2_Div8); 	
	// 配置ADC 通道的转换顺序和采样时间
	ADC_RegularChannelConfig(ADCx_2, ADCx_2_CHANNEL, 1, 
	                         ADC_SampleTime_239Cycles5);
	/* 使能ADCx_2的外部触发转换 */
	ADC_ExternalTrigConvCmd(ADC2, ENABLE);
	
	/* ----------------ADCx_1 校准--------------------- */
	// 开启ADC ，并开始转换
	ADC_Cmd(ADCx_1, ENABLE);	
	// 初始化ADC 校准寄存器  
	ADC_ResetCalibration(ADCx_1);
	// 等待校准寄存器初始化完成
	while(ADC_GetResetCalibrationStatus(ADCx_1));	
	// ADC开始校准
	ADC_StartCalibration(ADCx_1);
	// 等待校准完成
	while(ADC_GetCalibrationStatus(ADCx_1));
	
	/* ----------------ADCx_2 校准--------------------- */
		// 开启ADC ，并开始转换
	ADC_Cmd(ADCx_2, ENABLE);	
	// 初始化ADC 校准寄存器  
	ADC_ResetCalibration(ADCx_2);
	// 等待校准寄存器初始化完成
	while(ADC_GetResetCalibrationStatus(ADCx_2));	
	// ADC开始校准
	ADC_StartCalibration(ADCx_2);
	// 等待校准完成
	while(ADC_GetCalibrationStatus(ADCx_2));

	// 由于没有采用外部触发，所以使用软件触发ADC转换 
	/* 使能ADCx_2的外部触发转换 */
	ADC_ExternalTrigConvCmd(ADC2, ENABLE);
	// 由于没有采用外部触发，所以使用软件触发ADC转换 
	ADC_SoftwareStartConvCmd(ADCx_1, ENABLE);
	
	
}	



void ADCx_Init(void)
{
	ADCx_GPIO_Config();
	ADC_Mode_Config();
}









