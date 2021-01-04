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
  
#ifndef __BSP_GPIO_LED_H
#define __BSP_GPIO_LED_H

/* Includes ------------------------------------------------------------------*/
/* Exported typedef -----------------------------------------------------------*/
/* Exported define ------------------------------------------------------------*/
/* Exported macro -------------------------------------------------------------*/
/* Exported variables ---------------------------------------------------------*/
/* Exported function prototypes -----------------------------------------------*/
/* Exported functions ---------------------------------------------------------*/

/**
	* @brief  LED���ƹܽ�,���ó��������,������LED�ĳ�ʼ״̬��Ϊ��
	* @param  ��
	* @retval ��
	*/
void LEDInit(void);

/**
	* @brief  LED1����
	* @param  ��
	* @retval ��
	*/
void Led1On(void);
/**
	* @brief  LED1Ϩ��
	* @param  ��
	* @retval ��
	*/
void Led1Off(void);

/**
	* @brief  LED1״̬��ת
	* @param  ��
	* @retval ��
	*/
void Led1Reverse(void);

/**
	* @brief  LED2����
	* @param  ��
	* @retval ��
	*/
void Led2On(void);

/**
	* @brief  LED2Ϩ��
	* @param  ��
	* @retval ��
	*/
void Led2Off(void);

/**
	* @brief  LED2״̬��ת
	* @param  ��
	* @retval ��
	*/
void Led2Reverse(void);

#endif
