# P1 - Principios de Sistemas Operativos

Escuela de Ingeniería en Computación
Bachillerato en Ingeniería en Computación
Sede Central Cartago

Prof. Erika Schumann
Principios de Sistemas Operativos
Semestre I, 2023

Estudiantes: 

David Jose Espinoza Soto - 2016012024

Jean Paul Rodriguez      - 2020059156

Taylor                   - 0000000000

Ronald                   - 0000000000

## Objetivos del proyecto
- Aprender a desarrollar un esquema de cliente-servidor.
- Conocer la comunicación por medio de sockets.
- Desarrollar un programa donde se utilicen threads.
- Poner en práctica la teoría del Planificador de CPU

## Definición general

Este primer proyecto tiene como finalidad desarrollar un simulador de planificador de CPU. Este simulador debe implementar los siguientes algoritmos: FIFO, SJF, HPF y Round Robin con un quantum especificado por el usuario.

Además, el proyecto será con un esquema cliente servidor que enviará mediante sockets la información de los procesos a ejecutar. Obviamente, el estudiante debe investigar sobre el protocolo de comunicación de los sockets.

Se contará con un cliente que funciona de 2 maneras: automático o manual. El modo manual leerá desde un archivo la información de procesos (PID, burst, prioridad). El modo automático creará un proceso con estos valores al azar. Por cada proceso se creará un hilo que debe conectarse via sockets al planificador de CPU. Este podrá estar en otra computadora, oyendo desde algún puerto definido.

El planificador de CPU recibirá la información de los procesos, los pondrá en una cola de espera y empezará la “ejecución” de los procesos. Apenas se tenga un proceso en la cola de espera ya se iniciará la simulación de la ejecución del mismo. Se espera que el Planificador de CPU tenga al menos 2 hilos: uno que reciba los mensajes del socket y ponga los procesos en la cola (Job scheduler) y otro que seleccione cual proceso tendrá el CPU (Cpu scheduler) y simule al CPU ejecutando. La ejecución de un proceso debe ser de la duración real del burst. 

El Planificador de CPU no debe dejar de funcionar hasta que uno se lo indique. Al finalizar debe desplegar información resumen de los procesos ejecutados. Se debe tener cuidado, de no dejar procesos sin matar o sockets abiertos. El proyecto debe ser desarrollado en C para Linux, utilizando la librería pthreads

## Descripción Detallada

- Cliente Manual: Recibirá de parámetro un archivo con una lista de procesos. Por cada uno de estos procesos debe crear un thread que le envié al planificador la información. El thread espera 2 segundos y envia la información. Además, debe haber un tiempo de sleep entre la lectura en el archivo de cada uno de los procesos. Esa duración será un tiempo random (3 a 8 segundos). La información que tendrá el archivo de entrada es la siguiente: (ejemplo)
  BURST Prioridad
      8         3
      7         2

- Cliente Automático: Debe funcionar igual que el anterior, con un thread por proceso y un tiempo random en la creación de cada uno de los procesos. La diferencia es que la información de los procesos no la tomará de un archivo sino la “inventará” poniendo valores random en el Burst y la Prioridad (1-5). El rango de los valores para el random del Burst y de la tasa de creación será un parámetro de entrada al correr esta versión del cliente. Este programa debe seguir creando procesos mientras nadie lo detenga.

- Una vez enviada la información de los procesos al planificador, los threads del cliente, estos recibirán la notificación de recibido por parte del server, desplegar el valor que recibe por parte del server y después deben morir

- Comunicación: La comunicación entre los clientes y el Simulador debe hacerse por medio de sockets. 

- Simulador (Server): Se debe seleccionar el algoritmo a correr(FIFO, SJF, HPF, Round Robin) como parámetro de entrada a este programa. debe tener al menos los siguientes procesos (hilos)
  - Job Scheduler: Será un hilo que reciba los mensajes de los sockets y los vaya guardando en algún tipo de lista. Esta lista simulará la cola del ready. Cuando este hilo recibe el proceso:
    - Le pone el PID
    - Le envía un mensaje de confirmación al cliente con el valor del PID. 
    - Le “crea” su PCB y lo guarda en la lista de espera.
  - CPU Scheduler: Constantemente deberá verificar si hay procesos en la cola. Si los hay debe ponerlos a ejecutar. Esto significa que según el algoritmo que se haya seleccionado, deberá escoger a alguien de la cola, “Ejecutarlo” (durar su burst por medio de un sleep) y seleccionar a alguien más, según el criterio del algoritmo. 
    - Debe quedar claro que mientras se ejecutan procesos, otros irán llegando a la cola.
    - Cada vez que hay un context switch y un proceso se ejecutará, se debe desplegar en pantalla (ej: Proceso 1 con burst x y prioridad x entra en ejecución)
    - Cada vez que un proceso termina completamente su ejecución y deja de estar en espera debe desplegarlo en pantalla.
    - En cualquier momento de la ejecución el usuario puede consultar la cola. Solo debe desplegar los procesos que están Ready. No los que ya hayan terminado. 
    - Se recomienda que tenga buen control del estado de los procesos. 
    - Para el Round Robin, debe tomar en cuenta siempre lo que lleve ejecutado. 
    - Para el FIFO el criterio de selección será el PID.
    - No se implementará ningún algoritmo apropiativo (salvo el RR)
    - Debe haber alguna forma de detener la simulación. Cuando esto ocurra, el Simulador debe desplegar la siguiente información resumen:
      - Cantidad de procesos ejecutados
      - Cantidad de segundos con CPU ocioso. 
      - Tabla de TAT y WT para los procesos ejecutados
      - Promedio de Waiting Time
      - Promedio de Turn Around Time
    - Puede ser que necesiten otros threads, para llevar tiempos, o para obtener comandos (despliegue cola / detener) de la simulación o para lo que ocupen. No hay problema, pero debe haber al menos los de los Scheduler.
- Diseñe bien la información que debe contener de cada proceso. Piense que tendrá un tipo de PCB para que el CPU Scheduler sepa a quien seleccionar.
- ~Dependiendo de cómo guarde la información de los procesos, pudiera necesitar un semáforo.~

Enlace a la documentación : https://docs.google.com/document/d/1VFjvgt5YmsJe_snunHGSWW_PE-PiR8DsU9gOijt_uzA/edit?usp=sharing
