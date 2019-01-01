#include "buzzer.h"
#include "delay.h"

void BUZZER_Init(void){ //�������Ľӿڳ�ʼ��
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	 //ʹ��GPIOA�˿�ʱ��
 
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;				 //BEEP-->PB.8 �˿�����
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 //�ٶ�Ϊ50MHz
 GPIO_Init(GPIOA, &GPIO_InitStructure);	 //���ݲ�����ʼ��GPIOA.8
 
 GPIO_SetBits(GPIOA,GPIO_Pin_8);//���0���رշ��������
}


uc16 music1[70]={ //����1�����ݱ�������������ż���ǳ��ȣ�
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

void MIDI_PLAY(void){ //MIDI����
	u16 i,e;
	for(i=0;i<35;i++){	//��35������
		for(e=0;e<music1[i*2]*music1[i*2+1]/1000;e++){ //һ����������һ�γ���
			BUZZER=0; //�������ӿ����0
			delay_us(500000/music1[i*2]); //��ʱ		
			BUZZER=1; //�������ӿ�����ߵ�ƽ1
			delay_us(500000/music1[i*2]); //��ʱ	
		}	
	}
}
