#include "Motor.h"
#include "MyGlobe.h"
#include "delay.h"

void Motor_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(MOTOR_CONTROL_EN_PORT_CLK, ENABLE);//AHB1 ,168MHz
	GPIO_InitStructure.GPIO_Pin   =  MOTOR_CONTROL_EN_PIN;
	GPIO_InitStructure.GPIO_Mode  =  GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed =  GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType =  GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  =  GPIO_PuPd_DOWN;
	GPIO_Init(MOTOR_CONTROL_EN_PORT , &GPIO_InitStructure);
	GPIO_ResetBits(MOTOR_CONTROL_EN_PORT , MOTOR_CONTROL_EN_PIN);

	RCC_AHB1PeriphClockCmd(MOTOR_CONTROL_RESET_PORT_CLK, ENABLE);//AHB1 ,168MHz
	GPIO_InitStructure.GPIO_Pin   =  MOTOR_CONTROL_RESET_PIN;
	GPIO_InitStructure.GPIO_PuPd  =  GPIO_PuPd_DOWN;
	GPIO_Init(MOTOR_CONTROL_RESET_PORT , &GPIO_InitStructure);
	GPIO_SetBits(MOTOR_CONTROL_RESET_PORT , MOTOR_CONTROL_RESET_PIN);

	RCC_AHB1PeriphClockCmd(MOTOR_COM_SDI_PORT_CLK, ENABLE);//AHB1 ,168MHz
	GPIO_InitStructure.GPIO_Pin   =  MOTOR_COM_SDI_PIN;
	GPIO_InitStructure.GPIO_PuPd  =  GPIO_PuPd_DOWN;
	GPIO_Init(MOTOR_COM_SDI_PORT , &GPIO_InitStructure);

	RCC_AHB1PeriphClockCmd(MOTOR_COM_NSTR_PORT_CLK, ENABLE);//AHB1 ,168MHz
	GPIO_InitStructure.GPIO_Pin   =  MOTOR_COM_NSTR_PIN;
	GPIO_InitStructure.GPIO_PuPd  =  GPIO_PuPd_UP;
	GPIO_Init(MOTOR_COM_NSTR_PORT , &GPIO_InitStructure);

	RCC_AHB1PeriphClockCmd(MOTOR_COM_SDO_PORT_CLK, ENABLE);//AHB1 ,168MHz
	GPIO_InitStructure.GPIO_Pin   =  MOTOR_COM_SDO_PIN;
	GPIO_InitStructure.GPIO_Mode  =  GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_Speed =  GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType =  GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  =  GPIO_PuPd_UP;
	GPIO_Init(MOTOR_COM_SDO_PORT , &GPIO_InitStructure);

	GPIO_SetBits(MOTOR_COM_NSTR_PORT , MOTOR_COM_NSTR_PIN);

	RCC_AHB1PeriphClockCmd(MOTOR_PWM_OUT_PORT_CLK , ENABLE);

	GPIO_InitStructure.GPIO_Pin   = MOTOR_PWM_HA_PIN | MOTOR_PWM_LB_PIN;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_DOWN;     
	GPIO_Init(MOTOR_PWM_OUT_PORT , &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin   = MOTOR_PWM_NLA_PIN | MOTOR_PWM_NHB_PIN;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;     
	GPIO_Init(MOTOR_PWM_OUT_PORT , &GPIO_InitStructure);

	GPIO_ResetBits(MOTOR_PWM_OUT_PORT , MOTOR_PWM_HA_PIN );
	GPIO_SetBits(MOTOR_PWM_OUT_PORT , MOTOR_PWM_NLA_PIN );
	GPIO_SetBits(MOTOR_PWM_OUT_PORT , MOTOR_PWM_NHB_PIN );
	GPIO_ResetBits(MOTOR_PWM_OUT_PORT , MOTOR_PWM_LB_PIN );		

	//��ʱ������
	TIM_MOTOR_PWM_Init();
	MotorBrk();
}

/****
��ʱ�� PWM��ʼ��
****/
void TIM_MOTOR_PWM_Init(void)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    TIM_OCInitTypeDef  TIM_OCInitStructure;
	

    PWM_TIMER1_CLK_INIT(PWM_TIMER1_CLK, ENABLE);

    GPIO_PinAFConfig(MOTOR_PWM_OUT_PORT, MOTOR_PWM_HA_Pinsource,  MOTOR_PWM_OUT_AF_TIM );
    GPIO_PinAFConfig(MOTOR_PWM_OUT_PORT, MOTOR_PWM_NLA_Pinsource, MOTOR_PWM_OUT_AF_TIM );
		GPIO_PinAFConfig(MOTOR_PWM_OUT_PORT, MOTOR_PWM_NHB_Pinsource, MOTOR_PWM_OUT_AF_TIM );
    GPIO_PinAFConfig(MOTOR_PWM_OUT_PORT, MOTOR_PWM_LB_Pinsource,  MOTOR_PWM_OUT_AF_TIM );

    /* Time base configuration */
    TIM_TimeBaseStructure.TIM_Period = MAX_MOTOR_PWM - 1;
    
	TIM_TimeBaseStructure.TIM_Prescaler = (uint16_t) (((SystemCoreClock / 2) / PWM_MOTOR_FREQ) / MAX_MOTOR_PWM ) - 1;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_CenterAligned1;
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;

	TIM_TimeBaseInit(PWM_TIMER1, &TIM_TimeBaseStructure);

	TIM_ARRPreloadConfig(PWM_TIMER1, ENABLE);

	TIM_OCStructInit(&TIM_OCInitStructure);		
	/* PWM2 Mode configuration: */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0;

	/*Channel HA,LB*/
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;

	TIM_OC1Init(PWM_TIMER1, &TIM_OCInitStructure);    
	TIM_OC4Init(PWM_TIMER1, &TIM_OCInitStructure);


	/*Channel nLA,nHB*/
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

	TIM_OC2Init(PWM_TIMER1, &TIM_OCInitStructure);    
	TIM_OC3Init(PWM_TIMER1, &TIM_OCInitStructure);

	TIM_OC1PreloadConfig(PWM_TIMER1, TIM_OCPreload_Enable);
	TIM_OC2PreloadConfig(PWM_TIMER1, TIM_OCPreload_Enable);
	TIM_OC3PreloadConfig(PWM_TIMER1, TIM_OCPreload_Enable);
	TIM_OC4PreloadConfig(PWM_TIMER1, TIM_OCPreload_Enable);	

	TIM_Cmd(PWM_TIMER1, ENABLE);
	TIM_CtrlPWMOutputs(PWM_TIMER1, ENABLE);

	TIM_SelectOutputTrigger(PWM_TIMER1,TIM_TRGOSource_Update);
}


/* ����ر�*/
void MotorDisable(void)
{
    GPIO_ResetBits(MOTOR_CONTROL_EN_PORT , MOTOR_CONTROL_EN_PIN );  //��0��ʹ�ܹر�
}
/* �������*/
void MotorEnable(void)
{
    GPIO_SetBits(MOTOR_CONTROL_EN_PORT , MOTOR_CONTROL_EN_PIN );  //��1��ʹ�ܿ���
}

#define GHA_ON_PWM(PWM)   (TIM_SetCompare1(PWM_TIMER1,PWM))
#define GLA_OFF_PWM(PWM)  (TIM_SetCompare2(PWM_TIMER1,PWM)) 
#define GHB_OFF_PWM(PWM)  (TIM_SetCompare3(PWM_TIMER1,PWM))
#define GLB_ON_PWM(PWM)   (TIM_SetCompare4(PWM_TIMER1,PWM)) 

/****/
/* ɲ�� */
void MotorBrk(void)  //��H�ŵͶ˵�ͨ������Զ̽ӣ��Ե綯��ɲ��
{
    GHA_ON_PWM(0);
	GLA_OFF_PWM(0);
	GHB_OFF_PWM(MAX_MOTOR_PWM); 
	GLB_ON_PWM(MAX_MOTOR_PWM);
}

u8 MOTOR_INVERSE_DIR;
DRIVER_MODE_TypeDef DriverMode = SYNC_RECTIFY;

/***********�������**********************/
void Motor_PWM_Update(s32 PWM) //����PWMֵ
{
	if(MOTOR_INVERSE_DIR)	
	{
		PWM = -PWM;
	}
	if(PWM >= 0)
	{
		if(PWM >= MAX_MOTOR_PWM_LIMIT)
		{
			PWM = MAX_MOTOR_PWM;//ǿ����ռ�ձ�
		}
		
		switch( DriverMode )
		{
			case DIODE_RECTIFY:
				  if(PWM == 0)//ȫ��
					{
						GHA_ON_PWM(0);															 
						GLA_OFF_PWM(MAX_MOTOR_PWM);
						GHB_OFF_PWM(MAX_MOTOR_PWM);
						GLB_ON_PWM(0);
					}
					else
					{
						GHA_ON_PWM(0);															   //ʼ�չر�����MOS��
						GLA_OFF_PWM(0); 							 								 //ʼ�տ�ͨ����MOS��
						GHB_OFF_PWM(MAX_MOTOR_PWM - PWM);				       //����MOS�ܹؿ�
						GLB_ON_PWM(0);         				 								 //ʼ�չر�����MOS��
					}
					
					break;
			case SYNC_RECTIFY:                                 //�Ұ���ͬ���ؿ�����
					GHA_ON_PWM(0);															   //ʼ�չر�����MOS��
					GLA_OFF_PWM(0); 							 							   //ʼ�տ�ͨ����MOS��
					GHB_OFF_PWM(MAX_MOTOR_PWM - PWM);					     //����MOS�ܹؿ�
					GLB_ON_PWM(MAX_MOTOR_PWM - PWM);      		     //����MOS�ܿ���
					break;
			case FAST_DIODE_RECTIFY:                           //���º�����ͬ������
				  GHA_ON_PWM(0);															   //ʼ�չر�����MOS��
					GLA_OFF_PWM(MAX_MOTOR_PWM - PWM); 				     //����MOS�ܹؿ�
					GHB_OFF_PWM(MAX_MOTOR_PWM - PWM);					     //����MOS�ܹؿ�
					GLB_ON_PWM(0);         				 							   //ʼ�չر�����MOS��
					break;
			case FAST_SYNC_RECTIFY:                            //ȫ��ͬ��
					PWM = ( MAX_MOTOR_PWM + PWM )/2;
				  GHA_ON_PWM(MAX_MOTOR_PWM - PWM);					     //����MOS�ܿ���
					GLA_OFF_PWM(MAX_MOTOR_PWM - PWM); 				     //����MOS�ܹؿ�
					GHB_OFF_PWM(MAX_MOTOR_PWM - PWM);					     //����MOS�ܹؿ�
					GLB_ON_PWM(MAX_MOTOR_PWM - PWM);         	     //����MOS�ܿ���
				  break;			
		}	
		
	}
	else
	{
		PWM = -PWM;
		
		if(PWM >= MAX_MOTOR_PWM_LIMIT)
		{
			PWM = MAX_MOTOR_PWM;//ǿ����ռ�ձ�
		}
		
		switch(	DriverMode )
		{
			case DIODE_RECTIFY:
					GHA_ON_PWM(PWM);															 //����MOS�ܿ���
					GLA_OFF_PWM(MAX_MOTOR_PWM); 							     //ʼ�չر�����MOS��
					GHB_OFF_PWM(MAX_MOTOR_PWM);								     //ʼ�չر�����MOS��
					GLB_ON_PWM(MAX_MOTOR_PWM);         				     //ʼ�տ�ͨ����MOS��
					break;
			case SYNC_RECTIFY:                                 //�����ͬ�����عؿ�
					GHA_ON_PWM(PWM);															 //����MOS�ܿ���
					GLA_OFF_PWM(PWM); 							 							 //����MOS�ܹؿ�
					GHB_OFF_PWM(MAX_MOTOR_PWM);								     //ʼ�չر�����MOS��
					GLB_ON_PWM(MAX_MOTOR_PWM);         				     //ʼ�տ�ͨ����MOS��
					break;
			case FAST_DIODE_RECTIFY:                           //���Ϻ�����ͬ������
				  GHA_ON_PWM(PWM);															 //����MOS�ܿ���
					GLA_OFF_PWM(MAX_MOTOR_PWM); 							     //ʼ�չر�����MOS��
					GHB_OFF_PWM(MAX_MOTOR_PWM);								     //ʼ�չر�����MOS��
					GLB_ON_PWM(PWM);         				 							 //����MOS�ܿ���
					break;
			case FAST_SYNC_RECTIFY:                            //ȫ��ͬ��
					PWM = ( MAX_MOTOR_PWM + PWM )/2;
				  GHA_ON_PWM(PWM);															 //����MOS�ܿ���
					GLA_OFF_PWM(PWM); 							 							 //����MOS�ܹؿ�
					GHB_OFF_PWM(PWM);								               //����MOS�ܹؿ�
					GLB_ON_PWM(PWM);         				 							 //����MOS�ܿ���
					break;			
		}				
	} 
}
