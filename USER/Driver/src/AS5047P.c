#include "AS5047P.h"
#include "spi.h"
//#include "tim.h"
#include "delay.h"

uint8_t data_correction = 1;
uint16_t data_transfer;
uint16_t data_confirm;
uint16_t address_check;
uint16_t data_recieve = 0;
uint16_t data_caleven;
uint16_t errocode = 0;
CheckTransmissionErrorTypedef TransmissionError = ERROR_IDEL;


uint16_t anglecom_initial = 0;
uint16_t zposm = 0;
uint16_t zposl = 0;


//软硬件SPI读写
uint16_t MY_SPI2_ReadWriteByte(uint16_t TxData)
{
	uint16_t RxData=0;
	unsigned char  i;
	
	for(i=16;i>0;i--)
	{
		if(TxData&0x8000)						
			AS5047P_MOSI_1;
		else
			AS5047P_MOSI_0;
		TxData <<= 1;	
		AS5047P_CLK_1;
		MyDelayus(1);
		RxData=(RxData<<1)+AS5047P_MISO;
		AS5047P_CLK_0;
	}

    /**********************硬件SPI，未实现*************************/
    // while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET){}//等待发送区空  
	
	// SPI_I2S_SendData(SPI2, TxData); //通过外设SPIx发送一个byte  数据
		
  	// while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET){} //等待接收完一个byte  
 
	// RxData = SPI_I2S_ReceiveData(SPI2); //返回通过SPIx最近接收的数据
	return RxData;
}

//偶检验
uint16_t parity(uint16_t x)
{
	uint16_t parity = 0;

	while(x != 0)
	{
		parity ^= x;
		x >>= 1;
	}
	return (parity & 0x1);
}


void AS5047P_Read(uint16_t *origin_data,uint16_t address)//读取带地址的数据
{
	if (parity(address | AS5047P_RD) == 1) address = address | 0x8000; // set parity bit
	address_check = address | AS5047P_RD; // it's a read command
  	AS5047P_CS_0;
	MY_SPI2_ReadWriteByte(address_check);
	AS5047P_CS_1;
  	MyDelayus(1);
	
	AS5047P_CS_0;
	data_recieve=MY_SPI2_ReadWriteByte(address_check);
	AS5047P_CS_1;
	
   data_caleven = data_recieve;
    if(data_caleven&0x4000)
    {
		data_correction=0;
        AS5047P_Check_Transmission_Error(&TransmissionError);
			//*origin_data = data_recieve & 0x3FFF;  // filter bits outside data, strip bit 14..15
    }
    else
    {
			
		data_correction=1;
        *origin_data = data_recieve & 0x3FFF;  // filter bits outside data, strip bit 14..15
    }
}

void AS5047P_ReadData(uint16_t* origin_data)//读取SPI数据
{
    AS5047P_CS_0;
		data_recieve = MY_SPI2_ReadWriteByte(0xffff);
		AS5047P_CS_1;
    MyDelayus(1);
    if(parity(data_recieve));//校验为奇，直接舍弃
    else if(data_recieve&0x4000)//error
    {
        data_correction = 0;
        //AS5047P_Check_Transmission_Error(&TransmissionError);
    }
    else
    {
        data_correction = 1;
        *origin_data = data_recieve & 0x7FFF;  // filter bits outside data, strip bit 14..15
    }

}

 uint16_t AS5047P_Write(uint16_t address, uint16_t data)
{
	
	if (parity(address & 0x3FFF) == 1) address = address | 0x8000; // set parity bit
	address = address & (AS5047P_WR | 0x8000);  // its  a write command and don't change the parity bit (0x8000)
	AS5047P_CS_0;
    MY_SPI2_ReadWriteByte(address);
	AS5047P_CS_1;
    MyDelayus(1);

	if (parity(data & 0x3FFF) == 1) data = data | 0x8000; // set parity bit
	data = data & (AS5047P_WR | 0x8000); // its a write command and don't change the parity bit (0x8000)
    AS5047P_CS_0;
	data_confirm = MY_SPI2_ReadWriteByte(data);
    AS5047P_CS_1;
    MyDelayus(1);
    
//    AS5047P_Read(&data_recieve,address);
//    if(data_recieve&0x4000)
//    {
//        AS5047P_Check_Transmission_Error(&TransmissionError);
//    }
//    else
//    {
//        data_recieve = data_recieve & 0x3FFF;  // filter bits outside data, strip bit 14..15
//    }
    return 0;//data_recieve;
}

void AS5047P_Check_Transmission_Error(CheckTransmissionErrorTypedef *TransmissionError)
{
	/** Check if transmission error **/
	//AS5047P_Read(&errocode,AS5047P_ERRFL);
    AS5047P_CS_0;
    MyDelayus(1);
	errocode = MY_SPI2_ReadWriteByte(0x4001);
    MyDelayus(1);	
    AS5047P_CS_1;
    MyDelayus(1);
    
    AS5047P_CS_0;
    MyDelayus(1);
	errocode = MY_SPI2_ReadWriteByte(0x4001);
    MyDelayus(1);	
	AS5047P_CS_1;
    MyDelayus(1);
    if(errocode&0x4000)
    {
        data_correction = 0;
    }
    else
    {
        data_correction = 1;
        errocode = errocode & 0x3FFF;  // filter bits outside data, strip bit 14..15
        if((errocode&0x0004)==0x0004){
        *TransmissionError = PARERR;
        }
        else if((errocode&0x0002)==0x0002){
            *TransmissionError = INVCOMM;
        }
        else if((errocode&0x0001)==0x0001){
            *TransmissionError = FRERR;
        }
        else{
            *TransmissionError = ERROR_IDEL;
        }
    }

}		


