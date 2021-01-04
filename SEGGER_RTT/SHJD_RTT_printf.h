/**
  ******************************************************************************
  * @file    
  * @author  
  * @version 
  * @date    
  * @brief   
  ******************************************************************************
  * @attention
  *
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

#ifndef __SHJD_RTT_PRINTF_H
#define __SHJD_RTT_PRINTF_H

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "SEGGER_RTT.h"
#include "SEGGER_RTT_Conf.h"
#include <stdlib.h>
#include <stdarg.h>
#include "semphr.h"
#include "stdio.h"
/* Exported typedef -----------------------------------------------------------*/

/* Exported define ------------------------------------------------------------*/


/* Exported macro -------------------------------------------------------------*/
/* Exported variables ---------------------------------------------------------*/
extern SemaphoreHandle_t xMutex_RTT_printf;


/* Exported function prototypes -----------------------------------------------*/
/* Exported functions ---------------------------------------------------------*/
extern int SEGGER_RTT_vprintf(unsigned BufferIndex, const char * sFormat, va_list * pParamList);

/**
  * @brief  main Function
  * @param  sFormat
	*   This parameter can be one of the following values:
	*     @arg : Pointer to format string, followed by the arguments for conversion
	*    (1) Conversion specifications have following syntax:
	*          %[flags][FieldWidth][.Precision]ConversionSpecifier
	*    (2) Supported flags:
	*          -: Left justify within the field width
	*          +: Always print sign extension for signed conversions
	*          0: Pad with 0 instead of spaces. Ignored when using '-'-flag or precision
	*        Supported conversion specifiers:
	*          c: Print the argument as one char
	*          d: Print the argument as a signed integer
	*          u: Print the argument as an unsigned integer
	*          x: Print the argument as an hexadecimal integer
	*          s: Print the string pointed to by the argument
	*          p: Print the argument as an 8-digit hexadecimal integer. (Argument shall be a pointer to void.)
  * @retval (SET or RESET).
  */
void SHJD_RTT_printf( const char * sFormat, ...);

void SHJD_RTT_printf_Hex(  char *p_data , unsigned short Len);
void SHJD_RTT_printf_ASCII( char *p_data , unsigned short Len);
#endif

/******************* (C) COPYRIGHT 2020  *****END OF FILE****/
