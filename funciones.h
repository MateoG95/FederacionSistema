

struct Jugador {
    char nombre[30];
    int golesTotales;
};

struct Equipo {
    char nombre[30];
    struct Jugador jugadores[8];
};

struct Partido {
    char equipo1[30];
    char equipo2[30];
    int goles1;
    int goles2;
    struct Jugador goleadores[16];
    int totalGoleadores;
};

void guardarEquipos(struct Equipo equipos[4]);
void cargarEquipos(struct Equipo equipos[4]);
void verEquipos(struct Equipo equipos[4]);
void registrarPartido(struct Partido partidos[], int *cont, struct Equipo equipos[4]);
void listarPartidos(struct Partido partidos[], int total);
void buscarEquipo(struct Equipo equipos[4]);
void verGoleadorPartido(struct Partido partidos[], int total);
void verGoleadorTorneo(struct Equipo equipos[4]);
void guardarTorneo(struct Equipo equipos[4], struct Partido partidos[], int totalPartidos);
void verResultadosTorneo(struct Partido partidos[], int totalPartidos);
int menu();
