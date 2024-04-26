#pragma once

#ifndef CONTROLADORAUDIO_H
#define CONTROLADORAUDIO_H

#include "al.h"
#include "alc.h"
#include <iostream>
#include "vector"
#include <thread>
#include<windows.h> 

#include "bufferAudio.h"
#include "recursoAudio.h"
#include "global.h"

using namespace std;

enum class sonido { muerte, explosion, bonificacion, pasos};

class ControladorAudio{
private:

	static ALCdevice* openALDevice;
	static ALCcontext* openALContext;
	static ALCboolean contextMadeCurrent;

	static ALuint bufferMuerte;
	static ALuint bufferExplosion;
	static ALuint bufferBonificacion;
	static ALuint bufferPasos;
	
	static recursoAudio* raMuerte;
	static recursoAudio* raExplosion;
	static recursoAudio* raBonificacion;
	static recursoAudio* raPasos;

	static void initOpenAl();
public:

	static void cargarAudios();

	static void playAudio(sonido s);
	static void pausarAudio();
	static void reanudarAudio();
	static void detenerAudio();

	static void limpiarAudios();

};

#endif

