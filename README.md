# Trabajo PIS (Proyecto Integrador de Saberes)
Descripción del proyecto:
El proyecto trata de solucionar el problema energético que se ha presentado en el país por ello se ha propuesto realizar un seguidor solar que tiene como objetivo hacer uso de la luz solar para proporcionar energía eléctrica y para ello se ha buscado la forma mas eficiente de hacerlo al no ser solamente un panel solar estático si no que cuente con movimiento y este movimiento se encuentre siempre orientado al sol para general la mayor cantidad de energía posible de la forma más eficiente posible.

 Requisitos:
Software:  
•	Compilador C++
•	Bibliotecas de C++
<stdio.h>: Para entrada y salida estándar.
<math.h>: Para funciones matemáticas.
<time.h> y <ctime>: Para funciones relacionadas con la fecha y hora.
<iostream>: Para manejo de entrada y salida de datos.
•	Sistema Operativo:
•	Unix/Linux: Debido al uso de la función sleep() que es específica para sistemas Unix/Linux.
•	Windows: Con modificaciones para reemplazar sleep() con Sleep() de Windows (incluyendo <windows.h>).
Hardware 
•	Procesador compatible con X86 o 86_64
•	Memoria RAM de al menos 1 GB (no es obligatorio, pero asegura que se puedan hacer que el sistema operativo y otras aplicaciones puedan ejecutarse sin problemas).
•	Al menos 100 MB de espacio libre para el compilador y los archivos del código fuente.
•	Reloj del sistema para proporcionar la fecha y hora actuales.
Intrucciones de instalación 
Uso 
1.	Ejecuta o compila el programa
2.	Ingrese las coordenadas solicitadas:
Ejemplo de Entrada

Ingrese la latitud del lugar:
40.7128
Ingrese la longitud del lugar:
-74.0060
Ingrese la longitud estándar del lugar:
-75.0

   3.	El programa se actualizará cada 5 segundos para mostrar los resultados:
Ejemplo de Salida

Fecha actual: 16/06/2024 
Hora actual: 12:34:56 
Dias transcurridos desde el inicio del anio: 168 
La declinacion solar es: -23.44 en grados 
La ecuacion del tiempo es: 1.234 minutos 
El tiempo solar verdadero es aproximadamente: 12.5678 
El angulo de altitud solar es: 45.6789 en grados 
El azimut calculado es: 123.456 grados #################################################################

     4.	El programa se detendrá a las 18:00 Horas (puede ser modificado)
 Ya que explicamos el funcionamiento del programa les comparto el link directo a este:https://github.com/alejrs7/Trabajo-PIS-Proyecto-Integrador-de-Saberes-/blob/main/OrientacionSolar.cpp
 
 Despues de compartir el link  directo al programa a continuacion se explica como clonar el repositorio de manera correcta:
 a de comandos en tu sistema operativo.
Utiliza el comando git clone seguido de la URL del repositorio. Por ejemplo:
bash
Copiar código
git clone https://github.com/tu_usuario/tu_repositorio.git
Sustituye https://github.com/tu_usuario/tu_repositorio.git con la URL real de tu repositorio en GitHub.
Acceder al Directorio del Repositorio:

Una vez clonado el repositorio, accede al directorio donde se ha clonado. Puedes hacerlo con el comando cd en la terminal:

bash
Copiar código
cd nombre_del_repositorio
Donde nombre_del_repositorio es el nombre del directorio creado después de clonar el repositorio.

Compilar el Código en C++:

Ahora que estás dentro del directorio del repositorio que contiene tu código C++, procede a compilarlo. Asumiremos que el archivo principal se llama OrientacionSolar.cpp.

Para compilar, puedes utilizar el compilador de C++ disponible en tu sistema. Normalmente se utiliza g++ en sistemas UNIX/Linux.
Ejecuta el siguiente comando para compilar:
bash
Copiar código
g++ OrientacionSolar.cpp -o OrientacionSolar
Esto compilará el archivo OrientacionSolar.cpp y generará un archivo ejecutable llamado OrientacionSolar en el mismo directorio.
Ejecutar el Programa Compilado:

Después de compilar sin errores, puedes ejecutar el programa compilado desde la terminal:

bash
Copiar código
./OrientacionSolar
Esto ejecutará el programa OrientacionSolar y comenzará a mostrar la salida en la terminal según lo definido en tu código C++.

Seguir las Instrucciones y Observar la Salida:

El programa solicitará ingresar la latitud, longitud y longitud estándar del lugar.
Mostrará la fecha y hora actual, así como los cálculos astronómicos como la declinación solar, ecuación del tiempo, tiempo solar verdadero, ángulo de altitud solar, y azimut solar.
La ejecución continuará mostrando actualizaciones cada 5 segundos hasta que se detenga manualmente (a las 6 PM según la lógica del código).
Notas Adicionales:
Asegúrate de tener instalado un compilador de C++ en tu sistema. En sistemas UNIX/Linux, g++ es común y está disponible en la mayoría de las distribuciones por defecto.
Verifica que el código C++ (OrientacionSolar.cpp) esté correctamente escrito y no contenga errores de sintaxis antes de compilar.
Los mensajes de salida y cálculos astronómicos se mostrarán en la terminal según lo programado en el código C++.

 


