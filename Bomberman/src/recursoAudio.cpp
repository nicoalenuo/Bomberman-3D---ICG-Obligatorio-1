#include "../lib/recursoAudio.h"

recursoAudio::recursoAudio(ALuint buffer){
	this->tono = 1.f;
	this->ganancia = 1.f;
	this->posicion[0] = 0.f;
	this->posicion[1] = 0.f;
	this->posicion[2] = 0.f;
	this->velocidad[0] = 0.f;
	this->velocidad[1] = 0.f;
	this->velocidad[2] = 0.f;
	this->bucle = false;
	this->buffer = buffer;

	alGenSources(1, &this->recurso);
	alSourcef(this->recurso, AL_PITCH, this->tono);
	alSourcef(this->recurso, AL_GAIN, this->ganancia);
	alSource3f(this->recurso, AL_POSITION, this->posicion[0], this->posicion[1], this->posicion[2]);
	alSource3f(this->recurso, AL_VELOCITY, this->velocidad[0], this->velocidad[1], this->velocidad[2]);
	alSourcei(this->recurso, AL_LOOPING, this->bucle);
	alSourcei(this->recurso, AL_BUFFER, this->buffer);
}

void recursoAudio::setTono(float& tono) {
	this->tono = tono;
	alSourcef(this->recurso, AL_PITCH, tono);
}

void recursoAudio::setGanancia(float& ganancia) {
	this->ganancia = ganancia;
	alSourcef(this->recurso, AL_GAIN, ganancia);
}

void recursoAudio::setPosicion(float& x, float& y, float& z) {
	this->posicion[0] = x;
	this->posicion[1] = y;
	this->posicion[2] = z;
	alSource3f(this->recurso, AL_POSITION, x, y, z);
}

ALint estado;
void recursoAudio::play() {
	/*if (buffer_to_play != p_Buffer)
	{
		p_Buffer = buffer_to_play;
		alSourcei(p_Source, AL_BUFFER, (ALint)p_Buffer);
	}*/
	alSourcePlay(recurso);
	//ALint state = AL_PLAYING;
	/*while (state == AL_PLAYING && alGetError() == AL_NO_ERROR) {
		alGetSourcei(p_Source, AL_SOURCE_STATE, &state);
	}*/
}

void recursoAudio::detener() {
	alGetSourcei(recurso, AL_SOURCE_STATE, &estado);
	if (estado == AL_PLAYING) {
		alSourceStop(recurso);
	}
}

void recursoAudio::pausar() {
	alGetSourcei(recurso, AL_SOURCE_STATE, &estado);
	if (estado == AL_PLAYING) {
		alSourcePause(recurso);
	}
}

void recursoAudio::reanudar() {
	alGetSourcei(recurso, AL_SOURCE_STATE, &estado);
	if (estado == AL_PAUSED) {
		alSourcePlay(recurso);
	}
}

void recursoAudio::silenciar(bool mute) {
	if (mute) {
		alSourcef(recurso, AL_GAIN, 0.0f);
	} else {
		alSourcef(recurso, AL_GAIN, this->ganancia);
	}
}

recursoAudio::~recursoAudio() {
	alDeleteSources(1, &this->recurso);
}