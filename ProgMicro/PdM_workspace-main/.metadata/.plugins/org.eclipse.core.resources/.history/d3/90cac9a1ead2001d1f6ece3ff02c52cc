
#include "main.h"
#include "SysConfig.h"
#include "API_uart.h"

int main(void)
{

  HAL_Init();

  /* Configure the system clock to 180 MHz */
  SystemClock_Config();

  uartInit();

  /* Initialize BSP Led for LED3*/
  BSP_LED_Init(LED3);

  /* Variable for uart test */
  uint8_t hello [] = "Hola mundo \r\n";
  /* Infinite loop */
  while (1)
  {
	  BSP_LED_Toggle(LED3);
	  uartSendString(hello);
	  HAL_Delay(1000);
//	  uartClearScreen();
  }
}

