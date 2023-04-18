#include "main.h"
#include "mpu9265_SPI.h"

int main(void){

	APISysInit();

	uint8_t data = 0;
	MPUSetAccel2G();
	data = MPUGetAccelResolution();
	MPUSetAccel4G();
	data = MPUGetAccelResolution();
	MPUSetAccel8G();
	data = MPUGetAccelResolution();
	MPUSetAccel16G();
	data = MPUGetAccelResolution();

	uint16_t accel_x, accel_y;

	while (1)
	{
		accel_x = MPUReadAccelXAxis();
		accel_y = MPUReadAccelYAxis();
		HAL_Delay(100);
	}
}

