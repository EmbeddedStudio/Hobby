#include "stm32f10x.h"   
#include "bsp_led.h"
#include "bsp_key.h"

//void delay(uint32_t count)
//{
//        for (;count!=0;count--);
//}

int main(void)
        {
        LED_GPIO_Config();
        LED_G(ON);
        KEY_GPIO_Config();
        while (1)
        {
                if ( Key_Scan(KEY1_GPIO_PORT,KEY1_GPIO_PIN) == KEY_ON )
                {
                        LED_G_TOGGLE;
                }
                if ( Key_Scan(KEY2_GPIO_PORT,KEY2_GPIO_PIN) == KEY_ON )
                {
                        LED_R_TOGGLE;
                }
                                
        }

}

