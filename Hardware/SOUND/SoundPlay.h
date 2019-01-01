#include "timer.h"
#include "BEEP.h"
#include "delay.h"
#include "rgb.h"
#include "digital.h"
/*说明**************************************************************************
 曲谱存贮格式 unsigned char code MusicName{音高，音长，音高，音长...., 0,0};	末尾:0,0 表示结束(Important)

 音高由三位数字组成：
 		个位是表示 1~7 这七个音符 
 		十位是表示音符所在的音区:1-低音，2-中音，3-高音;
 		百位表示这个音符是否要升半音: 0-不升，1-升半音。
 
 音长最多由三位数字组成： 
 		个位表示音符的时值，其对应关系是： 
 			|数值(n):  |0 |1 |2 |3 | 4 | 5 | 6 
 			|几分音符: |1 |2 |4 |8 |16 |32 |64 		音符=2^n
 		十位表示音符的演奏效果(0-2):  0-普通，1-连音，2-顿音
 		百位是符点位: 0-无符点，1-有符点

 调用演奏子程序的格式
 		Play(乐曲名,调号,升降八度,演奏速度);
	|乐曲名           : 要播放的乐曲指针,结尾以(0,0)结束;
	|调号(0-11)       :	是指乐曲升多少个半音演奏;
	|升降八度(1-3)	  : 1:降八度, 2:不升不降, 3:升八度;
	|演奏速度(1-12000):	值越大速度越快;

***************************************************************************/
#ifndef __SOUNDPLAY_H_REVISION_FIRST__
#define __SOUNDPLAY_H_REVISION_FIRST__

//**************************************************************************

#define SYSTEM_OSC 		72000000	//定义晶振频率72000000HZ
#define SOUND_SPACE 	4/5 		//定义普通音符演奏的长度分率,//每4分音符间隔
#define PSC 71 //预分频


//**************************************************************************


//**************************************************************************
void Play(u16 *Sound,u16 Signature,u16 Octachord,u16 Speed)
{
	u16  FreTab[12]  = { 262,277,294,311,330,349,369,392,415,440,466,494 }; //原始频率表
	u16 SignTab[7]  = { 0,2,4,5,7,9,11 }; 								  //1~7在频率表中的位
	u16 LengthTab[7]= { 1,2,4,8,16,32,64 };						
	u16 NewFreTab[12];		//新的频率表
	u8 i,j;
	int len=0;
	u16 Point,LDiv,LDiv0,LDiv1,LDiv2,LDiv4,CurrentFre,Temp_T,SoundLength,ledpwm;
	u8 Tone,Length,SL,SH,SM,SLen,XG,FD;
	delay_init();
//	RGB_Init();
//	LEDR=1;
	for(i=0;i<12;i++) 				// 根据调号及升降八度来生成新的频率表 
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
	while(Sound[SoundLength] != 0x00)	//计算歌曲长度
	{
		SoundLength+=2;
	}

	Point = 0;
	Tone   = Sound[Point];	
	Length = Sound[Point+1]; 			// 读出第一个音符和它时时值
	
	LDiv0 = 60000/Speed;				// 算出1分音符的长度(几个10ms) 	
	LDiv4 = LDiv0/4; 					// 算出4分音符的长度 
	LDiv4 = LDiv4-LDiv4*SOUND_SPACE; 	// 普通音最长间隔标准 
	//TIM4_Int_Init(Sound_Temp_arr1,PSC);

	while(Point < SoundLength)
	{
		SL=Tone%10; 								//计算出音符 
		SM=Tone/10%10; 								//计算出高低音 
		SH=Tone/100; 								//计算出是否升半 
		CurrentFre = NewFreTab[SignTab[SL-1]+SH]; 	//查出对应音符的频率 	
//					TIM_SetCompare1(TIM4,ledpwm);
//			LEDR=TIM_GetCapture1(TIM4);	
		if(SL!=0)
		{
			if (SM==1) CurrentFre >>= 1; 		//低音 
			if (SM==3) CurrentFre <<= 1; 		//高音
			Temp_T = 50000/CurrentFre;//计算计数器初值
			LEDB=1;
            LEDR=0;
			ledpwm=1000*(CurrentFre-130)/870;
			TIM3_Int_Init(1000,ledpwm,71);
			TIM2_Int_Init(Temp_T,PSC);
 
		}
		SLen=LengthTab[Length%10]; 	//算出是几分音符
		XG=Length/10%10; 			//算出音符类型(0普通1连音2顿音) 
		FD=Length/100;
		LDiv=LDiv0/SLen; 			//算出连音音符演奏的长度(多少个10ms)
		if (FD==1) 
			LDiv=LDiv+LDiv/2;
		if(XG!=1)	
			if(XG==0) 				//算出普通音符的演奏长度 
				if (SLen<=4)	
					LDiv1=LDiv-LDiv4;
				else
					LDiv1=LDiv*SOUND_SPACE;
			else
				LDiv1=LDiv/2; 		//算出顿音的演奏长度 
		else
			LDiv1=LDiv;
		if(SL==0) LDiv1=0;
			LDiv2=LDiv-LDiv1; 		//算出不发音的长度 
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
