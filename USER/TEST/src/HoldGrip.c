#include "HoldGrip.h"

volatile HoldGripController HoldGrip_Controller;

void HoldGripControllerInit(void)
{
    HoldGrip_Controller.Hold_State = H_INIT;
    HoldGrip_Controller.cylinderinitflag = 0;//气缸初始化标志
}

void HoldGripControllerRun(void)
{
    OS_ERR err;
    
    switch(HoldGrip_Controller.Hold_State)
    {
        case H_INIT:
        {
            if(HoldGrip_Controller.cylinderinitflag == 0)
            {
                GPIO_ResetBits(EXT_IO3_GPIO_PORT, EXT_IO3_PIN);//推爪气缸复位
                OSTimeDlyHMSM(0, 0, 0, 200, OS_OPT_TIME_HMSM_STRICT, &err);
                GPIO_ResetBits(EXT_IO4_GPIO_PORT, EXT_IO4_PIN);//抓爪气缸复位
                
                HoldGrip_Controller.cylinderinitflag = 1;
            }
            break;
        }
        case PUSH:
        {
            if(HoldGrip_Controller.cylinderinitflag == 1)
            {
                GPIO_SetBits(EXT_IO3_GPIO_PORT, EXT_IO3_PIN);//推爪气缸工位
                OSTimeDlyHMSM(0, 0, 0, 200, OS_OPT_TIME_HMSM_STRICT, &err);
                GPIO_SetBits(EXT_IO4_GPIO_PORT, EXT_IO4_PIN);//抓爪气缸复位
                
                HoldGrip_Controller.cylinderinitflag = 0;
            }
            break;
        }
        case LOOSE:
        {
            GPIO_ResetBits(EXT_IO4_GPIO_PORT, EXT_IO4_PIN);//抓爪气缸工位
            OSTimeDlyHMSM(0, 0, 0, 200, OS_OPT_TIME_HMSM_STRICT, &err);

            HoldGrip_Controller.Hold_State = H_INIT;
            break;
        }
        case H_CHECK:
        {
            GPIO_SetBits(EXT_IO3_GPIO_PORT, EXT_IO3_PIN);//推爪气缸工位
            OSTimeDlyHMSM(0, 0, 0,500, OS_OPT_TIME_HMSM_STRICT, &err);
            GPIO_SetBits(EXT_IO4_GPIO_PORT, EXT_IO4_PIN);//抓爪气缸复位
            OSTimeDlyHMSM(0, 0, 0,500, OS_OPT_TIME_HMSM_STRICT, &err);
            GPIO_ResetBits(EXT_IO4_GPIO_PORT, EXT_IO4_PIN);//抓爪气缸工位
            GPIO_ResetBits(EXT_IO3_GPIO_PORT, EXT_IO3_PIN);//推爪气缸复位
            HoldGrip_Controller.Hold_State = H_INIT;
            break;
        }
        default:
            break;
    }
}

