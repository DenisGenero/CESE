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
.global asm_downSampleM

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
@   void zeros(uint32_t * vector, uint32_t longitud)
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
@   void zeros16(uint16_t * vector, uint16_t longitud)
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

/* Uso de registros:
 * -r3: Indice para recorrer el vector de muestras
 * -r4: Indice para moverse en la ventana
 * -r5: Carga el valor de muestras, y sirve para hacer la división por el ancho de la ventana
 * -r6: Valor acumulado para cargar en el vector de salida
 * -r7: Límite inferior de la ventana en el vector de muestras
*/

.thumb_func
    asm_filtroVentana10:
    	push {r4-r10}
    	mov r3, r2		// Resguardo longitud (r2) para ver cuando estoy fuera del vector
    // Vucle que recorre el vector de muestras
    _for3:
    	subs r3, #1		// r3 = r3 - 1 --> r3 indice que recorre el vector
    	beq _exit2		// Salir del programa si se terminaron las muestras
    	mov r6, #0		// Reinicio el valor del acumulador cada vez que me muevo de muestra
    	add r4, r3, #SampleOffset	// r4 = r3 + 6 --> r4 indice para mover la ventana
    	cmp r4, #LimInfVentana	// Comparo con la cantidad de muestras que tiene la ventana
    	mov r7, #0	// Límite inferior igual a cero si no quedan más muestras --> ventana más grande que cantidad de muestras restantes
    	itt hi			// Si el tamamño de la ventana es mas grande que las muestras que quedan, se compara con cero
    	subhi r7, r4, #LimInfVentana	// Límite inferior de la ventana, si es necesario --> ventana más pequeña que muestras restantes
    	subhi r7, #1

    	// Bucle que recorre las muestras en la ventana
    	_for4:
    		subs r4, #1
    		beq _for3		// si r4 es cero volver al bucle principal
    		cmp r2, r4		// ignorar operaciones si estamos afura del vector
    		bls _for4		// retorna al for para seguir descontando r4
    		mov r5, #LimInfVentana // No se puede dividir directamente por un número, se acá para no esta dentror de it y sacar una instrucción
    		cmp r4, r7		// Comparo con el limite inferior
    		ittt ls			// Comparo para ver si llegue al límite del recorrido
    		udivls r6, r6, r5	// Si llegué al límite divido por la cantidad de muestras (cargadas en r5 previamente)
    		strhls r6, [r1, r3, LSL #1]	// *(r1 + (r3>>1)) = r6 --> guardo resultado en vector de salida
    		bls _for3		// Vuelvo al bucle principal
    		// En caso de que no llegue al límite, sigo acumulando
    		ldrh r5, [r0, r4, LSL #1]	// r5 = *(r0 + (r3>>1)) --> cargo un nuevo valor del vector de muestras
    		add r6, r6, r5				// r6 = r6 + r5
    		b _for4

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
@   uint32_t max(int32_t *vectorIn, uint32_t longitud);
@
@ Parametros recibidos:
@   r0: dirección del vector entrada
@   r1: longitud
@
@ Valor de retorno: indice donde se encuentra el mayor valor
@
.thumb_func
    asm_max:
    	push {r4-r7}
    	sub r1, #1
    	ldr r2, [r0, r1, LSL #2] // Se guarda el primer valor para comparar
    	mov r3, r1	// Se guarda el índice
    	subs r1, #1

    _for6:
    	ldr r4, [r0, r1, LSL #2] // Se carga siguiente valor para comparar
    	cmp r4, r2 // Se compara con el valor cargado previo
    	itt gt
    	movgt r2, r4 // Si el nuevo valor es mayor, se almacena en r2 para volver a comparar
    	movgt r3, r1 // Se guarda el indice
    	subs r1, #1
    	bne _for6

    	pop {r4-r7}
    	mov r0, r3	// Se guarda el valor de retorno
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
@   uint32_t downSampleM(int32_t *vectorIn, int32_t *vectorOut, uint32_t longitud, uint32_t N)
@
@ Parametros recibidos:
@   r0: dirección del vector entrada
@   r1: dirección del vector salida
@   r2: longitud
@   r3: N
@
@ Valor de retorno: indice donde se encuentra el mayor valor
@
.thumb_func
    asm_downSampleM:
    	push {r4-r7}
    	mov r4, #0  // Indice para recorrer el vector
    	mov r5, #0  // Indice para guardar los valores
    	mov r6, r3  // Se copia n para ir modificando el valor de comparación
    	sub r6, #1  // Se resta uno para tener en cuenta la muestra en posición cero
    	sub r2, #1  // Se resta uno, para no exceder el límite del vector

    _for7:
    	ldr r7, [r0, r4, LSL #2]  // Se carga el valor del vector de entrada
    	cmp r4, r6  // Se compara con el N, que se va desplazando (por eso se hizo la copia)
    	itee eq
    	addeq r6, r6, r3	// Si es igual a N, omitir la muestra y actualizar el N de comparación
    	strne r7, [r1, r5, LSL #2] // Si es distinto, se guarda en el vector destino
    	addne r5, #1  // Se actualiza el índice del vector de salida
    	add r4, #1   // Se actualiza el índice del vector de entrada
    	cmp r4, r2  // Si el índice llego a la longitud se sale de la función
    	bne _for7  // Si no se llegó al final, se sigue iterando

    	pop {r4-r7}
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
