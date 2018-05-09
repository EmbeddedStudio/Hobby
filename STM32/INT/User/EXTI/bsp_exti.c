#include "bsp_exti.h"
#include "bsp_led.h"




static void EXTI_NVIC_Config (void)
{
        NVIC_InitTypeDef        NVIC_Initstuct;
        NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
        NVIC_Initstuct.NVIC_IRQChannel = EXTI9_5_IRQn;
        NVIC_Initstuct.NVIC_IRQChannelPreemptionPriority = 2;   //主优先级
        NVIC_Initstuct.NVIC_IRQChannelSubPriority = 1;          //子优先级
        NVIC_Initstuct.NVIC_IRQChannelCmd = ENABLE;
        NVIC_Init(&NVIC_Initstuct);
        
        NVIC_Initstuct.NVIC_IRQChannelPreemptionPriority = 2;   //主优先级
        NVIC_Initstuct.NVIC_IRQChannelSubPriority = 0;          //子优先级
        NVIC_Initstuct.NVIC_IRQChannel = EXTI15_10_IRQn;
        NVIC_Init(&NVIC_Initstuct);
}
void EXTI_Config (void)
{
        GPIO_InitTypeDef        GPIO_Initstuct;
        EXTI_InitTypeDef        EXTI_Initstuct;
        EXTI_NVIC_Config ( );

          
        //初始化要连接到EXTI的GPIO
        RCC_APB2PeriphClockCmd(KEY1_INT_GPIO_CLK , ENABLE);     //开时钟
        GPIO_Initstuct.GPIO_Pin = KEY1_INT_GPIO_PIN  ;
        GPIO_Initstuct.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
        GPIO_Init(KEY1_INT_GPIO_PORT, &GPIO_Initstuct);

        RCC_APB2PeriphClockCmd(KEY2_INT_GPIO_CLK , ENABLE);     //开时钟
        GPIO_Initstuct.GPIO_Pin = KEY2_INT_GPIO_PIN  ;
        GPIO_Initstuct.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
        GPIO_Init(KEY2_INT_GPIO_PORT, &GPIO_Initstuct);

        //初始化EXTI
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO , ENABLE);   
        GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource6);
        EXTI_Initstuct.EXTI_Mode = EXTI_Mode_Interrupt;         //中断模式
        EXTI_Initstuct.EXTI_Trigger = EXTI_Trigger_Falling;      //触发方式下降沿
        EXTI_Initstuct.EXTI_Line = EXTI_Line6;                  //0号引脚
        EXTI_Initstuct.EXTI_LineCmd = ENABLE;                   //使能
        EXTI_Init( &EXTI_Initstuct);



        GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource13);
        EXTI_Initstuct.EXTI_Mode = EXTI_Mode_Interrupt;
        EXTI_Initstuct.EXTI_Trigger = EXTI_Trigger_Falling;
        EXTI_Initstuct.EXTI_Line = EXTI_Line13;
        EXTI_Initstuct.EXTI_LineCmd = ENABLE;
        EXTI_Init( &EXTI_Initstuct);
}





