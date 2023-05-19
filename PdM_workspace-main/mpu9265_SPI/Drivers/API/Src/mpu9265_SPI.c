/*
 * mpu9265_SPI.c
 *
 *  Created on: 16 abr. 2023
 *      Author: denis
 */
#include "mpu9265_SPI.h"

/* mpu9265 register's directions macros */
#define GYRO_RESOLUTION		27	// Register 27 (8 bits):
#define GYRO_250_RES		0	// 0bx00000000
#define GYRO_500_RES		8	// 0bx00001000
#define GYRO_1000_RES		16	// 0bx00010000
#define GYRO_2000_RES		24	// 0bx00011000

#define ACCEL_RESOLUTION 	28	// Register 28 (8 bits):
#define ACCEL_2G_RES		0	// 0bx00000000
#define ACCEL_4G_RES		8	// 0bx00001000
#define ACCEL_8G_RES		16	// 0bx00010000
#define ACCEL_16G_RES		24	// 0bx00011000

#define ACCEL_DATA			59
#define ACCEL_XAXIS			59
#define ACCEL_YAXIS			61
#define ACCEL_ZAXIS			63

#define TEMPERATURE			65

#define GYRO_DATA			67
#define GYRO_XAXIS			67
#define GYRO_YAXIS			69
#define GYRO_ZAXIS			71


/* ################# Private functions ################# */

/* @brief: SPI peripheral wrapper. Obtain information from the specified MPU register
 * @params:
 * 			- reg: MPU register
 * 			- data: pointer to the received data
 * 			- bytes: amount of data to transmit
 * @retval: None
 * */
static void MPURead(uint8_t reg, uint8_t *data, uint8_t bytes){
	SPIRead(reg, data, bytes);
}

/* @brief: SPI peripheral wrapper. Send data to the specified MPU register
 * @params:
 * 			- reg: MPU register
 * 			- command: data to be written in the MPU register
 * @retval: None
 * */
static void MPUWrite(uint8_t reg, uint8_t command){
	SPIWrite(reg, command);
}

/* @brief: Transform 2 uint8_t data in one uint16_t value
 * @params:
 * 			- msbData: MSB portion of the data
 * 			- lsbData: MSB portion of the data
 * @retval: new value in the uint16_t format
 * */
static uint16_t convertData(uint8_t msbData, uint8_t lsbData){
	uint16_t result = msbData<<8 | lsbData;
	return (result);
}

/* @brief: Write in the accelerometer calibration register of the MPU
 * @param: the desired resolution. Can be +/-2, 4, 8 or 16 G for the full
 * range of the sensor output
 * @retval: None
 * */
static void MPUAccelCalibration(uint8_t resolution){
	MPUWrite(ACCEL_RESOLUTION, resolution);
}

/* @brief: Write in the gyroscope calibration register of the MPU
 * @param: the desired resolution. Can be 250, 500, 1000 or 2000 dps for the full
 * range of the sensor output (dps stands for degrees per second).
 * @retval: None
 * */
static void MPUGyroCalibration(uint8_t resolution){
	MPUWrite(GYRO_RESOLUTION, resolution);
}

/* ################# Public functions ################# */
/* Accelerometer functions */

/* @brief: Get all the accelerometer data. Take in count that data pointer
 * will store 6 bytes of information, two for each axis.
 * @param: data pointer to store MPU reading
 * @retval: None
 * */
void MPUReadAccel(uint8_t *data){
	/* Accelerometer gives 6 bytes of data:
	 * two bytes for each axis */
	uint8_t byteCount = 6;
	MPURead(ACCEL_DATA, data, byteCount);
}

/* @brief: Get the x axis accelerometer data
 * @param: None
 * @retval: x axis acceleration read
 * */
uint16_t MPUReadAccelXAxis(){
	uint8_t byteCount = 2;
	uint8_t *data = &byteCount;
	MPURead(ACCEL_XAXIS, data, byteCount);
	uint16_t result = convertData(data[0], data[1]);
	return(result);
}

/* @brief: Get the y axis accelerometer data
 * @param: None
 * @retval: y axis acceleration read
 * */
uint16_t MPUReadAccelYAxis(){
	uint8_t byteCount = 2;
	uint8_t *data = &byteCount;
	MPURead(ACCEL_YAXIS, data, byteCount);
	uint16_t result = convertData(data[0], data[1]);
	return(result);
}

/* @brief: Get the z axis accelerometer data
 * @param: None
 * @retval: z axis acceleration read
 * */
uint16_t MPUReadAccelZAxis(){
	uint8_t byteCount = 2;
	uint8_t *data = &byteCount;
	MPURead(ACCEL_YAXIS, data, byteCount);
	uint16_t result = convertData(data[0], data[1]);
	return(result);
}

/* @brief: Configure the MPU accelerometer to work with 2g of resolution.
 * @param: None
 * @retval: None
 * */
void MPUSetAccel2G(){
	MPUAccelCalibration(ACCEL_2G_RES);
}

/* @brief: Configure the MPU accelerometer to work with 4g of resolution.
 * @param: None
 * @retval: None
 * */
void MPUSetAccel4G(){
	MPUAccelCalibration(ACCEL_4G_RES);
}

/* @brief: Configure the MPU accelerometer to work with 8g of resolution.
 * @param: None
 * @retval: None
 * */
void MPUSetAccel8G(){
	MPUAccelCalibration(ACCEL_8G_RES);
}

/* @brief: Configure the MPU accelerometer to work with 16g of resolution.
 * @param: None
 * @retval: None
 * */
void MPUSetAccel16G(){
	MPUAccelCalibration(ACCEL_16G_RES);
}

/* @brief: Get the actual resolution of the accelerometer
 * @param: None
 * @retval: One of the macros defined above
 * */
uint8_t MPUGetAccelResolution(){
	uint8_t data;
	MPURead(ACCEL_RESOLUTION, &data, 1);
	return(data);
}

/* Temperature sensor */
/* @brief: Get the actual temperature that the MPU is sensing
 * @param: None
 * @retval: Temperature read
 * */
uint16_t MPUReadTemperature(){
	uint8_t byteCount = 2;
	uint8_t *data = &byteCount;
	MPURead(TEMPERATURE, data, byteCount);
	uint16_t result = convertData(data[0], data[1]);
	return(result);
}

/* Gyroscope functions */

/* @brief: Get all the gyroscope data. Take in count that data pointer
 * will store 6 bytes of information, two for each axis.
 * @param: data pointer to store MPU reading
 * @retval: None
 * */
void MPUReadGyro(uint8_t *data){
	/* Gyroscope gives 6 bytes of data:
	 * two bytes for each axis */
	uint8_t byteCount = 6;
	MPURead(GYRO_DATA, data, byteCount);
}

/* @brief: Get the x axis gyroscope data
 * @param: None
 * @retval: x axis gyroscope read
 * */
uint16_t MPUReadGyroXAxis(){
	uint8_t byteCount = 2;
	uint8_t *data = &byteCount;
	MPURead(GYRO_XAXIS, data, byteCount);
	uint16_t result = convertData(data[0], data[1]);
	return(result);
}

/* @brief: Get the y axis gyroscope data
 * @param: None
 * @retval: y axis gyroscope read
 * */
uint16_t MPUReadGyroYAxis(){
	uint8_t byteCount = 2;
	uint8_t *data = &byteCount;
	MPURead(GYRO_YAXIS, data, byteCount);
	uint16_t result = convertData(data[0], data[1]);
	return(result);
}

/* @brief: Get the z axis gyroscope data
 * @param: None
 * @retval: z axis gyroscope read
 * */
uint16_t MPUReadGyroZAxis(){
	uint8_t byteCount = 2;
	uint8_t *data = &byteCount;
	MPURead(GYRO_ZAXIS, data, byteCount);
	uint16_t result = convertData(data[0], data[1]);
	return(result);
}

/* @brief: Configure the MPU gyroscope to work with 250dps of resolution.
 * @param: None
 * @retval: None
 * */
void MPUSetGyro250(){
	MPUGyroCalibration(GYRO_250_RES);
}

/* @brief: Configure the MPU gyroscope to work with 500dps of resolution.
 * @param: None
 * @retval: None
 * */
void MPUSetGyro500(){
	MPUGyroCalibration(GYRO_500_RES);
}

/* @brief: Configure the MPU gyroscope to work with 1000dps of resolution.
 * @param: None
 * @retval: None
 * */
void MPUSetGyro1000(){
	MPUGyroCalibration(GYRO_1000_RES);
}

/* @brief: Configure the MPU gyroscope to work with 2000dps of resolution.
 * @param: None
 * @retval: None
 * */
void MPUSetGyro2000(){
	MPUGyroCalibration(GYRO_2000_RES);
}

/* @brief: Get the actual resolution of the gyroscope
 * @param: None
 * @retval: One of the macros defined above
 * */
uint8_t MPUGetGyroResolution(){
	uint8_t data;
	MPURead(GYRO_RESOLUTION, &data, 1);
	return(data);
}
