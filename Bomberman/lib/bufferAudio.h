#pragma once

#include "al.h"
#include "alc.h"
#include <iostream>
#include "vector"

#include "cargadorAudio.h"

#ifndef BUFFERAUDIO_H
#define BUFFERAUDIO_H

using namespace std;

class bufferAudio {
private:
	static vector<ALuint> bufferSonidos;
public:
	static ALuint agregarSonido(const char* filename);
	static bool removerSonido(const ALuint& buffer);
	static void limpiarBuffer();
};

#endif BUFFERAUDIO_H
