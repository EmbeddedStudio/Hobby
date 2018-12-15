#ifndef __BSP_KEY_H
#define __BSP_KEY_H

#include <reg52.h>

#define GPIO_KEY    P1

#define  u8  unsigned char

extern u8 location;
extern u8 temp[];
extern u8 week;
extern u8 nian[];
extern u8 riqi[];
extern u8 value[];
extern u8 alarm[];
extern u8 state;




u8 Key_Scan(void);
void key_control(u8 keyValue);

#endif /*__BSP_KEY_H*/
