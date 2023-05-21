/*
 * port.h
 *
 *  Created on: Apr 17, 2023
 *      Author: denis
 */

#ifndef API_INC_PORT_H_
#define API_INC_PORT_H_

#include <stdint.h>
#include <stdbool.h>

void APISysInit();
void SystemClock_Config(void);
void MX_GPIO_Init(void);
void MX_DMA_Init(void);
void MX_TIM1_Init(void);
void MX_SPI1_Init(void);
void MX_USART3_UART_Init(void);

void uartInit();
uint8_t uartReceiveString();
void uartSendString(uint8_t *pstring);
bool uartNewData();

void SPIRead(uint8_t reg, uint8_t *data, uint8_t length);
void SPIWrite(uint8_t reg, uint8_t command);

#endif /* API_INC_PORT_H_ */
