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

enum class sonido { muerte, bonificacion, pasos, inicioJuego, puertaAbierta, musica, timer10}; //explosion

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

	//bombas
	static int cantFuentesBomba;
	static int actualBomba, actualMecha;
	static recursoAudio** sonidosBomba, ** sonidosMecha;

	static void initOpenAl();
public:

	static void cargarAudios();

	static void playAudio(sonido s);
	static void playAudio(sonido s, vector_3 pos);
	static void playBomba(vector_3 pos);
	static int  playMecha(vector_3 pos);
	static void detenerMecha(int idMecha);
	static void pausarAudio();
	static void reanudarAudio();
	static void detenerAudio();
	static void silenciarAudio();

	static void modificarVelocidad(float velocidad);

	static void limpiarAudios();

};

#endif

