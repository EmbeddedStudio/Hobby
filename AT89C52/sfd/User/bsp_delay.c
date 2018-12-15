#include "bsp_delay.h" 

void delay_ms(u8 ms)
{
	u32 temp;
	
	for( ; ms > 0; ms--)
	{
		for(temp = 1000; temp > 0; temp--);
	}
}