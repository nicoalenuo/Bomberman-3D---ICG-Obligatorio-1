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

enum class sonido { muerte, bonificacion, pasos, inicioJuego, puertaAbierta, musica, timer10, menu, muerteEnemigo}; //explosion

struct sounds{
	sonido sonido;
	recursoAudio* recurso;
};

class ControladorAudio{
private:
	static ControladorAudio* instancia;
	ControladorAudio();

	ALCdevice* openALDevice;
	ALCcontext* openALContext;
	ALCboolean contextMadeCurrent;

	list<sounds> sonidos;

	//bombas
	int cantFuentesBomba;
	int actualBomba, actualMecha;
	recursoAudio** sonidosBomba, ** sonidosMecha;

	void initOpenAl();
public:
	static ControladorAudio* getInstance();
	~ControladorAudio();

	void playAudio(sonido s);
	void playAudio(sonido s, vector_3 pos);
	void playBomba(vector_3 pos);
	int  playMecha(vector_3 pos);
	void detenerMecha(int idMecha);
	void pausarAudio();
	void reanudarAudio();
	void detenerAudio();
	void silenciarAudio();
	void pausarMusica();

	void modificarVelocidad(float velocidad);
};

#endif

