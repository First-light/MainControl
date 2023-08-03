/**
 ******************************************************************************
 * @file    RobotCOM_ExecuteLib.c
 * @author  Robocon
 * @brief   �������ṩ�˴���Ϣ���������Ķ���:
 *           - �Զ����ŶӴ���Э��֡��Ϣ��������
 *  @verbatim
 *          ��������������Ӧ����Ϣ�������������Ӻ������Ӧ��proplist.c����
 *  @endverbatim
 ******************************************************************************
 */
#include "RobotCOM_Basic.h"
#include "RobotCOM_Proplist.h"
#include "BluetoothStatic.h"
#include "task_init.h"


uint32_t Echo_MM = 0;//超声波检测的距离（mm）

int16_t FrontLine = 0;//前轮偏移 0为无偏移
int16_t BehindLine = 0;//后轮偏移
uint8_t	FrontCount = 0;
uint8_t BehindCount = 0;

uint8_t PointList[POINT_TYPE] ={0};



uint8_t	BluetoothGetButton = 0;

uint8_t BluetoothGetJoystickLX = 0;
uint8_t BluetoothGetJoystickLY = 0;

uint8_t BluetoothGetJoystickRX = 0;
uint8_t BluetoothGetJoystickRY = 0;



void Usart_Test(COMFrame *Frame)//test
{
	UART_SendString(USART6,"GREAT");
}

void BlueTooth_Get_BUTTON_4Claw(COMFrame *Frame)//蓝牙接受信号，并转换为控制命令 
{
	BluetoothGetButton=Frame->Data.uint8_ts[0];

	switch (BluetoothGetButton) {
		case  goto_getleftring:
			
			break;
		case  goto_getrightring:
			break;
		case  goto_leftshootplace:
			break;
		case  goto_rightshootplace:
			break;
		case  lock_chassis:
			break;
		case  shoot:
			MainControlRun.ManualMode == MANUAL_OFF;
			break;
		
		
	}
	
	
}

void BlueTooth_Get_JOYSTICK_LEFT_4Claw(COMFrame *Frame)//按下左边手柄接受
{
   BluetoothGetJoystickLX=Frame->Data.uint8_ts[0];
	 BluetoothGetJoystickLY=Frame->Data.uint8_ts[1];
}

void BlueTooth_Get_JOYSTICK_RIGHT_4Claw(COMFrame *Frame)
{
   BluetoothGetJoystickRX=Frame->Data.uint8_ts[0];
	 BluetoothGetJoystickRY=Frame->Data.uint8_ts[1];
}

void Usart_SubMainEcho_4Claw(COMFrame *Frame)//串口接收超声波信号
{
	Echo_MM =Frame->Data.uint32_ts[0];
}

void Usart_SubMainLine_8Claw(COMFrame *Frame)//串口接收循迹红外偏移量信号
{
	FrontLine = Frame->Data.int16_ts[0];
	BehindLine = Frame->Data.int16_ts[1];
	FrontCount = Frame->Data.uint8_ts[4];
	BehindCount = Frame->Data.uint8_ts[5];
}
 
void Usart_SubMainPoint_8Claw(COMFrame *Frame)//串口接收负责点检测的传感器的信号
{
	PointList[LeftPoint] = Frame->Data.uint8_ts[0];
	PointList[RightPoint] = Frame->Data.uint8_ts[1];
	PointList[CenterPoint] = Frame->Data.uint8_ts[2];
	PointList[FrontPoint] = Frame->Data.uint8_ts[3];	
}
 

/*

extern int launch_flag;
extern int on_shoot_order;
extern int circle_order;
extern volatile MotorTypeDef  Motor2;
*/
/*
extern float gun_angle[8];
extern float gun_speed[8];
extern float gun_angle_init[8];
extern float gun_speed_init[8];
extern float gun_speed_fine_tuning[8];
extern float gun_angle_fine_tuning[8];
extern int gun_speed_delta_units[8];
extern int gun_angle_delta_units[8];

extern int checking_in_place_times;

extern int gun_in_advance_flag;

extern uint8_t gun_site_flag;
extern int gun_site_para_1[8][2];
extern int gun_site_para_2[8][2];
extern int gun_site_para_3[8][2];
extern int gun_site_para_4[8][2];
extern int gun_site_para_5[8][2];
extern int gun_site_para_6[8][2];
extern int gun_site_para_7[8][2];
extern int gun_site_para_8[8][2];
*/

/*

void Gun_For_Shoot_8Claw(COMFrame *Frame)//准备发射
{
	circle_order=0;
	launch_flag=GUN_POS_SHOOT_READY;
	checking_in_place_times=0;
}
void Gun_Shoot_8Claw(COMFrame *Frame)//炮台发射
{
	on_shoot_order=Frame->Data.int8_ts[0];
	
	circle_order++;
	launch_flag=SHOOTING_SPEED_ON;
	checking_in_place_times=0;
}
void Gun_For_Circle_8Claw(COMFrame *Frame)//炮台待分环
{
	circle_order=0;
	checking_in_place_times=0;
	if(Motor2.PositionMeasure<=20)
	{
		launch_flag=GUN_FOR_CIRCLE_ON;
	}
}
void Gun_Reset_8Claw(COMFrame *Frame)//炮台复位
{
	circle_order=0;
	launch_flag=GUN_RESET_1;
	checking_in_place_times=0;
}
void Gun_Angle_Get_8Claw(COMFrame *Frame)//炮台角度
{

}

void Gun_Stop_8Claw(COMFrame *Frame)//停转
{
	launch_flag=GUN_STOP_SHOOTING;
	checking_in_place_times=0;
}

void Gun_On_Place_8Claw(COMFrame *Frame)
{
		int8_t left_Gun_Target = Frame->Data.int8_ts[0];
    int8_t right_Gun_Target = Frame->Data.int8_ts[1];
		int8_t angle_delta = Frame->Data.int8_ts[2];
    int8_t speed_delta = Frame->Data.int8_ts[3];
		
		on_shoot_order=left_Gun_Target;
		if(left_Gun_Target>0)
		{
			gun_angle_fine_tuning[left_Gun_Target-1]=angle_delta*GUN_ANGLE_DELTA_UNIT+gun_angle[left_Gun_Target-1];
			gun_speed_fine_tuning[left_Gun_Target-1]=speed_delta*GUN_SPEED_DELTA_UNIT+gun_speed[left_Gun_Target-1];
		}
		launch_flag=GUN_ON_PLACE_FINE_TUNING;
}

void Gun_Single_Shoot_8Claw(COMFrame *Frame)
{
		int8_t left_Gun_Target = Frame->Data.int8_ts[0];
    int8_t right_Gun_Target = Frame->Data.int8_ts[1];
		int8_t angle_delta = Frame->Data.int8_ts[2];
    int8_t speed_delta = Frame->Data.int8_ts[3];
	
		launch_flag=GUN_SINGLE_SHOOT_FINE_TUNING;
}


void Gun_In_Advance_8Claw(COMFrame *Frame)
{
	gun_in_advance_flag=1;
}

void Site_Chooese_8Claw(COMFrame *Frame)
{
	gun_site_flag=Frame->Data.uint8_ts[0];
	for(int i=0;i<8;i++)
	{
		switch(gun_site_flag)
		{
			case 1:
			{				
				gun_angle[i]=gun_angle_init[i]+gun_site_para_1[i][0]*GUN_ANGLE_DELTA_UNIT;
				gun_angle_fine_tuning[i]=gun_angle_init[i]+gun_site_para_1[i][0]*GUN_ANGLE_DELTA_UNIT;
				
				gun_speed[i]=gun_speed_init[i]+gun_site_para_1[i][1]*GUN_SPEED_DELTA_UNIT;
				gun_speed_fine_tuning[i]=gun_speed_init[i]+gun_site_para_1[i][1]*GUN_SPEED_DELTA_UNIT;
				break;
			}
			case 2:
			{				
				gun_angle[i]=gun_angle_init[i]+gun_site_para_2[i][0]*GUN_ANGLE_DELTA_UNIT;
				gun_angle_fine_tuning[i]=gun_angle_init[i]+gun_site_para_2[i][0]*GUN_ANGLE_DELTA_UNIT;
				
				gun_speed[i]=gun_speed_init[i]+gun_site_para_2[i][1]*GUN_SPEED_DELTA_UNIT;
				gun_speed_fine_tuning[i]=gun_speed_init[i]+gun_site_para_2[i][1]*GUN_SPEED_DELTA_UNIT;
				break;
			}
			
			case 3:
			{				
				gun_angle[i]=gun_angle_init[i]+gun_site_para_3[i][0]*GUN_ANGLE_DELTA_UNIT;
				gun_angle_fine_tuning[i]=gun_angle_init[i]+gun_site_para_3[i][0]*GUN_ANGLE_DELTA_UNIT;
				
				gun_speed[i]=gun_speed_init[i]+gun_site_para_3[i][1]*GUN_SPEED_DELTA_UNIT;
				gun_speed_fine_tuning[i]=gun_speed_init[i]+gun_site_para_3[i][1]*GUN_SPEED_DELTA_UNIT;
				break;
			}			
			case 4:
			{				
				gun_angle[i]=gun_angle_init[i]+gun_site_para_4[i][0]*GUN_ANGLE_DELTA_UNIT;
				gun_angle_fine_tuning[i]=gun_angle_init[i]+gun_site_para_4[i][0]*GUN_ANGLE_DELTA_UNIT;
				
				gun_speed[i]=gun_speed_init[i]+gun_site_para_4[i][1]*GUN_SPEED_DELTA_UNIT;
				gun_speed_fine_tuning[i]=gun_speed_init[i]+gun_site_para_4[i][1]*GUN_SPEED_DELTA_UNIT;
				break;
			}
			case 5:
			{				
				gun_angle[i]=gun_angle_init[i]+gun_site_para_5[i][0]*GUN_ANGLE_DELTA_UNIT;
				gun_angle_fine_tuning[i]=gun_angle_init[i]+gun_site_para_5[i][0]*GUN_ANGLE_DELTA_UNIT;
				
				gun_speed[i]=gun_speed_init[i]+gun_site_para_5[i][1]*GUN_SPEED_DELTA_UNIT;
				gun_speed_fine_tuning[i]=gun_speed_init[i]+gun_site_para_5[i][1]*GUN_SPEED_DELTA_UNIT;
				break;
			}
			case 6:
			{				
				gun_angle[i]=gun_angle_init[i]+gun_site_para_6[i][0]*GUN_ANGLE_DELTA_UNIT;
				gun_angle_fine_tuning[i]=gun_angle_init[i]+gun_site_para_6[i][0]*GUN_ANGLE_DELTA_UNIT;
				
				gun_speed[i]=gun_speed_init[i]+gun_site_para_6[i][1]*GUN_SPEED_DELTA_UNIT;
				gun_speed_fine_tuning[i]=gun_speed_init[i]+gun_site_para_6[i][1]*GUN_SPEED_DELTA_UNIT;
				break;
			}
			default:
			{				
				gun_angle[i]=gun_angle_init[i];
				gun_angle_fine_tuning[i]=gun_angle_init[i];
				
				gun_speed[i]=gun_speed_init[i];
				gun_speed_fine_tuning[i]=gun_speed_init[i];
				break;
			}				
		}
	}
	Renew_Site_2Claw(gun_site_flag);
}
void Renew_Site_8Claw(COMFrame *Frame)
{
	for(int i=0;i<8;i++)
	{
		switch(gun_site_flag)
		{
			case 1:
			{				
				gun_angle[i]=gun_angle_init[i]+gun_site_para_1[i][0]*GUN_ANGLE_DELTA_UNIT;
				gun_angle_fine_tuning[i]=gun_angle_init[i]+gun_site_para_1[i][0]*GUN_ANGLE_DELTA_UNIT;
				
				gun_speed[i]=gun_speed_init[i]+gun_site_para_1[i][1]*GUN_SPEED_DELTA_UNIT;
				gun_speed_fine_tuning[i]=gun_speed_init[i]+gun_site_para_1[i][1]*GUN_SPEED_DELTA_UNIT;
				break;
			}
			case 2:
			{				
				gun_angle[i]=gun_angle_init[i]+gun_site_para_2[i][0]*GUN_ANGLE_DELTA_UNIT;
				gun_angle_fine_tuning[i]=gun_angle_init[i]+gun_site_para_2[i][0]*GUN_ANGLE_DELTA_UNIT;
				
				gun_speed[i]=gun_speed_init[i]+gun_site_para_2[i][1]*GUN_SPEED_DELTA_UNIT;
				gun_speed_fine_tuning[i]=gun_speed_init[i]+gun_site_para_2[i][1]*GUN_SPEED_DELTA_UNIT;
				break;
			}
			
			case 3:
			{				
				gun_angle[i]=gun_angle_init[i]+gun_site_para_3[i][0]*GUN_ANGLE_DELTA_UNIT;
				gun_angle_fine_tuning[i]=gun_angle_init[i]+gun_site_para_3[i][0]*GUN_ANGLE_DELTA_UNIT;
				
				gun_speed[i]=gun_speed_init[i]+gun_site_para_3[i][1]*GUN_SPEED_DELTA_UNIT;
				gun_speed_fine_tuning[i]=gun_speed_init[i]+gun_site_para_3[i][1]*GUN_SPEED_DELTA_UNIT;
				break;
			}			
			case 4:
			{				
				gun_angle[i]=gun_angle_init[i]+gun_site_para_4[i][0]*GUN_ANGLE_DELTA_UNIT;
				gun_angle_fine_tuning[i]=gun_angle_init[i]+gun_site_para_4[i][0]*GUN_ANGLE_DELTA_UNIT;
				
				gun_speed[i]=gun_speed_init[i]+gun_site_para_4[i][1]*GUN_SPEED_DELTA_UNIT;
				gun_speed_fine_tuning[i]=gun_speed_init[i]+gun_site_para_4[i][1]*GUN_SPEED_DELTA_UNIT;
				break;
			}
			case 5:
			{				
				gun_angle[i]=gun_angle_init[i]+gun_site_para_5[i][0]*GUN_ANGLE_DELTA_UNIT;
				gun_angle_fine_tuning[i]=gun_angle_init[i]+gun_site_para_5[i][0]*GUN_ANGLE_DELTA_UNIT;
				
				gun_speed[i]=gun_speed_init[i]+gun_site_para_5[i][1]*GUN_SPEED_DELTA_UNIT;
				gun_speed_fine_tuning[i]=gun_speed_init[i]+gun_site_para_5[i][1]*GUN_SPEED_DELTA_UNIT;
				break;
			}
			case 6:
			{				
				gun_angle[i]=gun_angle_init[i]+gun_site_para_6[i][0]*GUN_ANGLE_DELTA_UNIT;
				gun_angle_fine_tuning[i]=gun_angle_init[i]+gun_site_para_6[i][0]*GUN_ANGLE_DELTA_UNIT;
				
				gun_speed[i]=gun_speed_init[i]+gun_site_para_6[i][1]*GUN_SPEED_DELTA_UNIT;
				gun_speed_fine_tuning[i]=gun_speed_init[i]+gun_site_para_6[i][1]*GUN_SPEED_DELTA_UNIT;
				break;
			}
			default:
			{				
				gun_angle[i]=gun_angle_init[i];
				gun_angle_fine_tuning[i]=gun_angle_init[i];
				
				gun_speed[i]=gun_speed_init[i];
				gun_speed_fine_tuning[i]=gun_speed_init[i];
				break;
			}				
		}
	}
	Renew_Site_2Claw(gun_site_flag);
}

*/