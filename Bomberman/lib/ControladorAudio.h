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

enum class sonido { muerte, explosion, bonificacion, pasos, inicioJuego, puertaAbierta, musica};

class ControladorAudio{
private:

	static ALCdevice* openALDevice;
	static ALCcontext* openALContext;
	static ALCboolean contextMadeCurrent;

	static ALuint bufferMuerte;
	static ALuint bufferExplosion;
	static ALuint bufferBonificacion;
	static ALuint bufferPasos;
	static ALuint bufferInicioJuego;
	static ALuint bufferPuertaAbierta;

	static ALuint bufferMusica;
	
	static recursoAudio* raMuerte;
	static recursoAudio* raExplosion;
	static recursoAudio* raBonificacion;
	static recursoAudio* raPasos;
	static recursoAudio* raInicioJuego;
	static recursoAudio* raPuertaAbierta;
	static recursoAudio* raMusica;

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

