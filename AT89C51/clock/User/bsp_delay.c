#include "bsp_delay.h"


void delay(unsigned int ms)
{
        unsigned int  i;
        for (;ms>0;ms--)
        {
                for(i=0;i<100;i++);
        }
}


