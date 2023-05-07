// Al inciarlizar la biblioteca todos los leds quedan apagados.
// Con todos los leds apagados, prendo el led 2, verifico que se el bit 1 vale 1.
// Con el led 2 prendido, apago el led 2, verifico que se enciende el bit 1 vale 0.
// Con todos los leds apagados, prendo el 3, prendo el 5, apago el 3 y apago el 7, deberían quedar el bit 4 en 1 y el resto en 0
// Prendo un led, consulto el estado y tiene que estar prendido.
// Apago un led, consulto el estado y tiene que estar apagado.
// Con todos los leds apagados, prendo todos los leds y verifico que se encienden.
// Con todos los leds prendidor, apagado todos los leds y verifico que se apagan.
// Revisar los valores limites de los argumentos.
// Revisar que pasa con valores erroneos en los argumento.


#include "unity.c"
#include "leds.h"
#include <stdint.h>

static uint16_t puerto_virtual;

// funcion que se ejecuta antes de cada prueba, así no se tiene que llamar en cada test
void setUp(void){
    ledsInit(&puerto_virtual);
}

// Al inicializar la biblioteca todos los leds quedan apagados
void test_todos_los_leds_inician_apagados(void){
    //Aca puerto_virtual es local y pisa a la global a proposito para probar la inicialización
    uint16_t puerto_virtual = 0xFFFF;
    ledsInit(&puerto_virtual);
    //TEST_ASSERT_EQUAL(0x0000, puerto_virtual);
    TEST_ASSERT_EQUAL_HEX16(0x0000, puerto_virtual);
}

// Con todos los leds apagados, prendo el led 2, verifico que se el bit 1 vale 1.
void test_prender_un_led(void){
    ledsTurnOnOne(2);
    TEST_ASSERT_EQUAL_HEX16(0x0002, puerto_virtual);
}

// Con el led 2 prendido, apago el led 2, verifico que se enciende el bit 1 vale 0.
void test_prender_y_apagar_un_led(void){
    ledsTurnOnOne(2);
    ledsTurnOffOne(2);
    TEST_ASSERT_EQUAL_HEX16(0x0000, puerto_virtual);
}

// Con todos los leds apagados, prendo el 3, prendo el 5, apago el 3 y apago el 7, deberían quedar el bit 4 en 1 y el resto en 0
void test_prender_y_apagar_varios_leds(void){
    ledsTurnOnOne(3);
    ledsTurnOnOne(5);
    ledsTurnOffOne(3);
    ledsTurnOffOne(7);
    //Debería quedar solo el bit 4 en 1
    TEST_ASSERT_EQUAL_HEX16(0x0010, puerto_virtual);
}