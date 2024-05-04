#pragma once

#ifndef GLOBAL_H
#define GLOBAL_H

#include "../constantes/constantes.h"
#include <list>
#include <chrono>

using namespace std;

struct vector_3 {
	GLfloat x;
	GLfloat y;
	GLfloat z;
};

class objeto;
class particula;
class bomberman;
class door;
class enemigo;

extern bool moverArriba;
extern bool moverAbajo;
extern bool moverDerecha;
extern bool moverIzquierda;

extern GLfloat mouseX;
extern GLfloat mouseY;
extern GLfloat mouseY_invertido;

extern bool wireframe;
extern bool texturas_habilitadas;
extern float velocidad_juego;
extern bool tipoLuz;
extern bool mostrarHud;
extern bool inmortal;
extern bool pararTiempo;
extern bool atravesar_paredes;

extern bool pausa;
extern bool mute;

extern int puntaje;

extern objeto*** estructuras;
extern objeto*** bombas;
extern objeto*** fuegos;
extern objeto*** bonificadores;

extern list<objeto*> borde;
extern list<particula*> particulas;
extern list<enemigo*> enemigos;

extern bomberman* jugador;
extern door* puerta;

extern int getIndiceTablero(GLfloat coord);

extern bool fin;
extern bool finJuego;
extern int nivel;
extern int puntaje; 
extern int tiempoJuego; //milisegundos
extern bool puertaAbierta;

extern chrono::duration<int> delta_time;
extern GLfloat elapsed_time;
extern chrono::high_resolution_clock::time_point current_t, previous_t;

extern void toggle(bool& valor);

extern void aumentarNivel();
extern void sumarPuntaje(int puntos);
extern void disminuirTiempo(GLfloat milisegundos);

extern int largoPantalla;
extern int altoPantalla;

#endif
