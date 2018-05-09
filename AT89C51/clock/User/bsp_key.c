#include "bsp_key.h"
#include "bsp_delay.h"



/** 
 * @Description 按键扫描函数(8个按键同时扫描)
 * @return u8   按键键值
 */
u8 Key_Scan(void)
{
        /* 保存按键键值的变量，默认值0xff表示没有按键按下 */
        u8 keyValue = 0xff;
        
        /* 用于松手检测的累加变量 */
        int i = 0;
        
        /* 这里在1ms前后检测两边是为了滤除按键抖动产生的尖峰脉冲 */
        if(GPIO_KEY != 0xff)
        {
                delay(1);
                
                /* 如果1ms前后检测都是低电平的话，就说明是真的有按键按下 */
                if(GPIO_KEY != 0xff)
                {
                        /* 真的有按键按下，则将按键键值存入keyValue中 */
                        keyValue = GPIO_KEY;
                        
                        /* 这里是松手检测，在20ms内按键没有放开，程序会一直停在此处 */
                        /* 倘若50ms期间，松开了按键，则会跳出此while循环 */
                        /* 也就是说：按键没有松开的话，程序不会去做其他的事情 */
                        /* 当然也有松手检测的超时时间，就是我们设置的20ms */
                        while((i < 20) && (GPIO_KEY != 0xff))
                        {
                                delay(1);
                                i++;
                        }
                }
        }
        
        /* 返回按键的键值，通过解析这个键值，就能知道是哪一个按键按下 */
        return keyValue;
}

void Key_Control (u8 keyValue)
{
        switch(keyValue)
        {
                case(0xfe):                              //左/年
                        if(state==0)
                        {
                                state=2;
                        }
                        else
                        {
                                if(location>0)
                                {
                                        location-=1;
                                }
                        }
                
                break;
                case(0xfd):                             //右/日期
                        if(state==0)
                        {
                                state=3;
                        }
                        else
                        {
                                if(location<4)
                                {
                                        location+=1;
                                }
                        }
                break;
                case(0xfb):                          //设置
                        switch(state)
                        {
                                case(0):
                                        state=1;
                                break;
                                case(2):
                                        state=21;
                                        location=2;
                                break;
                                case(3):
                                        state=31;
                                break;
                                case(4):
                                        state=41;
                                break;
                                case(5):
                                        state=51;
                                break;
                                case(6):
                                        state=61;
                                break;
                        }
                        
                break;
                case(0xf7):                     //切换/星期
                        if(state==0)
                        {
                                state=4;
                        }
                        else if (state==1||state==21||state==31||state==41||state==51||state==61)
                        {
                                state=0;
                                location=0;
                        }
                break;
                case(0xef):                     //加/闹钟
                        switch(state)
                        {
                                case(0):
                                        state=5;
                                break;
                                case(1):
                                        if(value[0]==0&&location==0)
                                        {
                                                value[0]+=1;
                                        }
                                        else if(value[0]==1&&value[1]>3&&value[1]<=9&&location==0)
                                        {
                                                value[0]+=1;
                                                value[1]=3;
                                        }
                                        else if(value[0]<2&&value[1]<3&&location==0)
                                        {
                                                value[0]+=1;
                                        }
                                        else if ((value[0]<2&&value[1]<9&&location==1)||(value[0]==2&&value[1]<3&&location==1))
                                        {
                                                value[1]+=1;
                                        }
                                        else if(value[2]<5&&location==2)
                                        {
                                                value[2]+=1;
                                        }
                                        else if(value[3]<9&&location==3)
                                        {
                                                value[3]+=1;
                                        }
                                break;
                                case(21):
                                        if(nian[2]<9&&location==2)
                                        {
                                                nian[2]+=1;
                                        }
                                        else if(nian[3]<9&&location==3)
                                        {
                                                nian[3]+=1;
                                        }
                                break;
                                case(31):
                                        if(riqi[0]==0&&location==0)
                                        {
                                                riqi[0]+=1;
                                        }
                                        else if( ((riqi[0]*10+riqi[1]) <12 ) &&location==1)
                                        {
                                                riqi[1]+=1;
                                        }
                                        else if(riqi[2]<2  &&location==2)
                                        {
                                                riqi[2]+=1;
                                        }
                                        else if(riqi[2]==2  &&location==2)
                                        {
                                                riqi[2]+=1;
                                                riqi[3]=0;
                                        }
                                        else if(((riqi[2]*10+riqi[3]) <29 ) &&location==3)
                                        {
                                                riqi[3]+=1;
                                        }
                                        else if(riqi[2]==3&& riqi[3]==0 &&location==3)
                                        {
                                                riqi[3]+=1;
                                        }
                                break;
                                case(41):
                                        if(week<7&&location==2)
                                        {
                                                week+=1;
                                        }
                                break;
                                case(51):
                                        if(alarm[0]==0&&location==0)
                                        {
                                                alarm[0]+=1;
                                        }
                                        else if(alarm[0]==1&&alarm[1]>3&&alarm[1]<=9&&location==0)
                                        {
                                                alarm[0]+=1;
                                                alarm[1]=3;
                                        }
                                        else if(alarm[0]<2&&alarm[1]<3&&location==0)
                                        {
                                                alarm[0]+=1;
                                        }
                                        else if ((alarm[0]<2&&alarm[1]<9&&location==1)||(alarm[0]==2&&alarm[1]<3&&location==1))
                                        {
                                                alarm[1]+=1;
                                        }
                                        else if(alarm[2]<5&&location==2)
                                        {
                                                alarm[2]+=1;
                                        }
                                        else if(alarm[3]<9&&location==3)
                                        {
                                                alarm[3]+=1;
                                        }
                                break;
                                case(61):
                                        if(temp[0]<9&&location==0)
                                        {
                                                temp[0]+=1;
                                        }
                                        else if(temp[1]<9&&location==1)
                                        {
                                                temp[1]+=1;
                                        }
                                        else if(temp[2]<9&&location==2)
                                        {
                                                temp[2]+=1;
                                        }
                                        else if(temp[3]<9&&location==3)
                                        {
                                                temp[3]+=1;
                                        }
                                break;
                                        
                                        
                        }
                break;
                case(0xdf):                     //减/温度
                        switch(state)
                        {
                                case(0):
                                        state=6;
                                break;
                                case(1):
                                        if(value[0]>0&&location==0)
                                        {
                                                value[0]-=1;
                                        }
                                        else if(value[1]>0&&location==1)
                                        {
                                                value[1]-=1;
                                        }
                                        else if(value[2]>0&&location==2)
                                        {
                                                value[2]-=1;
                                        }
                                        else if(value[3]>0&&location==3)
                                        {
                                                value[3]-=1;
                                        }
                                break;
                                case(21):
                                        if(nian[0]>0&&location==0)
                                        {
                                                nian[0]-=1;
                                        }
                                        else if(nian[1]>0&&location==1)
                                        {
                                                nian[1]-=1;
                                        }
                                        else if(nian[2]>0&&location==2)
                                        {
                                                nian[2]-=1;
                                        }
                                        else if(nian[3]>0&&location==3)
                                        {
                                                nian[3]-=1;
                                        }
                                break;
                                case(31):
                                        if(riqi[0]>0&&location==0)
                                        {
                                                riqi[0]-=1;
                                        }
                                        else if(riqi[1]>0&&location==1)
                                        {
                                                riqi[1]-=1;
                                        }
                                        else if(riqi[2]>0&&location==2)
                                        {
                                                riqi[2]-=1;
                                        }
                                        else if(riqi[3]>0&&location==3)
                                        {
                                                riqi[3]-=1;
                                        }
                                break;
                                case(41):
                                        if(week>0&&location==2)
                                        {
                                                week-=1;
                                        }
                                break;
                                case(51):
                                        if(alarm[0]>0&&location==0)
                                        {
                                                alarm[0]-=1;
                                        }
                                        else if(alarm[1]>0&&location==1)
                                        {
                                                alarm[1]-=1;
                                        }
                                        else if(alarm[2]>0&&location==2)
                                        {
                                                alarm[2]-=1;
                                        }
                                        else if(alarm[3]>0&&location==3)
                                        {
                                                alarm[3]-=1;
                                        }
                                break;
                                case(61):
                                        if(temp[0]>0&&location==0)
                                        {
                                                temp[0]-=1;
                                        }
                                        else if(temp[1]>0&&location==1)
                                        {
                                                temp[1]-=1;
                                        }
                                        else if(temp[2]>0&&location==2)
                                        {
                                                temp[2]-=1;
                                        }
                                        else if(temp[3]>0&&location==3)
                                        {
                                                temp[3]-=1;
                                        }
                                break;
                                
                        }
                break;
                
        }
}



