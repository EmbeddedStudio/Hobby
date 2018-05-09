#include "bsp_adc.h"

static void ADCx_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	ADC_GPIO_APBxClock_FUN(ADC_GPIO_CLK,ENABLE);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_InitStruct.GPIO_Pin = ADC_PIN;
	
	GPIO_Init(ADC_PORT,&GPIO_InitStruct);
}

static void ADC_Mode_Config(void)
{
	ADC_InitTypeDef ADC_InitStruct;
	
	ADC_APBxClock_FUN(ADC_CLK,ENABLE);
	
	// ����ת��ģʽ 
	ADC_InitStruct.ADC_ContinuousConvMode =  ENABLE ;
	// ת������Ҷ���
	ADC_InitStruct.ADC_DataAlign =   ADC_DataAlign_Right ;
	// �����ⲿ����ת���������������
	ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None ; 
	// ֻʹ��һ��ADC�����ڶ���ģʽ
	ADC_InitStruct.ADC_Mode =  ADC_Mode_Independent ; 
	// ת��ͨ��1��
	ADC_InitStruct.ADC_NbrOfChannel = 1 ;
	// ��ֹɨ��ģʽ����ͨ����Ҫ����ͨ������Ҫ
	ADC_InitStruct.ADC_ScanConvMode =  DISABLE ;
	// ��ʼ��ADC
	ADC_Init(ADC_x, &ADC_InitStruct);
	
	// ����ADCʱ��ΪPCLK2��8��Ƶ����9MHz
	RCC_ADCCLKConfig(RCC_PCLK2_Div8); 
	
	// ���� ADC ͨ��ת��˳��Ͳ���ʱ��
	ADC_RegularChannelConfig(ADC_x, ADC_CHANNEL, 1, 
	                         ADC_SampleTime_55Cycles5);
	
	// ADC ת�����������жϣ����жϷ�������ж�ȡת��ֵ
	ADC_ITConfig(ADC_x, ADC_IT_EOC, ENABLE);
	
	// ����ADC ������ʼת��
	ADC_Cmd(ADC_x, ENABLE);
	
	// ��ʼ��ADC У׼�Ĵ���  
	ADC_ResetCalibration(ADC_x);
	// �ȴ�У׼�Ĵ�����ʼ�����
	while(ADC_GetResetCalibrationStatus(ADC_x));
	// ADC��ʼУ׼
	ADC_StartCalibration(ADC_x);
	// �ȴ�У׼���
	while(ADC_GetCalibrationStatus(ADC_x));
	
	// ����û�в����ⲿ����������ʹ���������ADCת�� 
	ADC_SoftwareStartConvCmd(ADC_x, ENABLE);
}	

static void ADC_NVIC_Config(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	// ���ȼ�����
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

	// �����ж����ȼ�
	NVIC_InitStructure.NVIC_IRQChannel = ADC_IRQ;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

void ADCx_Init(void)
{
	ADCx_GPIO_Config();
	ADC_Mode_Config();
	ADC_NVIC_Config();
}









