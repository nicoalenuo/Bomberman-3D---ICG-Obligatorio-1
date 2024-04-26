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
bool wireframe = false;
bool texturas_habilitadas = true;
bool audio_habilitado = true;
bool mute = true; //cambiar a true para que inicie con sonido

unsigned int pasos;
bool tipoLuz = false; //false = facetado, true = interpolado
bool pantallaCompleta = false;

objeto*** estructuras = new objeto * *[largoTablero];
objeto*** bombas = new objeto * *[largoTablero];
objeto*** enemigos = new objeto * *[largoTablero];
objeto*** fuegos = new objeto * *[largoTablero];

list<objeto*> particulas;

bomberman* jugador;

bool fin = false;
bool finJuego = false;
bool inmortal = false;

int nivel = 1;
int puntaje = 0;
int tiempoJuego = 200; //segundos

int getPosicionXEnTablero(GLfloat coord_x, GLfloat ancho_x) {
	return int(coord_x + (ancho_x / 2)) / int(tile_size);
}

int getPosicionZEnTablero(GLfloat coord_z, GLfloat ancho_z) {
	return int(coord_z + (ancho_z / 2)) / int(tile_size);
}

void toggle_pausa() {
    pausa = !pausa;
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

void sumarPuntaje(int puntos){
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