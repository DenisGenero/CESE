/*
 * Console.h
 *
 *  Created on: Apr 17, 2023
 *      Author: denis
 */

#ifndef API_INC_CONSOLE_H_
#define API_INC_CONSOLE_H_

#include <stdint.h>
#include "stm32f4xx_hal.h"
#include "port.h"

/* Serial console functions */
void ConsoleInit();
void ConsolePrintStr(uint8_t * pstring);
void ConsolePrintFloat(float number);
void ConsolePrintDeg(int16_t degree);
bool ConsoleNewData();
uint8_t ConsoleDataReceive();
void ConsoleClear();

#endif /* API_INC_CONSOLE_H_ */
