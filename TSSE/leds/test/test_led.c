// 1- Al inciarlizar la biblioteca todos los leds quedan apagados.
// 2- Con todos los leds apagados, prendo el led 2, verifico que se el bit 1 vale 1.
// 3- Con el led 2 prendido, apago el led 2, verifico que se enciende el bit 1 vale 0.
// 4- Con todos los leds apagados, prendo el 3, prendo el 5, apago el 3 y apago el 7, deberían quedar el bit 4 en 1 y el resto en 0
// 5- Prendo un led, consulto el estado y tiene que estar prendido.
// 6- Apago un led, consulto el estado y tiene que estar apagado.
// 7- Con todos los leds apagados, prendo todos los leds y verifico que se encienden.
// 8- Con todos los leds prendidos, apagado todos los leds y verifico que se apagan.
// 9- Revisar los valores limites de los argumentos.
// 10- Revisar que pasa con valores erroneos en los argumento.


#include "unity.c"
#include "leds.h"
#include <stdint.h>

static uint16_t puerto_virtual;

// funcion que se ejecuta antes de cada prueba, así no se tiene que llamar en cada test
void setUp(void){
    ledsInit(&puerto_virtual);
}

// 1- Al inicializar la biblioteca todos los leds quedan apagados
void test_todos_los_leds_inician_apagados(void){
    //Aca puerto_virtual es local y pisa a la global a proposito para probar la inicialización
    uint16_t puerto_virtual = 0xFFFF;
    ledsInit(&puerto_virtual);
    //TEST_ASSERT_EQUAL(0x0000, puerto_virtual);
    TEST_ASSERT_EQUAL_HEX16(0x0000, puerto_virtual);
}

// 2- Con todos los leds apagados, prendo el led 2, verifico que se el bit 1 vale 1.
void test_prender_un_led(void){
    ledsTurnOnOne(2);
    TEST_ASSERT_EQUAL_HEX16(0x0002, puerto_virtual);
}

// 3- Con el led 2 prendido, apago el led 2, verifico que se enciende el bit 1 vale 0.
void test_prender_y_apagar_un_led(void){
    ledsTurnOnOne(2);
    ledsTurnOffOne(2);
    TEST_ASSERT_EQUAL_HEX16(0x0000, puerto_virtual);
}

// 4- Con todos los leds apagados, prendo el 3, prendo el 5, apago el 3 y apago el 7, deberían quedar el bit 4 en 1 y el resto en 0
void test_prender_y_apagar_varios_leds(void){
    ledsTurnOnOne(3);
    ledsTurnOnOne(5);
    ledsTurnOffOne(3);
    ledsTurnOffOne(7);
    //Debería quedar solo el bit 4 en 1
    TEST_ASSERT_EQUAL_HEX16(0x0010, puerto_virtual);
}

// 5- Prendo un led, consulto el estado y tiene que estar prendido.
void test_prendo_led_y_consulto_estado(void){
    ledsTurnOnOne(9);
    TEST_ASSERT_EQUAL_HEX16(0x100, puerto_virtual); // 0x100 = 0000 0000 1000 0000 (bit 8 --> led 9)
    // Consulto el estado --> deber ser true
    TEST_ASSERT_TRUE(getLedState(9));
}

// 6- Apago un led, consulto el estado y tiene que estar apagado.
void test_apago_led_y_consulto_estado(void){
    ledsTurnOffOne(13);
    TEST_ASSERT_EQUAL_HEX16(0x000, puerto_virtual);
    // Consulto el estado --> debe ser false
    TEST_ASSERT_FALSE(getLedState(13));
}

// 7- Con todos los leds apagados, prendo todos los leds y verifico que se encienden.
void test_prendo_todos_y_verifico_todos_prendidos(void){
    ledsTurnOnAll();
    TEST_ASSERT_EQUAL_HEX16(0xFFFF, puerto_virtual);
}

/******************* Test agregado por mi *******************/ 
// Prendo todos los leds, apago uno y consulto si se apago solamente ese
void test_prendo_todo_apago_uno_verifico_estado(void){
    ledsTurnOnAll();
    ledsTurnOffOne(14);
    TEST_ASSERT_EQUAL_HEX16(0xDFFF, puerto_virtual); // 0xDFFF = 1101 1111 1111 1111 (bit 13 --> led 14)
}

// 8- Con todos los leds prendidos, apagado todos los leds y verifico que se apagan.
void test_prendo_todo_apago_todo_verifico_estado(void){
    ledsTurnOnAll();
    ledsTurnOffAll();
    TEST_ASSERT_EQUAL_HEX16(0x0000, puerto_virtual);
}

// 9- Revisar los valores limites de los argumentos.
// 9a- limite inferior: prendido
void test_prendido_limite_inferior(void){
    ledsTurnOnOne(1);
    TEST_ASSERT_EQUAL_HEX16(0x0001, puerto_virtual);
}
// 9b- limite inferior: apagado
void test_apagado_limite_inferior(void){
    ledsTurnOffOne(1);
    TEST_ASSERT_EQUAL_HEX16(0x0000, puerto_virtual);
}
// 9c- limite superior: prendido
void test_prendido_limite_superior(void){
    ledsTurnOnOne(16);
    TEST_ASSERT_EQUAL_HEX16(0x8000, puerto_virtual); // 0x8000 = 1000 0000 0000 0000 (bit 15 --> led 16)
}
// 9d- limite superior: apagado
void test_apagado_limite_superior(void){
    ledsTurnOffOne(16);
    TEST_ASSERT_EQUAL_HEX16(0x0000, puerto_virtual);
}

// 10- Revisar que pasa con valores erroneos en los argumento.
// 10a- Función para prender un led: Si se pasa un valor erroneo
// se debe dejar al puerto como estaba
void test_revisar_argumentos_erroneos_prender(void){
    // Prender un led conocido
    ledsTurnOnOne(12);
    // Colocar argumento erroneo
    ledsTurnOnOne(20);
    TEST_ASSERT_EQUAL_HEX16(0x0800, puerto_virtual); // 0x0800 = 0000 1000 0000 0000 (bit 11 --> led 12)
}

// 10b- Función para apagar un led: Si se pasa un valor erroneo
// se debe dejar al puerto como estaba
void test_revisar_argumentos_erroneos_apagar(void){
    // Prender un led conocido
    ledsTurnOnOne(6);
    // Colocar argumento erroneo
    ledsTurnOffOne(-6);
    TEST_ASSERT_EQUAL_HEX16(0x0020, puerto_virtual); // 0x0020 = 0000 0000 0010 0000 (bit 5 --> led 6)
}

