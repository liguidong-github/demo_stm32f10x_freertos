/**
  ******************************************************************************
  * @file    GPIO_LED.c
  * @author  �����γ� ���Ʋ�Ʒ��
  * @version V1.0.0
  * @date    2020-12-18
  * @brief   
  ******************************************************************************
  * @attention
  *
  * LED���Ƶ�Ӳ����ʼ���� LED���ƹܽ�,���ó��������,������LED�ĳ�ʼ״̬��Ϊ��
  * 
	* 
  * 
  * 
  * 
  * 
  *
  * 
  ******************************************************************************
  */  

/* Includes ------------------------------------------------------------------*/
#include "bsp_gpio_led.h"
#include "stm32f10x.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

#define LED1_GPIO_PORT	GPIOA								
#define LED1_GPIO_CLK		RCC_APB2Periph_GPIOA
#define LED1_GPIO_PIN		GPIO_Pin_7

#define LED2_GPIO_PORT	GPIOA								
#define LED2_GPIO_CLK	  RCC_APB2Periph_GPIOA
#define LED2_GPIO_PIN	  GPIO_Pin_8

//#define LED1_ON()    GPIO_SetBits(LED1_GPIO_PORT   , LED1_GPIO_PIN) //��
//#define LED1_OFF()   GPIO_ResetBits(LED1_GPIO_PORT , LED1_GPIO_PIN) //��
//#define LED2_ON()    GPIO_SetBits(LED2_GPIO_PORT   , LED2_GPIO_PIN) //��
//#define LED2_OFF()   GPIO_ResetBits(LED2_GPIO_PORT , LED2_GPIO_PIN) //��

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
	* @brief  LED���ƹܽ�,���ó��������,������LED�ĳ�ʼ״̬��Ϊ��
	* @param  ��
	* @retval ��
	*/
void LEDInit(void)
{
	GPIO_InitTypeDef	GPIO_InitStructure;
	//ʹ��ʱ��
	RCC_APB2PeriphClockCmd(LED1_GPIO_CLK , ENABLE);
	RCC_APB2PeriphClockCmd(LED2_GPIO_CLK , ENABLE);

	//�����������
	GPIO_InitStructure.GPIO_Pin = LED1_GPIO_PIN ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(LED1_GPIO_PORT , &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = LED2_GPIO_PIN ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(LED2_GPIO_PORT , &GPIO_InitStructure);

	//����LED ��ʼ״̬
	Led1Off();
	Led2Off();
}



/**
	* @brief  LED1����
	* @param  ��
	* @retval ��
	*/
void Led1On(void)
{
	GPIO_SetBits(LED1_GPIO_PORT , LED1_GPIO_PIN);
}

/**
	* @brief  LED1Ϩ��
	* @param  ��
	* @retval ��
	*/
void Led1Off(void)
{
	GPIO_ResetBits(LED1_GPIO_PORT , LED1_GPIO_PIN);
}

/**
	* @brief  LED1״̬��ת
	* @param  ��
	* @retval ��
	*/
void Led1Reverse(void)
{
	if( GPIO_ReadInputDataBit(LED1_GPIO_PORT, LED1_GPIO_PIN)==SET )
	{
		GPIO_ResetBits(LED1_GPIO_PORT , LED1_GPIO_PIN);
	}
	else
	{
		GPIO_SetBits(LED1_GPIO_PORT , LED1_GPIO_PIN);
	}
}

/**
	* @brief  LED2����
	* @param  ��
	* @retval ��
	*/
void Led2On(void)
{
	GPIO_SetBits(LED2_GPIO_PORT , LED2_GPIO_PIN);
}

/**
	* @brief  LED2Ϩ��
	* @param  ��
	* @retval ��
	*/
void Led2Off(void)
{
	GPIO_ResetBits(LED2_GPIO_PORT , LED2_GPIO_PIN);
}

/**
	* @brief  LED2״̬��ת
	* @param  ��
	* @retval ��
	*/
void Led2Reverse(void)
{
	if( GPIO_ReadInputDataBit(LED2_GPIO_PORT, LED2_GPIO_PIN)==SET )
	{
		GPIO_ResetBits(LED2_GPIO_PORT , LED2_GPIO_PIN);
	}
	else
	{
		GPIO_SetBits(LED2_GPIO_PORT , LED2_GPIO_PIN);
	}
}





/******************* (C) COPYRIGHT 2020 JSXC  *****END OF FILE****/
