#include "digital.h" 
#include "delay.h"

void DIG_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC, ENABLE);	 //ʹ��PA,PB,PC�˿�ʱ��
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_6;				      //LED0-->PA.5/6 �˿�����
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
 GPIO_Init(GPIOA, &GPIO_InitStructure);				     	 //�����趨������ʼ��GPIOA.8
 GPIO_SetBits(GPIOA,GPIO_Pin_5|GPIO_Pin_6);						        //PA.5/6 �����
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_14|GPIO_Pin_15;				      //LED0-->PA.8 �˿�����
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
 GPIO_Init(GPIOB, &GPIO_InitStructure);				     	 //�����趨������ʼ��GPIOA.8
 GPIO_SetBits(GPIOB,GPIO_Pin_12|GPIO_Pin_14|GPIO_Pin_15);						        //PA.8 �����	

 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;	    		 //LED1-->PD.2 �˿�����, �������
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   //�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
 GPIO_Init(GPIOC, &GPIO_InitStructure);	  				 //������� ��IO���ٶ�Ϊ50MHz
 GPIO_SetBits(GPIOC, GPIO_Pin_6|GPIO_Pin_7); 					    	 //PC ����� 
}

void HC595SendData(unsigned char SendVal)//��������
{  
  unsigned char i;
  for(i=0;i<8;i++) 
   {
if((SendVal<<i)&0x80) DDA=1;
else DDA=0;
DCK=0;//DDA Ϊ�������ݣ��� DCK �������أ������������뵽�ڲ��� 8 λλ�ƻ�����
delay_us(1);
delay_us(1);
DCK=1; 
   }
} 
void HC595ShowData()//�� DLC �������ؽ��� 8 λλ�ƻ����������ݴ��˵� 8 λƽ�����
{
  DLC=0;
  delay_us(1);
  delay_us(1);
  DLC=1; 
}

void ShowData(int Time,u8 loc,u8 time_start)
{
	u8 j,k=0;
	u16 temp[4];
	unsigned char Send[4], DIG_NUM[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0x88,0x83,0xc6,0xa1,0x86,0x8e};
	DIG_Init();
	temp[1]=0;
	if(Time==0)
	{
		temp[0]=0;
		k=1;
	}
	else
	{
	while(Time >0)
	{
		temp[k]=Time%10;
		Time=Time/10;
		k++;
	}
	}
	j=0;
	while(j<k)
	{
		Send[j]=DIG_NUM[temp[j]];
		j++;
	}
// 	if(time_start==0)
// 	{
// 		Send[1]-=0x80;
// 		if(temp[1]==0)
// 		Send[1]=0x40;
// 	}
		
// 	if(loc<k)
	{
 		HC595SendData(Send[loc]);
		HC595ShowData();
	}
	}
