#include "bsp_tube.h"
#include "bsp_delay.h" 
unsigned char table[]=
{0x3f,0x06,0x5b,0x4f,
0x66,0x6d,0x7d,0x07,
0x7f,0x6f,0x77};

unsigned char selected[]=
{0xff,0xfe,0xfd,0xfb,0xf7,
0xef,0xdf,0xbf,0x7f};

unsigned char number[]={0,0,0,0,0,0};
	
unsigned char i,j;
	
void tube(unsigned int num )
{	
	number[0]=(num/10000);
	number[1]=((num%10000)/1000);       
	number[2]=((num%1000)/100);	      
	number[3]=((num%100)/10);		
	number[4]=(num%10);		

	for(i=0;i<6;i++)//Ñ­»·6Î»
	{	
		P0 = table[ number[i-1] ];
		dula=1;
		dula=0;
		P0 = selected[i];
		wela=1;
		wela=0;
		delay_ms(1);
	}

}





