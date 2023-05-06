Cuestionario:

Preguntas orientadoras:

1- Existen tres familias de procesadores de ARM:
 - Cortex A (Application):
	Son procesadores potentes que están más pensados para sistemas operativos de propósito general, como android por ejemplo. El punto fuerte de estos es su velocidad y
	poder correr muchos procesos en paralelo
- Cortex R (Real time):
	Están pensados, como su nombre lo indica, para aplicaciones de tiempo real y críticas. Se caracterizan por ser sistemas de baja latencia, lo cual es muy importante al
	estar en un sistema operativo de tiempo real. Esta baja latencia permite hacer conmutaciones de contexto de manera rápida y poder determinar con mayor certeza el tiempo
	de respuesta del sistema.
-Cortex M (Microcontroller):
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
	*Arquitectura Von Neumann: Se utiliza una sola memoria para los datos y las instrucciones.
	- Cortex M3:
	Estos procesadores a mi entender representan un punto medio en la familia de los Cortex-M. En lo personal es el que más me llama la atención, ya que a diferencia del M0, ahora
	estamos en presencia de un bus con arquitectura Hardvard y la arquitectura del core es ahora ARMv7. Además se agregan más herramientas de hardware ya que permite multiplicación
	y división por hardware, lo que da como resultado mejor eficiencia en camputo que involucren estas operaciones respecto del M0.
	Son procesadores que permiten resolver aplicaciones que involucren cálculos un poco más complejos, y vienen acompañados con más consumo y un mayor precio con respecto a los M0.
	*Arquitectura Hardvard: la memoria de datos y de instrucciones están separadas (usan distintos buses).
	-Cortex M4:
	Son una evolución de los M3 y resuelven a nivel de hardware cuestiones que pueden escapar a estos. Un ejemplo claro de esto es la FPU o unidad de punto flotante, que permite
	trabajar con estos tipos de datos de manera mucho más eficiente que en M3, ya que hay un espcaio en el silicio dedicado a atender estas operaciones (si bien existen M4 sin FPU
	la verdad es que son muy escasos y no están muy difundidos). Además incorpora instrucciones que los hacen más eficientes para procesamiento de señales, como por ejemplo en la 
	implementación de filtros (MAC: multiply accumulate, SIMD: single instruction multiple data, etc.). Todo esto viene acompañado además de un reloj con posibilidades de trabajar 
	a frecuencias más altas que en los casos anteriores.

2- Thumb permite mayor dencidad de código

	El ISA (set de instrucciones de arquitectura) Thumb permite generar una mayor densidad de código ya que para ejecutar una tarea con este set se puede hacer de manera más compacta,
	es decir, queda un programa menos extenso. Esto además conlleva, por lo general, a un mejor entendimiento y legibilidad del código.
	
3- Arquitectura load-store
	Significa que por cada vez que se quiera procesar información que esta en la memoria, el procesador tiene que cargarla, procesarla y luego volver a almacenarla en memoria (si
	es necesario).
	######################### Preguntar que tipo de instrucciones no tiene esta arquitectura #################################

4- Mapa de memoria de la familia
	El mapa de memoria es "plano", es decir, se tiene un ancho de bus de memoria de 32 bits, lo que da lugar a direccionar hasta 4GB. En este sentido, absolutamente todo se dispone en 
	este rango de direcciones, como la SRAM, la Flash, periféricos, etc. Cada uno de ellos se puede acceder desde diferentes buses, como por ejemplo AHB (Advance High-performance Bus)
	o el APB (Advance Peripheral Bus).

5- Ventajas de los "shadowed pointers": PSP y MSP
	El MSP es el "Main Stack Pointer" y el PSP es el "Procces Stack Pointer". La ventaja de tener 2 Stack pointer se puede apreciar mejor con un ejemplo. En el caso de que se tenga un RTOS
	corriendo en el microcontrolador, el MSP será el encargado de guardar la información y recursos del OS, en los "cambios de contexto". Por otro lado, el PSP tiene la misma función que
	el MSP pero para almacenar información y recursos de las tareas y/o funciones que defina el usuario o programador. De esta manera, al tener 2 SP, el cambio de contexto del OS se realiza
	de forma más "trasparente" y segura, sin correr el riesgo de que se pierda información que pueda alterar el correcto funcionamiento del RTOS. Cabe mencionar que en ejecución "bare metal"
	solo se utiliza el MSP, y este solo se puede utilizar en el modo "privilegiado" (activado por defecto en bare metal).

6- 