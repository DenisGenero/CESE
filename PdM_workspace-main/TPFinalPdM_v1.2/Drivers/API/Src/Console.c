/*
 * Console.c
 *
 *  Created on: Apr 17, 2023
 *      Author: denis
 */

#include "Console.h"

/* Variable to keep the count of lines printed */
static uint16_t printedLines = 0;

/* @brief: Initialize the serial console through uart port
 * @param: None
 * @retval: None
 * */
void ConsoleInit(){
	uartInit();
}

/* @brief: Indicates if there is new data in console
 * @param: None
 * @retval: true if data is available
 * */
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

/* @brief: Print an integer number up to 3 digits
 * @param: data to be printed
 * @retval: None
 *  */
void ConsolePrintDeg(int16_t degree){
	/* Amount of digit to print (included sign) */
	uint8_t digitNumber = 4;
	uint8_t buffer[digitNumber];
	uint8_t degMark[] = " grad.\r\n";
	uint16_t num;
	uint8_t plusMark[] = "+";
	uint8_t minusMark[] = "-";
	uint8_t spaceMark[] = "\0";
	/* Offset to map char and integer types */
	uint8_t uintZero = 48;
	/* If number is negative, add a minus sign */
	if(degree < 0){
		buffer[0] = minusMark[0];
		num = -degree;
	}
	else {
		buffer[0] = plusMark[0];
		num = degree;
	}
	for(uint8_t i = 1; i <= digitNumber - 1; i ++){
			buffer[digitNumber - i] = num%10 + uintZero;
			num = num/10;
		}
	if(buffer[1] == uintZero){
		buffer[1] = buffer[2];
		buffer[2] = buffer[3];
		buffer[3] = spaceMark[0];
		if(buffer[1] == uintZero){
			buffer[1] = buffer[2];
			buffer[2] = spaceMark[0];
		}
	}
	ConsolePrintStr(buffer);
	ConsolePrintStr(degMark);
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
	/* Offset to map char and integer types */
	uint8_t uintZero = 48;
	/* Invisible space character is set to respect data padding */
	uint8_t whiteSpace[1] = " ";
	uint8_t buffer[digitNumber];

	for(uint8_t i = 2; i <= digitNumber; i++){
		if (i == commaOffset){
			buffer[digitNumber-i] = *comma;
		}
		else{
			buffer[digitNumber - i] = num%10 + uintZero;
			num = (uint16_t)num/10;
		}
	}
	/* check for zeros in left positions (in hundred and ten position) */
	if(buffer[0] == uintZero){
		buffer[0] = *whiteSpace;
		if(buffer[1] == uintZero){
			buffer[1] = *whiteSpace;
		}
	}
	/* check for zeros in the last position (only the last one)*/
	if(buffer[digitNumber-2] == uintZero){
		buffer[digitNumber-2] = *whiteSpace;
	}
	/* Add end of transmission mark at the end of the buffer */
	buffer[digitNumber-1] = 0;

	/* Send the result */
	uartSendString(buffer);
	printedLines ++;
}

/* @brief: Receive incoming data in non blocking mode
 * @param: None
 * @retval: pointer to data received
 * */
uint8_t ConsoleDataReceive(){
	return(uartReceiveString());
}

/* @brief: Clear printed lines. WARNING: Not all console support escape commands.
 * @param: None
 * @retval: None
 * */
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
