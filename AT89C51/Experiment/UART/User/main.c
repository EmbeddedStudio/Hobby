#include <reg52.h>
#define XTAL_110592M  1

#define u8  unsigned char
#define u16 unsigned short
#define u32 unsigned long

u8 SegCode[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};  // 段选低电平有效

u8 Num1[4]={8,3,2,3};//改成自己的学号
u8 Num2[5]={'3','2','7','7','\n'};//改成自己的学号

u8 receiveData;  //接收缓存
u8 time =0;  //中断计数

/* 函数的声明*/
void delay( u16 t);

void main()
{
        u8 i=0;
        TMOD=0x21; //确定定时器方式
        PCON = 0x00;  //波特率不加倍为9600
        SCON = 0x50;  //工作在方式1
        
        #if XTAL_110592M
                TH1=0xFD;       //赋初值
                TL1=0xFD; 
                TH0=0xA6;
                TL0=0x00;
        #else
                TH1=0xFA;       //赋初值
                TL1=0xFA;
                TH0=0x4C;       //赋初值
                TL0=0x00;
        #endif
        TI =0;
        RI =0;
        TR1=1;
        TR0=1;
        IE = 0x9A;
        while(1)
        {
                if(receiveData=='1')
                {
                        for(i=0;i<4;i++)
                        {
                                P1&=0xf8; //1111 1000
                                P1|=i;   //xxxx x001
                                P2=SegCode[Num1[i]];
                                delay(1);
                                P2=0x00;//消隐
                        }
                }
                else
                {
                        P2=0x00; 
                }
        }
}

void delay( u16 t)
{
        u16 i,j;
        for(i=0;i<t;i++)
                for(j=0;j<1000;j++);
}
void TIM0_IRQHander(void) interrupt 1
{
        u8 i=0;
        TR0=0;
        #if XTAL_110592M
                TH0=0xA6;       //赋初值
//                TL0=0x00;  
        #else     
                TH0=0x4C;       //赋初值
//                TL0=0x00;
        #endif
        TR0=1;
        time++;
        if (time>=40)
        {
                time=0;
                for(i=0;i<5;i++)
                {
                        SBUF=Num2[i];
                        while(!TI);                 // 等待发送完成
                        TI=0;                   // 清除发送标志
                }
        }
}
void Usart() interrupt 4  //串口收发中断
{
            /*          接收中断        */
            TI=0;
            RI=0;           //置0，便于下一次的接收
            receiveData = SBUF;//将接收到的数据保存在 receiveData 中
}


