#include "/var/lib/gems/3.0.0/gems/ceedling-0.31.1/vendor/unity/src/unity.c"
#include "src/leds.h"




static uint16_t puerto_virtual;





void setUp(void){

    ledsInit(&puerto_virtual);

}





void test_todos_los_leds_inician_apagados(void){



    uint16_t puerto_virtual = 0xFFFF;

    ledsInit(&puerto_virtual);



    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0x0000)), (UNITY_INT)(UNITY_INT16)((puerto_virtual)), (

   ((void *)0)

   ), (UNITY_UINT)(30), UNITY_DISPLAY_STYLE_HEX16);

}





void test_prender_un_led(void){

    ledsTurnOnOne(2);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0x0002)), (UNITY_INT)(UNITY_INT16)((puerto_virtual)), (

   ((void *)0)

   ), (UNITY_UINT)(36), UNITY_DISPLAY_STYLE_HEX16);

}





void test_prender_y_apagar_un_led(void){

    ledsTurnOnOne(2);

    ledsTurnOffOne(2);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0x0000)), (UNITY_INT)(UNITY_INT16)((puerto_virtual)), (

   ((void *)0)

   ), (UNITY_UINT)(43), UNITY_DISPLAY_STYLE_HEX16);

}





void test_prender_y_apagar_varios_leds(void){

    ledsTurnOnOne(3);

    ledsTurnOnOne(5);

    ledsTurnOffOne(3);

    ledsTurnOffOne(7);



    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0x0010)), (UNITY_INT)(UNITY_INT16)((puerto_virtual)), (

   ((void *)0)

   ), (UNITY_UINT)(53), UNITY_DISPLAY_STYLE_HEX16);

}
