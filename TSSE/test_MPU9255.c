/*
############## TP3: Testing unitario para librería MPU9255 ############## 
Se realizaron 5 test unitarios a una librería de un proyecto para 
corroborar el funcionamiento de la misma.
*/

#include "unity.h"
#include "mock_port.h"
#include "mpu9265_SPI.h"

void auxiliar_MPUReadOne(uint8_t *data){
     // Dato MSB
     data[0] = 100;
     //Dato LSB
     data[1] = 28;
}


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

/* 2- Verifiica lectura de acelerómetro en eje X*/
void test_verifica_lectura_aceleracion_eje_x(void){
     uint16_t accel;
     uint8_t *pData;
     SPIRead_fake.custom_fake = auxiliar_MPUReadOne(pData);
     // SPIRead_Expect(*pData);
     accel = MPUReadAccelXAxis();
     
}