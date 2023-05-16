#include "leds.h"

static uint16_t * puerto_virtual;

#define INDEX_OFFSET    1
#define FIRST_BIT       1
#define FIRST_LED       1
#define LAST_LED        16
#define ALL_LEDS_OFF    0x0000
#define ALL_LEDS_ON     0xFFFF

uint16_t indexToMask(uint8_t led){
    return (FIRST_BIT<<(led - INDEX_OFFSET));
}

void ledsInit(uint16_t *direccion){
    puerto_virtual = direccion;
    *puerto_virtual = 0;
};

void ledsTurnOnOne(uint8_t led){
    if(led>=FIRST_LED && led<=LAST_LED){
        *puerto_virtual |= indexToMask(led);
    }
};

void ledsTurnOffOne(uint8_t led){
    if(led>=FIRST_LED && led<=LAST_LED){
        *puerto_virtual &= ~indexToMask(led);
    }
}

void ledsTurnOnAll(){
    *puerto_virtual = ALL_LEDS_ON;
}

void ledsTurnOffAll(){
    *puerto_virtual = ALL_LEDS_OFF;
}