#include "bsp_tpad.h"
#include "bsp_usart.h"
#include "stm32f10x.h"
#include "bsp_systick.h"
// 电容按键空载的时候充电时间
uint16_t tpad_default_val;


static void TPAD_TIM_GPIO_Config(void) 
{
	  GPIO_InitTypeDef GPIO_InitStructure;

	  // 输入捕获通道 GPIO 初始化
		RCC_APB2PeriphClockCmd(TPAD_TIM_CH_GPIO_CLK, ENABLE);
	  GPIO_InitStructure.GPIO_Pin =  TPAD_TIM_CH_PIN;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	  GPIO_Init(TPAD_TIM_CH_PORT, &GPIO_InitStructure);	
}

static void TPAD_TIM_Mode_Config(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;
	// 开启定时器时钟,即内部时钟 CK_INT=72M
	TPAD_TIM_APBxClock_FUN(TPAD_TIM_CLK,ENABLE);
	/*--------------------时基结构体初始化-------------------------*/
	// 自动重装载寄存器的值，累计 TIM_Period+1 个频率后产生一个更新或者中断
	TIM_TimeBaseStructure.TIM_Period=TPAD_TIM_Period;
	// 驱动 CNT 计数器的时钟 = Fck_int/(psc+1)
	TIM_TimeBaseStructure.TIM_Prescaler= TPAD_TIM_Prescaler;
	// 时钟分频因子 ，配置死区时间时需要用到
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	// 计数器计数模式，设置为向上计数
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
	// 重复计数器的值，没用到不用管
	TIM_TimeBaseStructure.TIM_RepetitionCounter=0;
	// 初始化定时器
	TIM_TimeBaseInit(TPAD_TIM, &TIM_TimeBaseStructure);
	/*--------------------输入捕获结构体初始化-------------------*/
		
	// 配置输入捕获的通道，需要根据具体的 GPIO 来配置
	TIM_ICInitStructure.TIM_Channel = TPAD_TIM_CHANNEL_x;
	// 输入捕获信号的极性配置
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
	// 输入通道和捕获通道的映射关系，有直连和非直连两种
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
	// 输入的需要被捕获的信号的分频系数
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
	// 输入的需要被捕获的信号的滤波系数
	TIM_ICInitStructure.TIM_ICFilter = 0;
	// 定时器输入捕获初始化
	TIM_ICInit(TPAD_TIM, &TIM_ICInitStructure);

	// 使能计数器
	TIM_Cmd(TPAD_TIM, ENABLE);
}


void TIM_TPAD_Init(void)
{
	TPAD_TIM_Mode_Config();
	TPAD_TIM_GPIO_Config();
}
void TPAD_Reset(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	// 输入捕获通道1 GPIO 初始化
	RCC_APB2PeriphClockCmd(TPAD_TIM_CH_GPIO_CLK, ENABLE);
	GPIO_InitStructure.GPIO_Pin =  TPAD_TIM_CH_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(TPAD_TIM_CH_PORT, &GPIO_InitStructure);
	
	// 连接TPAD的IO配置为输出，然后输出低电平，延时一会，确保电容按键放电完毕
	GPIO_ResetBits(TPAD_TIM_CH_PORT,TPAD_TIM_CH_PIN);
  
	// 放电是很快的，一般是us级别
	SysTick_Delay_Ms( 5 );
	
	// 连接TPAD的IO配置为输入，用于输入捕获
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(TPAD_TIM_CH_PORT, &GPIO_InitStructure);
}


uint16_t TPAD_Get_Val(void)
{
	// 每次捕获的时候，必须先复位放电
	TPAD_Reset();

	// 当电容按键复位放电之后，计数器清 0 开始计数
	TIM_SetCounter (TPAD_TIM,0);
	// 清除相关的标志位
	TIM_ClearITPendingBit (TPAD_TIM, TPAD_TIM_IT_CCx | TIM_IT_Update);
	// 等待捕获上升沿，当电容按键充电到 1.8V 左右的时候，就会被认为是上升沿
	while (TIM_GetFlagStatus (TPAD_TIM, TPAD_TIM_IT_CCx) == RESET) 
	{
		// 如果超时了,直接返回 CNT 的值
		// 一般充电时间都是在 ms 级别以内，很少会超过定时器的最大计数值
		if (TIM_GetCounter(TPAD_TIM) > TPAD_TIM_Period-100) 
		{
			 return TIM_GetCounter (TPAD_TIM);
		}
	}
	 // 获取捕获比较寄存器的值
	return TPAD_TIM_GetCapturex_FUN(TPAD_TIM);
}

uint8_t TPAD_Init(void)
{
	uint16_t temp;
	// 电容按键用到的输入捕获的 IO 和捕获模式参数初始化
	TIM_TPAD_Init();
	
	temp = TPAD_Get_Val();
	// 电容按键空载的充电时间非常稳定，不同的硬件充电时间不一样
	// 需要实际测试所得， 指南者 上的电容按键空载充电时间稳定在 76
	if ( (TPAD_DEFAULT_VAL_MIN<temp) && (temp<TPAD_DEFAULT_VAL_MAX) ) 
	{
		tpad_default_val = temp;
		// 调试的时候可以把捕获的值打印出来，看看默认的充电时间是多少
		printf("电容按键默认充电时间为: %d us\n",tpad_default_val);
		return 1; // 成功
	} 
	else 
	{
		return 0; // 失败
	}
}



uint16_t TPAD_Get_MaxVal( uint8_t num )
{
	uint16_t temp=0, res=0;
	 while (num--) 
	{
		temp = TPAD_Get_Val();
		if ( temp > res )
		res = temp;
	}
	return res;
}

uint8_t TPAD_Scan(void)
{
	// keyen：按键检测使能标志
	// 0：可以开始检测
	// >0：还不能开始检测，表示按键一直被按下
	// 注意： keytn 这个变量由 static
	//修饰，相当于一个全局变量，但是因为是在函数内部定义，
	// 所以是相当于这个函数的全局变量，每次修改之前保留的是上一次的值
	static uint8_t keyen=0;
	uint8_t res=0,sample=3;
	uint16_t scan_val;
	
	// 根据 sample 值采样多次，并取最大值，小的一般是干扰或者是误触摸
	scan_val = TPAD_Get_MaxVal(sample);
	
	// 当扫描的值大于空载值加上默认的门限值之后，表示按键按下
	// 这个 TPAD_GATE_VAL 根据硬件决定，需要实际测试
	if (scan_val > (tpad_default_val+TPAD_GATE_VAL)) 
	{
		// 再次检测，类似于机械按键的去抖
			
		scan_val = TPAD_Get_MaxVal(sample);
		if ( ( keyen == 0 )&& (scan_val > (tpad_default_val+TPAD_GATE_VAL)))
		res = 1; // 有效的按键

		// 如果按键一直被按下， keyen 的值会一直在 keyen 的初始值和 keyen-1 之间循环，永远不会等于 0
		keyen = 2;
	}

	// 当按键没有被按下或者 keyen>0 时，会执行 keyen--
	if ( keyen > 0)
	keyen--;

	 return res;
}


