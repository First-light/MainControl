#include "system_config.h"
#include "task_init.h"

//��������Ϊmotor1������Ϊmotor2������Ϊmotor3 ��˳ʱ��Ϊ����

MoveStruct ManualExpected;//�����ٶ�
ThreeWheel_Classic My3Moter; 

void TaskMove(void *p_arg)//�����ֶ�ģʽ
{
  	OS_ERR err;
	if(MainControlRun.ManualMode == MANUAL_ON)
	{
		
	}



	OSTimeDlyHMSM(0, 0, 0, 1, OS_OPT_TIME_HMSM_STRICT, &err);
}