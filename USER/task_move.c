#include "system_config.h"
#include "task_init.h"

#define SIDE_BALANCE_P 0.433

//��������Ϊmotor1������Ϊmotor2������Ϊmotor3 ��˳ʱ��Ϊ����
MoveStruct ManualExpected;//�����ٶ�

ThreeWheel_Classic My3Moter;

ThreeWheel_MoveDeliver Forth; //ǰ��
ThreeWheel_MoveDeliver Side;//����
ThreeWheel_MoveDeliver Spin;//��ת

ThreeWheel_MoveParameter Manual_P = {
	2.0,//ǰ��
	1.0,//����
	1.0,//��ת
};

void ManualMoveDeliver(MoveStruct Expected)
{
	Forth.Left = -Expected.Forth * Manual_P.Forth;
	Forth.Right = Expected.Forth * Manual_P.Forth;
	Forth.Behind = 0.0;
	
	Side.Left = Expected.Side * Manual_P.Side;
	Side.Right = Expected.Side * Manual_P.Side;
	Side.Behind = -SIDE_BALANCE_P * Manual_P.Side;
	
	Spin.Left = -Expected.Angle * Manual_P.Spin;
	Spin.Right = -Expected.Angle * Manual_P.Spin;
	Spin.Behind = -Expected.Angle * Manual_P.Spin;
}

void TaskMove(void *p_arg)//�����ֶ�ģʽ
{
  	OS_ERR err;
	if(MainControlRun.ManualMode == MANUAL_ON)
	{
		

		
	}



	OSTimeDlyHMSM(0, 0, 0, 1, OS_OPT_TIME_HMSM_STRICT, &err);
}