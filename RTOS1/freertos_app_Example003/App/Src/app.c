/* Copyright 2020, Juan Manuel Cruz.
 * All rights reserved.
 *
 * This file is part of Project => freertos_app_Example003
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

    app.c (Released 2022-12)

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
#include "task_A.h"
#include "task_B.h"
#include "task_Monitor.h"
#include "task_Test.h"

// ------ Macros and definitions ---------------------------------------
#define TaskBQuantity	2

// ------ internal data declaration ------------------------------------
/* Declare a variable of type xSemaphoreHandle.  This is used to reference the
 * semaphore that is used to synchronize a task with other task. */
xSemaphoreHandle xBinarySemaphoreEntry;
xSemaphoreHandle xBinarySemaphoreExit0;
xSemaphoreHandle xBinarySemaphoreExit1;
xSemaphoreHandle xCountingSemaphoreContinue;

/* Declare a variable of type xSemaphoreHandle.  This is used to reference the
 * mutex type semaphore that is used to ensure mutual exclusive access to ........ */
xSemaphoreHandle xMutex;

/* Declare a variable of type QueueHandle_t. This is used to reference queues. */
QueueHandle_t xQueueVehicle;
QueueHandle_t xQueueVehicleDateTime;

/* Declare a variable of type xTaskHandle. This is used to reference tasks. */
xTaskHandle vTask_AHandle;
xTaskHandle vTask_B0Handle;
xTaskHandle vTask_B1Handle;
xTaskHandle vTask_MonitorHandle;
xTaskHandle vTask_TestHandle;

/* Task A & B Counter	*/
uint32_t	lTasksCnt;

// ------ internal functions declaration -------------------------------

// ------ internal data definition -------------------------------------
const char *pcTextForMain = "freertos_app_Example003 is running: parking lot\r\n\n";

// ------ external data definition -------------------------------------

// ------ internal functions definition --------------------------------

// ------ external functions definition --------------------------------


/*------------------------------------------------------------------*/
/* App Initialization */
void appInit( void )
{
	uint32_t index;

	/* Print out the name of this Example. */
  	vPrintString( pcTextForMain );

    /* Before a semaphore is used it must be explicitly created.
     * In this example a binary semaphore is created. */
    vSemaphoreCreateBinary( xBinarySemaphoreEntry    );
    vSemaphoreCreateBinary( xBinarySemaphoreExit0    );
    vSemaphoreCreateBinary( xBinarySemaphoreExit1    );
    /* Create a counting semaphore that has a maximum count of TaskBQuantity
     * and an initial count of 0. */
    xCountingSemaphoreContinue = xSemaphoreCreateCounting( TaskBQuantity, 0 );

    /* Check the semaphore was created successfully. */
	configASSERT( xBinarySemaphoreEntry      !=  NULL );
	configASSERT( xBinarySemaphoreExit0      !=  NULL );
	configASSERT( xBinarySemaphoreExit1      !=  NULL );
	configASSERT( xCountingSemaphoreContinue !=  NULL );

    /* Add semaphore to registry. */
	vQueueAddToRegistry(xBinarySemaphoreEntry,     "xBinarySemaphoreEntry");
    vQueueAddToRegistry(xBinarySemaphoreExit0,      "xBinarySemaphoreExit0");
    vQueueAddToRegistry(xBinarySemaphoreExit1,      "xBinarySemaphoreExit1");
    vQueueAddToRegistry(xCountingSemaphoreContinue, "xCountingSemaphoreContinue");

    /* Before a semaphore is used it must be explicitly created.
     * In this example a mutex semaphore is created. */
    xMutex = xSemaphoreCreateMutex();

    /* Add mutex to registry. */
	vQueueAddToRegistry(xMutex, "xMutex");

    /* Check the mutex was created successfully. */
    configASSERT( xMutex !=  NULL );

    /* The queue is created to hold a maximum of 5 structures of type message_xQueueV..._t . */
    xQueueVehicle		  = xQueueCreate( 5, sizeof( message_xQueueVehicle_t ) );
    xQueueVehicleDateTime = xQueueCreate( 5, sizeof( message_xQueueVehicleDateTime_t ) );

    /* Check the queues was created successfully */
    configASSERT( xQueueVehicle			!= NULL );
    configASSERT( xQueueVehicleDateTime != NULL );

    /* Add queue to registry. */
	vQueueAddToRegistry(xQueueVehicle,         "xQueueVehicle");
	vQueueAddToRegistry(xQueueVehicleDateTime, "xQueueVehicleDateTime");

	BaseType_t ret;

    /* Task A thread at priority 2 */
    ret = xTaskCreate( vTask_A,						/* Pointer to the function thats implement the task. */
					   "Task A",					/* Text name for the task. This is to facilitate debugging only. */
					   (2 * configMINIMAL_STACK_SIZE),	/* Stack depth in words. 				*/
					   NULL,						/* We are not using the task parameter.		*/
					   (tskIDLE_PRIORITY + 2UL),	/* This task will run at priority 1. 		*/
					   &vTask_AHandle );			/* We are using a variable as task handle.	*/

    /* Check the task was created successfully. */
    configASSERT( ret == pdPASS );

	index = 0;
    /* Task B 0 thread at priority 2 */
    ret = xTaskCreate( vTask_B,						/* Pointer to the function thats implement the task. */
					   "Task B 0",					/* Text name for the task. This is to facilitate debugging only. */
					   (2 * configMINIMAL_STACK_SIZE),	/* Stack depth in words. 				*/
	                   (void*)index,    			/* Pass the index as the task parameter. */
					   (tskIDLE_PRIORITY + 2UL),	/* This task will run at priority 1. 		*/
					   &vTask_B0Handle );			/* We are using a variable as task handle.	*/

    /* Check the task was created successfully. */
    configASSERT( ret == pdPASS );

	index = 1;
    /* Task B 1 thread at priority 2 */
    ret = xTaskCreate( vTask_B,						/* Pointer to the function thats implement the task. */
					   "Task B 1",					/* Text name for the task. This is to facilitate debugging only. */
					   (2 * configMINIMAL_STACK_SIZE),	/* Stack depth in words. 				*/
	                   (void*)index,    			/* Pass the index as the task parameter. */
					   (tskIDLE_PRIORITY + 2UL),	/* This task will run at priority 1. 		*/
					   &vTask_B1Handle );			/* We are using a variable as task handle.	*/

    /* Check the task was created successfully. */
    configASSERT( ret == pdPASS );

    /* Task Monitor thread at priority 2 */
    ret = xTaskCreate( vTask_Monitor,				/* Pointer to the function thats implement the task. */
					   "Task Monitor",				/* Text name for the task. This is to facilitate debugging only. */
					   (2 * configMINIMAL_STACK_SIZE),	/* Stack depth in words. 				*/
					   NULL,						/* We are not using the task parameter.		*/
					   (tskIDLE_PRIORITY + 2UL),	/* This task will run at priority 1. 		*/
					   &vTask_MonitorHandle );		/* We are using a variable as task handle.	*/

    /* Check the task was created successfully. */
    configASSERT( ret == pdPASS );

    /* Task Test at priority 1, periodically excites the other tasks */
    ret = xTaskCreate( vTask_Test,					/* Pointer to the function thats implement the task. */
					   "Task Test",					/* Text name for the task. This is to facilitate debugging only. */
					   (2 * configMINIMAL_STACK_SIZE),	/* Stack depth in words. 				*/
					   NULL,						/* We are not using the task parameter.		*/
					   (tskIDLE_PRIORITY + 1UL),	/* This task will run at priority 2. 		*/
					   &vTask_TestHandle );			/* We are using a variable as task handle.	*/

    /* Check the task was created successfully. */
    configASSERT( ret == pdPASS );
}

/*------------------------------------------------------------------*-
  ---- END OF FILE -------------------------------------------------
-*------------------------------------------------------------------*/
