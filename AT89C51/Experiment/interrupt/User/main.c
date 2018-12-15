#include <reg52.h>

#define u8  unsigned char
#define u16 unsigned short
#define u32 unsigned long

//sbit key1=P3^0;
//sbit key2=P3^1;
sbit key3=P3^2;
//sbit key4=P3^3;

u8 SegCode[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};  // 段选低电平有效

u8 Num1[4]={8,0,2,3};//改成自己的学号
u8 Num2[4]={9,1,2,3};//改成自己的学号

char count=0;
void delay( u16 t);
//u8  key_contraol(void);
u8  location=0;
u8 key_flag=0;
void main(void)
{
        
        u8 i=0;
        
        IE = 0x85;
        IT1 = 1;
        IT0 = 1;
        P0=0x00;
        P2=0x00;
        while(1)
        {
//                key_flag=key_contraol();
                
                if(location!=0)
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
                                delay(1);
                                P0=0x00;//消隐
                        }
                }
        }

}
void delay( u16 t)
{
        u16 i,j;
        for(i=0;i<t;i++)
                for(j=0;j<2000;j++);
}

//u8  key_contraol(void)
//{
//        u8 key ;
//        if(key1==0)
//        {
//                delay(10)  ;
//                if(key1==0)
//                {
//                          key=0;
//                }
//        }
//        if(key2==0)
//        {
//                delay(10)  ;
//                if(key2==0)
//                {
//                          key=1;
//                }
//        }
//return key;
//}


void INT0_IRQHander(void) interrupt 0
{
        u8 i=0;
        location=1;
        key_flag=!key_flag;
        if(key3==0)
        {
                delay(10);
                if(key3==0)
                {
                        count+=1;
                        if(count>10)
                                count=0;
                } 
                while( (key3==0) && i<20)
                {
                        i++;
                }
        }
}

//void INT1_IRQHander(void) interrupt 2
//{
//        u8 i=0;
//        location=1;
//        key_flag=!key_flag;
//        if(key4==0)
//        {
//                delay(10);
//                if(key4==0)
//                {
//                        count+=1;
//                        if(count>=10)
//                                count=0;
//                } 
//                while( (key4==0) && i<20)
//                {
//                        i++;
//                }
//        }
//}