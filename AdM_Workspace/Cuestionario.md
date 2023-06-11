# Cuestionario

***

## Preguntas orientadoras:

**1- Describa brevemente los diferentes perfiles de familias de microprocesadores/microcontroladores de ARM. Explique alguna de sus diferencias características.**

Existen tres familias de procesadores de ARM:  
 - *Cortex A (Application):*  
	Son procesadores potentes que están más pensados para sistemas operativos de propósito general, como android por ejemplo. El punto fuerte de estos es su velocidad y
	poder correr muchos procesos en paralelo.
- *Cortex R (Real time):*  
	Están pensados, como su nombre lo indica, para aplicaciones de tiempo real y críticas. Se caracterizan por ser sistemas de baja latencia, lo cual es muy importante al
	estar en un sistema operativo de tiempo real. Esta baja latencia permite hacer conmutaciones de contexto de manera rápida y poder determinar con mayor certeza el tiempo
	de respuesta del sistema.
- *Cortex M (Microcontroller):*  
	Son los más económicos y están pensados para dispositivos de uso cotidiano. Existen diferentes variantes, algunas con menores prestaciones, como los M0 y M0+, pero ptimizados
	en cosnumo energético y de bajo costo; y otros con myores prestaciones y hardware dedicado a funciones específicas como los M4F con la FPU (unidad de punto flotante), 
	aritmética de saturación, CRC, DSP, etc.

***
	
## Cortex M:

**1- Describa brevemente las diferencias entre las familias de procesadores Cortex M0, M3 y M4.**

Diferencias entre Cortex M0, M3 y M4:  
- *Cortex M0:*  
	Representa la puerta de entrada a la familia Cortex-M de microcontroladores, y es la que tiene el set de instrucciones más reducido. Así mismo, por lo general es el más 
	económico de la familia y de menor consumo energético. A diferencia de los demás tiene un bus de memoria con arquitectura Von Neumann y la arquitectura del core es ARMv6.
	No posee MPU (unidad de protección de memoria), aunque su variante M0+ si la incorpora.  
	Es el procesador ideal si lo que se busca es bajo consumo en una aplicación que no requiera de calculos complejos, ya que posee multiplicación por hardware algo limitada y
	no posee división por hardware, lo que puede llegar a resultar muy ineficiente al realizarlo por software.  
	*Arquitectura Von Neumann:* Se utiliza un solo bus de memoria para los datos y las instrucciones.  
- *Cortex M3:*  
	Estos procesadores a mi entender representan un punto medio en la familia de los Cortex-M. En lo personal es el que más me llama la atención, ya que a diferencia del M0, ahora
	estamos en presencia de un bus con arquitectura Hardvard y la arquitectura del core es ahora ARMv7. Además se agregan más herramientas de hardware ya que permite multiplicación
	y división por hardware, lo que da como resultado mejor eficiencia en camputo que involucren estas operaciones respecto del M0.  
	Son procesadores que permiten resolver aplicaciones que involucren cálculos un poco más complejos, y vienen acompañados con más consumo y un mayor precio con respecto a los M0.  
	*Arquitectura Hardvard:* Se utilizan distintos buses para los datos y las instrucciones.  
- *Cortex M4:*  
	Son una evolución de los M3 y resuelven a nivel de hardware cuestiones que pueden escapar a estos. Un ejemplo claro de esto es la FPU o unidad de punto flotante, que permite
	trabajar con estos tipos de datos de manera mucho más eficiente que en M3, ya que hay un espcaio en el silicio dedicado a atender estas operaciones (si bien existen M4 sin FPU
	la verdad es que son muy escasos y no están muy difundidos). Además incorpora instrucciones que los hacen más eficientes para procesamiento de señales, como por ejemplo en la 
	implementación de filtros (MAC: multiply accumulate, SIMD: single instruction multiple data, etc.). Todo esto viene acompañado además de un reloj con posibilidades de trabajar 
	a frecuencias más altas que en los casos anteriores.  

**2- ¿Por qué se dice que el set de instrucciones Thumb permite mayor densidad de código? Explique**

El ISA (set de instrucciones de arquitectura) Thumb permite generar una mayor densidad de código ya que para ejecutar una tarea con este set se puede hacer de manera más compacta,
es decir, queda un programa menos extenso. Esto además conlleva, por lo general, a un mejor entendimiento y legibilidad del código. En Cortex-M se pueden encontrar instrucciones
de 16 bits y de 32 bits. Algunas de las primeras son versiones más compactas de las segundas (a expensas de una funcionalidad más limitada), permitiendo ahorrar espacio en memoria
de programa.  
	
**3- ¿Qué entiende por arquitectura load-store? ¿Qué tipo de instrucciones no posee este tipo de arquitectura?**

La arquitectura load-store se caracteriza por la presencia de dos instrucciones específicas para acceder a la memoria: una para cargar datos (load) y otra para almacenarlos (store)
El resto de las instrucciones del ISA opera directamente con los registros y no acceden a la memoria. Por lo tanto este tipo de arquitecturas no tienen  instrucciones que puedan
cargar un dato y hacer operaciones sobre el mismo, sino que en primera instancias lo deberan cargar en un registro, y luego operar sobre este.  

**4- ¿Cómo es el mapa de memoria de la familia?**

El mapa de memoria es *"plano"*, es decir, se tiene un ancho de bus de memoria de 32 bits, lo que da lugar a direccionar hasta 4GB. En este sentido, absolutamente todo se dispone en 
este rango de direcciones, como la SRAM, la Flash, periféricos, etc. Cada uno de ellos se puede acceder desde diferentes buses, como por ejemplo AHB (Advance High-performance Bus)
o el APB (Advance Peripheral Bus).  

**5- ¿Qué ventajas presenta el uso de los “shadowed pointers” del PSP y el MSP?**

El MSP es el *"Main Stack Pointer"* y el PSP es el *"Procces Stack Pointer"*. La ventaja de tener 2 Stack pointer se puede apreciar mejor con un ejemplo. En el caso de que se tenga un RTOS
corriendo en el microcontrolador, el MSP será el encargado de guardar la información y recursos del OS, en los "cambios de contexto". Por otro lado, el PSP tiene la misma función que
el MSP pero para almacenar información y recursos de las tareas y/o funciones que defina el usuario o programador. De esta manera, al tener 2 SP, el cambio de contexto del OS se realiza
de forma más *"trasparente"* y segura, sin correr el riesgo de que se pierda información que pueda alterar el correcto funcionamiento del RTOS. Cabe mencionar que en ejecución "bare metal"
solo se utiliza el MSP, y este solo se puede utilizar en el modo *"privilegiado"* (activado por defecto en bare metal).
El termino *"shadowed pointers"* hace referencia a que el procesador lee siempre el registro SP (R13), y con un bit, el SPSEL, se elije si se accede al MSP o al PSP

**6- Describa los diferentes modos de privilegio y operación del Cortex M, sus relaciones y como se conmuta de uno al otro. Describa un ejemplo en el que se pasa del modo privilegiado a no priviligiado y nuevamente a privilegiado.**

Existen dos modos de funcionamiento: el privilegiado el no privilegiado. En bare metal, por defecto se está en modo privilegiado. En cambio, cuando se utiliza un RTOS por ejemplo, este
modelo cobra más relevancia, ya que el Kernel del OS se ejecutará en modo privilegiado y las tareas que el usuario defina se ejecutarán en modo no privilegiado. De esta manera el OS
tendrá completo control y acceso a los recursos del microcontrolador (modo privilegiado) y podrá restringir el acceso a regiones de memoria a lo que se este ejecutando en modo no 
privilegiado. Con este modelo, el OS tiene el control de los recursos que cada tarea quiere ocupar, y en caso de detectar algún  problema, por ejemplo una tarea intentando leer o escribir
en una posición de memoria "prohibida", el OS podrá matar esa tarea y evitar así que todo el sistema se "crashee" o se "cuelgue", pudiendo reiniciar el proceso o tarea, y cotinuar con el 
normal funcionamiento del RTOS.  
Para conmutar del estado privilegiado al no privilegiado se debe modificar el registro *"CONTROL"*. Este registro sólo se puede modificar en modo privilegiado, por lo que, una vez modificado
y pasado al modo no privilegiado, no se puede volver al modo privilegiado. Esto es así para proteger el modo privilegiado.

**7- ¿Qué se entiende por modelo de registros ortogonal? Dé un ejemplo**

Los registros ortogonales son aquellos en los cuales al modificar el valor en uno, el otro no se ve afectado. Un ejemplo de esto es el banco de registros de uso general que tiene el procesador R0 a R12.  

**8- ¿Qué ventajas presenta el uso de intrucciones de ejecución condicional (IT)? Dé un ejemplo**

Las instrucciones IT son similares al "if" que conocemos del lenguaje C. Su uso permite ejecutar una instrucción si se cumple una condición determinada. Por consiguiente se puede alterar el curso 
del programa, dependiendo la condición que se utilice.

**9- Describa brevemente las excepciones más prioritarias (reset, NMI, Hardfault).**

- *reset:* Es la excepción que se produce cuando el procesador es energizado y tiene la mayor prioridad de todas. Dentro de esta se debe contener la seccuencia de reset, es decir los comandos 
para inicializar el microcontrolador.  
- *NMI:* Las siglas provienen de Non Maskeable Interrupts, que como su nombre lo indica será invocada por interrupciones no enmascarables. Tiene un nivel de prioridad menor que reset.  
- *HardFault:* Se invoca cuando se producen excepciones del sistema en las cuales no se ha definido como responder a dicho evento.

**10- Describa las funciones principales de la pila. ¿Cómo resuelve la arquitectura el llamado a funciones y su retorno?**

La función de la pila consiste en guardar el entorno actual de ejecución del programa ante un llamado a función. De esta manera, se guardan los valores de los registros y se los deja
disponibles para que puedan ser usados en el entotno de la función. Si dentro de esa función se invoca otra función, nuevamente se guarda el entorno y así sucesivamente. Se debe tener
cuidado en este aspecto, ya que se puede desbordar la pila si no se tiene cuida, pudiendo verse afectado la normal ejecución del programa.  

**11- Describa la secuencia de reset del microprocesador.**

Luego de un reset, el procesador se dirige a la posición 0x0000 de la memoria en donde se encuentra el Stack Pointer. Luego se dirige a la posición de memoria contigua, región donde comienza 
el NVIC, en la excepción reset, ejecutando la rutina de reset, para luego si ejecutar código de programa creado por el desarrollador. Por lo general esta última porción de memoria se aloja 
luego de la porción de memoria donde está alojado el NVIC.

**12- ¿Qué entiende por “core peripherals”? ¿Qué diferencia existe entre estos y el resto de los periféricos?**

Los  *"core-peripherals"* son aquellos que se encuentran "integrados" en el procesador, es decir son aquellos que encontraremos en todos los procesadores de Cortex (dependiendo el modelo en 
algunos casos) como pueden ser el NVIC, SysTick Timer y la MPU, donde estos últimos estpan ausentes en el M0/M0+.  
El resto de los periféricos dependerá del fabricante que desarrolle el procesador, y pueden ser módulos de comunicación (USART, SPI, I2C), Timers, ADCs, DACs, etc. En este caso será la empresa 
quién decida cuales, cuantos y en en que direcciones de memoria estarán estos periféricos.

**13- ¿Cómo se implementan las prioridades de las interrupciones? Dé un ejemplo**  

**14- ¿Qué es el CMSIS? ¿Qué función cumple? ¿Quién lo provee? ¿Qué ventajas aporta?**  

La CMSIS en un conjunto de librerias escritas en C que las provee ARM y permiten hacer uso de toda la funcionalidad de los procesadores Cortex. Esto representa una gran ventaja en la 
portabilidad del código, ya que se puede cambiar de un fabricante a otro y reutilizar el código ya desarrollado.

**15- Cuando ocurre una interrupción, asumiendo que está habilitada ¿Cómo opera el microprocesador para atender a la subrutina correspondiente? Explique con un ejemplo**  

**16- ¿Cómo cambia la operación de stacking al utilizar la unidad de punto flotante?**  

**17- Explique las características avanzadas de atención a interrupciones: tail chaining y late arrival.**  

**18- ¿Qué es el systick? ¿Por qué puede afirmarse que su implementación favorece la portabilidad de los sistemas operativos embebidos?**  

Es un timer que etsá en la arquitectura Cortex-M (no en M0 y M0+), por lo general de 24 bits, que se suele configurar para que produzca una interrupción cada 1 milisegundo. Este se utiliza 
como base de tiempo	para los RTOS, por lo que si se implementa un RTOS en un Cortex M3, es muy fácil portarlo a un M4, ya que ambos poseen la misma base de timepo.

**19- ¿Qué funciones cumple la unidad de protección de memoria (MPU)?**

Como su nombre lo indica, la función de la MPU es proteger sectores de memoria para que no puedan ser leídos y/o escrtios por procesos que no tengan autorización. Esto es muy útil cuando se
tiene un RTOS, en donde el Kernel es quién gestiona la memoria y asigna los recursos a cada tarea que se crea. En caso de que por algún motivo la tarea quiera utilizar más memoria de la asignada,
 se le bloqueará el acceso a dicho sector, el Kernel será avisado de esto y se tomararán acciones: matar o reiniciar la tarea, por ejemplo.

**20- ¿Cuántas regiones pueden configurarse como máximo? ¿Qué ocurre en caso de haber solapamientos de las regiones? ¿Qué ocurre con las zonas de memoria no cubiertas por las regiones definidas?**  

Se pueden configurar como máximo hasta 8 regiones. En caso de que se produzca un solapamiento de regiones, en dicha zona rigen los permisos y atributos de la región de mayor número. En caso de que se 
se quiera acceder a una zona de memoria que no está cubierta por las zonas definidas en la MPU, la transferencia se bloqueará y se producirá una excepción.  
	
**21- ¿Para qué se suele utilizar la excepción PendSV? ¿Cómo se relaciona su uso con el resto de las excepciones? Dé un ejemplo**  

La excepsión PsndSV se suele utilizar por el kernel de un sistema operativo para ejecutar un cambio de contexto. En FreeRtos por ejemplo, cuando se cumple un "time slice" el SysTick Timer genera una 
interrupción y luego llama a esta excepción para que en ella se pueda produicir el cambio de contexto, y así poder ejecutar otra tarea, guardando el contexto de la tarea previamente ejecutada. Se debe 
tener presente que dentro de esta excepción, el procesador se encuentra en modo Handler, teniendo acceso a todos los recursos (modo privilegiado).  

**22- ¿Para qué se suele utilizar la excepción SVC? Expliquelo dentro de un marco de un sistema operativo embebido.**  

La excepción del SVC es aquella que se puede inducir o invocar por software, y por lo general es utilizada para pasar de modo "no privilegiado" a "privilegiado". Esto se logra ya que el procesador 
al ingresar en una excepción, sale del modo *Thread* y entra en modo *Handler*, donde por defecto tiene el modo privilegiado, permitiendo así modificar el registro de CONTROL (cambiando el estado de
 ejecución de no privilegiado a privilegiado). Esta es la manera que tiene un RTOS de cambiar de estados cuando le da el control del procesador a una tarea (modo no privilegiado) y esta le devuelve 
 luego el control al kernel (modo privilegiado).

***

## ISA

**1- ¿Qué son los sufijos y para qué se los utiliza? Dé un ejemplo**

Los sufijos son agregados que se le pueden hacer a una instrucción de assembly para ser más específico en lo que se quiere ejecutar, y su sintaxis coonsta en agregar un punto al final de la
instrucción y luego el sufijo (letra/s o letra y digitos). Un ejemplo muy claro de esto son los sufijos .N (de "narrow"), que hacen referencia a las instrucciones de 16 bits y .W (de "wide"),
haciendo alución a las de 32 bits. En caso de no colocar ningún sufijo, el compilador de assembler decidirá cual instrucción colocar en memoria, dependiendo el caso, pero siempre dando
prioridad a las de 16 bits.

**2- ¿Para qué se utiliza el sufijo ‘s’? Dé un ejemplo**

El hecho de agregar una "s" al final de una instrucción hace referencia a actualizar el *"Application Program Status Register" (APSR)*, que es el responsable de indicar ciertas situaciones como 
resultado de la operación ejecutada, ejemplo: si hubo Carry, Overflow, etc. Por ende, no es lo mismo la instrucción ADD (suma que no actualiza el APSR) que ADDS (actualiza el ASPR en caso de 
ser necesario).

**3- ¿Qué utilidad tiene la implementación de instrucciones de aritmética saturada? Dé un ejemplo con operaciones con datos de 8 bits.**

Este tipo de operaciones es muy útil en el ámbito del procesamiento de señales, por ejemplo en la aplicación de filtros digitales. Consta en la aplicación de un valor máximo y mínimo, dentro
de los cuales se podrá alojar el resulado de una operatoria, teniendo presente evitar *"overflow"* (superar el límite superior) o *"underflow"* (superar el límite inferior). Por ejemplo, si tenemos
datos de 8 bits, y sus valores límites son 128 y -127, veamos que sucede con y sin aritmética de saturación:
- Aritmética común: 	A = 125 + 10 	--> A = -121: Hay overflow, por eso el resultado se vuelve negativo
- Aritmética saturada:	B = -124 - 50 	--> B = -127: No hay underflow, se supera el límite mínimo, pero la variable queda con el valor del límite inferior.

**4- Describa brevemente la interfaz entre assembler y C ¿Cómo se reciben los argumentos de las funciones? ¿Cómo se devuelve el resultado? ¿Qué registros deben guardarse en la pila antes de ser modificados?**

Los argumentos se reciben a través de los registros de propóisto generales, comenzando con r0 para el primer argumento y continuando con los demás según la cantidad de parámetros que tenga la función. 
El resultado de una función se devuelve meidante r0. Los registros que deben guardarse en la pila antes de utilizarce son de r4 a r12. Se debe tener la precaución de hacer un push al inicio de la 
función y un pop antes de retornar de la misma. Tanto el push y el pop se deben hacer con el mismo orden de los registros, por ejemplo:  
MiFunc_asm:  
	push {r4-r7}  //Guarda los valores de los registro r4 a r7  
	...  
	...  
	pop {r4-r7}  //Restaura el valor de los registros para no afectar el comprtamiento del programa principal  
	bx lr		 //Retorna al programa principal  
	
**5- ¿Qué es una instrucción SIMD? ¿En qué se aplican y que ventajas reporta su uso? Dé un ejemplo.**  

Como su nombre en inglés lo indica, SIMD significa Single Instruction, Multiple Data. Esto se refiere a la posibilidad de realizar operaciones con multiples datos en un solo ciclo de reloj. El secreto está 
en utilizar los registros de 32 bits para almacenar 2 datos de 16 o 4 de 8 bits, y realizar operaciones como suma, resta, etc, como si fueran registros independientes. Para lograr esto, el procesador crea una 
"barrera" entre los datos, de manera que las operaciones sobre un dato no afectan al contiguo. Un ejemplo simple puede ser la ADD8, en donde en una sola instrucción se suman 4 pares de datos de 8 bits cada uno.  

***

## Tabla comparativa de ciclos  

| Función | SIMD | Asm | Int | C |
| :--- | :---: | :---: | :---: |
| zeros | N/A | 103 | N/A | 431 |
| productoEscalar32 | N/A | XXX | N/A | XXX |
| productoEscalar16 | N/A | XXX | N/A | XXX |
| productoEscalar12 | N/A | XXX | XXX | XXX |
| filtroVentana10 | N/A | XXX | N/A | XXX |
| pack32to16 | N/A | XXX | N/A | XXX |
| max | N/A | XXX | N/A | XXX |