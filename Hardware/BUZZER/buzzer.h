#ifndef __BUZZER_H
#define __BUZZER_H	 
#include "sys.h"

#define BUZZER PAout(8)	// BEEP,蜂鸣器接口		



void BUZZER_Init(void);//初始化
void MIDI_PLAY(void);
		 				    
#endif
