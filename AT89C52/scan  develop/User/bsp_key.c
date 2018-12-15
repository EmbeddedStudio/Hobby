#include "bsp_key.h" 
#include "bsp_delay.h" 

sbit K2 = P3^4;
sbit K3 = P3^5;
sbit K4 = P3^6;
sbit K5 = P3^7;

extern u8 location;
extern u8 flag;
extern u8 wei;
void key_scan()
{
	
	if(0 == K4)
	{
		// 按键消抖
		delay_ms(1);
		if(0 == K4)
		{
			if(9 != location)
			{
				location = location +1;
			}
		}
		
		// 松手检测
		while(0 == K4);
		
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
		while(0 == K3);
		
	}

	if(0 == K2)
	{
		// 按键消抖
		delay_ms(1);
		if(0 == K2)
		{
			if(0 != location)
			{
				location = location - 1;
			}
		}
		
		// 松手检测
		while(0 == K2);
	}
	if(0 == K5)
	{
		// 按键消抖
		delay_ms(1);
		if(0 == K5)
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
		while(0 == K5);
	}
}