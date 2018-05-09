#include "stm32f10x.h"   
#include "bsp_led.h"
#include "bsp_usart.h"
#include "bsp_adc.h"

extern __IO uint16_t ADC_ConvertedValue[NOFCHANEL];

float ADC_ConvertedValueLocal[NOFCHANEL]; 


// 软件延时
void Delay(__IO uint32_t nCount)
{
  for(; nCount != 0; nCount--);
}


int main(void)
{		
	uint16_t temp0=0 ,temp1=0;
	
	USART_Config ();
	
	ADCx_Init();
	
	while (1)
	{	
		// 取出ADC1数据寄存器的高16位，这个是ADC2的转换数据
		temp0 = (ADC_ConvertedValue[0]&0XFFFF0000) >> 16;
		// 取出ADC1数据寄存器的低16位，这个是ADC1的转换数据
		temp1 = (ADC_ConvertedValue[0]&0XFFFF);	
		
		ADC_ConvertedValueLocal[0] =(float) temp0/4096*3.3;
		ADC_ConvertedValueLocal[1] =(float) temp1/4096*3.3;
		
		printf("\r\n ADCx_1 value = %f V \r\n",
		        ADC_ConvertedValueLocal[1]);
		printf("\r\n ADCx_2 value = %f V \r\n",
		        ADC_ConvertedValueLocal[0]);
		
		printf("\r\n\r\n");
		Delay(0xffffee); 
		 
	}
	
}

