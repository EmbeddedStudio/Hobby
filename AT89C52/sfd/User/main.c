#include <reg51.h>
int a=0;//0x0a
void main()
{
			while(1)
			{
						P0=a;
			}
}
void exter0() interrupt 0
{
		a=~a;
}