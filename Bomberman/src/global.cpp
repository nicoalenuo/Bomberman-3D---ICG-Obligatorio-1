#include "../lib/global.h"

int velocidad_juego = 1;

bool moverArriba = false;
bool moverAbajo = false;
bool moverDerecha = false;
bool moverIzquierda = false;

int mouseX = 0;
int mouseY = 0;

bool texturas_habilitadas = true;
bool audio_habilitado = true;
bool mute = true; //cambiar a true para que inicie con sonido

unsigned int pasos;

objeto*** estructuras = new objeto * *[largoTablero];
objeto*** bombas = new objeto * *[largoTablero];
objeto*** enemigos = new objeto * *[largoTablero];
objeto*** fuegos = new objeto * *[largoTablero];
objeto*** bonificadores = new objeto * *[largoTablero];

list<particula*> particulas;

bomberman* jugador;

int getPosicionXEnTablero(GLfloat coord_x) {
	return int(floor(coord_x  / tile_size));
}

int getPosicionZEnTablero(GLfloat coord_z) {
	return int(floor(coord_z  / tile_size));
}