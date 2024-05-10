#include "../lib/global.h"

float velocidad_juego = 1.0f;

bool moverArriba = false;
bool moverAbajo = false;
bool moverDerecha = false;
bool moverIzquierda = false;

bool pausa = true;
bool pararTiempo = false;
bool wireframe = false;
bool texturas_habilitadas = true;
bool mute = false; //cambiar a false para que inicie con sonido
bool mostrarHud = true;
bool inmortal = false;

bool tipoLuz = true; //false = facetado, true = interpolado
bool atravesar_paredes = false;

objeto*** estructuras = new objeto * *[largoTablero];
objeto*** bombas = new objeto * *[largoTablero];
objeto*** fuegos = new objeto * *[largoTablero];
objeto*** bonificadores = new objeto * *[largoTablero];

list<objeto*> borde;
list<particula*> particulas;
list<enemigo*> enemigos;

bomberman* jugador;

door* puerta;

GLfloat tiempo_entre_frames;
chrono::high_resolution_clock::time_point marca_tiempo_anterior, marca_tiempo_actual;

bool fin = false;
bool finJuego = false;

int nivel = 1;
int puntaje = 0;
int tiempoJuego = 200000; //milisegundos
bool puertaAbierta = false;
bool temporizador = false;

int getIndiceTablero(GLfloat coord) {
    return int(floor(coord / tile_size));
}

void toggle(bool &valor){
    valor = !valor;
}

void aumentarNivel() {
    nivel++;
    tiempoJuego = 200000;
    if (nivel >= INT_MAX) {
        nivel = INT_MAX;
    }
}

void sumarPuntaje(int puntos) {
    puntaje += puntos;
    if (puntos > INT_MAX) {
        puntos = INT_MAX;
    }
}

void disminuirTiempo(GLfloat milisegundos){
    tiempoJuego -= int(tiempo_entre_frames);
    if (tiempoJuego <= 0) {
        tiempoJuego = 0;
        finJuego = true;
    }
}