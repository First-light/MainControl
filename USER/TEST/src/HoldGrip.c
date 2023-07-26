#include "HoldGrip.h"

volatile HoldGripController HoldGrip_Controller;

void HoldGripControllerInit(void)
{
    HoldGrip_Controller.Hold_State = H_INIT;
    HoldGrip_Controller.cylinderinitflag = 0;//���׳�ʼ����־
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
                GPIO_ResetBits(EXT_IO3_GPIO_PORT, EXT_IO3_PIN);//��צ���׸�λ
                OSTimeDlyHMSM(0, 0, 0, 200, OS_OPT_TIME_HMSM_STRICT, &err);
                GPIO_ResetBits(EXT_IO4_GPIO_PORT, EXT_IO4_PIN);//ץצ���׸�λ
                
                HoldGrip_Controller.cylinderinitflag = 1;
            }
            break;
        }
        case PUSH:
        {
            if(HoldGrip_Controller.cylinderinitflag == 1)
            {
                GPIO_SetBits(EXT_IO3_GPIO_PORT, EXT_IO3_PIN);//��צ���׹�λ
                OSTimeDlyHMSM(0, 0, 0, 200, OS_OPT_TIME_HMSM_STRICT, &err);
                GPIO_SetBits(EXT_IO4_GPIO_PORT, EXT_IO4_PIN);//ץצ���׸�λ
                
                HoldGrip_Controller.cylinderinitflag = 0;
            }
            break;
        }
        case LOOSE:
        {
            GPIO_ResetBits(EXT_IO4_GPIO_PORT, EXT_IO4_PIN);//ץצ���׹�λ
            OSTimeDlyHMSM(0, 0, 0, 200, OS_OPT_TIME_HMSM_STRICT, &err);

            HoldGrip_Controller.Hold_State = H_INIT;
            break;
        }
        case H_CHECK:
        {
            GPIO_SetBits(EXT_IO3_GPIO_PORT, EXT_IO3_PIN);//��צ���׹�λ
            OSTimeDlyHMSM(0, 0, 0,500, OS_OPT_TIME_HMSM_STRICT, &err);
            GPIO_SetBits(EXT_IO4_GPIO_PORT, EXT_IO4_PIN);//ץצ���׸�λ
            OSTimeDlyHMSM(0, 0, 0,500, OS_OPT_TIME_HMSM_STRICT, &err);
            GPIO_ResetBits(EXT_IO4_GPIO_PORT, EXT_IO4_PIN);//ץצ���׹�λ
            GPIO_ResetBits(EXT_IO3_GPIO_PORT, EXT_IO3_PIN);//��צ���׸�λ
            HoldGrip_Controller.Hold_State = H_INIT;
            break;
        }
        default:
            break;
    }
}

