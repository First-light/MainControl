/* Includes ------------------------------------------------------------------*/
#include "Encoder.h"
#include "stdbool.h"
#include  "EncodeParame.h"
#include "includes.h"
#include "globalTime.h"


/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

volatile EncoderTypeDef Encoder;
volatile float EncoderSpeedMeasure = 0;

void Encoder_Reset()
{
	TIM_SetCounter(ENC_TIMER, 0);

	Encoder.encoder = 0;
	Encoder.old_encoder = 0;
	Encoder.distance = 0;
}

void ENC_Light_Switch_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Pin = ENC_GPIO_PIN_A;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
	GPIO_Init(ENC_GPIO_A_PORT, &GPIO_InitStructure);
}

void ENC_Init(void)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd( ENC_GPIO_A_CLK | ENC_GPIO_B_CLK, ENABLE);	
	
	GPIO_InitStructure.GPIO_Pin = ENC_GPIO_PIN_A;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
	GPIO_Init(ENC_GPIO_A_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = ENC_GPIO_PIN_B;
	GPIO_Init(ENC_GPIO_B_PORT, &GPIO_InitStructure);
	
	GPIO_PinAFConfig(ENC_GPIO_A_PORT, ENC_GPIO_Pinsource_A, ENC_GPIO_AF_TIM);
	GPIO_PinAFConfig(ENC_GPIO_B_PORT, ENC_GPIO_Pinsource_B, ENC_GPIO_AF_TIM); 

	RCC_APB1PeriphClockCmd(ENC_TIMER_CLK, ENABLE);
	
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
	TIM_TimeBaseStructure.TIM_Prescaler = 0x0;  // No prescaling 
	TIM_TimeBaseStructure.TIM_Period = ENCODER_TIM_PERIOD;  
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	
	TIM_TimeBaseInit(ENC_TIMER, &TIM_TimeBaseStructure);
	
	// set them up as encoder inputs
	// set both inputs to rising polarity to let it use both edges
	TIM_EncoderInterfaceConfig(ENC_TIMER,TIM_EncoderMode_TI12,TIM_ICPolarity_Rising,TIM_ICPolarity_Rising);

	Encoder_Reset();	
	// turn on the timer/counters
	TIM_Cmd(ENC_TIMER, ENABLE);
	Encoder_Read();
}


void Encoder_Read()
{
	int16_t count;
	
	Encoder.old_encoder = Encoder.encoder;
	Encoder.encoder = TIM_GetCounter(ENC_TIMER);
	count = Encoder.encoder - Encoder.old_encoder;//�˴���������ת��uint16->int16,��Χ-32768~32767������1024��ת�����16000r/min�˺�������29ms���ڵ���һ��
	Encoder.distance += count;
}

float Enc_GetPosition(void)
{
	Encoder_Read();
	return ENC_DIR * Encoder.distance * ENC_PARA;
}


float watch = 1;
uint32_t coff = 1000000;
//�˺����������룡���������ڶ������Ҫ��д�˺���
//����1024��ת�����16000r/min�˺�������29ms���ڵ���һ��
float Enc_GetSpeed(void)
{
	  OS_ERR      err;
	  volatile static u16 pre_us_time = 0;
	  volatile static u16 old_encoder = 0;
	  
		static bool Enc_IsFirstMeasurement = true;
	  
		volatile uint16_t    now_us_t,d_us_t;
	  volatile uint16_t    now_encoder;
	  volatile int16_t     d_count;

		now_us_t    = DT_US_COUNT;
    now_encoder	= TIM_GetCounter(ENC_TIMER);

		d_us_t = now_us_t - pre_us_time;
	  d_count = now_encoder - old_encoder;
	
		pre_us_time = now_us_t;
		old_encoder = now_encoder;
	
		if (Enc_IsFirstMeasurement) 
		{
			Enc_IsFirstMeasurement = false; 
			return 0 ;
		}
    return d_count * (1000 * ENC_PARA) *1000* ENC_DIR/(float)d_us_t/6.0f;
}

float Enc_GetAcceleration(void)
{
	  OS_ERR      err;
	  volatile static u16 pre_us_time = 0;
	  volatile static u16 old_encoder_speed = 0;
	  
		static bool Enc_IsFirstMeasurement = true;
	  
		volatile uint16_t    now_us_t,d_us_t;
	  volatile uint16_t    now_encoder_speed;
	  volatile uint16_t     d_speed;

		now_us_t    = DT_US_COUNT;
    now_encoder_speed	= (uint32_t)EncoderSpeedMeasure;
	
		d_us_t = now_us_t - pre_us_time;
	  d_speed = now_encoder_speed - old_encoder_speed;
	
  	pre_us_time = now_us_t;
		old_encoder_speed = now_encoder_speed;
	
		if (Enc_IsFirstMeasurement) 
		{
			Enc_IsFirstMeasurement = false; 
			return 0 ;
		}
    return d_speed * 1000 *1000/(float)d_us_t/6.0f;
}

/******************* (C) COPYRIGHT 2017 HUST-Robocon *****END OF FILE**********/
