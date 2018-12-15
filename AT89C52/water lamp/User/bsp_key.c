#include "bsp_key.h" 
#include "bsp_delay.h" 

sbit K2 = P3^4;
sbit K3 = P3^5;
sbit K4 = P3^6;

extern u8 location;
extern u8 flag;

void key_scan()
{
	
	if(0 == K4)
	{
		// 按键消抖
		delay_ms(1);
		if(0 == K4)
		{
			if(0x80 != location)
			{
				location = location << 1;
			}
		}
		
		// 松手检测
//		while(0 == K4);
		
	}
	
	if(0 == K3)
	{
		// 按键消抖
		delay_ms(1);
		if(0 == K3)
		{
			flag = !flag;
		}
		
		// 松手检测
//		while(0 == K3);
		
	}

	if(0 == K2)
	{
		delay_ms(1);
		if(0 == K2)
		{
			if(0x01 != location)
			{
				location = location >> 1;
			}
		}
		
		// 松手检测
//		while(0 == K2);
	}
}