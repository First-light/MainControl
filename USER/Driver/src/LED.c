#include "LED.h"

GPIO_TypeDef *LED_GPIO_PORT[LEDn]={
								LED1_GPIO_PORT,
								LED2_GPIO_PORT,
								LED3_GPIO_PORT
								};
const uint16_t LED_PIN[LEDn]={	
								LED1_PIN,
								LED2_PIN,
								LED3_PIN
								};
const uint32_t LED_GPIO_CLK[LEDn]={	
								LED1_GPIO_CLK,
								LED2_GPIO_CLK,
								LED3_GPIO_CLK
								};
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
void LED_InitAll(void)
{ 
	LED_Init(LED1);
	LED_Init(LED2);
	LED_Init(LED3);
}

void LED_Init(LED_TypeDef LED)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(LED_GPIO_CLK[LED],ENABLE);

	GPIO_InitStructure.GPIO_Pin = LED_PIN[LED];
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;

	GPIO_Init(LED_GPIO_PORT[LED],&GPIO_InitStructure);
	GPIO_SetBits(LED_GPIO_PORT[LED],LED_PIN [LED]);
	
}


void LED_On(LED_TypeDef LED)
{
	GPIO_ResetBits(LED_GPIO_PORT[LED],LED_PIN [LED]);
}


void LED_Off(LED_TypeDef LED)
{
	GPIO_SetBits(LED_GPIO_PORT[LED],LED_PIN [LED]);
}

void LED_Toggle(LED_TypeDef LED)
{
	GPIO_ToggleBits(LED_GPIO_PORT[LED],LED_PIN [LED]);
}
/******************* (C) COPYRIGHT 2014 HUST-Robocon *****END OF FILE**********/


