#include "../lib/global.h"

int velocidad_juego = 1;

bool moverArriba = false;
bool moverAbajo = false;
bool moverDerecha = false;
bool moverIzquierda = false;

int mouseX = 0;
int mouseY = 0;

bool texturas_habilitadas = true;

int puntaje = 0;

objeto*** estructuras = new objeto * *[largoTablero];
objeto*** bombas = new objeto * *[largoTablero];
objeto*** enemigos = new objeto * *[largoTablero];
objeto*** fuegos = new objeto * *[largoTablero];

list<objeto*> particulas;

bomberman* jugador;

int getPosicionXEnTablero(GLfloat coord_x, GLfloat ancho_x) {
	return int(coord_x + (ancho_x / 2)) / int(tile_size);
}

int getPosicionZEnTablero(GLfloat coord_z, GLfloat ancho_z) {
	return int(coord_z + (ancho_z / 2)) / int(tile_size);
}
