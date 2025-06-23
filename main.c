#include <stdio.h>
#include <string.h>
#include "funciones.h"

int main() {
    struct Equipo equipos[4];
    struct Partido partidos[10];
    int totalPartidos = 0;
    int cargado = 0;
    int opc;
    

    printf("========================================\n");
    printf("     SISTEMA DE LA FEDERACION EFC       \n");
    printf("========================================\n");

    do {
        opc = menu();
        switch(opc) {
            case 1:
                printf("Los equipos ya estan precargados.\n");
                break;
            case 2:
                verEquipos(equipos); // corregido
                break;
            case 3:
                registrarPartido(partidos, &totalPartidos, equipos); // corregido
                break;
            case 4:
                listarPartidos(partidos, totalPartidos);
                break;
            case 5:
                buscarEquipo(equipos); // corregido
                break;
            case 6:
                verGoleadorPartido(partidos, totalPartidos);
                break;
            case 7:
                verGoleadorTorneo(equipos); // corregido
                break;
            case 8:
                guardarTorneo(equipos, partidos, totalPartidos);
                break;
            case 9:
                verResultadosTorneo(partidos, totalPartidos);
                break;
            case 10:
                printf("Saliendo del sistema...\n");
                break;
            default:
                printf("Opcion invalida.\n");
        }
    } while (opc != 10);

    return 0;
}
