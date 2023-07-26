#ifndef ROBOTCAN_BASIC_H_
#define ROBOTCAN_BASIC_H_
#include "RobotCAN_IDconf.h"

/*******************************************************************************
	对29位扩展形式ID分段定义
*******************************************************************************/
typedef struct
{
	uint32_t DesDEVICE_ID   	:8;     //源设备ID
	uint32_t Property		      :8;		  //指令属性值定义
	uint32_t SrcDEVICE_ID   	:8;     //目标设备ID	
	uint32_t Priority				  :4;			//优先级
	uint32_t Permit           :1;
}EXT_ID_Typedef;								  //定义29位扩展ID


#define FILTER_MASK      0x00000000

/*******************************************************************************
	对ID类型定义
*******************************************************************************/
typedef union
{
	uint32_t	all;
	uint32_t	StdID		:11;		//标准ID
	EXT_ID_Typedef	  ExtID;		//扩展ID
}ID;

/*******************************************************************************
	对CAN帧内的数据格式定义
*******************************************************************************/
typedef union
{
	int8_t			chars[8];			  //8个char
	int16_t			shorts[4];			//4个short
	int32_t			ints[2];			  //2个int
	int64_t			longs[1];			  //1个Long
	uint8_t			uchars[8];			//8个无符号char
	uint16_t		ushorts[4];			//4个无符号short
	uint32_t		uints[2];			  //2个无符号int
	uint64_t		ulongs[1];			//1个无符号Long
	float       floats[2];
}CAN_Data;								//定义CAN的帧内的数据类型

/*******************************************************************************
	对CAN帧内的特殊位定义
*******************************************************************************/
typedef struct
{
	ID 			id;						//ID
	char		isRemote;			//是否是远程帧
	char 		length;				//数据长度
	CAN_Data	data;				//数据
}Frame;

extern  Frame	Frame1_tsm;
extern  Frame	Frame1_rcv;
extern  Frame	Frame2_tsm;
extern  Frame	Frame2_rcv;

/*******************************************************************************
	建立属性值与处理函数对应结构
*******************************************************************************/

typedef struct
{
	uint16_t	prop;				  //属性名称
	void(*fun)(Frame* frm);					//此属性对应的处理函数
}FunDict;

/*******************************************************************************

处理函数

*******************************************************************************/
void SendFrame(Frame* Frame_send, CAN_TypeDef* CANx);			 //帧发送函数

void GetFrame(Frame* Frame_get, CAN_TypeDef* CANx);        //帧接收函数

void ProcessFrame(Frame* Frame_Process, CAN_TypeDef* CANx);//帧处理函数
#endif /*ROBOT_CAN_BASIC_H_*/
