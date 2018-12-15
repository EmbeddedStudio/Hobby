#include "stm32f10x.h"
#include "bsp_systick.h"
#include "bsp_usart.h"
#include "bsp_led.h"
#include "bsp_motor_pwm.h"


int main(void)
{
        
        PWM_Init();
        while(1)
        {
                PWM_M1_Forward(0xff00);
        }
}
