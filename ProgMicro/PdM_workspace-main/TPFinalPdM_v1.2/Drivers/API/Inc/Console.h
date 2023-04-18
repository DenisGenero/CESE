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

void floatToStr(float number, uint8_t *result);

void ConsoleInit();
void ConsolePrintStr(uint8_t * pstring);
void ConsolePrintFloat(float number);
bool ConsoleNewData();
//void ConsoleDataReceive(uint8_t *pData);
uint8_t ConsoleDataReceive();
void ConsoleClear();

/* Wrappers */
//void uartSendString(uint8_t * pstring);
//void uartReceiveStringSize(uint8_t * pstring, uint16_t size);

#endif /* API_INC_CONSOLE_H_ */