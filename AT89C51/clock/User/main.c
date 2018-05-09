#include <reg52.h>
#include "main.h"
#include "bsp_delay.h"
#include "bsp_key.h"

/* 定义模型变量 */
u8 temp[4] = {2,5,8,0};
u8 week = 7;
u8 nian[4] = {2,0,1,7};                 //记录当前的年份
u8 riqi[4] = {1,0,0,1};
u8 value[4] = {1, 1, 5, 9};          // 记录数码管每一位对应值的数组
u8 alarm[4] = {1, 2, 0, 0};                // 记录闹钟的时间的变量，这里只支持一个闹钟
u8 location = 0;                           // 记录当期是哪一位闪烁

/* 数码管段选码、位选码 */
u8 SegCode[10] = {~0x3F, ~0x06, ~0x5B, ~0x4F, ~0x66, ~0x6D, ~0x7D, ~0x07, ~0x7F, ~0x6F};  // 段选低电平有效
u8 DigCode[4] = {0x01,0x02,0x04,0x08};                           // 位选高电平有效
u8 state=0;                 //状态标志 0 正常显示 1 设置模式
                                //2 年份 3星期

sbit beep=P3^6;
sbit m=P0^7;
sbit n=P2^1;
u8 color=0;             //冒号闪烁的标志
u16 time0_interrupt_count = 0;                   // 中断计数变量
u8 time1_interrupt_count = 0;                   // 中断计数变量

void main()
{
         u8 i,j;                                // 循环需要用到的临时变量
         beep=0;
        /* 配置外部中断 0, 用于捕捉按键的输入数据 */
        IT0 = 1;                                // 设置外部中断 0 触发方式为下降沿触发
        EX0 = 1;                                // 开启外部中断 0 中断
       
        /* 配置定时器 0 中断, 用于实现 2 秒后自动返回功能 */
        TMOD = 0x01;                            // 定时器 0 工作在方式 1: 16 位定时计数模式
        TH0 = 0x0b;                             // 这里计数初值为 3036 计数 62500 溢出, 64 次就可以得到 4000000 次计数, 即 2 秒
        TL0 = 0xdc;
        ET0 = 1;                                // 开启定时器 0 中断
        TR0 = 1;
        /* 配置定时器 1 中断, 用于实现 0.5 秒后冒号闪烁功能 */
        TMOD = TMOD | 0x10;                     // 定时器 1 工作在方式 1: 16 位定时计数模式
        TH1 = 0x0b;                             // 这里计数初值为 3036
        TL1 = 0xdc;
        ET1 = 1;                                // 开启定时器 1 中断
        EA = 1;                                 // 开启总中断
        TR1 = 1;                                // 开启定时器 1
        
        
        
        while(1)
        {
                if(state==0||state==1)
                {
                        for (j=0;j<10;j++)
                        {
                                for (i=0;i<4;i++)
                                {
                                        P2=DigCode[i];
                                        P0=SegCode[value[i]];
                                        delay(10);
                                       
                                }
                        }
                        if(state==1)
                        {
                                for (j=0;j<10;j++)
                                {
                                        for (i=0;i<4;i++)
                                        {
                                               /* 判断当期扫描的位是不是location对应位 */
                                                if(location == i)
                                                {
                                                        /* 如果是的话，不选中任何位选，也就是全灭 */
                                                        P2 = 0x00;
                                                }
                                                else
                                                {
                                                         /* 对于其他为就正常显示就好 */
                                                        P2 = DigCode[i];
                                                        P0=SegCode[value[i]];
                                                }
                                               delay(10);
                                                
                                        }
                                }
                        }
                }
                if(state==2||state==21)
                {
                        for (j=0;j<10;j++)
                        {
                                for (i=0;i<4;i++)
                                {
                                        P2=DigCode[i];
                                        P0=SegCode[nian[i]];
                                        delay(10);
                                       
                                }
                        }
                        if(state==21)
                        {
                                for (j=0;j<10;j++)
                                {
                                        for (i=0;i<4;i++)
                                        {
                                                if(location == i)
                                                {
                                                        /* 如果是的话，不选中任何位选，也就是全灭 */
                                                        P2 = 0x00;
                                                }
                                                else
                                                {
                                                        P2=DigCode[i];
                                                        P0=SegCode[nian[i]];
                                                }
                                               delay(10);
                                        }
                                }
                        }
                }
                if(state==3||state==31)
                {
                        for (j=0;j<10;j++)
                        {
                                for (i=0;i<4;i++)
                                {
                                        P2=DigCode[i];
                                        P0=SegCode[riqi[i]];
                                        delay(10);
                                       
                                }
                        }
                        if(state==31)
                        {
                                for (j=0;j<10;j++)
                                {
                                        for (i=0;i<4;i++)
                                        {
                                                if(location == i)
                                                {
                                                        /* 如果是的话，不选中任何位选，也就是全灭 */
                                                        P2 = 0x00;
                                                }
                                                else
                                                {
                                                        P2=DigCode[i];
                                                        P0=SegCode[riqi[i]];
                                                }
                                               delay(10);
                                        }
                                }
                        }
                }
                if(state==4||state==41)
                {
                        for (j=0;j<10;j++)
                        {
                                for (i=0;i<4;i++)
                                {
                                        if(i==2)
                                        {
                                                P2=DigCode[i];
                                                P0=SegCode[week];
                                        }
                                        else 
                                        {
                                                P2=DigCode[i];
                                                P0=0x3f;
                                        }
                                        delay(10);
                                       
                                }
                        }
                        if(state==41)
                        {
                                for (j=0;j<10;j++)
                                {
                                        for (i=0;i<4;i++)
                                        {
                                                if( 2 == i)
                                                {
                                                        /* 如果是的话，不选中任何位选，也就是全灭 */
                                                        P2 = 0x00;
                                                        
                                                }
                                                else
                                                {
                                                        P2=DigCode[i];
                                                        P0=0x3f;
                                                }
                                               delay(10);
                                        }
                                }
                        }
                }
                if(state==5||state==51)
                {
                        for (j=0;j<10;j++)
                        {
                                for (i=0;i<4;i++)
                                {
                                        P2=DigCode[i];
                                        P0=SegCode[alarm[i]];
                                        delay(10);
                                       
                                }
                        }
                        if(state==51)
                        {
                                for (j=0;j<10;j++)
                                {
                                        for (i=0;i<4;i++)
                                        {
                                                if(location == i)
                                                {
                                                        /* 如果是的话，不选中任何位选，也就是全灭 */
                                                        P2 = 0x00;
                                                }
                                                else
                                                {
                                                        P2=DigCode[i];
                                                        P0=SegCode[alarm[i]];
                                                }
                                               delay(10);
                                        }
                                }
                        }
                }
                if(state==6||state==61)
                {
                        for (j=0;j<10;j++)
                        {
                                for (i=0;i<4;i++)
                                {
                                        P2=DigCode[i];
                                        if(i==1)
                                        {
                                                P0=SegCode[temp[i]]|0x80;
                                        }
                                        else
                                        {
                                                P0=SegCode[temp[i]];
                                        }
                                        delay(10);
                                       
                                }
                        }
                        if(state==61)
                        {
                                for (j=0;j<10;j++)
                                {
                                        for (i=0;i<4;i++)
                                        {
                                                if(location == i)
                                                {
                                                        /* 如果是的话，不选中任何位选，也就是全灭 */
                                                        P2 = 0x00;
                                                }
                                                else
                                                {
                                                        P2=DigCode[i];
                                                        if(i==1)
                                                        {
                                                                P0=SegCode[temp[i]]|0x80;
                                                        }
                                                        else
                                                        {
                                                                P0=SegCode[temp[i]];
                                                        }
                                                }
                                               delay(10);
                                        }
                                }
                        }
                }
                
                if(alarm[0]==value[0]&&alarm[1]==value[1]&&alarm[2]==value[2]&&alarm[3]==value[3])
                {
                        beep=1;
                }
        }

}

void INTO_IRQHander() interrupt 0
{
        key_control(Key_Scan());
}

void TIMO_IRQHander() interrupt 1
{
        
        TH0 = 0x0b;                             /* 重新转载计数初值 3036 */
        TL0 = 0xdc;
        
        if(state!=1&&state!=21&&state!=31&&state!=41&&state!=51&&state!=61)
        {
                time0_interrupt_count++;        /* 每中断一次, 中断计数变量加一 */
        }
        if(time0_interrupt_count >= 1920)         /* 定时时间到了 1 秒之后返回时间显示界面 */
        {
                time0_interrupt_count = 0;      // 清空中断计数值
               
                       
                        value[3]++;
                        if (value[3]==10)
                        {
                                value[3]=0;
                                value[2]++;
                                if(value[2]==6)
                                {
                                        value[2]=0;
                                        value[1]++;
                                        if(value[0]==2&&value[1]==4)
                                        {
                                                value[0]=0;
                                                value[1]=0;
                                        }
                                        else if (value[0]<2&&value[1]==10)
                                        {
                                                value[1]=0;
                                                value[0]++;
                                        }
                                }
                        }
                
        }

       
}

void TIM1_IRQHander() interrupt 3
{
        TH1 = 0x0b;                             /* 重新转载计数初值 */
        TL1 = 0xdc;
        if(state!=0&&state!=1&&state!=21&&state!=31&&state!=41&&state!=51&&state!=61)
                //如果不是正常显示的状态就搞事情2s后自动回到正常状态
        {
                time1_interrupt_count++;                
                
                if(time1_interrupt_count >= 128)         
                {
                        time1_interrupt_count = 0;      // 清空中断计数值
                        
                        state=0;
                }
        }
}
