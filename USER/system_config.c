#include "system_config.h"
#include "globalTime.h"

void System_Init(void)
{
	GlobeVariableInit();
	
	globalTimInit();
	
	#ifdef _USE_EASYSET
		EasySet();
	#endif	
	
	#ifdef _USE_CAN1
	CAN_Hard_Init(MYCAN1);
	CAN_Hard_Init(MYCAN2);
	#endif
	
	#ifdef _USE_LED
	LED_InitAll();
	#endif
	
	#ifdef _USE_SWITCH
	SW_InitAll();
	#endif

  #ifdef _USE_PC_USART
		USART_Hard_Init(MYUSART1);
		USART_Hard_Init(MYUSART2);
//		USART_Hard_Init(MYUSART3);
		USART_Hard_Init(MYUSART4);
  #endif

  #ifdef _USE_SPI
//	  SPI2_Init();
  #endif

	#ifdef _USE_EXT_IO
//	ExtIo_InitAll();
	#endif

	#ifdef _USE_MOTOR
  Motor_Init();
	MotorEnable();
  #endif
	
	#ifdef _USE_ENCODER
//	ENC_Init();
//  ENC_Light_Switch_Init();
	#endif

	#ifdef _USE_PID
	PidInit();
	#endif
	
	#ifdef _USE_Cylinder
	IIC_Hard_Init();
	#endif
	
	#ifdef _USE_TIM_FOR_VISUAL
//	TIM5_Int_Init(50-1,8400-1);	//��ʱ��ʱ��84M����Ƶϵ��8400������84M/8400=10Khz�ļ���Ƶ�ʣ�����5000��Ϊ500ms;����50�Σ�Ϊ5ms;
	#endif
	
	#ifdef _USE_LED_WS2815b
	TIM2_PWM_Init(105-1,1-1);	//84M/84=1Mhz�ļ���Ƶ��,��װ��ֵ500������PWMƵ��Ϊ 1M/500=2Khz.   
  WS2812B_TIM_init();
	#endif
}
