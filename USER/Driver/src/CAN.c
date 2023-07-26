#include "CAN.h"
#include "RobotCAN_IDconf.h"
#include "RobotCAN_Basic.h"


CAN_TypeDef * const CAN_SOURCE[CANn]={
	CAN1,
	CAN2,
};

const uint32_t CAN_CLK[CANn]={
	CAN1_CLK,
	CAN2_CLK,
};

const uint16_t CAN_RX_PIN[CANn]={	
	CAN1_RX_PIN,
	CAN2_RX_PIN,
};

const uint16_t CAN_TX_PIN[CANn]={	
	CAN1_TX_PIN,
	CAN2_TX_PIN,
};

GPIO_TypeDef * const CAN_GPIO_PORT[CANn]={
	CAN1_GPIO_PORT,
	CAN2_GPIO_PORT,
};

const uint32_t CAN_GPIO_CLK[CANn] ={
	CAN1_GPIO_CLK,
	CAN2_GPIO_CLK,
};

const uint8_t  CAN_AF_PORT[CANn]={
	CAN1_AF_PORT,
	CAN2_AF_PORT,
};

const uint16_t CAN_RX_SOURCE[CANn]={
	CAN1_RX_SOURCE,
	CAN2_RX_SOURCE,
};

const uint16_t CAN_TX_SOURCE[CANn]={
	CAN1_TX_SOURCE,
	CAN2_TX_SOURCE,
};

const uint8_t CAN_RX_IRQn[CANn] ={
	CAN1_RX_IRQn,
	CAN2_RX_IRQn,
};

const uint8_t CAN_FILTER_NUMBER[CANn] ={
	CAN1_FILTER_NUMBER,
	CAN2_FILTER_NUMBER,
};	

const uint16_t CAN_FILTER_FIFO[CANn]={
    CAN1_Filter_FIFO,
    CAN2_Filter_FIFO,
};

const uint32_t CAN_IT_FMP[CANn]={
    CAN1_IT_FMP,
    CAN2_IT_FMP,
};

const uint8_t CAN_PROTOCOL[CANn] ={
	CAN1_Protocol,
	CAN2_Protocol,
};

/**
  * @brief  CAN通信硬件初始化
  * @note 
  * @param  CANx为相对应的CAN接口
  *         取值：
  *             @arg MYCAN1
  *             @arg MYCAN2
  * @retval None
  */
void CAN_Hard_Init(MyCANTypedef CANx)
{
	GPIO_InitTypeDef  		GPIO_InitStructure;
	CAN_InitTypeDef         CAN_InitStructure;
	CAN_FilterInitTypeDef   CAN_FilterInitStructure;
	NVIC_InitTypeDef 		NVIC_InitStructure;
  
    /* CAN GPIOs configuration **************************************************/

    /* Enable GPIO clock */
    RCC_AHB1PeriphClockCmd(CAN_GPIO_CLK[CANx], ENABLE);

    /* Connect CAN pins to AF9 */
    GPIO_PinAFConfig(CAN_GPIO_PORT[CANx], CAN_RX_SOURCE[CANx], CAN_AF_PORT[CANx]);
    GPIO_PinAFConfig(CAN_GPIO_PORT[CANx], CAN_TX_SOURCE[CANx], CAN_AF_PORT[CANx]); 
    
    /* Configure CAN RX and TX pins */
    GPIO_InitStructure.GPIO_Pin   = CAN_RX_PIN[CANx] | CAN_TX_PIN[CANx];
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_DOWN;
    GPIO_Init(CAN_GPIO_PORT[CANx], &GPIO_InitStructure);

    /* CAN configuration ********************************************************/  
    /* Enable CAN clock */
    RCC_APB1PeriphClockCmd(CAN_CLK[CANx], ENABLE);
    
    /* CAN register init */
    CAN_DeInit(CAN_SOURCE[CANx]);

    /* CAN cell init */
    CAN_InitStructure.CAN_TTCM = DISABLE;
    CAN_InitStructure.CAN_ABOM = ENABLE;
    CAN_InitStructure.CAN_AWUM = DISABLE;
    CAN_InitStructure.CAN_NART = DISABLE;
    CAN_InitStructure.CAN_RFLM = DISABLE;
    CAN_InitStructure.CAN_TXFP = DISABLE;
    CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;
    CAN_InitStructure.CAN_SJW  = CAN_SJW_1tq;
        
    /* CAN Baudrate = 42M/(1+BS1+BS2)/Prescaler (CAN clocked at 42 MHz) */
    CAN_InitStructure.CAN_BS1 = CAN_BS1_8tq;            //(42/(1+8+5)/3=1M)
    CAN_InitStructure.CAN_BS2 = CAN_BS2_5tq;
    //CAN_InitStructure.CAN_Prescaler = 24;             //500K
    CAN_InitStructure.CAN_Prescaler = 3;	              //1M
    CAN_Init(CAN_SOURCE[CANx], &CAN_InitStructure);
        
    /* CAN filter init */
    CAN_SlaveStartBank(14);
    CAN_FilterInitStructure.CAN_FilterNumber         = CAN_FILTER_NUMBER[CANx];
    CAN_FilterInitStructure.CAN_FilterMode           = CAN_FilterMode_IdMask;
    CAN_FilterInitStructure.CAN_FilterScale          = CAN_FilterScale_32bit;
    CAN_FilterInitStructure.CAN_FilterIdHigh         = ((FILTER_SECOND_ID <<3)&0xFFFF0000)>>16;
    CAN_FilterInitStructure.CAN_FilterIdLow          = (FILTER_SECOND_ID <<3) &0x0000FFFF;
    CAN_FilterInitStructure.CAN_FilterMaskIdHigh     = ((FILTER_MASK<<3)&0xFFFF0000)>>16;
    CAN_FilterInitStructure.CAN_FilterMaskIdLow      = (FILTER_MASK<<3) &0x0000FFFF;
    CAN_FilterInitStructure.CAN_FilterFIFOAssignment = CAN_FILTER_FIFO[CANx];
    CAN_FilterInitStructure.CAN_FilterActivation     = ENABLE;
    CAN_FilterInit(&CAN_FilterInitStructure);
        
    #ifdef SLAVER_DEVICE
        CAN_SlaveStartBank(14);
        CAN_FilterInitStructure.CAN_FilterNumber         = CAN_FILTER_NUMBER[CANx] + 1;
        CAN_FilterInitStructure.CAN_FilterMode           = CAN_FilterMode_IdMask;
        CAN_FilterInitStructure.CAN_FilterScale          = CAN_FilterScale_32bit;
        CAN_FilterInitStructure.CAN_FilterIdHigh         = ((FILTER_SECOND_ID <<3)&0xFFFF0000)>>16;
        CAN_FilterInitStructure.CAN_FilterIdLow          = (FILTER_SECOND_ID <<3) &0x0000FFFF;
        CAN_FilterInitStructure.CAN_FilterMaskIdHigh     = ((FILTER_MASK<<3)&0xFFFF0000)>>16;
        CAN_FilterInitStructure.CAN_FilterMaskIdLow      = (FILTER_MASK<<3) &0x0000FFFF;
        CAN_FilterInitStructure.CAN_FilterFIFOAssignment = CAN_FILTER_FIFO[CANx];
        CAN_FilterInitStructure.CAN_FilterActivation     = ENABLE;
        CAN_FilterInit(&CAN_FilterInitStructure);
    #endif
        
    /* Configures the NVIC *****************************************************/
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    NVIC_InitStructure.NVIC_IRQChannel                   = CAN_RX_IRQn[CANx];
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_Init(&NVIC_InitStructure);  
    
    /* Enable FIFO 0 message pending Interrupt */
    CAN_ITConfig(CAN_SOURCE[CANx], CAN_IT_FMP[CANx], ENABLE);
}


