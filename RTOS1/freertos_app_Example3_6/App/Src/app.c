/* Copyright 2020, Juan Manuel Cruz.
 * All rights reserved.
 *
 * This file is part of Project => freertos_app_Example3_6
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */


/*--------------------------------------------------------------------*-

    app.c (Released 2022-10)

--------------------------------------------------------------------

    app file for FreeRTOS - Event Driven System (EDS) - Project for
    STM32F429ZI_NUCLEO_144.

    See readme.txt for project information.

-*--------------------------------------------------------------------*/


// ------ Includes -----------------------------------------------------
/* Project includes. */
#include "main.h"
#include "cmsis_os.h"

/* Standard includes. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/* Demo includes. */
#include "supporting_Functions.h"

/* Application & Tasks includes. */
#include "app.h"
#include "task_Function.h"

// ------ Macros and definitions ---------------------------------------

// ------ internal data declaration ------------------------------------
/* Declare a variable of type xTaskHandle. This is used to reference tasks. */
TaskHandle_t xTask1Handle;
TaskHandle_t xTask2Handle;
TaskHandle_t xTask3Handle;
TaskHandle_t xTask4Handle;
TaskHandle_t xTask5Handle;
TaskHandle_t xTask6Handle;

// ------ internal functions declaration -------------------------------

// ------ internal data definition -------------------------------------
const char *pcTextForMain = "freertos_app_Example3_6 is running: PO (3 de 6)\r\n\n";

// ------ external data definition -------------------------------------

// ------ internal functions definition --------------------------------

// ------ external functions definition --------------------------------


/*------------------------------------------------------------------*/
/* App Initialization */
void appInit( void )
{
	LDX_Config_t* ptr;
	BaseType_t ret;

	/* Print out the name of this Example. */
  	vPrintString( pcTextForMain );

	ptr = &LDX_Config[0];
	/* Button for Led 1 task function  */
	ret = xTaskCreate( vTaskButton,				/* Pointer to the function thats implement the task. */
					   "Task 1",					/* Text name for the task. This is to facilitate debugging only. */
					   (2 * configMINIMAL_STACK_SIZE),	/* Stack depth in words. 				*/
	                   (void*)ptr,    				/* Pass the index as the task parameter. */
					   (tskIDLE_PRIORITY + 1UL),	/* This task will run at priority 1. 		*/
					   &xTask1Handle );				/* We are using a variable as task handle.	*/

	/* Check the task was created successfully. */
	configASSERT( ret == pdPASS );

	/* Led 1 task thread at priority 1 */
	ret = xTaskCreate( vTaskLed,				/* Pointer to the function thats implement the task. */
					   "Task 2",					/* Text name for the task. This is to facilitate debugging only. */
					   (2 * configMINIMAL_STACK_SIZE),	/* Stack depth in words. 				*/
	                   (void*)ptr,    				/* Pass the index as the task parameter. */
					   (tskIDLE_PRIORITY + 1UL),	/* This task will run at priority 1. 		*/
					   &xTask2Handle );				/* We are using a variable as task handle.	*/

	/* Check the task was created successfully. */
	configASSERT( ret == pdPASS );

	ptr = &LDX_Config[1];
	/* Button for Led 2 task function  */
	ret = xTaskCreate( vTaskButton,				/* Pointer to the function thats implement the task. */
						"Task 3",					/* Text name for the task. This is to facilitate debugging only. */
						(2 * configMINIMAL_STACK_SIZE),	/* Stack depth in words. 				*/
						(void*)ptr,    				/* Pass the index as the task parameter. */
						(tskIDLE_PRIORITY + 1UL),	/* This task will run at priority 1. 		*/
						&xTask3Handle );				/* We are using a variable as task handle.	*/

	/* Check the task was created successfully. */
	configASSERT( ret == pdPASS );

	/* Led 2 task thread at priority 1 */
	ret = xTaskCreate( vTaskLed,				/* Pointer to the function thats implement the task. */
						"Task 4",					/* Text name for the task. This is to facilitate debugging only. */
						(2 * configMINIMAL_STACK_SIZE),	/* Stack depth in words. 				*/
						(void*)ptr,    				/* Pass the index as the task parameter. */
						(tskIDLE_PRIORITY + 1UL),	/* This task will run at priority 1. 		*/
						&xTask4Handle );				/* We are using a variable as task handle.	*/

	/* Check the task was created successfully. */
	configASSERT( ret == pdPASS );

	ptr = &LDX_Config[2];
	/* Button for Led 3 task function  */
	ret = xTaskCreate( vTaskButton,				/* Pointer to the function thats implement the task. */
						"Task 5",					/* Text name for the task. This is to facilitate debugging only. */
						(2 * configMINIMAL_STACK_SIZE),	/* Stack depth in words. 				*/
						(void*)ptr,    				/* Pass the index as the task parameter. */
						(tskIDLE_PRIORITY + 1UL),	/* This task will run at priority 1. 		*/
						&xTask5Handle );				/* We are using a variable as task handle.	*/

	/* Check the task was created successfully. */
	configASSERT( ret == pdPASS );

	/* Led 3 task thread at priority 1 */
	ret = xTaskCreate( vTaskLed,				/* Pointer to the function thats implement the task. */
						"Task 6",					/* Text name for the task. This is to facilitate debugging only. */
						(2 * configMINIMAL_STACK_SIZE),	/* Stack depth in words. 				*/
						(void*)ptr,    				/* Pass the index as the task parameter. */
						(tskIDLE_PRIORITY + 1UL),	/* This task will run at priority 1. 		*/
						&xTask6Handle );				/* We are using a variable as task handle.	*/

	/* Check the task was created successfully. */
	configASSERT( ret == pdPASS );
}

/*------------------------------------------------------------------*-
  ---- END OF FILE -------------------------------------------------
-*------------------------------------------------------------------*/
