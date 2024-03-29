#include "main.h"
#include "mpu9265_SPI.h"

#define ACCEL_REF 32768
#define CALIB_POS	50000

uint8_t shiftBits = 1;
uint8_t accelRes = 2;

int16_t getXAngle(){
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

int16_t getYAngle(){
	int16_t retAngle;
	uint16_t yAccel = MPUReadAccelYAxis();
	/* See in which plane is inclined to determine how
	 * to calculate the angle*/
	/* Positive angles */
	if(yAccel > ACCEL_REF){
		retAngle = 90 - (int16_t)((yAccel-ACCEL_REF)/364);
	}
	/* Negative angles */
	else{
		retAngle = (int16_t)-yAccel/364;
	}
	return (retAngle);
}

int main(void){

	APISysInit();

//	uint8_t data = 0;
//	MPUSetAccel2G();
//	data = MPUGetAccelResolution();
//	MPUSetAccel4G();
//	data = MPUGetAccelResolution();
//	MPUSetAccel8G();
//	data = MPUGetAccelResolution();
//	MPUSetAccel16G();
//	data = MPUGetAccelResolution();

	uint32_t x_acum, y_acum;
	int16_t accel_y, accel_x;

	while (1)
	{
		x_acum = MPUReadAccelXAxis();
		y_acum = MPUReadAccelYAxis();
//		accel_x = (x_acum<<4);
		accel_x = getXAngle();
		accel_y = getYAngle();
		HAL_Delay(100);
	}
}


