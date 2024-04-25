#pragma once

#ifndef GLOBAL_H
#define GLOBAL_H

#include "../constantes/constantes.h"
#include <list>

using namespace std;

class objeto;
class particula;
class bomberman;

extern int velocidad_juego;

extern bool moverArriba;
extern bool moverAbajo;
extern bool moverDerecha;
extern bool moverIzquierda;

extern int mouseX;
extern int mouseY;

extern bool texturas_habilitadas;

extern objeto*** estructuras;
extern objeto*** bombas;
extern objeto*** enemigos;
extern objeto*** fuegos;
extern objeto*** bonificadores;
extern list<particula*> particulas;

extern bomberman* jugador;

extern int getPosicionXEnTablero(GLfloat coord_x);

extern int getPosicionZEnTablero(GLfloat coord_z);
#endif