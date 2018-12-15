#include <reg52.h>
#include "bsp_delay.h"       

sbit Motor0 = P2^0;
sbit Motor1 = P2^1;
sbit Motor2 = P2^2;
sbit Motor3 = P2^3;

void main()
{
        u8 i=0;
        P2=0x00;
        while(1)
        {
                P2=0x01;
                for(i=0;i<4;i++)
                {
                        delay_ms(200);
                        P2<<=1;
                }
        }

}
