/*
 * ZY_VisualScope.h
 *
 *  Created on: 2014-10-27
 *      Author: Yue
 */

#ifndef ZY_VISUALSCOPE_H_
#define ZY_VISUALSCOPE_H_

#include "stm32f4xx.h"

extern u8 ZY_VisualScope[10];
void ZY_VisualScope_Send(float Channel1,float Channel2,float Channel3,float Channel4);//œ‘ æ∑∂Œß -30000~30000;
void CRC_CHECK(u8 *Buf,  u8 Len);

#endif /* ZY_VISUALSCOPE_H_ */
