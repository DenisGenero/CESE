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

    task_Monitor.c (Released 2022-12)

--------------------------------------------------------------------

    task file for FreeRTOS - Event Driven System (EDS) - Project for
    STM32F429ZI_NUCLEO_144.

    See readme.txt for project information.

-*--------------------------------------------------------------------*/


// ------ Includes -------------------------------------------------
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

/* Application includes. */
#include "app_Resources.h"
#include "task_B.h"
#include "task_Monitor.h"

// ------ Macros and definitions ---------------------------------------

// ------ internal data declaration ------------------------------------
/* Task Monitor Counter */
uint32_t lTaskCnt;

// ------ internal functions declaration -------------------------------

// ------ internal data definition -------------------------------------
/* Define the strings that will be passed in as the Supporting Functions parameters.
 * These are defined const and off the stack to ensure they remain valid when the
 * tasks are executing. */
const char *pcTextForTask_Monitor				= "  ==> Task Mon. - Running\r\n";

const char *pcTextForTask_Monitor_lTaskCnt		= "  <=> Task Mon. - lTaskCnt  :";

const char *pcTextForTask_Monitor_WaitRec		= "  ==> Task Mon. - Wait:   Receive       \r\n\n";
const char *pcTextForTask_Monitor_WaitSend		= "  ==> Task Mon. - Wait:   Send          \r\n\n";
const char *pcTextForTask_Monitor_CouldNotSend	= "  ==> Task Mon. - Could not send to the queue \r\n\n";

// ------ external data definition -------------------------------------

// ------ internal functions definition --------------------------------

// ------ external functions definition --------------------------------

/*------------------------------------------------------------------*/
/* Task A thread */
void vTask_Monitor( void *pvParameters )
{
	/*  Declare & Initialize Task Monitor variables */
	BaseType_t xStatus;
	message_xQueueVehicleDateTime_t xStructToSend = { { "------", NULL },
													   "YYYYMMDDHHMMSS" };

	/* Print out the name of this task. */
	vPrintString( pcTextForTask_Monitor );

	/* As per most tasks, this task is implemented within an infinite loop.
	 *
	 * Take the semaphore once to start with so the semaphore is empty before the
	 * infinite loop is entered.  The semaphore was created before the scheduler
	 * was started so before this task ran for the first time.*/
    xSemaphoreTake( xBinarySemaphoreEntry, (portTickType) 0 );

    /* Init Task Monitor Counter */
    lTaskCnt = 0;

    while( 1 )
    {
		/* The first parameter is the queue from which data is to be received.  The
		   queue is created before the scheduler is started, and therefore before this
		   task runs for the first time.

		   The second parameter is the buffer into which the received data will be
		   placed.  In this case the buffer is simply the address of a variable that
		   has the required size to hold the received data.

		   the last parameter is the block time – the maximum amount of time that the
		   task should remain in the Blocked state to wait for data to be available should
		   the queue already be empty. */
    	vPrintString( pcTextForTask_Monitor_WaitRec );
    	xQueueReceive( xQueueVehicle, &xStructToSend.message_xQueueVehicle, portMAX_DELAY );

		/* The first parameter is the queue to which data is being sent.  The
		queue was created before the scheduler was started, so before this task
		started to execute.

		The second parameter is the address of the data to be sent.

		The third parameter is the Block time – the time the task should be kept
		in the Blocked state to wait for space to become available on the queue
		should the queue already be full.  In this case we don’t specify a block
		time because there should always be space in the queue. */
    	vPrintString( pcTextForTask_Monitor_WaitSend );
		xStatus = xQueueSendToBack( xQueueVehicleDateTime, &xStructToSend, 0 );
		if( xStatus != pdPASS )
		{
			/* We could not write to the queue because it was full – this must
			be an error as the queue should never contain more than one item! */
	    	vPrintString( pcTextForTask_Monitor_CouldNotSend );
		}

		/* Update Task Monitor Counter */
    	lTaskCnt++;
    	vPrintStringAndNumber( pcTextForTask_Monitor_lTaskCnt, lTaskCnt);

    }
}

/*------------------------------------------------------------------*-
  ---- END OF FILE -------------------------------------------------
-*------------------------------------------------------------------*/
