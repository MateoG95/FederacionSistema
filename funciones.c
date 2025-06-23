#include <stdio.h>
#include <string.h>
#include "funciones.h"

int menu() {
    int opc;
    printf("\nMenu de opciones:\n");
    printf("1. Cargar Equipos\n");
    printf("2. Ver Equipos\n");
    printf("3. Registrar Partido\n");
    printf("4. Listar Partidos\n");
    printf("5. Buscar Equipo\n");
    printf("6. Ver Goleador de un Partido\n");
    printf("7. Ver Goleador del Torneo\n");
    printf("8. Guardar Datos del Torneo\n");
    printf("9. Ver Resultados del Torneo\n");
    printf("10. Salir\n");
    printf("Ingrese una opcion: ");
    scanf("%d", &opc);
    return opc;
}

void cargarEquipos(struct Equipo equipos[4]) {
    strcpy(equipos[0].nombre, "Tiburones");
    char jugadoresT[8][30] = {"Carlos", "Juan", "Luis", "Andres", "Pedro", "Mario", "Ricardo", "Erick"};
    for (int i = 0; i < 8; i++) {
        strcpy(equipos[0].jugadores[i].nombre, jugadoresT[i]);
        equipos[0].jugadores[i].golesTotales = 0;
    }

    strcpy(equipos[1].nombre, "Churos");
    char jugadoresC[8][30] = {"Bryan", "Mateo", "Dario", "Jorge", "Sebas", "Tomas", "Hugo", "Eloy"};
    for (int i = 0; i < 8; i++) {
        strcpy(equipos[1].jugadores[i].nombre, jugadoresC[i]);
        equipos[1].jugadores[i].golesTotales = 0;
    }

    strcpy(equipos[2].nombre, "EncebolladoFC");
    char jugadoresE[8][30] = {"Samuel", "Milton", "David", "Cristian", "Ronald", "Esteban", "Alex", "Steven"};
    for (int i = 0; i < 8; i++) {
        strcpy(equipos[2].jugadores[i].nombre, jugadoresE[i]);
        equipos[2].jugadores[i].golesTotales = 0;
    }

    strcpy(equipos[3].nombre, "Cupidos");
    char jugadoresP[8][30] = {"Kevin", "Roberto", "Danilo", "Felipe", "Alexis", "Fidel", "Henry", "Brian"};
    for (int i = 0; i < 8; i++) {
        strcpy(equipos[3].jugadores[i].nombre, jugadoresP[i]);
        equipos[3].jugadores[i].golesTotales = 0;
    }
}

void verEquipos(struct Equipo equipos[4]) {
    for (int i = 0; i < 4; i++) {
        printf("Equipo %d: %s\n", i + 1, equipos[i].nombre);
        for (int j = 0; j < 8; j++) {
            printf("  Jugador %d: %s\n", j + 1, equipos[i].jugadores[j].nombre);
        }
        printf("--------------------------------------\n");
    }
}

void registrarPartido(struct Partido partidos[], int *cont, struct Equipo equipos[4]) {
    if (*cont >= 10) {
        printf("Limite de partidos alcanzado.\n");
        return;
    }

    int eq1, eq2;
    printf("Seleccione equipo 1 (0-3): ");
    scanf("%d", &eq1);
    printf("Seleccione equipo 2 (0-3): ");
    scanf("%d", &eq2);

    if (eq1 == eq2 || eq1 < 0 || eq2 < 0 || eq1 > 3 || eq2 > 3) {
        printf("Seleccion invalida.\n");
        return;
    }

    for (int i = 0; i < *cont; i++) {
        if ((strcmp(partidos[i].equipo1, equipos[eq1].nombre) == 0 && strcmp(partidos[i].equipo2, equipos[eq2].nombre) == 0) ||
            (strcmp(partidos[i].equipo1, equipos[eq2].nombre) == 0 && strcmp(partidos[i].equipo2, equipos[eq1].nombre) == 0)) {
            printf("Estos equipos ya jugaron.\n");
            return;
        }
    }

    strcpy(partidos[*cont].equipo1, equipos[eq1].nombre);
    strcpy(partidos[*cont].equipo2, equipos[eq2].nombre);

    printf("Goles %s: ", equipos[eq1].nombre);
    scanf("%d", &partidos[*cont].goles1);
    printf("Goles %s: ", equipos[eq2].nombre);
    scanf("%d", &partidos[*cont].goles2);

    int totalGoles = partidos[*cont].goles1 + partidos[*cont].goles2;
    int golesRegistrados = 0;
    partidos[*cont].totalGoleadores = 0;

    while (golesRegistrados < totalGoles) {
        char nombre[30];
        int goles, equipoNum;
        printf("Ingrese nombre del jugador que anoto: ");
        fflush(stdin);
        fgets(nombre, 30, stdin);
        nombre[strcspn(nombre, "\n")] = 0;
        printf("Equipo del jugador (0-3): ");
        scanf("%d", &equipoNum);
        printf("Cuantos goles metio: ");
        scanf("%d", &goles);

        int encontrado = 0;
        for (int j = 0; j < 8; j++) {
            if (strcmp(equipos[equipoNum].jugadores[j].nombre, nombre) == 0) {
                equipos[equipoNum].jugadores[j].golesTotales += goles;
                partidos[*cont].goleadores[partidos[*cont].totalGoleadores] = equipos[equipoNum].jugadores[j];
                partidos[*cont].goleadores[partidos[*cont].totalGoleadores].golesTotales = goles;
                partidos[*cont].totalGoleadores++;
                golesRegistrados += goles;
                encontrado = 1;
                break;
            }
        }
        if (!encontrado) {
            printf("Jugador no encontrado en el equipo.\n");
        }
    }

    (*cont)++;
    printf("Partido registrado correctamente.\n");
}

void listarPartidos(struct Partido partidos[], int total) {
    for (int i = 0; i < total; i++) {
        printf("Partido %d: %s vs %s | %d - %d\n", i + 1,
               partidos[i].equipo1, partidos[i].equipo2,
               partidos[i].goles1, partidos[i].goles2);
    }
}

void buscarEquipo(struct Equipo equipos[4]) {
    char nombre[30];
    printf("Ingrese el nombre del equipo a buscar: ");
    fflush(stdin);
    fgets(nombre, 30, stdin);
    nombre[strcspn(nombre, "\n")] = 0;

    for (int i = 0; i < 4; i++) {
        if (strcmp(equipos[i].nombre, nombre) == 0) {
            printf("Equipo encontrado: %s\n", equipos[i].nombre);
            for (int j = 0; j < 8; j++) {
                printf("Jugador: %s | Goles: %d\n",
                       equipos[i].jugadores[j].nombre,
                       equipos[i].jugadores[j].golesTotales);
            }
            return;
        }
    }
    printf("Equipo no encontrado.\n");
}

void verGoleadorPartido(struct Partido partidos[], int total) {
    listarPartidos(partidos, total);
    int index;
    printf("Seleccione el numero de partido: ");
    scanf("%d", &index);
    index--;

    if (index < 0 || index >= total) {
        printf("Partido no valido.\n");
        return;
    }

    struct Jugador *goleador = &partidos[index].goleadores[0];
    for (int i = 1; i < partidos[index].totalGoleadores; i++) {
        if (partidos[index].goleadores[i].golesTotales > goleador->golesTotales) {
            goleador = &partidos[index].goleadores[i];
        }
    }

    printf("Goleador del Partido %s vs %s:\n", partidos[index].equipo1, partidos[index].equipo2);
    printf("Jugador: %s | Goles: %d\n", goleador->nombre, goleador->golesTotales);
}

void verGoleadorTorneo(struct Equipo equipos[4]) {
    struct Jugador *goleador = NULL;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 8; j++) {
            if (!goleador || equipos[i].jugadores[j].golesTotales > goleador->golesTotales) {
                goleador = &equipos[i].jugadores[j];
            }
        }
    }

    if (goleador) {
        printf("Goleador del torneo: %s con %d goles.\n", goleador->nombre, goleador->golesTotales);
    } else {
        printf("No hay goles registrados.\n");
    }
}

void guardarTorneo(struct Equipo equipos[4], struct Partido partidos[], int totalPartidos) {
    FILE *f = fopen("torneo.txt", "w");
    if (!f) {
        printf("Error al abrir el archivo para guardar el torneo.\n");
        return;
    }

    fprintf(f, "=== DATOS DE EQUIPOS ===\n");
    for (int i = 0; i < 4; i++) {
        fprintf(f, "Equipo: %s\n", equipos[i].nombre);
        for (int j = 0; j < 8; j++) {
            fprintf(f, " - Jugador: %s | Goles: %d\n",
                    equipos[i].jugadores[j].nombre,
                    equipos[i].jugadores[j].golesTotales);
        }
        fprintf(f, "-----------------------------\n");
    }

    fprintf(f, "\n=== PARTIDOS REGISTRADOS ===\n");
    for (int i = 0; i < totalPartidos; i++) {
        fprintf(f, "Partido %d: %s vs %s | Resultado: %d - %d\n",
                i + 1,
                partidos[i].equipo1,
                partidos[i].equipo2,
                partidos[i].goles1,
                partidos[i].goles2);

        fprintf(f, "  Goleadores:\n");
        for (int j = 0; j < partidos[i].totalGoleadores; j++) {
            fprintf(f, "   - %s: %d goles\n",
                    partidos[i].goleadores[j].nombre,
                    partidos[i].goleadores[j].golesTotales);
        }
    }

    fclose(f);
    printf("Torneo guardado en 'torneo.txt'\n");
}

void verResultadosTorneo(struct Partido partidos[], int totalPartidos) {
    FILE *f = fopen("torneo.txt", "r");
    if (!f) {
        printf("No hay resultados guardados.\n");
        return;
    }
    char linea[200];
    while (fgets(linea, sizeof(linea), f)) {
        printf("%s", linea);
    }
    fclose(f);
}

    }
    fclose(f);
}
