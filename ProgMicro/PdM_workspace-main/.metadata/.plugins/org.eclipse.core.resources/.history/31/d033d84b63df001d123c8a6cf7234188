/*
 * DigitalLeve.c
 *
 *  Created on: 18 abr. 2023
 *      Author: denis
 */
/* Include drivers libraries */
#include "API_delay.h"
#include "Console.h"
#include "API_debounce.h"
#include "mpu9265_SPI.h"
#include "Neopixel4x4.h"

/* Accelerometer reference to determine the inclination plane*/
#define ACCEL_REF		32768 // (2^15) --> half range for each plane
#define CALIB_POS 		50000
/* Sensibility preset values */
#define LO_SENS			15
#define MED_SENS		10
#define HI_SENS			5
/* Configuration options */
#define SENS_OP			49
#define REF_OP			50
/* Sensibility options */
#define HIGH_SENS_OP	49
#define MED_SENS_OP		50
#define LOW_SENS_OP		51

/* Digital level FSM valid states */
typedef enum{
	IDLE,
	MEASURE,
	CONFIG,
	SENSIBILITY,
	REFERENCE
} LevelState_t;

/* Digital level FSM state variable */
static LevelState_t actualState;

/* API messages */
static uint8_t idleMsg[] = "Dispositivo en REPOSO. Pulse el botón para comenzar a medir\r\n";
static uint8_t measureMsg[] = "Dispositivo en MEDICIÓN. Ingrese por consola para configuración.\r\n Lecturas obtenidas: \r\n";
static uint8_t xDataMsg [] = "Plano x: ";
static uint8_t yDataMsg [] = "Plano y: ";
static uint8_t configMsg[] = "Dispositivo en modo CONFIGURAiÓN.Ingrese:\r\n1- Sensibilidad\r\n2-Nueva referencia\r\n";
static uint8_t sensMsg[] = "Seleccione sensibilidad:\r\n1- Alta\r\n2- Media(Por defecto)\r\n3- Baja\r\n";
static uint8_t refMsg[] = "Deje el dispositivo en la nueva posisión. Cuando la pantalla se ponga verde estará seteado.\r\n";

/* User desired option handler*/
static uint8_t userOption;

/* Variables to set new zero position */
static uint16_t xZero = 0;
static int16_t yZero = 0;

/* Variables to work with inclination measure */
static int16_t xAngle, yAngle;
static int16_t xOffset = 10;
static int16_t yOffset = 10;

/* Delay to getting out of configuration mode, if no command sent. 10 seconds*/
static delay_t configDelay, sensDelay, measureDelay;
static tick_t maxDelay = 10000;
static tick_t measureUpdate = 500;


static void setLowSensibility(){
	xOffset = LO_SENS;
	yOffset = LO_SENS;
}

static void setMedSensibility(){
	xOffset = MED_SENS;
	yOffset = MED_SENS;
}

static void setHighSensibility(){
	xOffset = HI_SENS;
	yOffset = HI_SENS;
}

/* @brief: Inform the actual angle of the X axis
 * @param: None
 * @retval: The actual angle read from mpu9265 accelerometer.
 * This could be a value from -90° to 90°
 * */
static int16_t getXAngle(){
	int16_t retAngle;
	uint16_t xAccel = MPUReadAccelXAxis();
	/* See in which plane is inclined to determine how
	 * to calculate the angle*/
	/* Positive angles */
	if(xAccel > ACCEL_REF){
		retAngle = 90 - (int16_t)((xAccel-CALIB_POS)/173);
	}
	/* Negative angles */
	else{
		retAngle = (int16_t)-xAccel/178;
	}
	return (retAngle);
}

/* @brief: Inform the actual angle of the Y axis
 * @param: None
 * @retval: The actual angle read from mpu9265 accelerometer.
 * This could be a value from -90° to 90°
 * */
static int16_t getYAngle(){
	int16_t retAngle;
	uint16_t yAccel = MPUReadAccelYAxis();
	/* See in which plane is inclined to determine how
	 * to calculate the angle*/
	/* Positive angles */
	if(yAccel > ACCEL_REF){
		retAngle = 90 - (int16_t)((yAccel-CALIB_POS)/173);
	}
	/* Negative angles */
	else{
		retAngle = (int16_t)-yAccel/178;
	}
	return (retAngle);
}

/* @brief: Start digital level FSM in idle state
 * @param: None
 * @retval: None
 * */
void digitalLevInit(){
	/* Initialize all the drivers */
	neopixelInit();
	debounceFSM_init();
	/* Initialize non blocking delays */
	delayInit(&configDelay, maxDelay);
	delayInit(&sensDelay, maxDelay);
	delayInit(&measureDelay, measureUpdate);
	/* Start the device in IDLE mode*/
	actualState = IDLE;
	/* Indicate idle mode */
	ConsolePrintStr(idleMsg);
}

/* @brief: Check and pass through the digital level states.
 * @param: None
 * @retval: None
 * */
void digitalLevUpdate(){
	/* Update button FSM */
	debounceFSM_update();
	/* Check the digital level FSM */
	switch(actualState){
	/***************** IDLE Mode *****************/
	case IDLE:
		/* Reset neopixel matrix*/
		turnAllOff();
		/* Indicate idle mode */
		turnCenterOn(1, 0, 0);
		if (readKey()){
			actualState = MEASURE;
			/* Indicate measure mode */
			ConsolePrintStr(measureMsg);
		}
		break;
	/**************** MEASURE Mode ****************/
	case MEASURE:
		/* If key pressed go to idle mode*/
		if (readKey()){
			actualState = IDLE;
			/* Indicate idle mode */
			ConsolePrintStr(idleMsg);
		}
		/* If get data by console, go to configuration mode*/
		if(ConsoleNewData()){
			actualState = CONFIG;
			ConsolePrintStr(configMsg);
		}
		/* Take some time to update screen values*/
		if(delayRead(&measureDelay)){
			xAngle = getXAngle() - xZero;
			yAngle = getYAngle() - yZero;
			/* Show in console actual degrees read */
			ConsolePrintStr(xDataMsg);
			ConsolePrintDeg(xAngle);
			ConsolePrintStr(yDataMsg);
			ConsolePrintDeg(yAngle);
			/* Show if there is inclination */
			bool moved = false;
			/* Movement's direction determination */
			if(xAngle > xOffset){
				moved = true;
				turnAllOff();
				/* Compound movement: */
				if(yAngle > yOffset){
					turnCornerOn00();
				}
				if (yAngle < -yOffset){
					turnCornerOn03();
				}
				/* X axis only movements */
				if (-yOffset < yAngle && yAngle < yOffset){
					turnColumnOn(0, 1, 0, 0);
				}
			}
			if(xAngle < -xOffset){
				moved = true;
				turnAllOff();
				/* Compound movement: */
				if(yAngle > yOffset){
					turnCornerOn30();
				}
				if (yAngle < -yOffset){
					turnCornerOn33();
				}
				/* X axis only movements */
				if (-yOffset < yAngle && yAngle < yOffset){
					turnColumnOn(3, 1, 0, 0);
				}
			}
			/* Y axis only movements */
			if((!moved) && (yAngle > yOffset)){
				turnAllOff();
				turnRowOn(0, 1, 0, 0);
				moved = true;
			}
			if ((!moved) && (yAngle < -yOffset)){
				turnAllOff();
				turnRowOn(3, 1, 0, 0);
				moved = true;
			}
			/* Indicate correct leveling */
			if (!moved){
				turnAllOff();
				turnCenterOn(0, 1, 0);
			}
		}
		break;
	/**************** CONFIG Mode ****************/
	case CONFIG:
		turnAllOff();
		/* Indicate configuration mode */
		turnCenterOn(0, 0, 1);
		/* Start delay count. If 10 seconds pass, the get out of the configuration mode */
		if(delayRead(&configDelay)){
			actualState = IDLE;
			/* Indicate idle mode */
			ConsolePrintStr(idleMsg);
		}
		/* See if user enters an option */
		if(ConsoleNewData()){
			userOption = ConsoleDataReceive();
			if (userOption == SENS_OP){
				actualState = SENSIBILITY;
				ConsolePrintStr(sensMsg);
			}
			else{
				actualState = REFERENCE;
				ConsolePrintStr(refMsg);
			}
		}
		break;
	/**************** SENSIBILITY Mode ****************/
	case SENSIBILITY:
		/* Start delay count. If 10 seconds pass, the get out of the configuration mode */
		if(delayRead(&sensDelay)){
			actualState = IDLE;
			/* Indicate idle mode */
			ConsolePrintStr(idleMsg);
		}
		if(ConsoleNewData()){
			userOption = ConsoleDataReceive();
			switch(userOption){
			/* High sensibility */
			case HIGH_SENS_OP:
				setHighSensibility();
				break;
				/* Medium sensibility */
			case MED_SENS_OP:
				setMedSensibility();
				break;
				/* Low sensibility */
			case LOW_SENS_OP:
				setLowSensibility();
				break;
			/* Set defensive guard */
			default:
				setMedSensibility();
			}
			/* Return to MEASURE Mode*/
			actualState = MEASURE;
			/* Indicate measure mode */
			ConsolePrintStr(measureMsg);
		}
		break;
	/**************** REFERENCE Mode ****************/
	case REFERENCE:
		xZero = getXAngle();
		yZero = getYAngle();
		/* Return to MEASURE Mode*/
		actualState = MEASURE;
		/* Indicate measure mode */
		ConsolePrintStr(measureMsg);
		break;
	/* Defensive guard if unexpected state detected: go to IDLE mode */
	default:
		actualState = IDLE;
		/* Indicate idle mode */
		ConsolePrintStr(idleMsg);
		break;
	}

}
