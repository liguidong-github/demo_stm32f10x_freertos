/**
  ******************************************************************************
  * @file    C文件 格式模板
  * @author  江苏鑫晨 控制产品部
  * @version V1.0.0
  * @date    2020-12-18
  * @brief   
  ******************************************************************************
  * @attention
  *
  * 
  * 公司内部建议统一格式风格，具体编程规范请参考《江苏鑫晨 嵌入式软件编程规范》 
	* 文本编码格式为 ANSI
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
	* @brief  串口GPIO 初始化
	* @param  无
	* @retval 返回值
	*/
static void Usart1GpioConfig(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	//使能AFIO 时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	//使能GPIO 时钟
	RCC_APB2PeriphClockCmd(USART1_TX_GPIO_CLK, ENABLE);
	RCC_APB2PeriphClockCmd(USART1_RX_GPIO_CLK, ENABLE);
	
	//使能 Remapping
	GPIO_PinRemapConfig(GPIO_Remap_USART1, ENABLE);  

	//Tx 复用推挽输出 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = USART1_TX_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(USART1_TX_GPIO_PORT, &GPIO_InitStructure);

	//Rx 浮空输入
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//GPIO_Mode_IPU;//GPIO_Mode_IN_FLOATING; //GPIO_Mode_IPU;//;
	GPIO_InitStructure.GPIO_Pin = USART1_RX_PIN;
	GPIO_Init(USART1_RX_GPIO_PORT, &GPIO_InitStructure);
}


/**
  * @brief  串口DMA 配置
  * @param  无
  * @retval 无
  */
static void Usart1DMAConfig(unsigned int tx_memory_base_addr,unsigned int tx_dma_buffer_size,
														unsigned int rx_memory_base_addr,unsigned int rx_dma_buffer_size )
{

	DMA_InitTypeDef DMA_InitStructure;
	
	//使能 DMA时钟
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	
	//配置 USART Tx DMA通道
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
	
	//配置 USART Rx DMA通道
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
  * @brief  配置 Tx DMA
  * @param  无
  * @retval 无
  */
static void USART1_Tx_DMA_Configuration(unsigned short len )
{
	//失能 Tx DMA通道
	DMA_Cmd(USART1_Tx_DMA_Channel, DISABLE);
	
	DMA_SetCurrDataCounter(USART1_Tx_DMA_Channel, len);
	
	//使能 Tx DMA通道
	DMA_Cmd(USART1_Tx_DMA_Channel, ENABLE);
}

/**
  * @brief  配置 Rx DMA
  * @param  无
  * @retval 无
  */
static void USART1_Rx_DMA_Configuration(unsigned short len )
{
	//失能 Rx DMA通道
	DMA_Cmd(USART1_Rx_DMA_Channel, DISABLE);
	
	DMA_SetCurrDataCounter(USART1_Rx_DMA_Channel, len);
	
	//使能 Rx DMA通道
	DMA_Cmd(USART1_Rx_DMA_Channel, ENABLE);
	
}




/**
  * @brief  串口1 配置
  * @param  None
  * @retval None.
  */
void Usart1Init(unsigned int tx_memory_base_addr,unsigned int tx_dma_buffer_size,
								unsigned int rx_memory_base_addr,unsigned int rx_dma_buffer_size )
{
	USART_InitTypeDef USART_InitStructure;
	
	// 配置 GPIO
	Usart1GpioConfig();
	// 配置DMA
	
	Usart1DMAConfig(tx_memory_base_addr,tx_dma_buffer_size,rx_memory_base_addr,rx_dma_buffer_size);
	
	// 使能 串口外设时钟
  RCC_APB2PeriphClockCmd(USART1_CLK, ENABLE); 
	
	// 串口参数配置
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
	
	// 使能 DMA请求
	USART_DMACmd(USART1_PERIPHERAL, USART_DMAReq_Rx | USART_DMAReq_Tx, ENABLE);
	
	
	// 使能 TX DMA通道
	DMA_Cmd(USART1_Tx_DMA_Channel, ENABLE);

	// 使能 RX DMA通道
	DMA_Cmd(USART1_Rx_DMA_Channel, ENABLE);
	
	// 使能 串口外设
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
