#include <reg52.h>
#include "bsp_delay.h"

void main()
{
        IT0=1;//下降沿触发
        IT1=1;//下降沿触发
        IE = 0x85;
//        PX0=0;
        PX1=1;
        
        while(1)
        {
              P1=0x0f;  
        }
}

void TIM0_IRQHander() interrupt 0
{
        P1=0xfe;
        delay(3000);
}

void TIM1_IRQHander() interrupt 2
{
        P1=0xf0;
        delay(3000);
}





