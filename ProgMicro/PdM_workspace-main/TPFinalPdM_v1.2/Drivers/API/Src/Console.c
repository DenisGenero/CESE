/*
 * Console.c
 *
 *  Created on: Apr 17, 2023
 *      Author: denis
 */

#include "Console.h"

uint16_t printedLines = 0;

void ConsoleInit(){
	uartInit();
}

bool ConsoleNewData(){
	return(uartNewData());
}

/* @brief: print a uint8_t chain to the console through the uart
 * @param: chain to be printed
 * @retval: None
 * */
void ConsolePrintStr(uint8_t *pstring){
	uartSendString(pstring);
	printedLines ++;
}

/* @brief: print a float point of up to 3 digits in the integer position and up
 * to 3 after comma digits. Zeros in left (hundreds and tens) and last right position
 * are not printed.
 * @param: float number to print
 * @retval: None
 * */
void ConsolePrintFloat(float number){
	uint16_t num = number*1000;
	/* Define the amount of digit to print: 6 digit and a comma character.
	 * the last position is reserved as end of transmission*/
	uint8_t digitNumber = 8;
	/* Comma position must be in the 3° place from right to left, as this function
	 * can only show up to 3 float digit and up to 3 integer portion digits. The calculation
	 * is commaPlace = digitNumber - commaOffset*/
	uint8_t commaOffset = 5;
	uint8_t comma [1] = ",";
	/* Invisible space character is set to respect data padding */
	uint8_t whiteSpace[1] = " ";
	uint8_t buffer[digitNumber];

	for(uint8_t i = 2; i <= digitNumber; i++){
		if (i == commaOffset){
			buffer[digitNumber-i] = *comma;
		}
		else{
			buffer[digitNumber - i] = num%10 + 48;
			num = (uint16_t)num/10;
		}
	}
	/* check for zeros in left positions (in hundred and ten position) */
	if(buffer[0] == 48){
		buffer[0] = *whiteSpace;
		if(buffer[1] == 48){
			buffer[1] = *whiteSpace;
		}
	}
	/* check for zeros in the last position (only the last one)*/
	if(buffer[digitNumber-2] == 48){
		buffer[digitNumber-2] = *whiteSpace;
	}
	/* Add end of trasmition mark at the end of the buffer */
	buffer[digitNumber-1] = 0;

	/* Send the result */
	uartSendString(buffer);
	printedLines ++;
}

//void ConsoleDataReceive(uint8_t *pData){
//	uartReceiveString(pData);
//}
uint8_t ConsoleDataReceive(){
	return(uartReceiveString());
}

void ConsoleClear(){
//	uint8_t clearCommand [] = "\033[2J";
	uint8_t clearCommand[] = "\r                                                                           \n";
	uint8_t homePosition [] = "\033[H";
	/* Go to home position*/
	uartSendString(homePosition);
	/* Erase all printed lines*/
	for (uint16_t i = 0; i< printedLines; i ++){
		uartSendString(clearCommand);
	}
	/* Set once again the cursor to home position*/
	uartSendString(homePosition);
}