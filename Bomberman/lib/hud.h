#pragma once
#ifndef MODELS_H
#define MODELS_H

#include "SDL.h"
#include "SDL_opengl.h"
#include "SDL_ttf.h"
#include <GL/glu.h>

enum class HUDComponentIs { top_left, top_right, top_center };

struct HUDComponent {
	HUDComponentIs position;
	SDL_Surface* surface_message;
	SDL_Surface* rgb_surface;
	int width;
	int height;
	GLuint texture_id;
	SDL_Color message_color;
};

struct color {
	float red;
	float blue;
	float green;
	float alpha;
};

#endif
