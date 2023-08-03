#include "easyset.h"
#include <string.h>
#include <stdio.h>

void PWM_Set	(GPIO_TypeDef * GPIOx ,
				uint16_t pin,
				uint8_t GPIO_PinSourceX,
				uint8_t GPIO_AF_TIMx,
				TIM_TypeDef * TIMx)
{
	TIM_TimeBaseInitTypeDef TIM_Struct;
	TIM_OCInitTypeDef TIM_OC;
	GPIO_InitTypeDef GPIO_InitStruct;//����ṹ��
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin = pin;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;	
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOx,&GPIO_InitStruct);//����
	
	GPIO_PinAFConfig(GPIOx,GPIO_PinSourceX,GPIO_AF_TIMx);
	
	TIM_Struct.TIM_ClockDivision = TIM_CKD_DIV1;//�����벶�����
	TIM_Struct.TIM_CounterMode = TIM_CounterMode_Up;//����ģʽ��������
	TIM_Struct.TIM_Period = 500-1;  //�趨ʱ����
	TIM_Struct.TIM_Prescaler = 84-1;  //���Ƶ
	TIM_TimeBaseInit(TIMx,&TIM_Struct);	
	
	TIM_OC.TIM_OCMode = TIM_OCMode_PWM1;   //ѡ��pwm���ģʽ
	TIM_OC.TIM_OutputState = TIM_OutputState_Enable;  //����ʹ��
	//TIM_OC.TIM_Pulse = 50-1;                      //����ռ�ձ�
	TIM_OC.TIM_OCNPolarity = TIM_OCPolarity_High;     //��������Ч
	TIM_OC1Init(TIMx, &TIM_OC);  //����Tָ���Ĳ�����ʼ������TIM 4OC1
	TIM_OC1PreloadConfig(TIMx,TIM_OCPreload_Enable);  //ʹ��TIM��CCR1�ϵ�Ԥװ�ؼĴ���
	TIM_ARRPreloadConfig(TIMx,ENABLE);//ARPEʹ�� 
	TIM_Cmd(TIMx, ENABLE);  //ʹ��TIM
}

void NVICMode(int ChannelIRQn,int Priority,int SubPriority)
{//���жϴ򿪣�����NVIC
	NVIC_InitTypeDef NVIC_Struct;
	NVIC_Struct.NVIC_IRQChannel = ChannelIRQn;
	NVIC_Struct.NVIC_IRQChannelPreemptionPriority = Priority;
	NVIC_Struct.NVIC_IRQChannelSubPriority = SubPriority;
	NVIC_Struct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�������ȼ�Ⱥ��
	//0000�Ĵ�����λ�洢���ȼ���Ϣ��ģʽ��Ϊ2λ�����ȼ���2λ�����ȼ�
	//���������ȼ����Ϊ4�������ȼ����Ϊ3	
	NVIC_Init(&NVIC_Struct);
}


int32_t Pin_to_Int(uint16_t Input)
{
	int32_t Output = 0;
	switch(Input)
	{
		case GPIO_Pin_0: Output = 0 ;break; 
		case GPIO_Pin_1: Output = 1 ;break;
		case GPIO_Pin_2: Output = 2 ;break;
		case GPIO_Pin_3: Output = 3 ;break;
		case GPIO_Pin_4: Output = 4 ;break;
		case GPIO_Pin_5: Output = 5 ;break;
		case GPIO_Pin_6: Output = 6 ;break;
		case GPIO_Pin_7: Output = 7 ;break;
		case GPIO_Pin_8: Output = 8 ;break;
		case GPIO_Pin_9: Output = 9 ;break;
		case GPIO_Pin_10: Output = 10 ;break;
		case GPIO_Pin_11: Output = 11 ;break;
		case GPIO_Pin_12: Output = 12 ;break;
		case GPIO_Pin_13: Output = 13 ;break;
		case GPIO_Pin_14: Output = 14 ;break;
		case GPIO_Pin_15: Output = 15 ;break;
		default:break;
	}
	return Output;
} 

uint16_t Int_to_Pin(int32_t Input)
{
	uint16_t Output = 0x0000;
	switch(Input)
	{
		case 0: Output = GPIO_Pin_0 ;break; 
		case 1: Output = GPIO_Pin_1 ;break;
		case 2: Output = GPIO_Pin_2 ;break;
		case 3: Output = GPIO_Pin_3 ;break;
		case 4: Output = GPIO_Pin_4 ;break;
		case 5: Output = GPIO_Pin_5 ;break;
		case 6: Output = GPIO_Pin_6 ;break;
		case 7: Output = GPIO_Pin_7 ;break;
		case 8: Output = GPIO_Pin_8 ;break;
		case 9: Output = GPIO_Pin_9 ;break;
		case 10: Output = GPIO_Pin_10 ;break;
		case 11: Output = GPIO_Pin_11 ;break;
		case 12: Output = GPIO_Pin_12 ;break;
		case 13: Output = GPIO_Pin_13 ;break;
		case 14: Output = GPIO_Pin_14 ;break;
		case 15: Output = GPIO_Pin_15 ;break;
		default:break;
	}
	return Output;
} 


void Pin_Up(GPIO_TypeDef * GPIOx,int32_t pin)
{
	 GPIO_SetBits(GPIOx,Int_to_Pin(pin));
}

void Pin_Down(GPIO_TypeDef * GPIOx ,int32_t pin)
{
	 GPIO_ResetBits(GPIOx,Int_to_Pin(pin));
}

void PinMode(GPIO_TypeDef * GPIOx ,int32_t pin ,int32_t MODE ,int32_t LEVEL)
{
	GPIOMode_TypeDef MODE_t = GPIO_Mode_IN; //Ĭ������
	GPIOPuPd_TypeDef LEVEL_t = GPIO_PuPd_UP;
	GPIOOType_TypeDef OTYPE = GPIO_OType_OD;
	GPIO_InitTypeDef GPIO_InitStruct;//����ṹ��
		switch(MODE)
		{
			case INPUT: MODE_t = GPIO_Mode_IN;OTYPE = GPIO_OType_PP ;break;
			case OUTPUT: MODE_t = GPIO_Mode_OUT;OTYPE = GPIO_OType_PP ;break;
			default:break;
		}
		switch(LEVEL)
		{
			case HIGH: LEVEL_t = GPIO_PuPd_UP;break;
			case LOW:LEVEL_t = GPIO_PuPd_DOWN;break;
			default:break;
		}		
		GPIO_InitStruct.GPIO_Pin = Int_to_Pin(pin);
		GPIO_InitStruct.GPIO_Mode = MODE_t;
		GPIO_InitStruct.GPIO_OType = OTYPE;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStruct.GPIO_PuPd = LEVEL_t;
	
	GPIO_Init(GPIOx, &GPIO_InitStruct);
}

int32_t INT_CHAR_Change(char* ar)
{
	int32_t i = 0;
	int32_t back = 0;
	int32_t m = 0;
	
	while(ar[i] != '\0')
	{
		i++;
	}
	for(;i>0;i--)
	{
		int32_t num = 1;
		int32_t j = 0;
		for(j=i;j>1;j--)
		{
			num *= 10;
		}
		back += num*(ar[m] - '0');
		
		m++;
	}
	return back;
}

void CHAR_INT_Change(char* ar2,int32_t b)
{//intתchar*���ͺ���

	int32_t i;
	int32_t j;
	char ar[64] = {0};
	for(i=0;i <64;i++)
	{//��int��λת��Ϊchar��
		ar[i] = '0' + (b % 10);
		b /= 10;
		if(b == 0)
		{//���int���꣬����ѭ��
			break;
		}
	}
	strcpy(ar2,"\0");
	for(j = 0;i >= 0;i--,j++){
		ar2[i] = ar[j];//�����鵹��
	} 
}

void EasySet(void)
{
	//RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE); //�������ڶ�Ӧ��GPIOA��ʱ��
	//RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE); //�������ڶ�Ӧ��GPIOC��ʱ��
	//RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE); //�������ڶ�Ӧ��GPIOD��ʱ��
	//RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE); //������Ӧ��TIM3��ʱ��  
	
	//PinMode(LED2_GPIO,LED2_Pin,OUTPUT,HIGH);//D2
	//PinMode(LED3_GPIO,LED3_Pin,OUTPUT,HIGH);//D3
	
	//�Ÿ�ǰ�˴������źŽ���
	//PinMode(GPIOC,12,INPUT,HIGH);//���Ҷ˴�����
	//PinMode(GPIOD,0,INPUT,HIGH);//����
	//PinMode(GPIOD,1,INPUT,HIGH);
	//PinMode(GPIOD,2,INPUT,LOW);
	//PinMode(GPIOD,3,INPUT,LOW);
	//PinMode(GPIOD,4,INPUT,LOW);
	//PinMode(GPIOD,5,INPUT,LOW);
	//PinMode(GPIOD,6,INPUT,LOW);
	//PinMode(GPIOD,7,INPUT,LOW);	
 	//������
	//PinMode(GPIOA,0,OUTPUT,HIGH,0);
	//PinMode(GPIOA,1,INPUT,LOW,0);
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);//��������1��ʱ��
	//Timer_Set(TIM5,9,71);//��ʱ������
	//TIM_InternalClockConfig(TIM5);
	//NVIC_Set(TIM5_IRQn,1,3);//��ʱ���ж�ʹ��
}


