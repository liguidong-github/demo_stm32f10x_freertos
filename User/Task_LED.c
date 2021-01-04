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

#include "Task_LED.h"
#include "bsp_gpio_led.h"
#include "FreeRTOS.h"
#include "queue.h"
#include "task.h"
#include "Task_Log.h"

/* Private typedef -----------------------------------------------------------*/

typedef struct
{
	unsigned char  id;    //LED�ı�� 0-LED1 1-LED2
	unsigned short data; //��˸ʱ�䳤�� ��λ TASK_LED_INTERVAL ms
}LED_QUEUE_MSG_T;

/* Private define ------------------------------------------------------------*/

#define TASK_LED_INTERVAL 2 //����ѭ�����ʱ�� ��λms

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

static QueueHandle_t led_queue_handle = NULL; //�������� ��LED�����ͨѶ���С�


/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/


/**
	* @brief  ͨ������led_queue_handle������LED1��LED2����˸Ƶ�ʡ�
	* @param  id LED�ı���
	*     @arg  id=1��LED1��  id=2��LED2; 
	* @param  time ��˸ʱ�䳤��. 0-����; 65535-����
	* @retval ��
	*/
void LedFlashConfig(unsigned char id, unsigned short time )
{
	LED_QUEUE_MSG_T led_queue_tx_msg ={0,0}; //���͵Ķ�����Ϣ
	
	if((id==1)||(id==2))
	{
		led_queue_tx_msg.id   = id;
		led_queue_tx_msg.data = time;
		xQueueSend( led_queue_handle , (void *)&led_queue_tx_msg , portMAX_DELAY  );
	}
	
}  


/**
	* @brief  LED��������
	* @param  p_parameters ���뺯���Ĳ���
	* @retval ����ֵ
	*/
void TaskLED(void * p_parameters)
{

	LED_QUEUE_MSG_T led_queue_rx_msg ={0,0}; //���յĶ�����Ϣ
	
	unsigned short led1_tick_cnt = 0; //LED1�ļ����� 
	unsigned short led2_tick_cnt = 0; //LED2�ļ����� 
	
	unsigned short led1_time_len = 0; //LED1����˸ʱ�䳤��
	unsigned short led2_time_len = 0; //LED2����˸ʱ�䳤��
	
	LEDInit(); //�ܽ�Ӳ����ʼ��
	
	led_queue_handle = xQueueCreate( 10, sizeof( LED_QUEUE_MSG_T ) ); //����LED���� �������������ͨѶ

	if( led_queue_handle == NULL )
	{
		/* Queue was not created and must not be used. */
		while(1);
	}
	
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
		
		if( xQueueReceive( led_queue_handle , &( led_queue_rx_msg ),( TickType_t ) 0 ) == pdPASS ) //������������
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
		
		if(led1_time_len==0) //����
		{
			Led1Off();
			led1_tick_cnt = 0; //����ʱ
		}
		else if(led1_time_len==65535) //����
		{
			Led1On();
			led1_tick_cnt = 0; //����ʱ
		}
		else
		{
			led1_tick_cnt++; //��ʼ��ʱ
			if(led1_tick_cnt>=led1_time_len)
			{
				led1_tick_cnt=0;
				Led1Reverse();
			}
		}
		
		if(led2_time_len==0) //����
		{
			Led2Off();
			led2_tick_cnt = 0; //����ʱ
		}
		else if(led2_time_len==65535) //����
		{
			Led2On();
			led2_tick_cnt = 0; //����ʱ
		}
		else
		{
			led2_tick_cnt++;  //��ʼ��ʱ
			if(led2_tick_cnt>=led2_time_len)
			{
				led2_tick_cnt=0;
				Led2Reverse();
			}
		}
	}
}


/******************* (C) COPYRIGHT 2020 JSXC  *****END OF FILE****/
