#include <stdio.h>
#include <stdlib.h>
int main (void)
{
	int i=0,sum=0,wei;
 	char num[13]={0};
 	unsigned int xishu[12]={1,3,1,3,1,3,1,3,1,3,1,3};
	printf("请输入ISBN码的前12位\n");
	
	num[i] = getchar();
	while('0'<=num[i] && num[i] <= '9') 
	{
		i++;
		num[i] = getchar();
	}
	num[i]='\0';
	if (i<12)
	{
		printf("");
		exit(1);
	}
	printf("%s\n",num); 
	for(i=0;i<12;i++)
	{
		sum+=(num[i]-48)*xishu[i];
		
	}
	wei=sum%10;
	wei=10-wei;
	if(wei==10)
	{
		wei=0;
	}
	printf("%d",wei);
	return 0;	
} 

