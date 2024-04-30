#include "../lib/global.h"

int velocidad_juego = 1;

bool moverArriba = false;
bool moverAbajo = false;
bool moverDerecha = false;
bool moverIzquierda = false;

int mouseX = 0;
int mouseY = 0;

int cantLuces = 1; //la ambiente

bool pausa = false;
bool pararTiempo = false;
bool wireframe = false;
bool texturas_habilitadas = true;
bool audio_habilitado = true;
bool mute = false; //cambiar a false para que inicie con sonido

unsigned int pasos;
bool tipoLuz = false; //false = facetado, true = interpolado
bool pantallaCompleta = false;

objeto*** estructuras = new objeto * *[largoTablero];
objeto*** bombas = new objeto * *[largoTablero];
//objeto*** enemigos = new objeto * *[largoTablero];
objeto*** fuegos = new objeto * *[largoTablero];
objeto*** bonificadores = new objeto * *[largoTablero];

list<particula*> particulas;
list<bonificador*> bonificadorEnTablero; //es la lista de los bonificadores que se dibujan, los que no, no pertenecen a esta lista
list<enemigo*> enemigos;

bomberman* jugador;

door* puerta;
int largoPantalla = WINDOW_WIDTH;
int altoPantalla = WINDOW_HEIGHT;

int getIndiceTablero(GLfloat coord) {
    return int(floor(coord / tile_size));
}

bool fin = false;
bool finJuego = false;
bool inmortal = false;

int nivel = 1;
int puntaje = 0;
int tiempoJuego = 200; //segundos

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

void aumentarNivel() {
    nivel++;
    if (nivel >= INT_MAX) {
        nivel = INT_MAX;
        finJuego = true;
    }
}

void sumarPuntaje(int puntos) {
    puntaje += puntos;
    if (puntos > INT_MAX) {
        puntos = INT_MAX;
        finJuego = true;
    }
}

void disminuirTiempo(int segundos){
    tiempoJuego -= segundos;
    if (tiempoJuego <= 0) {
        tiempoJuego = 0;
        finJuego = true;
    }
}

void pausarTiempo() {
    pararTiempo = !pararTiempo;
}

bool contieneBonificador(bonificador* bon, list<bonificador*> lista) {
    for (bonificador* elemento : lista) {
        if (elemento == bon) {
            return true;
        }
    }
    return false;
}