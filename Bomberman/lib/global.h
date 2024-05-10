#pragma once

#ifndef GLOBAL_H
#define GLOBAL_H

#include "../constantes/constantes.h"
#include <chrono>
#include <list>

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

//flags
extern bool wireframe;
extern bool texturas_habilitadas;
extern bool tipoLuz;
extern bool mostrarHud;
extern bool inmortal;
extern bool pararTiempo;
extern bool atravesar_paredes;
extern bool pausa;
extern bool mute;
extern bool fin;
extern bool finJuego;
//-----

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

extern int nivel;
extern int puntaje; 
extern int tiempoJuego; //milisegundos
extern float velocidad_juego;
extern bool puertaAbierta;
extern bool temporizador;

extern GLfloat tiempo_entre_frames;
extern chrono::high_resolution_clock::time_point marca_tiempo_anterior, marca_tiempo_actual;

extern void toggle(bool& valor);

extern void aumentarNivel();
extern void sumarPuntaje(int puntos);
extern void disminuirTiempo(GLfloat milisegundos);

#endif
