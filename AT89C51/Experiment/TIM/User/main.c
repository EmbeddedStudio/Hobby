#include <reg52.h>
#define XTAL_12M  0

#define u8  unsigned char
#define u16 unsigned short
#define u32 unsigned long
        
//9E56  12M
//4C00  22.1184M

u8 SegCode[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};  // ��ѡ�͵�ƽ��Ч
sbit K1 = P3^2; 
sbit K2 = P3^3; 
sbit K3 = P3^0; 

u8 Num1[4]={8,3,2,3};//�ĳ��Լ���ѧ��
u8 Num2[4]={7,7,2,3};//�ĳ��Լ���ѧ��
u8 Num3[4]={0,0,0,0};//�ĳ��Լ���ѧ��

u8 start=0;  //��ʼ��ʾ�ı�־λ
u8  dir=0;   //��ʱ���ӻ��Ǽ��ı�־���� 0 �ӷ��� 1 ������
char count=0;  //��̬�������ʾ����ֵ
u8 key_flag=0;//��ʾѧ�ŵı�־λ
u8 time =0;
/* ����������*/
void delay( u16 t);


void main()
{
       
        u8 i=0;
        TMOD=0x10; //ȷ����ʱ����ʽ
        
        #if XTAL_12M
                TH1=0x9E;       //����ֵ
                TL1=0x58;  
        #else
                TH1=0x4C;       //����ֵ
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
                                P2=0x00;//����
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
                TH1=0x9E;       //����ֵ
                TL1=0x56;  
        #else     
                TH1=0x4C;       //����ֵ
                TL1=0x00;
        #endif
        TR1=1;
        time+=1;
        if(dir!=0)  // ������
        {
                if (time>=40)
                {
                        time=0;
                        count-=1;        //1��ʱ�䵽
                        if(count<0)
                                count=9;
                }
        }
        else   //�ӷ���
        {
                if(time>=20)
                {
                        time=0;
                        count+=1;       //0.5��ʱ�䵽
                        if(count>=10)
                                count=0;
                }
        }
}


