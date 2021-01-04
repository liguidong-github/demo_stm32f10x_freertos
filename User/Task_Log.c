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
static QueueHandle_t log_queue_handle = NULL;    //�������� ��log��ӡ�����ͨѶ����.
static SemaphoreHandle_t log_mutex_handle = NULL;//log��Դ������.

static struct LOG_INFO log_buffer;


/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
	* @brief  printf �ײ�ӿ�
	* @param  ch�� ����ӡ���ַ�
	* @retval ����ӡ���ַ�
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
	* @brief  log��ʽ��ӡ����  log����������ô˺���
	* @param  sFormat ��ʽ����
	* @retval ��
	*/
void Log( const char * sFormat, ...)
{
	
	xSemaphoreTake( log_mutex_handle , portMAX_DELAY ); //��ȡ������
	
	va_list ParamList;
	
	log_buffer.len = 0; //������0
	
	va_start(ParamList, sFormat);

	printf(sFormat, &ParamList);
	
	xQueueSend( log_queue_handle , (void *)&log_buffer , portMAX_DELAY  );
	
	xSemaphoreGive( log_mutex_handle ); //�ͷŻ�����
}


/**
	* @brief  Log ��ӡ����
	* @param  p_parameters ���뺯���Ĳ���
	* @retval ��i
	*/
void TaskLog(void * p_parameters)
{
	struct LOG_INFO log_msg;
	
	log_mutex_handle = xSemaphoreCreateMutex(); //log������Դ

	if( log_mutex_handle == NULL )
	{
		 // The semaphore was not created and must not be used.
		while(1);
	}
	
	log_queue_handle = xQueueCreate( 2, sizeof(struct LOG_INFO) ); //����Log���� �������������ͨѶ

	if( log_queue_handle == NULL )
	{
		// Queue was not created and must not be used. 
		while(1);
	}
	
	SEGGER_RTT_Init();
	
	
	//�ȴ��������� ��ʼ�����
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
		if( xQueueReceive( log_queue_handle , &( log_msg ),( TickType_t ) portMAX_DELAY ) == pdPASS ) //������������
		{
			SEGGER_RTT_WriteNoLock(0, log_msg.data, log_msg.len);
		}
	}
	
	
	
	
	
}




/******************* (C) COPYRIGHT 2020 JSXC  *****END OF FILE****/
