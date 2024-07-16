#include <stdio.h> // Libreria estandar
#include <math.h>// Libreria para usar funciones matematicas
#include <time.h>// Libreria para la fecha
#include <iostream>// Libreria para ordenar algunos datos
#include <ctime>// Libreria para la hora
#include <unistd.h> //Libreria para usar sleep en segundos (solo en sistemas Unix/Linux)

struct Orientacion {// Struct para guardar la latitud y longitud
    float latitud;//Variable para almacenar la latitud
    float longitud;//Variable para almacenar la longitud
    float longEstandar;//Variable para la longitud estandar esta se calcula con -5 *15 por nuestra region
};

float obtenerNumero(const char* mensaje, int valor) {//funcion para verificar que no ingresen letras en lugar de numeros
    float numero;//Variable donde ingresaremos los datos
    bool band;
    do {//Validamos si ingreso un numero o letra
        band = true;
        printf("%s", mensaje);
        if (scanf("%f", &numero) == 1) {//Si no ingreso letras el programa continua como corresponde
            switch (valor)
            {
                case 1:
                    if (numero < -90 || numero > 90 ) {
                        printf("Error: dato no valido. Por favor, ingrese un numero entre -90 y 90.\n");
                        band = false;
                    }
                    break;
                case 2:
                    if(numero < -180 || numero > 180) {
                        printf("Error: dato no valido. Por favor, ingrese un numero entre -180 y 180.\n");
                        band = false;
                    }
                    break;
                case 3:
                    if(numero < 0 || numero > 60) {
                        printf("Error: dato no valido. Por favor, ingrese un numero entre 0 y 60.\n");
                        band = false;
                    }
                    break;
            }
            while (getchar() != '\n'); // Limpiamos los datos residuales que pudieran quedar
        } else {//En caso de haber ingresado letras saltara un error hasta que se corriga el error
            printf("Error no se puede ingresar letras. Por favor, ingrese un numero.\n");
            while (getchar() != '\n'); // Limpiamos los datos residuales que pudieran quedar
            band = false;
        }
    } while(!band);
    return numero;
}

float obtenerDatos(const char* mensaje, int valor) {
    float grados;
    float min;
    float seg;
    float result;

    printf("%s", mensaje);
    grados = obtenerNumero("ingrese los grados: ", valor);
    min = obtenerNumero("ingresar los minutos: ", 3);
    seg = obtenerNumero("ingresar los segundos: ", 3);
    result = grados + (min/60) + (seg/3600);
    return result;
}

struct Orientacion ingresarOrientacion()//Estructura para Ingresar los datos 
{
    struct Orientacion Datos;//Indicamos donde hubicaremos y guardaremos la informacion que ingresemos

    printf("Ingrese los datos para calcular la posicion del sol en formato grados, minutos, segundos\n");
    printf("Ejemplo: Latitud = grados:3, minutos:59, segundos:35.3, Longitud grados:79, minutos:12, segundos:15.2\n");
    Datos.latitud = obtenerDatos("Ingrese la latitud del lugar\n", 1);
    Datos.longitud = obtenerDatos("Ingrese la longitud del lugar\n", 2);
    Datos.longEstandar = obtenerNumero("Ingrese la longitud estandar del lugar\n", 2);

    return Datos;
}

void FechaActual() {  // Funcion para obtener la fecha
    std::time_t tiempoActual = std::time(nullptr);/*Obtenemos el tiempo actual en segundos y lo guardamos en la variable tiempo actual,
    std::time(nullptr) esto devuelve el tiempo en segundos desde epoch que es el 1 de enero de 1970*/
    std::tm* fechaLocal = std::localtime(&tiempoActual);/*se utiliza la función std::localtime para convertir 
    el tiempo en formato std::time_t a una estructura std::tm que representa la fecha y hora local del sistema.*/ 

    int dia = fechaLocal->tm_mday;//El campo tm_mday representa el día del mes (1-31).
    int mes = fechaLocal->tm_mon + 1; /*se extrae el mes del año de la estructura std::tm.
    hay una correccion de +1 ya que tm_mon representa los meses desde 0 hasta 11,
    por lo que se suma 1 para obtener el número real del mes (1-12).*/ 
    int anio = fechaLocal->tm_year + 1900; /*se obtiene el año actual de la estructura std::tm. 
    hay una corrección de +1900 porque tm_year representa los años desde 1900. 
    Por lo tanto, sumando 1900 se obtiene el año actual en el formato normal*/ 

    printf("Fecha actual: %02d/%02d/%04d\n", dia, mes, anio);
}

int HoraActual() {  // Funcion para la hora actual
    std::time_t tiempoActual = std::time(nullptr);/*Obtenemos el tiempo actual en segundos y lo guardamos en la variable tiempo actual,
    std::time(nullptr) esto devuelve el tiempo en segundos desde epoch que es el 1 de enero de 1970*/
    std::tm* horaLocal = std::localtime(&tiempoActual);/*Utilizamos la funcion std::localtime para convertir el tiempo en formato
    std::time_t a una estructura std::tm lo que representa la hora local del sistema*/

    int hora = horaLocal->tm_hour;/*extraemos los componentes de la hora como hora, minutos y segundos de la estructura std::tm */
    int minuto = horaLocal->tm_min;
    int segundo = horaLocal->tm_sec;

    printf("Hora actual: %02d:%02d:%02d\n", hora, minuto, segundo);//Presentamos la hora, minuto y segundos

    return hora; //Regresamos la hora 
}

int DiasTranscurridos() {  // Funcion para contar los dias desde el inicio del año
    std::time_t tiempoActual = std::time(nullptr);/*Obtenemos el tiempo actual en segundos y lo guardamos en la variable tiempo actual,
    std::time(nullptr) esto devuelve el tiempo en segundos desde epoch que es el 1 de enero de 1970*/

    std::tm* fechaLocal = std::localtime(&tiempoActual);/*se utiliza la función std::localtime para convertir 
    el tiempo en formato std::time_t a una estructura std::tm que representa la fecha y hora local del sistema.*/ 

    int diasTranscurridos = fechaLocal->tm_yday;/*es un campo de la estructura std::tm que representa 
    el numero de dias transcurridos desde el inicio del año*/ 
    int diasTotal = diasTranscurridos + 1;/*Se suma 1 al numero de dias transcurridos para obtener el numero total de dias transcurridos 
    desde el inicio del año hasta la fecha actual.Esto se hace porque tm_yday comienza desde 0, por lo que sumar 1 lo ajusta.*/

    printf("Dias transcurridos desde el inicio del anio: %d\n", diasTotal);
    return diasTotal;
}

double DeclinacionSolar(int diasTotal) {// Funcion de la declinacion solar
    double AnguIncli = -23.44;// angulo de la inclinacion del eje de la Tierra
    double ReDeclinacion = 0;// Donde realizamos la operacion

    double radianesPorDia = ((360/365) * (diasTotal + 10)) * (M_PI / 180);  // Conversion a radianes
    ReDeclinacion = AnguIncli * cos(radianesPorDia);// Formula declinacion solar usando los dias totales
    
    printf("La declinacion solar es: %g en grados\n", ReDeclinacion);

    return ReDeclinacion;
}

double EcuacionDelTiempo(int diasTotal) {// Funcion de la ecuacion del tiempo en minutos
    double EoT = 0;// Ecuacion del tiempo en minutos
    double B = (360.0 / 365.0) * (diasTotal - 81);// angulo en grados
    B = B * (M_PI / 180.0);// Convertir a radianes

    EoT = 9.87 * sin(2 * B) - 7.53 * cos(B) - 1.5 * sin(B); //formula de la ecuacion del tiempo

    printf("La ecuacion del tiempo es: %g minutos\n", EoT);

    return EoT;
}

double TiempoSolarVerdadero(Orientacion orientacion, double EoT, int hora) {//funcion del tiempo solar verdadero
    std::time_t tiempoActual = std::time(nullptr);/*Obtenemos el tiempo actual en segundos y lo guardamos en la variable tiempo actual,
    std::time(nullptr) esto devuelve el tiempo en segundos desde epoch que es el 1 de enero de 1970*/

    std::tm* horaLocal = std::localtime(&tiempoActual);/*Utilizamos la funcion std::localtime para convertir el tiempo en formato
    std::time_t a una estructura std::tm lo que representa la hora local del sistema*/


    double minuto = horaLocal->tm_min;/*extraemos los componentes de la hora como hora, minutos y segundos de la estructura std::tm */
    double segundo = horaLocal->tm_sec;

    double horaDecimal = hora + (minuto / 60.0) + (segundo / 3600.0);// Hora local en decimales

    double longit = orientacion.longitud;//Variable para poder usar la longitud que ingresamos
    double longEs = orientacion.longEstandar;//Variable para poder usar la longitud estandar que ingresamos
    double TSV = 0;//Variable donde haremos las operaciones

    TSV = horaDecimal + (4 * (longit - longEs) + EoT) / 60;//Formula del tiempo solar verdadero

    printf("El tiempo solar verdadero es aproximadamente: %g\n", TSV);

    return TSV;
}

double AnguloAltitudSolar(Orientacion orientacion, double declinacionSolar, double TSV) {//funcion para el angulo de altitud solar

    double lat = orientacion.latitud;//Variable para poder usar la latitud que ingresamos
    lat = lat * (M_PI / 180.0);// Convertimos a radianes
    double d = declinacionSolar;//Variable para poder usar la declinacion solar
    d = d * (M_PI / 180.0);// Convertimos a radianes
    double H = 15 * (TSV - 12);// Hora solar local
    H = H * (M_PI / 180.0);// Convertimos a radianes
    double c = 0;  //angulo de la altitud solar

    c = asin(sin(d) * sin(lat) + cos(d) * cos(lat) * cos(H));//formula del angulo de altitud solar

    c = c * (180.0 / M_PI);// Convertimos a grados

    printf("El angulo de altitud solar es: %g en grados\n", c);

    return c;
}

double Azimut(Orientacion orientacion,double declinacionSolar, double anguloAltitudSolar, double TSV) {//Funcion para el azimut 

    const double formRadianes = M_PI / 180.0;
    double lat = orientacion.latitud;//Variable para usar la latitud
    lat = lat * formRadianes;
    double d = declinacionSolar;//Variable para usar la declinacion solar
    d = d * formRadianes;
    double Sa = anguloAltitudSolar;//Variable para usar el angulo de altitud solar
    Sa = Sa * formRadianes;
    double H = 15 * (TSV - 12); // Hora solar local
    double Azi = 0;//Variable donde haremos las operaciones

    //Formula para calcular el zimut pasando los datos a radianes
    Azi = acos((sin(d) - sin(Sa) * sin(lat)) / (cos(Sa) * cos(lat)));
    Azi = Azi * (180.0 / M_PI);  // Convertimos a grados

    if (H > 0) {
        Azi = 360 - Azi; // Ajuste del azimut
    }

    return Azi;
}

int main() {//Presentamos los valores calculados

    Orientacion orientacion = ingresarOrientacion(); //llamamos a la estructura y las funciones que vamos a presentar

    while (true) {//bucle para mostrar los resultados cada 5 segundos

        FechaActual();
        int hora = HoraActual();

        if (hora >= 18)//condicional para detener la ejecucion del programa a la hora que se oculta el sol
        {
            printf("Se detiene el programa a las 6 de la tarde\n");
            break;
        }

        int diasTranscurridos = DiasTranscurridos();
        double declinacionSolar = DeclinacionSolar(diasTranscurridos);
        double ecuacionDelTiempo = EcuacionDelTiempo(diasTranscurridos);
        double tiempoSolarVerdadero = TiempoSolarVerdadero(orientacion, ecuacionDelTiempo, hora);
        double anguloAltitudSolar = AnguloAltitudSolar(orientacion, declinacionSolar, tiempoSolarVerdadero);
        double azimut = Azimut(orientacion, declinacionSolar, anguloAltitudSolar, tiempoSolarVerdadero);
        printf("El azimut calculado es: %g grados\n", azimut);
        printf("#################################################################\n");//mostramos un espacio para separar las actualizaciones

        sleep(60);//Pausa de 60 segundos antes de la proxima actualizacion
    }
    return 0;
}
