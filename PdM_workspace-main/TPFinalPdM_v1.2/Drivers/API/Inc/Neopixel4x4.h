/*
 * Library made by Genero, Denis J.
 * Last revision: 15/04/2023
 *
 * Description:
 * The purpose of this file is to give easy to use functions to interface
 * a Neopixel 4x4 matrix containing a total of 16 WS2812B intelligent led.
 * */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __NEOPIXEL4x4_H
#define __NEOPIXEL4x4_H

#include "port.h"

/* Neopixel user functions */
void neopixelInit();
void loadLedColor(uint8_t row, uint8_t col, uint8_t red, uint8_t green, uint8_t blue);
void turnLedOn(uint8_t row, uint8_t col, uint8_t red, uint8_t green, uint8_t blue);
void turnLedOff(uint8_t row, uint8_t col);
void turnColumnOn(uint8_t col, uint8_t red, uint8_t green, uint8_t blue);
void turnColumnOff(uint8_t col);
void turnRowOn(uint8_t row, uint8_t red, uint8_t green, uint8_t blue);
void turnRowOff(uint8_t row);
void turnCenterOn(uint8_t red, uint8_t green, uint8_t blue);
void turnCornerOn00();
void turnCornerOn03();
void turnCornerOn30();
void turnCornerOn33();
void turnAllOff();

/* Function to set pwm data to DMA */
void turnSecuenceOn();
/* Hal's functions wrappers*/
void fillSendBuffer();
void setPWMData(uint32_t *Data, uint16_t size);

#endif /* __NEOPIXEL4x4_H */
