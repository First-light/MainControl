#include "Archery.h"

volatile ArcheryController Archery_Controller;

void ArcheryControllerInit(void)
{
    Archery_Controller.archery_state = PULL;
    Archery_Controller.arrow_count = 0;
}

void ArcheryControllerRun(void)
{
    OS_ERR err;
    switch(Archery_Controller.archery_state)
    {
        case PULL:
        {
            GPIO_ResetBits(EXT_IO7_GPIO_PORT,EXT_IO7_PIN);//
            GPIO_ResetBits(EXT_IO1_GPIO_PORT,EXT_IO1_PIN);//
            break;
        }
        case SHOT:
        {
            if(Archery_Controller.arrow_count == 0)
            {
                GPIO_SetBits(EXT_IO7_GPIO_PORT,EXT_IO7_PIN);
                Archery_Controller.arrow_count += 1;
                OSTimeDlyHMSM(0, 0, 0, 500, OS_OPT_TIME_HMSM_STRICT, &err);
                Archery_Controller.archery_state = PULL;
            }
            else if(Archery_Controller.arrow_count == 1)
            {
                GPIO_SetBits(EXT_IO1_GPIO_PORT,EXT_IO1_PIN);
                Archery_Controller.arrow_count += 1;
                OSTimeDlyHMSM(0, 0, 0, 500, OS_OPT_TIME_HMSM_STRICT, &err);
                Archery_Controller.archery_state = PULL;
            }
            else
                Archery_Controller.archery_state = PULL;
            break;
        }
        case A_CHECK:
        {
            GPIO_SetBits(EXT_IO7_GPIO_PORT,EXT_IO7_PIN);
            GPIO_SetBits(EXT_IO1_GPIO_PORT,EXT_IO1_PIN);
            OSTimeDlyHMSM(0, 0, 0, 500, OS_OPT_TIME_HMSM_STRICT, &err);
            Archery_Controller.archery_state = PULL;
            break;
        }
        default:
            break;
    }
}
