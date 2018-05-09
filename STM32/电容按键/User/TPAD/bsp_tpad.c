#include "bsp_tpad.h"
#include "bsp_usart.h"
#include "stm32f10x.h"
#include "bsp_systick.h"
// ���ݰ������ص�ʱ����ʱ��
uint16_t tpad_default_val;


static void TPAD_TIM_GPIO_Config(void) 
{
	  GPIO_InitTypeDef GPIO_InitStructure;

	  // ���벶��ͨ�� GPIO ��ʼ��
		RCC_APB2PeriphClockCmd(TPAD_TIM_CH_GPIO_CLK, ENABLE);
	  GPIO_InitStructure.GPIO_Pin =  TPAD_TIM_CH_PIN;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	  GPIO_Init(TPAD_TIM_CH_PORT, &GPIO_InitStructure);	
}

static void TPAD_TIM_Mode_Config(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;
	// ������ʱ��ʱ��,���ڲ�ʱ�� CK_INT=72M
	TPAD_TIM_APBxClock_FUN(TPAD_TIM_CLK,ENABLE);
	/*--------------------ʱ���ṹ���ʼ��-------------------------*/
	// �Զ���װ�ؼĴ�����ֵ���ۼ� TIM_Period+1 ��Ƶ�ʺ����һ�����»����ж�
	TIM_TimeBaseStructure.TIM_Period=TPAD_TIM_Period;
	// ���� CNT ��������ʱ�� = Fck_int/(psc+1)
	TIM_TimeBaseStructure.TIM_Prescaler= TPAD_TIM_Prescaler;
	// ʱ�ӷ�Ƶ���� ����������ʱ��ʱ��Ҫ�õ�
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	// ����������ģʽ������Ϊ���ϼ���
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
	// �ظ���������ֵ��û�õ����ù�
	TIM_TimeBaseStructure.TIM_RepetitionCounter=0;
	// ��ʼ����ʱ��
	TIM_TimeBaseInit(TPAD_TIM, &TIM_TimeBaseStructure);
	/*--------------------���벶��ṹ���ʼ��-------------------*/
		
	// �������벶���ͨ������Ҫ���ݾ���� GPIO ������
	TIM_ICInitStructure.TIM_Channel = TPAD_TIM_CHANNEL_x;
	// ���벶���źŵļ�������
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
	// ����ͨ���Ͳ���ͨ����ӳ���ϵ����ֱ���ͷ�ֱ������
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
	// �������Ҫ��������źŵķ�Ƶϵ��
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
	// �������Ҫ��������źŵ��˲�ϵ��
	TIM_ICInitStructure.TIM_ICFilter = 0;
	// ��ʱ�����벶���ʼ��
	TIM_ICInit(TPAD_TIM, &TIM_ICInitStructure);

	// ʹ�ܼ�����
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

	// ���벶��ͨ��1 GPIO ��ʼ��
	RCC_APB2PeriphClockCmd(TPAD_TIM_CH_GPIO_CLK, ENABLE);
	GPIO_InitStructure.GPIO_Pin =  TPAD_TIM_CH_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(TPAD_TIM_CH_PORT, &GPIO_InitStructure);
	
	// ����TPAD��IO����Ϊ�����Ȼ������͵�ƽ����ʱһ�ᣬȷ�����ݰ����ŵ����
	GPIO_ResetBits(TPAD_TIM_CH_PORT,TPAD_TIM_CH_PIN);
  
	// �ŵ��Ǻܿ�ģ�һ����us����
	SysTick_Delay_Ms( 5 );
	
	// ����TPAD��IO����Ϊ���룬�������벶��
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(TPAD_TIM_CH_PORT, &GPIO_InitStructure);
}


uint16_t TPAD_Get_Val(void)
{
	// ÿ�β����ʱ�򣬱����ȸ�λ�ŵ�
	TPAD_Reset();

	// �����ݰ�����λ�ŵ�֮�󣬼������� 0 ��ʼ����
	TIM_SetCounter (TPAD_TIM,0);
	// �����صı�־λ
	TIM_ClearITPendingBit (TPAD_TIM, TPAD_TIM_IT_CCx | TIM_IT_Update);
	// �ȴ����������أ������ݰ�����絽 1.8V ���ҵ�ʱ�򣬾ͻᱻ��Ϊ��������
	while (TIM_GetFlagStatus (TPAD_TIM, TPAD_TIM_IT_CCx) == RESET) 
	{
		// �����ʱ��,ֱ�ӷ��� CNT ��ֵ
		// һ����ʱ�䶼���� ms �������ڣ����ٻᳬ����ʱ����������ֵ
		if (TIM_GetCounter(TPAD_TIM) > TPAD_TIM_Period-100) 
		{
			 return TIM_GetCounter (TPAD_TIM);
		}
	}
	 // ��ȡ����ȽϼĴ�����ֵ
	return TPAD_TIM_GetCapturex_FUN(TPAD_TIM);
}

uint8_t TPAD_Init(void)
{
	uint16_t temp;
	// ���ݰ����õ������벶��� IO �Ͳ���ģʽ������ʼ��
	TIM_TPAD_Init();
	
	temp = TPAD_Get_Val();
	// ���ݰ������صĳ��ʱ��ǳ��ȶ�����ͬ��Ӳ�����ʱ�䲻һ��
	// ��Ҫʵ�ʲ������ã� ָ���� �ϵĵ��ݰ������س��ʱ���ȶ��� 76
	if ( (TPAD_DEFAULT_VAL_MIN<temp) && (temp<TPAD_DEFAULT_VAL_MAX) ) 
	{
		tpad_default_val = temp;
		// ���Ե�ʱ����԰Ѳ����ֵ��ӡ����������Ĭ�ϵĳ��ʱ���Ƕ���
		printf("���ݰ���Ĭ�ϳ��ʱ��Ϊ: %d us\n",tpad_default_val);
		return 1; // �ɹ�
	} 
	else 
	{
		return 0; // ʧ��
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
	// keyen���������ʹ�ܱ�־
	// 0�����Կ�ʼ���
	// >0�������ܿ�ʼ��⣬��ʾ����һֱ������
	// ע�⣺ keytn ��������� static
	//���Σ��൱��һ��ȫ�ֱ�����������Ϊ���ں����ڲ����壬
	// �������൱�����������ȫ�ֱ�����ÿ���޸�֮ǰ����������һ�ε�ֵ
	static uint8_t keyen=0;
	uint8_t res=0,sample=3;
	uint16_t scan_val;
	
	// ���� sample ֵ������Σ���ȡ���ֵ��С��һ���Ǹ��Ż���������
	scan_val = TPAD_Get_MaxVal(sample);
	
	// ��ɨ���ֵ���ڿ���ֵ����Ĭ�ϵ�����ֵ֮�󣬱�ʾ��������
	// ��� TPAD_GATE_VAL ����Ӳ����������Ҫʵ�ʲ���
	if (scan_val > (tpad_default_val+TPAD_GATE_VAL)) 
	{
		// �ٴμ�⣬�����ڻ�е������ȥ��
			
		scan_val = TPAD_Get_MaxVal(sample);
		if ( ( keyen == 0 )&& (scan_val > (tpad_default_val+TPAD_GATE_VAL)))
		res = 1; // ��Ч�İ���

		// �������һֱ�����£� keyen ��ֵ��һֱ�� keyen �ĳ�ʼֵ�� keyen-1 ֮��ѭ������Զ������� 0
		keyen = 2;
	}

	// ������û�б����»��� keyen>0 ʱ����ִ�� keyen--
	if ( keyen > 0)
	keyen--;

	 return res;
}


