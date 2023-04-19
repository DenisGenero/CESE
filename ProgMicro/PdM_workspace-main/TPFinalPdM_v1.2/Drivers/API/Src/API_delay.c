#include "API_delay.h"

/* @brief: Initialize the count taking in count the SysTick timer
 * @params:
 * 			- delay: variable to store the count
 * 			- duration: amount milliseconds delay
 * @retval: None
 * */
void delayInit(delay_t *delay, tick_t duration ){
	delay->duration = duration;
	delay->running = false;
}

/* @brief: Tells if the count is running.
 * @param: variable where the count is stored
 * @retval: true if the count is running
 * */
bool_t delayRead(delay_t *delay ){
	bool_t finish = false;

	if(!delay->running){
		delay->running = true;
		delay->startTime = HAL_GetTick();
	}
	else{
		uint32_t actual_count = HAL_GetTick() - delay->startTime;
		if(actual_count >= delay->duration){
			finish = true;
			delay->running = false;
		}
		else{finish = false;}
	}
	return(finish);
}

/* @brief: Change the delay duration
 * @params:
 * 			- delay: variable where the count is stored
 * 			- duration: amount milliseconds delay
 * @retval: None
 * */
void delayWrite(delay_t *delay, tick_t duration ){
	delay->duration = duration;
}
