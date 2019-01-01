#include "rgb.h"

//��ʼ��PC2/PC3/PC1Ϊ�����.��ʹ���������ڵ�ʱ��		    
//LED IO��ʼ��
void RGB_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC, ENABLE);	 //ʹ��PA,PB,PC�˿�ʱ��
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_5|GPIO_Pin_6;				      //LED0-->PA.8 �˿�����
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;		 //IO���ٶ�Ϊ50MHz
 GPIO_Init(GPIOA, &GPIO_InitStructure);				     	 //�����趨������ʼ��GPIOA.8
 GPIO_SetBits(GPIOA,GPIO_Pin_8|GPIO_Pin_5|GPIO_Pin_6);						        //PA.8 �����
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_14|GPIO_Pin_15;				      //LED0-->PA.8 �˿�����
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;		 //IO���ٶ�Ϊ50MHz
 GPIO_Init(GPIOB, &GPIO_InitStructure);				     	 //�����趨������ʼ��GPIOA.8
 GPIO_SetBits(GPIOB,GPIO_Pin_12|GPIO_Pin_14|GPIO_Pin_15);						        //PA.8 �����	

 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_6|GPIO_Pin_7;	    		 //LED1-->PD.2 �˿�����, �������
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   //�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;		 //IO���ٶ�Ϊ50MHz
 GPIO_Init(GPIOC, &GPIO_InitStructure);	  				 //������� ��IO���ٶ�Ϊ50MHz
 GPIO_SetBits(GPIOC,GPIO_Pin_12|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_6|GPIO_Pin_7); 	
}


 
