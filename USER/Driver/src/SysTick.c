
#include "SysTick.h"

/**
  * @brief  ����ϵͳʱ�ӡ�
  * @param  None
  * @retval None
  */
void SysTick_Init(void)
{
	if (SysTick_Config(SystemCoreClock / 1000))     		//1ms
  {  
    while (1);
  }
	Close_System_Timer();
}
