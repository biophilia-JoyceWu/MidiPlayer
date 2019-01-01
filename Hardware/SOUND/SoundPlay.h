#include "timer.h"
#include "BEEP.h"
#include "delay.h"
#include "rgb.h"
#include "digital.h"
/*˵��**************************************************************************
 ���״�����ʽ unsigned char code MusicName{���ߣ����������ߣ�����...., 0,0};	ĩβ:0,0 ��ʾ����(Important)

 ��������λ������ɣ�
 		��λ�Ǳ�ʾ 1~7 ���߸����� 
 		ʮλ�Ǳ�ʾ�������ڵ�����:1-������2-������3-����;
 		��λ��ʾ��������Ƿ�Ҫ������: 0-������1-��������
 
 �����������λ������ɣ� 
 		��λ��ʾ������ʱֵ�����Ӧ��ϵ�ǣ� 
 			|��ֵ(n):  |0 |1 |2 |3 | 4 | 5 | 6 
 			|��������: |1 |2 |4 |8 |16 |32 |64 		����=2^n
 		ʮλ��ʾ����������Ч��(0-2):  0-��ͨ��1-������2-����
 		��λ�Ƿ���λ: 0-�޷��㣬1-�з���

 ���������ӳ���ĸ�ʽ
 		Play(������,����,�����˶�,�����ٶ�);
	|������           : Ҫ���ŵ�����ָ��,��β��(0,0)����;
	|����(0-11)       :	��ָ���������ٸ���������;
	|�����˶�(1-3)	  : 1:���˶�, 2:��������, 3:���˶�;
	|�����ٶ�(1-12000):	ֵԽ���ٶ�Խ��;

***************************************************************************/
#ifndef __SOUNDPLAY_H_REVISION_FIRST__
#define __SOUNDPLAY_H_REVISION_FIRST__

//**************************************************************************

#define SYSTEM_OSC 		72000000	//���徧��Ƶ��72000000HZ
#define SOUND_SPACE 	4/5 		//������ͨ��������ĳ��ȷ���,//ÿ4���������
#define PSC 71 //Ԥ��Ƶ


//**************************************************************************


//**************************************************************************
void Play(u16 *Sound,u16 Signature,u16 Octachord,u16 Speed)
{
	u16  FreTab[12]  = { 262,277,294,311,330,349,369,392,415,440,466,494 }; //ԭʼƵ�ʱ�
	u16 SignTab[7]  = { 0,2,4,5,7,9,11 }; 								  //1~7��Ƶ�ʱ��е�λ
	u16 LengthTab[7]= { 1,2,4,8,16,32,64 };						
	u16 NewFreTab[12];		//�µ�Ƶ�ʱ�
	u8 i,j;
	int len=0;
	u16 Point,LDiv,LDiv0,LDiv1,LDiv2,LDiv4,CurrentFre,Temp_T,SoundLength,ledpwm;
	u8 Tone,Length,SL,SH,SM,SLen,XG,FD;
	delay_init();
//	RGB_Init();
//	LEDR=1;
	for(i=0;i<12;i++) 				// ���ݵ��ż������˶��������µ�Ƶ�ʱ� 
	{
		j = i + Signature;
		if(j > 11)
		{
			j = j-12;
			NewFreTab[i] = FreTab[j]*2;
		}
		else
			NewFreTab[i] = FreTab[j];

		if(Octachord == 1)
			NewFreTab[i]>>=2;
		else if(Octachord == 3)
			NewFreTab[i]<<=2;
	}										
	
	SoundLength = 0;
	while(Sound[SoundLength] != 0x00)	//�����������
	{
		SoundLength+=2;
	}

	Point = 0;
	Tone   = Sound[Point];	
	Length = Sound[Point+1]; 			// ������һ����������ʱʱֵ
	
	LDiv0 = 60000/Speed;				// ���1�������ĳ���(����10ms) 	
	LDiv4 = LDiv0/4; 					// ���4�������ĳ��� 
	LDiv4 = LDiv4-LDiv4*SOUND_SPACE; 	// ��ͨ��������׼ 
	//TIM4_Int_Init(Sound_Temp_arr1,PSC);

	while(Point < SoundLength)
	{
		SL=Tone%10; 								//��������� 
		SM=Tone/10%10; 								//������ߵ��� 
		SH=Tone/100; 								//������Ƿ����� 
		CurrentFre = NewFreTab[SignTab[SL-1]+SH]; 	//�����Ӧ������Ƶ�� 	
//					TIM_SetCompare1(TIM4,ledpwm);
//			LEDR=TIM_GetCapture1(TIM4);	
		if(SL!=0)
		{
			if (SM==1) CurrentFre >>= 1; 		//���� 
			if (SM==3) CurrentFre <<= 1; 		//����
			Temp_T = 50000/CurrentFre;//�����������ֵ
			LEDB=1;
            LEDR=0;
			ledpwm=1000*(CurrentFre-130)/870;
			TIM3_Int_Init(1000,ledpwm,71);
			TIM2_Int_Init(Temp_T,PSC);
 
		}
		SLen=LengthTab[Length%10]; 	//����Ǽ�������
		XG=Length/10%10; 			//�����������(0��ͨ1����2����) 
		FD=Length/100;
		LDiv=LDiv0/SLen; 			//���������������ĳ���(���ٸ�10ms)
		if (FD==1) 
			LDiv=LDiv+LDiv/2;
		if(XG!=1)	
			if(XG==0) 				//�����ͨ���������೤�� 
				if (SLen<=4)	
					LDiv1=LDiv-LDiv4;
				else
					LDiv1=LDiv*SOUND_SPACE;
			else
				LDiv1=LDiv/2; 		//������������೤�� 
		else
			LDiv1=LDiv;
		if(SL==0) LDiv1=0;
			LDiv2=LDiv-LDiv1; 		//����������ĳ��� 
	  	if (SL!=0)
		{
			while(m_delay!=LDiv1/10);
			m_delay=0;
			len=len+LDiv1;
//			ShowData(len,1);
			BEEP=0;
		}
		if(LDiv2!=0)
		{
			BEEP=0;
			TIM2_Int_Init(65535,PSC);
			while(m_delay!=LDiv2/10);
			m_delay=0;
			
		}
		Point+=2; 
		Tone=Sound[Point];
		Length=Sound[Point+1];
	}

	BEEP = 0;
}

//************************************************u**************************
#endif
