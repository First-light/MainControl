#include "IIC.h"

//起始条件:在SCL高电平期间，SDA从高到低跳变
void IIC_Hard_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;               //定义gpio初始化结构体 
	IIC_GPIO_CLK_CMD(IIC_CLK, ENABLE); 

	GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_OUT;     //端口模式为输出模式
	GPIO_InitStruct.GPIO_OType = GPIO_OType_OD;     //端口输出类型为开漏模式
	GPIO_InitStruct.GPIO_Pin   = IIC_SCL | IIC_SDA; //选择PH4 和 PH5 端口
	GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_UP;      //若外部有上拉，则可配置为无上下拉
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;   //标准速度仅100K

	GPIO_Init(IIC_GPIO_PORT, &GPIO_InitStruct);     //3. 初始状态：空闲状态
	GPIO_SetBits(IIC_GPIO_PORT,IIC_SDA);			//拉高SDA 
	GPIO_SetBits(IIC_GPIO_PORT,IIC_SCL);			//拉高SCL
	MyDelayus(5);
}
void IIC_Start(void)
{
	GPIO_SetBits(IIC_GPIO_PORT,IIC_SDA);			//拉高SDA 此函数为设置高电平函数 第一个参数为具体GPIO 第二个是哪个端口设置为高电平
	GPIO_SetBits(IIC_GPIO_PORT,IIC_SCL);			//拉高SCL
	MyDelayus(5);
	GPIO_ResetBits(IIC_GPIO_PORT,IIC_SDA);		    //SDA从高到低跳变 此函数为设置低电平函数，参数和上述一样
	MyDelayus(5); 
	GPIO_ResetBits(IIC_GPIO_PORT,IIC_SCL);		    //每次操作完拉低SCL，继续占用总线
}

//停止条件：在SCL高电平期间，SDA从低到高跳变
void IIC_Stop(void)
{
    GPIO_ResetBits(IIC_GPIO_PORT,IIC_SCL);		    //SCL为低
	GPIO_ResetBits(IIC_GPIO_PORT,IIC_SDA);		    //SDA为低
	MyDelayus(5);	
	GPIO_SetBits(IIC_GPIO_PORT,IIC_SCL);		    //SCL为高
	MyDelayus(5);
	GPIO_SetBits(IIC_GPIO_PORT,IIC_SDA);		    //SDA由低到高跳变
	MyDelayus(5);
}

//数据发送：低电平发数据，以字节为单位，先传高位
void IIC_Send_Byte(u8 dat)
{
	u8 i = 0;
	GPIO_ResetBits(IIC_GPIO_PORT,IIC_SCL);			//拉低时钟，低电平发数据
	for(i=0;i<8;i++)
	{
		GPIO_ResetBits(IIC_GPIO_PORT,IIC_SCL);		//拉低时钟，低电平发数据
		MyDelayus(5);
		if((dat & 0x80)>>7)
			GPIO_SetBits(IIC_GPIO_PORT,IIC_SDA);	//发数据位1
		else
			GPIO_ResetBits(IIC_GPIO_PORT,IIC_SDA);	//发数据位0
		MyDelayus(5);
		
		GPIO_SetBits(IIC_GPIO_PORT,IIC_SCL);		//拉高SCL，从机读取数据
		MyDelayus(5);
		
		dat <<= 1;									//移掉高位，准备发次高位
		GPIO_ResetBits(IIC_GPIO_PORT,IIC_SCL);		
		MyDelayus(5);
	}
	
	GPIO_ResetBits(IIC_GPIO_PORT,IIC_SCL);			//每次操作完拉低SCL，继续占用总线
	MyDelayus(5);	
}

//接收数据：在SCL高电平期间读取数据
u8 IIC_Recv_Byte(void)
{
	u8 i    = 0;
	u8 temp = 0;                                    //用于保存接收的数据
	
	for(i=0;i<8;i++)
	{
		GPIO_ResetBits(IIC_GPIO_PORT,IIC_SCL);		//主机拉低SCL，让从机发数据过来
		GPIO_SetBits(IIC_GPIO_PORT,IIC_SDA);		//主机读数据前，先切断输出通道，切换为输入模式
		MyDelayus(5);	
		GPIO_SetBits(IIC_GPIO_PORT,IIC_SCL);		//拉高SCL,准备接收数据
		MyDelayus(5);	
		if(GPIO_ReadInputDataBit(IIC_GPIO_PORT, IIC_SDA) == Bit_SET)
			temp |= 1<<(7-i);						//接收数据位
		MyDelayus(5);	
	}
	
	GPIO_ResetBits(IIC_GPIO_PORT,IIC_SCL);			//每次操作完拉低SCL，继续占用总线
	MyDelayus(5);	
	
	return temp;
}

//主机向从机发送应答信号
void IIC_ACK2Slave(void)
{
	GPIO_ResetBits(IIC_GPIO_PORT,IIC_SCL);			//拉低SCL，发应答信号
	MyDelayus(5);	
	GPIO_ResetBits(IIC_GPIO_PORT,IIC_SDA);			//拉低SDA，发应答
	MyDelayus(5);	
	GPIO_SetBits(IIC_GPIO_PORT,IIC_SCL);			//拉高SCL，使从机接收应答
	MyDelayus(5);
	GPIO_ResetBits(IIC_GPIO_PORT,IIC_SCL);			//每次操作完拉低SCL，继续占用总线
	MyDelayus(5);
}

//主机向从机发送非应答信号
void IIC_NoACK2Slave(void)
{
	GPIO_ResetBits(IIC_GPIO_PORT,IIC_SCL);			//拉低SCL，发应答信号
	MyDelayus(5);	
	GPIO_SetBits(IIC_GPIO_PORT,IIC_SDA);			//拉高SDA，发非应答
	MyDelayus(5);	
	GPIO_SetBits(IIC_GPIO_PORT,IIC_SCL);			//拉高SCL，使从机接收应答
	MyDelayus(5);
	GPIO_ResetBits(IIC_GPIO_PORT,IIC_SCL);			//每次操作完拉低SCL，继续占用总线
	MyDelayus(5);
}

//从机向主机发应答，主机读取SDA，判断应答状态
u8 IIC_Check_Ack(void)
{
	u8 ack = 0;
	
	GPIO_ResetBits(IIC_GPIO_PORT,IIC_SCL);			//拉低SCL，使从机发应答信号
	GPIO_SetBits(IIC_GPIO_PORT,IIC_SDA);			//主机读数据前，先切断输出通道，切换为输入模式
	MyDelayus(5);
	GPIO_SetBits(IIC_GPIO_PORT,IIC_SCL);			//拉高SCL，准备接收应答
	MyDelayus(5);
	if(GPIO_ReadInputDataBit(IIC_GPIO_PORT, IIC_SDA) == Bit_SET)    //从机向主机发非应答信号
		ack = 1;
	else if(GPIO_ReadInputDataBit(IIC_GPIO_PORT, IIC_SDA) == Bit_RESET)	//从机向主机发应答信号
		ack = 0;
	MyDelayus(5);
	
	GPIO_ResetBits(IIC_GPIO_PORT,IIC_SCL);			//每次操作完拉低SCL，继续占用总线
	MyDelayus(5);
	
	return ack;
}

void IIC_Write_Port(u8 dat,u8 *err)
{
	u8 ack =0;

	IIC_Start();                                    //主机启动总线
	IIC_Send_Byte(0x20<<1);                         //发写数据地址 （rw=0） 查手册能知道从设备PCF8574的地址是0x20 
	ack = IIC_Check_Ack();                          //从机向主机发应答，主机读取SDA，判断应答状态
	if(ack!=0)                                      //寻址出错
	{
		IIC_Stop();                                 //停止总线
		*err=1;                                     //寻址出错，保存错误值
		return;                                     //结束程序
	}
	IIC_Send_Byte(dat);				                //发数据
	ack = IIC_Check_Ack(); 
	if(ack !=0)
    {
		IIC_Stop();										
		*err = 2;											
		return;		                                //从机不接受数据，写数据出错
	}
	IIC_Stop();					                    //正常停止总线
	*err = 0;
	return;
}

//主机读取pcf8574端口状态
u8 IIC_Read_Port(u8 *err)
{
	u8 ack =0;
	u8 temp = 0;

	IIC_Start();                                    //主机启动总线
	IIC_Send_Byte(0x20);                            //发写数据的地址
	ack = IIC_Check_Ack();                          //从机应答
	if(ack != 0)				                    //寻址出错
	{
		IIC_Stop();				                    //停止总线
		*err = 1;				                    //寻址出错，保存错误值
		return 1;				                    //结束程序
	}
	temp = IIC_Recv_Byte();			                //读取数据
	IIC_NoACK2Slave();				                //主机回应不应答信号，不继续读取数据
	IIC_Stop();					                    //停止总线
	*err = 0;					                    //无错误
	return temp;				                    //返回读取的结果
}


