#include "leds.h"

static uint16_t * puerto_virtual;

#define INDEX_OFFSET    1
#define FIRST_BIT       1
#define ALL_LEDS_OFF    0x0000
uint16_t indexToMask(uint8_t led){
    return (FIRST_BIT<<(led - INDEX_OFFSET));
}

void ledsInit(uint16_t *direccion){
    puerto_virtual = direccion;
    *puerto_virtual = 0;
};

void ledsTurnOnOne(uint8_t led){
    *puerto_virtual |= indexToMask(led);
};

void ledsTurnOffOne(uint8_t led){
    *puerto_virtual &= ~indexToMask(led);
}