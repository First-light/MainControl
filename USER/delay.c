#include "delay.h"
static u32  fac_us=0;//us��ʱ������

//��֧��ucos����ʱ��ֻ����ϵͳ��ʼ��֮ǰ
void MyDelayms(u32 nCount)
{
	uint16_t i;
	for(;nCount > 0;nCount--)
		for(i=39999;i>0;i--);
}

void MyDelayus(u32 nCount)
{
	uint16_t i;
	for(;nCount > 0;nCount--)
		for(i=39;i>0;i--);
}


//ʹ��ucos�����ӳ�
void delay_init()	 
{
	u32 reload;
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);	//ѡ���ⲿʱ��  HCLK/8
	reload=SystemCoreClock/8000000;
	fac_us=SystemCoreClock/8000000;	
	reload*=1000000/OS_CFG_TICK_RATE_HZ; //����OS_CFG_TICK_RATE_HZ�趨���ʱ��   
	SysTick->CTRL|=SysTick_CTRL_TICKINT_Msk;   	//����SYSTICK�ж�
	SysTick->LOAD=reload-1; 	//ÿ1/OS_TICKS_PER_SEC���ж�һ��	
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk;   	//����SYSTICK    
}			
void delay_us(u32 nus)
{		
	OS_ERR err;
  u32  reload;
	u32 ticks;	
	u32 told,tnow,tcnt=0;
	ticks=nus*fac_us; 			//��Ҫ�Ľ�����	  		 
	tcnt=0;
	reload=SysTick->LOAD;   //������Ҫ��ΪOS_CRITICAL_ENTER_CPU_EXIT() ����֤�жϽ���
	OSSchedLock(&err);
	told=SysTick->VAL;      //�ս���ʱ�ļ�����ֵ
	while(1)
	{
		tnow=SysTick->VAL;

		if(told != tnow)
		{
			if(tnow<told)tcnt+=told-tnow;//����ע��һ��SYSTICK��һ���ݼ��ļ������Ϳ�����.
			else tcnt+=reload-tnow+told;	    
			told=tnow;
	  }
    if(tcnt>=ticks)
		{			
		  break;//ʱ�䳬��/����Ҫ�ӳٵ�ʱ��,���˳�.	
		}			
	}
  OSSchedUnlock(&err);
}	

