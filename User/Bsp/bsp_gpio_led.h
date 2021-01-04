/**
  ******************************************************************************
  * @file    GPIO_LED.c
  * @author  江苏鑫晨 控制产品部
  * @version V1.0.0
  * @date    2020-12-18
  * @brief   
  ******************************************************************************
  * @attention
  *
  * LED控制的硬件初始化。 LED控制管脚,配置成推挽输出,并设置LED的初始状态均为灭。
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
	* @brief  LED控制管脚,配置成推挽输出,并设置LED的初始状态均为灭。
	* @param  无
	* @retval 无
	*/
void LEDInit(void);

/**
	* @brief  LED1点亮
	* @param  无
	* @retval 无
	*/
void Led1On(void);
/**
	* @brief  LED1熄灭
	* @param  无
	* @retval 无
	*/
void Led1Off(void);

/**
	* @brief  LED1状态翻转
	* @param  无
	* @retval 无
	*/
void Led1Reverse(void);

/**
	* @brief  LED2点亮
	* @param  无
	* @retval 无
	*/
void Led2On(void);

/**
	* @brief  LED2熄灭
	* @param  无
	* @retval 无
	*/
void Led2Off(void);

/**
	* @brief  LED2状态翻转
	* @param  无
	* @retval 无
	*/
void Led2Reverse(void);

#endif
