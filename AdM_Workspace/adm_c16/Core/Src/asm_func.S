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
.global asm_invertir
.global asm_generaEco
.global asm_generaEcoSIMD
.global asm_corr
.global asm_corrSIMD

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
    	mov r8, #LimInfVentana // No se puede dividir directamente por un número, se acá para no esta dentror de it y sacar una instrucción

    	// Bucle que recorre las muestras en la ventana
    	_for4:
    		subs r4, #1
    		beq _for3		// si r4 es cero volver al bucle principal
    		cmp r2, r4		// ignorar operaciones si estamos afura del vector
    		bls _for4		// retorna al for para seguir descontando r4
    		cmp r4, r7		// Comparo con el limite inferior
    		ittt ls			// Comparo para ver si llegue al límite del recorrido
    		udivls r6, r6, r8	// Si llegué al límite divido por la cantidad de muestras (cargadas en r5 previamente)
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

@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ Prototipo en "C":
@   void invertir(uint16_t *vectorIn, uint32_t longitud);
@
@ Parametros recibidos:
@   r0: dirección del vector entrada
@   r1: longitud
@
@ Valor de retorno: indice donde se encuentra el mayor valor
@
.thumb_func
    asm_invertir:
    	push {r4-r7}
    	mov r2, #0  // Índice para invertir el vector

    _for8:
    	subs r1, #1	// Se decrementa el contador decreciente
    	ldrh r3, [r0, r1, LSL #1]  // Se carga la muestras desde "longitud" hacia el medio --> índice que decrece
    	ldrh r4, [r0, r2, LSL #1]  // Se carga la muestras desde "cero" hacia el medio --> índice que crece
    	cmp r1, r2 //Comparo los índices, sin son iguales o r2 supero a r1 entonces ya se terminó el proceso
    	itte hi
    	strhhi r4, [r0, r1, LSL #1] // Guardar desde el extremo "longitud" el valor hacia el extremo "cero"
		strhhi r3, [r0, r2, LSL #1]// Guardar desde el extremo "cero" el valor hacia el extremo "longitud"
		bls _exit3		// Salir si los índices son iguales o r2 superó a r1
    	add r2, #1		// Se incrementa el índice creciente
    	bne _for8  // Si no se llegó al final, se sigue iterando

    _exit3:
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

@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ Prototipo en "C":
@   void asm_generaEco(int16_t *vectorIn, int16_t *vectorOut, uint32_t longitud, uint32_t msegRetardo)
@
@ Parametros recibidos:
@   r0: dirección del vector entrada
@   r1: dirección del vector de salida
@   r2: longitud
@   r3: retardo del eco
@
@ Valor de retorno: Nada
@

#define SAMPLE_FREQ	44100

.thumb_func
    asm_generaEco:
    	push {r4-r10}
    	// Calcular muestra a partir de donde se inicia el eco --> r4
    	// La cuenta es SampleOffset = msegRetardo*SAMPLE_FREQ/1000
    	mov r4, #SAMPLE_FREQ  // r4 será el límite a partir de donde se aplicará el eco
    	mul r4, r4, r3    // r4 = SAMPLE_FREQ*msegRetardo
    	mov r3, #1000  // Se recicla r3 --> 1000 por que son milisegundos, y la frecuencia está en segundos
    	udiv r4, r4, r3  // r4 = r4/1000 (para el ej 10 debería da 882)
    	sub r2, #1  // longitud = longitud - 1
    	mov r6, #-1

    _for9:
    	sub r3, r2, r4  // Se recicla r3 = longitud - muestraEco(882 en el ejemplo)
    	ldrsh r5, [r0, r2, LSL #1]  // Desde la última muestra
    	ldrsh r6, [r0, r3, LSL #1]  // Desde la muestra del eco
    	asr r6, #1	// Muestra de eco dividido por dos
    	add r5, r5, r6 // Se compone la muestra con el eco
    	ssat r6, #16, r5
    	strh r6, [r1, r2, LSL #1] // Se guarda con el índice r2
    	cmp r2, r4  // Si el índice es igual al offset del eco, se debe dejar de añadir
    	sub r2, #1	// Se decrementa el índice, sin modificar el APSR
    	bne _for9

    _for10:
    	// Muestras sin eco
    	ldrh r5, [r0, r2, LSL #1]
    	strh r5, [r1, r2, LSL #1]
    	subs r2, #1
    	bne _for10

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
@   void asm_generaEcoSIMD(int16_t *vectorIn, int16_t *vectorOut, uint32_t longitud, uint32_t msegRetardo)
@
@ Parametros recibidos:
@   r0: dirección del vector entrada
@   r1: dirección del vector de salida
@   r2: longitud
@   r3: retardo del eco
@
@ Valor de retorno: Nada
@

.thumb_func
    asm_generaEcoSIMD:
    	push {r4-r10}
    	// Calcular muestra a partir de donde se inicia el eco --> r4
    	// La cuenta es SampleOffset = msegRetardo*SAMPLE_FREQ/1000
    	mov r4, #SAMPLE_FREQ  // r4 será el límite a partir de donde se aplicará el eco
    	mul r4, r4, r3    // r4 = SAMPLE_FREQ*msegRetardo
    	mov r3, #1000  // Se recicla r3 --> 1000 por que son milisegundos, y la frecuencia está en segundos
    	udiv r4, r4, r3  // r4 = r4/1000 (para el ej 10 debería da 882)
    	lsr r4, #1 // Como ahora se cargan 2 registros los índices se dividen por 2
    	lsr r2, #1 // Como ahora se cargan 2 registros los índices se dividen por 2
    	sub r2, #1  // longitud = longitud - 1
    	mov r7, #0  // Es un registro dummy, para poder hacer la atenuación por 2 (shift a la derecha) en la muestra con eco

    _for11:
    	// Como ahora se cargan 2 registros los índices se incrementan el doble
    	sub r3, r2, r4  // Se recicla r3 = (longitud - muestraEco)/2 --> (441 en el ejemplo)
    	ldr r5, [r0, r2, LSL #2]  // Desde la última muestra (ahora se cargan 32 bits)
    	ldr r6, [r0, r3, LSL #2]  // Desde la muestra del eco (ahora se cargan 32 bits)
    	shadd16 r6, r6, r7 // muestra de eco dividido por 2 (r7 = 0, por lo que no afecta a r6)
    	qadd16 r6, r6, r5	// r6 = sat(r6 + r5, 16bits)
    	str r6, [r1, r2, LSL #2] // Se guarda con el índice r2
    	cmp r2, r4  // Si el índice es igual al offset del eco, se debe dejar de añadir
    	sub r2, #1	// Se decrementa el índice, sin modificar el APSR
    	bne _for11

    _for12:
    	// Muestras sin eco
    	ldrh r5, [r0, r2, LSL #1]
    	strh r5, [r1, r2, LSL #1]
    	subs r2, #1
    	bne _for12

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
@   void corr(int16_t *vectorX, int16_t *vectorY, int16_t *vectorCorr, uint32_t longitud)
@
@ Parametros recibidos:
@   r0: dirección del vector X
@   r1: dirección del vector Y
@   r2: dirección del vector de salida
@   r3: longitud
@
@ Valor de retorno: Nada
@

.thumb_func
    asm_corr:
    	push {r4-r10}
    	// Loop principal, para el vector de correlación
    	mov r4, #0  // índice l
    	mov r5, #0  // índice n
    	mov r9, #0  // acumulador
    	sub r3, #1 // longitud = longitud - 1

    _for13:
    	sub r6, r5, r4 // r6 = r5 - r4 (n-l)
    	ldrh r7, [r0, r5, LSL #1]  // x[n]
    	ldrh r8, [r1, r6, LSL #1]  // y[n-l]
    	mul r7, r7, r8  // r7 = x[n]*y[n-l]
    	add r9, r9, r7  // r9 = sum(x[n]*y[n-l])
    	cmp r5, r3    // n == longitud ?
    	ittt eq			// si es cierto:
    	//ssateq r8, #16, r9
    	strheq r9, [r2, r4, LSL #1]  // Terminó el cilco, se guarda el resultado acumulado
    	moveq r9, #0  // Se resetea el acumulador
    	beq _for14  // Se pasa al otro bucle, donde se decrementa l
    	add r5, #1  // Si el proceso continúan, incremento r5
    	b _for13

    _for14:
    	add r4, #1  // Se incrementa l
    	mov r5, r4  // n = l, ya que para n menores la comparación no tiene sentido (n<0)
    	cmp r3, r4 // Si l == longitud, termina la función, sino se sigue iterando
    	bne _for13

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
@   void corr(int16_t *vectorX, int16_t *vectorY, int16_t *vectorCorr, uint32_t longitud)
@
@ Parametros recibidos:
@   r0: dirección del vector X
@   r1: dirección del vector Y
@   r2: dirección del vector de salida
@   r3: longitud
@
@ Valor de retorno: Nada
@

.thumb_func
    asm_corrSIMD:
    	push {r4-r10}
    	// Loop principal, para el vector de correlación
    	mov r4, #0  // índice l
    	mov r5, #0  // índice n
    	mov r9, #0  // acumulador
    	lsr r3, #1  // Ahora se cargan 2 valores, por lo que se debe iterar la mitad de veces
    	sub r3, #1 // longitud = longitud - 1

    _for15:
    	subs r6, r5, r4 // r6 = r5 - r4 (n-l)
    	ldr r7, [r0, r5, LSL #2]  // x[n], x[n+1]
    	ldr r8, [r1, r6, LSL #2]  // y[n-l], y[n+1-l]
    	smuad r7, r7, r8  // r7 = x[n]*y[n-l] + x[n+1]*y[n+1-l]
    	add r9, r9, r7  // r9 = acumulado + r7
    	cmp r5, r3    // n == longitud ?
    	itt eq			// si es cierto:
    	strheq r9, [r2, r4, LSL #1]  // Terminó el cilco, se guarda el resultado acumulado
    	beq _for16  // Se pasa al otro bucle, donde se decrementa l
    	add r5, #1  // Si el proceso continúan, incremento r5 (índice n)
    	b _for15

    _for16:
    	mov r9, #0  // Se resetea el acumulador
    	add r4, #1  // Se incrementa el índice l
    	mov r5, r4  // n = l, ya que para n menores la comparación no tiene sentido (n<0)
    	cmp r3, r4 // Si l == longitud, termina la función, sino se sigue iterando
    	bne _for15

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
