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
	
	printf("\r\n 这是一个LCD实验 \r\n");
	
	printf("\r\n 0x0c的命令返回测试  0x%x",Read_Format());
	
	LCD_SetFont(&Font8x16);

	LCD_SetColors(RED,GREEN);
	
	LCD_Clear(0,0,LCD_X_LENGTH,LCD_Y_LENGTH);

	LCD_DispStringLine_EN_CH(LINE(1),"aa陈嘉彬aa");
	
	LCD_DisplayStringEx(36,36,36,36,"aa陈嘉彬bb",0);

	pStr = "ABCDEF";
	//居中时，要插入的空格个数 = (液晶宽度/单个字体宽度 - 字符串长度)/2
	sprintf(dispBuff,"%*c%s",((LCD_X_LENGTH/(((sFONT *)LCD_GetFont())->Width))-strlen(pStr))/2,' ',pStr);
	LCD_ClearLine(LINE(6));													// 清除单行文字 
	LCD_DispStringLine_EN_CH(LINE(6),dispBuff);//显示格式化后的字符串
	
	pStr = "中文居中示例";
	//居中时，要插入的空格个数 = (液晶宽度/字体宽度 - 字符串长度)/2
	//strlen计算长度时，一个中文等于2个字节，即2个英文字符，而且插入的是英文空格
	//所以用(WIDTH_CH_CHAR/2)来计算字体宽度
	sprintf(dispBuff,"%*c%s",(LCD_X_LENGTH/(WIDTH_CH_CHAR/2)-strlen(pStr))/2,' ',pStr);
	LCD_ClearLine(LINE(15));													// 清除单行文字 
	LCD_DispStringLine_EN_CH(LINE(15),dispBuff);
	
	while(1);
	
}


