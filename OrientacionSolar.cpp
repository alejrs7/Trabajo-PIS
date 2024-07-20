#include <stdio.h> // Libreria estandar
#include <math.h>  // Libreria para usar funciones matematicas
#include <time.h>  // Libreria para la fecha
#include <iostream> // Libreria para ordenar algunos datos
#include <ctime>   // Libreria para la hora
#include <windows.h> // Libreria para usar Sleep en milisegundos (solo en sistemas Windows)

struct Orientacion {
    float latitud;
    float longitud;
    float longEstandar;
};

float obtenerNumero(const char* mensaje, int valor) {
    float numero;
    bool band;
    do {
        band = true;
        printf("%s", mensaje);
        if (scanf("%f", &numero) == 1) {
            switch (valor) {
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
        } else {
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

int obtenerSigno(const char* mensaje) {
    char respuesta[4];
    printf("%s (s/n): ", mensaje);
    scanf("%3s", respuesta);
    while (getchar() != '\n'); // Limpiamos los datos residuales

    if (respuesta[0] == 's' || respuesta[0] == 'S') {
        return -1; // Sur u Oeste
    } else if (respuesta[0] == 'n' || respuesta[0] == 'N') {
        return 1; // Norte u Este
    } else {
        printf("Respuesta no valida. Suponiendo Norte/Este.\n");
        return 1; // Default a Norte/Este
    }
}

struct Orientacion ingresarOrientacion() {
    struct Orientacion Datos;

    printf("Ingrese los datos para calcular la posicion del sol en formato grados, minutos, segundos\n");
    printf("Ejemplo: Latitud = grados:3, minutos:59, segundos:35.3, Longitud grados:79, minutos:12, segundos:15.2\n");

    int signoLatitud = obtenerSigno("La latitud esta en el sur?");
    int signoLongitud = obtenerSigno("La longitud esta en el oeste?");

    Datos.latitud = signoLatitud * obtenerDatos("Ingrese la latitud del lugar\n", 1);
    Datos.longitud = signoLongitud * obtenerDatos("Ingrese la longitud del lugar\n", 2);
    Datos.longEstandar = obtenerNumero("Ingrese la longitud estandar del lugar\n", 2);

    return Datos;
}

void FechaActual() {
    std::time_t tiempoActual = std::time(nullptr);
    std::tm* fechaLocal = std::localtime(&tiempoActual);

    int dia = fechaLocal->tm_mday;
    int mes = fechaLocal->tm_mon + 1;
    int anio = fechaLocal->tm_year + 1900;

    printf("Fecha actual: %02d/%02d/%04d\n", dia, mes, anio);
}

int HoraActual() {
    std::time_t tiempoActual = std::time(nullptr);
    std::tm* horaLocal = std::localtime(&tiempoActual);

    int hora = horaLocal->tm_hour;
    int minuto = horaLocal->tm_min;
    int segundo = horaLocal->tm_sec;

    printf("Hora actual: %02d:%02d:%02d\n", hora, minuto, segundo);

    return hora;
}

int DiasTranscurridos() {
    std::time_t tiempoActual = std::time(nullptr);
    std::tm* fechaLocal = std::localtime(&tiempoActual);

    int diasTranscurridos = fechaLocal->tm_yday;
    int diasTotal = diasTranscurridos + 1;

    printf("Dias transcurridos desde el inicio del anio: %d\n", diasTotal);
    return diasTotal;
}

double DeclinacionSolar(int diasTotal) {
    double AnguIncli = -23.44;
    double ReDeclinacion = 0;

    double gradosPorDia = (360.0 / 365.0) * (diasTotal + 10);
    double radianesPorDia = gradosPorDia * (M_PI / 180.0);  // Convertir grados a radianes
    ReDeclinacion = AnguIncli * cos(radianesPorDia);

    printf("La declinacion solar es: %g en grados\n", ReDeclinacion);

    return ReDeclinacion;
}

double EcuacionDelTiempo(int diasTotal) {
    double EoT = 0;
    double B = (360.0 / 365.0) * (diasTotal - 81);
    B = B * (M_PI / 180.0);  // Convertir grados a radianes

    EoT = 9.87 * sin(2 * B) - 7.53 * cos(B) - 1.5 * sin(B);

    printf("La ecuacion del tiempo es: %g minutos\n", EoT);

    return EoT;
}

double TiempoSolarVerdadero(Orientacion orientacion, double EoT, int hora) {
    std::time_t tiempoActual = std::time(nullptr);
    std::tm* horaLocal = std::localtime(&tiempoActual);

    double minuto = horaLocal->tm_min;

    double horaDecimal = hora + (minuto / 60.0);

    double longit = orientacion.longitud;
    double longEs = orientacion.longEstandar;
    double TSV = 0;

    TSV = horaDecimal + (4 * (longit - longEs) + EoT) / 60;

    printf("El tiempo solar verdadero es aproximadamente: %g\n", TSV);

    return TSV;
}

double AnguloAltitudSolar(Orientacion orientacion, double declinacionSolar, double TSV) {
    double lat = orientacion.latitud;
    lat = lat * (M_PI / 180.0);  // Convertir grados a radianes
    double d = declinacionSolar;
    d = d * (M_PI / 180.0);  // Convertir grados a radianes
    double H = 15 * (TSV - 12);
    H = H * (M_PI / 180.0);  // Convertir grados a radianes
    double c = 0;

    c = asin(sin(d) * sin(lat) + cos(d) * cos(lat) * cos(H));

    c = c * (180.0 / M_PI);  // Convertir radianes a grados

    printf("El angulo de altitud solar es: %g en grados\n", c);

    return c;
}

double Azimut(Orientacion orientacion, double declinacionSolar, double anguloAltitudSolar, double TSV) {
    const double formRadianes = M_PI / 180.0;
    double lat = orientacion.latitud;
    lat = lat * formRadianes;  // Convertir grados a radianes
    double d = declinacionSolar;
    d = d * formRadianes;  // Convertir grados a radianes
    double Sa = anguloAltitudSolar;
    Sa = Sa * formRadianes;  // Convertir grados a radianes
    double H = 15 * (TSV - 12);
    H = H * formRadianes;  // Convertir grados a radianes
    double Azi = 0;

    Azi = acos((sin(d) - sin(Sa) * sin(lat)) / (cos(Sa) * cos(lat)));
    Azi = Azi * (180.0 / M_PI);  // Convertir radianes a grados

    if (H > 0) {
        Azi = 360 - Azi;
    }

    printf("El azimut calculado es: %g grados\n", Azi);

    return Azi;
}

int main() {
    Orientacion orientacion = ingresarOrientacion();

    // Abrir archivo para escritura
    FILE* archivo = fopen("datos_sol.txt", "w");
    if (archivo == nullptr) {
        printf("Error al abrir el archivo.\n");
        return 1;
    }

    while (true) {
        FechaActual();
        int hora = HoraActual();

        if (hora >= 18) {
            printf("Se detiene el programa a las 6 de la tarde\n");
            break;
        }

        int diasTranscurridos = DiasTranscurridos();
        double declinacionSolar = DeclinacionSolar(diasTranscurridos);
        double ecuacionDelTiempo = EcuacionDelTiempo(diasTranscurridos);
        double tiempoSolarVerdadero = TiempoSolarVerdadero(orientacion, ecuacionDelTiempo, hora);
        double anguloAltitudSolar = AnguloAltitudSolar(orientacion, declinacionSolar, tiempoSolarVerdadero);
        double azimut = Azimut(orientacion, declinacionSolar, anguloAltitudSolar, tiempoSolarVerdadero);

        // Actualizar el archivo con los datos
        rewind(archivo); // Mover el puntero del archivo al inicio para sobreescribir
        fprintf(archivo, "Azimut: %g\n", azimut);
        fprintf(archivo, "Angulo de Altitud Solar: %g \n", anguloAltitudSolar);

        printf("El azimut calculado es: %g grados\n", azimut);
        printf("#################################################################\n");

        Sleep(60000); // Pausa de 60 segundos antes de la próxima actualización
    }
    fclose(archivo); // Cerrar el archivo
    
    return 0;
}
