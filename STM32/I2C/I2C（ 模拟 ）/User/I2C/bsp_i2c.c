#include "bsp_i2c.h"
#include "bsp_usart.h"
#include "bsp_systick.h"

void I2C_GPIO_Init (void)
{
	GPIO_InitTypeDef	 GPIO_Initstuct;
	
	RCC_APB2PeriphClockCmd(I2C_GPIO_CLK, ENABLE);		//��ʱ��
	
        GPIO_Initstuct.GPIO_Mode = GPIO_Mode_Out_PP;    //����ģʽΪ�������
	GPIO_Initstuct.GPIO_Speed = GPIO_Speed_50MHz;	//�����ٶ�
        
	GPIO_Initstuct.GPIO_Pin = I2C_SDA_PIN;
        GPIO_Init(I2C_GPIO_PORT, &GPIO_Initstuct);
        
        GPIO_Initstuct.GPIO_Pin = I2C_SCL_PIN;	
	GPIO_Init(I2C_GPIO_PORT, &GPIO_Initstuct);
        
//        I2C_Stop();
}

void I2C_In_GPIO_Config (void)
{
        GPIO_InitTypeDef GPIO_InitStructure;
        GPIO_InitStructure.GPIO_Pin = I2C_SDA_PIN;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_Init(I2C_GPIO_PORT,&GPIO_InitStructure);
}

void I2C_Out_GPIO_Config (void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
        GPIO_InitStructure.GPIO_Pin = I2C_SDA_PIN;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(I2C_GPIO_PORT,&GPIO_InitStructure);

}




////��ʼ�ź�   ģ��i2cʱ��
//void I2C_Start(void)
//{
//        
//        I2C_Out_GPIO_Config();
//        I2C_SDA_1();
//        I2C_SCL_1();
//        delay_ms(10);
//        I2C_SDA_0();
//        delay_ms(10);
//        I2C_SCL_0();
//        delay_ms(10);
//}

void I2C_Start()
{
        I2C_Out_GPIO_Config();
        
        /* ������Ҫע��˳��, SDA ������, SCL ������ */
        /* ��Ϊ SCL Ϊ�ߵ�ƽ�������, SDA �ı��ض������������, ��� SDA Ҫ������ */
        I2C_SDA_1();
        I2C_SCL_1();
        delay_ms(10);
        
        /* �� SCL Ϊ�ߵ�ƽ�������, SDA ����һ���½��ر�ʾ��ʼ*/
        I2C_SDA_0();
        delay_ms(10);
        
        /* ������ʵ���ǿ�ʼ���������ʱ���� */
        I2C_SCL_0();
}

//ֹͣ�ź�
void I2C_Stop(void)
{
        I2C_GPIO_Init();
        I2C_Out_GPIO_Config();
        I2C_SDA_0();
        delay_ms(1);
        I2C_SCL_1();
        delay_ms(1);
        I2C_SDA_1();    
        delay_ms(1);
        I2C_SCL_0();
}

//Ӧ��������Ӧ������Ч
void I2C_Ask(void)
{
        I2C_Out_GPIO_Config();
        I2C_SDA_0();
        delay_ms(1);
        I2C_SCL_1();
        delay_ms(1);
        I2C_SCL_0();
        delay_ms(1);
        I2C_SDA_1();
}
//��Ӧ�������߱�����Ч����
void I2C_Nask(void)
{
        I2C_Out_GPIO_Config();
        I2C_SDA_1();
        delay_ms(1);
        I2C_SCL_1();
        delay_ms(1);
        I2C_SCL_0();
        delay_ms(1);
}

//��������ʱ������Ч֮ǰӦ׼����������
//void I2C_SentData(uint8_t Data)
//{
//        uint8_t i;
//        I2C_Out_GPIO_Config();
//        I2C_SCL_0();
//        delay_ms(5);
//        for(i=0; i<8; i++)
//        {
//                if(Data & 0x80)
//                {
//                      I2C_SDA_1();
//                }
//                else
//                {
//                      I2C_SDA_0();  
//                }
//                delay_ms(5);
//                I2C_SCL_1();
//                delay_ms(10);
//                I2C_SCL_0();
//                delay_ms(5);
//                Data = Data << 1;
//        }
//}


void I2C_SentData( u8 data)
{
        u8 t;
        I2C_Out_GPIO_Config();

        /* ���е����ݵ������ SDA ���϶����� SCL �ĵ͵�ƽ�ڼ� */
        I2C_SCL_0();

        /* ���η���8������ֵ */
        for(t = 0; t < 8; t++)
        {
                /* д�����ݵ����λ */
                *(I2Cx->SDA) = (data & 0x80) >> 7;

                /* �����������λ, ��������һ��, �θ�λ������µ����λ */
                data <<= 1;
                delay_ms(5);

                /* �� SCL ��������(���߸ߵ�ƽ�ڼ�), ���ݱ��ӻ����ն�ȡ */
                I2C_SCL_1();
                delay_ms(5);
                I2C_SCL_0();
                delay_ms(5);
        }
        /* �⺯��������ʱ���ǲ��� SCL = 0 */
        /* һ������������ͻ��� WaitResponse ������ */
        /* WaitResponse ��ʱ�����ֱ�Ӵ� SCL = 0 ��ʼ��, �����Ͳ�������һ�� SCL ������ */
}


//��ȡ����   ͨ���鿴SDA�ߵ����ŵ�ƽ   ��ƽ�仯Ӧ��ʱ������Ч�ڼ�
uint8_t I2C_ReadData(void)
{
        uint8_t i;
        uint8_t DATA=0;
        printf("[i2c][%d] %s  \r\n", __LINE__, __FUNCTION__);
        I2C_In_GPIO_Config();
        for(i=0; i<8; i++)
        {
                DATA<<=1;
                I2C_SCL_1();
                delay_ms(1);
                if( I2C_SDA_READ() )
                {
                        DATA++;
                }
                I2C_SCL_0();
                delay_ms(1);
        }
        
        return DATA;
}

//�ȴ��豸Ӧ��
uint8_t I2C_WiteAsk(void)
{
        
        uint8_t ASK;
       
        I2C_SDA_1();
        delay_ms(1);
        I2C_SCL_1();
        delay_ms(1);
        I2C_In_GPIO_Config();
        
        if(I2C_SDA_READ())
        {
                
                ASK = 1;
        }
        else
        {
                ASK = 0;
        }
        
        I2C_SCL_0();
        delay_ms(1);
        return ASK;
}

//�жϸõ�ַ�豸�Ƿ����
uint8_t I2C_Device(uint8_t ADDR)
{
        uint8_t AS;
        I2C_Out_GPIO_Config();
        I2C_GPIO_Init();
        I2C_Start();
        I2C_SentData(ADDR);
        AS = I2C_WiteAsk();
        I2C_Stop();
        return AS;    
}











