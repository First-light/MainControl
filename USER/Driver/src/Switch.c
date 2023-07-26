#include "Switch.h"
#include "stm32f4xx.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
GPIO_TypeDef *SW_GPIO_PORT[SWn]	=	{SW1_GPIO_PORT, SW2_GPIO_PORT};
const uint16_t SW_PIN[SWn]			=	{SW1_PIN, SW2_PIN};
const uint16_t SW_GPIO_CLK[SWn]	=	{SW1_GPIO_CLK, SW2_GPIO_CLK};
/**
  * @brief  SW_Init
  * @param  SW
  * @retval None
  */
void SW_Init(SW_TypeDef SW)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(SW_GPIO_CLK[SW],ENABLE);

	GPIO_InitStructure.GPIO_Pin 		= 	SW_PIN[SW];
	GPIO_InitStructure.GPIO_Mode 		= 	GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_OType 	= 	GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed 	= 	GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd 		= 	GPIO_PuPd_UP;
	GPIO_Init(SW_GPIO_PORT[SW],&GPIO_InitStructure);
	
	//GPIO_ResetBits(SW_GPIO_PORT[SW],SW_PIN[SW]);	
//	GPIO_SetBits(SW_GPIO_PORT[SW],SW_PIN[SW]);	
}
/**
  * @brief  SW_InitAll
  * @param  None
  * @retval None
  */
void SW_InitAll(void)
{
  SW_Init(SW1);
	SW_Init(SW2);
}
/**
  * @brief  IsSW0Touched
  * @param  None
  * @retval true/false 
  */
bool IsSWTouched(SW_TypeDef SW_N)
{
  if(GPIO_ReadInputDataBit(SW_GPIO_PORT[SW_N],SW_PIN[SW_N]))
	{
		return true;
	}
  return false;  			
}
/******************* (C) COPYRIGHT 2014 HUST-Robocon *****END OF FILE**********/
