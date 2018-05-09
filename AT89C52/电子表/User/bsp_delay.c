#include "bsp_delay.h" 

void delay_ms(u8 ms)
{
	u16 temp;
	
	for( ; ms > 0; ms--)
	{
		for(temp = 100; temp > 0; temp--);
	}
}