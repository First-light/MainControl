#include "TurnArrow.h"

volatile bool isStart = 0;
volatile bool isStop = 0;
int firstFlag = 0;
volatile bool turnInitFlag = 0;
void CalculatePreAngle(void);
void CalPreYawAngle(void);
void CalPreDisAngle(void);
void CalPositionGain(void);

float preYawAngle = 0;

volatile TurnArrowController TurnArrow_Controller;

void TurnArrowControllerInit(void)//调试结果保存在这
{
    TurnArrow_Controller.TurnDisMotor.State = PIDPOSITION;
    TurnArrow_Controller.TurnYawMotor.State = PIDPOSITION;
    
    TurnArrow_Controller.DM_InitPosition = -5.0f;
    TurnArrow_Controller.YM_InitPosition = 45.0f;
    
    TurnArrow_Controller.DM_PrePosition = -5.0f;
    TurnArrow_Controller.YM_PrePosition = 45.0f;//90.0f;
    
    TurnArrow_Controller.Turn_State = PREINIT;
    
    TurnArrow_Controller.rotate_speed = 4500.0f;
}

void TurnArrowControllerRun(void)
{
    OS_ERR err;
    
    
    switch(TurnArrow_Controller.Turn_State)
    {
        case PREINIT:
        {
            TurnArrow_Controller.TurnDisMotor.PositionExpected = TurnArrow_Controller.DM_InitPosition;
            TurnArrow_Controller.TurnYawMotor.PositionExpected = 0.0 * YM_POSITION_PARA;
            break;
        }
        case INIT:
        {
            firstFlag = 0;
            isStart = 0;
            
            MotorPositionPid2.Kp = 5.0f;
            MotorPositionPid1.Kp = 0.8f;
            
 //           OSTimeDlyHMSM(0 , 0 , 1 , 0 , OS_OPT_TIME_HMSM_STRICT ,  &err);
            TurnArrow_Controller.TurnDisMotor.PositionExpected = TurnArrow_Controller.DM_InitPosition;
            if(fabs(TurnArrow_Controller.DM_InitPosition - TurnArrow_Controller.TurnDisMotor.PositionMeasure) < 10)
                TurnArrow_Controller.TurnYawMotor.PositionExpected = TurnArrow_Controller.YM_InitPosition * YM_POSITION_PARA;
            
//            comm_can_set_current(VESC_CAN_ID_TURNARROW , 0.0f);//失能 
            break;
        }
        case PREPARE:
        {
            
            if((TurnArrow_Controller.goal_x == 0)&&(TurnArrow_Controller.goal_y == 0))
            {
                TurnArrow_Controller.Turn_State = STOP;
                break;
            }
            
            CalculatePreAngle();
    
            
            if(firstFlag == 0)
            {
                MotorPositionPid2.Kp = 5.0f;
                MotorPositionPid1.Kp = 0.8f;
                if((fabs(TurnArrow_Controller.DM_PrePosition - TurnArrow_Controller.TurnDisMotor.PositionMeasure) < 10) &&
                    (fabs(TurnArrow_Controller.YM_PrePosition * YM_POSITION_PARA - TurnArrow_Controller.TurnYawMotor.PositionMeasure) < 10))
                {
                    firstFlag = 1;
                }
                
                TurnArrow_Controller.TurnYawMotor.PositionExpected = TurnArrow_Controller.YM_PrePosition * YM_POSITION_PARA;
                if(fabs(TurnArrow_Controller.TurnYawMotor.PositionExpected - TurnArrow_Controller.TurnYawMotor.PositionMeasure) < 10)
                    TurnArrow_Controller.TurnDisMotor.PositionExpected = TurnArrow_Controller.DM_PrePosition;
            }
            else
            {
                TurnArrow_Controller.TurnYawMotor.PositionExpected = TurnArrow_Controller.YM_PrePosition * YM_POSITION_PARA;
                TurnArrow_Controller.TurnDisMotor.PositionExpected = TurnArrow_Controller.DM_PrePosition;
                //CalPositionGain();
            }

            if((isStart != 0) && (isStop == 0))
            {
               
            }
            else if((isStart == 0) && (isStop == 0))
            {
            }
            else if(isStop == 1)
            {
                
            }
            
            break;
        }
        case STOP:
        {
           
            isStart = 0;
            firstFlag = 0;
            MotorPositionPid2.Kp = 0.8f;
            MotorPositionPid1.Kp = 0.8f;
            TurnArrow_Controller.TurnDisMotor.PositionExpected = TurnArrow_Controller.DM_InitPosition;
            if(fabs(TurnArrow_Controller.DM_InitPosition - TurnArrow_Controller.TurnDisMotor.PositionMeasure) < 5)
                TurnArrow_Controller.TurnYawMotor.PositionExpected = TurnArrow_Controller.YM_InitPosition * YM_POSITION_PARA;
            TurnArrow_Controller.Turn_State = INIT;
            break;
        }
        case T_CHECK:
        {
            TurnArrow_Controller.TurnYawMotor.PositionExpected = -30 * YM_POSITION_PARA;
            TurnArrow_Controller.TurnDisMotor.PositionExpected = -30;
         
            if((fabs(TurnArrow_Controller.TurnYawMotor.PositionExpected - TurnArrow_Controller.TurnYawMotor.PositionMeasure)<5.0f)&&(fabs(TurnArrow_Controller.TurnDisMotor.PositionExpected - TurnArrow_Controller.TurnDisMotor.PositionMeasure)<10.0f))
            {
             
                OSTimeDlyHMSM(0 , 0 , 0 , 500 , OS_OPT_TIME_HMSM_STRICT ,  &err);
                TurnArrow_Controller.Turn_State = PREINIT;
            }
            break;
        }
        default:
            break;
    }
}

void CalculatePreAngle(void)
{
    CalPreYawAngle();
    CalPreDisAngle();
}

void CalPreYawAngle(void)
{
    float yaw_angle = FastTableAtan2(TurnArrow_Controller.goal_y, TurnArrow_Controller.goal_x);
    

//    
//    if((TurnArrow_Controller.goal_y == 0)&&(TurnArrow_Controller.goal_x == 0))
//        yaw_angle = PI/4;
    
    TurnArrow_Controller.YM_PrePosition = -yaw_angle * 180.0f / PI + 225.0;
    
    if(TurnArrow_Controller.YM_PrePosition >= TurnArrow_Controller.YM_RealPosition + 180.0)
    {
        TurnArrow_Controller.YM_PrePosition -= 360.0;
    }
    else if(TurnArrow_Controller.YM_PrePosition <= TurnArrow_Controller.YM_RealPosition - 180.0)
    {
        TurnArrow_Controller.YM_PrePosition += 360.0;
    }
//    preYawAngle = yaw_angle;
}

void CalPreDisAngle(void)
{
    float y = TurnArrow_Controller.goal_y;
    float x = TurnArrow_Controller.goal_x;
    
    float goal_dis = sqrtf(x * x + y * y);
    
    TurnArrow_Controller.DM_PrePosition = -(0.00000030 * goal_dis * goal_dis * goal_dis - 0.00058484 * goal_dis * goal_dis + 0.47069207 * goal_dis - 106.64149372) + 10.0;//-(0.0002f * goal_dis * goal_dis - 0.004f * goal_dis - 8.1488f) + 90.0f;//拟合多项式曲线
    
    TurnArrow_Controller.DM_PrePosition = Clamp(TurnArrow_Controller.DM_PrePosition, -80.0f, -5.0f);
    
    if((TurnArrow_Controller.goal_point == 3) ||(TurnArrow_Controller.goal_point == 1))
    {
        TurnArrow_Controller.DM_PrePosition = -40;
    }
}

void CalPositionGain(void)
{
    float YMPositionError = fabs(TurnArrow_Controller.TurnYawMotor.PositionExpected - TurnArrow_Controller.TurnYawMotor.PositionMeasure);
    if(YMPositionError > 20)
    {
        MotorPositionPid1.Kp = 0.8;
        MotorPositionPid1.LimitOutput = 1000;
    }
    else if((YMPositionError <= 20)&&(YMPositionError > 5))
    {
        MotorPositionPid1.Kp = 5;
        MotorPositionPid1.LimitOutput = 1000;
    }
    else if(YMPositionError <= 5)
    {
        MotorPositionPid1.Kp = 10;
        MotorPositionPid1.LimitOutput = 1000;
    }
    
    float DMPositionError = fabs(TurnArrow_Controller.TurnYawMotor.PositionExpected - TurnArrow_Controller.TurnYawMotor.PositionMeasure);
    if(DMPositionError > 20)
    {
        MotorPositionPid2.Kp = 0.8;
        MotorPositionPid2.LimitOutput = 1000;
    }
    else if((DMPositionError <= 20)&&(DMPositionError > 5))
    {
        MotorPositionPid2.Kp = 5;
        MotorPositionPid2.LimitOutput = 1000;
    }
    else if(DMPositionError <= 5)
    {
        MotorPositionPid2.Kp = 10;
        MotorPositionPid2.LimitOutput = 1000;
    }
    
}

