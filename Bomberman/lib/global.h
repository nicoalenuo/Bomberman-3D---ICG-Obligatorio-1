#pragma once

#ifndef GLOBAL_H
#define GLOBAL_H

#include "../constantes/constantes.h"
#include <list>

using namespace std;

class objeto;
class bomberman;

extern int velocidad_juego;

extern bool moverArriba;
extern bool moverAbajo;
extern bool moverDerecha;
extern bool moverIzquierda;

extern int mouseX;
extern int mouseY;

extern bool texturas_habilitadas;
extern bool mute;

extern int puntaje;

extern objeto*** estructuras;
extern objeto*** bombas;
extern objeto*** enemigos;
extern objeto*** fuegos;
extern list<objeto*> particulas;

extern bomberman* jugador;

extern int getPosicionXEnTablero(GLfloat coord_x, GLfloat ancho_x);

extern int getPosicionZEnTablero(GLfloat coord_z, GLfloat ancho_z);
#endif