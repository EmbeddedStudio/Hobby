#include <stdio.h>
#include <stdlib.h>
char * ten2hex(int num)
{
	char buff[10]={0};
	char i=0,cnt=0;
	int num2;
//	printf("sdfsfwsdf\n");
	num2=num;
	while((num2/16)>0)
	{
		num2=num2/16;
		printf("num2:%d\n",num2);
		cnt++;
	}
//printf("cnt:%d\n",cnt);
	num2=num;
	for(i=cnt;i>=0;i--)
	{
		buff[i]=num%16;
		printf("buff[%d]:%d\n",i,buff[i]);
		num=(num-buff[i])/16;
	}
	
	for(i=cnt;i>=0;i--)
	{
		if(buff[i]<10)
		{
			buff[i]=buff[i]+' ';
		}
		else if((buff[i]<=16)&&buff[i]>=10)
		{
			buff[i]=buff[i]-10+'A'; 
		}
		printf("buff[%d]:%s",i,buff[i]);
	}
	buff[cnt+1]='\0';
	return buff ;
}


int main ()
{
	char *p;
	p=ten2hex(159);
	printf("%s",p);
	
	printf("\n ------------------\n");

	return 0;
} 
