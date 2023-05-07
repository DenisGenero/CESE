Cuestionario:

Preguntas orientadoras:

1- Existen tres familias de procesadores de ARM:
 - Cortex A (Application):
	Son procesadores potentes que están más pensados para sistemas operativos de propósito general, como android por ejemplo. El punto fuerte de estos es su velocidad y
	poder correr muchos procesos en paralelo.
- Cortex R (Real time):
	Están pensados, como su nombre lo indica, para aplicaciones de tiempo real y críticas. Se caracterizan por ser sistemas de baja latencia, lo cual es muy importante al
	estar en un sistema operativo de tiempo real. Esta baja latencia permite hacer conmutaciones de contexto de manera rápida y poder determinar con mayor certeza el tiempo
	de respuesta del sistema.
- Cortex M (Microcontroller):
	Son los más económicos y están pensados para dispositivos de uso cotidiano. Existen diferentes variantes, algunas con menores prestaciones, como los M0 y M0+, pero ptimizados
	en cosnumo energético y de bajo costo; y otros con myores prestaciones y hardware dedicado a funciones específicas como los M4F con la FPU (unidad de punto flotante), 
	aritmética de saturación, CRC, DSP, etc.
	
Cortex M:

1- Diferencias entre Cortex M0, M3 y M4:

	- Cortex M0:
	Representa la puerta de entrada a la familia Cortex-M de microcontroladores, y es la que tiene el set de instrucciones más reducido. Así mismo, por lo general es el más 
	económico de la familia y de menor consumo energético. A diferencia de los demás tiene un bus de memoria con arquitectura Von Neumann y la arquitectura del core es ARMv6.
	No posee MPU (unidad de protección de memoria), aunque su variante M0+ si la incorpora.
	Es el procesador ideal si lo que se busca es bajo consumo en una aplicación que no requiera de calculos complejos, ya que posee multiplicación por hardware algo limitada y
	no posee división por hardware, lo que puede llegar a resultar muy ineficiente al realizarlo por software.
	*Arquitectura Von Neumann: Se utiliza un solo bus de memoria para los datos y las instrucciones.
	- Cortex M3:
	Estos procesadores a mi entender representan un punto medio en la familia de los Cortex-M. En lo personal es el que más me llama la atención, ya que a diferencia del M0, ahora
	estamos en presencia de un bus con arquitectura Hardvard y la arquitectura del core es ahora ARMv7. Además se agregan más herramientas de hardware ya que permite multiplicación
	y división por hardware, lo que da como resultado mejor eficiencia en camputo que involucren estas operaciones respecto del M0.
	Son procesadores que permiten resolver aplicaciones que involucren cálculos un poco más complejos, y vienen acompañados con más consumo y un mayor precio con respecto a los M0.
	*Arquitectura Hardvard: se utilizan distintos buses para los datos y las instrucciones.
	- Cortex M4:
	Son una evolución de los M3 y resuelven a nivel de hardware cuestiones que pueden escapar a estos. Un ejemplo claro de esto es la FPU o unidad de punto flotante, que permite
	trabajar con estos tipos de datos de manera mucho más eficiente que en M3, ya que hay un espcaio en el silicio dedicado a atender estas operaciones (si bien existen M4 sin FPU
	la verdad es que son muy escasos y no están muy difundidos). Además incorpora instrucciones que los hacen más eficientes para procesamiento de señales, como por ejemplo en la 
	implementación de filtros (MAC: multiply accumulate, SIMD: single instruction multiple data, etc.). Todo esto viene acompañado además de un reloj con posibilidades de trabajar 
	a frecuencias más altas que en los casos anteriores.

2- Thumb permite mayor dencidad de código:

	El ISA (set de instrucciones de arquitectura) Thumb permite generar una mayor densidad de código ya que para ejecutar una tarea con este set se puede hacer de manera más compacta,
	es decir, queda un programa menos extenso. Esto además conlleva, por lo general, a un mejor entendimiento y legibilidad del código. En Cortex-M se pueden encontrar instrucciones
	de 16 bits y de 32 bits. Algunas de las primeras son versiones más compactas de las segundas (a expensas de una funcionalidad más limitada), permitiendo ahorrar espacio en memoria
	de programa.
	
3- Arquitectura load-store:

	Significa que por cada vez que se quiera procesar información que esta en la memoria, el procesador tiene que cargarla, procesarla y luego volver a almacenarla en memoria (si
	es necesario).
	######################### Preguntar que tipo de instrucciones no tiene esta arquitectura #################################

4- Mapa de memoria de la familia:

	El mapa de memoria es "plano", es decir, se tiene un ancho de bus de memoria de 32 bits, lo que da lugar a direccionar hasta 4GB. En este sentido, absolutamente todo se dispone en 
	este rango de direcciones, como la SRAM, la Flash, periféricos, etc. Cada uno de ellos se puede acceder desde diferentes buses, como por ejemplo AHB (Advance High-performance Bus)
	o el APB (Advance Peripheral Bus).

5- Ventajas de los "shadowed pointers": PSP y MSP

	El MSP es el "Main Stack Pointer" y el PSP es el "Procces Stack Pointer". La ventaja de tener 2 Stack pointer se puede apreciar mejor con un ejemplo. En el caso de que se tenga un RTOS
	corriendo en el microcontrolador, el MSP será el encargado de guardar la información y recursos del OS, en los "cambios de contexto". Por otro lado, el PSP tiene la misma función que
	el MSP pero para almacenar información y recursos de las tareas y/o funciones que defina el usuario o programador. De esta manera, al tener 2 SP, el cambio de contexto del OS se realiza
	de forma más "trasparente" y segura, sin correr el riesgo de que se pierda información que pueda alterar el correcto funcionamiento del RTOS. Cabe mencionar que en ejecución "bare metal"
	solo se utiliza el MSP, y este solo se puede utilizar en el modo "privilegiado" (activado por defecto en bare metal).

6- Modos de privilegio:

	Existen dos modos de funcionamiento: el privilegiado el no privilegiado. En bare metal, por defecto se está en modo privilegiado. En cambio, cuando se utiliza un RTOS por ejemplo, este
	modelo cobra más relevancia, ya que el Kernel del OS se ejecutará en modo privilegiado y las tareas que el usuario defina se ejecutarán en modo no privilegiado. De esta manera el OS
	tendrá completo control y acceso a los recursos del microcontrolador (modo privilegiado) y podrá restringir el acceso a regiones de memoria a lo que se este ejecutando en modo no 
	privilegiado. Con este modelo, el OS tiene el control de los recursos que cada tarea quiere ocupar, y en caso de detectar algún  problema, por ejemplo una tarea intentando leer o escribir
	en una posición de memoria "prohibida", el OS podrá matar esa tarea y evitar así que todo el sistema se "crashee" o se "cuelgue", pudiendo reiniciar el proceso o tarea, y cotinuar con el 
	normal funcionamiento del RTOS.
	Para conmutar del estado privilegiado al no privilegiado se debe modificar el registro "CONTROL". Este registro sólo se puede modificar en modo privilegiado, por lo que, una vez modificado
	y pasado al modo no privilegiado, no se puede volver al modo privilegiado. Esto es así para proteger el modo privilegiado.



17- SysTick Timer:

	Es un timer que etsá en la arquitectura Cortex-M (no en M0 y M0+), por lo general de 24 bits, que se suele configurar para que produzca una interrupción cada 1 milisegundo. Este se utiliza 
	como base de tiempo	para los RTOS, por lo que si se implementa un RTOS en un Cortex M3, es muy fácil portarlo a un M4, ya que ambos poseen la misma base de timepo.

ISA

1- Sufijos:

	Los sufijos son agregados que se le pueden hacer a una instrucción de assembly para ser más específico en lo que se quiere ejecutar, y su sintaxis coonsta en agregar un punto al final de la
	instrucción y luego el sufijo (letra/s o letra y digitos). Un ejemplo muy claro de esto son los sufijos .N (de "narrow"), que hacen referencia a las instrucciones de 16 bits y .W (de "wide"),
	haciendo alución a las de 32 bits. En caso de no colocar ningún sufijo, el compilador de assembler decidirá cual instrucción colocar en memoria, dependiendo el caso, pero siempre dando
	prioridad a las de 16 bits.

2- Sufijo "s":

	El hecho de agregar una "s" al final de una instrucción hace referencia a actualizar el "Application Program Status Register" (APSR), que es el responsable de indicar ciertas situaciones como 
	resultado de la operación ejecutada, ejemplo: si hubo Carry, Overflow, etc. Por ende, no es lo mismo la instrucción ADD (suma que no actualiza el APSR) que ADDS (actualiza el ASPR en caso de 
	ser necesario).

3- Aritmética saturada:

	Este tipo de operaciones es muy útil en el ámbito del procesamiento de señales, por ejemplo en la aplicación de filtros digitales. Consta en la aplicación de un valor máximo y mínimo, dentro
	de los cuales se podrá alojar el resulado de una operatoria, teniendo presente evitar "overflow" (superar el límite superior) o "underflow" (superar el límite inferior). Por ejemplo, si tenemos
	datos de 8 bits, y sus valores límites son 128 y -127, veamos que sucede con y sin aritmética de saturación:
	- Aritmética común: 	A = 125 + 10 	--> A = -121: Hay overflow, por eso el resultado se vuelve negativo
	- Aritmética saturada:	B = -124 - 50 	--> B = -127: No hay underflow, se supera el límite mínimo, pero la variable queda con el valor del límite inferior.
