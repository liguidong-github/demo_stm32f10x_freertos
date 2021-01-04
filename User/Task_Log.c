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
#include "Task_Log.h"
#include "FreeRTOS.h"
#include "queue.h"
#include "task.h"
#include "semphr.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "SEGGER_RTT.h"

/* Private typedef -----------------------------------------------------------*/

#define INFO_SIZE 200

struct LOG_INFO
{
	char data[INFO_SIZE];
	unsigned short len;
};

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static QueueHandle_t log_queue_handle = NULL;    //其他任务 与log打印任务的通讯队列.
static SemaphoreHandle_t log_mutex_handle = NULL;//log资源互斥量.

static struct LOG_INFO log_buffer;


/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
	* @brief  printf 底层接口
	* @param  ch： 待打印的字符
	* @retval 待打印的字符
	*/
int fputc(int ch, FILE *f) {
	
	//int temp_ch = ch;

	log_buffer.data[log_buffer.len] = ch;
	log_buffer.len++;
	if(log_buffer.len>=INFO_SIZE)
	{
		log_buffer.len = (INFO_SIZE-1);
	}
		
	return ch;
}

/**
	* @brief  log格式打印函数  log任务谨慎调用此函数
	* @param  sFormat 格式输入
	* @retval 无
	*/
void Log( const char * sFormat, ...)
{
	
	xSemaphoreTake( log_mutex_handle , portMAX_DELAY ); //获取互斥量
	
	va_list ParamList;
	
	log_buffer.len = 0; //长度清0
	
	va_start(ParamList, sFormat);

	printf(sFormat, &ParamList);
	
	xQueueSend( log_queue_handle , (void *)&log_buffer , portMAX_DELAY  );
	
	xSemaphoreGive( log_mutex_handle ); //释放互斥量
}


/**
	* @brief  Log 打印任务
	* @param  p_parameters 传入函数的参数
	* @retval 我i
	*/
void TaskLog(void * p_parameters)
{
	struct LOG_INFO log_msg;
	
	log_mutex_handle = xSemaphoreCreateMutex(); //log互斥资源

	if( log_mutex_handle == NULL )
	{
		 // The semaphore was not created and must not be used.
		while(1);
	}
	
	log_queue_handle = xQueueCreate( 2, sizeof(struct LOG_INFO) ); //创建Log队列 用于其他任务的通讯

	if( log_queue_handle == NULL )
	{
		// Queue was not created and must not be used. 
		while(1);
	}
	
	SEGGER_RTT_Init();
	
	
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
	
	//Log("Task Log Start... \r\n");
	
	for( ; ; )
	{
		if( xQueueReceive( log_queue_handle , &( log_msg ),( TickType_t ) portMAX_DELAY ) == pdPASS ) //队列里有数据
		{
			SEGGER_RTT_WriteNoLock(0, log_msg.data, log_msg.len);
		}
	}
	
	
	
	
	
}




/******************* (C) COPYRIGHT 2020 JSXC  *****END OF FILE****/
