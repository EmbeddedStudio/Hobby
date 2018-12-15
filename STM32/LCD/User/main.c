#include "stm32f10x.h"   
#include "bsp_usart.h"   
#include "bsp_lcd.h"
#include "fonts.h"
#include "bsp_spi.h"
#include <stdio.h>
extern uint16_t LCD_X_LENGTH;
extern uint16_t LCD_Y_LENGTH;

int main(void)
{	
	char dispBuff[100];
	char *pStr = 0;
	
	LCD_Init();
	
	USART_Config ();
	
	printf("\r\n ����һ��LCDʵ�� \r\n");
	
	printf("\r\n 0x0c������ز���  0x%x",Read_Format());
	
	LCD_SetFont(&Font8x16);

	LCD_SetColors(RED,GREEN);
	
	LCD_Clear(0,0,LCD_X_LENGTH,LCD_Y_LENGTH);

	LCD_DispStringLine_EN_CH(LINE(1),"aa�¼α�aa");
	
	LCD_DisplayStringEx(36,36,36,36,"aa�¼α�bb",0);

	pStr = "ABCDEF";
	//����ʱ��Ҫ����Ŀո���� = (Һ�����/���������� - �ַ�������)/2
	sprintf(dispBuff,"%*c%s",((LCD_X_LENGTH/(((sFONT *)LCD_GetFont())->Width))-strlen(pStr))/2,' ',pStr);
	LCD_ClearLine(LINE(6));													// ����������� 
	LCD_DispStringLine_EN_CH(LINE(6),dispBuff);//��ʾ��ʽ������ַ���
	
	pStr = "���ľ���ʾ��";
	//����ʱ��Ҫ����Ŀո���� = (Һ�����/������ - �ַ�������)/2
	//strlen���㳤��ʱ��һ�����ĵ���2���ֽڣ���2��Ӣ���ַ������Ҳ������Ӣ�Ŀո�
	//������(WIDTH_CH_CHAR/2)������������
	sprintf(dispBuff,"%*c%s",(LCD_X_LENGTH/(WIDTH_CH_CHAR/2)-strlen(pStr))/2,' ',pStr);
	LCD_ClearLine(LINE(15));													// ����������� 
	LCD_DispStringLine_EN_CH(LINE(15),dispBuff);
	
	while(1);
	
}


