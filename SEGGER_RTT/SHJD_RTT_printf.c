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

/* Includes ------------------------------------------------------------------*/
#include "SHJD_RTT_printf.h"

	
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/



/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
SemaphoreHandle_t xMutex_RTT_printf = NULL;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
   

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
void SHJD_RTT_printf( const char * sFormat, ...) {
  int r;
	
	if(xMutex_RTT_printf == NULL )
	{
		SEGGER_RTT_Init();
		xMutex_RTT_printf = xSemaphoreCreateMutex();

		if( xMutex_RTT_printf != NULL )
		{
			 /* The semaphore was created successfully and
			 can be used. */
		}
		else
		{
			while(1);
		}
	}
	
	
	
	/*  we obtain the semaphore.  If the semaphore is not available wait portMAX_DELAY ticks to see if it becomes free. */
	xSemaphoreTake( xMutex_RTT_printf , portMAX_DELAY );
	
  va_list ParamList;

  va_start(ParamList, sFormat);
	
	printf(sFormat, &ParamList);
	
  //r = SEGGER_RTT_vprintf(0, sFormat, &ParamList);
  va_end(ParamList);
	
//	if(r<0)
//	{
//		
//	}
	
	/* We have finished accessing the shared resource.  Release the semaphore. */
  xSemaphoreGive( xMutex_RTT_printf );
  //return r;
}



void SHJD_RTT_printf_Hex( char *p_data , unsigned short Len) {
	unsigned short Temp_Cnt;
	
	if(xMutex_RTT_printf == NULL )
	{
		SEGGER_RTT_Init();
		xMutex_RTT_printf = xSemaphoreCreateMutex();

		if( xMutex_RTT_printf != NULL )
		{
			 /* The semaphore was created successfully and
			 can be used. */
		}
		else
		{
			while(1);
		}
	}
	
	
	
	/*  we obtain the semaphore.  If the semaphore is not available wait portMAX_DELAY ticks to see if it becomes free. */
	xSemaphoreTake( xMutex_RTT_printf , portMAX_DELAY );
	
	for(Temp_Cnt=0;Temp_Cnt<Len;Temp_Cnt++)
	{
		if( (*(p_data+Temp_Cnt)<=0x0F))
		{
			printf("0x0%x ",*(p_data+Temp_Cnt));
		}
		else
		{
			printf("0x%x ",*(p_data+Temp_Cnt));
			
		}
		//SEGGER_RTT_printf(0,"0x%x ",*(p_data+Temp_Cnt));
		
	}
	printf("\r\n");
	/* We have finished accessing the shared resource.  Release the semaphore. */
  xSemaphoreGive( xMutex_RTT_printf );
  //return r;
}


void SHJD_RTT_printf_ASCII( char *p_data , unsigned short Len) {
	unsigned short Temp_Cnt;
	
	if(xMutex_RTT_printf == NULL )
	{
		SEGGER_RTT_Init();
		xMutex_RTT_printf = xSemaphoreCreateMutex();

		if( xMutex_RTT_printf != NULL )
		{
			 /* The semaphore was created successfully and
			 can be used. */
		}
		else
		{
			while(1);
		}
	}
	
	
	
	/*  we obtain the semaphore.  If the semaphore is not available wait portMAX_DELAY ticks to see if it becomes free. */
	xSemaphoreTake( xMutex_RTT_printf , portMAX_DELAY );
	
	for(Temp_Cnt=0;Temp_Cnt<Len;Temp_Cnt++)
	{
		printf("%c",*(p_data+Temp_Cnt));
	}
	//printf("\r\n");
	/* We have finished accessing the shared resource.  Release the semaphore. */
  xSemaphoreGive( xMutex_RTT_printf );
  //return r;
}
	










/******************* (C) COPYRIGHT 2020  *****END OF FILE****/
