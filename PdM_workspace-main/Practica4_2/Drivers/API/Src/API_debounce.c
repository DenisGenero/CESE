
/* Includes ------------------------------------------------------------------*/
#include "API_debounce.h"

/* Private functions ---------------------------------------------------------*/
/* ################ Button state definitions ################ */
/* This typedef can not be declared as static or private variable because it is on a .c file*/
typedef enum{
BUTTON_UP,
BUTTON_FALLING,
BUTTON_DOWN,
BUTTON_RISING,
} debounceState_t;

static delay_t delay;
static debounceState_t actualState;
static bool_t isPressed;

// TODO:
/* @brief
 * Tell the API if the button is pressed or released
 * @param  None
 * @retval true if the button is press, false if it is released*/
bool_t readKey(){
	bool_t flag = false;
	if (isPressed) {
		flag = true;
		isPressed = false;
	}

	return flag;
}

/* @brief
 * Initialize the Finite State Machine assuming that
 * the button is release (normal button state --> normal open)
 * @param  None
 * @retval None */
void debounceFSM_init(){
	/* Set the initial state --> normal state is open */
	actualState = BUTTON_UP;
	/* Load the de-bouncing time */
	delayInit(&delay, DEBOUNCE_TIME);
}

/* @brief
 * Ask for the actual state and determine if the button was hold down or up
 *  applying a de-bouncing method, that consist in check twice with a 40 milliseconds wait,
 *  if it was a real state change or a spurious mechanic noise.
 * @param  None
 * @retval None */
void debounceFSM_update(){
	switch(actualState){
		case BUTTON_UP:
			if(BSP_PB_GetState(BUTTON_USER)){
				/* Update to next state */
				actualState = BUTTON_FALLING;
				/* Start the delay count */
				delayRead(&delay);
			}
		break;

		case BUTTON_FALLING:
			/* Check for the de-bouncing time */
			if(delayRead(&delay)){
				/* If after de-bouncing time the button is still pressed, it is assumed
				 * that the user has pressed the button */
				if(BSP_PB_GetState(BUTTON_USER)) {
					/* Update to next state */
					actualState = BUTTON_DOWN;
					/* Set the flag to indicate that the button is pressed */
					isPressed = true;
				}
				else{
					/* If spurious noise detected, return to previous state */
					actualState = BUTTON_UP;
				}
			}
		  break;

		case BUTTON_DOWN:
		  if(!BSP_PB_GetState(BUTTON_USER)){
			  /* Update to next state */
			  actualState = BUTTON_RISING;
			  /* Start the delay count */
			  delayRead(&delay);
		  }
		  break;

		case BUTTON_RISING:
			/* If after de-bouncing time the button is still released, it is assumed
			 * that the user has released the button */
			if(delayRead(&delay)){
				if(!BSP_PB_GetState(BUTTON_USER)){
					/* Update to next state */
					actualState = BUTTON_UP;
					/* Indicate that the button is no more pressed */
					isPressed = false;
				}
				else{
					/* If spurious noise detected, return to previous state */
					actualState = BUTTON_DOWN;
				}
			}
		  break;
	  default:
		  /* Defensive guard: if another state is loaded in actualState variable,
		   * return to the first state */
		  actualState = BUTTON_UP;
		  break;
	}

}
