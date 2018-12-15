#include <stdio.h>

int main ()
{
	unsigned int i,j=1;
	for(i=1;i<=9;i++)
	{
	AA:	if(j<=i)
		{
			printf("%d*%d=%d  ", j, i, i*j); 
			j++;
		}
		if(i==(j-1))
		{
			j=1;
			goto BB;
		}
		else
		{
			goto  AA;
		}
	BB:	printf("\n");
	
	}	
	
	getchar();	
} 
