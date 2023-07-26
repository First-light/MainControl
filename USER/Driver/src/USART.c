#include "usart.h"

u8 ReceiveBuffer1[BUFFERSIZE];
u8 SendBuffer1[BUFFERSIZE];

u8 ReceiveBuffer2[BUFFERSIZE];
u8 SendBuffer2[BUFFERSIZE];

//u8 ReceiveBuffer3[BUFFERSIZE];
//u8 SendBuffer3[BUFFERSIZE];

u8 ReceiveBuffer4[BUFFERSIZE];
u8 SendBuffer4[BUFFERSIZE];

USART_TypeDef * const USART_SOURCE[USARTn] ={
	MY_USART1,
	MY_USART2,
//	MY_USART3,
	MY_USART4,
};

GPIO_TypeDef * const USART_GPIO_PORT[USARTn]={
	MY_USART1_GPIO_PORT,
	MY_USART2_GPIO_PORT,
//	MY_USART3_GPIO_PORT,
	MY_USART4_GPIO_PORT,
};

const uint32_t USART_GPIO_CLK[USARTn] ={
	MY_USART1_GPIO_CLK,
	MY_USART2_GPIO_CLK,
//	MY_USART3_GPIO_CLK,
	MY_USART4_GPIO_CLK,
};

const uint16_t USART_TX_PIN[USARTn]={	
	MY_USART1_TX_PIN,
	MY_USART2_TX_PIN,
//	MY_USART3_TX_PIN,
	MY_USART4_TX_PIN,
};
const uint16_t USART_TX_PIN_SOURCE[USARTn]={
	MY_USART1_TX_SOURCE,
	MY_USART2_TX_SOURCE,
//	MY_USART3_TX_SOURCE,
	MY_USART4_TX_SOURCE,
};
const uint16_t USART_RX_PIN[USARTn]={	
	MY_USART1_RX_PIN,
	MY_USART2_RX_PIN,
//	MY_USART3_RX_PIN,
	MY_USART4_RX_PIN,
};

const uint16_t USART_RX_PIN_SOURCE[USARTn]={
	MY_USART1_RX_SOURCE,
	MY_USART2_RX_SOURCE,
//	MY_USART3_RX_SOURCE,
	MY_USART4_RX_SOURCE,
};
const uint8_t USART_IRQn[USARTn] ={
	MY_USART1_IRQn,
	MY_USART2_IRQn,
//	MY_USART3_IRQn,
	MY_USART4_IRQn,
};	

const uint8_t  USART_AF[USARTn]={
	MY_USART1_AF,
	MY_USART2_AF,
//	MY_USART3_AF,
	MY_USART4_AF,
};

const uint32_t USART_BAUDRATE[USARTn] ={
	MY_USART1_BAUDRATE,
	MY_USART2_BAUDRATE,
//	MY_USART3_BAUDRATE,
	MY_USART4_BAUDRATE,
};	

void (*UART_PERIPH_CLOCK_CMD[USARTn])(uint32_t , FunctionalState)={
	MY_USART1_CLK_INIT,
	MY_USART2_CLK_INIT,
//	MY_USART3_CLK_INIT,
	MY_USART4_CLK_INIT,
};

const uint32_t USART_PERIPH_CLK[USARTn]={
	MY_USART1_CLK,
	MY_USART2_CLK,
//	MY_USART3_CLK,
	MY_USART4_CLK,
};

void (*UART_DMA_CLOCK_CMD[USARTn])(uint32_t , FunctionalState)={
	MY_USART1_DMAx_INIT,
	MY_USART2_DMAx_INIT,
};

const uint32_t DMA_PERIPH_CLK[USARTn]={
	MY_USART1_DMAx_CLK,
	MY_USART2_DMAx_CLK
};

DMA_Stream_TypeDef * USARTx_TX_DMA_STREAM[USARTn] ={
	MY_USART1_TX_DMA_STREAM,
	MY_USART2_TX_DMA_STREAM,
};

const uint32_t USARTx_Tx_DMA_CHANNEL[USARTn]={
	MY_USART1_TX_DMA_CHANNEL,
	MY_USART2_TX_DMA_CHANNEL,
};

uint8_t* const USART_SENDBUFFER[USARTn] ={
	SendBuffer1,
	SendBuffer2,
};

DMA_Stream_TypeDef * USARTx_RX_DMA_STREAM[USARTn] ={
	MY_USART1_RX_DMA_STREAM,
	MY_USART2_RX_DMA_STREAM,
};

const uint32_t USARTx_Rx_DMA_CHANNEL[USARTn]={
	MY_USART1_RX_DMA_CHANNEL,
	MY_USART2_RX_DMA_CHANNEL
};

uint8_t* const USART_RECVBUFFER[USARTn] ={
	ReceiveBuffer1,
	ReceiveBuffer2,
};

const uint32_t USART_TX_TCIF[USARTn] ={
	MY_USART1_TX_DMA_FLAG_TCIF,
	MY_USART2_TX_DMA_FLAG_TCIF,	
};

const uint32_t USART_RX_TCIF[USARTn] ={
	MY_USART1_RX_DMA_FLAG_TCIF,
	MY_USART2_RX_DMA_FLAG_TCIF,	
};
											
void USARTx_DMA_Init(MyUSARTTypedef USARTx)
{
	DMA_InitTypeDef  DMA_InitStructure;
	
	UART_DMA_CLOCK_CMD[USARTx](DMA_PERIPH_CLK[USARTx], ENABLE);
	
	DMA_DeInit(USARTx_TX_DMA_STREAM[USARTx]);  
	while (DMA_GetCmdStatus(USARTx_TX_DMA_STREAM[USARTx]) != DISABLE);
	
	DMA_InitStructure.DMA_BufferSize         = BUFFERSIZE ;
	DMA_InitStructure.DMA_FIFOMode           = DMA_FIFOMode_Disable ;
	DMA_InitStructure.DMA_FIFOThreshold      = DMA_FIFOThreshold_Full ;
	DMA_InitStructure.DMA_MemoryBurst        = DMA_MemoryBurst_Single ;
	DMA_InitStructure.DMA_MemoryDataSize     = DMA_MemoryDataSize_Byte;
	DMA_InitStructure.DMA_MemoryInc          = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_Mode               = DMA_Mode_Normal;
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t) (&(USART_SOURCE[USARTx]->DR)) ;
	DMA_InitStructure.DMA_PeripheralBurst    = DMA_PeripheralBurst_Single;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	DMA_InitStructure.DMA_PeripheralInc      = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_Priority           = DMA_Priority_High;
	/* Configure TX DMA */
	DMA_InitStructure.DMA_Channel         = USARTx_Tx_DMA_CHANNEL[USARTx] ;
	DMA_InitStructure.DMA_DIR             = DMA_DIR_MemoryToPeripheral ;
	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)USART_SENDBUFFER[USARTx];
	DMA_Init(USARTx_TX_DMA_STREAM[USARTx],&DMA_InitStructure);
	DMA_Cmd(USARTx_TX_DMA_STREAM[USARTx], ENABLE);
	
	/* Configure RX DMA */
	DMA_DeInit(USARTx_RX_DMA_STREAM[USARTx]);  
	while (DMA_GetCmdStatus(USARTx_RX_DMA_STREAM[USARTx]) != DISABLE);
	
	DMA_InitStructure.DMA_Channel         = USARTx_Rx_DMA_CHANNEL[USARTx] ;
	DMA_InitStructure.DMA_DIR             = DMA_DIR_PeripheralToMemory ;
	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)USART_RECVBUFFER[USARTx] ;
	DMA_Init(USARTx_RX_DMA_STREAM[USARTx],&DMA_InitStructure);
	
	DMA_Cmd(USARTx_RX_DMA_STREAM[USARTx], ENABLE); 
}

/**
  * @brief  串口通信硬件初始化
  * @note   若采用DMA进行通讯，需在System_Config.h文件中宏定义_USE_DMA
  * @param  USARTx为相对应的串口接口
  *         取值：
  *             @arg MYUSART1
  *             @arg MYUSART2
  *             @arg MYUSART3
  *             @arg MYUSART4
  * @retval None
  */
void USART_Hard_Init(MyUSARTTypedef USARTx)
{
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef  NVIC_InitStructure;
    GPIO_InitTypeDef  GPIO_InitStructure;

    /* Enable GPIO(AHB1) clock */
    RCC_AHB1PeriphClockCmd(USART_GPIO_CLK[USARTx], ENABLE);

    /* Enable USART clock */
    UART_PERIPH_CLOCK_CMD[USARTx](USART_PERIPH_CLK[USARTx],ENABLE);
	
    /* Connect USART pins to AF */
    GPIO_PinAFConfig(USART_GPIO_PORT[USARTx], USART_TX_PIN_SOURCE[USARTx], USART_AF[USARTx]);
    GPIO_PinAFConfig(USART_GPIO_PORT[USARTx], USART_RX_PIN_SOURCE[USARTx], USART_AF[USARTx]);

    /* Configure USART Tx and Rx as alternate function push-pull */
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Pin   = USART_TX_PIN[USARTx];
    GPIO_Init(USART_GPIO_PORT[USARTx], &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin =  USART_RX_PIN[USARTx];
    GPIO_Init(USART_GPIO_PORT[USARTx], &GPIO_InitStructure);

    USART_OverSampling8Cmd(USART_SOURCE[USARTx], ENABLE);

    USART_InitStructure.USART_BaudRate            = USART_BAUDRATE[USARTx];
    USART_InitStructure.USART_WordLength          = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits            = USART_StopBits_1;
    USART_InitStructure.USART_Parity              = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode                = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART_SOURCE[USARTx], &USART_InitStructure);

    #ifdef _USE_DMA
	    USART_ITConfig(USART_SOURCE[USARTx], USART_IT_IDLE, ENABLE);
	#else
	    USART_ITConfig(USART_SOURCE[USARTx], USART_IT_RXNE, ENABLE);
	#endif
    /* Configure the Priority Group to 2 bits */
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    /* Enable the USARTx Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel                   = USART_IRQn[USARTx];
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    /* Enable USART */
    USART_Cmd(USART_SOURCE[USARTx], ENABLE);
		
	#ifdef _USE_DMA
		USART_DMACmd(USART_SOURCE[USARTx], USART_DMAReq_Tx, ENABLE);
	  	USART_DMACmd(USART_SOURCE[USARTx], USART_DMAReq_Rx, ENABLE);
	#endif
		
	USART_ClearFlag(USART_SOURCE[USARTx], USART_FLAG_TC);
}

void COM_Write(uint8_t* Send_Buf, uint8_t Length_Temp, MyUSARTTypedef USARTx)
{
	uint8_t i = 0;
	USART_TypeDef *USART_INSTANCE = USART_SOURCE[USARTx];
	for(i = 0;i < Length_Temp;i++)
	{
		while(USART_GetFlagStatus(USART_INSTANCE,USART_FLAG_TXE)!= SET);
		USART_SendData(USART_INSTANCE,*Send_Buf++);
	}
}

/* printf串口输出重定向函数 */
#pragma import(__use_no_semihosting)                
struct __FILE       { int handle; };                // 标准库需要的支持函数
FILE __stdout;                                      // FILE 在stdio.h文件
void _sys_exit(int x) {	x = x; }                    // 定义_sys_exit()以避免使用半主机模式
 
int fputc(int ch, FILE *f)                          // 重定向fputc函数，使printf的输出，由fputc输出到UART,  这里使用串口1(USART1)
{   
    // if(xFlag.PrintfOK == 0) return 0;            // 判断USART是否已配置，防止在配置前调用printf被卡死
	
    while((MY_USART1 ->SR&0X40)==0);                // 等待上一次串口数据发送完成  
	MY_USART1 ->DR = (u8) ch;      	                // 写DR,串口1将发送数据    
	
	return ch;
}

/******************* (C) COPYRIGHT 2017 HUST-Robocon *****END OF FILE**********/


