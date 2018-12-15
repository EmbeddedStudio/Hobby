#include <reg52.h>
//宏定义
#define uint unsigned int
#define uchar unsigned char

//时间计算
#define Imax 14000    //此处为晶振为11.0592时的取值, 
#define Imin 8000    //如用其它频率的晶振时,
#define Inum1 1450    //要改变相应的取值。
#define Inum2 700 
#define Inum3 3000 
//解码变量
unsigned char Im[4]={0x00,0x00,0x00,0x00};

//全局变量
uchar f;
unsigned long m,Tc;
unsigned char IrOK;


//主函数
void main()
{
        P2=0xff;
        
        EA=1;//开启总中断
         
        IT1=1;//下降沿有效
        EX1=1;//外部中断1开
         
        TMOD=0x11;//定时器初始化  
        TH0=0;//T0赋初值
        TL0=0;
        TR0=0;//t0开始计时
        while(1)
        {
                if(IrOK==1) 
                {
                        //1键
                        if(Im[2]==0x0c)
                        {
                           P2=0xfc;
                        }
                        //2键
                        else if(Im[2]==0x18)
                        {
                           P2=0xa2;
                        }
                        //3键
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
                        //7键
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
                        //关机
                        else if(Im[2]==0x45)
                        {
                           P2=0xff;
                        }
                   IrOK=0;          
                }
        }
}

//外部中断解码程序_外部中断1using 1
void intersvr1(void) interrupt 2 
{
        TR0=1;
        Tc=TH0*256+TL0;//提取中断时间间隔时长
        TH0=0; 
        TL0=0;         //定时中断重新置零
        if((Tc>Imin)&&(Tc<Imax))
        { 
                m=0;
                f=1;
                return;
        }       //找到启始码
        if(f==1)
        {
                if(Tc>Inum1&&Tc<Inum3) 
                {
                        Im[m/8]=Im[m/8]>>1|0x80; m++; 
                }
                if(Tc>Inum2&&Tc<Inum1) 
                {
                        Im[m/8]=Im[m/8]>>1; m++; //取码
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
                        else IrOK=0;   //取码完成后判断读码是否正确
                }
                //准备读下一码
        }
}