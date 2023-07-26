#ifndef _LED_WS2815b_H
#define _LED_WS2815b_H

#include "stm32f4xx_conf.h"
#include "delay.h"

#define PIXEL_NUM  36
#define GRB        24

#define WS_LOW 35
#define WS_HIGH 53
void TIM2_PWM_Init(u32 arr,u32 psc);
void WS2812B_TIM_init(void);
void WS281x_Show(void);
void WS281x_CloseAll(void);
uint32_t WS281x_Color(uint8_t red, uint8_t green, uint8_t blue);
void WS281x_SetPixelRGB(uint16_t n ,uint8_t red, uint8_t green, uint8_t blue);
void WS281x_SetPixelColor(uint16_t n, uint32_t GRBColor);
uint32_t WS281x_Wheel(uint8_t wheelPos) ;
void WS281x_Rainbow(uint8_t wait) ;
void WS281x_RainbowCycle(uint8_t wait) ;
void WS281x_TheaterChase(uint32_t c, uint8_t wait) ;
void WS281x_TheaterChaseRainbow(uint8_t wait) ;
void WS281x_ColorWipe(uint32_t c, uint8_t wait); 
#endif
