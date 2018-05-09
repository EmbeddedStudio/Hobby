#include <reg51.h>

unsigned char i,j;

unsigned  char   selected[]={0x01,0x02,0x04,0x08,0x10,0x20};//位选数组

unsigned  char   table[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};//段选数组

unsigned  char number[] ={1,2,3,4,4,0};

void main()
{
	
	TMOD=0x01;
	TH0=0x0b;
	TL0=0xdc;
	IE=0x82;
	TR0=1;
	while (1)
	{
		for(i=0;i<6;i++)//循环6位
			{	
				P1 = selected[i];
				if (i==1||i==3)//加小数点
				{
					P0 = ~table[number[i]]|0x80;
					for(j=0;j<100;j++);
				}
				else
				{
					P0 = ~table[number[i]];
					for(j=0;j<100;j++);
				}
			}
	}
}

void fun() interrupt 1
{
	unsigned char a;
	TR0=0;
	TH0=0x0b;
	TL0=0xdc;
	TR0=1;
	a+=1;
	if (a>=16)
	{
		a=0;
		
		if (number[4]!=5)
		{
			if(number[5]<9)
			{
				number[5]+=1;
			}
			else
			{
				number[4]+=1;
				number[5]=0;				
			}
		}
		else
		{
			if(number[5]<9)
			{
				number[5]+=1;
			}
			else
			{
				number[3]+=1;
				number[4]=0;
				number[5]=0;
			}
		}
		
	}
}