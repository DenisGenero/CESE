#include "main.h"
#include "port.h"
#include "Console.h"

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
	/* MCU peripherals configurations */
	APISysInit();

	ConsoleInit();
	ConsoleClear();
	uint8_t pData[] = "La concha de tu madre \n";
	uint8_t pData2[] = "\r Cariverga ";
	uint8_t pData3[] = "\r Chupacu489";
	ConsolePrintStr(pData);
	ConsolePrintStr(pData2);
	ConsolePrintStr(pData3);
	HAL_Delay(1000);
	ConsoleClear();
	uint8_t op[1];
	ConsolePrintStr(pData);

	while (1)
	{
		ConsolePrintStr(pData2);
		ConsolePrintFloat(12.254);
		HAL_Delay(500);
		ConsolePrintStr(pData3);
		ConsolePrintFloat(0.25);
		HAL_Delay(500);
		if(ConsoleNewData()){
			op[1] = ConsoleDataReceive();
			ConsolePrintStr(op);
		}
	}
}