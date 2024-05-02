#pragma once

#ifndef RECURSOAUDIO_H
#define RECURSOAUDIO_H

#include "al.h"
#include <iostream>

using namespace std;

class recursoAudio{
private:
	ALuint recurso;
	float tono;
	float ganancia;
	float posicion[3];
	float velocidad[3];
	bool bucle;
	ALuint buffer;
public:
	recursoAudio(ALuint buffer);

	void setTono(float& tono);
	void setGanancia(float& ganancia);
	void setPosicion(float& x, float& y, float& z);
	void setBucle(bool bucle);
	//void setVelocidad(float x, float y, float z);

	void play();
	void detener();
	void pausar();
	void reanudar();

	~recursoAudio();

};

#endif RECURSOAUDIO_H
