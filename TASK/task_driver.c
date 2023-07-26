#include "system_config.h"
#include "elmo.h"
//#include "com_prop.h"
#include "RobotCAN_proplist.h"

#include "VESC_CAN.h"
#include "motor_control.h"
#include "EXT_IO.h"
#include "IIC.h"
#include "RobotCOM_proplist.h"
//motor1 3508 
//motor2 3508 翻转环
//motor3 2006 
//motor4 2006 上环
//motor5 2006 回转
//motor6 2006
//motor7 2006
//motor8 2006
#define SWING_REDUCTION_RATIO         140/17//回转减速比

#define MOTOR2_GAP 2 
#define MOTOR4_GAP 2
#define MOTOR5_GAP 0.5
#define GUN_SPEED_GAP  30

int circle_order=0;
int launch_flag=0;

float gun_speed_init[8]={
22500,//1
20500,//2
0,//3
26800,//4
30300,//5
35500,//6
36000,//7
37900//8
};
float gun_angle_init[8]={
490,//1
-370,//2
0,//3
20,//4
-320,//5
-130,//6 
6.5,//7
-198//8
};
float gun_speed[8]={0};
float gun_angle[8]={0};
float gun_speed_fine_tuning[8]={0};
float gun_angle_fine_tuning[8]={0};
int gun_speed_delta_units[8]={0};
int gun_angle_delta_units[8]={0};
uint8_t gun_site_flag=4;

//外场红1
int gun_site_para_1[8][2]=
{
{0,0},//1
{0,0},//2
{0,0},//3
{0,0},//4
{0,0},//5
{5,5},//6
{4,-3},//7
{2,-7}//8
};
//外场蓝2
int gun_site_para_2[8][2]=
{
{0,0},//1
{0,0},//2
{0,0},//3
{0,0},//4
{0,0},//5
{4,6},//6
{4,5},//7
{-3,-5}//8
};
//内场红3
int gun_site_para_3[8][2]=
{
{0,0},//1
{0,0},//2
{0,0},//3
{0,0},//4
{0,0},//5
{11,0},//6
{8,-5},//7
{6,-10}//8
};
//内场蓝4
int gun_site_para_4[8][2]=
{
{0,0},//1
{0,0},//2
{0,0},//3
{-3,5},//4
{0,0},//5
{4,0},//6
{3,-2},//7
{-2,-5}//8
};
//一楼红5
int gun_site_para_5[8][2]=
{
{-8,0},//1
{0,0},//2
{0,0},//3
{0,0},//4
{5,0},//5
{10,1},//6
{4,5},//7
{-3,-5}//8
};
//一楼蓝6
int gun_site_para_6[8][2]=
{
{-16,10},//1
{0,0},//2
{0,0},//3
{-6,0},//4
{1,0},//5
{6,0},//6
{4,5},//7
{-3,-5}//8
};
float angle_offset[8]={0};

int on_shoot_speed=0;
int on_shoot_order=0;
int checking_in_place_times=0;
int gun_in_advance_flag=0;
int shoot_times_success=0;
void TaskRegulate(void* p_arg)
{	
	OS_ERR err;	
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
	while (1)
	{
		switch(launch_flag)
		{						
			case GUN_FOR_CIRCLE_ON:
			{
				Motor2.PositionExpected=-16;
				Motor5.PositionExpected=292.421631f;//36.2*SWING_REDUCTION_RATIO+15.02;//276;				
				break;
			}
			case GUN_POS_SHOOT_READY:
			{
				//Motor2.PositionExpected=-16;
				if(gun_in_advance_flag==1)
				{
					comm_can_set_rpm(frictionleft_id,gun_speed_fine_tuning[3]);
					comm_can_set_rpm(frictionright_id,gun_speed_fine_tuning[3]);
				}
				Motor5.PositionExpected=182.17041f;
				if(fabs(Motor5.PositionMeasure-Motor5.PositionExpected)<MOTOR5_GAP)
				{
					launch_flag=SWING_ON;
				}
				break;
			}
			case SWING_ON:
			{
				Motor4.PositionExpected= -735.0f;//-650;
				if(gun_in_advance_flag==1)
				{
					comm_can_set_rpm(frictionleft_id,gun_speed_fine_tuning[3]);
					comm_can_set_rpm(frictionright_id,gun_speed_fine_tuning[3]);
				}
				if(Motor2.PositionExpected<=220)
				{
					checking_in_place_times++;
					if(checking_in_place_times>=33)
					{
						checking_in_place_times=0;
						Motor2.PositionExpected+=24.4*2;
					}
				}
				else
				{
					Motor2.PositionExpected=250;				
				}
				break;
			}
//			case GUN_IN_ADVANCE:
//			{
//				gun_in_advance_flag=1;
//				comm_can_set_rpm(frictionleft_id,gun_speed_fine_tuning[3]);
//				comm_can_set_rpm(frictionright_id,gun_speed_fine_tuning[3]);
//				break;
//			}
			case GUN_ON_PLACE_FINE_TUNING:
			{
				gun_in_advance_flag=0;
				Motor4.PositionExpected= -735.0f;//-650;
				if(on_shoot_order>=1&&on_shoot_order<=8&&on_shoot_order!=3)
				{
					on_shoot_speed=gun_speed_fine_tuning[on_shoot_order-1];
					Motor5.PositionExpected=gun_angle_fine_tuning[on_shoot_order-1];
					comm_can_set_rpm(frictionleft_id,on_shoot_speed);
					comm_can_set_rpm(frictionright_id,on_shoot_speed);
				}					
				break;
			}
			case GUN_SINGLE_SHOOT_FINE_TUNING:
			{
				gun_in_advance_flag=0;
				comm_can_set_rpm(frictionleft_id,on_shoot_speed);
				comm_can_set_rpm(frictionright_id,on_shoot_speed);
				shoot_times_success++;
				if(fabs(Motor4.PositionMeasure-Motor4.PositionExpected)<MOTOR4_GAP&&
					 fabs(Motor5.PositionMeasure-Motor5.PositionExpected)<MOTOR5_GAP&&
					 shoot_times_success>=200
//					 fabs(frictionright.SpeedMeasure-on_shoot_speed)<GUN_SPEED_GAP&&
//					 fabs(frictionleft.SpeedMeasure-on_shoot_speed)<GUN_SPEED_GAP&&
//					 fabs(frictionright.SpeedMeasure-frictionleft.SpeedMeasure)<GUN_SPEED_GAP
				)
				{
					shoot_times_success=0;
					//checking_in_place_times++;
					//if(checking_in_place_times>=3)
					//{
						launch_flag=SHOOTING_OUT;
						//checking_in_place_times=0;
					//}		
				}
				break;
			}
			case SHOOTING_SPEED_ON:
			{
				gun_in_advance_flag=0;
				Motor4.PositionExpected= -735.0f;//-650;
				if(on_shoot_order>=1&&on_shoot_order<=8&&on_shoot_order!=3)
				{				
					on_shoot_speed=gun_speed[on_shoot_order-1];
					Motor5.PositionExpected=gun_angle[on_shoot_order-1];
					comm_can_set_rpm(frictionleft_id,on_shoot_speed);
					comm_can_set_rpm(frictionright_id,on_shoot_speed);
				} 
				shoot_times_success++;
				if(fabs(Motor4.PositionMeasure-Motor4.PositionExpected)<MOTOR4_GAP&&
					 fabs(Motor5.PositionMeasure-Motor5.PositionExpected)<MOTOR5_GAP&&
					 shoot_times_success>=200
//					 fabs(frictionright.SpeedMeasure-on_shoot_speed)<GUN_SPEED_GAP&&
//					 fabs(frictionleft.SpeedMeasure-on_shoot_speed)<GUN_SPEED_GAP&&
//					 fabs(frictionright.SpeedMeasure-frictionleft.SpeedMeasure)<GUN_SPEED_GAP
				)
				{
					shoot_times_success=0;
					//checking_in_place_times++;
					//if(checking_in_place_times>=3)
					//{
						launch_flag=SHOOTING_OUT;
						//checking_in_place_times=0;
					//}		
				}
				break;
			}
			case SHOOTING_OUT:
			{
				comm_can_set_rpm(frictionleft_id,on_shoot_speed);
				comm_can_set_rpm(frictionright_id,on_shoot_speed);
				Motor4.PositionExpected= 0;
				if(fabs(Motor4.PositionMeasure-Motor4.PositionExpected)<MOTOR4_GAP)
				{
				  	launch_flag=SHOOT_OVER_CHECKING;					
				}
				break;
			}
			case SHOOT_OVER_CHECKING:
			{
				Motor4.PositionExpected=-735;
				comm_can_set_rpm(frictionleft_id,on_shoot_speed);
				comm_can_set_rpm(frictionright_id,on_shoot_speed);
				if(circle_order%5==0&&circle_order!=0)
				{
					checking_in_place_times++;
					if(checking_in_place_times>=300)
					{					
						Motor4.PositionExpected=0;
						Motor5.PositionExpected=182.17041f;
						if(fabs(Motor5.PositionMeasure-Motor5.PositionExpected)<MOTOR5_GAP)
						{
							launch_flag=GUN_SHOOT_OVER_RESET_1;
							checking_in_place_times=0;
						}
					}	

				}
				break;
			}
			case GUN_SHOOT_OVER_RESET_1:
			{								
				Motor2.PositionExpected=0;			
				if(Motor2.PositionMeasure<5)
				{
					launch_flag=GUN_SHOOT_OVER_RESET_2;					
				}
				break;
			}
			case GUN_SHOOT_OVER_RESET_2:
			{
				Motor2.PositionExpected=0;
				Motor4.PositionExpected=0;
				break;
			}
			case GUN_RESET_1:
			{
				Motor5.PositionExpected=182.17041f;
				if(fabs(Motor5.PositionMeasure-Motor5.PositionExpected)<MOTOR5_GAP)
				{				
					Motor2.PositionExpected=0;			
					if(Motor2.PositionMeasure<5)
					{
						launch_flag=GUN_RESET_2;					
					}
				}
				break;
			}			
			case GUN_RESET_2:
			{
				Motor5.PositionExpected=0;
				Motor4.PositionExpected=0;				
				if(fabs(Motor5.PositionMeasure-Motor5.PositionExpected)<MOTOR5_GAP)
				{
					Motor2.PositionExpected=0;
				}
				break;
			}
			case GUN_STOP_SHOOTING:
			{
				
				break;
			}
			default:
			{
				break;
			}

		}

		Motor_Position_Update(Motor1.PositionExpected,Motor2.PositionExpected,Motor3.PositionExpected,Motor4.PositionExpected,
													Motor5.PositionExpected,Motor6.PositionExpected,Motor7.PositionExpected,Motor8.PositionExpected);

		OSTimeDlyHMSM(0, 0, 0, 3, OS_OPT_TIME_HMSM_STRICT, &err);
		
	}
}