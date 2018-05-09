#include "bsp_delay.h" 
#define uchar unsigned char
	
extern uchar temp;
void delay_ms(u8 ms)
{
	u32 temp;
	
	for( ; ms > 0; ms--)
	{
		for(temp = 500; temp > 0; temp--);
	}
}