/**
  ******************************************************************************
  * @file    main.c
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
#include "stm32f10x.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#include "Task_LED.h"
#include "Task_LOG.h"


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

#define TASK_LED_STACK_SIZE 128  //LED����Ķ�ջ��С
#define TASK_LED_PRIORITY   2    //LED��������ȼ�

#define TASK_LOG_STACK_SIZE 512  //LED����Ķ�ջ��С
#define TASK_LOG_PRIORITY   1    //LED��������ȼ�


/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

TaskHandle_t task_led_handle = NULL; //LED����ľ��
TaskHandle_t task_log_handle = NULL; //LED����ľ��

unsigned char task_sync_flag = 0;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
	* @brief  ���������
	* @param  ��
	* @retval ��
	*/
int main(void)
{
		
	BaseType_t xReturned;
	

	
	/* Configure the NVIC Preemption Priority Bits */  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
	
	
	//���� LED ���� 
	xReturned = xTaskCreate(
									TaskLED,             //��������ָ��
									"TaskLED",           //���������
									TASK_LED_STACK_SIZE, //��ջ��С ��λ:2byre
									( void * )(&task_sync_flag),         //�������
									TASK_LED_PRIORITY,   //�������ȼ�
									&task_led_handle );  //������

	if( xReturned != pdPASS )
	{
		while(1);
	}
	
	//���� log ��ӡ���� 
	xReturned = xTaskCreate(
									TaskLog,             //��������ָ��
									"TaskLog",           //���������
									TASK_LOG_STACK_SIZE, //��ջ��С ��λ:2byre
									( void * )(&task_sync_flag),         //�������
									TASK_LOG_PRIORITY,   //�������ȼ�
									&task_log_handle );  //������

	if( xReturned != pdPASS )
	{
		while(1);
	}
	
	//SHJD_RTT_printf("***************** SystemInit ******************\r\n");
	
	
	vTaskStartScheduler(); //��ʼ�������

	/* Will only get here if there was not enough heap space to create the
	idle task. */
	return 0;
}





/******************* (C) COPYRIGHT 2020 JSXC  *****END OF FILE****/
