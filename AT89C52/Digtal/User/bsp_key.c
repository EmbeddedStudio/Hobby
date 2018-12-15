#include "bsp_key.h" 
#include "bsp_delay.h" 

sbit s3 = P3^5;

extern u8 num;

void key_scan()
{
	if(0 == s3)
	{
		// 按键消抖
		delay_ms(1);
		if(0 == s3)
		{
			if(num < 9)
				num = num+1;
		}
		
		// 松手检测
		while(0 == s3);
		
	}
	
}