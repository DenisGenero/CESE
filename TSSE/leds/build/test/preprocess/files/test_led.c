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





void test_prendo_led_y_consulto_estado(void){

    ledsTurnOnOne(9);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0x100)), (UNITY_INT)(UNITY_INT16)((puerto_virtual)), (

   ((void *)0)

   ), (UNITY_UINT)(59), UNITY_DISPLAY_STYLE_HEX16);

}





void test_apago_led_y_consulto_estado(void){

    ledsTurnOffOne(13);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0x000)), (UNITY_INT)(UNITY_INT16)((puerto_virtual)), (

   ((void *)0)

   ), (UNITY_UINT)(65), UNITY_DISPLAY_STYLE_HEX16);

}





void test_prendo_todos_y_verifico_todos_prendidos(void){

    ledsTurnOnAll();

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0xFFFF)), (UNITY_INT)(UNITY_INT16)((puerto_virtual)), (

   ((void *)0)

   ), (UNITY_UINT)(71), UNITY_DISPLAY_STYLE_HEX16);

}







void test_prendo_todo_apago_uno_verifico_estado(void){

    ledsTurnOnAll();

    ledsTurnOffOne(14);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0xDFFF)), (UNITY_INT)(UNITY_INT16)((puerto_virtual)), (

   ((void *)0)

   ), (UNITY_UINT)(79), UNITY_DISPLAY_STYLE_HEX16);

}





void test_prendo_todo_apago_todo_verifico_estado(void){

    ledsTurnOnAll();

    ledsTurnOffAll();

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0x0000)), (UNITY_INT)(UNITY_INT16)((puerto_virtual)), (

   ((void *)0)

   ), (UNITY_UINT)(86), UNITY_DISPLAY_STYLE_HEX16);

}







void test_prendido_limite_inferior(void){

    ledsTurnOnOne(1);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0x0001)), (UNITY_INT)(UNITY_INT16)((puerto_virtual)), (

   ((void *)0)

   ), (UNITY_UINT)(93), UNITY_DISPLAY_STYLE_HEX16);

}



void test_apagado_limite_inferior(void){

    ledsTurnOffOne(1);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0x0000)), (UNITY_INT)(UNITY_INT16)((puerto_virtual)), (

   ((void *)0)

   ), (UNITY_UINT)(98), UNITY_DISPLAY_STYLE_HEX16);

}



void test_prendido_limite_superior(void){

    ledsTurnOnOne(16);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0x8000)), (UNITY_INT)(UNITY_INT16)((puerto_virtual)), (

   ((void *)0)

   ), (UNITY_UINT)(103), UNITY_DISPLAY_STYLE_HEX16);

}



void test_apagado_limite_superior(void){

    ledsTurnOffOne(16);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0x0000)), (UNITY_INT)(UNITY_INT16)((puerto_virtual)), (

   ((void *)0)

   ), (UNITY_UINT)(108), UNITY_DISPLAY_STYLE_HEX16);

}









void test_revisar_argumentos_erroneos_prender(void){



    ledsTurnOnOne(12);



    ledsTurnOnOne(20);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0x0800)), (UNITY_INT)(UNITY_INT16)((puerto_virtual)), (

   ((void *)0)

   ), (UNITY_UINT)(119), UNITY_DISPLAY_STYLE_HEX16);

}







void test_revisar_argumentos_erroneos_apagar(void){



    ledsTurnOnOne(6);



    ledsTurnOffOne(-6);

    UnityAssertEqualNumber((UNITY_INT)(UNITY_INT16)((0x0020)), (UNITY_INT)(UNITY_INT16)((puerto_virtual)), (

   ((void *)0)

   ), (UNITY_UINT)(129), UNITY_DISPLAY_STYLE_HEX16);

}
