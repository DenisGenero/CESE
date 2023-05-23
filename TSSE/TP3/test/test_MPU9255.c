/*
############## TP3: Testing unitario para librería MPU9255 ############## 
Se realizaron 5 test unitarios a una librería de un proyecto para 
corroborar el funcionamiento de la misma.
*/

#include "unity.h"
#include "mock_port.h"
#include "mpu9265_SPI.h"

#define ACCEL_DIR   59
#define ACCEL_RES   28
#define TEMP_DIR    65

/* 1- Test static uint16_t converData(uint8_t msbData, uint8_t lsbData)
Es una función privada de la libreria que sirve para obtener
un dato uint16_t a partir de dos datos uint8_t recibidos por SPI
*/
void test_verifica_correcta_conversion_datos(void){
     uint8_t dato_msb = 45;  // 45 = 0010 1101 (<<8)
     uint8_t dato_lsb = 89;  // 89 = 0101 1001
     // res = 0101 1001 0010 1101 = 0x2D59
     uint16_t res = converData(dato_msb, dato_lsb);
     TEST_ASSERT_EQUAL_HEX16(0x2D59, res);
}

/* 2- Verifiica lectura de acelerómetro en todos los ejes*/
void test_verifica_lectura_aceleracion_todos_ejes(void){
     // Cantidad de bytes de datos (2 por eje)
     uint8_t bytes = 6;
     uint8_t *pData = &bytes;
     // Función Mock que será llamada
     SPIRead_ExpectAndReturn(ACCEL_DIR, pData, bytes, 0);
     SPIRead_IgnoreArg_data();
     SPIRead_ReturnThruPtr_data(&bytes);
     // SPIRead_ReturnMemThruPtr_data(&bytes, 6);
     // Lectura del puntero pasado por parámetro
     MPUReadAccel(pData);
     TEST_ASSERT_EQUAL_HEX16(0x0006, *pData);
}

/* 3- Verifiica lectura de acelerómetro en eje X*/
void test_verifica_lectura_aceleracion_eje_x(void){
     uint16_t accel;
     uint8_t bytes = 2;
     uint8_t *pData = &bytes;
     // Función Mock que será llamada
     SPIRead_ExpectAndReturn(ACCEL_DIR, pData, bytes, 0);
     SPIRead_IgnoreArg_data();
     SPIRead_ReturnThruPtr_data(&bytes);
     // Aceleración obtenida
     accel = MPUReadAccelXAxis();
     TEST_ASSERT_EQUAL_HEX16(0x0200, accel);
}

/*4- Verificar lectura de resolución actual*/
void test_verifica_lectura_resolucion_actual(void){
     uint8_t resolucion;
     uint8_t bytes = 1;
     uint8_t *pData;

     SPIRead_ExpectAndReturn(ACCEL_RES, pData, bytes, 0);
     SPIRead_IgnoreArg_data();
     SPIRead_ReturnThruPtr_data(&bytes);
     resolucion = MPUGetAccelResolution();
     TEST_ASSERT_EQUAL_HEX16(0x001, resolucion);
}

/* 5- Verifiica lectura de temperatura*/
void test_verifica_lectura_temperatura(void){
     uint16_t temp;
     uint8_t bytes = 2;
     uint8_t *pData = &bytes;
     // Función Mock que será llamada
     SPIRead_ExpectAndReturn(TEMP_DIR, pData, bytes, 0);
     SPIRead_IgnoreArg_data();
     SPIRead_ReturnThruPtr_data(&bytes);
     // Aceleración obtenida
     temp = MPUReadTemperature();
     TEST_ASSERT_EQUAL_HEX16(0x0200, temp);
}