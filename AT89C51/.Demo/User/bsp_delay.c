#include "bsp_delay.h" 

void delay(u8 ms)
{
        u32 temp;
        
        for( ; ms > 0; ms--)
        {
                for(temp = 100; temp > 0; temp--);
        }
}