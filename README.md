# Avance PIS (Proyecto Integrador de Saberes)
Descripción del proyecto:
El proyecto tiene como objetivo solucionar el problema energético del país mediante el desarrollo de un seguidor solar. Este sistema utiliza la luz solar para proporcionar energía eléctrica de manera más eficiente, ajustando la orientación de los paneles solares para maximizar la captación de energía.
  Requisitos:
  
Software

Compilador C++

Bibliotecas de C++:

<stdio.h>: Para entrada y salida estándar.

<math.h>: Para funciones matemáticas.

<time.h>: Para funciones relacionadas con la fecha y hora.

<iostream>: Para manejo de entrada y salida de datos.
Sistema Operativo
Unix/Linux: Recomendado debido al uso de la función sleep() específica para estos sistemas.
Windows: Con modificaciones para reemplazar sleep() con Sleep() de Windows (incluyendo <windows.h>).
Hardware
Procesador: Compatible con X86 o 86_64
Memoria RAM: Al menos 1 GB (no obligatorio, pero asegura mejor rendimiento).
Espacio Libre: Al menos 100 MB para el compilador y archivos del código fuente.
Reloj del sistema: Para proporcionar la fecha y hora actuales.
Instrucciones de Instalación y Uso
Clonar el Repositorio
Abre una terminal en tu sistema operativo.
Usa el comando git clone seguido de la URL del repositorio:
bash
Copiar código

git clone https://github.com/alejrs7/Avance-PIS-.git
Accede al directorio del repositorio clonado:
bash
Copiar código

cd Avance-Pis
Compilar el Código en C++
Una vez dentro del directorio, compila el archivo principal OrientacionSolar.cpp:
bash
Copiar código
g++ OrientacionSolar.cpp -o OrientacionSolar
Ejecutar el Programa Compilado
Ejecuta el programa compilado:
bash
Copiar código
./OrientacionSolar
Seguir las Instrucciones y Observar la Salida
El programa solicitará ingresar la latitud, longitud y longitud estándar del lugar:
plaintext
Copiar código
Ingrese la latitud del lugar: 40.7128
Ingrese la longitud del lugar: -74.0060
Ingrese la longitud estándar del lugar: -75.0
Mostrará la fecha y hora actual, y realizará cálculos astronómicos como la declinación solar, ecuación del tiempo, tiempo solar verdadero, ángulo de altitud solar y azimut solar.
La salida se actualizará cada 5 segundos hasta detenerse manualmente o a las 6 PM según la lógica del código.
Ejemplo de Entrada
plaintext
Copiar código
Ingrese la latitud del lugar: 40.7128
Ingrese la longitud del lugar: -74.0060
Ingrese la longitud estándar del lugar: -75.0
Ejemplo de Salida
plaintext
Copiar código
Fecha actual: 16/06/2024
Hora actual: 12:34:56
Días transcurridos desde el inicio del año: 168
La declinación solar es: -23.44 grados
La ecuación del tiempo es: 1.234 minutos
El tiempo solar verdadero es aproximadamente: 12.5678
El ángulo de altitud solar es: 45.6789 grados
El azimut calculado es: 123.456 grados
Notas Adicionales
Asegúrate de tener instalado un compilador de C++ en tu sistema (g++ es común en UNIX/Linux).
Verifica que el archivo OrientacionSolar.cpp esté correctamente escrito y sin errores de sintaxis antes de compilar.
Los mensajes de salida y cálculos astronómicos se mostrarán en la terminal según lo programado en el código C++
Aqui les comparto el enlace directo al contenido de nuestro algoritmo y los elementos que empleamos del lenguaje c/c++ para que el avance nuestro Proyecto PiS:https://github.com/alejrs7/Avance-PIS/blob/main/OrientacionSolar.cpp


