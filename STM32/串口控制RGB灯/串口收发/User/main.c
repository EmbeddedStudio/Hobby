#include "stm32f10x.h"   
#include "bsp_led.h"
#include "bsp_usart.h"

void delay(uint32_t count)
{
        for (;count!=0;count--);
}
int main(void)
{
        USART_Config ();
        USART_sent(  DEBUG_USARTx , 'A' );
        while (1)
        {

        }
}

