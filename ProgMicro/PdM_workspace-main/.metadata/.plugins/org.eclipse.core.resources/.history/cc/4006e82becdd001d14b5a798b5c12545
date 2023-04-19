#include <Neopixel4x4.h>
#include "stm32f4xx_hal.h"
#include "main.h"
#include <stdbool.h>

#define MATRIX_COLUMNS	4
#define MATRIX_ROWS		4
#define DATA_LENGTH 	24
#define SEND_BUFF_SIZE	17 // 24 bit data for each led plus 1 final zero data to keep pwm output low

/* ############# Description #############
 * This file provide functions to control a
 * 4x4 Neopixel led matrix. The led's distribution is:
 *
 *	Column:    0     1     2     3  | Row
 * 	  Wires	-------------------------
 * 		|	| [1]   [2]   [3]   [4] |  0
 * 		V	|						|
 * GND -----| [8]   [7]   [6]   [5] |  1
 * VCC -----|						|
 * DIN -----| [9]  [10]  [11]  [12] |  2
 *	 		|						|
 *	 		| [16] [15]  [14]  [13] |  3
 *	 		-------------------------
 *
 * */

/* ##################### Typedef ##################### */
/* Define a structure for each led*/
typedef struct{
	uint8_t red;
	uint8_t green;
	uint8_t blue;
	uint8_t row;
	uint8_t column;
	uint8_t ledNumber;
	bool ledOn;
}Led_t;

/* ##################### Global variables ##################### */
// Led matrix
Led_t matrix[MATRIX_ROWS][MATRIX_COLUMNS];
// Buffer to store matrix colors
uint16_t sendBuffer [SEND_BUFF_SIZE][DATA_LENGTH];

/* ##################### Public functions ##################### */

///* @brief: Initialize GPIO, TIMER1 and DMA to work with pwm
// * @param: none
// * @retval: none
// * */
//void peripheralInit(){
//	MX_GPIO_Init();
//	MX_DMA_Init();
//	MX_TIM1_Init();
//}

/* @brief: initialize all the matrix led turned off
 * @param: none
 * @retval: none
 * */
void neopixelInit(){
	// Variable to assign led number
	uint8_t position = 1;
	// Load each led with 0
	for (uint8_t i = 0; i < MATRIX_ROWS; i++){
		for (uint8_t j = 0; j < MATRIX_COLUMNS; j++){
			matrix[i][j].red = 0;
			matrix[i][j].green = 0;
			matrix[i][j].blue = 0;
			matrix[i][j].row = i;
			matrix[i][j].column = j;
			matrix[i][j].ledNumber = position;
			matrix[i][j].ledOn = false;
			position ++;
		}
	}
	// Put in the send buffer's last memory position a zero data:
	for(uint8_t i = 0; i < DATA_LENGTH; i++){
		sendBuffer[SEND_BUFF_SIZE-1][i] = 0;
	}
}

/* @brief: Load color in the specified led in the row and col position of the neopixel matrix.
 * This function does not turn the led on. See turnLedOn function.
 * @param:
 * 			- row: desired row
 * 			- col: desired column
 * 			- red: red color intensity (zero is off)
 * 			- green: green color intensity (zero is off)
 * 			- blue: blue color intensity (zero is off)
 * @retval: none
 * */
void loadLedColor(uint8_t row, uint8_t col, uint8_t red, uint8_t green, uint8_t blue){
	uint8_t col_aux = col;
	// Check if parameters are in range
	if((row < MATRIX_ROWS) && (col < MATRIX_COLUMNS)){
		if(row == 1 || row == 3){
			col_aux = 3 - col;
		}
		matrix[row][col_aux].red = red;
		matrix[row][col_aux].green = green;
		matrix[row][col_aux].blue = blue;
	}
}

/* @brief: Load color in the specified led number position of the neopixel matrix,
 * according to the above description. This function does not turn the led on.
 * See turnLedOn function.
 * @param:
 * 			- ledNum: desired led
 * 			- red: red color intensity (zero is off)
 * 			- green: green color intensity (zero is off)
 * 			- blue: blue color intensity (zero is off)
 * @retval: none
 * */
void loadNumLedColor(uint8_t ledNum, uint8_t red, uint8_t green, uint8_t blue){
	for (uint8_t i = 0; i < MATRIX_ROWS; i++){
			for (uint8_t j = 0; j < MATRIX_COLUMNS; j++){
				if(ledNum == matrix[i][j].ledNumber){
					loadLedColor(i, j, red, green, blue);
				}
			}
	}
}

/* @brief: Turn on the specified led in the row and col position of the neopixel matrix.
 * @param:
 * 			- row: desired row
 * 			- col: desired column
 * 			- red: red color intensity (zero is off)
 * 			- green: green color intensity (zero is off)
 * 			- blue: blue color intensity (zero is off)
 * @retval: none
 * */
void turnLedOn(uint8_t row, uint8_t col, uint8_t red, uint8_t green, uint8_t blue){
	// Check if parameters are in range
	if((row < MATRIX_ROWS) && (col < MATRIX_COLUMNS)){
		loadLedColor(row, col, red, green, blue);
		turnSecuenceOn();
	}
}

/* @brief: Turn off the specified led in the row and col position of the neopixel matrix.
 * @param:
 * 			- row: desired row
 * 			- col: desired column
 * @retval: none
 */
void turnLedOff(uint8_t row, uint8_t col){
	// Check if parameters are in range
	if((row < MATRIX_ROWS) && (col < MATRIX_COLUMNS)){
		loadLedColor(row, col, 0, 0, 0);
		turnSecuenceOn();
	}
}

/* @brief: Turn on the specified led column of the neopixel matrix, according to the above description.
 * @param:
 * 			- col: desired column
 * 			- red: red color intensity (zero is off)
 * 			- green: green color intensity (zero is off)
 * 			- blue: blue color intensity (zero is off)
 * @retval: none
 */
void turnColumnOn(uint8_t col, uint8_t red, uint8_t green, uint8_t blue){
	// Check if parameter is in range
	if  (col < MATRIX_COLUMNS){
		for (uint8_t i = 0; i < MATRIX_ROWS; i++){
			loadLedColor(i, col, red, green, blue);
		}
		turnSecuenceOn();
	}
}

/* @brief: Turn off the specified led column of the neopixel matrix, according to the above description.
 * @param:
 * 			- col: desired column
 * @retval: none
*/
void turnColumnOff(uint8_t col){
	// Check if parameter is in range
		if  (col < MATRIX_COLUMNS){
			turnColumnOn(col, 0, 0, 0);
		}
}

/* @brief: Turn on the specified led row of the neopixel matrix, according to the above description.
 * @param:
 * 			- row: desired row
 * 			- red: red color intensity (zero is off)
 * 			- green: green color intensity (zero is off)
 * 			- blue: blue color intensity (zero is off)
 * @retval: none
 */
void turnRowOn(uint8_t row, uint8_t red, uint8_t green, uint8_t blue){
	// Check if parameter is in range
	if  (row < MATRIX_ROWS){
		for (uint8_t i = 0; i < MATRIX_ROWS; i++){
			loadLedColor(row, i, red, green, blue);
		}
		turnSecuenceOn();
	}
}

/* @brief: Turn off the specified led row of the neopixel matrix, according to the above description.
 * @param:
 * 			- row: desired row
 * @retval: none
*/
void turnRowOff(uint8_t row){
	// Check if parameter is in range
	if(row < MATRIX_ROWS){
		turnRowOn(row, 0, 0, 0);
	}
}

/* @brief: Send data buffer to the pwm output.
 * @param: none
 * @retval: none
 * */
void turnSecuenceOn(){
	fillSendBuffer();
	setPWMData((uint32_t *) sendBuffer, SEND_BUFF_SIZE*DATA_LENGTH);
}

/* @brief: Load the send buffer with the matrix information.
 * @param: none
 * @retval: none
 * */
void fillSendBuffer(){
	uint32_t color;
	uint8_t bufIndex = 0;
	for (uint8_t i = 0; i < MATRIX_ROWS; i++){
		for (uint8_t j = 0; j < MATRIX_COLUMNS; j++){
			// Make the 24 bit data for each buffer data
			color = (matrix[i][j].blue<<16) | (matrix[i][j].red<<8) | matrix[i][j].green;
			// Transform the 24 bit data into 24 pwm duties cycles:
			for(int8_t k = 23; k>=0; k--){
				if(color&(1<<k)) sendBuffer[bufIndex][k] = 68; 	// Load an one (DC = 68%)
				else sendBuffer[bufIndex][k] = 32;				// Load a zero (DC = 32%)
			}
			// Prevent buffer overflow and zero end mark erase
			if(bufIndex < SEND_BUFF_SIZE - 1){
				bufIndex ++;
			}
		}
	}
}
