/*
 * API_uart.c
 *
 *  Created on: 3 abr. 2023
 *      Author: denis
 */

#include "API_uart.h"

/* UART handler declaration */
UART_HandleTypeDef UartHandle;

#define BAUD_RATE 115200
#define DEFAULT_TIMEOUT 50

uint8_t initialConfig [] = "\r UART configured: 115200 Baud-rate, 8 bits, Parity: None, 1 stop bit \n\r";

/* @brief: initialize USART3 module. Print UART configuration
 * @param: none
 * @retval: none */

bool_t uartInit(){

	/* Flag to indicate correct initialization */
	bool_t correct_init = true;
	/*##-1- Configure the UART peripheral ######################################*/
	/* Put the USART peripheral in the Asynchronous mode (UART Mode) */
	/* UART configured as follows:
	      - Word Length = 8 Bits (7 data bit + 1 parity bit) :
		                  BE CAREFUL : Program 7 data bits + 1 parity bit in PC HyperTerminal
	      - Stop Bit    = One Stop bit
	      - Parity      = ODD parity
	      - BaudRate    = 9600 baud
	      - Hardware flow control disabled (RTS and CTS signals) */
	  UartHandle.Instance        = USARTx;
	  UartHandle.Init.BaudRate   = BAUD_RATE;
	  UartHandle.Init.WordLength = UART_WORDLENGTH_8B;
	  UartHandle.Init.StopBits   = UART_STOPBITS_1;
	  UartHandle.Init.Parity     = UART_PARITY_NONE;
	  UartHandle.Init.HwFlowCtl  = UART_HWCONTROL_NONE;
	  UartHandle.Init.Mode       = UART_MODE_TX_RX;
	  UartHandle.Init.OverSampling = UART_OVERSAMPLING_16;
	  if (HAL_UART_Init(&UartHandle) != HAL_OK)
	  {
	    /* If initialization fail, set the error flag*/
		  correct_init = false;
	  }
	  if(correct_init){
		  uartClearScreen();
		  /* Output a message on to know that uart configuration has been done successfully */
		  uartSendString(initialConfig);
	  }
	  return(correct_init);
}

/* @brief: Send a string chain
 * @param: pointer to data
 * @retval: none*/
void uartSendString(uint8_t * pstring){
	while(*pstring){
		HAL_UART_Transmit(&UartHandle, pstring, 1, DEFAULT_TIMEOUT);
		pstring += 1;
	}
}

/* @brief: Send a string chain specifying the data length
 * @param:
 * 	- pointer to data
 * 	- data length
 * @retva: none*/
void uartSendStringSize(uint8_t * pstring, uint16_t size){
	for(uint8_t i=0; i<size; i ++){
			HAL_UART_Transmit(&UartHandle, pstring, size, DEFAULT_TIMEOUT);
			pstring ++;
		}
}

/* @brief: Receive a string chain data
 * @param:
 * 	- pointer to data
 * 	- data length
 * @retval: none*/
void uartReceiveStringSize(uint8_t * pstring, uint16_t size){
	HAL_UART_Receive(&UartHandle, pstring, size, DEFAULT_TIMEOUT);
}

/* This function was made for test purposes */
/* @brief: clean serial monitor and set cursor to home position
 * @param: none
 * @retval: none*/
void uartClearScreen(){
	uint8_t clearCommand [] = "\033[2J";
	uint8_t homePosition [] = "\033[H";
	HAL_UART_Transmit(&UartHandle, homePosition, sizeof(homePosition), 150);
	HAL_UART_Transmit(&UartHandle, clearCommand, sizeof(clearCommand), 150);
	HAL_Delay(150);
}
