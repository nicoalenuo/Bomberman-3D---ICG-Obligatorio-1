#pragma once

#ifndef CONTROLADORAUDIO_H
#define CONTROLADORAUDIO_H

#include "al.h"
#include "alc.h"
#include <iostream>
#include "vector"

#include "cargadorAudio.h"

using namespace std;

class ControladorAudio{
private:
	ControladorAudio();

	static ControladorAudio* instancia;

	ALCdevice* openALDevice;
	ALCcontext* openALContext;
	ALCboolean contextMadeCurrent;

public:
	static ControladorAudio* getInstance();

	void cargarAudios();

	~ControladorAudio();
};

#endif

