#include "../lib/global.h"

float velocidad_juego = 1;

bool moverArriba = false;
bool moverAbajo = false;
bool moverDerecha = false;
bool moverIzquierda = false;

GLfloat mouseX = 0;
GLfloat mouseY = 0;
GLfloat mouseY_invertido = 0;

int cantLuces = 1; //la ambiente

bool pausa = false;
bool pararTiempo = false;
bool wireframe = false;
bool texturas_habilitadas = true;
bool audio_habilitado = true;
bool mute = false; //cambiar a false para que inicie con sonido

bool tipoLuz = false; //false = facetado, true = interpolado
bool pantallaCompleta = false;
bool atravesar_paredes = false;

objeto*** estructuras = new objeto * *[largoTablero];
objeto*** bombas = new objeto * *[largoTablero];
//objeto*** enemigos = new objeto * *[largoTablero];
objeto*** fuegos = new objeto * *[largoTablero];
objeto*** bonificadores = new objeto * *[largoTablero];

list<objeto*> borde;
list<particula*> particulas;
list<enemigo*> enemigos;

bomberman* jugador;

door* puerta;
int largoPantalla = WINDOW_WIDTH;
int altoPantalla = WINDOW_HEIGHT;


chrono::duration<int> delta_time;
GLfloat elapsed_time;
chrono::high_resolution_clock::time_point current_t, previous_t;

int getIndiceTablero(GLfloat coord) {
    return int(floor(coord / tile_size));
}

bool fin = false;
bool finJuego = false;
bool inmortal = false;

int nivel = 1;
int puntaje = 0;
int tiempoJuego = 200000; //milisegundos

bool puertaAbierta = false;

void toggle_pausa() {
    pausa = !pausa;
    pararTiempo = !pararTiempo;
}

void toggle_wireframe() {
    wireframe = !wireframe;
}

void toggle_texturas() {
    texturas_habilitadas = !texturas_habilitadas;
}

void toggle_tipoLuz() {
    tipoLuz = !tipoLuz;
}

void toggle_pantallaCompleta() {
    pantallaCompleta = !pantallaCompleta;
}

void toggle_inmortal() {
    inmortal = !inmortal;
}

void toggle_atravesar_paredes() {
    atravesar_paredes = !atravesar_paredes;
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
    tiempoJuego -= int(elapsed_time);
    if (tiempoJuego <= 0) {
        tiempoJuego = 0;
        finJuego = true;
    }
}

void pausarTiempo() {
    pararTiempo = !pararTiempo;
}