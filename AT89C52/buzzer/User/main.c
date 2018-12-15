#include <reg51.h>
#include "bsp_delay.h" 

#define u32 unsigned int 
#define u8 unsigned char 
// MVC Model View Control
	
sbit S = P2^3;

sbit a = P0^0;


void main()
{

	while(1)
	{
		S=0;
	  delay_ms(100);
	  S=1;
	  delay_ms(100);

		
		a=0;
		delay_ms(100);
		a=1;
		delay_ms(100);
		
		
	}

}


