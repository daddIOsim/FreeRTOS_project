/* Standard includes.  */
#include <stdio.h>
#include <string.h>

/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"
/* Not feasible set of tasks */
/**/
#define A_PERIOD 5
#define B_PERIOD 7
#define A_CAPACITY 2
#define B_CAPACITY 4




/* Feasible set of tasks 
#define A_PERIOD 3
#define A_CAPACITY 1
#define B_PERIOD 5
#define B_CAPACITY 2
*/

/* Task handlers creation. */
TaskHandle_t myTask1Handle = NULL;
TaskHandle_t myTask2Handle = NULL;

/* Task functions definitions*/
static void myTask1( void *p );
static void myTask2( void *p );

/* 
 * Main function
 * Two tasks are created and scheduled with the basic scheduler configured as RM
 */

void main_tasks_rate_mono( void )
{
/* Period of task1 < period of task2 --> priority of task1 > priority of task2
 */

	xTaskCreate(myTask1, "task1", 200, (void*) 0, tskIDLE_PRIORITY+2, &myTask1Handle);
	xTaskCreate(myTask2, "task2", 200, (void*) 0, tskIDLE_PRIORITY+1, &myTask2Handle);
	
	vTaskStartScheduler();
	/* infinite loop */

	while(1){

		/* add application code here */
	}
}

/* Task functions implementations */

static void myTask1 (void *p)
{
	(void) p;

	TickType_t xLastWakeTimeA;

	const TickType_t xPeriod = pdMS_TO_TICKS(A_PERIOD * 1000); // task A period in ticks
	const TickType_t comp_time = pdMS_TO_TICKS(A_CAPACITY * 1000); // task A computation time in ticks

	xLastWakeTimeA = 0;

	while(1)
	{
		TickType_t xTime = xTaskGetTickCount();

		uint32_t inner_counter = 0;


		while(inner_counter < comp_time)
		{
			TickType_t xTime2 = xTaskGetTickCount();
			inner_counter++;
			while(xTaskGetTickCount() - xTime2 < 1){
				
			};
 		}

		vTaskDelayUntil( &xLastWakeTimeA, xPeriod );
	}

}

static void myTask2 (void *p)
{
	(void) p;

	TickType_t xLastWakeTimeB;

	const TickType_t xPeriod = pdMS_TO_TICKS(B_PERIOD * 1000); // task B period
	const TickType_t comp_time = pdMS_TO_TICKS(B_CAPACITY * 1000); // task B computation time
	
	xLastWakeTimeB = 0;

	while(1)
	{
		TickType_t xTime = xTaskGetTickCount ();

		uint32_t inner_counter = 0;


		while(inner_counter < comp_time)
		{
			TickType_t xTime2 = xTaskGetTickCount();
			inner_counter++;
			while(xTaskGetTickCount() - xTime2 < 1){
				
			};
 		}
		
		vTaskDelayUntil( &xLastWakeTimeB, xPeriod);
	}

}

