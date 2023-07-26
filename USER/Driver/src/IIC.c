#include "IIC.h"

//��ʼ����:��SCL�ߵ�ƽ�ڼ䣬SDA�Ӹߵ�������
void IIC_Hard_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;               //����gpio��ʼ���ṹ�� 
	IIC_GPIO_CLK_CMD(IIC_CLK, ENABLE); 

	GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_OUT;     //�˿�ģʽΪ���ģʽ
	GPIO_InitStruct.GPIO_OType = GPIO_OType_OD;     //�˿��������Ϊ��©ģʽ
	GPIO_InitStruct.GPIO_Pin   = IIC_SCL | IIC_SDA; //ѡ��PH4 �� PH5 �˿�
	GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_UP;      //���ⲿ���������������Ϊ��������
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;   //��׼�ٶȽ�100K

	GPIO_Init(IIC_GPIO_PORT, &GPIO_InitStruct);     //3. ��ʼ״̬������״̬
	GPIO_SetBits(IIC_GPIO_PORT,IIC_SDA);			//����SDA 
	GPIO_SetBits(IIC_GPIO_PORT,IIC_SCL);			//����SCL
	MyDelayus(5);
}
void IIC_Start(void)
{
	GPIO_SetBits(IIC_GPIO_PORT,IIC_SDA);			//����SDA �˺���Ϊ���øߵ�ƽ���� ��һ������Ϊ����GPIO �ڶ������ĸ��˿�����Ϊ�ߵ�ƽ
	GPIO_SetBits(IIC_GPIO_PORT,IIC_SCL);			//����SCL
	MyDelayus(5);
	GPIO_ResetBits(IIC_GPIO_PORT,IIC_SDA);		    //SDA�Ӹߵ������� �˺���Ϊ���õ͵�ƽ����������������һ��
	MyDelayus(5); 
	GPIO_ResetBits(IIC_GPIO_PORT,IIC_SCL);		    //ÿ�β���������SCL������ռ������
}

//ֹͣ��������SCL�ߵ�ƽ�ڼ䣬SDA�ӵ͵�������
void IIC_Stop(void)
{
    GPIO_ResetBits(IIC_GPIO_PORT,IIC_SCL);		    //SCLΪ��
	GPIO_ResetBits(IIC_GPIO_PORT,IIC_SDA);		    //SDAΪ��
	MyDelayus(5);	
	GPIO_SetBits(IIC_GPIO_PORT,IIC_SCL);		    //SCLΪ��
	MyDelayus(5);
	GPIO_SetBits(IIC_GPIO_PORT,IIC_SDA);		    //SDA�ɵ͵�������
	MyDelayus(5);
}

//���ݷ��ͣ��͵�ƽ�����ݣ����ֽ�Ϊ��λ���ȴ���λ
void IIC_Send_Byte(u8 dat)
{
	u8 i = 0;
	GPIO_ResetBits(IIC_GPIO_PORT,IIC_SCL);			//����ʱ�ӣ��͵�ƽ������
	for(i=0;i<8;i++)
	{
		GPIO_ResetBits(IIC_GPIO_PORT,IIC_SCL);		//����ʱ�ӣ��͵�ƽ������
		MyDelayus(5);
		if((dat & 0x80)>>7)
			GPIO_SetBits(IIC_GPIO_PORT,IIC_SDA);	//������λ1
		else
			GPIO_ResetBits(IIC_GPIO_PORT,IIC_SDA);	//������λ0
		MyDelayus(5);
		
		GPIO_SetBits(IIC_GPIO_PORT,IIC_SCL);		//����SCL���ӻ���ȡ����
		MyDelayus(5);
		
		dat <<= 1;									//�Ƶ���λ��׼�����θ�λ
		GPIO_ResetBits(IIC_GPIO_PORT,IIC_SCL);		
		MyDelayus(5);
	}
	
	GPIO_ResetBits(IIC_GPIO_PORT,IIC_SCL);			//ÿ�β���������SCL������ռ������
	MyDelayus(5);	
}

//�������ݣ���SCL�ߵ�ƽ�ڼ��ȡ����
u8 IIC_Recv_Byte(void)
{
	u8 i    = 0;
	u8 temp = 0;                                    //���ڱ�����յ�����
	
	for(i=0;i<8;i++)
	{
		GPIO_ResetBits(IIC_GPIO_PORT,IIC_SCL);		//��������SCL���ôӻ������ݹ���
		GPIO_SetBits(IIC_GPIO_PORT,IIC_SDA);		//����������ǰ�����ж����ͨ�����л�Ϊ����ģʽ
		MyDelayus(5);	
		GPIO_SetBits(IIC_GPIO_PORT,IIC_SCL);		//����SCL,׼����������
		MyDelayus(5);	
		if(GPIO_ReadInputDataBit(IIC_GPIO_PORT, IIC_SDA) == Bit_SET)
			temp |= 1<<(7-i);						//��������λ
		MyDelayus(5);	
	}
	
	GPIO_ResetBits(IIC_GPIO_PORT,IIC_SCL);			//ÿ�β���������SCL������ռ������
	MyDelayus(5);	
	
	return temp;
}

//������ӻ�����Ӧ���ź�
void IIC_ACK2Slave(void)
{
	GPIO_ResetBits(IIC_GPIO_PORT,IIC_SCL);			//����SCL����Ӧ���ź�
	MyDelayus(5);	
	GPIO_ResetBits(IIC_GPIO_PORT,IIC_SDA);			//����SDA����Ӧ��
	MyDelayus(5);	
	GPIO_SetBits(IIC_GPIO_PORT,IIC_SCL);			//����SCL��ʹ�ӻ�����Ӧ��
	MyDelayus(5);
	GPIO_ResetBits(IIC_GPIO_PORT,IIC_SCL);			//ÿ�β���������SCL������ռ������
	MyDelayus(5);
}

//������ӻ����ͷ�Ӧ���ź�
void IIC_NoACK2Slave(void)
{
	GPIO_ResetBits(IIC_GPIO_PORT,IIC_SCL);			//����SCL����Ӧ���ź�
	MyDelayus(5);	
	GPIO_SetBits(IIC_GPIO_PORT,IIC_SDA);			//����SDA������Ӧ��
	MyDelayus(5);	
	GPIO_SetBits(IIC_GPIO_PORT,IIC_SCL);			//����SCL��ʹ�ӻ�����Ӧ��
	MyDelayus(5);
	GPIO_ResetBits(IIC_GPIO_PORT,IIC_SCL);			//ÿ�β���������SCL������ռ������
	MyDelayus(5);
}

//�ӻ���������Ӧ��������ȡSDA���ж�Ӧ��״̬
u8 IIC_Check_Ack(void)
{
	u8 ack = 0;
	
	GPIO_ResetBits(IIC_GPIO_PORT,IIC_SCL);			//����SCL��ʹ�ӻ���Ӧ���ź�
	GPIO_SetBits(IIC_GPIO_PORT,IIC_SDA);			//����������ǰ�����ж����ͨ�����л�Ϊ����ģʽ
	MyDelayus(5);
	GPIO_SetBits(IIC_GPIO_PORT,IIC_SCL);			//����SCL��׼������Ӧ��
	MyDelayus(5);
	if(GPIO_ReadInputDataBit(IIC_GPIO_PORT, IIC_SDA) == Bit_SET)    //�ӻ�����������Ӧ���ź�
		ack = 1;
	else if(GPIO_ReadInputDataBit(IIC_GPIO_PORT, IIC_SDA) == Bit_RESET)	//�ӻ���������Ӧ���ź�
		ack = 0;
	MyDelayus(5);
	
	GPIO_ResetBits(IIC_GPIO_PORT,IIC_SCL);			//ÿ�β���������SCL������ռ������
	MyDelayus(5);
	
	return ack;
}

void IIC_Write_Port(u8 dat,u8 *err)
{
	u8 ack =0;

	IIC_Start();                                    //������������
	IIC_Send_Byte(0x20<<1);                         //��д���ݵ�ַ ��rw=0�� ���ֲ���֪�����豸PCF8574�ĵ�ַ��0x20 
	ack = IIC_Check_Ack();                          //�ӻ���������Ӧ��������ȡSDA���ж�Ӧ��״̬
	if(ack!=0)                                      //Ѱַ����
	{
		IIC_Stop();                                 //ֹͣ����
		*err=1;                                     //Ѱַ�����������ֵ
		return;                                     //��������
	}
	IIC_Send_Byte(dat);				                //������
	ack = IIC_Check_Ack(); 
	if(ack !=0)
    {
		IIC_Stop();										
		*err = 2;											
		return;		                                //�ӻ����������ݣ�д���ݳ���
	}
	IIC_Stop();					                    //����ֹͣ����
	*err = 0;
	return;
}

//������ȡpcf8574�˿�״̬
u8 IIC_Read_Port(u8 *err)
{
	u8 ack =0;
	u8 temp = 0;

	IIC_Start();                                    //������������
	IIC_Send_Byte(0x20);                            //��д���ݵĵ�ַ
	ack = IIC_Check_Ack();                          //�ӻ�Ӧ��
	if(ack != 0)				                    //Ѱַ����
	{
		IIC_Stop();				                    //ֹͣ����
		*err = 1;				                    //Ѱַ�����������ֵ
		return 1;				                    //��������
	}
	temp = IIC_Recv_Byte();			                //��ȡ����
	IIC_NoACK2Slave();				                //������Ӧ��Ӧ���źţ���������ȡ����
	IIC_Stop();					                    //ֹͣ����
	*err = 0;					                    //�޴���
	return temp;				                    //���ض�ȡ�Ľ��
}


