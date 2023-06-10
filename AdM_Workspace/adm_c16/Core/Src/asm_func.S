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
.global asm_filtroVentana10
.global asm_pack32to16
.global asm_max

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
		// Guardas de seguridad
		cbz r0, exit
		cbz r1, exit
		mov r2, #0
	loop:
		// Se recorre el vector del último al primer elemento
		subs r1, #1
		// El shift se hace por dos, por lo que se incrementa de a 4 bytes
		str r2, [r0, r1, LSL #2]
		bne loop
	exit:
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
    	// Guardas de seguridad
		cbz r0, exit1
		cbz r1, exit1
		mov r2, #0
	loop1:
		// Se recorre el vector del último al primer elemento
		subs r1, #1
		// El shift se hace por 1, por lo que se incrementa de a 2 bytes
		strh r2, [r0, r1, LSL #1]
		bne loop1
	exit1:
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
    	// Los registros a partir de r4 se deben guardar (ejemplo de varios registros)
    	push {r4-r8}				// Resguardar registros de r4 a r8
    _for:
    	subs r2, #1
    	ldr r4, [r0, r2, LSL #2]	// r4 = *(r0 + (r2 << 2))
    	mul r4, r4, r3 				// r4 = r3*r4
    	str r4, [r1, r2, LSL #2]	// *(r1 + (r2 << 2) = r4
    	bne _for					// Seguir en el ciclo mientras r2>0
    	pop {r4-r8}					// Recuperar valores de registros. 1Se puede ocupar hasta r12
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
    	push {r4}					// Resguardar r4
    _for1:
    	subs r2, #1					// r2 = r2 - 1
    	ldrh r4, [r0, r2, LSL #2]	// r4 = *(r0 + (r2 << 2))
    	mul r4, r4, r3				// r4 = r4 * r3
    	strh r4, [r1, r2, LSL #2]	// *(r1 + (r2 << 2)) = r4
        bne _for1					// Seguir en el ciclo mientras r2>0
        pop {r4}					// Recuperar el valor de r4
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
@   void productoEscalar12(uint16_t *vectorIn, uint16_t *vectorOut, uint32_t longitud, uint16_t escalar)
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
        push {r4, r5}				// Resguardar r4 y r5
    _for2:
    	subs r2, #1					// r2 = r2 - 1
    	ldrh r4, [r0, r2, LSL #2]	// r4 = *(r0 + (r2 << 2))
    	mul r4, r4, r3				// r4 = r4 * r3
    	usat r5, #12, r4			// Saturación en 12 bits
    	strh r5, [r1, r2, LSL #2]	// *(r1 + (r2 << 2)) = r5
        bne _for2					// Seguir en el ciclo mientras r2>0
        pop {r4, r5}				// Recuperar el valor de r4 y r5
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
@   void filtroVentana10(uint16_t *vectorIn, uint16_t *vectorOut, uint32_t longitud)
@
@ Parametros recibidos:
@   r0: dirección del vector entrada
@   r1: dirección del vector resultado
@	r2: longitud
@
@ Valor de retorno: Nada
@
#define SampleOffset 6
#define LimInfVentana 11
.thumb_func
    asm_filtroVentana10:
    	push {r4-r10}
    	mov r3, r2		// Resguardo longitud (r2) para ver cuando estoy fuera del vector
    _for3:
    	subs r3, #1		// r3 = r3 - 1 --> r3 indice que recorre el vector
    	beq _exit2		// Salir del programa si se terminaron las muestras
    	add r4, r3, #SampleOffset	// r4 = r3 + 6 --> r4 indice para mover la ventana
    	cmp r4, LimInfVentana
    	it ls			// Si el tamamño de la ventana es mas grande que las muestras que quedan, se compara con cero
    	subls r7, r3, #SampleOffset	// Límite inferior de la ventana, si es necesario
    	_for4:
    		subs r4, #1
    		cmp r2, r4		// ignorar operaciones si estamos afura del vector
    		bls _for4		// retorna al for para seguir descontando r4
    		bne _for3		// si r4 es cero volver al bucle principal
    		cmp r4, r7		// Comparo con el limite inferior
    		ldrh r5, [r0, r3, LSL #2]	// r5 = *(r0 + (r3>>2))
    		add r6, r6, r5				// r6 = r6 + r5
    		bne _for4

    	strh r6, [r1, r3, LSL #2]	// *(r1 + (r3>>2)) = r6

    _exit2:
    	pop {r4-r10}
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
@   void pack32to16(int32_t *vectorIn, int16_t *vectorOut, uint32_t longitud)
@
@ Parametros recibidos:
@   r0: dirección del vector entrada
@   r1: dirección del vector resultado
@	r2: longitud
@
@ Valor de retorno: Nada
@
.thumb_func
    asm_pack32to16:
    	push {r4}				// Resguardar r4
    _for5:
    	subs r2, #1					// r2 = r2 - 1
    	ldr r4, [r0, r2, LSL #2]	// r4 = *(r0 + (r2 << 4))
    	asr r3, r4, #16				// r3 = r4>>16 --> aritmetic shift right (tiene en cuenta el signo)
    	strh r3, [r1, r2, LSL #1]	// *(r1 + (r2 << 2)) = r3
        bne _for5					// Seguir en el ciclo mientras r2>0
        pop {r4}

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
@   uint32_t asm_max(int32_t *vectorIn, uint32_t longitud);
@
@ Parametros recibidos:
@   r0: dirección del vector entrada
@   r1: dirección del vector resultado
@	r2: longitud
@
@ Valor de retorno: indice donde se encuentra el mayor valor
@
.thumb_func
    asm_max:

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
