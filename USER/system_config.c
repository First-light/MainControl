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
//	TIM5_Int_Init(50-1,8400-1);	//定时器时钟84M，分频系数8400，所以84M/8400=10Khz的计数频率，计数5000次为500ms;计数50次，为5ms;
	#endif
	
	#ifdef _USE_LED_WS2815b
	TIM2_PWM_Init(105-1,1-1);	//84M/84=1Mhz的计数频率,重装载值500，所以PWM频率为 1M/500=2Khz.   
  WS2812B_TIM_init();
	#endif
}
