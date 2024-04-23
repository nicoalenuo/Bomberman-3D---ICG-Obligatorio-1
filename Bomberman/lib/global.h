#pragma once

#ifndef GLOBAL_H
#define GLOBAL_H

#include "../constantes/constantes.h"

class objeto;
class bomberman;

extern bool moverArriba;
extern bool moverAbajo;
extern bool moverDerecha;
extern bool moverIzquierda;

extern int mouseX;

extern bool texturas_habilitadas;
extern bool audio_habilitado;


extern int puntaje;

extern objeto*** estructuras;
extern objeto*** bombas;
extern objeto*** enemigos;
extern objeto*** fuegos;

extern bomberman* jugador;

extern int getPosicionXEnTablero(GLfloat coord_x, GLfloat ancho_x);

extern int getPosicionZEnTablero(GLfloat coord_z, GLfloat ancho_z);

#endif