#include <reg52.h>

void Delay(u8 ms)
{
        u8 temp;
        
        for( ; ms > 0; ms--)
        {
                for(temp = 200; temp > 0; temp--);
        }
}

void main()
{
        
        while(1)
        {
                P1=0xff;
                Delay(100);
                P1=0x00;
                Delay(100);
        }

}
