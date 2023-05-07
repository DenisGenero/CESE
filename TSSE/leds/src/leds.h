#ifndef LEDS_H
#define LEDS_H

#include <stdint.h>

void ledsInit(uint16_t *direccion);
void ledsTurnOnOne(uint8_t led);
void ledsTurnOffOne(uint8_t led);
void ledsTurnOnAll();
void ledsTurnOffAll();

#endif