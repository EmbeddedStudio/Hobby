#include <reg52.h>
#define u8  unsigned char
#define u16 unsigned short
#define u32 unsigned long

sbit key1=P2^7;
sbit key2=P2^6;

u8 SegCode[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};  // 段选低电平有效
u8 Num1[4]={7,7,2,3};//改成自己的学号
u8 Num2[4]={8,3,2,3};//改成自己的学号

void delay( u16 t);
u8  key_contraol(void);

void main(void)
{
        u8 i=0;
        u8 key_flag=0;
        P0=0x00;
        while(1)
        {
                key_flag=key_contraol();
                for(i=0;i<4;i++)
                {
                        P1&=0xf8; //1111 1000
                        P1|=i;   //xxxx x001
                        if(key_flag ==1)
                        {
                                P0=SegCode[Num1[i]];
                        }
                        if (key_flag==2)
                        {
                            P0=SegCode[Num2[i]];
                        }
                        delay(1);
                        P0=0x00;//消隐
                         
                }
        }

}
void delay( u16 t)
{
        u16 i,j;
        for(i=0;i<t;i++)
                for(j=0;j<100;j++);
}

u8  key_contraol(void)
{
        u8 key ;
        if(key1==0)
        {
                delay(5)  ;
                if(key1==0)
                {
                          key=2;
                }
        }
        if(key2==0)
        {
                delay(5)  ;
                if(key2==0)
                {
                          key=1;
                }
        }
return key;
}
