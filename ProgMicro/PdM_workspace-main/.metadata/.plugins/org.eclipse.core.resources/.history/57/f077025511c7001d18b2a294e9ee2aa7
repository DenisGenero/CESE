 /**
  ******************************************************************************
  * @file    UART/UART_Printf/Src/main.c
  * @author  MCD Application Team
  * @brief   This example shows how to retarget the C library printf function
  *          to the UART.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2017 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "API_delay.h"

/* Private functions ---------------------------------------------------------*/
void delayInit( delay_t * delay, tick_t duration ){
	delay->duration = duration;
	delay->running = false;

}

bool_t delayRead( delay_t * delay ){
	bool_t finish = false;

	if(!delay->running){
		delay->running = true;
		delay->startTime = HAL_GetTick();
	}
	else{
		uint32_t actual_count = HAL_GetTick() - delay->startTime;
		if(actual_count >= delay->duration){
			finish = true;
			delay->running = false;
		}
		else{finish = false;}
	}
	return(finish);
}

void delayWrite( delay_t * delay, tick_t duration ){
	delay->duration = duration;
}
