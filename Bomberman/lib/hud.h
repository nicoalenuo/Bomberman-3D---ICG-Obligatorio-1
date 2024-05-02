#pragma once

#ifndef HUD_H
#define HUD_H

#include "SDL.h"
#include "SDL_opengl.h"
#include "SDL_ttf.h"
#include <GL/glu.h>

enum class position { 
	top_left, top_right,
	top_center, 
	left,
	right,
	center,
	bottom_left,
	bottom_right,
	bottom_center 
};

class hud {
	public: 
		position posicion;
		SDL_Surface* mensajeSurface;
		SDL_Surface* colorSurface;
		int width;
		int height;
		GLuint idTextura;
		SDL_Color colorMensaje;	
};

#endif

