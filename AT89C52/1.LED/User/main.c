#include <reg51.h>
#include "bsp_delay.h" 

#define u32 unsigned int 
#define u8 unsigned char 

void key_scan();

// MVC Model View Control
	
sbit S2 = P3^4;
sbit S3 = P3^5;
sbit S4 = P3^6;

#define FLIKER_ON 1
#define FLIKER_OFF 0
	
u8 location = 0x01;
u8 flag = FLIKER_OFF;


void main()
{
//	IT0=1;
//	IT1=1;
//	EA=1;
//	EX0=1;
	P1 = 0xfe;
	while(1)
	{
//		P1 = ~location;
	}
}

void key_scan()
{
	
	if(0 == S4)
	{
		// 按键消抖
		delay_ms(1);
		if(0 == S4)
		{
			if(0x80 != location)
			{
				location = location << 1;
			}
		}
		
		// 松手检测
		while(0 == S4);
		
	}
	
	if(0 == S3)
	{
		// 按键消抖
		delay_ms(1);
		if(0 == S3)
		{
			flag = !flag;
		}
		
		// 松手检测
		while(0 == S3);
		
	}

	if(0 == S2)
	{
		delay_ms(1);
		if(0 == S2)
		{
			if(0x01 != location)
			{
				location = location >> 1;
			}
		}
		
		// 松手检测
		while(0 == S2);
	}
}

void exter0() interrupt 0
{
	key_scan();
	delay_ms(50);
	if(FLIKER_ON == flag)
		{
			P1 = 0xff;
			delay_ms(50);
		}
}

