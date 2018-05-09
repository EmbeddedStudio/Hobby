#include <reg51.h>
#include "bsp_delay.h"
#include "bsp_key.h"

#define u16 unsigned int 
#define u8 unsigned char 
        
// MVC Model View Control
        
sbit K2 = P2^2;
sbit K3 = P2^3;
sbit K4 = P2^4;
sbit K5 = P2^0;
sbit K1 = P2^1;
sbit BUZ = P3^7;

u8 i,j,wei=0;

u8 flag=0;//0常亮 正常显示 1设置 2闹钟

void time(void);

number[]={2,3,5,9,5,0};  //这里需要定义类型 但不知道为什么定义u8就跑不动
                        //不定义反而没问题
nao[]={0,0,0,0};

unsigned  char selected[]={0x02,0x04,0x08,0x10,0x20,0x40,0x80};//位选数组高电平有效

unsigned  char table[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};//段选数组高电平有效

void main()
{
        TMOD=0x01; //确定定时器方式
        TH0=0x0b;       //赋初值
        TL0=0xdc;
        TR0=1;           //开定时器
        IE = 0x83;
        while(1)
        {       
                
                if (2!=flag)
                {
                        
                        for (j=0;j<10;j++)//进行10次正常显示的循环
                        {
                                for(i=0;i<6;i++)//循环6位
                                { 
                                        P1 = ~selected[i];
                                        if (i==1||i==3)//加小数点
                                        {
                                                P0 = table[number[i]]|0x80;
                                                delay_ms(1);
                                        }
                                        else
                                        {
                                                P0 = table[number[i]];
                                                delay_ms(1);
                                        }

                                }
                        }
                        if (1==flag)//判断闪烁状态为设置界面
                        {
                                for(j=0;j<10;j++)//进行非正常10次扫描循环
                                {
                                        for(i=0;i<6;i++)
                                        {
                                                if(wei==i)
                                                {
                                                        P1=0xff;
                                                }
                                                else
                                                {
                                                        P1 = ~selected[i];
                                                        if (i==1||i==3)//加小数点
                                                        {
                                                                P0 = table[number[i]]|0x80;
                                                        }
                                                        else
                                                        {
                                                                P0 = table[number[i]];
                                                        }
                                                }
                                                delay_ms(10);
                                                
                                        }
                                        
                                }
                        }
                }
                else if (2==flag)
                {
                        
                        for (j=0;j<10;j++)//进行10次正常显示的循环
                        {
                                for(i=0;i<4;i++)//循环4位
                                { 
                                        P1 = ~selected[i];
                                        if (i==1||i==3)//加小数点
                                        {
                                                P0 = table[nao[i]]|0x80;
                                                delay_ms(1);
                                        }
                                        else
                                        {
                                                P0 = table[nao[i]];
                                                delay_ms(1);
                                        }

                                }
                        }
                        
                        for(j=0;j<10;j++)//进行非正常10次扫描循环
                        {
                                for(i=0;i<4;i++)//循环四位
                                {
                                        if(wei==i)
                                        {
                                                P1=0xff;
                                        }
                                        else
                                        {
                                                P1 = ~selected[i];
                                                if (i==1||i==3)//加小数点
                                                {
                                                        P0 = table[nao[i]]|0x80;
                                                }
                                                else
                                                {
                                                        P0 = table[nao[i]];
                                                }
                                        }
                                        delay_ms(10);
                                        
                                }
                                
                        }
                }
        }
}

void INTO_Handler() interrupt 0  //外部中断
{
        
        key_scan();
}

void TIM0_Handler() interrupt 1
{
        unsigned char a;
        TR0=0;
        TH0=0x0b;
        TL0=0xdc;
        TR0=1;
        a+=1;
        if (a>=16)
        {
                a=0;
                time();
        }
}


void time()
{
        number[5]++;            //每次都给秒针加1  当满足相应的条件就进位
        if(number[5]>9)
        {
                number[5]=0;
                number[4]++;
                if(number[4]>5)
                {
                        number[4]=0;
                        number[3]++;
                        if(number[3]>9)
                        {
                                number[3]=0;
                                number[2]++;
                                if(number[2]>5)
                                {
                                        number[2]=0;
                                        number[1]++;
                                        if(number[0]<2 && number[1]>9)
                                        {
                                                number[1]=0;
                                                number[0]++;
                                        }
                                        else if (number[0]==2&&number[1]>3)
                                        {
                                                number[1]=0;
                                                number[0]=0;
                                        }
                                }
                        }
                }
        }

        if(number[0]==nao[0] && number[1]==nao[1] && number[2]==nao[2] && number[3]==nao[3])
        {
                BUZ=1;          //当闹钟的前四位和时间的前四位相同时开启蜂鸣器
        }
        else
        {
                BUZ=0;
        }

}