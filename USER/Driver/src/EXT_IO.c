#include "EXT_IO.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
GPIO_TypeDef* EXT_IO_GPIO_PORT[EXT_IOn] = {	
				EXT_IO0_GPIO_PORT,EXT_IO1_GPIO_PORT,EXT_IO2_GPIO_PORT,EXT_IO3_GPIO_PORT	,EXT_IO4_GPIO_PORT,EXT_IO5_GPIO_PORT,EXT_IO6_GPIO_PORT,EXT_IO7_GPIO_PORT
																											};

const uint16_t EXT_IO_PIN[EXT_IOn] = {	
				EXT_IO0_PIN,EXT_IO1_PIN,EXT_IO2_PIN,EXT_IO3_PIN,EXT_IO4_PIN,EXT_IO5_PIN,EXT_IO6_PIN,EXT_IO7_PIN
																								 };

const uint32_t EXT_IO_GPIO_CLK[EXT_IOn] = {	
				EXT_IO0_GPIO_CLK,EXT_IO1_GPIO_CLK,EXT_IO2_GPIO_CLK,EXT_IO3_GPIO_CLK,EXT_IO4_GPIO_CLK,EXT_IO5_GPIO_CLK,EXT_IO6_GPIO_CLK,EXT_IO7_GPIO_CLK
																											};

const GPIOMode_TypeDef EXT_IO_GPIO_MODE[EXT_IOn] = {
			  EXT_IO0_GPIO_MODE,EXT_IO1_GPIO_MODE,EXT_IO2_GPIO_MODE,EXT_IO3_GPIO_MODE,EXT_IO4_GPIO_MODE,EXT_IO5_GPIO_MODE,EXT_IO6_GPIO_MODE,EXT_IO7_GPIO_MODE
																											};
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
void ExtIo_Init(EXT_IO_TypeDef ExtIo)
{
 	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_AHB1PeriphClockCmd(EXT_IO_GPIO_CLK[ExtIo],ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = EXT_IO_PIN[ExtIo];	
	GPIO_InitStructure.GPIO_Mode = EXT_IO_GPIO_MODE[ExtIo];
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
	GPIO_Init(EXT_IO_GPIO_PORT[ExtIo],&GPIO_InitStructure);
	
	GPIO_ResetBits(EXT_IO_GPIO_PORT[ExtIo],EXT_IO_PIN[ExtIo]);	
}
/**
  * @brief  
  * @param  
  * @retval 
*/
/**
  * @brief  
  * @param  
  * @retval 
*/

void ExtIo_InitAll(void)
{ 
	ExtIo_Init(EXT_IO0);
	ExtIo_Init(EXT_IO1);
	ExtIo_Init(EXT_IO2);
	ExtIo_Init(EXT_IO3);
	ExtIo_Init(EXT_IO4);
	ExtIo_Init(EXT_IO5);
	ExtIo_Init(EXT_IO6);
	ExtIo_Init(EXT_IO7);
}
/******************* (C) COPYRIGHT 2014 HUST-Robocon *****END OF FILE**********/
