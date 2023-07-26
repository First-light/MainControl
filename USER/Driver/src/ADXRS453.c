#include "ADXRS453.h"
#include "delay.h"

int ADXRS453Command(unsigned char Address, unsigned int SendValue, unsigned char OperateType)
{
    uint32_t  SendCommand = 0;
    uint32_t  ReceiveValue;
  
    SendCommand = Address;
    SendCommand = SendCommand<<17;
    SendCommand = SendCommand + (SendValue<<1);
  
    if (OperateType == 0)
    {
        SendCommand = SendCommand|0x40000000;          //write command
    }
    else
    {
        SendCommand = SendCommand|0x80000000;          //read command
    }
    
    ReceiveValue = ADXRS453_SpiFunction(SendCommand);           

    return(ReceiveValue);
}


//软件SPI读写
uint32_t ADXRS453_SpiFunction(uint32_t TxData)
{
	u8 i;
	uint32_t RxData;

    ADXRS453_CS_0;

    if(TxData&0x80000000)						
		ADXRS453_MOSI_1;
	else
		ADXRS453_MOSI_0;
	TxData <<= 1;
    MyDelayus(1);

    for(i=32; i>0; i--){
        ADXRS453_CLK_1;

        RxData=(RxData<<1)+ADXRS453_MISO;
        MyDelayus(1);
        ADXRS453_CLK_0;	

        if(TxData&0x80000000)						
			ADXRS453_MOSI_1;
		else
			ADXRS453_MOSI_0;
		TxData <<= 1;
		MyDelayus(1);
    }
    ADXRS453_CS_1;

	return RxData;
}

int ADXRS453SingleRead(unsigned char Address)
{
    int ReceiveValue;
    ADXRS453Command(Address, 0, READ);
    MyDelayus(1);
    ReceiveValue =  ADXRS453Command(Address, 0, READ);    //the second sequential response the read command
    ReceiveValue =  (ReceiveValue>>5)&0x0000FFFF;
    return(ReceiveValue);
}

int  ADXRS453SensorData(void)
{
    uint32_t  SendCommand;
    uint32_t  ReceiveValue;
  
    SendCommand = 0x20000000;
    ReceiveValue = ADXRS453_SpiFunction(SendCommand);

    ReceiveValue =  (ReceiveValue>>10)&0xFFFF;
    return(ReceiveValue);
}

void ADXRS453StartUp(void)
{
    uint32_t  SendCommand;
    uint32_t  ReceiveValue;
    unsigned char i;
  
    SendCommand = 0x20000003;
    ReceiveValue = ADXRS453_SpiFunction(SendCommand);       //0x20000003
    MyDelayus(1);
  
    SendCommand = 0x20000000;

    for (i=0; i<3; i++)
    {
        ReceiveValue = ADXRS453_SpiFunction(SendCommand);   //0x20000000
        MyDelayus(1000);     
    }
}