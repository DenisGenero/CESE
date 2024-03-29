/**
  ******************************************************************************
  * @file    UART/UART_Printf/Inc/main.h
  * @author  MCD Application Team
  * @brief   Header for main.c module
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __API_DEBOUNCE_H
#define __API_DEBOUNCE_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"  		/* <- HAL include */
#include "stm32f4xx_nucleo_144.h" 	/* <- BSP include */
#include <stdint.h>					/* <- Standard integer library */
#include <stdbool.h>				/* <- Standard boolean library*/
#include "API_delay.h"

/* Exported types ------------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
#define DEBOUNCE_TIME 40
/* Exported functions ------------------------------------------------------- */
/* ################ My function definitions ################ */
bool_t readKey();
void fallingEdge();
void risingEdge();
void debounceFSM_init();
void debounceFSM_update();


#endif /* __API_DEBOUNCE_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
