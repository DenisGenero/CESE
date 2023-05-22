#include "src/mpu9265_SPI.h"
#include "build/test/mocks/mock_port.h"
#include "/var/lib/gems/3.0.0/gems/ceedling-0.31.1/vendor/unity/src/unity.h"












void test_verifica_correcta_conversion_datos(void){

     uint8_t dato_msb = 45;

     uint8_t dato_lsb = 89;



     uint16_t res = converData(dato_msb, dato_lsb);

     UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0x2D59)), (UNITY_INT)(UNITY_INT16)((res)), (

    ((void *)0)

    ), (UNITY_UINT)(23), UNITY_DISPLAY_STYLE_HEX16);

}





void test_verifica_lectura_aceleracion_todos_ejes(void){



     uint8_t bytes = 6;

     uint8_t *pData = &bytes;







     PSIRead_ReturnThruPtr_data();



     MPUReadAccel(pData);

     UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0x06)), (UNITY_INT)(UNITY_INT16)((*pData)), (

    ((void *)0)

    ), (UNITY_UINT)(37), UNITY_DISPLAY_STYLE_HEX16);

}





void test_verifica_lectura_aceleracion_eje_x(void){

     uint16_t accel;

     uint8_t bytes = 2;

     uint8_t *pData = &bytes;



     SPIRead_CMockExpectAndReturn(46, 59, pData, bytes, 0);



     accel = MPUReadAccelXAxis();

     UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0x0200)), (UNITY_INT)(UNITY_INT16)((accel)), (

    ((void *)0)

    ), (UNITY_UINT)(49), UNITY_DISPLAY_STYLE_HEX16);

}





void test_verifica_lectura_resolucion_actual(void){

     uint8_t resolucion;

     uint8_t bytes = 1;

     uint8_t data = 50;

     SPIRead_CMockExpectAndReturn(57, 28, &data, bytes, 0);

     SPIRead_CMockReturnMemThruPtr_data(58, , sizeof(uint8_t));

     resolucion = MPUGetAccelResolution();

     UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0x50)), (UNITY_INT)(UNITY_INT16)((resolucion)), (

    ((void *)0)

    ), (UNITY_UINT)(60), UNITY_DISPLAY_STYLE_HEX16);

}
