#include "bsp_i2c.h"
#include "bsp_usart.h"
#include "bsp_systick.h"

void I2C_GPIO_Init (void)
{
	GPIO_InitTypeDef	 GPIO_Initstuct;
	
	RCC_APB2PeriphClockCmd(I2C_GPIO_CLK, ENABLE);		//开时钟
	
        GPIO_Initstuct.GPIO_Mode = GPIO_Mode_Out_PP;    //设置模式为推挽输出
	GPIO_Initstuct.GPIO_Speed = GPIO_Speed_50MHz;	//设置速度
        
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




////开始信号   模拟i2c时序
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
        
        /* 这里需要注意顺序, SDA 先拉高, SCL 再拉高 */
        /* 因为 SCL 为高电平的情况下, SDA 的边沿动作是有意义的, 因此 SDA 要先拉高 */
        I2C_SDA_1();
        I2C_SCL_1();
        delay_ms(10);
        
        /* 在 SCL 为高电平的情况下, SDA 产生一个下降沿表示起始*/
        I2C_SDA_0();
        delay_ms(10);
        
        /* 这里其实就是开始驱动传输的时钟了 */
        I2C_SCL_0();
}

//停止信号
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

//应答数据线应保持有效
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
//不应答数据线保持无效即可
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

//发送数据时钟线有效之前应准备好数据线
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

        /* 所有的数据的输出到 SDA 线上都是在 SCL 的低电平期间 */
        I2C_SCL_0();

        /* 依次发送8个数据值 */
        for(t = 0; t < 8; t++)
        {
                /* 写入数据的最高位 */
                *(I2Cx->SDA) = (data & 0x80) >> 7;

                /* 发送完了最高位, 数据左移一个, 次高位变成了新的最高位 */
                data <<= 1;
                delay_ms(5);

                /* 在 SCL 的上升沿(或者高电平期间), 数据被从机接收读取 */
                I2C_SCL_1();
                delay_ms(5);
                I2C_SCL_0();
                delay_ms(5);
        }
        /* 这函数结束的时候是不是 SCL = 0 */
        /* 一般这里接下来就会是 WaitResponse 操作了 */
        /* WaitResponse 的时候就是直接从 SCL = 0 开始的, 这样就不会多出来一个 SCL 的脉冲 */
}


//读取数据   通过查看SDA线的引脚电平   电平变化应在时钟线有效期间
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

//等待设备应答
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

//判断该地址设备是否存在
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











