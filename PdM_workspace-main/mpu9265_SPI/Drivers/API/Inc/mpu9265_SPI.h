/*
 * mpu9265_SPI.h
 *
 *  Created on: 16 abr. 2023
 *      Author: denis
 */

#ifndef API_MPU9265_SPI_H_
#define API_MPU9265_SPI_H_

#include <stdint.h>

/* Accelerometer functions */
void MPUReadAccel(uint8_t *data);
uint16_t MPUReadAccelXAxis();
uint16_t MPUReadAccelYAxis();
uint16_t MPUReadAccelZAxis();
void MPUSetAccel2G();
void MPUSetAccel4G();
void MPUSetAccel8G();
void MPUSetAccel16G();
uint8_t MPUGetAccelResolution();

/* Temperature sensor */
uint16_t MPUReadTemperature();

/* Gyroscope functions */
void MPUReadGyro(uint8_t *data);
uint16_t MPUReadGyroXAxis();
uint16_t MPUReadGyroYAxis();
uint16_t MPUReadGyroZAxis();
void MPUSetGyro250();
void MPUSetGyro500();
void MPUSetGyro1000();
void MPUSetGyro2000();
uint8_t MPUGetGyroResolution();

/* Wrappers */
void SPIRead(uint8_t reg, uint8_t *data, uint8_t length);
void SPIWrite(uint8_t reg, uint8_t command);

/* Peripherals functions */
void APISysInit();
void SystemClock_Config(void);
void MX_GPIO_Init(void);
void MX_SPI1_Init(void);

#endif /* API_MPU9265_SPI_H_ */
