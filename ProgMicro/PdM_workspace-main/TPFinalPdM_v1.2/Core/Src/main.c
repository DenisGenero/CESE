#include "Console.h"
#include "DigitalLevel.h"

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
	/* MCU peripherals configurations */
	APISysInit();

	/* Initialize serial console */
	ConsoleInit();
	uint8_t welcomeMsg [] = "Bienvenidos al Nivel Digital \r\n";
	/* Send welcome mesageg and start the digital level FSM */
	ConsolePrintStr(welcomeMsg);
	digitalLevInit();

	while (1)
	{
		/* Update digital level FSM */
		digitalLevUpdate();

	}
}
