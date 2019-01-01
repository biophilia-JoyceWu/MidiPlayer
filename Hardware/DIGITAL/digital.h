#ifndef __DIGITAL_H
#define __DIGITAL_H
#include "sys.h"

#define DDA PBout(12)// PB12
#define DCK PBout(15)// PC14
#define DLC PBout(14)//PC15

#define DIG1 PCout(7)// PC7
#define DIG2 PCout(6)// PC6
#define DIG3 PAout(5)// PA5
#define DIG4 PAout(6)// PA6


void DIG_Init(void);//初始化
void HC595SendData(unsigned char SendVal);//发送数据
void HC595ShowData(void);
void ShowData(int Time,u8 loc,u8 time_start);

#endif
