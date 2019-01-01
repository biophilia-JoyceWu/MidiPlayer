#include "buzzer.h"
#include "delay.h"

void BUZZER_Init(void){ //蜂鸣器的接口初始化
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	 //使能GPIOA端口时钟
 
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;				 //BEEP-->PB.8 端口配置
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 //速度为50MHz
 GPIO_Init(GPIOA, &GPIO_InitStructure);	 //根据参数初始化GPIOA.8
 
 GPIO_SetBits(GPIOA,GPIO_Pin_8);//输出0，关闭蜂鸣器输出
}


uc16 music1[70]={ //音乐1的数据表（奇数是音调，偶数是长度）
440,375,
494,375,
440,375,
988,375,
880,3375,
440,375,
494,375,
440,375,
740,375,
659,3375,
440,375,
494,375,
440,375,
740,375,
659,3375,
587,375,
494,375,
440,375,
988,375,
880,3375,
587,375,
659,375,
587,375,
1318,375,
1175,375,
1175,3000,
1318,375,
1109,375,
988,375,
880,1125,
740,750,
880,750,
880,750,
659,750,
659,3000
};

void MIDI_PLAY(void){ //MIDI音乐
	u16 i,e;
	for(i=0;i<35;i++){	//有35个音符
		for(e=0;e<music1[i*2]*music1[i*2+1]/1000;e++){ //一个音符播放一段长度
			BUZZER=0; //蜂鸣器接口输出0
			delay_us(500000/music1[i*2]); //延时		
			BUZZER=1; //蜂鸣器接口输出高电平1
			delay_us(500000/music1[i*2]); //延时	
		}	
	}
}
