#include <Neopixel4x4.h>
#include "main.h"
#include "SysConfig.h"

#define ROWS		4
#define COLUMNS		4

/* Description: This is an example of how to use the Neopixel4x4.h and
 * the Neopixel4x4.c files. The connections must be:
 * Neopixel wire		Board connection
 * 		VCC -----------> 	5V
 * 		GND -----------> 	GND
 * 		IN  -----------> 	PE9
 *
 * */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* Configure the system clock @80MHz */
  SystemClock_Config();

  /* Initialize all configured peripherals */
  peripheralInit();

  /* Initialize the Neopixel matrix*/
  neopixelInit();

  /* Turn on and off a couple of led to test the Neopixel driver*/
  while (1)
  {
	  for (uint8_t i = 0; i<ROWS; i++){
		  for (uint8_t j = 0; j<COLUMNS; j++){
			  turnLedOn(i, j, 0, 1, 1);
			  HAL_Delay(100);
		  }
	  }
	  turnCenterOn(0, 200, 0);
	  HAL_Delay(500);
	  turnAllOff();
	  HAL_Delay(500);
	  turnLedOn(1, 3, 0, 0, 10);
	  HAL_Delay(500);
	  turnLedOff(1, 3);
	  HAL_Delay(500);
	  turnRowOn(2, 50, 50, 0);
	  HAL_Delay(500);
	  turnRowOff(2);
	  HAL_Delay(500);
	  turnColumnOn(3, 1, 0, 0);
	  HAL_Delay(500);
	  turnColumnOff(3);
	  HAL_Delay(500);
  }
}
