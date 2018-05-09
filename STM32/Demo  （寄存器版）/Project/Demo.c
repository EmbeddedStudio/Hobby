#include "stm32f10x.h"

int main ()
{
		//打开GPIO的时钟
		*(unsigned int *) 0x40021018 |=((1)<<3);
		// 配置IO输出
		*(unsigned int *) 0x40010C00 |=((1)<<(4*0));
			//控制ODR寄存器
		*(unsigned int *) 0x40010C0C &=~(1<<0);
}

void SystemInit (void)
{

}
