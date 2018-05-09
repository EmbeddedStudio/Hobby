#include <reg51.h>

#define u32 unsigned int 
#define u8 unsigned char 
#define FLIKER_ON 0
#define FLIKER_OFF 1
void delay_ms(u32 ms);
u8 loction,b;
u8 flag = FLIKER_OFF;
void main()
{
	while(1)
	{
		P0 = 0;
		
		delay_ms(100);
		
		P0 = 255;
		
		delay_ms(100);
	}	
	
	
	
}

//void delay(b)   
//{ 
//    u8 a; 
//    for(;b>0;b--) 
//        for(a=1000;a>0;a--); 
//} 





void delay_ms(u32 ms)
{
	u32 temp;
	
	for( ; ms > 0; ms--)
	{
		for(temp = 1000; temp > 0; temp--);
	}
}