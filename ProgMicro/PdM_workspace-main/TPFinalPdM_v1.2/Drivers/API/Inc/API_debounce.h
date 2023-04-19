/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __API_DEBOUNCE_H
#define __API_DEBOUNCE_H

#include "stm32f4xx_hal.h"  		/* <- HAL include */
#include "stm32f4xx_nucleo_144.h" 	/* <- BSP include */
#include <stdint.h>					/* <- Standard integer library */
#include <stdbool.h>				/* <- Standard boolean library*/
#include "API_delay.h"

#define DEBOUNCE_TIME 40

/* ################ My function definitions ################ */
bool_t readKey();
void debounceFSM_init();
void debounceFSM_update();

#endif /* __API_DEBOUNCE_H */
