#include "delay.h"
static u32  fac_us=0;//us延时倍乘数

//不支持ucos的延时，只用于系统初始化之前
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


//使用ucos进行延迟
void delay_init()	 
{
	u32 reload;
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);	//选择外部时钟  HCLK/8
	reload=SystemCoreClock/8000000;
	fac_us=SystemCoreClock/8000000;	
	reload*=1000000/OS_CFG_TICK_RATE_HZ; //根据OS_CFG_TICK_RATE_HZ设定溢出时间   
	SysTick->CTRL|=SysTick_CTRL_TICKINT_Msk;   	//开启SYSTICK中断
	SysTick->LOAD=reload-1; 	//每1/OS_TICKS_PER_SEC秒中断一次	
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk;   	//开启SYSTICK    
}			
void delay_us(u32 nus)
{		
	OS_ERR err;
  u32  reload;
	u32 ticks;	
	u32 told,tnow,tcnt=0;
	ticks=nus*fac_us; 			//需要的节拍数	  		 
	tcnt=0;
	reload=SysTick->LOAD;   //可能需要改为OS_CRITICAL_ENTER_CPU_EXIT() 来保证中断进入
	OSSchedLock(&err);
	told=SysTick->VAL;      //刚进入时的计数器值
	while(1)
	{
		tnow=SysTick->VAL;

		if(told != tnow)
		{
			if(tnow<told)tcnt+=told-tnow;//这里注意一下SYSTICK是一个递减的计数器就可以了.
			else tcnt+=reload-tnow+told;	    
			told=tnow;
	  }
    if(tcnt>=ticks)
		{			
		  break;//时间超过/等于要延迟的时间,则退出.	
		}			
	}
  OSSchedUnlock(&err);
}	

