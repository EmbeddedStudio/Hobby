#include "reg52.h"

unsigned char code DSY_CODE[]= {0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};

unsigned char NUM[4] = {8,0,2,3};              //ѧ��
unsigned int Counter = 0;                       //������
sbit key=P3^2;
unsigned char location=0;
void Delay(int MS);
//�ⲿ�ж�0������
void EX_INT0() interrupt 0             //�ⲿ�ж�0������
{
        location=1;
        if(key==0)
        {
                Delay(10);
                if(key==0)
                {
                         Counter++;                                  //����⵽�ⲿ�ж�0ʱ����������1
                        if(Counter >=10)
                        {
                          Counter = 0;						      //������9�򷵻�
                        }
                }
        }
 
}

//�ⲿ�ж�0��ʼ������
void initINT0(void)
{
  IT0 = 1;        //�����ⲿ�ж�0Ϊ���ش�����ʽ
  EX0 = 1;      //ʹ���ⲿ�ж�0
  EA = 1;       //ʹ���ж��¼�
}
//��ʱ����
void Delay(int MS)      
{ 
        unsigned int i,j;
        for(i = 0;i < MS;i++)
        for(j = 0;j <2000;j++) ;
}

int main(void)
{
  unsigned char i;
  initINT0();           //��ʼ���ⲿ�ж�
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
