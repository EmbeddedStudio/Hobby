#include "bsp_delay.h" 
#include <reg52.h>

void delay(u8 ms)
{
        u16 temp;
        
        for( ; ms > 0; ms--)
        {
                for(temp = 1000; temp > 0; temp--);
        }
}