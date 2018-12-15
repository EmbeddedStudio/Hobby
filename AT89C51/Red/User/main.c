#include <reg52.h>
//�궨��
#define uint unsigned int
#define uchar unsigned char

//ʱ�����
#define Imax 14000    //�˴�Ϊ����Ϊ11.0592ʱ��ȡֵ, 
#define Imin 8000    //��������Ƶ�ʵľ���ʱ,
#define Inum1 1450    //Ҫ�ı���Ӧ��ȡֵ��
#define Inum2 700 
#define Inum3 3000 
//�������
unsigned char Im[4]={0x00,0x00,0x00,0x00};

//ȫ�ֱ���
uchar f;
unsigned long m,Tc;
unsigned char IrOK;


//������
void main()
{
        P2=0xff;
        
        EA=1;//�������ж�
         
        IT1=1;//�½�����Ч
        EX1=1;//�ⲿ�ж�1��
         
        TMOD=0x11;//��ʱ����ʼ��  
        TH0=0;//T0����ֵ
        TL0=0;
        TR0=0;//t0��ʼ��ʱ
        while(1)
        {
                if(IrOK==1) 
                {
                        //1��
                        if(Im[2]==0x0c)
                        {
                           P2=0xfc;
                        }
                        //2��
                        else if(Im[2]==0x18)
                        {
                           P2=0xa2;
                        }
                        //3��
                        else if(Im[2]==0x5e)
                        {
                           P2=0xb0;
                        }
                        //4
                        else if(Im[2]==0x08)
                        {
                           P2=0x9c;
                        }
                        //5
                        else if(Im[2]==0x1c)
                        {
                           P2=0x91;
                        }
                        //6
                        else if(Im[2]==0x5a)
                        {
                           P2=0x81;
                        }
                        //7��
                        else if(Im[2]==0x42)
                        {
                           P2=0xf8;
                        }
                        //8
                        else if(Im[2]==0x52) 
                        {
                           P2=0x80;
                        }
                        //9
                        else if(Im[2]==0x4a)
                        {
                           P2=0x90;
                        }
                        //0
                        else if(Im[2]==0x16)
                        {
                           P2=0xc0;
                        }
                        //�ػ�
                        else if(Im[2]==0x45)
                        {
                           P2=0xff;
                        }
                   IrOK=0;          
                }
        }
}

//�ⲿ�жϽ������_�ⲿ�ж�1using 1
void intersvr1(void) interrupt 2 
{
        TR0=1;
        Tc=TH0*256+TL0;//��ȡ�ж�ʱ����ʱ��
        TH0=0; 
        TL0=0;         //��ʱ�ж���������
        if((Tc>Imin)&&(Tc<Imax))
        { 
                m=0;
                f=1;
                return;
        }       //�ҵ���ʼ��
        if(f==1)
        {
                if(Tc>Inum1&&Tc<Inum3) 
                {
                        Im[m/8]=Im[m/8]>>1|0x80; m++; 
                }
                if(Tc>Inum2&&Tc<Inum1) 
                {
                        Im[m/8]=Im[m/8]>>1; m++; //ȡ��
                }
                if(m==32) 
                {
                        m=0;  
                        f=0;
                        if(Im[2]==~Im[3]) 
                        {
                                IrOK=1;
                                TR0=0; 
                        }
                        else IrOK=0;   //ȡ����ɺ��ж϶����Ƿ���ȷ
                }
                //׼������һ��
        }
}