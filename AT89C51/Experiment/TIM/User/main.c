#include <reg52.h>
#define XTAL_12M  0

#define u8  unsigned char
#define u16 unsigned short
#define u32 unsigned long
        
//9E56  12M
//4C00  22.1184M

u8 SegCode[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};  // 段选低电平有效
sbit K1 = P3^2; 
sbit K2 = P3^3; 
sbit K3 = P3^0; 

u8 Num1[4]={8,3,2,3};//改成自己的学号
u8 Num2[4]={7,7,2,3};//改成自己的学号
u8 Num3[4]={0,0,0,0};//改成自己的学号

u8 start=0;  //开始显示的标志位
u8  dir=0;   //定时器加还是减的标志方向 0 加方向 1 减方向
char count=0;  //静态数码管显示的数值
u8 key_flag=0;//显示学号的标志位
u8 time =0;
/* 函数的声明*/
void delay( u16 t);


void main()
{
       
        u8 i=0;
        TMOD=0x10; //确定定时器方式
        
        #if XTAL_12M
                TH1=0x9E;       //赋初值
                TL1=0x58;  
        #else
                TH1=0x4C;       //赋初值
                TL1=0x00;
        #endif
        IE = 0x8F;
        P0=0x00;
        P2=0x00;
        while(1)
        {
                if(K3==0)
                {
                        delay(10);
                        if(K3==0)
                        {
                                start=1;
                                TR1=0;
                                key_flag=2;
                                count=0;
                                time=0;
                        }
                }
                if(start!=0)
                {
                        
                        P0=SegCode[count];
                        for(i=0;i<4;i++)
                        {
                                P1&=0xf8; //1111 1000
                                P1|=i;   //xxxx x001
                                if(key_flag ==0)
                                {
                                        P2=SegCode[Num1[i]];
                                }
                                if (key_flag==1)
                                {
                                        P2=SegCode[Num2[i]];
                                }
                                if(key_flag==2)
                                {
                                        P2=SegCode[Num3[i]];
                                }
                                delay(1);
                                P2=0x00;//消隐
                        }
                }
        }
}

void delay( u16 t)
{
        u16 i,j;
        for(i=0;i<t;i++)
                for(j=0;j<1000;j++);
}

void INT0_IRQHander(void) interrupt 0
{
       
        if(K1==0)
        {
                delay(20);
                if(K1==0)
                {
                        TR1=1;
                        start=1;
                        key_flag=0;
                        dir=0;
                        time=0;
                }
        }
}
void INT1_IRQHander(void) interrupt 2
{
        if(K2==0)
        {
                delay(20);
                if(K2==0)
                {
                        TR1=1;
                        start=1;
                        key_flag=1;
                        dir=1;
                        time=0;
                }
        }
}
void TIM1_IRQHander(void) interrupt 3
{
        TR1=0;
        #if XTAL_12M
                TH1=0x9E;       //赋初值
                TL1=0x56;  
        #else     
                TH1=0x4C;       //赋初值
                TL1=0x00;
        #endif
        TR1=1;
        time+=1;
        if(dir!=0)  // 减方向
        {
                if (time>=40)
                {
                        time=0;
                        count-=1;        //1秒时间到
                        if(count<0)
                                count=9;
                }
        }
        else   //加方向
        {
                if(time>=20)
                {
                        time=0;
                        count+=1;       //0.5秒时间到
                        if(count>=10)
                                count=0;
                }
        }
}


