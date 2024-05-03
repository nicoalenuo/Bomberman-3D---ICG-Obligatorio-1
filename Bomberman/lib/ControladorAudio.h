#pragma once

#ifndef CONTROLADORAUDIO_H
#define CONTROLADORAUDIO_H

#include "al.h"
#include "alc.h"
#include <iostream>
#include "vector"
#include <thread>
#include <windows.h> 

#include "bufferAudio.h"
#include "recursoAudio.h"
#include "global.h"

using namespace std;

enum class sonido { muerte, explosion, bonificacion, pasos, inicioJuego, puertaAbierta, musica};

struct sounds{
	sonido sonido;
	recursoAudio* recurso;
};

class ControladorAudio{
private:

	static ALCdevice* openALDevice;
	static ALCcontext* openALContext;
	static ALCboolean contextMadeCurrent;

	static list<sounds> sonidos;

	static void initOpenAl();
public:

	static void cargarAudios();

	static void playAudio(sonido s);
	static void pausarAudio();
	static void reanudarAudio();
	static void detenerAudio();
	static void silenciarAudio();

	static void limpiarAudios();

};

#endif

