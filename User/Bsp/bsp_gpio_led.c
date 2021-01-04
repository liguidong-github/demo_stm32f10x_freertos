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

//#define LED1_ON()    GPIO_SetBits(LED1_GPIO_PORT   , LED1_GPIO_PIN) //亮
//#define LED1_OFF()   GPIO_ResetBits(LED1_GPIO_PORT , LED1_GPIO_PIN) //灭
//#define LED2_ON()    GPIO_SetBits(LED2_GPIO_PORT   , LED2_GPIO_PIN) //亮
//#define LED2_OFF()   GPIO_ResetBits(LED2_GPIO_PORT , LED2_GPIO_PIN) //灭

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
	* @brief  LED控制管脚,配置成推挽输出,并设置LED的初始状态均为灭。
	* @param  无
	* @retval 无
	*/
void LEDInit(void)
{
	GPIO_InitTypeDef	GPIO_InitStructure;
	//使能时钟
	RCC_APB2PeriphClockCmd(LED1_GPIO_CLK , ENABLE);
	RCC_APB2PeriphClockCmd(LED2_GPIO_CLK , ENABLE);

	//配置推挽输出
	GPIO_InitStructure.GPIO_Pin = LED1_GPIO_PIN ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(LED1_GPIO_PORT , &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = LED2_GPIO_PIN ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(LED2_GPIO_PORT , &GPIO_InitStructure);

	//设置LED 初始状态
	Led1Off();
	Led2Off();
}



/**
	* @brief  LED1点亮
	* @param  无
	* @retval 无
	*/
void Led1On(void)
{
	GPIO_SetBits(LED1_GPIO_PORT , LED1_GPIO_PIN);
}

/**
	* @brief  LED1熄灭
	* @param  无
	* @retval 无
	*/
void Led1Off(void)
{
	GPIO_ResetBits(LED1_GPIO_PORT , LED1_GPIO_PIN);
}

/**
	* @brief  LED1状态翻转
	* @param  无
	* @retval 无
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
	* @brief  LED2点亮
	* @param  无
	* @retval 无
	*/
void Led2On(void)
{
	GPIO_SetBits(LED2_GPIO_PORT , LED2_GPIO_PIN);
}

/**
	* @brief  LED2熄灭
	* @param  无
	* @retval 无
	*/
void Led2Off(void)
{
	GPIO_ResetBits(LED2_GPIO_PORT , LED2_GPIO_PIN);
}

/**
	* @brief  LED2状态翻转
	* @param  无
	* @retval 无
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
