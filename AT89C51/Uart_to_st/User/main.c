#include <reg52.h>

sbit mode_select = P1^0;
sbit led=P1^4;
sbit led_R=P1^1;
sbit led_G=P1^2;
sbit led_B=P1^3;

#define open  'o'
#define close 'c'

void delay(u8 ms);

void main()
{
        char signal  = ' ';
        
        IE=0x98;
        TMOD=0x20;
        TH1 = 0xfd; 
        TL1 = 0xfd;
        TR1=1;
        PCON = 0x00;  //�����ʲ��ӱ�Ϊ9600
        SCON = 0x40;  //�����ڷ�ʽ1
        
        
        while(1)
        {
                if(mode_select == 1)      // ѡ��λΪ�ߵ�ƽΪ���ͻ�
                {
                        
                        TI = 0;
                        
                        if(led_R==1)
                        {
                                SBUF='R';
                                while(TI == 0);                 // �ȴ��������
                                TI = 0;                         // ������ͱ�־
                                delay(500);
                        }
                        else if(led_R==0)
                        {
                                SBUF='r';
                                while(TI == 0);                 // �ȴ��������
                                TI = 0;                         // ������ͱ�־
                                delay(500);
                        }
                        if(led_G==1)
                        {
                                SBUF='G';
                                while(TI == 0);                 // �ȴ��������
                                TI = 0;                         // ������ͱ�־
                                delay(500);
                        }
                       else if(led_G==0)
                        {
                                SBUF='g';
                                while(TI == 0);                 // �ȴ��������
                                TI = 0;                         // ������ͱ�־
                                delay(500);
                        }
                         if(led_B==1)
                        {
                                SBUF='B';
                                while(TI == 0);                 // �ȴ��������
                                TI = 0;                         // ������ͱ�־
                                delay(500);
                        }
                       else if(led_B==0)
                        {
                                SBUF='b';
                                while(TI == 0);                 // �ȴ��������
                                TI = 0;                         // ������ͱ�־
                                delay(500);
                        }
                        
                        
                        
                }
                else                         // ѡ��λΪ�ߵ�ƽΪ���ջ�
                {
                        SCON = 0x50;
                        RI = 0;
                        if(RI)
                        {
                                signal =SBUF;
                                RI = 0;
                                delay(10);
                        }
                        if(signal == open)
                        {
                                led=0;
                        }
                        else if(signal == close)
                        {
                                led=1;
                        }
                }
        }

}

void delay(u8 ms)
{
        u32 temp;

        for( ; ms > 0; ms--)
        {
                for(temp = 100; temp > 0; temp--);
        }
}

