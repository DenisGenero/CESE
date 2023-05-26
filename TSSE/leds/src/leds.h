#ifndef LEDS_H
#define LEDS_H

#include <stdint.h>
#include <stdbool.h>

void ledsInit(uint16_t *direccion);
bool getLedState(uint8_t led);
void ledsTurnOnOne(uint8_t led);
void ledsTurnOffOne(uint8_t led);
void ledsTurnOnAll();
void ledsTurnOffAll();

#endif