#include "bsp_key.h" 
#include "bsp_delay.h" 

sbit K2 = P2^2;
sbit K3 = P2^3;
sbit K4 = P2^4;
sbit K5 = P2^0;
sbit K1 = P2^1;

extern u8 location;
extern u8 flag,wei;
extern  number[];
extern  nao[];

void key_scan()
{
	
	if(0 == K4)
	{
		// 按键消抖
		delay_ms(5);
		if(0 == K4);
		if(flag==1)//判断为设置界面
		{
			switch(wei)		//判断当前闪烁的位并给出相应的限制条件
			{
				case(0):
				if (number[wei]==1 && number[wei+1]>3)
				{
					
					number[wei+1] =3;
					number[wei] = number[wei] + 1;
				}
				else if(number[wei]<2)
				{
					number[wei] = number[wei] + 1;
				}
				
				break;
				case(1):
				if(number[wei-1]!=2)
				{
					if(number[wei]<9)
					{
						number[wei] = number[wei] + 1;
					}
				}
				else
				{
					if(number[wei]<3)
					{
						number[wei] = number[wei] + 1;
					}
				}
				break;
				case(2):
				if(number[wei]<5)	
				{
					number[wei] = number[wei] + 1;
				}
				break;
				case(3):
					if(number[wei]<9)
				{
					number[wei] = number[wei] + 1;
				}
				break;
				case(4):
				if (number[wei]<5)
				{
					number[wei] = number[wei] + 1;
				}
				
				break;
				case(5):
					if(number[wei]<9)
				{
					number[wei] = number[wei] + 1;
				}
				break;
			}
		}
		
		if (2==flag)		//判断当前为闹钟界面
		{
			switch(wei)		//判断当前闪烁的位并给出相应的限制条件
			{
				case(0):
				if (nao[wei]==1 && nao[wei+1]>3)
				{
					
					nao[wei+1] =3;
					nao[wei] = nao[wei] + 1;
				}
				else if(nao[wei]<2)
				{
					nao[wei] = nao[wei] + 1;
				}
				
				break;
				case(1):
				if(nao[wei-1]!=2)
				{
					if(nao[wei]<9)
					{
						nao[wei] = nao[wei] + 1;
					}
				}
				else
				{
					if(nao[wei]<3)
					{
						nao[wei] = nao[wei] + 1;
					}
				}
				break;
				case(2):
				if(nao[wei]<5)	
				{
					nao[wei] = nao[wei] + 1;
				}
				break;
				case(3):
					if(nao[wei]<9)
				{
					nao[wei] = nao[wei] + 1;
				}
				break;
			}
		}
		
		// 松手检测
		while(0 == K4);
	}
	
	if(0 == K3)
	{
		// 按键消抖
		delay_ms(5);
		if(0 == K3)
		{
			if (flag<2)	//以0 1 2 的状态方式切换
			{
				flag+=1;
				TR0=0;
			}
			else
			{
				flag=0;
				TR0=1;
			}
			
		}
		
		// 松手检测
		while(0 == K3);
	}

	if(0 == K2)
	{
		delay_ms(5);	//时间调整和闹钟的设置界面的减法设置
		if(0 == K2);
		if(flag==1)
		{
			
				if(0 != number[wei])  //因为每位的最低位是相同的所以代码可以简化为同一条代码
				{
					number[wei] = number[wei] - 1;
				}
			
		}
		
		if(flag==2)
		{
			
				if(0 != nao[wei])
				{
					nao[wei] = nao[wei] - 1;
				}
			
		}
		
		// 松手检测
		while(0 == K2);
	}
	if(0 == K5)
	{
		delay_ms(5);
		if(0 == K5)
		{
			if(5 != wei)
			{
				wei= wei+1;

			}
			
		}
		
		// 松手检测
		while(0 == K5);
	}
	if(0 == K1)
	{
		delay_ms(5);
		if(0 == K1)
		{
			
			 if(0!=wei)
			{
				wei=wei-1;

			}
		}
		
		// 松手检测
		while(0 == K1);
	}
}