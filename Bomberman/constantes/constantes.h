#pragma once

#ifndef CONSTANTES_H
#define CONSTANTES_H

#include "SDL_opengl.h"

#include <map>

const unsigned int frameDelay = 33 ; //33 milisegundos entre cada frame
const double generadorTerreno = 0.6; //probabilidad de 0 a 1 de generar terreno destructible
const double generadorBonificador = 0.05;
const GLfloat tile_size = 2;

const float PI = 3.14159f;

const float radians = PI / 180.0f;

const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;
const float WINDOW_RATIO = (float) WINDOW_WIDTH / (float) WINDOW_HEIGHT;

const float velocidadCamara = 10;

const int largoTablero = 29;
const int anchoTablero = 11;

#endif
