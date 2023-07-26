#ifndef ROBOTCAN_BASIC_H_
#define ROBOTCAN_BASIC_H_
#include "RobotCAN_IDconf.h"

/*******************************************************************************
	��29λ��չ��ʽID�ֶζ���
*******************************************************************************/
typedef struct
{
	uint32_t DesDEVICE_ID   	:8;     //Դ�豸ID
	uint32_t Property		      :8;		  //ָ������ֵ����
	uint32_t SrcDEVICE_ID   	:8;     //Ŀ���豸ID	
	uint32_t Priority				  :4;			//���ȼ�
	uint32_t Permit           :1;
}EXT_ID_Typedef;								  //����29λ��չID


#define FILTER_MASK      0x00000000

/*******************************************************************************
	��ID���Ͷ���
*******************************************************************************/
typedef union
{
	uint32_t	all;
	uint32_t	StdID		:11;		//��׼ID
	EXT_ID_Typedef	  ExtID;		//��չID
}ID;

/*******************************************************************************
	��CAN֡�ڵ����ݸ�ʽ����
*******************************************************************************/
typedef union
{
	int8_t			chars[8];			  //8��char
	int16_t			shorts[4];			//4��short
	int32_t			ints[2];			  //2��int
	int64_t			longs[1];			  //1��Long
	uint8_t			uchars[8];			//8���޷���char
	uint16_t		ushorts[4];			//4���޷���short
	uint32_t		uints[2];			  //2���޷���int
	uint64_t		ulongs[1];			//1���޷���Long
	float       floats[2];
}CAN_Data;								//����CAN��֡�ڵ���������

/*******************************************************************************
	��CAN֡�ڵ�����λ����
*******************************************************************************/
typedef struct
{
	ID 			id;						//ID
	char		isRemote;			//�Ƿ���Զ��֡
	char 		length;				//���ݳ���
	CAN_Data	data;				//����
}Frame;

extern  Frame	Frame1_tsm;
extern  Frame	Frame1_rcv;
extern  Frame	Frame2_tsm;
extern  Frame	Frame2_rcv;

/*******************************************************************************
	��������ֵ�봦������Ӧ�ṹ
*******************************************************************************/

typedef struct
{
	uint16_t	prop;				  //��������
	void(*fun)(Frame* frm);					//�����Զ�Ӧ�Ĵ�����
}FunDict;

/*******************************************************************************

������

*******************************************************************************/
void SendFrame(Frame* Frame_send, CAN_TypeDef* CANx);			 //֡���ͺ���

void GetFrame(Frame* Frame_get, CAN_TypeDef* CANx);        //֡���պ���

void ProcessFrame(Frame* Frame_Process, CAN_TypeDef* CANx);//֡������
#endif /*ROBOT_CAN_BASIC_H_*/
