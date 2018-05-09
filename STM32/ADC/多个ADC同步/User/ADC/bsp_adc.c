#include "bsp_adc.h"

__IO uint16_t ADC_ConvertedValue[NOFCHANEL]={0};

static void ADCx_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	// ADCx_1 GPIO ��ʼ��
	ADCx_1_GPIO_APBxClock_FUN ( ADCx_1_GPIO_CLK, ENABLE );
	GPIO_InitStruct.GPIO_Pin = ADCx_1_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(ADCx_1_PORT, &GPIO_InitStruct);

	// ADCx_2 GPIO ��ʼ��
	ADCx_1_GPIO_APBxClock_FUN ( ADCx_2_GPIO_CLK, ENABLE );
	GPIO_InitStruct.GPIO_Pin = ADCx_2_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(ADCx_2_PORT, &GPIO_InitStruct);	
}

static void ADC_Mode_Config(void)
{
	DMA_InitTypeDef DMA_InitStruct;
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	
	// ��λDMA������
	DMA_DeInit(ADC_DMA_CHANNEL);
	
	// ���� DMA ��ʼ���ṹ��
	// �����ַΪ��ADC ���ݼĴ�����ַ
	DMA_InitStruct.DMA_PeripheralBaseAddr = ( uint32_t ) ( & ( ADCx_1->DR ) );
	
	// �洢����ַ��ʵ���Ͼ���һ���ڲ�SRAM�ı���
	DMA_InitStruct.DMA_MemoryBaseAddr = (uint32_t)ADC_ConvertedValue;
	
	// ����Դ��������
	DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralSRC;
	
	// ��������СΪ1���������Ĵ�СӦ�õ��ڴ洢���Ĵ�С
	DMA_InitStruct.DMA_BufferSize = NOFCHANEL;
	
	// ����Ĵ���ֻ��һ������ַ���õ���
	DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Disable;

	// �洢����ַ�̶�
	DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Enable; 
	
	// �������ݴ�СΪ���֣��������ֽ�
	DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word;
	
	// �洢�����ݴ�СҲΪ���֣����������ݴ�С��ͬ
	DMA_InitStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_Word;
	
	// ѭ������ģʽ
	DMA_InitStruct.DMA_Mode = DMA_Mode_Circular;	
	
	// DMA ����ͨ�����ȼ�Ϊ�ߣ���ʹ��һ��DMAͨ��ʱ�����ȼ����ò�Ӱ��
	DMA_InitStruct.DMA_Priority = DMA_Priority_High;
	
	// ��ֹ�洢�����洢��ģʽ����Ϊ�Ǵ����赽�洢��
	DMA_InitStruct.DMA_M2M = DMA_M2M_Disable;
	
	// ��ʼ��DMA
	DMA_Init(ADC_DMA_CHANNEL, &DMA_InitStruct);
	
	// ʹ�� DMA ͨ��
	DMA_Cmd(ADC_DMA_CHANNEL , ENABLE);
	
	
	ADC_InitTypeDef  ADC_InitStruct;
	ADCx_1_APBxClock_FUN(ADCx_1_CLK,ENABLE);
	// ����ת��ģʽ 
	ADC_InitStruct.ADC_ContinuousConvMode =  ENABLE ;
	// ת������Ҷ���
	ADC_InitStruct.ADC_DataAlign =   ADC_DataAlign_Right ;
	// �����ⲿ����ת���������������
	ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None ; 
	// ˫ADC�Ĺ���ͬ��
	ADC_InitStruct.ADC_Mode =  ADC_Mode_RegSimult ; 
	// ת��ͨ��6��
	ADC_InitStruct.ADC_NbrOfChannel = NOFCHANEL ;
	// ɨ��ģʽ����ͨ��Ҫ
	ADC_InitStruct.ADC_ScanConvMode =  ENABLE ;
	ADC_Init(ADCx_1, &ADC_InitStruct);	
	// ����ADCʱ�ӣΪPCLK2��8��Ƶ����9MHz
	RCC_ADCCLKConfig(RCC_PCLK2_Div8); 	
	// ����ADC ͨ����ת��˳��Ͳ���ʱ��
	ADC_RegularChannelConfig(ADCx_1, ADCx_1_CHANNEL, 1, 
	                         ADC_SampleTime_239Cycles5);	
	// ʹ��ADC DMA ����
	ADC_DMACmd(ADCx_1, ENABLE);
	
	
	//ADC2
	ADCx_2_APBxClock_FUN(ADCx_2_CLK,ENABLE);
	// ����ת��ģʽ 
	ADC_InitStruct.ADC_ContinuousConvMode =  ENABLE ;
	// ת������Ҷ���
	ADC_InitStruct.ADC_DataAlign =   ADC_DataAlign_Right ;
	// �����ⲿ����ת���������������
	ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	// ˫ADC�Ĺ���ͬ��
	ADC_InitStruct.ADC_Mode =  ADC_Mode_RegSimult ; 
	// ת��ͨ��6��
	ADC_InitStruct.ADC_NbrOfChannel = NOFCHANEL ;
	// ɨ��ģʽ����ͨ��Ҫ
	ADC_InitStruct.ADC_ScanConvMode =  ENABLE ;
	ADC_Init(ADCx_2, &ADC_InitStruct);	
	// ����ADCʱ��ΪPCLK2��8��Ƶ����9MHz
	RCC_ADCCLKConfig(RCC_PCLK2_Div8); 	
	// ����ADC ͨ����ת��˳��Ͳ���ʱ��
	ADC_RegularChannelConfig(ADCx_2, ADCx_2_CHANNEL, 1, 
	                         ADC_SampleTime_239Cycles5);
	/* ʹ��ADCx_2���ⲿ����ת�� */
	ADC_ExternalTrigConvCmd(ADC2, ENABLE);
	
	/* ----------------ADCx_1 У׼--------------------- */
	// ����ADC ������ʼת��
	ADC_Cmd(ADCx_1, ENABLE);	
	// ��ʼ��ADC У׼�Ĵ���  
	ADC_ResetCalibration(ADCx_1);
	// �ȴ�У׼�Ĵ�����ʼ�����
	while(ADC_GetResetCalibrationStatus(ADCx_1));	
	// ADC��ʼУ׼
	ADC_StartCalibration(ADCx_1);
	// �ȴ�У׼���
	while(ADC_GetCalibrationStatus(ADCx_1));
	
	/* ----------------ADCx_2 У׼--------------------- */
		// ����ADC ������ʼת��
	ADC_Cmd(ADCx_2, ENABLE);	
	// ��ʼ��ADC У׼�Ĵ���  
	ADC_ResetCalibration(ADCx_2);
	// �ȴ�У׼�Ĵ�����ʼ�����
	while(ADC_GetResetCalibrationStatus(ADCx_2));	
	// ADC��ʼУ׼
	ADC_StartCalibration(ADCx_2);
	// �ȴ�У׼���
	while(ADC_GetCalibrationStatus(ADCx_2));

	// ����û�в����ⲿ����������ʹ���������ADCת�� 
	/* ʹ��ADCx_2���ⲿ����ת�� */
	ADC_ExternalTrigConvCmd(ADC2, ENABLE);
	// ����û�в����ⲿ����������ʹ���������ADCת�� 
	ADC_SoftwareStartConvCmd(ADCx_1, ENABLE);
	
	
}	



void ADCx_Init(void)
{
	ADCx_GPIO_Config();
	ADC_Mode_Config();
}









