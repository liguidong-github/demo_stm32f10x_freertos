/**
  ******************************************************************************
  * @file    main.c
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
#include "stm32f10x.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#include "Task_LED.h"
#include "Task_LOG.h"


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

#define TASK_LED_STACK_SIZE 128  //LED任务的堆栈大小
#define TASK_LED_PRIORITY   2    //LED任务的优先级

#define TASK_LOG_STACK_SIZE 512  //LED任务的堆栈大小
#define TASK_LOG_PRIORITY   1    //LED任务的优先级


/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

TaskHandle_t task_led_handle = NULL; //LED任务的句柄
TaskHandle_t task_log_handle = NULL; //LED任务的句柄

unsigned char task_sync_flag = 0;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
	* @brief  主函数入口
	* @param  无
	* @retval 无
	*/
int main(void)
{
		
	BaseType_t xReturned;
	

	
	/* Configure the NVIC Preemption Priority Bits */  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
	
	
	//创建 LED 任务 
	xReturned = xTaskCreate(
									TaskLED,             //任务函数的指针
									"TaskLED",           //任务的名称
									TASK_LED_STACK_SIZE, //堆栈大小 单位:2byre
									( void * )(&task_sync_flag),         //传入参数
									TASK_LED_PRIORITY,   //任务优先级
									&task_led_handle );  //任务句柄

	if( xReturned != pdPASS )
	{
		while(1);
	}
	
	//创建 log 打印任务 
	xReturned = xTaskCreate(
									TaskLog,             //任务函数的指针
									"TaskLog",           //任务的名称
									TASK_LOG_STACK_SIZE, //堆栈大小 单位:2byre
									( void * )(&task_sync_flag),         //传入参数
									TASK_LOG_PRIORITY,   //任务优先级
									&task_log_handle );  //任务句柄

	if( xReturned != pdPASS )
	{
		while(1);
	}
	
	//SHJD_RTT_printf("***************** SystemInit ******************\r\n");
	
	
	vTaskStartScheduler(); //开始任务调度

	/* Will only get here if there was not enough heap space to create the
	idle task. */
	return 0;
}





/******************* (C) COPYRIGHT 2020 JSXC  *****END OF FILE****/
