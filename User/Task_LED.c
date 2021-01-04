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

#include "Task_LED.h"
#include "bsp_gpio_led.h"
#include "FreeRTOS.h"
#include "queue.h"
#include "task.h"
#include "Task_Log.h"

/* Private typedef -----------------------------------------------------------*/

typedef struct
{
	unsigned char  id;    //LED的编号 0-LED1 1-LED2
	unsigned short data; //闪烁时间长度 单位 TASK_LED_INTERVAL ms
}LED_QUEUE_MSG_T;

/* Private define ------------------------------------------------------------*/

#define TASK_LED_INTERVAL 2 //任务循环间隔时间 单位ms

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

static QueueHandle_t led_queue_handle = NULL; //其他任务 与LED任务的通讯队列。


/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/


/**
	* @brief  通过队列led_queue_handle，配置LED1和LED2的闪烁频率。
	* @param  id LED的编码
	*     @arg  id=1，LED1；  id=2，LED2; 
	* @param  time 闪烁时间长度. 0-常灭; 65535-常灭。
	* @retval 无
	*/
void LedFlashConfig(unsigned char id, unsigned short time )
{
	LED_QUEUE_MSG_T led_queue_tx_msg ={0,0}; //发送的队列消息
	
	if((id==1)||(id==2))
	{
		led_queue_tx_msg.id   = id;
		led_queue_tx_msg.data = time;
		xQueueSend( led_queue_handle , (void *)&led_queue_tx_msg , portMAX_DELAY  );
	}
	
}  


/**
	* @brief  LED控制任务
	* @param  p_parameters 传入函数的参数
	* @retval 返回值
	*/
void TaskLED(void * p_parameters)
{

	LED_QUEUE_MSG_T led_queue_rx_msg ={0,0}; //接收的队列消息
	
	unsigned short led1_tick_cnt = 0; //LED1的计数器 
	unsigned short led2_tick_cnt = 0; //LED2的计数器 
	
	unsigned short led1_time_len = 0; //LED1的闪烁时间长度
	unsigned short led2_time_len = 0; //LED2的闪烁时间长度
	
	LEDInit(); //管脚硬件初始化
	
	led_queue_handle = xQueueCreate( 10, sizeof( LED_QUEUE_MSG_T ) ); //创建LED队列 用于其他任务的通讯

	if( led_queue_handle == NULL )
	{
		/* Queue was not created and must not be used. */
		while(1);
	}
	
	//等待所有任务 初始化完成
	(*(unsigned char*)(p_parameters))++;
	for( ; ; )
	{
		vTaskDelay(1);
		if( *(unsigned char*)(p_parameters) == (configMAX_PRIORITIES-1))
		{
			break;
		}
	}
	
	
	Log("1 Task LED Start... \r\n");
	Log("2 Task LED Start... \r\n");
	Log("3 Task LED Start... \r\n");
	Log("4 Task LED Start... \r\n");
	Log("5 Task LED Start... \r\n");
	Log("6 Task LED Start... \r\n");
	Log("7 Task LED Start... \r\n");
	
	for( ; ; )
	{
		vTaskDelay(TASK_LED_INTERVAL);
		
		if( xQueueReceive( led_queue_handle , &( led_queue_rx_msg ),( TickType_t ) 0 ) == pdPASS ) //队列里有数据
		{
			switch(led_queue_rx_msg.id)
			{
				case 1:
				{
					led1_time_len = led_queue_rx_msg.data;
				}break;
				case 2:
				{
					led2_time_len = led_queue_rx_msg.data;
				}break;
				default:
				{}break;
			}
		}
		
		if(led1_time_len==0) //常灭
		{
			Led1Off();
			led1_tick_cnt = 0; //不计时
		}
		else if(led1_time_len==65535) //常亮
		{
			Led1On();
			led1_tick_cnt = 0; //不计时
		}
		else
		{
			led1_tick_cnt++; //开始计时
			if(led1_tick_cnt>=led1_time_len)
			{
				led1_tick_cnt=0;
				Led1Reverse();
			}
		}
		
		if(led2_time_len==0) //常灭
		{
			Led2Off();
			led2_tick_cnt = 0; //不计时
		}
		else if(led2_time_len==65535) //常亮
		{
			Led2On();
			led2_tick_cnt = 0; //不计时
		}
		else
		{
			led2_tick_cnt++;  //开始计时
			if(led2_tick_cnt>=led2_time_len)
			{
				led2_tick_cnt=0;
				Led2Reverse();
			}
		}
	}
}


/******************* (C) COPYRIGHT 2020 JSXC  *****END OF FILE****/
