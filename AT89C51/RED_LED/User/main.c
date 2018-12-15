#include "reg52.h"      //���ļ��ж����˵�Ƭ����һЩ���⹦�ܼĴ���

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
        IT0=1;//�½��ش���
        EX0=1;//���ж�0����
        EA=1; //�����ж�
        
        IRIN=1;//��ʼ���˿�
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
        if(IRIN==0) //ȷ���Ƿ���Ľ��յ���ȷ���ź�
        { 
                
                err=1000; //1000*10us=10ms,����˵�����յ�������ź�
                /*������������Ϊ����ѭ���������һ������Ϊ�ٵ�ʱ������ѭ������ó�������ʱ
                �������������*/ 
                while((IRIN==0)&&(err>0)) //�ȴ�ǰ��9ms�ĵ͵�ƽ��ȥ 
                { 
                        delay(1);
                        err--;
                } 
                if(IRIN==1) //�����ȷ�ȵ�9ms�͵�ƽ
                {
                        err=500;
                        while((IRIN==1)&&(err>0)) //�ȴ�4.5ms����ʼ�ߵ�ƽ��ȥ
                        {
                                delay(1);
                                err--;
                        }
                        for(k=0;k<4;k++) //����4������
                        { 
                                for(j=0;j<8;j++) //����һ������
                                {

                                        err=60; 
                                        while((IRIN==0)&&(err>0))//�ȴ��ź�ǰ���560us�͵�ƽ��ȥ
                                        {
                                                delay(1);
                                                err--;
                                        }
                                        err=500;
                                        while((IRIN==1)&&(err>0)) //����ߵ�ƽ��ʱ�䳤�ȡ�
                                        {
                                                delay(10); //0.1ms
                                                Time++;
                                                err--;
                                                if(Time>30)
                                                {
                                                        return;
                                                }
                                        }
                                        IrValue[k]>>=1;  //k��ʾ�ڼ�������
                                        if(Time>=8) //����ߵ�ƽ���ִ���565us����ô��1
                                        {
                                                IrValue[k]|=0x80;
                                        }
                                        Time=0; //����ʱ��Ҫ���¸�ֵ 
                                }
                        }
                }
                if(IrValue[2]!=~IrValue[3])
                {
                        return;
                }
        } 
}

