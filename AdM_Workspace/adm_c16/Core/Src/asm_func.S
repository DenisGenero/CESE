.syntax unified
.thumb
.text

@ Simbolos exportados
.global asm_svc
.global asm_sum
.global asm_zeros
.global asm_zeros16
.global asm_productoEscalar32
.global asm_productoEscalar16
.global asm_productoEscalar12

@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ Prototipo en "C":
@   void asm_svc (void)
@
.thumb_func
    asm_svc:
        svc 0
        bx lr


@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ Prototipo en "C":
@   uint32_t asmSum (uint32_t firstOperand, uint32_t secondOperand)
@
@ Parametros recibidos:
@   r0: firstOperand
@   r1: secondOperand
@
@ Valor de retorno:
@   r0: resultado de la suma de firstOperand y secondOperand
@
.thumb_func
    asm_sum:
        add r0, r1  @ r0 = r0 + r1
        bx lr       @ vuelve adonde fue llamada (especificamente, si "pc"
                    @ es la direccion, en el codigo del programa, de la
                    @ instruccion "bl asm_sum" usada para saltar a
                    @ esta funcion, entonces "lr" contiene ese "pc" + 4).
                    @ el valor de retorno debe quedar en el registro r0.
                    @ En este caso, r0 es el resultado de r0 + r1.

        @ Otras alternativas para el retorno
        @ mov pc,lr
        @ bx lr
        @ push {lr} ... pop {pc}

@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ Prototipo en "C":
@   void asm_zeros(uint32_t * vector, uint32_t longitud)
@
@ Parametros recibidos:
@   r0: dirección del vector
@   r1: longitud
@
@ Valor de retorno: Nada
@
.thumb_func
    asm_zeros:
    	mov r2, 0
    	str r2, [r0] // *r0 = 0
    	subs r1, 1	// r1 = r1 - 1
    _for:
        str r2, [r0, 4]! // *(r0 + 4 bytes) = 0
        subs r1, 1	// r1 = r1 - 1
        bne _for		// seguir en el ciclo for
        bx lr       @ vuelve adonde fue llamada (especificamente, si "pc"
                    @ es la direccion, en el codigo del programa, de la
                    @ instruccion "bl asm_sum" usada para saltar a
                    @ esta funcion, entonces "lr" contiene ese "pc" + 4).
                    @ el valor de retorno debe quedar en el registro r0.
                    @ En este caso, r0 es el resultado de r0 + r1.

        @ Otras alternativas para el retorno
        @ mov pc,lr
        @ bx lr
        @ push {lr} ... pop {pc}


@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ Prototipo en "C":
@   void asm_zeros(uint32_t * vector, uint32_t longitud)
@
@ Parametros recibidos:
@   r0: dirección del vector
@   r1: longitud
@
@ Valor de retorno: Nada
@
.thumb_func
    asm_zeros16:
    	mov r2, 0
    	strh r2, [r0] // *r0 = 0
    	subs r1, 1	// r1 = r1 - 1
    _for4:
        strh r2, [r0, 2]! // *(r0 + 4 bytes) = 0
        subs r1, 1	// r1 = r1 - 1
        bne _for4		// seguir en el ciclo for
        bx lr       @ vuelve adonde fue llamada (especificamente, si "pc"
                    @ es la direccion, en el codigo del programa, de la
                    @ instruccion "bl asm_sum" usada para saltar a
                    @ esta funcion, entonces "lr" contiene ese "pc" + 4).
                    @ el valor de retorno debe quedar en el registro r0.
                    @ En este caso, r0 es el resultado de r0 + r1.

        @ Otras alternativas para el retorno
        @ mov pc,lr
        @ bx lr
        @ push {lr} ... pop {pc}

@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ Prototipo en "C":
@   void productoEscalar32(uint32_t *vectorIn, uint32_t *vectorOut, uint32_t longitud, uint32_t escalar)
@
@ Parametros recibidos:
@   r0: dirección del vector entrada
@   r1: dirección del vector resultado
@	r2: longitud
@	r3: escalar
@
@ Valor de retorno: Nada
@
.thumb_func
    asm_productoEscalar32:
    	ldr r5, [r0]
    	mul r4, r5, r3
    	str r4, [r1]		// Elemento 0 del vector
    	subs r2, 1			// r2 = r2 - 1
    _for2:
    	ldr r5, [r0, 4]!	// r5 = *r0 + 2
    	mul r4, r5, r3
        str r4, [r1, 4]! 	// *(r1 + 2 bytes) = r5*r3
        subs r2, 1			// r2 = r2 - 1
        bne _for2		// seguir en el ciclo for
        bx lr       @ vuelve adonde fue llamada (especificamente, si "pc"
                    @ es la direccion, en el codigo del programa, de la
                    @ instruccion "bl asm_sum" usada para saltar a
                    @ esta funcion, entonces "lr" contiene ese "pc" + 4).
                    @ el valor de retorno debe quedar en el registro r0.
                    @ En este caso, r0 es el resultado de r0 + r1.

        @ Otras alternativas para el retorno
        @ mov pc,lr
        @ bx lr
        @ push {lr} ... pop {pc}

@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ Prototipo en "C":
@   void productoEscalar16(uint16_t *vectorIn, uint16_t *vectorOut, uint32_t longitud, uint16_t escalar)
@
@ Parametros recibidos:
@   r0: dirección del vector entrada
@   r1: dirección del vector resultado
@	r2: longitud
@	r3: escalar
@
@ Valor de retorno: Nada
@
.thumb_func
    asm_productoEscalar16:
    	ldrh r5, [r0]
    	mul r4, r5, r3
    	strh r4, [r1]		// Elemento 0 del vector
    	subs r2, 1			// r2 = r2 - 1
    _for3:
    	ldrh r5, [r0, 2]!	// *r0 = *r0 + 4
    	mul r4, r5, r3
        strh r4, [r1, 2]! 	// *(r4 + 4 bytes) = r0*r3
        subs r2, 1			// r2 = r2 - 1
        bne _for3		// seguir en el ciclo for
        bx lr       @ vuelve adonde fue llamada (especificamente, si "pc"
                    @ es la direccion, en el codigo del programa, de la
                    @ instruccion "bl asm_sum" usada para saltar a
                    @ esta funcion, entonces "lr" contiene ese "pc" + 4).
                    @ el valor de retorno debe quedar en el registro r0.
                    @ En este caso, r0 es el resultado de r0 + r1.

        @ Otras alternativas para el retorno
        @ mov pc,lr
        @ bx lr
        @ push {lr} ... pop {pc}


@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ Prototipo en "C":
@   void productoEscalar16(uint16_t *vectorIn, uint16_t *vectorOut, uint16_t longitud, uint16_t escalar)
@
@ Parametros recibidos:
@   r0: dirección del vector entrada
@   r1: dirección del vector resultado
@	r2: longitud
@	r3: escalar
@
@ Valor de retorno: Nada
@
.thumb_func
    asm_productoEscalar12:
    	ldrh r5, [r0]
    	mul r4, r5, r3
    	usat r5, 12, r4
    	strh r4, [r1]		// Elemento 0 del vector
    	subs r2, 1			// r2 = r2 - 1
    _for5:
    	ldrh r5, [r0, 2]!	// *r0 = *r0 + 4
    	mul r4, r5, r3
    	usat r5, #12, r4
        strh r5, [r1, 2]! 	// *(r4 + 4 bytes) = r0*r3
        subs r2, 1			// r2 = r2 - 1
        bne _for5		// seguir en el ciclo for
        bx lr       @ vuelve adonde fue llamada (especificamente, si "pc"
                    @ es la direccion, en el codigo del programa, de la
                    @ instruccion "bl asm_sum" usada para saltar a
                    @ esta funcion, entonces "lr" contiene ese "pc" + 4).
                    @ el valor de retorno debe quedar en el registro r0.
                    @ En este caso, r0 es el resultado de r0 + r1.

        @ Otras alternativas para el retorno
        @ mov pc,lr
        @ bx lr
        @ push {lr} ... pop {pc}
