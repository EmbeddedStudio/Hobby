#include <reg52.h>
#define XTAL_110592M  1

#define u8  unsigned char
#define u16 unsigned short
#define u32 unsigned long

u8 SegCode[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};  // ��ѡ�͵�ƽ��Ч

u8 Num1[4]={8,3,2,3};//�ĳ��Լ���ѧ��
u8 Num2[5]={'3','2','7','7','\n'};//�ĳ��Լ���ѧ��

u8 receiveData;  //���ջ���
u8 time =0;  //�жϼ���

/* ����������*/
void delay( u16 t);

void main()
{
        u8 i=0;
        TMOD=0x21; //ȷ����ʱ����ʽ
        PCON = 0x00;  //�����ʲ��ӱ�Ϊ9600
        SCON = 0x50;  //�����ڷ�ʽ1
        
        #if XTAL_110592M
                TH1=0xFD;       //����ֵ
                TL1=0xFD; 
                TH0=0xA6;
                TL0=0x00;
        #else
                TH1=0xFA;       //����ֵ
                TL1=0xFA;
                TH0=0x4C;       //����ֵ
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
                                P2=0x00;//����
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
                TH0=0xA6;       //����ֵ
//                TL0=0x00;  
        #else     
                TH0=0x4C;       //����ֵ
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
                        while(!TI);                 // �ȴ��������
                        TI=0;                   // ������ͱ�־
                }
        }
}
void Usart() interrupt 4  //�����շ��ж�
{
            /*          �����ж�        */
            TI=0;
            RI=0;           //��0��������һ�εĽ���
            receiveData = SBUF;//�����յ������ݱ����� receiveData ��
}


