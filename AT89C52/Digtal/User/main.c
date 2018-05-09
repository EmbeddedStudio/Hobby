#include <reg51.h>
#include "bsp_delay.h"
#include "bsp_key.h"


#define u32 unsigned int 
#define u8 unsigned char 

u8 num = 0;
 
u8 table[]={
0x3f,0x06,0x5b,0x4f,
0x66,0x6d,0x7d,0x07,
0x7f,0x6f,0x77,};

void main()
{
	IT0=1;
	EA=1;
	EX0=1;
	while(1)
	{
		P0=~table[num];
	}
}



void exter0() interrupt 0
{
	key_scan();
}

