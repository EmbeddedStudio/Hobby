#include <reg51.h>
#include "bsp_delay.h"
#include "bsp_key.h"


#define u32 unsigned int 
#define u8 unsigned char 
	
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
	IT0=1;
	IT1=1;
	EA=1;
	EX0=1;
	P1 = 0xfe;
	while(1)
	{
		P1 = ~location;
		delay_ms(50);
		if(FLIKER_ON == flag)
		{
			P1 = 0xff;
			delay_ms(50);
		}
	}
}



void exter0() interrupt 0
{
	key_scan();
}

