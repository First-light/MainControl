#include "LED_WS2815b.h"

uint32_t pixelBuffer[PIXEL_NUM][GRB]={0};

void TIM2_PWM_Init(u32 arr,u32 psc)
{		 					 
	//�˲������ֶ��޸�IO������
	
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);  	//TIM14ʱ��ʹ��    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE); 	//ʹ��PORTFʱ��	
	
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource10,GPIO_AF_TIM2); //GPIOF9����Ϊ��ʱ��14
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;           //GPIOF9
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //���츴�����
//	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //����
	GPIO_Init(GPIOB,&GPIO_InitStructure);              //��ʼ��PF9
	  
	TIM_TimeBaseStructure.TIM_Prescaler=psc;  //��ʱ����Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseStructure.TIM_Period=arr;   //�Զ���װ��ֵ
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseStructure);//��ʼ����ʱ��14
	
	//��ʼ��TIM14 Channel1 PWMģʽ	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ե�
	TIM_OC3Init(TIM2, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM1 4OC1

	TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);  //ʹ��TIM14��CCR1�ϵ�Ԥװ�ؼĴ���
 
  TIM_ARRPreloadConfig(TIM2,ENABLE);//ARPEʹ�� 
	
	TIM_Cmd(TIM2, ENABLE);  //ʹ��TIM14
 							  
}  
void WS2812B_TIM_init(void)
{
	  DMA_InitTypeDef DMA_InitStructure;
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);

    /* DMA1 Channel6 Config */
//    DMA_DeInit(DMA1_Stream7);
    
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&TIM2->CCR3;    // physical address of Timer 3 CCR4
		DMA_InitStructure.DMA_Channel=DMA_Channel_3;
    DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)pixelBuffer;        // this is the buffer memory
    DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;                        // data shifted from memory to peripheral
    DMA_InitStructure.DMA_BufferSize = PIXEL_NUM*GRB;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;                    // automatically increase buffer index
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_PeripheralDataSize_Word;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;                            // stop DMA feed after buffer size is reached
    DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;
	  DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;   //DMAͨ��xû������Ϊ�ڴ浽�ڴ洫��
	  DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;//DMA_FIFOThreshold_HalfFull;//DMA_FIFOThreshold_1QuarterFull;
	  DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
	  DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;


    DMA_Init(DMA1_Stream1, &DMA_InitStructure);
    /* ֻ��ʹ��ͨ��1 TIMx_UP  TIM_DMA_CC2 */
    TIM_DMACmd(TIM2, TIM_DMA_CC3, ENABLE);
}

void WS281x_Show(void)
{
	DMA_Cmd(DMA1_Stream1, DISABLE);
  DMA_SetCurrDataCounter(DMA1_Stream1, PIXEL_NUM * GRB);
  TIM_Cmd(TIM2, ENABLE);
  DMA_Cmd(DMA1_Stream1, ENABLE);
  while(DMA_GetFlagStatus(DMA1_Stream1,DMA_FLAG_TCIF1) != SET);
  TIM_Cmd(TIM2, DISABLE);
  //TIM_SetCompare1(TIM2, 0); �þ䲻�ܼӣ����ϵƲ��ᰴ����������ʾ
  DMA_Cmd(DMA1_Stream1, DISABLE);
  DMA_ClearFlag(DMA1_Stream1 , DMA_FLAG_TCIF1 | DMA_FLAG_FEIF1 | DMA_FLAG_DMEIF1 | DMA_FLAG_TEIF1 | DMA_FLAG_HTIF1);
}

void WS281x_CloseAll(void)
{
  uint16_t i;
  uint8_t j;
  for(i = 0; i < PIXEL_NUM; ++i)
  {
    for(j = 0; j < 24; ++j)
    {
      pixelBuffer[i][j] = WS_LOW;
    }
  }
//	for(i = 0; i < 3456; ++i)
//  {
//      pixelBuffer[i] = WS_HIGH;
//  }
//	TIM_SetCompare2(TIM2, 53);
  WS281x_Show(); 
}

uint32_t WS281x_Color(uint8_t red, uint8_t green, uint8_t blue)
{
  return green << 16 | red << 8 | blue;
}

void WS281x_SetPixelColor(uint16_t n, uint32_t GRBColor)
{
  uint8_t i;
  if(n < PIXEL_NUM)
  {
    for(i = 0; i < GRB; i++)
    {
      pixelBuffer[n][i] = ((GRBColor << i) & 0x800000) ? WS_HIGH : WS_LOW;
    }
  }
}

void WS281x_SetPixelRGB(uint16_t n ,uint8_t red, uint8_t green, uint8_t blue)
{
  uint8_t i;
  
  if(n < PIXEL_NUM)
  {
    for(i = 0; i < GRB; ++i)
    {
       pixelBuffer[n][i] = (((WS281x_Color(red,green,blue) << i) & 0x800000) ? WS_HIGH : WS_LOW);
    }
  }
}
void WS281x_ColorWipe(uint32_t c, uint8_t wait) 
{
	for(uint16_t i=0; i<PIXEL_NUM; i++)
	{
		WS281x_SetPixelColor(i, c);
		WS281x_Show();
		MyDelayms(wait);
	}
	MyDelayms(wait);
}
uint32_t WS281x_Wheel(uint8_t wheelPos) 
{
  wheelPos = 255 - wheelPos;
  if(wheelPos < 85) {
    return WS281x_Color((255 - wheelPos * 3)*0.15, 0, (wheelPos * 3)*0.15);
  }
  if(wheelPos < 170) {
    wheelPos -= 85;
    return WS281x_Color(0, (wheelPos * 3)*0.15, (255 - wheelPos * 3)*0.15);
  }
  wheelPos -= 170;
  return WS281x_Color((wheelPos * 3)*0.15, (255 - wheelPos * 3)*0.15, 0);
}

void WS281x_Rainbow(uint8_t wait) 
{
	uint16_t i, j;
	for(j=0; j<256; j++) 
	{
		for(i=0; i<PIXEL_NUM; i++)
		{
			WS281x_SetPixelColor(i, WS281x_Wheel((i+j) & 255));
		}
		WS281x_Show();
		MyDelayms(wait);
	}
}

void WS281x_RainbowCycle(uint8_t wait) 
{
	uint16_t i, j;
	for(j=0; j<256*5; j++) 
	{ // 5 cycles of all colors on wheel
		for(i=0; i< PIXEL_NUM; i++) 
		{
			WS281x_SetPixelColor(i, WS281x_Wheel(((i * 256 / PIXEL_NUM) + j) & 50));
		}
		WS281x_Show();
		MyDelayms(wait);
	}
}

void WS281x_TheaterChase(uint32_t c, uint8_t wait) 
{
	for (int j=0; j<10; j++) 
	{  //do 10 cycles of chasing
		for (int q=0; q < 3; q++) 
		{
			for (uint16_t i=0; i < PIXEL_NUM; i=i+3) 
			{
				WS281x_SetPixelColor(i+q, c);    //turn every third pixel on
			}
			WS281x_Show();

			MyDelayms(wait);

			for (uint16_t i=0; i < PIXEL_NUM; i=i+3) 
			{
				WS281x_SetPixelColor(i+q, 0);        //turn every third pixel off
			}
			WS281x_Show();

			MyDelayms(wait);
		}
	}
}

void WS281x_TheaterChaseRainbow(uint8_t wait) 
{
	for (int j=0; j < 256; j++) 
	{     // cycle all 256 colors in the wheel
		for (int q=0; q < 3; q++) 
		{
			for (uint16_t i=0; i < PIXEL_NUM; i=i+3) 
			{
				WS281x_SetPixelColor(i+q, WS281x_Wheel( (i+j) % 50));    //turn every third pixel on
			}
			WS281x_Show();
			MyDelayms(wait);
			for (uint16_t i=0; i < PIXEL_NUM; i=i+3) 
			{
				WS281x_SetPixelColor(i+q, 0);        //turn every third pixel off
			}
			WS281x_Show();
			MyDelayms(wait);
		}
	}
}

