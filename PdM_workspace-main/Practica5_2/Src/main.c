/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "API_delay.h"
#include "API_debounce.h"
#include "API_uart.h"
#include "SysConfig.h"

/* Private typedef -----------------------------------------------------------*/
#define DELAY_100_MS 100
#define DELAY_500_MS 500
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/


/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void){

	HAL_Init();

	/* Configure the system clock to 180 MHz */
	SystemClock_Config();

	  /* If uart fail to initialize, trap the cpu and blink red led*/
	  if(!uartInit()){
		  BSP_LED_Init(LED_RED);
		  while(1){
			  BSP_LED_Toggle(LED_RED);
			  HAL_Delay(300);
		  }
	  }

	/* Initialize BSP Led for blue led (LED2) */
	BSP_LED_Init(LED_BLUE);

	/* Initialize BSP for button */
	BSP_PB_Init(BUTTON_USER, BUTTON_MODE_GPIO);

	/* Start the FSM */
	debounceFSM_init();


	/* Variable definitions */
	uint8_t delaySelect = 0;
	delay_t ledDelay;

	/* Initialize delay structure and run it */
	delayInit(&ledDelay, DELAY_100_MS);
	delayRead(&ledDelay);

	/* Infinite loop */
	while (1)
	{
		/* Check for the actual state and update the FSM if necessary */
		debounceFSM_update();
		/* Check if the key was pressed */
		if(readKey()){
			/* Change the led toggle delay time with defensive programming */
			if(delaySelect >= 1) {
				delaySelect = 0;
				delayWrite(&ledDelay, DELAY_100_MS);
			}
			else{
				delaySelect = 1;
				delayWrite(&ledDelay, DELAY_500_MS);
			}

		}
		/* Ask for toggle delay time */
		if(delayRead(&ledDelay)){
			BSP_LED_Toggle(LED_BLUE);
		}

	}
}
