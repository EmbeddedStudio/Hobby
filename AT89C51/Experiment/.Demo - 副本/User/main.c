#include "reg52.h"

unsigned char code DSY_CODE[]= {0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};

unsigned char NUM[4] = {8,0,2,3};              //学号
unsigned int Counter = 0;                       //计数器
sbit key=P3^2;
unsigned char location=0;
void Delay(int MS);
//外部中断0服务函数
void EX_INT0() interrupt 0             //外部中断0服务函数
{
        location=1;
        if(key==0)
        {
                Delay(10);
                if(key==0)
                {
                         Counter++;                                  //当检测到外部中断0时，计数器加1
                        if(Counter >=10)
                        {
                          Counter = 0;						      //计数到9则返回
                        }
                }
        }
 
}

//外部中断0初始化函数
void initINT0(void)
{
  IT0 = 1;        //设置外部中断0为边沿触发方式
  EX0 = 1;      //使能外部中断0
  EA = 1;       //使能中断事件
}
//延时函数
void Delay(int MS)      
{ 
        unsigned int i,j;
        for(i = 0;i < MS;i++)
        for(j = 0;j <2000;j++) ;
}

int main(void)
{
  unsigned char i;
  initINT0();           //初始化外部中断
        P0=0x00;
        while(1)
        {
                if(location!=0)
                {
                        P0 =~DSY_CODE[Counter];
                        for(i = 0;i < 4;i++)
                        {
                                P1&= 0xf8; //1111 1000
                                P1|= i;   //xxxx x001
                                P2 = ~DSY_CODE[NUM[i]];
                                Delay(1); 
                        }
                }
        }
}
