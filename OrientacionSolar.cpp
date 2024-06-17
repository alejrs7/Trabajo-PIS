#include <stdio.h> // Libreria estandar
#include <math.h>// Libreria para usar funciones matematicas
#include <time.h>// Libreria para la fecha
#include <iostream>// Libreria para ordenar algunos datos
#include <ctime>// Libreria para la hora
#include <unistd.h> // Librería para usar sleep en segundos (solo en sistemas Unix/Linux)


struct Orientacion {// Struct para guardar la latitud y longitud
    float latitud;
    float longitud; 
    float longEstandar;//Esta se calcula con -5 *15
};

struct Orientacion ingresarOrientacion()
{
    struct Orientacion Datos;

    printf("Ingrese la latitud del lugar\n");
    scanf("%f", &Datos.latitud);
    printf("Ingrese la longitud del lugar\n");
    scanf("%f", &Datos.longitud);
    printf("Ingrese la longitud estandar del lugar\n");
    scanf("%f", &Datos.longEstandar);

    return Datos;
}




void FechaActual() {  // Funcion para obtener la fecha
    std::time_t tiempoActual = std::time(nullptr);
    std::tm* fechaLocal = std::localtime(&tiempoActual);

    int dia = fechaLocal->tm_mday;
    int mes = fechaLocal->tm_mon + 1; // tm_mon esta en el rango 0-11
    int anio = fechaLocal->tm_year + 1900; // tm_year cuenta desde 1900

    printf("Fecha actual: %02d/%02d/%04d\n", dia, mes, anio);
}

int HoraActual() {  // Funcion para la hora actual
    std::time_t tiempoActual = std::time(nullptr);
    std::tm* horaLocal = std::localtime(&tiempoActual);

    int hora = horaLocal->tm_hour;
    int minuto = horaLocal->tm_min;
    int segundo = horaLocal->tm_sec;

    printf("Hora actual: %02d:%02d:%02d\n", hora, minuto, segundo);

    return hora; 
}

int DiasTranscurridos() {  // Funcion para contar los dias desde el inicio del año
    std::time_t tiempoActual = std::time(nullptr);
    std::tm* fechaLocal = std::localtime(&tiempoActual);

    int diasTranscurridos = fechaLocal->tm_yday;
    int diasTotal = diasTranscurridos + 1;

    printf("Dias transcurridos desde el inicio del anio: %d\n", diasTotal);
    return diasTotal;
}

double DeclinacionSolar(int diasTotales) {// Funcion de la declinacion solar
    double AnguIncli = -23.44;// angulo de la inclinacion del eje de la Tierra
    double ReDeclinacion = 0;// Donde realizamos la operacion

    double radianesPorDia = 2 * M_PI / 365;  // Conversion a radianes
    ReDeclinacion = AnguIncli * cos(radianesPorDia * (diasTotales + 10));  // Formula declinacion solar
    
    printf("La declinacion solar es: %g en grados\n", ReDeclinacion);

    return ReDeclinacion;
}

double EcuacionDelTiempo(int dias) {// Funcion de la ecuacion del tiempo en minutos
    double EoT = 0;// Ecuacion del tiempo en minutos
    double B = (360.0 / 365.0) * (dias - 81);// angulo en grados
    B = B * (M_PI / 180.0);// Convertir a radianes

    EoT = 9.87 * sin(2 * B) - 7.53 * cos(B) - 1.5 * sin(B); //formula de la ecuacion del tiempo

    printf("La ecuacion del tiempo es: %g minutos\n", EoT);

    return EoT;
}

double TiempoSolarVerdadero(Orientacion orientacion, double EoT, int hora) {//funcion del tiempo solar verdadero
    std::time_t tiempoActual = std::time(nullptr);
    std::tm* horaLocal = std::localtime(&tiempoActual);


    double minuto = horaLocal->tm_min;
    double segundo = horaLocal->tm_sec;

    double horaDecimal = hora + (minuto / 60.0) + (segundo / 3600.0);// Hora local en decimales

    double longit = orientacion.longitud;
    double longEs = orientacion.longEstandar;
    double TSV = 0;

    TSV = horaDecimal + (4 * (longit - longEs) + EoT) / 60;//Formula del tiempo solar verdadero

    printf("El tiempo solar verdadero es aproximadamente: %g\n", TSV);

    return TSV;
}

double AnguloAltitudSolar(Orientacion orientacion, double declinacionSolar, double TSV) {//funcion para el angulo de altitud solar

    double lat = orientacion.latitud;
    lat = lat * (M_PI / 180.0);// Convertimos a radianes
    double d = declinacionSolar;
    d = d * (M_PI / 180.0);// Convertimos a radianes
    double H = 15 * (TSV - 12);// Hora solar local
    H = H * (M_PI / 180.0);// Convertimos a radianes
    double c = 0;  //angulo de la altitud solar

    c = asin(sin(d) * sin(lat) + cos(d) * cos(lat) * cos(H));//formula del angulo de altitud solar

    c = c * (180.0 / M_PI);// Convertimos a grados

    printf("El angulo de altitud solar es: %g en grados\n", c);

    return c;
}

double Azimut(Orientacion orientacion,double declinacionSolar, double anguloAltitudSolar) {//Funcion para el azimut 

    double lat = orientacion.latitud;
    double d = declinacionSolar;
    double Sa = anguloAltitudSolar;

    double Azi = 0;
    //Formula para calcular el zimut pasando los datos a radianes
    Azi = acos((sin(d * (M_PI / 180.0)) - sin(Sa * (M_PI / 180.0)) * sin(lat * (M_PI / 180.0))) / (cos(Sa * (M_PI / 180.0)) * cos(lat * (M_PI / 180.0))));
    Azi = Azi * (180.0 / M_PI);  // Convertimos a grados


    return Azi;
}

int main() {//Presentamos los valores calculados

    Orientacion orientacion = ingresarOrientacion();

    while (true) {
        FechaActual();
        int hora = HoraActual();
        int diasTranscurridos = DiasTranscurridos();
        double declinacionSolar = DeclinacionSolar(diasTranscurridos);
        double ecuacionDelTiempo = EcuacionDelTiempo(diasTranscurridos);
        double tiempoSolarVerdadero = TiempoSolarVerdadero(orientacion, ecuacionDelTiempo, hora);
        double anguloAltitudSolar = AnguloAltitudSolar(orientacion, declinacionSolar, tiempoSolarVerdadero);
        double azimut = Azimut(orientacion, declinacionSolar, anguloAltitudSolar);
        printf("El azimut calculado es: %g grados\n", azimut);
        printf("#################################################################\n");

        sleep(5); // Pausa de 5 segundos antes de la próxima actualización
    }
    return 0;
}
