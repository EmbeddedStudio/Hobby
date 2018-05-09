#include <reg52.h>
#include "main.h"
#include "bsp_delay.h"
#include "bsp_key.h"

/* ����ģ�ͱ��� */
u8 temp[4] = {2,5,8,0};
u8 week = 7;
u8 nian[4] = {2,0,1,7};                 //��¼��ǰ�����
u8 riqi[4] = {1,0,0,1};
u8 value[4] = {1, 1, 5, 9};          // ��¼�����ÿһλ��Ӧֵ������
u8 alarm[4] = {1, 2, 0, 0};                // ��¼���ӵ�ʱ��ı���������ֻ֧��һ������
u8 location = 0;                           // ��¼��������һλ��˸

/* ����ܶ�ѡ�롢λѡ�� */
u8 SegCode[10] = {~0x3F, ~0x06, ~0x5B, ~0x4F, ~0x66, ~0x6D, ~0x7D, ~0x07, ~0x7F, ~0x6F};  // ��ѡ�͵�ƽ��Ч
u8 DigCode[4] = {0x01,0x02,0x04,0x08};                           // λѡ�ߵ�ƽ��Ч
u8 state=0;                 //״̬��־ 0 ������ʾ 1 ����ģʽ
                                //2 ��� 3����

sbit beep=P3^6;
sbit m=P0^7;
sbit n=P2^1;
u8 color=0;             //ð����˸�ı�־
u16 time0_interrupt_count = 0;                   // �жϼ�������
u8 time1_interrupt_count = 0;                   // �жϼ�������

void main()
{
         u8 i,j;                                // ѭ����Ҫ�õ�����ʱ����
         beep=0;
        /* �����ⲿ�ж� 0, ���ڲ�׽�������������� */
        IT0 = 1;                                // �����ⲿ�ж� 0 ������ʽΪ�½��ش���
        EX0 = 1;                                // �����ⲿ�ж� 0 �ж�
       
        /* ���ö�ʱ�� 0 �ж�, ����ʵ�� 2 ����Զ����ع��� */
        TMOD = 0x01;                            // ��ʱ�� 0 �����ڷ�ʽ 1: 16 λ��ʱ����ģʽ
        TH0 = 0x0b;                             // ���������ֵΪ 3036 ���� 62500 ���, 64 �ξͿ��Եõ� 4000000 �μ���, �� 2 ��
        TL0 = 0xdc;
        ET0 = 1;                                // ������ʱ�� 0 �ж�
        TR0 = 1;
        /* ���ö�ʱ�� 1 �ж�, ����ʵ�� 0.5 ���ð����˸���� */
        TMOD = TMOD | 0x10;                     // ��ʱ�� 1 �����ڷ�ʽ 1: 16 λ��ʱ����ģʽ
        TH1 = 0x0b;                             // ���������ֵΪ 3036
        TL1 = 0xdc;
        ET1 = 1;                                // ������ʱ�� 1 �ж�
        EA = 1;                                 // �������ж�
        TR1 = 1;                                // ������ʱ�� 1
        
        
        
        while(1)
        {
                if(state==0||state==1)
                {
                        for (j=0;j<10;j++)
                        {
                                for (i=0;i<4;i++)
                                {
                                        P2=DigCode[i];
                                        P0=SegCode[value[i]];
                                        delay(10);
                                       
                                }
                        }
                        if(state==1)
                        {
                                for (j=0;j<10;j++)
                                {
                                        for (i=0;i<4;i++)
                                        {
                                               /* �жϵ���ɨ���λ�ǲ���location��Ӧλ */
                                                if(location == i)
                                                {
                                                        /* ����ǵĻ�����ѡ���κ�λѡ��Ҳ����ȫ�� */
                                                        P2 = 0x00;
                                                }
                                                else
                                                {
                                                         /* ��������Ϊ��������ʾ�ͺ� */
                                                        P2 = DigCode[i];
                                                        P0=SegCode[value[i]];
                                                }
                                               delay(10);
                                                
                                        }
                                }
                        }
                }
                if(state==2||state==21)
                {
                        for (j=0;j<10;j++)
                        {
                                for (i=0;i<4;i++)
                                {
                                        P2=DigCode[i];
                                        P0=SegCode[nian[i]];
                                        delay(10);
                                       
                                }
                        }
                        if(state==21)
                        {
                                for (j=0;j<10;j++)
                                {
                                        for (i=0;i<4;i++)
                                        {
                                                if(location == i)
                                                {
                                                        /* ����ǵĻ�����ѡ���κ�λѡ��Ҳ����ȫ�� */
                                                        P2 = 0x00;
                                                }
                                                else
                                                {
                                                        P2=DigCode[i];
                                                        P0=SegCode[nian[i]];
                                                }
                                               delay(10);
                                        }
                                }
                        }
                }
                if(state==3||state==31)
                {
                        for (j=0;j<10;j++)
                        {
                                for (i=0;i<4;i++)
                                {
                                        P2=DigCode[i];
                                        P0=SegCode[riqi[i]];
                                        delay(10);
                                       
                                }
                        }
                        if(state==31)
                        {
                                for (j=0;j<10;j++)
                                {
                                        for (i=0;i<4;i++)
                                        {
                                                if(location == i)
                                                {
                                                        /* ����ǵĻ�����ѡ���κ�λѡ��Ҳ����ȫ�� */
                                                        P2 = 0x00;
                                                }
                                                else
                                                {
                                                        P2=DigCode[i];
                                                        P0=SegCode[riqi[i]];
                                                }
                                               delay(10);
                                        }
                                }
                        }
                }
                if(state==4||state==41)
                {
                        for (j=0;j<10;j++)
                        {
                                for (i=0;i<4;i++)
                                {
                                        if(i==2)
                                        {
                                                P2=DigCode[i];
                                                P0=SegCode[week];
                                        }
                                        else 
                                        {
                                                P2=DigCode[i];
                                                P0=0x3f;
                                        }
                                        delay(10);
                                       
                                }
                        }
                        if(state==41)
                        {
                                for (j=0;j<10;j++)
                                {
                                        for (i=0;i<4;i++)
                                        {
                                                if( 2 == i)
                                                {
                                                        /* ����ǵĻ�����ѡ���κ�λѡ��Ҳ����ȫ�� */
                                                        P2 = 0x00;
                                                        
                                                }
                                                else
                                                {
                                                        P2=DigCode[i];
                                                        P0=0x3f;
                                                }
                                               delay(10);
                                        }
                                }
                        }
                }
                if(state==5||state==51)
                {
                        for (j=0;j<10;j++)
                        {
                                for (i=0;i<4;i++)
                                {
                                        P2=DigCode[i];
                                        P0=SegCode[alarm[i]];
                                        delay(10);
                                       
                                }
                        }
                        if(state==51)
                        {
                                for (j=0;j<10;j++)
                                {
                                        for (i=0;i<4;i++)
                                        {
                                                if(location == i)
                                                {
                                                        /* ����ǵĻ�����ѡ���κ�λѡ��Ҳ����ȫ�� */
                                                        P2 = 0x00;
                                                }
                                                else
                                                {
                                                        P2=DigCode[i];
                                                        P0=SegCode[alarm[i]];
                                                }
                                               delay(10);
                                        }
                                }
                        }
                }
                if(state==6||state==61)
                {
                        for (j=0;j<10;j++)
                        {
                                for (i=0;i<4;i++)
                                {
                                        P2=DigCode[i];
                                        if(i==1)
                                        {
                                                P0=SegCode[temp[i]]|0x80;
                                        }
                                        else
                                        {
                                                P0=SegCode[temp[i]];
                                        }
                                        delay(10);
                                       
                                }
                        }
                        if(state==61)
                        {
                                for (j=0;j<10;j++)
                                {
                                        for (i=0;i<4;i++)
                                        {
                                                if(location == i)
                                                {
                                                        /* ����ǵĻ�����ѡ���κ�λѡ��Ҳ����ȫ�� */
                                                        P2 = 0x00;
                                                }
                                                else
                                                {
                                                        P2=DigCode[i];
                                                        if(i==1)
                                                        {
                                                                P0=SegCode[temp[i]]|0x80;
                                                        }
                                                        else
                                                        {
                                                                P0=SegCode[temp[i]];
                                                        }
                                                }
                                               delay(10);
                                        }
                                }
                        }
                }
                
                if(alarm[0]==value[0]&&alarm[1]==value[1]&&alarm[2]==value[2]&&alarm[3]==value[3])
                {
                        beep=1;
                }
        }

}

void INTO_IRQHander() interrupt 0
{
        key_control(Key_Scan());
}

void TIMO_IRQHander() interrupt 1
{
        
        TH0 = 0x0b;                             /* ����ת�ؼ�����ֵ 3036 */
        TL0 = 0xdc;
        
        if(state!=1&&state!=21&&state!=31&&state!=41&&state!=51&&state!=61)
        {
                time0_interrupt_count++;        /* ÿ�ж�һ��, �жϼ���������һ */
        }
        if(time0_interrupt_count >= 1920)         /* ��ʱʱ�䵽�� 1 ��֮�󷵻�ʱ����ʾ���� */
        {
                time0_interrupt_count = 0;      // ����жϼ���ֵ
               
                       
                        value[3]++;
                        if (value[3]==10)
                        {
                                value[3]=0;
                                value[2]++;
                                if(value[2]==6)
                                {
                                        value[2]=0;
                                        value[1]++;
                                        if(value[0]==2&&value[1]==4)
                                        {
                                                value[0]=0;
                                                value[1]=0;
                                        }
                                        else if (value[0]<2&&value[1]==10)
                                        {
                                                value[1]=0;
                                                value[0]++;
                                        }
                                }
                        }
                
        }

       
}

void TIM1_IRQHander() interrupt 3
{
        TH1 = 0x0b;                             /* ����ת�ؼ�����ֵ */
        TL1 = 0xdc;
        if(state!=0&&state!=1&&state!=21&&state!=31&&state!=41&&state!=51&&state!=61)
                //�������������ʾ��״̬�͸�����2s���Զ��ص�����״̬
        {
                time1_interrupt_count++;                
                
                if(time1_interrupt_count >= 128)         
                {
                        time1_interrupt_count = 0;      // ����жϼ���ֵ
                        
                        state=0;
                }
        }
}
