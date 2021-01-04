/**
  ******************************************************************************
  * @file    C�ļ� ��ʽģ��
  * @author  �����γ� ���Ʋ�Ʒ��
  * @version V1.0.0
  * @date    2020-12-18
  * @brief   
  ******************************************************************************
  * @attention
  *
  * 
  * ��˾�ڲ�����ͳһ��ʽ��񣬾����̹淶��ο��������γ� Ƕ��ʽ�����̹淶�� 
	* �ı������ʽΪ ANSI
  * 
  * 
  * 
  * 
  *
  * 
  ******************************************************************************
  */  

/* Includes ------------------------------------------------------------------*/
#include "bsp_usart1.h"
#include "stm32f10x.h"

/* Private typedef -----------------------------------------------------------*/

//#define USART1_RX_BUFFER_SIZE 1024
//#define USART1_TX_BUFFER_SIZE 1024

//typedef struct{
//	char  data[USART1_TX_BUFFER_SIZE];
//	unsigned short len;
//}USART1_TX_BUFFER;

//typedef struct{
//	char  data[USART1_RX_BUFFER_SIZE];
//	unsigned short len;
//}USART1_RX_BUFFER;

/* Private define ------------------------------------------------------------*/

#define USART1_PERIPHERAL             USART1
#define USART1_CLK                    RCC_APB2Periph_USART1
#define USART1_TX_PIN                 GPIO_Pin_6
#define USART1_TX_GPIO_PORT           GPIOB
#define USART1_TX_GPIO_CLK            RCC_APB2Periph_GPIOB
#define USART1_RX_PIN                 GPIO_Pin_7
#define USART1_RX_GPIO_PORT           GPIOB
#define USART1_RX_GPIO_CLK            RCC_APB2Periph_GPIOB
#define USART1_IRQn                   USART1_IRQn
#define USART1_IRQHandler             USART1_IRQHandler

#define USART1_Tx_DMA_Channel    DMA1_Channel4
#define USART1_Tx_DMA_FLAG       DMA1_FLAG_TC4
#define USART1_Rx_DMA_Channel    DMA1_Channel5
#define USART1_Rx_DMA_FLAG       DMA1_FLAG_TC5  
#define USART1_DR_Base           (uint32_t)(&(USART1_PERIPHERAL->DR))

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

//static USART1_RX_BUFFER usart1_rx_buffer;
//static USART1_TX_BUFFER usart1_tx_buffer;


/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

	
/**
	* @brief  ����GPIO ��ʼ��
	* @param  ��
	* @retval ����ֵ
	*/
static void Usart1GpioConfig(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	//ʹ��AFIO ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	//ʹ��GPIO ʱ��
	RCC_APB2PeriphClockCmd(USART1_TX_GPIO_CLK, ENABLE);
	RCC_APB2PeriphClockCmd(USART1_RX_GPIO_CLK, ENABLE);
	
	//ʹ�� Remapping
	GPIO_PinRemapConfig(GPIO_Remap_USART1, ENABLE);  

	//Tx ����������� 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = USART1_TX_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(USART1_TX_GPIO_PORT, &GPIO_InitStructure);

	//Rx ��������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//GPIO_Mode_IPU;//GPIO_Mode_IN_FLOATING; //GPIO_Mode_IPU;//;
	GPIO_InitStructure.GPIO_Pin = USART1_RX_PIN;
	GPIO_Init(USART1_RX_GPIO_PORT, &GPIO_InitStructure);
}


/**
  * @brief  ����DMA ����
  * @param  ��
  * @retval ��
  */
static void Usart1DMAConfig(unsigned int tx_memory_base_addr,unsigned int tx_dma_buffer_size,
														unsigned int rx_memory_base_addr,unsigned int rx_dma_buffer_size )
{

	DMA_InitTypeDef DMA_InitStructure;
	
	//ʹ�� DMAʱ��
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	
	//���� USART Tx DMAͨ��
	DMA_DeInit(USART1_Tx_DMA_Channel);  
	DMA_InitStructure.DMA_PeripheralBaseAddr = USART1_DR_Base;
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)(tx_memory_base_addr);
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
	DMA_InitStructure.DMA_BufferSize = tx_dma_buffer_size;//sizeof(usart1_tx_buffer);
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	DMA_Init(USART1_Tx_DMA_Channel, &DMA_InitStructure);
	
	//���� USART Rx DMAͨ��
	DMA_DeInit(USART1_Rx_DMA_Channel);  
	DMA_InitStructure.DMA_PeripheralBaseAddr = USART1_DR_Base;
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)(rx_memory_base_addr);
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
	DMA_InitStructure.DMA_BufferSize = rx_dma_buffer_size;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;//;//;DMA_Mode_Circular
	DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	DMA_Init(USART1_Rx_DMA_Channel, &DMA_InitStructure);
}



/**
  * @brief  ���� Tx DMA
  * @param  ��
  * @retval ��
  */
static void USART1_Tx_DMA_Configuration(unsigned short len )
{
	//ʧ�� Tx DMAͨ��
	DMA_Cmd(USART1_Tx_DMA_Channel, DISABLE);
	
	DMA_SetCurrDataCounter(USART1_Tx_DMA_Channel, len);
	
	//ʹ�� Tx DMAͨ��
	DMA_Cmd(USART1_Tx_DMA_Channel, ENABLE);
}

/**
  * @brief  ���� Rx DMA
  * @param  ��
  * @retval ��
  */
static void USART1_Rx_DMA_Configuration(unsigned short len )
{
	//ʧ�� Rx DMAͨ��
	DMA_Cmd(USART1_Rx_DMA_Channel, DISABLE);
	
	DMA_SetCurrDataCounter(USART1_Rx_DMA_Channel, len);
	
	//ʹ�� Rx DMAͨ��
	DMA_Cmd(USART1_Rx_DMA_Channel, ENABLE);
	
}




/**
  * @brief  ����1 ����
  * @param  None
  * @retval None.
  */
void Usart1Init(unsigned int tx_memory_base_addr,unsigned int tx_dma_buffer_size,
								unsigned int rx_memory_base_addr,unsigned int rx_dma_buffer_size )
{
	USART_InitTypeDef USART_InitStructure;
	
	// ���� GPIO
	Usart1GpioConfig();
	// ����DMA
	
	Usart1DMAConfig(tx_memory_base_addr,tx_dma_buffer_size,rx_memory_base_addr,rx_dma_buffer_size);
	
	// ʹ�� ��������ʱ��
  RCC_APB2PeriphClockCmd(USART1_CLK, ENABLE); 
	
	// ���ڲ�������
	USART_DeInit(USART1_PERIPHERAL);
	/* USART1_PERIPHERAL configured as follow:
        - BaudRate = 115200 baud  
        - Word Length = 8 Bits
        - One Stop Bit
        - No parity
        - Hardware flow control disabled (RTS and CTS signals)
        - Receive and transmit enabled
  */
  USART_InitStructure.USART_BaudRate = 115200;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	
	/* USART configuration */
  USART_Init(USART1_PERIPHERAL, &USART_InitStructure);
	
	// ʹ�� DMA����
	USART_DMACmd(USART1_PERIPHERAL, USART_DMAReq_Rx | USART_DMAReq_Tx, ENABLE);
	
	
	// ʹ�� TX DMAͨ��
	DMA_Cmd(USART1_Tx_DMA_Channel, ENABLE);

	// ʹ�� RX DMAͨ��
	DMA_Cmd(USART1_Rx_DMA_Channel, ENABLE);
	
	// ʹ�� ��������
	USART_Cmd(USART1_PERIPHERAL, ENABLE);
	
	
//	/* Wait until USARTy TX DMA1 Channel Transfer Complete */
//  while (DMA_GetFlagStatus(USART1_Tx_DMA_FLAG) == RESET)
//  {
//  }
//  /* Wait until USARTy RX DMA1 Channel Transfer Complete */
//  while (DMA_GetFlagStatus(USART1_Rx_DMA_FLAG) == RESET)
//  {
//  }
}




/******************* (C) COPYRIGHT 2020 JSXC  *****END OF FILE****/
