#include "spi.h"

//������SPIģ��ĳ�ʼ�����룬���ó�����ģʽ 						  
//SPI�ڳ�ʼ��
void SPI2_Init(void)
{	 
	GPIO_InitTypeDef  GPIO_InitStructure;
	SPI_InitTypeDef  SPI_InitStructure;
		
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);//ʹ��GPIOBʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);//ʹ��SPI2ʱ��
	
	/***************Ӳ��SPI*********************/
	// //GPIO��ʼ������
	// GPIO_InitStructure.GPIO_Pin = AS5047P_CLK_Pin|AS5047P_MOSI_Pin|AS5047P_MISO_Pin;//���ù������	
	// GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���
	// GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
	// GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
	// GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
	// GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��
	
	// GPIO_PinAFConfig(AS5047P_MISO_GPIO_Port,AS5047P_MISO_Pin,GPIO_AF_SPI2); //PB13����Ϊ SPI2
	// GPIO_PinAFConfig(AS5047P_CLK_GPIO_Port,AS5047P_CLK_Pin,GPIO_AF_SPI2); //PB14����Ϊ SPI2
	// GPIO_PinAFConfig(AS5047P_MOSI_GPIO_Port,AS5047P_MOSI_Pin,GPIO_AF_SPI2); //PB15����Ϊ SPI2
 
	// //����ֻ���SPI�ڳ�ʼ��
	// RCC_APB1PeriphResetCmd(RCC_APB1Periph_SPI2,ENABLE);//��λSPI2
	// RCC_APB1PeriphResetCmd(RCC_APB1Periph_SPI2,DISABLE);//ֹͣ��λSPI2

	// SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  //����SPI�������˫�������ģʽ:SPI����Ϊ˫��˫��ȫ˫��
	// SPI_InitStructure.SPI_Mode = SPI_Mode_Master;		//����SPI����ģʽ:����Ϊ��SPI
	// SPI_InitStructure.SPI_DataSize = SPI_DataSize_16b;		//����SPI�����ݴ�С:SPI���ͽ���8λ֡�ṹ
	// SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;		//����ͬ��ʱ�ӵĿ���״̬Ϊ�ߵ�ƽ
	// SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;	//����ͬ��ʱ�ӵĵڶ��������أ��������½������ݱ�����
	// SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;		//NSS�ź���Ӳ����NSS�ܽţ����������ʹ��SSIλ������:�ڲ�NSS�ź���SSIλ����
	// SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;		//���岨����Ԥ��Ƶ��ֵ:������Ԥ��ƵֵΪ256
	// SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;	//ָ�����ݴ����MSBλ����LSBλ��ʼ:���ݴ����MSBλ��ʼ
	// SPI_InitStructure.SPI_CRCPolynomial = 7;	//CRCֵ����Ķ���ʽ
	// SPI_Init(SPI2, &SPI_InitStructure);  //����SPI_InitStruct��ָ���Ĳ�����ʼ������SPIx�Ĵ���
 
	// SPI_Cmd(SPI2, ENABLE); //ʹ��SPI����

	// SPI2_ReadWriteByte(0xff);//��������		 
	
	/********************���SPI*******************/
	//GPIO��ʼ������
	GPIO_InitStructure.GPIO_Pin = AS5047P_CS_Pin|AS5047P_CLK_Pin|AS5047P_MOSI_Pin;//���ù������	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��

	GPIO_InitStructure.GPIO_Pin = AS5047P_MISO_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(AS5047P_MISO_GPIO_Port, &GPIO_InitStructure);//��ʼ��
}   
//SPI2�ٶ����ú���
//SPI�ٶ�=fAPB2/��Ƶϵ��
//@ref SPI_BaudRate_Prescaler:SPI_BaudRatePrescaler_2~SPI_BaudRatePrescaler_256  
//fAPB2ʱ��һ��Ϊ84Mhz��
void SPI2_SetSpeed(u8 SPI_BaudRatePrescaler)
{
  	assert_param(IS_SPI_BAUDRATE_PRESCALER(SPI_BaudRatePrescaler));//�ж���Ч��
	SPI2->CR1&=0XFFC7;//λ3-5���㣬�������ò�����
	SPI2->CR1|=SPI_BaudRatePrescaler;	//����SPI2�ٶ� 
	SPI_Cmd(SPI2,ENABLE); //ʹ��SPI2
} 
//SPI2 ��дһ���ֽ�
//TxData:Ҫд����ֽ�
//����ֵ:��ȡ�����ֽ�
u8 SPI2_ReadWriteByte(u8 TxData)
{		 			 
 
  	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET){}//�ȴ���������  
	
	SPI_I2S_SendData(SPI2, TxData); //ͨ������SPIx����һ��byte  ����
		
  	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET){} //�ȴ�������һ��byte  
 
	return SPI_I2S_ReceiveData(SPI2); //����ͨ��SPIx������յ�����	
 		    
}








