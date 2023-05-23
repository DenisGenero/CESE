#include "src/mpu9265_SPI.h"
#include "build/test/mocks/mock_port.h"
#include "/var/lib/gems/3.0.0/gems/ceedling-0.31.1/vendor/unity/src/unity.h"












void test_verifica_correcta_conversion_datos(void){

     uint8_t dato_msb = 45;

     uint8_t dato_lsb = 89;



     uint16_t res = converData(dato_msb, dato_lsb);

     UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0x2D59)), (UNITY_INT)(UNITY_INT16)((res)), (

    ((void *)0)

    ), (UNITY_UINT)(24), UNITY_DISPLAY_STYLE_HEX16);

}





void test_verifica_lectura_aceleracion_todos_ejes(void){



     uint8_t bytes = 6;

     uint8_t *pData = &bytes;



     SPIRead_CMockExpectAndReturn(33, 59, pData, bytes, 0);

     SPIRead_CMockIgnoreArg_data(34);

     SPIRead_CMockReturnMemThruPtr_data(35, &bytes, sizeof(uint8_t));





     MPUReadAccel(pData);

     UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0x0006)), (UNITY_INT)(UNITY_INT16)((*pData)), (

    ((void *)0)

    ), (UNITY_UINT)(39), UNITY_DISPLAY_STYLE_HEX16);

}





void test_verifica_lectura_aceleracion_eje_x(void){

     uint16_t accel;

     uint8_t bytes = 2;

     uint8_t *pData = &bytes;



     SPIRead_CMockExpectAndReturn(48, 59, pData, bytes, 0);

     SPIRead_CMockIgnoreArg_data(49);

     SPIRead_CMockReturnMemThruPtr_data(50, &bytes, sizeof(uint8_t));



     accel = MPUReadAccelXAxis();

     UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0x0200)), (UNITY_INT)(UNITY_INT16)((accel)), (

    ((void *)0)

    ), (UNITY_UINT)(53), UNITY_DISPLAY_STYLE_HEX16);

}





void test_verifica_lectura_resolucion_actual(void){

     uint8_t resolucion;

     uint8_t bytes = 1;

     uint8_t *pData;



     SPIRead_CMockExpectAndReturn(62, 28, pData, bytes, 0);

     SPIRead_CMockIgnoreArg_data(63);

     SPIRead_CMockReturnMemThruPtr_data(64, &bytes, sizeof(uint8_t));

     resolucion = MPUGetAccelResolution();

     UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0x001)), (UNITY_INT)(UNITY_INT16)((resolucion)), (

    ((void *)0)

    ), (UNITY_UINT)(66), UNITY_DISPLAY_STYLE_HEX16);

}





void test_verifica_lectura_temperatura(void){

     uint16_t temp;

     uint8_t bytes = 2;

     uint8_t *pData = &bytes;



     SPIRead_CMockExpectAndReturn(75, 65, pData, bytes, 0);

     SPIRead_CMockIgnoreArg_data(76);

     SPIRead_CMockReturnMemThruPtr_data(77, &bytes, sizeof(uint8_t));



     temp = MPUReadTemperature();

     UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0x0200)), (UNITY_INT)(UNITY_INT16)((temp)), (

    ((void *)0)

    ), (UNITY_UINT)(80), UNITY_DISPLAY_STYLE_HEX16);

}
