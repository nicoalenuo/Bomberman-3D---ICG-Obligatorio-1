#pragma once

#ifndef CONTROLADORAUDIO_H
#define CONTROLADORAUDIO_H

#include "al.h"
#include "alc.h"
#include <iostream>
#include "vector"

#include "bufferAudio.h"
#include "recursoAudio.h"

using namespace std;

class ControladorAudio{
private:

	static ALCdevice* openALDevice;
	static ALCcontext* openALContext;
	static ALCboolean contextMadeCurrent;

	static void initOpenAl();
public:

	static void cargarAudios();
	static void limpiarAudios();

};

#endif

