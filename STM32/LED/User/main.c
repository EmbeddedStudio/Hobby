#include "stm32f10x.h"   
#include "bsp_led.h"

void delay(uint32_t count)
{
        for (;count!=0;count--);
}
int main(void)
{
        LED_GPIO_Config();
        while (1)
        {
                LED_RED;            
                delay(0xffffff);
                LED_GREEN;
                delay(0xffffff);
                LED_BLUE;
                delay(0xffffff);  


        }

}

