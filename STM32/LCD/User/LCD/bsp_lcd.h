#ifndef __BSP_LCD_H
#define __BSP_LCD_H

#include "stm32f10x.h"	
#include "fonts.h"

/********LCD��������************/
#define      FSMC_Bank_NORSRAMx		 FSMC_Bank1_NORSRAM1

#define      ILI9341_CMD_ADDR  		        (__IO uint16_t*)(0x60000000)
#define      ILI9341_DATA_ADDR  		(__IO uint16_t*)(0x60020000)

#define      LCD_CS_CLK                          RCC_APB2Periph_GPIOD  
#define      LCD_CS_GPIO_PORT                    GPIOD
#define      LCD_CS_GPIO_PIN                     GPIO_Pin_7

#define      LCD_RD_CLK                          RCC_APB2Periph_GPIOD  
#define      LCD_RD_GPIO_PORT                    GPIOD
#define      LCD_RD_GPIO_PIN                     GPIO_Pin_4

#define      LCD_WE_CLK                          RCC_APB2Periph_GPIOD  
#define      LCD_WE_GPIO_PORT                    GPIOD
#define      LCD_WE_GPIO_PIN                     GPIO_Pin_5

#define      LCD_RS_CLK                          RCC_APB2Periph_GPIOD  
#define      LCD_RS_GPIO_PORT                    GPIOD
#define      LCD_RS_GPIO_PIN                     GPIO_Pin_11

#define      LCD_RESTE_CLK                       RCC_APB2Periph_GPIOE  
#define      LCD_RESTE_GPIO_PORT                 GPIOE
#define      LCD_RESTE_GPIO_PIN                  GPIO_Pin_1

#define      LCD_BL_CLK                          RCC_APB2Periph_GPIOD  
#define      LCD_BL_GPIO_PORT                    GPIOD
#define      LCD_BL_GPIO_PIN                     GPIO_Pin_12

/********LCD������************/

#define      ILI9341_D0_CLK                RCC_APB2Periph_GPIOD   
#define      ILI9341_D0_PORT               GPIOD
#define      ILI9341_D0_PIN                GPIO_Pin_14

#define      ILI9341_D1_CLK                RCC_APB2Periph_GPIOD   
#define      ILI9341_D1_PORT               GPIOD
#define      ILI9341_D1_PIN                GPIO_Pin_15

#define      ILI9341_D2_CLK                RCC_APB2Periph_GPIOD   
#define      ILI9341_D2_PORT               GPIOD
#define      ILI9341_D2_PIN                GPIO_Pin_0

#define      ILI9341_D3_CLK                RCC_APB2Periph_GPIOD  
#define      ILI9341_D3_PORT               GPIOD
#define      ILI9341_D3_PIN                GPIO_Pin_1

#define      ILI9341_D4_CLK                RCC_APB2Periph_GPIOE   
#define      ILI9341_D4_PORT               GPIOE
#define      ILI9341_D4_PIN                GPIO_Pin_7

#define      ILI9341_D5_CLK                RCC_APB2Periph_GPIOE   
#define      ILI9341_D5_PORT               GPIOE
#define      ILI9341_D5_PIN                GPIO_Pin_8

#define      ILI9341_D6_CLK                RCC_APB2Periph_GPIOE   
#define      ILI9341_D6_PORT               GPIOE
#define      ILI9341_D6_PIN                GPIO_Pin_9

#define      ILI9341_D7_CLK                RCC_APB2Periph_GPIOE  
#define      ILI9341_D7_PORT               GPIOE
#define      ILI9341_D7_PIN                GPIO_Pin_10

#define      ILI9341_D8_CLK                RCC_APB2Periph_GPIOE   
#define      ILI9341_D8_PORT               GPIOE
#define      ILI9341_D8_PIN                GPIO_Pin_11

#define      ILI9341_D9_CLK                RCC_APB2Periph_GPIOE   
#define      ILI9341_D9_PORT               GPIOE
#define      ILI9341_D9_PIN                GPIO_Pin_12

#define      ILI9341_D10_CLK                RCC_APB2Periph_GPIOE   
#define      ILI9341_D10_PORT               GPIOE
#define      ILI9341_D10_PIN                GPIO_Pin_13

#define      ILI9341_D11_CLK                RCC_APB2Periph_GPIOE   
#define      ILI9341_D11_PORT               GPIOE
#define      ILI9341_D11_PIN                GPIO_Pin_14

#define      ILI9341_D12_CLK                RCC_APB2Periph_GPIOE   
#define      ILI9341_D12_PORT               GPIOE
#define      ILI9341_D12_PIN                GPIO_Pin_15

#define      ILI9341_D13_CLK                RCC_APB2Periph_GPIOD   
#define      ILI9341_D13_PORT               GPIOD
#define      ILI9341_D13_PIN                GPIO_Pin_8

#define      ILI9341_D14_CLK                RCC_APB2Periph_GPIOD   
#define      ILI9341_D14_PORT               GPIOD
#define      ILI9341_D14_PIN                GPIO_Pin_9

#define      ILI9341_D15_CLK                RCC_APB2Periph_GPIOD   
#define      ILI9341_D15_PORT               GPIOD
#define      ILI9341_D15_PIN                GPIO_Pin_10

/*************************************** ����Ԥ�� ******************************************/
#define      DEBUG_DELAY()                

/***************************** ILI934 ��ʾ�������ʼ������������� ***************************/
#define      ILI9341_DispWindow_X_Star	        0     //��ʼ���X����
#define      ILI9341_DispWindow_Y_Star	        0     //��ʼ���Y����

#define      ILI9341_LESS_PIXEL	  		240	//Һ�����϶̷�������ؿ���
#define      ILI9341_MORE_PIXEL	 		320	//Һ�����ϳ���������ؿ���



/******************************* ���� ILI934 ��ʾ��������ɫ ********************************/
#define      BACKGROUND		                WHITE   //Ĭ�ϱ�����ɫ

#define      WHITE			   0xFFFF	   //��ɫ
#define      BLACK                         0x0000	   //��ɫ 
#define      GREY                          0xF7DE	   //��ɫ 
#define      BLUE                          0x001F	   //��ɫ 
#define      BLUE2                         0x051F	   //ǳ��ɫ 
#define      RED                           0xF800	   //��ɫ 
#define      MAGENTA                       0xF81F	   //����ɫ�����ɫ 
#define      GREEN                         0x07E0	   //��ɫ 
#define      CYAN                          0x7FFF	   //����ɫ����ɫ 
#define      YELLOW                        0xFFE0	   //��ɫ 
#define      BRED                          0xF81F
#define      GRED                          0xFFE0
#define      GBLUE                         0x07FF

#define RGB888_2_RGB565(R,G,B)		 (uint16_t)(((R & 0x1F) << 11) | ((G & 0x3F) << 5) | (B & 0x1F) )


/******************************* ���� ILI934 �������� ********************************/
#define      CMD_SetCoordinateX		 	0x2A	     //����X����
#define      CMD_SetCoordinateY		 	0x2B	     //����Y����
#define      CMD_SetPixel		 	0x2C	     //�������

/********************************** ���� ILI934 ���� ***************************************/
void LCD_Init(void);
uint8_t Read_Format(void);
void LCD_OpenWindow(uint16_t usX,uint16_t usY,uint16_t usWidth,uint16_t usHeight);
void LCD_DispChar_EN ( uint16_t usX, uint16_t usY, const char cChar );
void LCD_DispStringLine_EN (  uint16_t line,  char * pStr );
void LCD_DispChar_CH ( uint16_t usX, uint16_t usY, uint16_t usChar );
void LCD_GramScan ( uint8_t ucOption );
void LCD_DispString_CH ( uint16_t usX , uint16_t usY, char * pStr );
void LCD_DispString_EN_CH ( uint16_t usX , uint16_t usY, char * pStr );
void LCD_DispStringLine_EN_CH (  uint16_t line, char * pStr );
void LCD_Clear ( uint16_t usX, uint16_t usY, uint16_t usWidth, uint16_t usHeight );
void LCD_ClearLine(uint16_t Line);
void LCD_SetPointPixel ( uint16_t usX, uint16_t usY );
void LCD_SetColors(uint16_t TextColor, uint16_t BackColor) ;
void LCD_SetFont(sFONT *fonts);
sFONT *LCD_GetFont(void);
void LCD_DrawChar_Ex(uint16_t usX, uint16_t usY, uint16_t Font_width, uint16_t Font_Height,uint8_t *c,uint16_t DrawModel);
void LCD_DisplayStringEx(uint16_t x,  uint16_t y,uint16_t Font_width,uint16_t Font_Height,	uint8_t *ptr,uint16_t DrawModel) ;
void LCD_zoomChar(uint16_t in_width,uint16_t in_heig,uint16_t out_width,	
			uint16_t out_heig,uint8_t *in_ptr,uint8_t *out_ptr, uint8_t en_cn);


#endif /* __BSP_LCD_H*/