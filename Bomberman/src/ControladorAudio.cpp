#include "../lib/ControladorAudio.h"

ALCdevice* ControladorAudio::openALDevice = nullptr;
ALCcontext* ControladorAudio::openALContext = nullptr;
ALCboolean ControladorAudio::contextMadeCurrent = false;

ALuint ControladorAudio::bufferMuerte;
ALuint ControladorAudio::bufferExplosion;
ALuint ControladorAudio::bufferBonificacion;
ALuint ControladorAudio::bufferPasos;

void ControladorAudio::initOpenAl() {
	openALDevice = alcOpenDevice(nullptr); //obtengo el dispositivo
	if (!openALDevice) {
		cerr << "Error al inicilizar openAL" << endl;
		exit(1);
	}

	openALContext = alcCreateContext(openALDevice, nullptr); //creo el contexto
	if (!openALContext) {
		cerr << "Error al crear el contexto del audio" << endl;
		exit(1);
	}

	contextMadeCurrent = alcMakeContextCurrent(openALContext); //actulizo el contexto
	if (!contextMadeCurrent || (contextMadeCurrent != ALC_TRUE)) {
		cerr << "Error al actualizar el contexto del audio" << endl;
		exit(1);
	}
}

void ControladorAudio::cargarAudios() {
	
	initOpenAl();

	bufferMuerte = bufferAudio::agregarSonido("audio/muerte.wav");
	bufferExplosion = bufferAudio::agregarSonido("audio/explosion.wav");
	bufferBonificacion = bufferAudio::agregarSonido("audio/bonificacion.wav");
	bufferPasos = bufferAudio::agregarSonido("audio/pasos.wav");

	recursoAudio::initRecurso();
}
void aux() {
	Sleep(2000);
	cout << "Despues" << endl;
}

void ControladorAudio::playAudio(sonido s) {
	switch (s){
		case sonido::muerte:
			recursoAudio::Play(bufferMuerte);
			break;
		case sonido::explosion:
			recursoAudio::Play(bufferExplosion);
			break;
		case sonido::bonificacion:
			recursoAudio::Play(bufferBonificacion);
			break;
		case sonido::pasos:
			//cout << "Antes" << endl;
			//thread th(aux);
			
			//th.detach();
			/*if (th.joinable()) {
				th.join();
			}*/
			recursoAudio::Play(bufferPasos);
			break;
	}
}

//Se deberia controlar las excepciones
void ControladorAudio::limpiarAudios() {
	bufferAudio::limpiarBuffer();
	alcMakeContextCurrent(nullptr);
	alcDestroyContext(openALContext);
	alcCloseDevice(openALDevice);
}