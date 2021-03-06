#include "reg52.h"      //此文件中定义了单片机的一些特殊功能寄存器

sbit IRIN=P3^2;

u8 IrValue[6];
u8 Time,state=0;

sbit LEDL =P0^0;
sbit LED = P2^4;
sbit RGBR = P2^6;
sbit RGBL = P2^5;

void delay(u16 i)
{
        while(i--);     
}

void IrInit()
{
        IT0=1;//下降沿触发
        EX0=1;//打开中断0允许
        EA=1; //打开总中断
        
        IRIN=1;//初始化端口
}


void main()
{ 
        IrInit();
        LEDL=1;
        LED=1;
        RGBR=1;
        RGBL=1;
        while(1)
        { 
                state = IrValue[2];
                if(state==0x45)
                {
                        LED=1;
                }
                else if(state==0x44)
                {
                        LED=0;
                }
                else if(state==0x46)
                {
                        RGBL=0;
                }
                else if(state==0x40)
                {
                        
                        RGBL=1;
                }
                else if(state==0x47)
                {
                        RGBR=0;
                }
                else if(state==0x43)
                {
                        RGBR=1;
                }
        }       
}


void ReadIr() interrupt 0
{
        u8 j,k;
        u16 err;
        Time=0; 
        delay(700); //7ms
        if(IRIN==0) //确认是否真的接收到正确的信号
        { 
                
                err=1000; //1000*10us=10ms,超过说明接收到错误的信号
                /*当两个条件都为真是循环，如果有一个条件为假的时候跳出循环，免得程序出错的时
                侯，程序死在这里*/ 
                while((IRIN==0)&&(err>0)) //等待前面9ms的低电平过去 
                { 
                        delay(1);
                        err--;
                } 
                if(IRIN==1) //如果正确等到9ms低电平
                {
                        err=500;
                        while((IRIN==1)&&(err>0)) //等待4.5ms的起始高电平过去
                        {
                                delay(1);
                                err--;
                        }
                        for(k=0;k<4;k++) //共有4组数据
                        { 
                                for(j=0;j<8;j++) //接收一组数据
                                {

                                        err=60; 
                                        while((IRIN==0)&&(err>0))//等待信号前面的560us低电平过去
                                        {
                                                delay(1);
                                                err--;
                                        }
                                        err=500;
                                        while((IRIN==1)&&(err>0)) //计算高电平的时间长度。
                                        {
                                                delay(10); //0.1ms
                                                Time++;
                                                err--;
                                                if(Time>30)
                                                {
                                                        return;
                                                }
                                        }
                                        IrValue[k]>>=1;  //k表示第几组数据
                                        if(Time>=8) //如果高电平出现大于565us，那么是1
                                        {
                                                IrValue[k]|=0x80;
                                        }
                                        Time=0; //用完时间要重新赋值 
                                }
                        }
                }
                if(IrValue[2]!=~IrValue[3])
                {
                        return;
                }
        } 
}

