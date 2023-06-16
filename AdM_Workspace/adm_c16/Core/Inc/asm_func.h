#pragma once

#include <stdint.h>


void asm_svc (void);
uint32_t asm_sum (uint32_t firstOperand, uint32_t secondOperand);

/* Ej 1 */
void asm_zeros(uint32_t * vector, uint32_t longitud);
void asm_zeros16(uint16_t * vector, uint32_t longitud);
/* Ej 2 */
void asm_productoEscalar32(uint32_t *vectorIn, uint32_t *vectorOut, uint32_t longitud, uint32_t escalar);
/* Ej 3 */
void asm_productoEscalar16(uint16_t *vectorIn, uint16_t *vectorOut, uint32_t longitud, uint16_t escalar);
/* Ej 4 */
void asm_productoEscalar12(uint16_t *vectorIn, uint16_t *vectorOut, uint32_t longitud, uint16_t escalar);
/* Ej 5 */
void asm_filtroVentana10(uint16_t *vectorIn, uint16_t *vectorOut, uint32_t longitud);
/* Ej 6*/
void asm_pack32to16(int32_t *vectorIn, int16_t *vectorOut, uint32_t longitud);
/* Ej 7 */
uint32_t asm_max(int32_t *vectorIn, uint32_t longitud);
/* Ej 8 */
void asm_downSampleM(int32_t *vectorIn, int32_t *vectorOut, uint32_t longitud, uint32_t N);
/* Ej 9 */
void asm_invertir(uint16_t *vectorIn, uint32_t longitud);
/* Ej 10 */
void asm_generaEco(int16_t *vectorIn, int16_t *vectorOut, uint32_t longitud, uint32_t msegRetardo);
/* Ej 10 con SIMD */
void asm_generaEcoSIMD(int16_t *vectorIn, int16_t *vectorOut, uint32_t longitud, uint32_t msegRetardo);
/* Ej 11 */
void asm_corr(int16_t *vectorX, int16_t *vectorY, int16_t *vectorCorr, uint32_t longitud);
/* Ej 11 con SIMD */
void asm_corrSIMD(int16_t *vectorX, int16_t *vectorY, int16_t *vectorCorr, uint32_t longitud);
