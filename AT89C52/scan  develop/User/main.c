#include <reg51.h>
#include "bsp_delay.h"

#define u32 unsigned int 
#define u8 unsigned char 

// MVC Model View Control
sbit dula=P2^6;
sbit wela=P2^7;
sbit s2 = P3^4;
sbit s3 = P3^5;
sbit s4 = P3^6;
sbit s5 = P3^7;
#define FLIKER_ON 1
#define FLIKER_OFF 0
	
void key_scan();
u8 flag = FLIKER_OFF;

u8 location,num,wei;
selected[]={
0xff,0xfe,0xfd,0xfb,
0xf7,0xef,0xdf,};
table[]={
0x3f,0x06,0x5b,0x4f,
0x66,0x6d,0x7d,0x07,
0x7f,0x6f,0x77,};
void main()
{
	wei=1;
	location=0;
	while(1)
	{
		
		wela=1;
		P0 = selected[wei];
		wela=0;
		dula=1;
		P0 = table[location];
		dula=0;
		
		delay_ms(50);
		key_scan();
		if(FLIKER_ON == flag)
		{
			wela=1;
			P0 = selected[wei];
			wela=0;
			delay_ms(50);
		}
	}
}

void key_scan()
{
	
	if(0 == s4)
	{
		// 按键消抖
		delay_ms(1);
		if(0 == s4)
		{
			if(0==wei)
			{
				if(9 != location)
				{
					location = location +1;
				}
			}
		}
		
		// 松手检测
		while(0 == s4);
		
	}
	
	if(0 == s3)
	{
		// 按键消抖
		delay_ms(1);
		if(0 == s3)
		{
			flag = !flag;
		}
		
		// 松手检测
		while(0 == s3);
		
	}

	if(0 == s2)
	{
		// 按键消抖
		delay_ms(1);
		if(0 == s2)
		{
			if(0 != location)
			{
				location = location - 1;
			}
		}
		
		// 松手检测
		while(0 == s2);
	}
	if(0 == s5)
	{
		// 按键消抖
		delay_ms(1);
		if(0 == s5)
		{
			if(6 != wei)
			{
				wei = wei + 1;
			}
			else if (6==wei)
			{
				wei=wei-5;
			}	
		}
		
		// 松手检测
		while(0 == s5);
	}
}



